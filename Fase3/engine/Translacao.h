#pragma once

#include <iostream>

using namespace std;

class Translacao{
	float x;
	float y;
	float z;

public:
	Translacao();
	Translacao(float, float, float);
	~Translacao() {};
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	void setTransx(float a) { x = a; }
	void setTransy(float b) { y = b; }
	void setTransz(float c) { z = c; }
	void print();
};
