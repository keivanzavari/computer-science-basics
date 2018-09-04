#include <iostream>
#include <string>

#include <queue> // queue and priority_queue
#include <utility> //make_pair

#include <vector>
#include <algorithm> // make_heap

// have a look here
// http://rosettacode.org/wiki/Priority_queue#C.2B.2B

// highest priority is maximum here
void exampleSTL () {
    std::priority_queue<std::pair<int, std::string> > pq;
    pq.push(std::make_pair(3, "Clear drains"));
    pq.push(std::make_pair(4, "Feed cat"));
    pq.push(std::make_pair(5, "Make tea"));
    pq.push(std::make_pair(1, "Solve RC tasks"));
    pq.push(std::make_pair(2, "Tax return"));

    while (!pq.empty()) {
        std::cout << pq.top().first << ", " << pq.top().second << std::endl;
        pq.pop();
    }
}

void exampleHeap() {
    std::vector<std::pair<int, std::string> > pq;
    pq.push_back(std::make_pair(3, "Clear drains"));
    pq.push_back(std::make_pair(4, "Feed cat"));
    pq.push_back(std::make_pair(5, "Make tea"));
    pq.push_back(std::make_pair(1, "Solve RC tasks"));

    // heapify
    // Up to linear in three times the distance between first and last:
    // Compares elements and potentially swaps (or moves) them until
    // rearranged as a heap.
    std::make_heap(pq.begin(), pq.end());

    // enqueue
    // std:priority_queue does this automatically every time you call push
    pq.push_back(std::make_pair(2, "Tax return"));
    std::push_heap(pq.begin(), pq.end());

    while (!pq.empty()) {
        // peek
        std::cout << pq[0].first << ", " << pq[0].second << std::endl;
        // dequeue
        std::pop_heap(pq.begin(), pq.end());
        pq.pop_back();
    }
}

int main () {
    exampleHeap();

    return 0;

}
