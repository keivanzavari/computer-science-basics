from typing import List, Type
import sys

from lib.point import Point
import lib.line
import lib.geometry
import lib.math_utils


class Polygon:
    def __init__(self, vertices: List[Point]) -> None:
        if not isinstance(vertices, list):
            raise TypeError("input vertices should be a list")
        if len(vertices) <= 2:
            raise IOError("Polygon should at least have 3 vertices.")

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

        edges = self.get_edges()
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

    def get_edges(self) -> List[lib.line.LineSegment]:
        edges: List[lib.line.LineSegment] = []

        for idx in range(len(self.vertices) - 1):
            edges.append(lib.line.LineSegment(self.vertices[idx], self.vertices[idx + 1]))

        edges.append(lib.line.LineSegment(self.vertices[-1], self.vertices[0]))

        return edges

    def is_self_intersecting(self) -> bool:
        # The edges should only intersect at vertices
        edges = self.get_edges()
        for idx in range(len(self.vertices)):
            # edge 0 is between vertex 0 and vertex 1
            # edge 1 is between vertex 1 and vertex 2
            # edge 0 and edge 1 should only intersect at vertex 1
            idx1 = (idx + 1) % len(self.vertices)
            intersection = lib.line.compute_intersection(edges[idx], edges[idx1])
            if intersection is not None:
                if intersection != self.vertices[idx1]:
                    return False
        return True

    def _get_direction_from_three(self, point1: Point, point2: Point, point3: Point) -> int:
        vec1 = point2 - point1
        vec2 = point3 - point2
        _, _, res = lib.geometry.cross(vec1, vec2)
        direction = 0
        if lib.math_utils.are_almost_equal(res, 0):
            direction = 0
        elif res > 0:
            direction = 1
        elif res < 0:
            direction = -1
        return direction

    def is_convex(self) -> bool:
        # go through the vertices
        # find out if going from one vertex to another requires left or right turn.
        # If they are all the same, it is convex.
        # The number of angles is the same as the number of vertices.
        if len(self.vertices) == 3:
            return True

        init_direction = self._get_direction_from_three(self.vertices[0], self.vertices[1], self.vertices[2])
        print(f"initial direction {init_direction}")
        for idx in range(1, len(self.vertices) + 2):
            idx1 = (idx + 1) % len(self.vertices)
            idx2 = (idx + 2) % len(self.vertices)
            curr_direction = self._get_direction_from_three(self.vertices[idx], self.vertices[idx1],
                                                            self.vertices[idx2])
            print(f"curr_direction {curr_direction}")
            if curr_direction != init_direction:
                return False

        return True
