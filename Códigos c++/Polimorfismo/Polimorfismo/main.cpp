#include <iostream>
#include <vector>
#include "Pelicula.h"
#include "Serie.h"
using namespace std;

int main() {
    vector<Video*> videos;
    videos.push_back(new Pelicula("Inception", "Ciencia Ficción", 2010, 148, 4));
    videos.push_back(new Pelicula("The Godfather", "Drama", 1972, 175, 11));
    videos.push_back(new Pelicula("Pulp Fiction", "Crimen", 1994, 154, 7));
    videos.push_back(new Serie("Breaking Bad", "Drama", 2008, 47, 62));
    videos.push_back(new Serie("Stranger Things", "Ciencia Ficción", 2016, 50, 34));

    for (const auto& video : videos) {
        video->muestraDatos();
        cout << "----------------------------" << endl;
    }

    for (auto& video : videos) {
        delete video;
    }

    return 0;
}
