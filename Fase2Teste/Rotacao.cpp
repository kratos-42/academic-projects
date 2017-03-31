#include "rotacao.h"

Rotacao::Rotacao(){
	angulo = 0.0;
	x = 0.0;
	y = 0.0;
	z = 0.0;

}

Rotacao::Rotacao(float a, float b, float c, float d){
	angulo = a;
	x = b;
	y = c;
	z = d;
}