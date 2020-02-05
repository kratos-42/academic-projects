#include "Model.h"


Model::Model(){

}

Model::Model(string m){
    modelsName = m;
}



/*
Model::Model(string m, string t){
    modelsName = m;
    texture = t;
}*/


int Model::size(){
	
	return modelsName.size();
}

/*vector<string> split(string const &input) { 
    istringstream buffer(input);
    vector<string> ret {  istream_iterator<string>(buffer), 
                                    istream_iterator<string>()
                                 };
    return ret;
}
*/
void Model::loadModel(){
    float x, y, z;
    
    ifstream ifile(modelsName);
    string line, number;
    string np;
    int i, j = 0;

    while (getline(ifile, line)){
        stringstream ss(line);

        for(i = 0; i < 3 && getline(ss, number, ' '); i++){
            pontos.push_back(stof(number));

        }

        for(i = 0; i < 3 && getline(ss, number, ' '); i++){      
            normalV.push_back(stof(number));
            //cout << "normais:" << normalV[j] << endl;
        }

        for(i = 0; i < 2 && getline(ss, number, ' '); i++)
            textures.push_back(stof(number));
        
  }
  
}
/*
void Model::prepareModels(){

        loadModel();
        nVertexComponents = pontos.size();
        cout << nVertexComponents << " vertices" << endl;
        

        glGenBuffers(1, arrayBuffers);  
        glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nVertexComponents, &(pontos[0]), GL_STATIC_DRAW);  
}

void Model::draw(int nVertexComponents){

        glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, nVertexComponents);

}
          

/*
        pontos.push_back(stof(l[0]));
        pontos.push_back(stof(l[1]));
        pontos.push_back(stof(l[2]));

        normalV.push_back(stof(l[3]));
        normalV.push_back(stof(l[4]));
        normalV.push_back(stof(l[5]));

        textures.push_back(stof(l[6]));
        textures.push_back(stof(l[7]));
/*
        stringstream ss(line);
        for(i = 0; i < 3 && getline(ss, number, ' '); i++)
            pontos.push_back(stof(number));
        for(i = 0; i < 3 && getline(ss, number, ' '); i++)      
            normalV.push_back(stof(number));

        for(i = 0; i < 3 && getline(ss, number, ' '); i++)
          textures.push_back(stof(number));
          */
