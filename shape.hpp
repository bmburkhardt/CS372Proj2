#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED

#include <string>
#include <cmath>
#include <vector>
#include <memory>
using std::unique_ptr;
using std::make_unique;

class Shape {

public:
	virtual ~Shape() = default;
	virtual std::string generatePostScript() = 0;

	double height;
	double width;
	double x;
	double y;
};

class Circle : public Shape {
public:
	Circle(double radius);
	std::string generatePostScript() override;
};

class Polygon : public Shape {
public:
	Polygon() = default;
	Polygon(int numSides, double sideLength);
	std::string generatePostScript() override;

private:
	double sideLength_g;
	double numSides_g;
};

class Rectangle : public Shape {
public:
	Rectangle(double w, double h);
	std::string generatePostScript() override;

private:
	double halfHeight_;
	double halfWidth_;
};

class Spacer : public Shape {
public:
	Spacer(double w, double h);
	std::string generatePostScript() override;
};

class Square : public Polygon {
public:
	Square(double sideLength);
};

class Triangle : public Polygon {
public:
	Triangle(double sideLength);
};

class Custom : public Shape
{
public:
	Custom(double sideLength);
	std::string generatePostScript();
};

// class ComplexShape : public Shape
// {
// public:
// 	~ComplexShape() = default;
// 	ComplexShape() = default;
// 	ComplexShape(std::vector<unique_ptr<Shape>> shapeVec);
// 	string generatePostScript() const override;
// private:

// };

class Layered : public Shape
{
public:
	Layered(std::vector<unique_ptr<Shape>> shapeListGiven);
	std::string generatePostScript();

private:
	std::vector<unique_ptr<Shape>> shapeList;
};

class Scaled : public Shape
{
public:
	Scaled(Shape &shape, double fx, double fy);
	std::string generatePostScript() override;

private:
	std::string ScaleString;
};

class Rotated : public Shape {
public:
	Rotated(Shape &shape, int rotationAngle);
	std::string generatePostScript() override;

private:
	Shape &refShape;
	int rotAngle;
};

class Vertical : public Shape {
public:
	Vertical(std::vector<unique_ptr<Shape>> vertVec);
	std::string generatePostScript() override;
private:
	std::vector<unique_ptr<Shape>> vertStack;
};

class Horizontal : public Shape {
public:
	Horizontal(std::vector<unique_ptr<Shape>> horizontalVec);
	std::string generatePostScript() override;

private:
	std::vector<unique_ptr<Shape>> horizontalStack;
};

#endif // SHAPE_HPP_INCLUDED
