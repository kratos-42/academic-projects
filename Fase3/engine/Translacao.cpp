#include "Translacao.h"

Translacao::Translacao(){
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Translacao::Translacao(float a, float b, float c){
	x = a;
	y = b;
	z = c;
}

Translacao::Translacao(float t, vector<Ponto> vtp, int num, float d) {
	time = t;
	transPoints = vtp;
	tam = num;
	gt = d;
}


void Translacao::print(){
    cout << "Translacao(" << x << ", "
                          << y << ", "
                      	  << z << ") " << endl;
}



void getCatmullRomPoint(float t, int* indices, vector<Ponto> transP, float* res, float* deriv){
	float temp[4];
	float temp2[4];

	float m[4][4] = { 	{ -0.5f, 1.5f, -1.5f, 0.5f },
						{ 1.0f, -2.5f, 2.0f, -0.5f },
						{ -0.5f, 0.0f, 0.5f, 0.0f },
						{ 0.0f, 1.0f, 0.0f, 0.0f } };

	res[0] = 0.0; res[1] = 0.0; res[2] = 0.0;
	
	vector<float> vt = {t*t*t, t*t, t, 1};
	vector<float> vdt = {3*t*t, 2*t, 1, 0};
	

	//T*M
	temp[0] = vt[0]*m[0][0] + vt[1]*m[1][0] + vt[2]*m[2][0] + m[3][0];
	temp[1] = vt[0]*m[0][1] + vt[1]*m[1][1] + vt[2]*m[2][1] + m[3][1];
	temp[2] = vt[0]*m[0][2] + vt[1]*m[1][2] + vt[2]*m[2][2] + m[3][2];
	temp[3] = vt[0]*m[0][3] + vt[1]*m[1][3] + vt[2]*m[2][3] + m[3][3];

	int i0 = indices[0]; Ponto p0 = transP[i0];
	int i1 = indices[1]; Ponto p1 = transP[i1];
	int i2 = indices[2]; Ponto p2 = transP[i2];
	int i3 = indices[3]; Ponto p3 = transP[i3];

	//T*M*P = res
	res[0] = temp[0] * p0.getX() + temp[1] * p1.getX() + temp[2] * p2.getX() + temp[3] * p3.getX();
	res[1] = temp[0] * p0.getY() + temp[1] * p1.getY() + temp[2] * p2.getY() + temp[3] * p3.getY();
	res[2] = temp[0] * p0.getZ() + temp[1] * p1.getZ() + temp[2] * p2.getZ() + temp[3] * p3.getZ();

	// T'*M
	temp2[0] = vdt[0]*m[0][1] + vdt[1]*m[1][1] + vdt[3]*m[2][1] + m[3][1];
	temp2[1] = vdt[0]*m[0][2] + vdt[1]*m[1][2] + vdt[3]*m[2][2] + m[3][2];
	temp2[2] = vdt[0]*m[0][3] + vdt[1]*m[1][3] + vdt[3]*m[2][3] + m[3][3];
	temp2[3]  = vdt[0]*m[0][3] + vdt[1]*m[1][3] + vdt[3]*m[2][3] + m[3][3];

	deriv[0] = temp2[0] * p0.getX() + temp2[1] * p1.getX() + temp2[2] * p2.getX() + temp2[3] * p3.getX();
	deriv[1] = temp2[0] * p0.getY() + temp2[1] * p1.getY() + temp2[2] * p2.getY() + temp2[3] * p3.getY();
	deriv[2] = temp2[0] * p0.getZ() + temp2[1] * p1.getZ() + temp2[2] * p2.getZ() + temp2[3] * p3.getZ();
	
}

void Translacao::getGlobalCatmullRomPoint(float gt, vector<Ponto> transP, float* res, float* deriv) {
	int tamanho = transP.size();
	float t = gt * tamanho; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = (index + tamanho - 1) % tamanho;
	indices[1] = (indices[0] + 1) % tamanho;
	indices[2] = (indices[1] + 1) % tamanho;
	indices[3] = (indices[2] + 1) % tamanho;

	getCatmullRomPoint(t, indices, transP, res, deriv);
}



void Translacao::prepCurves() {
	float finalCoord[3];
	float deriv[3];

	for (float gt = 0; gt<1; gt += 0.01){
		getGlobalCatmullRomPoint(gt, transPoints, finalCoord, deriv);

		Ponto p = Ponto(finalCoord[0], finalCoord[1], finalCoord[2]);
		Ponto p2 = Ponto(deriv[0], deriv[1], deriv[2]);
		pontosCurva.push_back(p);
	}
}



