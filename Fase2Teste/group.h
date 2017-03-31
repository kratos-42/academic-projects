#pragma once

#ifdef __APPLE__q
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include "rotacao.h"
#include "translacao.h"
#include "escala.h"
#include <string>

using namespace std;

class Group{
	Rotacao rot;
	Translacao trans;
	Escala esc;
	vector<Group> groups;
	vector<string> modelos;



public:
	Group();
	Group(Translacao, Rotacao, Escala, vector<Group>);
	Translacao getTranslacao() { return trans; }
	Rotacao getRotacao() { return rot; }
	Escala getEscala() { return esc; }
	void setTranslacao(Translacao t){ trans = t; }
	void setRotacao(Rotacao r){ rot = r; }
	void setEscala(Escala e){ esc = e; }
	void addModel(string m){ modelos.push_back(m); }
	void draw(string filename);
	virtual ~Group() {};
};

