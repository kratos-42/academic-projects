#pragma once

#include <iostream>
#include "Ponto.h"
#include <vector>
#include <math.h>

using namespace std;

class Translacao{
	float x;
	float y;
	float z;
	float time;
	int tam;
	float gt;

	vector<Ponto> transPoints;
	vector<Ponto> pontosCurva;
	vector<Ponto> pontosDeriv;

public:
	Translacao();
	Translacao(float, vector<Ponto>, int, float);
	Translacao(float, float, float);
	~Translacao() {};
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	float getGt() { return gt;}
	void updateGt(float t) { gt = t;}
	void prepCurves();
	vector<Ponto> getTransPoints(){ return transPoints; }
	vector<Ponto> getPontosCurva(){ return pontosCurva; }
	float getTime(){ return time; }
	void setTime(float t) { time = t; }
	void getGlobalCatmullRomPoint(float gt, vector<Ponto> transP, float* res, float* deriv);
	void setTransPoints(vector<Ponto> p){ transPoints = p; }
	void setPontosCurva(vector<Ponto> p){ pontosCurva = p; }
	void setTransx(float a) { x = a; }
	void setTransy(float b) { y = b; }
	void setTransz(float c) { z = c; }
	void print();

};
