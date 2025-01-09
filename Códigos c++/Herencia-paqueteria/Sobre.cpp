#include "Sobre.h"
Sobre::Sobre(){
    ancho=0;
    largo=0;
    cargo=75;
}
void Sobre::setdimensiones(double largo,double ancho){
    this->ancho =ancho;
    this ->largo =largo;
    
}
double Sobre::getlargo(){
    return largo;
}
double Sobre:: getancho(){
    return ancho;
}
double Sobre ::calculaCosto() {
    
    if((ancho>30)|| (largo>25)){
        return getCosto()+cargo;
    }else{
        return getCosto();
    }
    
}
