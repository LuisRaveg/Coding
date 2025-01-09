#ifndef VIDEO_H
#define VIDEO_H

#include <string>
using namespace std;

class Video {
private:
    // Atributos privados
    string tipoVideo;
    string nombreVideo;
    string genero;
    int calificacion;
    int anioLanzamiento;
    int duracion;

public:
    // Constructores
    Video();  // Constructor sin parámetros de calificación
    Video(string tipo, string nombre, string gen, int anio, int dur);  // Constructor sin calificación
    Video(string tipo, string nombre, string gen, int calif, int anio, int dur);  // Constructor completo

    // Métodos set y get
    void setTipoVideo(const string &tipo);
    string getTipoVideo() const;

    void setNombreVideo(const string &nombre);
    string getNombreVideo() const;

    void setGenero(const string &gen);
    string getGenero() const;

    void setCalificacion(int calif);
    int getCalificacion() const;

    void setAnioLanzamiento(int anio);
    int getAnioLanzamiento() const;

    void setDuracion(int dur);
    int getDuracion() const;

    // Métodos específicos
    void calificaVideo(int calif);
    void muestraDatos() const;
};

#endif
