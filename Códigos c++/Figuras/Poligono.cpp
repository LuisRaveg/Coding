#include "Poligono.h"
#include <cmath>

Poligono::Poligono(int x, int y, int numLados, float longitud, float apotema) 
    : Shape(x, y), numLados(numLados), longitud(longitud), apotema(apotema) {}

float Poligono::area() const { 
    float perimetro = numLados * longitud;
    return (0.5 * perimetro * apotema);
}

std::string Poligono::draw() const{
    return "Soy un poligono"; 
}

Poligono::~Poligono() {}
