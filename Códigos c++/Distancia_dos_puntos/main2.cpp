#include <iostream>
#include "Punto.h"
#include <list>
using namespace std;

int main()
{
    Punto p1,p2;//Crear objetos e instancia
    /*

    p1.setX();
    p1.setY();

    p2.setX();//mensaje POO
    p2.setY();

    /*double d;

    d=p1.distanciaPuntos(p2);
    cout<<"La distancia de los puntos es: "<<d;
    p1.distanciaPuntos(p2.getX(),p2.getY());
   cout<<"La distancia de los puntos es: "<<p1.distanciaPuntos(p2);
    */
   list<Punto*>puntos;
    list<Punto*>::iterator aux;
    Punto *nuevo;
    char opc;

    do{
        //puntos.push_back(new punto(4,3));
        nuevo=new Punto();
        nuevo->setX();
        nuevo->setY();
        puntos.push_back(nuevo);
        cout<<"Capturar otra coordenada? s/n";
        cin>>opc;
    }while(opc!='n');

    aux=puntos.begin();
    while(aux!=puntos.end()){
        cout<<"x:"<<(*aux)->getX()<<" y:"<<(*aux)->getY()<<endl;
        aux++;
    }

    return 0;
}