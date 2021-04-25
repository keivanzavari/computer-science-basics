from typing import Optional
import copy

# An array, visualized as a nearly complete binary tree
# No pointers required! Height of a binary heap is O(lg n)
#
#                  [0]
#              /        \
#            /           \
#          [1]            [2]
#        /     \         /   \
#     [3]       [4]     [5]   [6]
#    /  \      /
# [7]   [8] [9] ...


class MinHeap:
    def __init__(self, data_: list = []):
        self.data = data_
        self.size = len(data_)

    def at(self, i):
        try:
            return self.data[i]
        except:
            raise IndexError(f"Index {i} doesn't exist.")

    def root(self):
        return self.data[0]

    def parent(self, i):
        parent_idx = i // 2
        return self.at(parent_idx)

    def left_idx(self, i):
        return 2 * i + 1

    def left(self, i):
        return self.at(self.left_idx(i))

    def right_idx(self, i):
        return 2 * i + 2

    def right(self, i):
        return self.at(self.right_idx(i))

    def swap(self, idx1: int, idx2: int) -> None:
        # print(f"swap {idx1} ({self.at(idx1)}) with {idx2} ({self.at(idx2)}).")

        self.data[idx2], self.data[idx1] = self.data[idx1], self.data[idx2]

    def build_min_heap(self):
        """
        Will produce a max-heap from an unordered array.
        """
        for i in range((self.size - 1) // 2, -1, -1):
            # print("-----------------------------------")
            # print(f"min heapify {i} ({self.at(i)}). Before: {self.data}")
            self.min_heapify(i)
            # print(f"after: {self.data}")

    def _swap_with_child(self, idx: int, case="") -> None:
        if case == "left":
            self.swap(idx, self.left_idx(idx))
        elif case == "right":
            self.swap(idx, self.right_idx(idx))

    def min_heapify(self, idx: int) -> None:
        """
        Min heap property: The key of a node is <= than the keys of its children.
        Correct a single violation of the heap property in a subtree at its root.
            * Assume that the trees rooted at left(i) and right(i) are min-heaps.
            * If element A[i] violates the min-heap property, correct violation by
            “trickling” element A[i] down the tree, making the subtree rooted at index i a max-heap
        """
        # get children, if there are no children, then nothing to do.
        # if left doesn't exist, look to right.
        # if they both exist, look at the greater.
        # print(f"min heapify {idx} ({self.at(idx)}).")

        if (self.left_idx(idx) < self.size) and (self.right_idx(idx) < self.size):
            swap_case = ""
            swap_idx = -1
            if self.left(idx) < self.right(idx):
                swap_case = "left" if self.left(idx) < self.at(idx) else ""
                swap_idx = self.left_idx(idx)
            elif self.right(idx) < self.left(idx):
                swap_case = "right" if self.right(idx) < self.at(idx) else ""
                swap_idx = self.right_idx(idx)
            if swap_case:
                self._swap_with_child(idx, swap_case)
                self.min_heapify(swap_idx)

        elif self.left_idx(idx) < self.size:

            if self.left(idx) < self.at(idx):
                swap_case = "left"
                # Min heap property is violated
                # swap the content
                self._swap_with_child(idx, swap_case)
                self.min_heapify(self.left_idx(idx))

        elif self.right_idx(idx) < self.size:

            if self.right(idx) < self.at(idx):
                # Max heap property is violated
                swap_case = "right"
                self._swap_with_child(idx, swap_case)

                self.min_heapify(self.right_idx(idx))


def heap_sort(vec: list) -> list:
    max_heap = MinHeap(vec)
    max_heap.build_min_heap()
    while max_heap.size > 0:
        last_idx = max_heap.size - 1
        max_heap.swap(0, last_idx)
        # popping is slower than simply moving the index. Here it is faster that we simply modify the heap size and
        # leave its underlying data untacked.
        # However, modifying the size is also not so nice because the size of the heap doesn't really change.
        # res.append(max_heap.data.pop())
        max_heap.size -= 1
        max_heap.min_heapify(0)
    return max_heap.data


if __name__ == '__main__':
    # entry = [16, 4, 10, 14, 7, 9, 3, 2, 8, 1]
    entry = [4, 1, 3, 2, 16, 9, 10, 14, 8, 7]
    # heap = MinHeap(entry)
    # heap.min_heapify(3)

    # res = [16, 14, 10, 8, 7, 9, 3, 2, 4, 1]
    # print(heap.data)

    res = heap_sort(entry)
    print(res)
