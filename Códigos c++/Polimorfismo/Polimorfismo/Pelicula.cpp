#include "Pelicula.h"
#include <iostream>
using namespace std;

Pelicula::Pelicula(string nombre, string gen, int anio, int dur, int nom)
    : Video(nombre, gen, anio, dur), nominaciones(nom) {}

void Pelicula::muestraDatos() const {
    cout << "Película: " << nombreVideo << endl;
    cout << "Género: " << genero << endl;
    cout << "Año de Lanzamiento: " << anioLanzamiento << endl;
    cout << "Duración: " << duracion << " minutos" << endl;
    cout << "Nominaciones: " << nominaciones << endl;
}
