#include <iostream>
#include "Rect.h"

using namespace std;

int main() {

	Rect r1(1,2);
	Rect r2(3, 4);
	Rect r3;

	r3=r1+r2;

	cout <<"La suma de las coordenadas rectangulares es: "<< r3.getX() << " " << r3.getY() << endl;

 	/*Pol p1(3, 50);
 	Pol p2(4, 30);

 	Pol p3=p1/p2;
 	cout << p3.getR() << " " << p3.getTheta() << endl;*/


	return 0;


}