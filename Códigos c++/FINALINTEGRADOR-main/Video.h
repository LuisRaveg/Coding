#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <iostream>
using namespace std;

class Video {
protected:
    string tipoVideo;
    string nombreVideo;
    string genero;
    int calificacion;
    int anioLanzamiento;
    int duracion;

public:
    Video(string tipo, string nombre, string gen, int anio, int dur);
    Video() : calificacion(0) {}
    virtual ~Video() {}

    virtual void muestraDatos() const = 0; // Método virtual puro
    virtual void setCalificacion(int calificacion);
    virtual int getCalificacion() const;
    virtual string getGenero() const;
    virtual string getNombre() const;

    // Sobrecarga de operadores
    bool operator==(const Video& otro) const; // Comparación por nombre
    friend ostream& operator<<(ostream& os, const Video& video); // Mostrar datos
};

#endif
