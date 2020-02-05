#include "group.h"

Group::Group(){
}

Group::Group(Translacao tr, Rotacao rt, Escala escala, vector<Group> gr){

	trans = tr;
	rot = rt;
	esc = esc;
	groups = gr;
}




void Group::print(){
    trans.print();
    rot.print();
    esc.print();

    
    for(auto g: groups)
        g.print();
}
