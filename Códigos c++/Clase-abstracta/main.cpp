#include <iostream>
#include "Perro.h"
#include "Gato.h"
#include <list>
using namespace std;

void creaListaPerros(list<Perro*>& Perros);
void creaListaGatos(list<Gato*>& Gatos);
void recorreLista(list<Perro*> Perros);
void recorreListaGatos(list<Gato*> Gatos);

int main() {
    list<Perro*> Perros;
    list<Gato*> Gatos;
    creaListaPerros(Perros);
    recorreLista(Perros);

    creaListaGatos(Gatos);
    recorreListaGatos(Gatos);

    return 0;
}

void creaListaPerros(list<Perro*>& Perros) {
    Perro* nuevo;
    for (int i = 0; i < 10; i++) {
        nuevo = new Perro();
        nuevo->setSonido();
        Perros.push_back(nuevo);
    }
}

void creaListaGatos(list<Gato*>& Gatos) {
    Gato* nuevo;
    for (int i = 0; i < 10; i++) {
        nuevo = new Gato();
        nuevo->setSonido();
        Gatos.push_back(nuevo);
    }
}

void recorreLista(list<Perro*> Perros) {
    list<Perro*>::iterator aux;
    aux = Perros.begin();
    while (aux != Perros.end()) {
        cout << "Perro: " << (*aux)->getSonido() << endl;
        aux++;
    }
}

void recorreListaGatos(list<Gato*> Gatos) {
    list<Gato*>::iterator aux;
    aux = Gatos.begin();
    while (aux != Gatos.end()) {
        cout << "Gato: " << (*aux)->getSonido() << endl;
        aux++;
    }
}
