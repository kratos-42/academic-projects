#include "Escala.h"

Escala::Escala(){
	x = 1.0;
	y = 1.0;
	z = 1.0;
};

Escala::Escala(float a, float b, float c){
	x = a;
	y = b;
	z = c;
};


void Escala::print(){
    cout << "Escala(" << x << ", "
                      << y << ", "
                      << z << endl;
}
