#include "Serie.h"
#include <iostream>
using namespace std;

Serie::Serie(string nombre, string gen, int anio, int dur, int cantEp)
    : Video(nombre, gen, anio, dur), cantEpisodios(cantEp) {}

void Serie::muestraDatos() const {
    cout << "Serie: " << nombreVideo << endl;
    cout << "Género: " << genero << endl;
    cout << "Año de Lanzamiento: " << anioLanzamiento << endl;
    cout << "Duración: " << duracion << " minutos por episodio" << endl;
    cout << "Cantidad de Episodios: " << cantEpisodios << endl;
}
