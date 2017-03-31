#include "group.h"

Group::Group(){
	trans = Translacao::Translacao();
	rot = Rotacao::Rotacao();
	esc = Escala::Escala();

	
}

Group::Group(Translacao tr, Rotacao rt, Escala escala, vector<Group> gr, ){

	trans = tr;
	rot = rt;
	esc = esc;
	groups = gr;
}

void Group::draw(char* filename){


	float x, y, z;
	FILE *f;

	glBegin(GL_TRIANGLES);
	int r = 0;

	f = fopen(filename, "r");

	while(r != -1){

		r = fscanf(f, "%f %f %f", &x, &y, &z);
		if (r == 3){
			glColor3f(0, 1, 1);
			glVertex3f(x, y, z);
		}
	}
	fclose(f);

	glEnd();
}


