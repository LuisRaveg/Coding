#ifndef MATFRAC_H
#define MATFRAC_H

#include "Fraccion.h"
#include <iostream>
#include <fstream>

class MatFrac {
private:
    Fraccion m[2][2]; 

public:
    MatFrac() = default;

    void setElemento(int i, int j, const Fraccion& frac) {
        if (i < 2 && j < 2) {
            m[i][j] = frac;
        }
    }
    void cargarDesdeArchivo(std::ifstream& archivo) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                int num, den;
                archivo >> num >> den;
                setElemento(i, j, Fraccion(num, den));
            }
        }
    }

    MatFrac sumar(const MatFrac& M2) const {
        MatFrac resultado;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                resultado.m[i][j] = m[i][j].sumaFracciones(M2.m[i][j]);
            }
        }
        return resultado;
    }

    MatFrac multiplicar(const MatFrac& M2) const {
        MatFrac resultado;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                Fraccion suma;
                for (int k = 0; k < 2; ++k) {
                    suma = suma.sumaFracciones(m[i][k].multiplicaFracciones(M2.m[k][j]));
                }
                resultado.setElemento(i, j, suma);
            }
        }
        return resultado;
    }

    void imprimeMatriz() const {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                m[i][j].imprimeFraccion();
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif