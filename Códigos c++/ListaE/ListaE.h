#ifndef LISTAE_H
#define LISTAE_H

#include "Nodo.h"


class Lista
{
   private:
   Nodo *cab;
public:
   Lista();
   void insertaInicio(int d);
   void insertaFinal(int d);
   void Recorre();
   void eliminaNodo(int d);
   void insertaOrdenado(int d);
   ~Lista();
};



#endif // LISTAE_H