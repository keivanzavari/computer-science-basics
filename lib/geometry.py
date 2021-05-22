import math
from typing import Tuple

from lib.point import Point


def cross(point_1: Point, point_2: Point) -> Tuple[float, float, float]:
    # homogeneous representation of a point is (x,y,1)
    cross_x = point_1.y - point_2.y
    cross_y = point_2.x - point_1.x
    cross_z = point_1.x * point_2.y - point_1.y * point_2.x
    return cross_x, cross_y, cross_z


def get_distance(point_1: Point, point_2: Point) -> float:
    diff = point_1 - point_2
    return math.sqrt(diff.x * diff.x + diff.y * diff.y)


def get_angle(point_1: Point, point_2: Point) -> float:
    # the line through two points is L=p cross p'
    # ax+by+c=0
    a, b, _ = cross(point_1, point_2)
    return math.atan2(-a, b)
