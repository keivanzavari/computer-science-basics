
// 1) Write a program, w/ main() + 2 functions, which are executed by a thread each. One function/thread will print the
// letter A. And the other function/thread will print the letter B. The output of the program will be "ABABABAB...
// (forever)"

#include <condition_variable>
// #include <functional>
#include <atomic>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class MultipleWorkers {
 public:
  MultipleWorkers(int num_workers) : num_workers_(num_workers), thread_state_(num_workers, false) {
    active_worker_ = 1;
    run_number_ = 0;
    for (int worker_number = 1; worker_number <= num_workers; ++worker_number) {
      threads_.emplace_back([this](int num) { do_work(num); }, worker_number);
    }
  }

  ~MultipleWorkers() {
    for (auto &thread : threads_) thread.join();
  }

  void do_work(int number) {
    while (run_number_ < 30) {
      std::unique_lock<std::mutex> lock(mx_);
      cv_.wait(lock, [&] {  // what to return here to ensure that the previous worker will emit once it is finished.
        return number == active_worker_;

      });

      std::cout << "worker " << number << "\t";

      ++active_worker_;
      if (active_worker_ > num_workers_) {
        active_worker_ = 1;
      }
      ++run_number_;
      lock.unlock();
      cv_.notify_all();
    }
  }

  void do_work_without_loop(int number) {
    std::unique_lock<std::mutex> lock(mx_);
    cv_.wait(lock, [&] {  // what to return here to ensure that the previous worker will emit once it is finished.
      return number == active_worker_;

    });

    std::cout << "worker " << number << "\t";

    ++active_worker_;
    if (active_worker_ > num_workers_) {
      active_worker_ = 1;
    }
    ++run_number_;
    lock.unlock();
    cv_.notify_one();
  }

 private:
  const int num_workers_;
  std::vector<std::thread> threads_;
  std::vector<bool> thread_state_;
  std::mutex mx_;
  std::condition_variable cv_;
  std::atomic<int> run_number_;
  std::atomic<int> active_worker_;
};

int main() {
  MultipleWorkers multiple_workers(3);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::cout << "\tfinished\n";
  return 0;
}
