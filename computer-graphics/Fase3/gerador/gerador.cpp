#include "Gerador.h"


void create_plane(float comprimento, float largura, int camadasH, int camadasV, char* filename){

  //pontos iniciais
  FILE *file = fopen(filename, "w");

  float startX = -((float) largura / 2);
  float startZ = -((float) comprimento / 2);

  //saltos

  float saltoLarg = (float) largura / camadasH;
  float saltoComp = (float) comprimento / camadasV;

  // variaveis xx e zz -> qual o proximo local a desenhar

  float xx, zz;
  int i, j;

  for(i=0 ; i < camadasH ; i++){

    xx = startX + saltoLarg * i;

    for(j=0 ; j < camadasV ; j++){

        zz = startZ + saltoComp * j;


        fprintf(file, "%f 0 %f\n", xx, zz);
        fprintf(file, "%f 0 %f\n", xx, saltoComp + zz);
        fprintf(file, "%f 0 %f\n", saltoLarg + xx, zz);
        
        fprintf(file, "%f 0 %f\n", xx, saltoComp + zz);
        fprintf(file, "%f 0 %f\n", saltoLarg + xx, saltoComp +zz);
        fprintf(file, "%f 0 %f\n", saltoLarg + xx, zz);
        


    }

  }

  fclose(file);
}

void create_box(float comp, float larg, float alt, int cmdh, int cmdv, int cmdl, char* filename){

  FILE *file = fopen(filename, "w");
  float saltox = (float) larg / cmdl;
  float saltoz = (float) comp / cmdv;
  float saltoy = (float) alt / cmdh;
  float initX = -((float) larg / 2); //Ponto inicial x
  float initZ = -((float) comp / 2); //Ponto inicial z
  float initY = -((float) alt / 2); //Ponto incial y
  float xx, yy, zz;
  int i, j;


  //Plano inferior e superior:
  for (i = 0; i < cmdl; i++)
  {
    xx = initX + saltox * i;
    for (j = 0; j < cmdv; j++)
    {
      zz = initZ + saltoz * j;
      //Plano Inferior
      fprintf(file, "%f %f %f\n", xx, initY, zz);
      
      fprintf(file, "%f %f %f\n", xx + saltox, initY, zz);
      
      fprintf(file, "%f %f %f\n", xx, initY, zz + saltoz);
      

      fprintf(file, "%f %f %f\n", xx, initY, zz + saltoz);
      
      fprintf(file, "%f %f %f\n", xx + saltox, initY, zz);
      
      fprintf(file, "%f %f %f\n", xx + saltox, initY, zz + saltoz);
      
      //Plano Superior
      fprintf(file, "%f %f %f\n", xx, -initY, zz);
      
      fprintf(file, "%f %f %f\n", xx, -initY, zz + saltoz);
      
      fprintf(file, "%f %f %f\n", xx + saltox, -initY, zz);
    

      fprintf(file, "%f %f %f\n", xx, -initY, zz + saltoz);
  
      fprintf(file, "%f %f %f\n", xx + saltox, -initY, zz + saltoz);

      fprintf(file, "%f %f %f\n", xx + saltox, -initY, zz);

    }
  }
  

  //Plano traseiro e frontal:
  for (i = 0; i < cmdh; i++)
  {
    yy = initY + saltoy * i;
    for (j = 0; j < cmdv; j++)
    {
      zz = initZ + saltoz * j;
      //Traseiro
      fprintf(file, "%f %f %f\n", initX, yy, zz);
      
      fprintf(file, "%f %f %f\n", initX, yy + saltoy, zz + saltoz);
      
      fprintf(file, "%f %f %f\n", initX, yy + saltoy, zz);
      

      fprintf(file, "%f %f %f\n", initX, yy, zz);
      
      fprintf(file, "%f %f %f\n", initX, yy, zz + saltoz);
      
      fprintf(file, "%f %f %f\n", initX, yy + saltoy, zz + saltoz);
      
      

      //Frontal
      fprintf(file, "%f %f %f\n", -initX, yy, zz);
      
      fprintf(file, "%f %f %f\n", -initX, yy + saltoy, zz);
      
      fprintf(file, "%f %f %f\n", -initX, yy + saltoy, zz + saltoz);  
      

      fprintf(file, "%f %f %f\n", -initX, yy, zz);
      
      fprintf(file, "%f %f %f\n", -initX, yy + saltoy, zz + saltoz);
      
      fprintf(file, "%f %f %f\n", -initX, yy, zz + saltoz);
      
    }
  }
  

  //Plano lateral esquerdo e lateral direito:
  for (i = 0; i < cmdh; i++)
  { 
    yy = initY + saltoy * i;
    for (j = 0; j < cmdl; j++)
    {
      xx = initX + saltox * j;
      //Lateral esquerdo:
      fprintf(file, "%f %f %f\n", xx, yy, initZ);
      
      fprintf(file, "%f %f %f\n", xx, yy + saltoy, initZ);
      
      fprintf(file, "%f %f %f\n", xx + saltox, yy, initZ);
      

      fprintf(file, "%f %f %f\n", xx, yy + saltoy, initZ);
      
      fprintf(file, "%f %f %f\n", xx + saltox, yy + saltoy, initZ);
      
      fprintf(file, "%f %f %f\n", xx + saltox, yy, initZ);
      


      //Lateral direito:
      fprintf(file, "%f %f %f\n", xx, yy, -initZ); 
      
      fprintf(file, "%f %f %f\n", xx + saltox, yy, -initZ); 
       
      fprintf(file, "%f %f %f\n", xx, yy + saltoy, -initZ); 
       

      fprintf(file, "%f %f %f\n", xx, yy + saltoy, -initZ); 
       
      fprintf(file, "%f %f %f\n", xx + saltox, yy, -initZ); 
       
      fprintf(file, "%f %f %f\n", xx + saltox, yy + saltoy, -initZ); 
       
    }
  }
  fclose(file);
}

void create_sphere(double raio, int camadasV, int camadasH, char* filename){

  FILE *file = fopen(filename, "w");
  float teta = 0; float fi = 0;
  float saltoH = M_PI / camadasH;
  float saltoV = 2 * (M_PI) / camadasV;
  int i, j;
  float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
  
  for (i = 0; i < camadasH; i++){
    teta = 0;

    for (j = 0; j < camadasV; j++){
      x1 = raio*sin(fi)*sin(teta);
      y1 = raio*cos(fi);
      z1 = raio*sin(fi)*cos(teta);

      x2 = raio*sin(fi + saltoH)*sin(teta + saltoV);
      y2 = raio*cos(fi + saltoH);
      z2 = raio*sin(fi + saltoH)*cos(teta + saltoV);

      x3 = raio*sin(fi + saltoH)*sin(teta);
      y3 = raio*cos(fi + saltoH);
      z3 = raio*sin(fi + saltoH)* cos(teta);

      x4 = raio*sin(fi)*sin(teta + saltoV);
      y4 = raio*cos(fi);
      z4 = raio*sin(fi)*cos(teta + saltoV);


      fprintf(file, "%f %f %f\n", x1, y1, z1);
      fprintf(file, "%f %f %f\n", x2, y2, z2);
      fprintf(file, "%f %f %f\n", x3, y3, z3);

      fprintf(file, "%f %f %f\n", x1, y1, z1);
      fprintf(file, "%f %f %f\n", x4, y4, z4);
      fprintf(file, "%f %f %f\n", x2, y2, z2);

      teta += saltoV;
    }
    fi += saltoH;
  }

  fclose(file);
}

void create_cone(double raio, double altura, double cmdv, double cmdh, char* filename){

  FILE *file = fopen(filename, "w");
  double espv = (2 * M_PI) / cmdv;
  double espl = altura / cmdh;
  double dif = raio / cmdh;
  double alfa = 0;
  double alfa1 = espv;


  altura = -(altura / 2);

  //This cycle represents the base construction.
  for (int i = 0; i <= cmdv; i++){
    fprintf(file, "%f %f %f\n", raio*sin(alfa), altura, raio*cos(alfa)); 
    fprintf(file, "0 %f 0\n", altura); 
    fprintf(file, "%f %f %f\n", raio*sin(alfa1), altura, raio*cos(alfa1)); 

    alfa = espv*(i + 1);
    alfa1 = espv*(i + 2);
  }

  //At this point, we build the rest of the solid.
  for (int i = 0; i < cmdh; i++){

    for (int j = 0; j < cmdv; j++){
      alfa += espv;
      double raionovo = raio - dif;

      fprintf(file, "%f %f %f\n", raio*sin(alfa), altura, raio*cos(alfa)); 
      fprintf(file, "%f %f %f\n", raio*sin(alfa + espv), altura, raio*cos(alfa + espv)); 
      fprintf(file, "%f %f %f\n", raionovo*sin(alfa), altura + espl, raionovo*cos(alfa)); 

      fprintf(file, "%f %f %f\n", raio*sin(alfa + espv), altura, raio*cos(alfa + espv)); 
      fprintf(file, "%f %f %f\n", raionovo*sin(alfa + espv), altura + espl, raionovo*cos(alfa + espv));
      fprintf(file, "%f %f %f\n", raionovo*sin(alfa), altura + espl, raionovo*cos(alfa)); 
    }
    raio = raio - dif;
    altura = altura + espl;
  }
}


void readPatchFile(string patchFile){

  int i, j, indice, nrPatches, hop, nrPoints, coord;
  float point[3], n;
  string line, currCoord, currIndice;

  ifstream file;
  file.open(patchFile, ios::in);

  if(file.is_open()){
    getline(file, line);
    nrPatches = stoi(line);

    for(i = 0; i < nrPatches && getline(file, line); i++){
      Patch patch = Patch();

      for(j = 0; j < 16; j++){
        hop = line.find(",");
        currIndice = line.substr(0, hop);
        indice = atof(currIndice.c_str());
        line.erase(0, hop+1);

        patch.addIndice(indice);
      }

      patches.push_back(patch);
    }

    getline(file, line);
    nrPoints = stoi(line);

    for (i = 0; i < nrPoints && getline(file, line); i++){
        for (j = 0; j < 3; j++) {
          hop = line.find(",");
          currCoord = line.substr(0, hop);
          coord = atof(currCoord.c_str());
          line.erase(0, hop+1);

          point[j] = coord;
        }
        vertices.push_back(Ponto(point[0], point[1], point[2]));
      }
      
  file.close();
}
  
  else {
      printf("Ficheiro %s.patch não existe. Verifique a diretoria.\n", patchFile);
    }

}

Ponto calculatePoint(float t, float *p1, float *p2, float *p3, float *p4) {
  
  float finalPoints[3];

  float it = 1.0 - t;

  float b0 = it * it * it; // (1-t)³ 
  float b1 = 3 * t * it * it; // 3 x (1-t)²t
  float b2 = 3 * t * t * it; // 3 x (1-t)²t
  float b3 = t * t * t; // (1-t)³ 

  finalPoints[0] = b0*p1[0] + b1*p2[0] + b2*p3[0] + b3*p4[0];
  finalPoints[1] = b0*p1[1] + b1*p2[1] + b2*p3[1] + b3*p4[1];
  finalPoints[2] = b0*p1[2] + b1*p2[2] + b2*p3[2] + b3*p4[2];

  return Ponto(finalPoints[0], finalPoints[1], finalPoints[2]);
}


Ponto bezier(float u, float v, vector<int> pID) {
  
  float bz[4][3], points[4][3];
  int i, j = 0, k = 0;

  for (i = 0; i < 16; i++) {
    bz[j][0] = vertices[pID[i]].getX();
    bz[j][1] = vertices[pID[i]].getY();
    bz[j][2] = vertices[pID[i]].getZ();

    j++;

    if (j % 4 == 0) {
      Ponto p = calculatePoint(u, bz[0], bz[1], bz[2], bz[3]);
      points[k][0] = p.getX();
      points[k][1] = p.getY();
      points[k][2] = p.getZ();

      k++;
      j = 0;
    }
  }
  return calculatePoint(v, points[0], points[1], points[2], points[3]);
}

void patchBezier(int tess, int idPatch, ofstream& file) {
  
  float inc = 1.0 / tess, u, v, u2, v2;

  for (int i = 0; i < tess; i++) {
    for (int j = 0; j < tess; j++) {
      u = i*inc;
      v = j*inc;
      u2 = (i + 1)*inc;
      v2 = (j + 1)*inc;

      Ponto p0 = bezier(u, v, patches[idPatch].getPatch());
      Ponto p1 = bezier(u, v2, patches[idPatch].getPatch());
      Ponto p2 = bezier(u2, v, patches[idPatch].getPatch());
      Ponto p3 = bezier(u2, v2, patches[idPatch].getPatch());

      file << p1.getX() << " " << p1.getY() << " " << p1.getZ() << endl;
      file << p2.getX() << " " << p2.getY() << " " << p2.getZ() << endl;
      file << p3.getX() << " " << p3.getY() << " " << p3.getZ() << endl;

    }
  }
}

//Escrever pontos do teapot
void prepBezier(int tess, string fileToWrite) {
  ofstream file;
  file.open(fileToWrite);

  int num = patches.size();

  for (int i = 0; i < num; i++)
    patchBezier(tess, i, file);
  
  file.close();
}







  int main(int argc, char** argv){

  
  char* file = argv[2];
  string str;
  int fd;


  if(argc == 1){

    cout << "                               **********************" << endl;
    cout << "                               **Menu de utilização**" << endl;
    cout << "                               **********************" << endl;

    //printf("Argumentos inválidos. Menu de utilização:\n");
    printf("\nplane <comprimento> <largura> <nº camada horizontais> <nº camadas verticais>  <filename>\n");
    printf("\nbox <comprimento> <largura> <altura> <nº camadas horizontais> <nº camadas verticais> <nº camadas laterais> <filename>\n");
    printf("\nsphere <raio> <nº camadas horizontais> <nº camadas verticais> <filename>\n");
    printf("\ncone <raio> <altura> <nº camadas horizontais> <nº camadas verticais> <filename>\n");
    printf("\nfile.patch <tessellation level> <filename>\n");
    cout << "\nPS: utilize a diretoria do engine como prefixo do filename" << endl; 

    return 0;


  }

  if(strcmp((argv[1]), "plane") == 0 && argc == 7){
      create_plane(atof(argv[2]), atoi(argv[3]), atof(argv[4]), atoi(argv[5]), argv[6]);
  }
  
  else if(strcmp((argv[1]), "box") == 0 && argc == 9)
      create_box(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atoi(argv[6]), atoi(argv[7]), argv[8]);

  else if(strcmp(argv[1], "sphere") == 0 && argc == 6)
      create_sphere(atof(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);

  else if(strcmp(argv[1], "cone") == 0 && argc == 7)
      create_cone(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);

  else if(argc == 4){
      str = argv[1];
      if(str.find(".patch")){
        readPatchFile((argv[1]));
        prepBezier(atof(argv[2]), (argv[3]));
      }
  }
    
  else {
    printf("Argumentos inválidos. Menu de utilização:\n");
    printf("\nplane <comprimento> <largura> <nº camada horizontais> <nº camadas verticais>  <filename>\n");
    printf("\nbox <comprimento> <largura> <altura> <nº camadas horizontais> <nº camadas verticais> <nº camadas laterais> <filename>\n");
    printf("\nsphere <raio> <nº camadas horizontais> <nº camadas verticais> <filename>\n");
    printf("\ncone <raio> <altura> <nº camadas horizontais> <nº camadas verticais> <filename>\n");

  }
  return 0;
}


