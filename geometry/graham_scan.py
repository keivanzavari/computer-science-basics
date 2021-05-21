#! /usr/bin/env python3
from typing import List, Tuple
import matplotlib.pyplot as plt
import sys
import pathlib
PARENT = pathlib.Path(__file__).parent.absolute().parent
sys.path.insert(0, PARENT.as_posix())

import lib.geometry
from lib.point import Point
from lib.limits import Range

# -----------------------------
# Graham Scan algorithm
# let points be the list of points
# let stack = empty_stack()
#
# find the lowest y-coordinate and leftmost point, called P0
# sort points by polar angle with P0, if several points have the same polar angle then only keep the farthest
#
# for point in points:
#     # pop the last point from the stack if we turn clockwise to reach this point
#     while count stack > 1 and ccw(next_to_top(stack), top(stack), point) <= 0:
#         pop stack
#     push point to stack
# end
# -----------------------------


class Stack:
    def __init__(self):
        self.data = []

    def push(self, el):
        self.data.append(el)

    def pop(self):
        return self.data.pop()

    def top(self):
        if (self.data):
            return self.data[-1]
        raise RuntimeError("stack is empty")

    def next_to_top(self):
        if (self.data) and len(self.data) >= 2:
            return self.data[-2]
        raise RuntimeError("stack is not large enough")

    def __len__(self):
        return len(self.data)


def test_sorting_based_on_polar_angle(points: List[Point]) -> None:
    sorted_points = sorted(points[1:], key=lambda p: lib.geometry.get_angle(points[0], p))

    idx = 1
    margin = 0.2
    for p in sorted_points:
        plt.plot([points[0].x, p.x], [points[0].y, p.y], ":")
        plt.text(p.x + margin, p.y + margin, f"point {idx}")
        idx += 1
    # The numbers should appear in ascending order with respect to the angle they make with point zero.


def compute_ccw(point1: Point, point2: Point, point3: Point) -> float:
    """
    Determining whether three points constitute a "left turn" or a "right turn" does not require computing
    the actual angle between the two line segments, and can actually be achieved with simple arithmetic only.
    For three points P1, P2 and P3, compute the z-coordinate of the cross product of the two vectors P1 P2 and P1P3,
    which is given by the expression:
    (P2.x - P1.x) * (P3.y - P1.y) - (P2.y - P1.y) * (P3.x - P1.x)
    If the result is 0, the points are collinear; if it is positive, the three points constitute a
    "left turn" or counter-clockwise orientation, otherwise a "right turn" or clockwise orientation
    (for counter-clockwise numbered points).
    """
    _, _, res = lib.geometry.cross(point2 - point1, point3 - point1)

    return res


def generate_random_points(num_points: int, points_range: Range) -> List[Point]:
    import random
    # seed random number generator generate random numbers between 0-1
    random.seed(1)
    values = []
    for _ in range(num_points):
        values.append(points_range.lo + random.random() * (points_range.hi - points_range.lo))

    points = set()
    while len(points) < num_points:
        x = random.choice(values)
        y = random.choice(values)
        points.add(Point(x, y))
    return list(points)


def move_left_bottom_to_first(points: List[Point]):
    min_point = min(points)
    idx = points.index(min_point)
    points[0], points[idx] = points[idx], points[0]


if __name__ == "__main__":
    # points = [Point(1, 2.5), Point(-2, -5), Point(-1, 3), Point(2.0, 0.5), Point(1.0, 5.0), Point(0, -1), Point(8, 0)]

    points = generate_random_points(20, Range(-5, 5))
    move_left_bottom_to_first(points)
    sorted_points = sorted(points[1:], key=lambda p: lib.geometry.get_angle(points[0], p))
    sorted_points.insert(0, points[0])

    stack = Stack()
    for point in sorted_points:
        # pop the last point from the stack if we turn clockwise to reach this point
        angle = 0.0
        if len(stack) >= 2:
            while len(stack) >= 2 and compute_ccw(stack.next_to_top(), stack.top(), point) < 0:
                p = stack.pop()
        stack.push(point)

    plt.figure()
    for p in points:
        plt.plot(p.x, p.y, "*", markersize=12)

    x = [p.x for p in stack.data]
    y = [p.y for p in stack.data]
    x.append(x[0])
    y.append(y[0])
    plt.plot(x, y, "-")

    test_sorting_based_on_polar_angle(points)
    plt.grid()
    plt.show()
