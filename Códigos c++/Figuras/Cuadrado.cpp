#include "Cuadrado.h"

Cuadrado::Cuadrado() : Shape() {
    lado = 0;
}

Cuadrado::Cuadrado(int x, int y, float lado) : Shape(x, y) {
    this->lado = lado;
}

void Cuadrado::setLado(float lado) {
    this->lado = lado;
}

float Cuadrado::getLado() {
    return lado;
}

float Cuadrado::area() const { 
    return lado * lado;
}
string Cuadrado::draw()const{
    return "Soy un cuadrado";
}

Cuadrado::~Cuadrado() {}
