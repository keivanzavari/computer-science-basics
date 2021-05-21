from typing import List
import sys

from lib.point import Point
from lib.line import LineSegment


class Polygon:
    def __init__(self, vertices: List[Point]) -> None:
        if not isinstance(vertices, list):
            raise IOError("input vertices should be a list")
        self.vertices = vertices
        self.max_point = Point(-sys.maxsize, -sys.maxsize)
        self.min_point = Point(sys.maxsize, sys.maxsize)
        self.assign_limits()

    def assign_limits(self) -> None:
        for vertex in self.vertices:
            if vertex.x < self.min_point.x:
                self.min_point.x = vertex.x
            if vertex.x > self.max_point.x:
                self.max_point.x = vertex.x

            if vertex.y < self.min_point.y:
                self.min_point.y = vertex.y

            if vertex.y > self.max_point.y:
                self.max_point.y = vertex.y

    def contains(self, point: Point) -> bool:
        if self.is_outside_limits(point):
            return False

        edges = self.getEdges()
        count_intersections = 0
        for edge in edges:
            if edge.intersects_with_horizontal_line(point.y):
                count_intersections += 1

        if (count_intersections % 2 == 0):
            return False

        return True

    def is_outside_limits(self, point: Point) -> bool:
        return point.x > self.max_point.x or \
               point.x < self.min_point.x or \
               point.y < self.min_point.y or \
               point.y > self.max_point.y

    def getEdges(self) -> List[LineSegment]:
        edges: List[LineSegment] = []

        for idx in range(len(self.vertices) - 1):
            edges.append(LineSegment(self.vertices[idx], self.vertices[idx + 1]))

        edges.append(LineSegment(self.vertices[-1], self.vertices[0]))

        return edges
