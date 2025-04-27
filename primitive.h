#pragma once
#include <memory>
#include <string>

class Primitive {
public:
    virtual ~Primitive() = default;

    virtual void draw() const = 0;

    virtual std::string getType() const = 0;

    virtual std::unique_ptr<Primitive> clone() const = 0;
};

class Circle : public Primitive {
public:
    Circle(double x, double y, double radius)
            : x(x), y(y), radius(radius) {}

    void draw() const override {}

    std::string getType() const override {
        return "Circle";
    }

    std::unique_ptr<Primitive> clone() const override {
        return std::make_unique<Circle>(*this);
    }

private:
    double x, y, radius;
};