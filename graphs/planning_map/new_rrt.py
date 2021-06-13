
from typing import Dict, List, Tuple, Set
import random
import math
import sys
import matplotlib.pyplot as plt

import lib.geometry as libg
import lib.point as libp


class Graph:
    def __init__(self, directed: bool = False) -> None:
        self.vertices: Dict[libp.Point, List[libp.Point]] = dict()
        self.directed = directed

    def in_graph(self, vertex: libp.Point) -> bool:
        return vertex in self.vertices

    def add_vertex(self, vertex: libp.Point) -> None:
        if not self.in_graph(vertex):
            self.vertices[vertex] = []

    def add_edge(self, from_vertex: libp.Point, to_vertex: libp.Point) -> None:
        self.add_vertex(from_vertex)
        self.add_vertex(to_vertex)
        self.vertices[from_vertex].append(to_vertex)
        if not self.directed:
            self.vertices[to_vertex].append(from_vertex)


class WorldMap:
    def __init__(self, obstacles: Set[libg.Circle], map_edges: Tuple[libp.Point, libp.Point]) -> None:
        self.obstacles = obstacles
        self.bottom_left_point = map_edges[0]
        self.top_right_point = map_edges[1]

    def get_random_config(self) -> libp.Point:
        return libp.Point(x=random.randint(self.bottom_left_point.x, self.top_right_point.x),
                          y=random.randint(self.bottom_left_point.y, self.top_right_point.y))


def get_nearest_vertex(in_vertex: libp.Point, graph: Graph) -> libp.Point:
    min_distance = sys.maxsize
    min_key = libp.Point(sys.maxsize, sys.maxsize)
    for vertex in graph.vertices.keys():
        distance = libg.get_distance(in_vertex, vertex)
        if distance < min_distance:
            min_key = vertex
            min_distance = distance
    return min_key


def go_in_direction(from_node: libp.Point, to_node: libp.Point, distance_to_go: float) -> libp.Point:
    theta = libg.get_angle(from_node, to_node)
    dx = distance_to_go * math.cos(theta)
    dy = distance_to_go * math.sin(theta)
    return from_node + libp.Point(dx, dy)


class Planner:
    def __init__(self, world_map: WorldMap) -> None:
        self.world_map = world_map

    def build_rrt(self, start: libp.Point, finish: libp.Point, incremental_distance: float = 1.0) -> Graph:
        num_vertices = 200  # abs(start.x - finish.x) * abs(start.y - finish.y) / incremental_distance
        graph = Graph(directed=True)
        graph.add_vertex(start)
        for _ in range(num_vertices):
            random_config = self.world_map.get_random_config()
            near_node = get_nearest_vertex(random_config, graph)
            if near_node.x != sys.maxsize:
                if libg.get_distance(near_node, finish) <= incremental_distance:
                    # new_node = go_in_direction(near_node, finish_node, )
                    print("finished")
                    break
                new_node = go_in_direction(near_node, random_config, incremental_distance)
                graph.add_edge(near_node, new_node)
        return graph


if __name__ == "__main__":
    min_point = libp.Point(0, 0)
    max_point = libp.Point(10, 10)
    world_map = WorldMap(obstacles={}, map_edges=(min_point, max_point))

    planner = Planner(world_map)
    graph = planner.build_rrt(start=libp.Point(0.0, 0.0), finish=libp.Point(6, 6))
    fig = plt.figure()
    for k in graph.vertices.keys():
        plt.plot(k.x, k.y, "*g", markersize=6)
        for v in graph.vertices[k]:
            plt.plot([k.x, v.x], [k.y, v.y])
    plt.grid(True)
