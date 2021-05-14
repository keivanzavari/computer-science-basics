from typing import Dict, List

# Problem:
# Given a rod of length n and a # table of prices p[i] for i in [1, 2, ..., n] determine the maximum revenue r[n]
# obtainable by cutting up the rod and selling the pieces. Note that if the price p[n] for a rod of length n is
# large enough, an optimal solution may require no cutting at all.


# Following the natural formulation of
# r_n = max (p_i + r_(n-i)) over 1 <= i <= n,
#
# simple O(2^n) formulation becomes
def cut_rod_brute_force(prices: Dict[int, int], length: int) -> int:
    if length == 0:
        return 0
    q = float("-inf")
    for i in range(1, length + 1):
        q = max(q, prices[i] + cut_rod_brute_force(prices, length - i))

    return q


# Top-down with memoization
def memoized_cut_rod(prices: Dict[int, int], length: int) -> int:
    r = [float("-inf")] * len(prices.keys())
    return memoized_cut_rod_aux(prices, length, r)


def memoized_cut_rod_aux(prices: Dict[int, int], length: int, r: List[float]) -> int:
    # Since arrays are zero indexed and we are using a simple array here, we need to use length-1.
    if r[length - 1] >= 0:
        return r[length]

    if length == 0:
        q = 0
    else:
        q = float("-inf")
        for i in range(1, length + 1):
            q = max(q, prices[i] + memoized_cut_rod_aux(prices, length - i, r))

    r[length - 1] = q
    return q


# Bottom-up method
# We sort the subproblems by size and solve them in size order, smallest first. When solving a particular subproblem,
# we have already solved all of the smaller subproblems its solution depends upon, and we have saved their solutions.
# We solve each sub-problem only once, and when we first see it, we have already solved all of its prerequisite
# subproblems.
def bottom_up_cut_rod(prices: Dict[int, int], length: int) -> Dict[int, int]:
    r = {0: 0}
    # If one prefers to use a list: r = [0] * (length + 1)
    for j in range(1, length + 1):
        q = float("-inf")
        for i in range(1, j + 1):
            q = max(q, prices[i] + r[j - i])
        r[j] = q
    return r


def extended_bottom_up_cut_rod(prices: Dict[int, int], length: int) -> tuple:
    r = {0: 0}
    sizes = {1: 1}
    for j in range(1, length + 1):
        q = float("-inf")
        for i in range(1, j + 1):
            if q < prices[i] + r[j - i]:
                # When j is equal to i, no cutting is preferred.
                q = prices[i] + r[j - i]
                sizes[j] = i
        r[j] = q
    return r, sizes


prices = {1: 1, 2: 5, 3: 8, 4: 9, 5: 10, 6: 17, 7: 17, 8: 20, 9: 24, 10: 30}
length = 10

# q = cut_rod_brute_force(prices, length)
# q = memoized_cut_rod(prices, length)
# all_lengths_solutions = bottom_up_cut_rod(prices, length)
solutions, sizes = extended_bottom_up_cut_rod(prices, length)
