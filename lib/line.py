from lib.point import Point


class Line:
    def __init__(self) -> None:
        self.a = 0
        self.b = 0
        self.c = 0

    def are_on_the_same_side(point_1, point_2)->bool:
        return True
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

def convert_to_line(line_segment: LineSegment) -> Line:
    line = Line()
    return line

def do_intersect(line_segment_1: LineSegment, line_segment_2: LineSegment) -> bool:
    line = convert_to_line(line_segment_1)
    if (line.are_on_the_same_side(line_segment_2.a, line_segment_2.b))
    return False
