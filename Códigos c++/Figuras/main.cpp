#include <iostream>
#include "Shape.h"
#include "Circle.h"
#include "Cuadrado.h"
#include "Triangulo.h"
#include "Poligono.h"
#include <list>                
using namespace std;

int main()
{
    list<Shape*> Shapes;
    list<Shape*>::iterator aux;
    Shapes.push_back(new Circle(4, 7, 3));
    Shapes.push_back(new Cuadrado(5, 6, 4));
    Shapes.push_back(new Triangulo(7, 8, 3, 4));
    Shapes.push_back(new Poligono(10, 10, 6, 4.0, 3.464));


    aux =Shapes.begin();
    while(aux!=Shapes.end()){
        cout<<"Figura"<<(*aux)->draw() <<endl;
        cout<<"Area"<<(*aux)->area()<<endl;
        aux++;
    }

    
   
    return 0;
}
