#ifndef FRACCION_H
#define FRACCION_H
#include <iostream>
#include <stdexcept>
class Fraccion {
private:
    int numerador;
    int denominador;
    int gcd(int a, int b) const {
        if (b == 0) return a;
        return gcd(b, a % b);
    }
public:
    Fraccion(int num = 0, int den = 1) : numerador(num), denominador(den) {
        if (den == 0) throw std::invalid_argument("Operacion imposible");
        reduceFraccion();
    }

    void setNumerador(int num) { numerador = num; }
    int getNumerador() const { return numerador; }

    void setDenominador(int den) { 
        if (den == 0) throw std::invalid_argument("Operacion imposible");
        denominador = den;
        reduceFraccion();
    }
    int getDenominador() const { return denominador; }

    void reduceFraccion() {
        int divisor = gcd(numerador, denominador);
        numerador /= divisor;
        denominador /= divisor;
        if (denominador < 0) { 
            numerador = -numerador;
            denominador = -denominador;
        }
    }

    Fraccion sumaFracciones(const Fraccion& f2) const {
        int num = numerador * f2.denominador + f2.numerador * denominador;
        int den = denominador * f2.denominador;
        return Fraccion(num, den);
    }

    Fraccion multiplicaFracciones(const Fraccion& f2) const {
        int num = numerador * f2.numerador;
        int den = denominador * f2.denominador;
        return Fraccion(num, den);
    }

    void imprimeFraccion() const {
        std::cout << numerador << " / " << denominador;
    }

    void leerFraccion() {
        int num, den;
        std::cout << "Ingrese el numerador y denominador (numerador denominador): ";
        std::cin >> num >> den;
        *this = Fraccion(num, den);
    }
};

#endif
