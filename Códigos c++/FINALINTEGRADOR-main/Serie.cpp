#include "Serie.h"
#include <iostream>
using namespace std;

Serie::Serie(string nombre, string gen, int anio, int dur, int epis, int temps)
    : Video("Serie", nombre, gen, anio, dur), numEpisodios(epis), temporadas(temps) {}

void Serie::muestraDatos() const {
    Video::muestraDatos(); 
    cout << "Número de Episodios: " << numEpisodios << endl;
    cout << "Temporadas: " << temporadas << endl;
}
