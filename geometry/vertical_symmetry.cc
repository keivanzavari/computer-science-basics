

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

// Input a set of 2D points in the x-y plane as input.
// Finds a vertical line of symmetry through the points, if ones exists.
//
//       *   |    *
//      *    |     *
//  x = 11.

struct Point2d {
  double x;
  double y;
};

double distance(double x, std::vector<Point2d>& points) {
  double distance = 0;
  for (const auto& point : points) {
    distance += x - point.x;
  }

  return distance;
}

double findVerticalSymmetry(std::vector<Point2d> points) {
  std::sort(points.begin(), points.end(), [](const Point2d& a, const Point2d& b) { return a.x < b.x; });

  // min point & max point
  Point2d min_point = points.front();
  Point2d max_point = points.back();

  double middle_point = (min_point.x + max_point.x) / 2;

  auto position = std::upper_bound(points.begin(), points.end(), middle_point,
                                   [](double value, const Point2d& point) { return point.x > value; });
  std::vector<Point2d> left_side(points.begin(), position);
  std::vector<Point2d> right_side(position, points.end());

  if (left_side.empty() || right_side.empty()) {
    throw "doesn't exist.";
  }

  double d_left = distance(middle_point, left_side);
  double d_right = distance(middle_point, right_side);
  if (std::abs(d_left + d_right) < 1e-3) return middle_point;

  std::cout << "d_left: " << d_left << std::endl;
  std::cout << "d_right: " << d_right << std::endl;

  return 0;
}

int main() {
  std::vector<Point2d> points{{5, 0}, {7, 0}, {7, 2}, {5, 2}};

  auto x_value = findVerticalSymmetry(points);
  std::cout << "x_value: " << x_value << std::endl;

  return 0;
}
