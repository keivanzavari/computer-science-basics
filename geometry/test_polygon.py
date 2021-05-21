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
    import random
    points = []
    r = Range(0, 10)
    for i in range(num_points):
        points.append(Point(random.randint(r.lo, i), random.randint(r.lo, i)))
    return points


if __name__ == "__main__":
    points = generate_random_points(5)
    random_polygon = Polygon(points)

    arr = to_array(random_polygon)
    matplotlib_polygon = pt.Polygon(arr)

    fig, ax = plt.subplots()
    colors = 100 * np.random.rand(5)
    patches = mc.PatchCollection([matplotlib_polygon], alpha=0.4)
    patches.set_array(colors)
    ax.add_collection(patches)
    # fig.colorbar(patches, ax=ax)
    print(arr)
    plt.plot(0, 0)
    plt.show()
