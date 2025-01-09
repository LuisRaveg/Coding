#include "Pelicula.h"
#include <iostream>
using namespace std;

Pelicula::Pelicula(string nombre, string gen, int anio, int dur, string dir)
    : Video("Pelicula", nombre, gen, anio, dur), director(dir) {}

void Pelicula::muestraDatos() const {
    Video::muestraDatos(); 
    cout << "Director: " << director << endl;
}
