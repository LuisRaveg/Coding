#ifndef FRACCION_H
#define FRACCION_H

class Fraccion {
private:
    int numerador;
    int denominador;
    int mcd(int a, int b);
    void simplificarFraccion();

public:
    
    Fraccion(int num = 2, int den = 4);
    int getNumerador();
    int getDenominador();
    void setNumerador(int numerador);
    void setDenominador(int denominador);
    Fraccion operator+(const Fraccion& f);
    Fraccion operator-(const Fraccion& f);
    Fraccion operator*(const Fraccion& f);
    Fraccion operator/(const Fraccion& f);
    bool operator==(const Fraccion& f) const;
    bool operator>(const Fraccion& f) const;
    bool operator<(const Fraccion& f) const;
};

#endif
