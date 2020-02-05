#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Ponto.h"


using namespace std;

class Light{

	vector<float> lvector;
	Ponto lpoint;

public:
	Light();
	void setLvector(float posX,float posY,float posZ){ lvector.push_back(posX); lvector.push_back(posY); lvector.push_back(posZ); }
	void setLpoint(Ponto p) {lpoint = p;}
	vector<float> getLvector(){ return lvector;}
	Ponto getLpoint(){ return lpoint;}
	~Light() {};

};