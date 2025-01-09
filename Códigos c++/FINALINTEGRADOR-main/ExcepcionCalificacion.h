#ifndef EXCEPCIONCALIFICACION_H
#define EXCEPCIONCALIFICACION_H

#include <stdexcept>
#include <string>

class ExcepcionCalificacion : public std::runtime_error {
public:
    ExcepcionCalificacion(const std::string& mensaje)
        : std::runtime_error(mensaje) {}
};

#endif
