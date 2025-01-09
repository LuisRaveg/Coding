#include <iostream>
#include "listaE.h"


using namespace std;

Lista::Lista()
{
	cab=NULL;
}

void Lista::insertaInicio(int d){
	Nodo *nuevo;
	nuevo = new(Nodo);
	nuevo -> setDato(d);
	nuevo -> setSiguiente(cab);
	cab = nuevo;
}

void Lista::Recorre(){
	Nodo *aux;
	aux = cab;
	while(aux != NULL){
		cout << aux->getDato() << " ";
		aux = aux->getSiguiente();
	}
	cout << endl;
}

Lista::~Lista(){
	Nodo *aux;
	while(cab!=NULL){
		aux=cab;
		cab=cab->getSiguiente();
		delete(aux);
	}
}
void Lista::eliminaNodo(int d) {
    Nodo *aux = cab;
    Nodo *anterior = NULL;

    while (aux != NULL && aux->getDato() != d) {
        anterior = aux;
        aux= aux->getSiguiente();
    }
    if (anterior == nullptr) {
        cab = aux->getSiguiente();
    } else {
        anterior->setSiguiente(aux->getSiguiente());
    }
    delete aux;
}
void Lista::insertaOrdenado(int d) {
    Nodo *aux = new Nodo();
    aux->setDato(d);

    
    if (cab == nullptr || cab->getDato() >= d) {
        aux->setSiguiente(cab);
        cab = aux;
    } else {
        Nodo *actual = cab;
        
        while (actual->getSiguiente() != nullptr && actual->getSiguiente()->getDato() < d) {
            actual = actual->getSiguiente();
        }
        
        aux->setSiguiente(actual->getSiguiente());
        actual->setSiguiente(aux);
    }
}
