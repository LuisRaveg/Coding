#ifndef POLIGONO_H
#define POLIGONO_H

#include "Shape.h"

class Poligono : public Shape {
private:
    int numLados;     
    float longitud;   
    float apotema;    
public:
    Poligono(int x, int y, int numLados, float longitud, float apotema); 
    float area() const override; 
    std::string draw() const override;   
    virtual ~Poligono();
};

#endif // POLIGONO_H
