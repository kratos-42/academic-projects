#include "group.h"

Group::Group(){
	trans = Translacao::Translacao();
	rot = Rotacao::Rotacao();
	esc = Escala::Escala();

	
}

Group::Group(Translacao tr, Rotacao rt, Escala escala, vector<Group> gr, vector<string> m){

	trans = tr;
	rot = rt;
	esc = esc;
	groups = gr;
	modelos = m;
}


