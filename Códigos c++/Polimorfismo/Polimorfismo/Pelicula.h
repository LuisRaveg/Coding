#ifndef PELICULA_H
#define PELICULA_H

#include "Video.h"

class Pelicula : public Video {
private:
    int nominaciones;

public:
    Pelicula(string nombre, string gen, int anio, int dur, int nom);
    void muestraDatos() const override;
};

#endif
