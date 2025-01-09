#ifndef SHAPE_H
#define SHAPE_H

#include <string>
using namespace std;

class Shape {
private:
    int x;
    int y;

public:
    Shape();
    Shape(int x, int y);
    
    virtual string draw() const=0;  

    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
    virtual ~Shape();

    virtual float area() const = 0; 
};

#endif // SHAPE_H

