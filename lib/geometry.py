import math
from typing import Tuple

from lib.point import Point


def cross(point1: Point, point2: Point) -> Tuple[float, float, float]:
    # homogeneous representation of a point is (x,y,1)
    cross_x = point1.y - point2.y
    cross_y = point2.x - point1.x
    cross_z = point1.x * point2.y - point1.y * point2.x
    return cross_x, cross_y, cross_z


def get_distance(point1: Point, point2: Point) -> float:
    diff = point1 - point2
    return math.sqrt(diff.x * diff.x + diff.y * diff.y)


def get_angle(point1: Point, point2: Point) -> float:
    # the line through two points is L=p cross p'
    # ax+by+c=0
    a, b, _ = cross(point1, point2)
    return math.atan2(-a, b)
