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


# you know the len of the list,
# you also know untill your position, what you have come across
# at position 3, you encounter 5 while you have come across only 1 & 2 which are smaller.
# at position 7 you get 6 and you have come across 7 & 8 which are larger.
# so they both have bribed 6
# so when you come across 3 and the previous one is larger number of bribes increases by 1
# keep a list of numbers that are not earlier than their position
# so at position 4, only 5 is on that list.
# when we reach position 5 we remove that element. so it is FIFO
# number of bribes is the length of this list at each position

# one cavity
# If a number appears after its index, we are going to make a mistake.
# let's say 6 appears after position 6, then we have to count how many there are after 6 that are smaller than 6


def minimum_bribes_single_loop(queue):
    num_bribes = 0
    numbers_before_their_place = []
    numbers_after_their_place = []
    # always do insert at 0 to make the list a queue
    for idx in range(len(queue)):
        # if idx % 5000 == 0:
        #     print(idx)
        if queue[idx] > idx + 3:
            print("Too chaotic")
            break

        if queue[idx] > idx + 1:

            # Number appearing sooner that it should.
            # numbers_before_their_place.insert(0, queue[idx])
            num_bribes += (queue[idx] - idx - 1)
            # print(f"{queue[idx]} appears sooner than it should, num_bribes: {num_bribes}")

        if queue[idx] <= idx + 1:
            # Number appearing after it should.
            if idx < int(len(queue) / 2):
                # print(f"{queue[idx]} appears after it should. Look back")
                potential = queue[idx]
                # Have all numbers smaller that this appeared?
                numbers_smaller = [v for v in queue[0:idx + 1] if v < queue[idx]]
                if len(numbers_smaller) != queue[idx] - 1:
                    numbers_after_their_place.append(potential)
            else:
                # from this position to the end, how many smaller numbers are there?
                numbers_smaller = [v for v in queue[idx + 1:] if v < queue[idx]]
                # print(f"{queue[idx]} appears after it should. Look front, numbers_smaller: {numbers_smaller}")
                numbers_after_their_place += numbers_smaller

        # if we come across a number that is smaller than the numbers of this list,

        # remove the out of place numbers from the list when we reach at their index.
        # if idx + 1 in numbers_before_their_place:
        #     numbers_before_their_place.remove(idx + 1)

        # print(f"at position {idx+1}, numbers_before_their_place: {numbers_before_their_place}")
        # count the len of out of place ones and add it to the number of bribes
        # num_bribes += len(numbers_before_their_place)

    num_bribes += len(numbers_after_their_place)
    print(num_bribes)


def minimum_bribes_single_loop_2(queue):
    # print(f"queue: {queue}")
    num_bribes = 0
    numbers_after_their_place = []
    for idx in range(len(queue)):
        if queue[idx] > idx + 3:
            print("Too chaotic")
            return

        if queue[idx] > idx + 1:
            # Number appearing sooner that it should.
            num_bribes += (queue[idx] - idx - 1)
        else:
            # Number appearing after it should.
            if idx < int(len(queue) / 2):
                potential = queue[idx]
                # Have all numbers smaller that this appeared?
                numbers_smaller = [v for v in queue[0:idx + 1] if v < queue[idx]]
                if len(numbers_smaller) != queue[idx] - 1:
                    numbers_after_their_place.append(potential)
            else:
                # from this position to the end, how many smaller numbers are there?
                numbers_smaller = [v for v in queue[idx + 1:] if v < queue[idx]]
                numbers_after_their_place += numbers_smaller

    num_bribes += len(numbers_after_their_place)
    print(num_bribes)


queue = [1, 2, 3, 5, 4, 6, 7]
queue = [4, 1, 3, 2]
queue = [1, 2, 5, 3, 7, 8, 6, 9, 4]
queue = [1, 4, 3, 2, 5]
queue = [2, 5, 1, 3, 4]

if __name__ == "__main__":
    input_file = pathlib.Path(
        "/home/keivan/playground/math_coding_problems/hackerrank/resources/test_case_new_year_chaos.txt")
    queues = read_file(input_file)
    # for queue in queues:
    minimum_bribes_single_loop_2(queue)
    # minimum_bribes(queue)
