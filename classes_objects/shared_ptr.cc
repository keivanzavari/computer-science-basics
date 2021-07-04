#include <iostream>
#include <memory>

struct Point {
  double x;
  double y;

  Point(double x_, double y_) : x(x_), y(y_) {}
};

std::shared_ptr<Point> create_object(double x, double y) {
  auto point_ptr = std::make_shared<Point>(x, y);
  std::cout << "count inside function: " << point_ptr.use_count() << "\n";

  return point_ptr;
}

int main() {
  auto point_ptr = create_object(2, 3);

  std::cout << "count after function: " << point_ptr.use_count() << "\n";
  std::cout << "x, y: [" << point_ptr->x << ", " << point_ptr->y << "]\n";

  return 0;
}
