#include "Fraccion.h"
#include <iostream>
#include <cmath>

int Fraccion::mcd(int a, int b) {
    if (b==0){
        return a;
    }
    return mcd(b,a%b);
}


Fraccion::Fraccion(int num, int den) {
    if (den != 0) {
        numerador = num;
        denominador = den;
        simplificarFraccion(); 
    } else {
        std::cout<<"Error";
    }
}
int Fraccion::getNumerador() {
    return numerador;
}

int Fraccion::getDenominador() {
    return denominador;
}

void Fraccion::setNumerador(int num) {
    numerador = num;
    simplificarFraccion(); 
}

void Fraccion::setDenominador(int den) {
    if (den != 0) {
        denominador = den;
        simplificarFraccion();
    } else {
        std::cout << "Error" << std::endl;
    }
}

void Fraccion::simplificarFraccion() {
    int mcd_val = mcd(std::abs(numerador), std::abs(denominador));
    numerador=std::abs(numerador / mcd_val);
    denominador= std::abs(denominador / mcd_val);
}

Fraccion Fraccion::operator+(const Fraccion& f) {
    int num_resultado = numerador * f.denominador + f.numerador * denominador;
    int den_resultado = denominador * f.denominador;
    Fraccion resultado(num_resultado, den_resultado);
    return resultado;
}

Fraccion Fraccion::operator-(const Fraccion& f) {
    int num_resultado = numerador * f.denominador - f.numerador * denominador;
    int den_resultado = denominador * f.denominador;
    Fraccion resultado(num_resultado, den_resultado);
    return resultado;
}

Fraccion Fraccion::operator*(const Fraccion& f) {
    int num_resultado = numerador * f.numerador;
    int den_resultado = denominador * f.denominador;
    Fraccion resultado(num_resultado, den_resultado);
    return resultado;
}

Fraccion Fraccion::operator/(const Fraccion& f) {
    if (f.numerador == 0) {
        std::cout << "Error" << std::endl;
        return Fraccion(0, 1); 
    }
    int num_resultado = numerador * f.denominador;
    int den_resultado = denominador * f.numerador;
    Fraccion resultado(num_resultado, den_resultado);
    return resultado;
}
bool Fraccion::operator==(const Fraccion& f) const {
    return numerador == f.numerador && denominador == f.denominador;
}
bool Fraccion::operator>(const Fraccion& f) const {
    float frac1 = static_cast<float>(numerador) / denominador;
    float frac2 = static_cast<float>(f.numerador) / f.denominador;
    return frac1 > frac2;
}
bool Fraccion::operator<(const Fraccion& f) const {
    
    float frac1 = static_cast<float>(numerador) / denominador;
    float frac2 = static_cast<float>(f.numerador) / f.denominador;
    return frac1 < frac2;
}
