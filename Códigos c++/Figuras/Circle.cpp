#include "Circle.h"
#include <iostream> 
#include <math.h>

Circle::Circle() : Shape() {
    r = 0;
}

Circle::Circle(int x, int y, float r) : Shape(x, y) {
    this->r = r;
}

void Circle::setRadio(float r) {
    this->r = r;
}

float Circle::getRadio() {
    return r;
}

float Circle::area() const { 
    return (3.1415 * pow(r, 2));
}

void Circle::imprimeArea() {
    cout << "El área es: " << area() << endl;
    cout << "Mis coordenadas x e y son: " << getX() << ", " << getY() << endl; 
}
string Circle::draw()const {
    return "Soy un circulo";
}
Circle::~Circle() {}
