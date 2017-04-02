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

using namespace std;

class Group{
	Rotacao rot;
	Translacao trans;
	Escala esc;
	vector<Group> groups;
	vector<string> modelosNames;
    vector<vector<float>> modelos;


public:
	Group();
	Group(Translacao, Rotacao, Escala, vector<Group>, vector<string>);
	~Group() {};
	Translacao getTranslacao() { return trans; }
	Rotacao getRotacao() { return rot; }
	Escala getEscala() { return esc; }
	vector<Group> getGroups(){ return groups;}
	vector<vector<float>> getModels(){ return modelos;}
	void setTranslacao(Translacao t){ trans = t; }
	void setRotacao(Rotacao r){ rot = r; }
	void setEscala(Escala e){ esc = e; }
	void addGroup(Group g){ groups.push_back(g);}
	void addModel(string m){cout << modelosNames.size() << endl; modelosNames.push_back(m); }
	//vector<string> getModels(string s){ return modelosNames;}
    void loadModels();
    void print();
};

