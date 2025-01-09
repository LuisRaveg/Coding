#ifndef CUADRADO_H
#define CUADRADO_H
#include "Shape.h"

class Cuadrado : public Shape {
private:
    float lado;

public:
    Cuadrado();
    Cuadrado(int x, int y, float lado);
    void setLado(float lado);
    float getLado();
    float area() const override; 
    virtual ~Cuadrado();
    virtual string draw() const override;
};

#endif // CUADRADO_H
