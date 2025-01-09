#include "Paquete.h"
#include <iostream>
Paquete::Paquete(int largo,int ancho,int profundidad,int pesokg,double costokg){
    this-> largo =largo;
    this -> ancho= ancho;
    this -> profundidad=profundidad;
    if(pesokg>0 && costokg  >0){
        this->pesokg =pesokg;
        this->costokg=costokg;
    }
}
double Paquete:: calculaCosto(){
    return getCosto() + (costokg*pesokg);
}