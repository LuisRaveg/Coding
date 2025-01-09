#ifndef SERIE_H
#define SERIE_H

#include "Video.h"

class Serie : public Video {
private:
    int cantEpisodios;

public:
    Serie(string nombre, string gen, int anio, int dur, int cantEp);
    void muestraDatos() const override;
};

#endif
