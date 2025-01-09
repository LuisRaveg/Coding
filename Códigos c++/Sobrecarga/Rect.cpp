#include <iostream>
#include "Rect.h"
Rect::Rect()
{
	x = 0;
	y = 0;
}

Rect::Rect(double x, double y){
	this->x=x;
	this->y=y;
}

Rect Rect:: operator+(Rect val){
    Rect temp;

	temp.setX(x+val.getX());
	temp.setY(y+val.getY());

	return temp;
}

Rect Rect:: operator-(Rect val){
    Rect temp;

	temp.setX(x-val.getX());
	temp.setY(y-val.getY());

	return temp;
}

void Rect::setX(double x){
    this->x=x;
}

void Rect::setY(double y){
    this->y=y;
}

double Rect::getX(){
	return x;
}

double Rect::getY(){
	return y;
}

Rect::~Rect(){
}