from typing import Union, Tuple
import random
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression, RANSACRegressor


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y


class Points:
    def __init__(self):
        self.x = []
        self.y = []

    def append(self, x, y):
        self.x.append(x)
        self.y.append(y)


class Limit:
    def __init__(self, lo, hi):
        self.lo = lo
        self.hi = hi


def create_random_points(limits: Limit, num_points: int) -> Points:
    points = Points()
    vals = np.linspace(limits.lo, limits.hi, num=num_points)
    for i in vals:
        x = i + 0.2 * limits.hi * random.random()
        y = i + 0.2 * limits.hi * random.random()
        points.append(x, y)

    vals = np.linspace(limits.lo, limits.hi, num=int(num_points / 10))
    for i in vals:
        x = i + 0.1 * limits.hi * random.random()
        y = 5 * i + 0.1 * limits.hi * random.random()
        points.append(x, y)
        y = 0.5 * i + 0.1 * limits.hi * random.random()
        points.append(x, y)

    return points


def fit_linear(points: Points):
    model = LinearRegression()
    x = np.array(points.x).reshape((-1, 1))
    y = np.array(points.y).reshape((-1, 1))
    model.fit(x, y)
    return model


def fit_ransac(points: Points):
    model = RANSACRegressor()
    x = np.array(points.x).reshape((-1, 1))
    y = np.array(points.y).reshape((-1, 1))
    model.fit(x, y)
    # print(f"model, intercept: {model.intercept_}, coef: {model.coef_}")
    return model


def create_line(model: Union[LinearRegression, RANSACRegressor], points_range: Limit) -> Points:
    vals = np.linspace(points_range.lo, points_range.hi, num=20)
    y = model.predict(vals.reshape((-1, 1)))
    points = Points()
    points.x = vals.flatten().tolist()
    points.y = y.flatten().tolist()
    return points


def cross(point1: Point, point2: Point) -> Tuple[float, float, float]:
    # homogeneous representation of a point is (x,y,1)
    cross_x = point1.y - point2.y
    cross_y = point2.x - point1.x
    cross_z = point1.x * point2.y - point1.y * point2.x
    return cross_x, cross_y, cross_z


points_range = Limit(0, 100)
num_points = 100
points = create_random_points(points_range, num_points)
model_linear = fit_linear(points)
model_ransac = fit_ransac(points)
line_points = create_line(model_linear, points_range)
line_points_ransac = create_line(model_ransac, points_range)

plt.figure()
plt.plot(points.x, points.y, "*", markersize=12, label="points")
plt.plot(line_points.x, line_points.y, "--o", markersize=6, label="linear regression")
plt.plot(line_points_ransac.x, line_points_ransac.y, "--o", markersize=6, label="ransac")
plt.legend()
plt.grid(True)
plt.show()
