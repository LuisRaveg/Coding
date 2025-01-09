#include <iostream>
#include <list>
#include <cstdlib> 
#include <ctime>   
#include <stdexcept>
#include <limits>
#include "Pelicula.h"
#include "Serie.h"
#include "ExcepcionCalificacion.h"

using namespace std;

void asignarCalificacionesAleatorias(list<Video*>& videos) {
    srand(static_cast<unsigned>(time(0))); // Inicializa la semilla para números aleatorios
    for (auto& video : videos) {
        int calificacion = rand() % 11; 
        video->setCalificacion(calificacion);
    }
    cout << "Calificaciones aleatorias asignadas a todos los videos.\n";
}

void mostrarTodosLosVideos(const list<Video*>& videos) {
    cout << "\nLista de todos los videos:\n";
    for (const auto& video : videos) {
        video->muestraDatos();
        cout << "----------------------------------------\n";
    }
}

void mostrarVideosPorCalificacionOGenero(const list<Video*>& videos) {
    int calificacion;
    string genero;
    cout << "Ingresa la calificación mínima que deseas filtrar (por ejemplo, 5): ";
    cin >> calificacion;
    cout << "Ingresa el género (o escribe 'todos' si no deseas filtrar por género): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, genero);

    cout << "\nVideos encontrados:\n";
    for (const auto& video : videos) {
        if ((genero == "todos" || video->getGenero() == genero) && video->getCalificacion() >= calificacion) {
            video->muestraDatos();
            cout << endl;
        }
    }
}

void mostrarSeriePorNombre(const list<Video*>& videos) {
    string nombreSerie;
    cout << "Ingresa el nombre de la serie que deseas buscar: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nombreSerie);

    cout << "\nInformación de la serie '" << nombreSerie << "':\n";
    for (const auto& video : videos) {
        Serie* serie = dynamic_cast<Serie*>(video);
        if (serie && serie->getNombre() == nombreSerie) {
            serie->muestraDatos();
            cout << endl;
            return;
        }
    }
    cout << "No se encontró ninguna serie con el nombre '" << nombreSerie << "'.\n";
}

void mostrarPeliculasPorCalificacion(const list<Video*>& videos) {
    int calificacion;
    cout << "Ingresa la calificación mínima para las películas (por ejemplo, 6): ";
    cin >> calificacion;

    cout << "\nPelículas con calificación mayor o igual a " << calificacion << ":\n";
    for (const auto& video : videos) {
        Pelicula* pelicula = dynamic_cast<Pelicula*>(video);
        if (pelicula && pelicula->getCalificacion() >= calificacion) {
            pelicula->muestraDatos();
            cout << endl;
        }
    }
}

void calificarVideo(list<Video*>& videos) {
    string titulo;
    int calificacion;
    cout << "Ingresa el título del video que deseas calificar: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, titulo);

    for (auto& video : videos) {
        if (video->getNombre() == titulo) {
            cout << "Ingresa la nueva calificación para '" << titulo << "' (entre 0 y 10): ";
            cin >> calificacion;

            try {
                if (calificacion < 0 || calificacion > 10) {
                    throw ExcepcionCalificacion("Calificación fuera de rango. Debe estar entre 0 y 10.");
                }
                video->setCalificacion(calificacion);
                cout << "Calificación actualizada correctamente.\n";
            } catch (const ExcepcionCalificacion& e) {
                cout << "Error: " << e.what() << endl;
            }
            return;
        }
    }
    cout << "No se encontró ningún video con el título '" << titulo << "'.\n";
}

void mostrarMenu(list<Video*>& videos) {
    int opcion;
    do {
        cout << "\nMenu de opciones:\n";
        cout << "1. Mostrar todos los videos\n";
        cout << "2. Mostrar videos por calificación o género\n";
        cout << "3. Buscar una serie por su nombre\n";
        cout << "4. Mostrar películas por calificación\n";
        cout << "5. Calificar un video\n";
        cout << "6. Comparar dos videos\n";
        cout << "7. Salir\n";
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarTodosLosVideos(videos);
                break;
            case 2:
                mostrarVideosPorCalificacionOGenero(videos);
                break;
            case 3:
                mostrarSeriePorNombre(videos);
                break;
            case 4:
                mostrarPeliculasPorCalificacion(videos);
                break;
            case 5:
                calificarVideo(videos);
                break;
            case 6: {
                
                if (videos.size() >= 2) {
                    auto it = videos.begin();
                    Video* video1 = *it;
                    ++it;
                    Video* video2 = *it;

                    if (*video1 == *video2) {
                        cout << "Los primeros dos videos en la lista son iguales.\n";
                    } else {
                        cout << "Los primeros dos videos en la lista son diferentes.\n";
                    }
                    cout << "\nMostrando información del primer video con el operador << :\n";
                    cout << *video1 << endl;
                } else {
                    cout << "No hay suficientes videos para comparar.\n";
                }
                break;
            }
            case 7:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción no válida. Inténtalo de nuevo.\n";
        }
    } while (opcion != 7);
}

int main() {
    list<Video*> videos;

    try {
        
        videos.push_back(new Pelicula("Inception", "Sci-Fi", 2010, 148, "Christopher Nolan"));
        videos.push_back(new Pelicula("The Matrix", "Action", 1999, 136, "The Wachowskis"));
        videos.push_back(new Serie("Breaking Bad", "Drama", 2008, 45, 62, 5));
        videos.push_back(new Serie("Stranger Things", "Sci-Fi", 2016, 50, 34, 3));
        videos.push_back(new Serie("Game of Thrones", "Fantasy", 2011, 55, 73, 8));

        
        asignarCalificacionesAleatorias(videos);

        
        mostrarMenu(videos);
    } catch (...) {
        cout << "Ocurrió un error inesperado.\n";
    }

    
    for (auto video : videos) {
        delete video;
    }

    return 0;
}
