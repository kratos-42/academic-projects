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

    while (std::getline(ifile, line)){
        stringstream ss(line);
        while (std::getline(ss, number, ' ')) {
        	pontos.push_back(stof(number));
        }
    }
 }
