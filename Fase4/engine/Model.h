#pragma once

#ifdef __APPLE__q
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>






using namespace std;

class Model{


	string modelsName;
	int nVertexComponents;
	vector<float> pontos;
	vector<float> normalV;
	vector<float> textures;
	GLuint* arrayBuffers;
	char* texture;
	unsigned int texID;
	unsigned char* texData;
	float diffR;
	float diffG;
	float diffB;

public:
	Model();
	Model(string m);
	void setModelsName(string m){ modelsName = m; }
	void setTexture(char* t) { texture = t;}
	void setDiffR(float d) { diffR = d;}
	void setDiffG(float d) { diffG = d;}
	void setDiffB(float d) { diffB = d;}
	GLuint getPontosBuffer() {return arrayBuffers[0];}
	void setArrayBuffers(GLuint* g){arrayBuffers=g;}
	string getModelsName(){ return modelsName;}
	GLuint* getArrayBuffers(){return arrayBuffers;}
	void prepareModels();
	void draw(int nVertexComponents);
	void loadModel();
	vector<float> getPontos(){ return pontos; }
	vector<float> getNormalV(){ return normalV; }
	vector<float> getTextures(){ return textures; }
	char* getTexture(){ return texture;}
	unsigned int getTexID(){ return texID;}
	void setTexData(unsigned char* c){ texData = c;}

	int size();
	~Model() {};

};
