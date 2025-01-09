#include "Fraccion.h"
#include <iostream>
using namespace std;

int main(){
    Fraccion f1(1,2);
    Fraccion f2(1,4);
    Fraccion suma = f1 + f2;
    Fraccion resta = f1 - f2;
    Fraccion multiplicacion = f1 * f2;
    Fraccion division = f1 / f2;
    float sum = static_cast<float>(suma.getNumerador()) / suma.getDenominador();
    float mult=static_cast<float>(multiplicacion.getNumerador()) / multiplicacion.getDenominador();
    float rest=static_cast<float>(resta.getNumerador()) / resta.getDenominador();
    float div=static_cast<float>(division.getNumerador()) / division.getDenominador();
    cout<<"Fraccion 1: "<<f1.getNumerador()<<"/ "<<f1.getDenominador()<<endl;
    cout<<"Fraccion 2: "<<f2.getNumerador()<<"/ "<<f2.getDenominador()<<endl;
    cout<<"Suma: "<<suma.getNumerador()<<"/ "<<suma.getDenominador()<<", "<<sum<<endl;
    
    cout<<"Resta: "<<resta.getNumerador()<<"/ "<<resta.getDenominador()<<", "<<rest<<endl;
    cout<<"Multiplicacion: "<<multiplicacion.getNumerador()<<"/ "<<multiplicacion.getDenominador()<<", "<<mult<<endl;
    cout<<"Division: "<<division.getNumerador()<<"/ "<<division.getDenominador()<<", "<<div<<endl;
}