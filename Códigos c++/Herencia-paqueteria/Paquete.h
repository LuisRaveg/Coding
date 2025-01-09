#ifndef PAQUETE_H
#define PAQUETE_H
#include "Envio.h"
#include <iostream>
using namespace std;
class Paquete:public Envio{
    private:
        int largo,ancho, profundidad,pesokg;
        double costokg;
    public:
    Paquete(int largo,int ancho,int profundidad,int pesokg,double costokg);
    double calculaCosto();
};
#endif