#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Shape {
  Shape(const std::string &given_name) : name(given_name) { std::cout << "Shape construct " << name << std::endl; }
  virtual ~Shape() { std::cout << "Destructor of Shape\n"; };
  Shape(const Shape &w) : name(w.name) { std::cout << "copy construct shape " << name << std::endl; }
  Shape(Shape &&w) : name(w.name) { std::cout << "move construct " << name << std::endl; }

  std::string getName() const { return name; }
  std::string name = "Shape";
};

struct Circle : public Shape {
  Circle() : Shape("Circle") {
    std::cout << "Empty Circle construct " << name << std::endl;
    radius = 2;
  }
  Circle(double radius_) : Shape("Circle"), radius(radius_) { std::cout << "Circle construct " << name << std::endl; }
  Circle(const std::string &given_name) : Shape(given_name) {}
  Circle(const Circle &w) : Shape("Circle") {
    std::cout << "copy construct circle " << name << std::endl;
    radius = w.radius;
  }
  ~Circle() { std::cout << "Destructor of Circle\n"; };
  double getRadius() const { return radius; }
  double x;
  double y;
  double radius;
};

struct Rectangle : public Shape {
  Rectangle() : Shape("Rectangle") {
    std::cout << "Rectangle construct " << name << std::endl;
    w = 2.4;
  }
  double getWidth() const { return w; }
  double w;
  double h;
};

void areColliding(const Shape *shape1, const Shape *shape2) {
  std::cout << "[Pointer] Are " << shape1->getName() << " and " << shape2->getName() << " colliding?\n";
  const auto obj = dynamic_cast<const Circle *>(shape1);

  std::cout << "[Pointer] radius: " << obj->getRadius() << "\n";
}

void areColliding(const Shape &shape1, const Shape &shape2) {
  std::cout << "[Reference] Are " << shape1.getName() << " and " << shape2.getName() << " colliding?\n";
  // This will cause an extra copy construct and upon going out of scope, will delete the object.
  const auto obj1 = dynamic_cast<const Circle &>(shape1);
  std::cout << "[Reference] radius: " << obj1.getRadius() << "\n";

  // This however will only create a pointer to the already existing object. So no more copies are made here.
  const auto obj2 = dynamic_cast<const Circle *>(&shape1);
  std::cout << "[Reference] radius: " << obj2->getRadius() << "\n";
}

void areColliding(const std::vector<Shape> &shape) {
  std::cout << "[Vector] Are " << shape[0].getName() << " and " << shape[1].getName() << " colliding?\n";
  // const auto obj = dynamic_cast<const Circle *>(shape1);
  // std::cout << "[Pointer] radius: " << obj->getRadius() << "\n";
}

int main() {
  int i = 0;
  {
    std::cout << ++i << "\n------------\n";
    // One gets called
    std::unique_ptr<Shape> shape(new Circle);
    // if destructor of the base class is virtual, it will make sure that the child class also gets called.
  }
  {
    std::cout << ++i << "\n------------\n";
    // Both get called
    Circle shape;
  }
  {
    std::cout << ++i << "\n------------\n";
    std::unique_ptr<Shape> shape1(new Circle(3.4));
    std::unique_ptr<Shape> shape2(new Rectangle);
    std::cout << "------------\n";
    areColliding(shape1.get(), shape2.get());
    std::cout << "------------\n";
    areColliding(*shape1, *shape2);
    std::cout << "------------\n";
  }
  {
    std::cout << ++i << "\n------------\n";
    std::unique_ptr<Shape> shape1(new Circle(3.4));
    std::cout << "------------\n";
    {
      // copy contructor of shape is called twice here.
      std::cout << "------- Make a vector from object.\n";
      std::vector<Shape> vec{*shape1};
      std::cout << "------------\n";
    }
    {
      // No copy constructor is called here.
      std::cout << "----- Make a vector from pointers to object.\n";
      std::vector<Shape *> vec{shape1.get()};
      std::cout << "------------\n";
    }
  }
}
