#include "Video.h"
#include <iostream>
using namespace std;

Video::Video(string nombre, string gen, int anio, int dur)
    : nombreVideo(nombre), genero(gen), anioLanzamiento(anio), duracion(dur) {}
