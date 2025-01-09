#include "Video.h"
#include <iostream>
using namespace std;

Video::Video(string tipo, string nombre, string gen, int anio, int dur)
    : tipoVideo(tipo), nombreVideo(nombre), genero(gen), anioLanzamiento(anio), duracion(dur), calificacion(0) {}

int Video::getCalificacion() const {
    return calificacion;
}

void Video::setCalificacion(int calificacion) {
    this->calificacion = calificacion;
}

string Video::getGenero() const {
    return genero;
}

string Video::getNombre() const {
    return nombreVideo;
}

// Implementación del método virtual puro
void Video::muestraDatos() const {
    cout << "Tipo de Video: " << tipoVideo << endl;
    cout << "Nombre del Video: " << nombreVideo << endl;
    cout << "Género: " << genero << endl;
    cout << "Calificación: " << calificacion << endl;
    cout << "Año de Lanzamiento: " << anioLanzamiento << endl;
    cout << "Duración: " << duracion << " minutos" << endl;
}

// Sobrecarga de operadores
bool Video::operator==(const Video& otro) const {
    return this->nombreVideo == otro.nombreVideo;
}

ostream& operator<<(ostream& os, const Video& video) {
    os << "Video: " << video.nombreVideo << ", Género: " << video.genero
       << ", Año: " << video.anioLanzamiento << ", Calificación: " << video.calificacion;
    return os;
}
