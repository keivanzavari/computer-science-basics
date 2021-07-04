#include <iostream>

int peakElementSweep(int arr[], int n) {
  if (n == 0 || n == 1) return 0;
  if (arr[0] > arr[1]) return 0;
  if (arr[n - 1] > arr[n - 2]) return n - 1;
  for (int idx = 1; idx < n - 1; ++idx) {
    if (arr[idx - 1] < arr[idx] && arr[idx] > arr[idx + 1]) return idx;
  }
  return -1;
}

int peakElement(int arr[], int n) {
  std::cout << "peak with input size " << n << "\n";
  if (n == 0 || n == 1) return 0;
  if (arr[0] > arr[1]) return 0;
  if (arr[n - 1] > arr[n - 2]) return n - 1;
  int left = 0;
  int right = n - 1;
  int mid = (left + right) / 2;
  while (left < right) {
    std::cout << "mid: " << mid << "\n";
    if (mid == 1 || mid == n - 1) {
      return -1;
    }
    if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
      return mid;
    }
    if (arr[mid] > arr[mid - 1]) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
    mid = (left + right) / 2;
  }

  return -1;
}

int main() {
  int arr[] = {108, 366, 997, 656, 248, 607, 150, 698, 351, 84,  3,   404, 239, 851, 56,
               893, 206, 22,  836, 192, 912, 496, 489, 440, 984, 324, 337, 758, 359, 727,
               303, 466, 92,  651, 121, 691, 609, 623, 389, 959, 58,  391, 362, 296, 241};
  std::cout << peakElement(arr, sizeof(arr) / sizeof(int)) << "\n";
  return 0;
}
