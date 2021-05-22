import numpy as np
import lib.geometry
import lib.point


def test_cross() -> None:
    p1 = lib.point.Point(2, 2)
    p2 = lib.point.Point(1, 2)
    res = lib.geometry.cross(p1, p2)
    print(f"cross: {res}")
    assert (res == (0, -1, 2))

    p1 = lib.point.Point(5, 2)
    p2 = lib.point.Point(1, 2)
    res = lib.geometry.cross(p1, p2)
    print(f"cross: {res}")
    assert (res == (0, -4, 8))

    p1 = lib.point.Point(2, 5)
    p2 = lib.point.Point(2, 1)
    res = lib.geometry.cross(p1, p2)
    print(f"cross: {res}")
    assert (res == (4, 0, -8))

    p1 = lib.point.Point(0, 5)
    p2 = lib.point.Point(0, 1)
    res = lib.geometry.cross(p1, p2)
    print(f"cross: {res}")
    assert (res == (4, 0, 0))


def test_cross3() -> None:
    p1 = [1, 2, 3]
    p2 = [1, 2, 3]
    res = lib.geometry.cross3(p1, p2)
    print(f"cross3: {res}")
    print(f"numpy cross: {np.cross(p1,p2)}")
    assert (res == (0, 0, 0))

    p1 = [1, -1, 0]
    p2 = [-1, 1, 0]
    res = lib.geometry.cross3(p1, p2)
    print(f"cross3: {res}")
    print(f"numpy cross: {np.cross(p1,p2)}")
    assert (res == (0, 0, 0))

    p1 = [1, -1, 2]
    p2 = [-1, 1, 2]
    res = lib.geometry.cross3(p1, p2)
    print(f"cross3: {res}")
    res_np = np.cross(p1, p2)
    print(f"numpy cross: {res_np}")
    assert (list(res) == list(res_np))

    p1 = [1, -1, 0]
    p2 = [-1, 0, 1]
    res = lib.geometry.cross3(p1, p2)
    print(f"cross3: {res}")
    res_np = np.cross(p1, p2)
    print(f"numpy cross: {res_np}")
    assert (list(res) == list(res_np))


if __name__ == "__main__":
    test_cross()
