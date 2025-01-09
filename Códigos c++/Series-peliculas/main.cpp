#include <iostream>
#include "Video.h"
using namespace std;

// Función para mostrar el menú y manejar opciones del usuario
void mostrarMenu(Video &video1, Video &video2) {
    int opcion;
    do {
        cout << "\nMenu de opciones:" << endl;
        cout << "1. Ver detalles de los videos" << endl;
        cout << "2. Calificar un video" << endl;
        cout << "3. Salir" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "\nDetalles del Video 1:" << endl;
                video1.muestraDatos();
                cout << "\nDetalles del Video 2:" << endl;
                video2.muestraDatos();
                break;
            case 2:
                int calificacion, videoSeleccionado;
                cout << "Selecciona el video a calificar (1 o 2): ";
                cin >> videoSeleccionado;
                cout << "Ingresa la calificación: ";
                cin >> calificacion;

                if (videoSeleccionado == 1) {
                    video1.calificaVideo(calificacion);
                } else if (videoSeleccionado == 2) {
                    video2.calificaVideo(calificacion);
                } else {
                    cout << "Video no válido." << endl;
                }
                break;
            case 3:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida. Intenta de nuevo." << endl;
        }
    } while(opcion != 3);
}

int main() {
    // Crear dos objetos de la clase Video
    Video video1("Documental", "Naturaleza", "Educativo", 2022, 90);
    Video video2("Película", "Aventura Espacial", "Ciencia Ficción", 5, 2023, 120);

    // Llamar a la función de menú
    mostrarMenu(video1, video2);

    return 0;
}
