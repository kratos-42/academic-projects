#pragma once

#ifdef __APPLE__q
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "Rotacao.h"
#include "Translacao.h"
#include "Escala.h"
#include "Model.h"
#include "Light.h"

using namespace std;

class Group{
	Rotacao rot;
	Translacao trans;
	Escala esc;
	vector<Group> groups;
    vector<Model> models;
    vector<Light> lights;


public:
	Group();
	Group(Translacao, Rotacao, Escala, vector<Group>);
	~Group() {};
	Translacao getTranslacao() { return trans; }
	Rotacao getRotacao() { return rot; }
	Escala getEscala() { return esc; }
	vector<Group> getGroups(){ return groups;}
	//vector<vector<float>> getModels(){ return modelos;}
	void setTranslacao(Translacao t){ trans = t; }
	void setRotacao(Rotacao r){ rot = r; }
	void setEscala(Escala e){ esc = e; }
	void addGroup(Group g){ groups.push_back(g);}
	void addModel(Model m){ models.push_back(m); }
	void addLight(Light l) {lights.push_back(l);}
	vector<Model> getModels(){ return models;}
    string getModel(){ return models[0].getModelsName();}
    void loadModels();
    void print();
};

