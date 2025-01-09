#ifndef VIDEO_H
#define VIDEO_H

#include <string>
using namespace std;

class Video {
protected:
    string nombreVideo;
    string genero;
    int anioLanzamiento;
    int duracion;

public:
    Video(string nombre, string gen, int anio, int dur);
    virtual void muestraDatos() const = 0;
    virtual ~Video() = default;
};

#endif
