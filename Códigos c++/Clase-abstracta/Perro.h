#include <iostream>

#ifndef PERRO_H
#include "Animal.h"
#define PERRO_H
class Perro:Animal
{
    public:
        Perro();
        void setSonido() override;
        string getSonido() override;
        void come() override;
        void muevete()override;
        void duerme()override;
        virtual ~Perro();
};
#endif