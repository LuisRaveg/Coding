#include <iostream>
#ifndef PUNTO_H
#define PUNTO_H

//Clase Punto
class Punto
{
    //Atributos son las caracteristicas escenciales del objeto
    private:
        double x;
        double y;

    //Métodos, son las acciones del objeto
    public:
        Punto(); //Contructor, inicializar los valores de los atributos

        //Métodos accesores y modificadores
        void setX();
        double getX();
        void setY();
        double getY();

        //Metodos especializados
        double distanciaPuntos(Punto p2);
        void imprime();

        virtual ~Punto();//Destructor

};

#endif // PUNTO_H