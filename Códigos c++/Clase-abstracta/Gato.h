#ifndef GATO_H
#define GATO_H
#include <iostream>
using namespace std;
#include "Animal.h"
class Gato:Animal
{
    public:
        Gato();
         void setSonido()override;
         string getSonido () override;
         void come() override;
         void muevete() override;
         void duerme()override;
         ~Gato();
    protected:

    private:
};
#endif