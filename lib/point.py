import lib.math_utils as m


class Point:
    def __init__(self, x: float = 0.0, y: float = 0.0):
        self.x = x
        self.y = y

    def __lt__(self, other: "Point") -> bool:
        if m.are_almost_equal(self.y, other.y):
            return self.x < other.x
        return self.y < other.y

    def __eq__(self, other: "Point") -> bool:
        return m.are_almost_equal(self.x, other.x) and m.are_almost_equal(self.y, other.y)

    def __str__(self) -> str:
        return f"({self.x}, {self.y})"

    def __hash__(self) -> str:
        return hash((self.x, self.y))

    def __repr__(self) -> str:
        return self.__str__()

    def __add__(self, other: "Point"):
        return Point(self.x + other.x, self.y + other.y)

    def __sub__(self, other: "Point"):
        return Point(self.x - other.x, self.y - other.y)
