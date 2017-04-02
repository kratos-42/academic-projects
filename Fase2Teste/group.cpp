#include "group.h"

Group::Group(){
}

Group::Group(Translacao tr, Rotacao rt, Escala escala, vector<Group> gr, vector<string> m){

	trans = tr;
	rot = rt;
	esc = esc;
	groups = gr;
	modelosNames = m;
}


void Group::loadModels(){
    float x, y, z;
    cout << modelosNames.size() << endl;
    cout << groups.size() << endl;
    for(int i = 0; i < modelosNames.size(); i++){
        vector<float> vs;
        ifstream ifile(modelosNames[i]);
        string line, number;
        string np;

        while (std::getline(ifile, line)){
            stringstream ss(line);
            while (std::getline(ss, number, ' ')) {
                vs.push_back(stof(number));
            }
        }
        modelos.push_back(vs);
    }

}


void Group::print(){
    trans.print();
    rot.print();
    esc.print();
    for(int i = 0; i < modelos.size(); i++){
    	cout << modelosNames[i] << ": " << modelos[i].size() << endl;

    	
    }
    for(auto g: groups)
        g.print();
}
