#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


using namespace std;

class Model{
	string modelsName;
	vector<float> pontos;
	vector<float> normalV;
	vector<float> textures;

public:
	Model();
	void setModel(string m){ modelsName = m; }
	string getModelsName(){ return modelsName;}
	void loadModel();
	Model(string m);
	vector<float> getPontos(){ return pontos; }
	int size();
	~Model() {};

};
