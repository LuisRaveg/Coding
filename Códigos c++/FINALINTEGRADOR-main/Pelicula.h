#ifndef PELICULA_H
#define PELICULA_H

#include "Video.h"

class Pelicula : public Video {
private:
    string director;

public:
    Pelicula(string nombre, string gen, int anio, int dur, string dir);
    Pelicula() {}
    void muestraDatos() const override;
};

#endif
