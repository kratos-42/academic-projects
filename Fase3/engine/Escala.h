#pragma once

#include <iostream>

using namespace std;

class Escala{
	float x;
	float y;
	float z;

public:
	Escala();
	Escala(float, float, float);
	~Escala() {};
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	void setX(float a){ x = a; }
	void setY(float b){ y = b; }
	void setZ(float c){ z = c; }
    void print();
};
