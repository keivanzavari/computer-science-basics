import lib.line
import lib.point


def test_line() -> None:
    p1 = lib.point.Point(0, 0)
    p2 = lib.point.Point(1, 1)
    line_1 = lib.line.Line(p1, p2)
    print(f"line 1: {line_1}")
    assert (line_1.as_tuple() == (-1, 1, 0))

    p1 = lib.point.Point(0, 0)
    p2 = lib.point.Point(0, 1)
    line_1 = lib.line.Line(p1, p2)
    print(f"line 1: {line_1}")
    assert (line_1.as_tuple() == (-1, 0, 0))

    p1 = lib.point.Point(5, 0)
    p2 = lib.point.Point(5, 5)
    line_1 = lib.line.Line(p1, p2)
    print(f"line 1: {line_1}")
    assert (line_1.as_tuple() == (-5, 0, 25))

    p1 = lib.point.Point(0, 3)
    p2 = lib.point.Point(5, 3)
    line_1 = lib.line.Line(p1, p2)
    print(f"line 1: {line_1}")
    assert (line_1.as_tuple() == (0, 5, -15))


def test_intersection() -> None:
    p1 = lib.point.Point(0, 0)
    p2 = lib.point.Point(1, 1)
    p3 = lib.point.Point(1, 0)
    line_1 = lib.line.Line(p1, p2)
    line_2 = lib.line.Line(p2, p3)
    print(f"line 1: {line_1}")
    print(f"line 2: {line_2}")
    assert (line_1.as_tuple() == (-1, 1, 0))
    assert (line_2.as_tuple() == (1, 0, -1))
    i = lib.line.compute_intersection(line_1, line_2)
    print(f"intersection: {i}")
    assert (i == p2)

    p1 = lib.point.Point(-2, 0)
    p2 = lib.point.Point(0, 2)
    line_1 = lib.line.Line(p1, p2)
    print(f"line 1: {line_1}")

    p3 = lib.point.Point(2, 0)
    p4 = lib.point.Point(0, -2)
    line_2 = lib.line.Line(p3, p4)
    print(f"line 2: {line_2}")

    i = lib.line.compute_intersection(line_1, line_2)
    print(f"intersection: {i}")
    assert (i == None)


def test_intersection_line_segment() -> None:
    p1 = lib.point.Point(0, 0)
    p2 = lib.point.Point(1, 1)
    p3 = lib.point.Point(1, 0)
    line_1 = lib.line.LineSegment(p1, p2)
    line_2 = lib.line.LineSegment(p2, p3)
    i = lib.line.compute_intersection(line_1, line_2)
    assert (i == p2)

    p1 = lib.point.Point(-2, 0)
    p2 = lib.point.Point(2, 0)
    line_1 = lib.line.LineSegment(p1, p2)

    p3 = lib.point.Point(0, 2)
    p4 = lib.point.Point(0, -2)
    line_2 = lib.line.LineSegment(p3, p4)

    i = lib.line.compute_intersection(line_1, line_2)
    assert (i == lib.point.Point(0, 0))

    p1 = lib.point.Point(0, 0)
    p2 = lib.point.Point(10, 0)
    line_1 = lib.line.LineSegment(p1, p2)
    print(f"line 1: {line_1}")

    p3 = lib.point.Point(10, 10)
    line_2 = lib.line.LineSegment(p3, p2)
    print(f"line 2: {line_2}")

    i = lib.line.compute_intersection(line_1, line_2)
    print(f"intersection: {i}")
    assert (i == lib.point.Point(10, 0))


if __name__ == "__main__":
    test_intersection_line_segment()
