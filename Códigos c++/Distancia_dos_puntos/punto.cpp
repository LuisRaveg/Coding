#include "Punto.h"
#include <iostream>
#include <math.h>
#include <list>
using namespace std;

Punto::Punto()
{
    x=0;
    y=0;
}

void Punto::setX(){
    cout<<"Captura el valor de la X"<<endl;
    cin>>x;
}

double Punto::getX(){
    return x;
}

void Punto::setY(){
    cout<<"Captura el valor de la Y"<<endl;
    cin>>y;
}

double Punto::getY(){
    return y;
}

double Punto::distanciaPuntos(Punto p2){
    return sqrt(pow(p2.getX()-x,2)+pow(p2.getY()-y,2));
}

void Punto::imprime(){

}

Punto::~Punto()
{
    //dtor
}