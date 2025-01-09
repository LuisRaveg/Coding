#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape {
private:
    float r;
public:
    Circle();
    Circle(int x, int y, float r);
    void setRadio(float r);
    float getRadio();
    float area() const override;  
    void imprimeArea();
    virtual ~Circle();
    virtual string draw() const override ;
};

#endif // CIRCLE_H
