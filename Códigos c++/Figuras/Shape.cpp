#include "Shape.h"

Shape::Shape() : x(0), y(0) {} 

Shape::Shape(int x, int y) : x(x), y(y) {}

string Shape::draw() const{
    return "Dibujando la figura";
}

void Shape::setX(int x) {
    this->x = x;
}

void Shape::setY(int y) {
    this->y = y;
}

int Shape::getX() {
    return x;
}

int Shape::getY() {
    return y;
}

Shape::~Shape() {}

float Shape::area() const {
    return 0;
}
