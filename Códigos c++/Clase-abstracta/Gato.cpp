#include "Gato.h"
#include <iostream>
Gato::Gato():Animal()
{}

void Gato::setSonido()
{
    sound="Miaw";
}

string Gato::getSonido(){
    return sound;
}

void Gato::come()
{
}
void Gato::muevete()
{}

void Gato::duerme()
{}

Gato::~Gato()
{
    //dtor
}
