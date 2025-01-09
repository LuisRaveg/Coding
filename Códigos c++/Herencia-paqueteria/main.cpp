#include <iostream>
#include "Sobre.h"
#include "Paquete.h"
#include "Envio.h"
#include <string>
using namespace std;
int main() {
    Envio envio;
    int opcion;
    string nombre1, direccion1,nombre2,direccion2, ciudad, estado;
    double largo,ancho,profundidad,pesokg;
    cout<<"Ingrese su nombre: ";
    Sobre sobre;
    getline(cin, nombre1);
    envio.setNombre1(nombre1);
    cout << "Ingrese su direccion  (Direccion,Ciudad,Estado y codigo postal): ";
    getline(cin,direccion1);
    envio.setDireccion1(direccion1);
    cout<<"Ingrese el nombre del destinatario: ";
    getline(cin, nombre2);
    envio.setNombre2(nombre2);
    cout << "Ingrese la direccion del destinatario  (Direccion,Ciudad,Estado y codigo postal): ";
    getline(cin,direccion2);
    envio.setDireccion2(direccion2);
    while(opcion!=0){
        cout<<"1. Costo envio sobre"<<endl;
        cout<<"2. Costo envio paquete"<<endl;
        cout<<"Salir"<<endl;
        cout<<"0. Ingrese una opcion:  ";
        cin>>opcion;
        if (opcion==1){
            cout<<"Ingrese el largo del sobre: ";
            cin>>largo;
            cout<<"Ingrese el ancho del sobre: ";
            cin>>ancho;
            sobre.setdimensiones(largo, ancho);
            sobre.setCosto(100);
            cout << "Costo total del sobre: " << sobre.calculaCosto() << endl;
        }else if(opcion==2){
            cout<<"Ingrese el largo del paquete: ";
            cin>>largo;
            cout<<"Ingrese el ancho del paquete: ";
            cin>>ancho;
            cout<<"Ingrese la profundidad del paquete: ";
            cin>>profundidad;
            cout<<"Ingrese el peso del paquete (kg): ";
            cin>>pesokg;
            Paquete paquete(largo, ancho, profundidad, pesokg, 2.5);
            paquete.setCosto(200);
            cout<<"Costo estandar del envio: "<<paquete.getCosto()<<endl;
            cout << "Costo del paquete: " << paquete.calculaCosto() << endl;
        }
    }
    return 0;
}
