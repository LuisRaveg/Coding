#ifndef SOBRE_H
#define SOBRE_H
#include "Envio.h"
#include <iostream>
using namespace std;
class Sobre: public Envio{
    private:
        int cargo;
        double largo,ancho;
    public:
        Sobre();
        double calculaCosto() ;
        void setdimensiones(double largo,double ancho);
        double getlargo();
        double getancho();
};
#endif