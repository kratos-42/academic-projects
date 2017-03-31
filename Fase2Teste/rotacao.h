#pragma once

class Rotacao{
	float angulo;
	float x;
	float y;
	float z;

public:
	Rotacao();
	Rotacao(float, float, float, float);
	float getAngulo() { return angulo; }
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	void setAngulo(float a){ angulo = a; }
	void setX(float a){ x = a; }
	void setY(float b){ y = b; }
	void setZ(float c){ z = c; }
	virtual ~Rotacao() {};
};