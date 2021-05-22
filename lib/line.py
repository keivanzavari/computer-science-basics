from lib.point import Point


class LineSegment:
    def __init__(self, point1: Point, point2: Point):
        self.a = point1
        self.b = point2

    def intersects_with_horizontal_line(self, y: float) -> bool:
        if (self.a.y > y and self.b.y > y):
            return False
        if (self.a.y < y and self.b.y < y):
            return False
        return True


def do_intersect(line1: LineSegment, line2: LineSegment) -> bool:
    return False
