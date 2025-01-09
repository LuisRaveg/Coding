#ifndef ENVIO_H
#define ENVIO_H
#include <iostream>
using namespace std;
class Envio{
    private:
    string nombre1,direccion1,nombre2,direccion2;
    double costo; 
    public:
        Envio();
        void setNombre1(string nombre1);
        void setDireccion1(string direccion1);
        void setNombre2(string nombre2);
        void setDireccion2(string direccion2);
        double calculaCosto() ;
        void setCosto(double costo);
        double getCosto();
};


#endif