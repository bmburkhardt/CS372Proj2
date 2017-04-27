#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED

#include <string>
#include <cmath>
#include <vector>
#include <memory>

// Base Class - Shape
class Shape {
public:
	virtual ~Shape() = default;
	virtual std::string generatePostScript() = 0;

	double height;
	double width;
	double x;
	double y;
};

// Circle
class Circle : public Shape {
public:
	Circle(double radius);
	std::string generatePostScript() override;
};

// Polygon
class Polygon : public Shape {
public:
	Polygon() = default;
	Polygon(int numSides, double sideLength);
	std::string generatePostScript() override;

private:
	double sideLength_g;
	double numSides_g;
};

// Rectangle
class Rectangle : public Shape {
public:
	Rectangle(double w, double h);
	std::string generatePostScript() override;

private:
	double halfHeight_;
	double halfWidth_;
};

// Spacer
class Spacer : public Shape {
public:
	Spacer(double w, double h);
	std::string generatePostScript() override;
};

// Square
class Square : public Polygon {
public:
	Square(double sideLength);
};

// Triangle
class Triangle : public Polygon {
public:
	Triangle(double sideLength);
};

// Custom
class Custom : public Shape
{
public:
	Custom(double sideLength);
	std::string generatePostScript();
};

// Scaled
class Scaled : public Shape
{
public:
	Scaled(Shape &shape, double fx, double fy);
	std::string generatePostScript() override;

private:
	std::string ScaleString;
};

// Rotated
class Rotated : public Shape {
public:
	Rotated(Shape &shape, int rotationAngle);
	std::string generatePostScript() override;

private:
	Shape &refShape;
	int rotAngle;
};

// Base class CompoundShape which inherits from Shape 
//		Used for Vertical, Horizontal, and Layered
class CompoundShape : public Shape
{
public:
	~CompoundShape() = default;
	CompoundShape() = default;
	CompoundShape(std::vector<std::shared_ptr<Shape>> shapeVec);
	std::string generatePostScript() override;

protected:
	virtual std::string forward_Translator(std::shared_ptr<Shape> shape) const;
	virtual std::string reverse_Translator(std::shared_ptr<Shape> shape) const;
	std::vector<std::shared_ptr<Shape>> shapeVec_;
};

// Layered
class Layered : public CompoundShape
{
public:
	Layered(std::vector<std::shared_ptr<Shape>> shapeVec);
};

// Vertical
class Vertical : public CompoundShape {
public:
	Vertical(std::vector<std::shared_ptr<Shape>> shapeVec);

protected:
	std::string forward_Translator(std::shared_ptr<Shape> shape) const override;
	std::string reverse_Translator(std::shared_ptr<Shape> shape) const override;
};

// Horizontal
class Horizontal : public CompoundShape {
public:
	Horizontal(std::vector<std::shared_ptr<Shape>> shapeVec);

protected:
	std::string forward_Translator(std::shared_ptr<Shape> shape) const override;
	std::string reverse_Translator(std::shared_ptr<Shape> shape) const override;
};

#endif // SHAPE_HPP_INCLUDED
