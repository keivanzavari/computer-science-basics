from typing import List
import unittest


def counting_sort(vector: List[int]) -> List[int]:
    if not vector:
        return vector
    # In counting sort, values are bounded by number k.
    k = max(vector)
    key_lists = []
    for _ in range(k):
        key_lists.append([])

    for v in vector:
        # The index in key_lists is not always directly vector[j]
        try:
            key_lists[v - 1].append(v)
        except:
            print(f"value: {v}, k: {k}")
            return []

    output = []
    for i in range(k):
        output.extend(key_lists[i])

    return output


class TestCountingSort(unittest.TestCase):
    def test_empty(self):
        self.assertEqual(counting_sort([]), [])

    def test_sorted(self):
        values = [1, 3, 4]

        self.assertTrue(counting_sort(values), values)

    def test_random(self):
        values = [1, 3, 8, 4, 7, 3, 9]

        self.assertEqual(counting_sort(values), sorted(values))


if __name__ == '__main__':
    unittest.main()
