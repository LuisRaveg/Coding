#include "Video.h"
#include <iostream>
using namespace std;

// Constructor sin calificación
Video::Video() : calificacion(0), anioLanzamiento(0), duracion(0) {}

// Constructor sin calificación
Video::Video(string tipo, string nombre, string gen, int anio, int dur)
    : tipoVideo(tipo), nombreVideo(nombre), genero(gen), calificacion(0), anioLanzamiento(anio), duracion(dur) {}

// Constructor completo
Video::Video(string tipo, string nombre, string gen, int calif, int anio, int dur)
    : tipoVideo(tipo), nombreVideo(nombre), genero(gen), calificacion(calif), anioLanzamiento(anio), duracion(dur) {}

// Métodos set y get
void Video::setTipoVideo(const string &tipo) { tipoVideo = tipo; }
string Video::getTipoVideo() const { return tipoVideo; }

void Video::setNombreVideo(const string &nombre) { nombreVideo = nombre; }
string Video::getNombreVideo() const { return nombreVideo; }

void Video::setGenero(const string &gen) { genero = gen; }
string Video::getGenero() const { return genero; }

void Video::setCalificacion(int calif) { calificacion = calif; }
int Video::getCalificacion() const { return calificacion; }

void Video::setAnioLanzamiento(int anio) { anioLanzamiento = anio; }
int Video::getAnioLanzamiento() const { return anioLanzamiento; }

void Video::setDuracion(int dur) { duracion = dur; }
int Video::getDuracion() const { return duracion; }

// Método para calificar el video
void Video::calificaVideo(int calif) {
    calificacion = calif;
}

// Método para mostrar datos
void Video::muestraDatos() const {
    cout << "Tipo de Video: " << tipoVideo << endl;
    cout << "Nombre del Video: " << nombreVideo << endl;
    cout << "Género: " << genero << endl;
    cout << "Calificación: " << calificacion << endl;
    cout << "Año de Lanzamiento: " << anioLanzamiento << endl;
    cout << "Duración: " << duracion << " minutos" << endl;
}
