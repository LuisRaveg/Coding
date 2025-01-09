#include "Envio.h"
#include <iostream>
using namespace std;
Envio::Envio(){
    costo=0;
}
void Envio::setCosto(double costo){
    this -> costo =costo;
}
double Envio::getCosto(){
    return costo;
}
double Envio::calculaCosto(){
    return costo;
}
void Envio::setNombre1(string nombre1){
    this->nombre1 =nombre1;
}
void Envio::setDireccion1(string direccion1){
    this-> direccion1 =direccion1;
}
void Envio::setNombre2(string nombre2){
    this->nombre2 =nombre2;
}
void Envio::setDireccion2(string direccion2){
    this-> direccion2 =direccion2;
}