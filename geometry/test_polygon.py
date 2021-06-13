import random
from typing import List
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as pt
import matplotlib.collections as mc

import sys
import pathlib
PARENT = pathlib.Path(__file__).parent.absolute().parent
sys.path.insert(0, PARENT.as_posix())

from lib.polygon import Polygon
from lib.point import Point
from lib.limits import Range


def to_array(p: Polygon) -> np.ndarray:
    array = np.ndarray((len(p.vertices), 2))
    for idx, vertex in enumerate(p.vertices):
        array[idx][0] = vertex.x
        array[idx][1] = vertex.y
    return array


def generate_random_points(num_points: int) -> List[Point]:
    points = []
    r = Range(0, 10)
    for i in range(num_points):
        points.append(Point(random.randint(r.lo, i), random.randint(r.lo, i)))
    return points


def generate_polygon(num_vertices: int, convex: bool = True) -> List[Point]:
    r = Range(0, 10)
    if num_vertices == 3:
        return [Point(r.lo, r.lo), Point(r.hi, r.lo), Point(r.lo, r.hi)]
    if num_vertices == 4:
        if convex:
            return [Point(r.lo, r.lo), Point(r.hi, r.lo), Point(r.hi, r.hi), Point(r.lo, r.hi)]
        else:
            return [Point(r.lo, r.lo), Point(r.hi, r.lo), Point(r.lo, r.hi), Point(r.hi, r.hi)]

    if num_vertices == 5:
        if convex:
            return [
                Point(r.hi * 0.3, r.hi * 0.15),
                Point(r.hi, r.hi * 0.4),
                Point(r.hi, r.hi * 0.8),
                Point(r.hi * 0.5, r.hi),
                Point(r.hi * 0.05, r.hi * 0.5)
            ]
        else:
            return [
                Point(r.hi, r.hi * 0.4),
                Point(r.hi * 0.5, r.hi),
                Point(r.hi * 0.3, r.hi * 0.15),
                Point(r.hi, r.hi * 0.8),
                Point(r.hi * 0.05, r.hi * 0.5)
            ]

    return []


if __name__ == "__main__":
    points = generate_polygon(5, False)
    random_polygon = Polygon(points)
    is_convex = random_polygon.is_convex()
    print(f"Is polygon convex: {is_convex}")

    arr = to_array(random_polygon)
    matplotlib_polygon = pt.Polygon(arr)
    matplotlib_polygon.set_edgecolor([0.5, 0, 0])

    fig, ax = plt.subplots()
    colors = 100 * np.array([0.0])
    patches = mc.PatchCollection([matplotlib_polygon], alpha=0.4)
    patches.set_array(colors)
    ax.add_collection(patches)
    plt.plot(arr[:, 0], arr[:, 1], "*", markersize=10)
    plt.grid(True)
    plt.show()
