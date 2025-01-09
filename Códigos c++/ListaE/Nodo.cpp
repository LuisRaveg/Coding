#include "Nodo.h"
#include <iostream>

Nodo::Nodo()
{
    num=0;
   sig=NULL;
}

void Nodo::setDato(int num)
{
   this->num=num;
}

int Nodo::getDato(){
    return num;
}

void Nodo::setSiguiente(Nodo *s)
{
  sig=s;
}

Nodo * Nodo::getSiguiente()
{
   return sig;
}

Nodo::~Nodo()
{
    //dtor
}