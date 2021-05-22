from typing import Optional, Tuple
from functools import singledispatch
import numpy as np

from lib.point import Point
import lib.geometry
import lib.math_utils


class Line:
    def __init__(self, point_a: Point, point_b: Point) -> None:
        if point_a == point_b:
            raise ValueError("Two points are the same. No line can be constructed.")

        self.a, self.b, self.c = lib.geometry.cross(point_a, point_b)

    def are_on_the_same_side(self, point_1: Point, point_2: Point) -> bool:
        return np.sign(self.a * point_1.x + self.b * point_1.y + self.c) == np.sign(self.a * point_2.x +
                                                                                    self.b * point_2.y + self.c)

    def normalize(self) -> Tuple[float, float, float]:
        sqrt_abc = np.sqrt(self.a * self.a + self.b * self.b + self.c * self.c)
        return (self.a / sqrt_abc, self.b / sqrt_abc, self.c / sqrt_abc)

    def as_tuple(self) -> Tuple[float, float, float]:
        return (self.a, self.b, self.c)

    def __str__(self) -> str:
        return f"line: {self.a} x + {self.b} y + {self.c} = 0"


class LineSegment:
    def __init__(self, point_a: Point, point_b: Point):
        self.point_a = point_a
        self.point_b = point_b

    def intersects_with_horizontal_line(self, y: float) -> bool:
        if (self.point_a.y > y and self.point_b.y > y):
            return False
        if (self.point_a.y < y and self.point_b.y < y):
            return False
        return True

    def __str__(self) -> str:
        return f"line segment between points {self.point_a}, {self.point_b}"


def convert_to_line(line_segment: LineSegment) -> Line:
    return Line(line_segment.point_a, line_segment.point_b)


@singledispatch
def compute_intersection(_, __) -> Optional[Point]:
    return None


@compute_intersection.register(Line)
def _(line_1: Line, line_2: Line) -> Optional[Point]:
    intersection = lib.geometry.cross3(line_1.as_tuple(), line_2.as_tuple())
    if lib.math_utils.are_almost_equal(intersection[2], 0):
        return None

    return Point(intersection[0] / intersection[2], intersection[1] / intersection[2])


@compute_intersection.register(LineSegment)
def _(line_segment_1: LineSegment, line_segment_2: LineSegment) -> Optional[Point]:
    line_1 = convert_to_line(line_segment_1)
    if (line_1.are_on_the_same_side(line_segment_2.point_a, line_segment_2.point_b)):
        return None
    line_2 = convert_to_line(line_segment_2)
    return compute_intersection(line_1, line_2)
