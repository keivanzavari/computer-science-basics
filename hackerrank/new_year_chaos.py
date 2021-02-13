#! /usr/bin/env python3
import pathlib

# It requires one swapping to be sorted.
# swap 5 with 4.
# If more than two swaps is required for a number, print "Too chaotic" and stop counting
# e.g. [4,1,2,3], 4 had to swap 3 times to get to the front.

# go through the list,
# if the number after the current number is larger, no swap was needed, so move on to next number.
# if it is smaller, then that one has swapped. Add it as the key of a dictionary, to count its number of swaps.
# In [4,1,3,2], both 3 and 4 have swapped. 4, 3 times, and 3, 1 time.

# for a number determine its original location.
# for its current position, the number of swaps it has done is the difference of these two.

# if the number is at its place, but the one on its right is smaller, it has swapped once.
# [1,4,3,2,5]
# [1,2,3,4,5,6]
queue = [1, 2, 3, 5, 4, 6, 7]
queue = [1, 4, 3, 2, 5]
queue = [4, 1, 3, 2]
queue = [2, 5, 1, 3, 4]
queue = [1, 2, 5, 3, 7, 8, 6, 4]
queue = [2, 1]


def minimum_bribes(queue):
    swaps = {}
    num_bribes = 0
    for idx in range(len(queue)):
        if queue[idx] >= idx + 4:
            # num_swaps = queue[idx] - idx - 1
            # print(f"idx {idx}, num_swaps {num_swaps}")
            # if num_swaps > 2:
            print("Too chaotic")
            break

        # Now go to the end of the list and count the number of numbers smaller than this one.
        the_rest_of_queue = queue[idx:]
        num_swaps = 0
        for v in the_rest_of_queue:
            if queue[idx] > v:
                num_swaps += 1
                num_bribes += 1
        swaps[queue[idx]] = num_swaps

    print(f"swaps {swaps}")
    print(num_bribes)


def read_file(input_file: pathlib.Path):
    """
    Input Format

    The first line contains an integer , the number of test cases.

    Each of the next  pairs of lines are as follows:
    - The first line contains an integer , the number of people in the queue
    - The second line has  space-separated integers describing the final state of the queue.
    """
    values = input_file.read_text()
    values = values.split("\n")
    # num_cases = int(values[0])
    # length = int(values[1])
    # queue_lengths = []
    # for i in range(1, len(values), 2):
    #     queue_lengths.append(int(values[i]))

    queues = []
    for i in range(2, len(values), 2):
        splitted = values[i].split(" ")
        queue = [int(v) for v in splitted]
        queues.append(queue)
    return queues


if __name__ == "__main__":
    input_file = pathlib.Path(
        "/home/keivan/playground/math_coding_problems/hackerrank/resources/test_case_new_year_chaos.txt")
    queues = read_file(input_file)
    # for queue in queues:
    minimum_bribes(queues[3])
