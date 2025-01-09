#ifndef SERIE_H
#define SERIE_H

#include "Video.h"

class Serie : public Video {
private:
    int numEpisodios;
    int temporadas;

public:
    Serie(string nombre, string gen, int anio, int dur, int epis, int temps);
    Serie() : numEpisodios(0), temporadas(0) {}
    void muestraDatos() const override;
};

#endif
