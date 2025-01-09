#include <iostream>
#include "Perro.h"

Perro::Perro():Animal()
{
    //ctor
}

void Perro::setSonido()
{
    sound="Guaw";
}

string Perro::getSonido(){
    return sound;
}
Perro::~Perro()
{
    //dtor
}
void Perro::come()
{
}

void Perro::muevete()
{
}

void Perro::duerme()
{
}