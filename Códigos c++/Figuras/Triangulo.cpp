#include "Triangulo.h"

Triangulo::Triangulo() : Shape() {
    base = 0;
    altura = 0;
}

Triangulo::Triangulo(int x, int y, float base, float altura) : Shape(x, y) {
    this->base = base;
    this->altura = altura;
}

void Triangulo::setBase(float base) {
    this->base = base;
}

void Triangulo::setAltura(float altura) {
    this->altura = altura;
}

float Triangulo::getBase() {
    return base;
}

float Triangulo::getAltura() {
    return altura;
}

float Triangulo::area() const {  
    return (base * altura) / 2;
}
string Triangulo::draw() const {
    return "Soy un triangulo";
}

Triangulo::~Triangulo() {}
