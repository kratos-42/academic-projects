#include "Model.h"


Model::Model(){

}

Model::Model(string m){
	modelsName = m;
}


int Model::size(){
	
	return modelsName.size();
}


void Model::loadModel(){
    float x, y, z;
    
    ifstream ifile(modelsName);
    string line, number;
    string np;
    int pos;

    while (std::getline(ifile, line)){
        stringstream ss(line);
        pos = 0;
        while (std::getline(ss, number, ' ')) {
        	pontos.push_back(stof(number));
            if(pos > 2){
                if(pos < 6)
                    normalV.push_back(number);
                else    
                    textures.push_back(number);
            }
            pos++;
        }
    }
 }
