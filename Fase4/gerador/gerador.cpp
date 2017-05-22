#include "Gerador.h"

void printCoords(FILE* file, vector<Ponto> p, vector<Ponto> n, vector<Ponto> t){

  
  fprintf(file, "%f %f %f %f %f %f %f %f %f\n", p[0].getX(), p[0].getY(), p[0].getZ(), n[0].getX(), n[0].getY(), n[0].getZ(), t[0].getX(), t[0].getY(), t[0].getZ());
  fprintf(file, "%f %f %f %f %f %f %f %f %f\n", p[1].getX(), p[1].getY(), p[1].getZ(), n[1].getX(), n[1].getY(), n[1].getZ(), t[1].getX(), t[1].getY(), t[1].getZ());
  fprintf(file, "%f %f %f %f %f %f %f %f %f\n", p[2].getX(), p[2].getY(), p[2].getZ(), n[2].getX(), n[2].getY(), n[2].getZ(), t[2].getX(), t[2].getY(), t[2].getZ());


}  


void create_plane(float comp, float larg, int cmdh, int cmdv, char* filename){

  //pontos iniciais
  FILE* file = fopen(filename, "w");
  float saltoz = (float) comp / cmdv; //Salto em comprimento
  float saltox = (float) larg / cmdh; //Salto em largura 
  float refx = -((float) larg / 2); //Ponto inicial x
  float refz = -((float) comp / 2); //Ponto inicial z
  float xx, zz;
  int i,j;

  //Saltos nas texturas
  float saltoTexx = 1.0 / cmdv;
  float saltoTexz = 1.0 / cmdh;


  // Normais e texturas:
  vector<Ponto> pontos;
  vector<Ponto> normalV;
  vector<Ponto> textures;

  //Numero de pontos:


  for (i = 0; i < cmdh; i++){
    xx = refx + saltox * i;

    for (j = 0; j < cmdv; j++){
      zz = refz + saltoz * j;

      pontos.push_back(Ponto(xx, 0, zz));
      normalV.push_back(Ponto(0, 1, 0));
      textures.push_back(Ponto(1 - (cmdv - j)*saltoTexx, 1 - i*saltoTexz, 0));
      
      pontos.push_back(Ponto(xx, 0, zz + saltoz));
      normalV.push_back(Ponto(0, 1, 0));
      textures.push_back(Ponto(1 - (cmdv - j)*saltoTexx, 1 - (i+1)*saltoTexz, 0));
      
      pontos.push_back(Ponto(xx + saltox, 0, zz));
      normalV.push_back(Ponto(0, 1, 0));
      textures.push_back(Ponto(1 - (cmdv - (j+1))*saltoTexx, 1 - i*saltoTexz, 0));

      printCoords(file, pontos, normalV, textures);
      pontos.clear(); normalV.clear(); textures.clear();


      pontos.push_back(Ponto(xx, 0, zz + saltoz));
      normalV.push_back(Ponto(0, 1, 0));
      textures.push_back(Ponto(1 - (cmdv - j)*saltoTexx, 1 - (i + 1)*saltoTexz, 0));


      pontos.push_back(Ponto(xx + saltox, 0, zz + saltoz));
      normalV.push_back(Ponto(0, 1, 0));
      textures.push_back(Ponto(1 - (cmdv - (j + 1))*saltoTexx, 1 - (i + 1)*saltoTexz, 0));


      pontos.push_back(Ponto(xx + saltox, 0, zz));
      normalV.push_back(Ponto(0, 1, 0));
      textures.push_back(Ponto(1 - (cmdv - (j + 1))*saltoTexx, 1 - i*saltoTexz, 0));


      printCoords(file, pontos, normalV, textures);
      pontos.clear(); normalV.clear(); textures.clear();
      }
    }
    fclose(file);
}












/*
  FILE* file = fopen(filename, "w");

  float h = size/2; 
  float texV = 1 / (float) size;
  float texH = 1 / (float) size;

  vector<float> pontos;
  vector<float> normalV;
  vector<float> textures;

  pontos.push_back(Ponto(h,0,h));
  normalV.push_back(Ponto(0,1,0));
  textures.push_back(Ponto(1,1,0));
  printCoords(file, pontos, normalV, textures);
  pontos.clear(); normalV.clear(); textures.clear();

  pontos.push_back(Ponto(h,0,-h));
  normalV.push_back(Ponto(0,1,0));
  textures.push_back(Ponto(1,0,0));
  printCoords(file, pontos, normalV, textures);
  pontos.clear(); normalV.clear(); textures.clear();

  pontos.push_back(Ponto(-h,0,h));
  normalV.push_back(Ponto(0,1,0));
  textures.push_back(Ponto(0,1,0));
  printCoords(file, pontos, normalV, textures);
  pontos.clear(); normalV.clear(); textures.clear();

  pontos.push_back(Ponto(-h,0,h));
  normalV.push_back(Ponto(0,-1,0));
  textures.push_back(Ponto(0,1,0));
  printCoords(file, pontos, normalV, textures);
  pontos.clear(); normalV.clear(); textures.clear();

  pontos.push_back(Ponto(h,0,-h));
  normalV.push_back(Ponto(0,-1,0));
  textures.push_back(Ponto(1,0,0));
  printCoords(file, pontos, normalV, textures);
  pontos.clear(); normalV.clear(); textures.clear();

  pontos.push_back(Ponto(-h,0,-h));
  normalV.push_back(Ponto(0,-1,0));
  textures.push_back(Ponto(0,0,0));
  printCoords(file, pontos, normalV, textures);
  pontos.clear(); normalV.clear(); textures.clear();


  fclose(file);
}
*/


void create_box(float comp, float larg, float alt, int cmdh, int cmdv, int cmdl, char* filename){

  FILE* file = fopen(filename, "w");

  float x = comp/2;
  float y = alt/2;
  float z = larg/2;

  float saltoX = (float)comp/cmdv;
  float saltoY = (float)alt/cmdh;
  float saltoZ = (float)larg/cmdl;

  float textureY1 = larg/((larg*2)+alt);
  float textureY2 = (larg+alt)/((larg*2)+alt);

  float textureX1 = (larg)/((larg*2)+(comp*2));
  float textureX2 = (larg+comp)/((larg*2)+(comp*2));
  float textureX3 = ((larg*2)+comp)/((larg*2)+(comp*2));

  float textureSaltoX = (larg/((larg*2)+(comp*2)))/cmdh;
  float textureSaltoY = (alt/((larg*2)+alt))/cmdv;
  float textureSaltoZ = (comp/((larg*2)+(comp*2)))/cmdl;

  vector<Ponto> normalV;
  vector<Ponto> textures;
  vector<Ponto> pontos;

  for(int i=0;i<alt;i++){
    for(int j=0;j<comp;j++){
      //Face da frente
      pontos.push_back(Ponto(-x + (j*saltoX),-y + (i*saltoY),z));
      pontos.push_back(Ponto((-x+saltoX) + (j*saltoX),-y + (i*saltoY),z));
      pontos.push_back(Ponto(-x + (j*saltoX),(-y+saltoY) + (i*saltoY),z));
      normalV.push_back(Ponto(0,0,1));
      normalV.push_back(Ponto(0,0,1));
      normalV.push_back(Ponto(0,0,1));
      textures.push_back(Ponto(textureX1+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto((textureX1+textureSaltoX)+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto(textureX1+(j*textureSaltoX),(textureY1+textureSaltoY)+(i*textureSaltoY),0));

      printCoords(file, pontos, normalV, textures);
      pontos.clear(); normalV.clear(); textures.clear();
      

      pontos.push_back(Ponto(-x + (j*saltoX),(-y+saltoY) + (i*saltoY),z));
      pontos.push_back(Ponto((-x+saltoX) + (j*saltoX),-y + (i*saltoY),z));
      pontos.push_back(Ponto((-x+saltoX) + (j*saltoX),(-y+saltoY) + (i*saltoY),z));
      normalV.push_back(Ponto(0,0,1));
      normalV.push_back(Ponto(0,0,1));
      normalV.push_back(Ponto(0,0,1));
      textures.push_back(Ponto(textureX1+(j*textureSaltoX),(textureY1+textureSaltoY)+(i*textureSaltoY),0));
      textures.push_back(Ponto((textureX1+textureSaltoX)+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto((textureX1+textureSaltoX)+(j*textureSaltoX),(textureY1+textureSaltoY)+(i*textureSaltoY),0));

      printCoords(file, pontos, normalV, textures);
      pontos.clear(); normalV.clear(); textures.clear();
    

      //Face traseira
      pontos.push_back(Ponto(-x + (j*saltoX),-y + (i*saltoY),-z));
      pontos.push_back(Ponto(-x + (j*saltoX),(-y+saltoY) + (i*saltoY),-z));
      pontos.push_back(Ponto((-x+saltoX) + (j*saltoX),-y + (i*saltoY),-z));
      normalV.push_back(Ponto(0,0,-1));
      normalV.push_back(Ponto(0,0,-1));
      normalV.push_back(Ponto(0,0,-1));
      textures.push_back(Ponto(textureX3+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto((textureX3+textureSaltoX)+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto(textureX3+(j*textureSaltoX),(textureY1+textureSaltoY)+(i*textureSaltoY),0));

      printCoords(file, pontos, normalV, textures);
      pontos.clear(); normalV.clear(); textures.clear();

      pontos.push_back(Ponto(-x + (j*saltoX),(-y+saltoY) + (i*saltoY),-z));
      pontos.push_back(Ponto((-x+saltoX) + (j*saltoX),(-y+saltoY) + (i*saltoY),-z));
      pontos.push_back(Ponto((-x+saltoX) + (j*saltoX),-y + (i*saltoY),-z));
      normalV.push_back(Ponto(0,0,-1));
      normalV.push_back(Ponto(0,0,-1));
      normalV.push_back(Ponto(0,0,-1));
      textures.push_back(Ponto(textureX3+(j*textureSaltoX),(textureY1+textureSaltoY)+(i*textureSaltoY),0));
      textures.push_back(Ponto((textureX3+textureSaltoX)+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto((textureX3+textureSaltoX)+(j*textureSaltoX),(textureY1+textureSaltoY)+(i*textureSaltoY),0));

      printCoords(file, pontos, normalV, textures);
      pontos.clear(); normalV.clear(); textures.clear();

      //Face direita
      pontos.push_back(Ponto(x,-y + (i*saltoY),-z + (j*saltoZ)));
      pontos.push_back(Ponto(x,(-y+saltoY) + (i*saltoY),-z +(j*saltoZ)));
      pontos.push_back(Ponto(x,-y + (i*saltoY),(-z+saltoZ) + (j*saltoZ)));
      normalV.push_back(Ponto(1,0,0));
      normalV.push_back(Ponto(1,0,0));
      normalV.push_back(Ponto(1,0,0));
      textures.push_back(Ponto(textureX3-(j*textureSaltoZ),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto((textureX3-textureSaltoZ)+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto(textureX3-(j*textureSaltoZ),(textureY1+textureSaltoY)+(i*textureSaltoY),0));

      printCoords(file, pontos, normalV, textures);
      pontos.clear(); normalV.clear(); textures.clear();

      pontos.push_back(Ponto(x,(-y+saltoY) + (i*saltoY),-z + (j*saltoZ)));
      pontos.push_back(Ponto(x,(-y+saltoY) + (i*saltoY),(-z+saltoZ) + (j*saltoZ)));
      pontos.push_back(Ponto(x,-y + (i*saltoY),(-z+saltoZ) + (j*saltoZ)));
      normalV.push_back(Ponto(1,0,0));
      normalV.push_back(Ponto(1,0,0));
      normalV.push_back(Ponto(1,0,0));
      textures.push_back(Ponto(textureX2+(j*textureSaltoZ),(textureY1+textureSaltoY)+(i*textureSaltoY),0));
      textures.push_back(Ponto((textureX2+textureSaltoZ)+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto((textureX2+textureSaltoZ)+(j*textureSaltoX),(textureY1+textureSaltoY)+(i*textureSaltoY),0));

      printCoords(file, pontos, normalV, textures);
      pontos.clear(); normalV.clear(); textures.clear();

      //Face esquerda
      pontos.push_back(Ponto(-x,-y + (i*saltoY),-z + (j*saltoZ)));
      pontos.push_back(Ponto(-x,-y + (i*saltoY),(-z+saltoZ) + (j*saltoZ)));
      pontos.push_back(Ponto(-x,(-y+saltoY) + (i*saltoY),-z +(j*saltoZ)));
      normalV.push_back(Ponto(-1,0,0));
      normalV.push_back(Ponto(-1,0,0));
      normalV.push_back(Ponto(-1,0,0));
      textures.push_back(Ponto((j*textureSaltoZ),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto(textureSaltoZ+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto((j*textureSaltoZ),(textureY1+textureSaltoY)+(i*textureSaltoY),0));

      printCoords(file, pontos, normalV, textures);
      pontos.clear(); normalV.clear(); textures.clear();

      pontos.push_back(Ponto(-x,(-y+saltoY) + (i*saltoY),-z + (j*saltoZ)));
      pontos.push_back(Ponto(-x,-y + (i*saltoY),(-z+saltoZ) + (j*saltoZ)));
      pontos.push_back(Ponto(-x,(-y+saltoY) + (i*saltoY),(-z+saltoZ) + (j*saltoZ)));
      normalV.push_back(Ponto(-1,0,0));
      normalV.push_back(Ponto(-1,0,0));
      normalV.push_back(Ponto(-1,0,0));
      textures.push_back(Ponto((j*textureSaltoX),(textureY1+textureSaltoY)+(i*textureSaltoY),0));
      textures.push_back(Ponto(textureSaltoX+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto(textureSaltoX+(j*textureSaltoX),(textureY1+textureSaltoY)+(i*textureSaltoY),0));

      printCoords(file, pontos, normalV, textures);
      pontos.clear(); normalV.clear(); textures.clear();

      //Topo
      pontos.push_back(Ponto(-x + (j*saltoX),y,-z + (i*saltoZ)));
      pontos.push_back(Ponto(-x + (j*saltoX),y,(-z+saltoZ) + (i*saltoZ)));
      pontos.push_back(Ponto((-x+saltoX) + (j*saltoX),y,-z + (i*saltoZ)));
      normalV.push_back(Ponto(0,1,0));
      normalV.push_back(Ponto(0,1,0));
      normalV.push_back(Ponto(0,1,0));
      textures.push_back(Ponto(textureX1+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto((textureX1+textureSaltoX)+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto(textureX1+(j*textureSaltoX),(textureY1+textureSaltoY)+(i*textureSaltoY),0));

      printCoords(file, pontos, normalV, textures);
      pontos.clear(); normalV.clear(); textures.clear();

      pontos.push_back(Ponto(-x + (j*saltoX),y,(-z+saltoZ) + (i*saltoZ)));
      pontos.push_back(Ponto((-x+saltoX) + (j*saltoX),y,(-z+saltoZ) + (i*saltoZ)));
      pontos.push_back(Ponto((-x+saltoX) + (j*saltoX),y,-z + (i*saltoZ)));
      normalV.push_back(Ponto(0,1,0));
      normalV.push_back(Ponto(0,1,0));
      normalV.push_back(Ponto(0,1,0));
      textures.push_back(Ponto(textureX1+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto((textureX1+textureSaltoX)+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto(textureX1+(j*textureSaltoX),(textureY1+textureSaltoY)+(i*textureSaltoY),0));

      printCoords(file, pontos, normalV, textures);
      pontos.clear(); normalV.clear(); textures.clear();

      //Base
      pontos.push_back(Ponto(-x + (j*saltoX),-y,-z + (i*saltoZ)));
      pontos.push_back(Ponto((-x+saltoX) + (j*saltoX),-y,-z + (i*saltoZ)));
      pontos.push_back(Ponto(-x + (j*saltoX),-y,(-z+saltoZ) + (i*saltoZ)));
      normalV.push_back(Ponto(0,-1,0));
      normalV.push_back(Ponto(0,-1,0));
      normalV.push_back(Ponto(0,-1,0));
      textures.push_back(Ponto(textureX1+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto((textureX1+textureSaltoX)+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto(textureX1+(j*textureSaltoX),(textureY1+textureSaltoY)+(i*textureSaltoY),0));

      printCoords(file, pontos, normalV, textures);
      pontos.clear(); normalV.clear(); textures.clear();

      pontos.push_back(Ponto(-x + (j*saltoX),-y,(-z+saltoZ) + (i*saltoZ)));
      pontos.push_back(Ponto((-x+saltoX) + (j*saltoX),-y,-z + (i*saltoZ)));
      pontos.push_back(Ponto((-x+saltoX) + (j*saltoX),-y,(-z+saltoZ) + (i*saltoZ))); 
      normalV.push_back(Ponto(0,-1,0));
      normalV.push_back(Ponto(0,-1,0));
      normalV.push_back(Ponto(0,-1,0));
      textures.push_back(Ponto(textureX1+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto((textureX1+textureSaltoX)+(j*textureSaltoX),textureY1+(i*textureSaltoY),0));
      textures.push_back(Ponto(textureX1+(j*textureSaltoX),(textureY1+textureSaltoY)+(i*textureSaltoY),0));

      printCoords(file, pontos, normalV, textures);
      pontos.clear(); normalV.clear(); textures.clear();
    }
  }
  fclose(file);
}

void create_sphere(double raio, int camadasV, int camadasH, char* filename){

  FILE *file = fopen(filename, "w");
  int i, j;
  float actX, actZ, nexX, nexZ, cimaActX, cimaActZ, cimaNexX, cimaNexZ;
  float passoH = (2*M_PI)/camadasV; // deslocamento na horizontal (angulo)
  float passoV = M_PI/camadasH; // deslocamento na vertical (angulo)
  float altura = raio * sin((M_PI/2) - passoV); // altura das camadas horizontais 
  float alturaCima = raio;
  vector<Ponto> pontos;
  vector<Ponto> normalV;
  vector<Ponto> textures;

  for (i = 0; i < camadasV; i++) {
    //fatia a fatia

    //Ponto actual (coord X e Z)
    float actualX = raio * sin(i*passoH);
    float actualZ = raio * cos(i*passoH);

    //Ponto seguinte (coord X e Z)
    float nextX = raio * sin((i+1)*passoH);
    float nextZ = raio * cos((i+1)*passoH);

    for (j = 1; j < camadasH + 2; j++){
      // o processo é feito percorrendo a cmdv de cima para baixo

      // Pontos inferiores do triangulo
      float aux = cos(asin(altura/raio));
      actX = actualX * aux;
      actZ = actualZ * aux;
      nexX = nextX * aux;
      nexZ = nextZ * aux;

      

      //Pontos superiores do triangulo
      float aux2 = cos(asin(alturaCima/raio));
      cimaActX = actualX * aux2;
      cimaActZ = actualZ * aux2;
      cimaNexX = nextX * aux2;
      cimaNexZ = nextZ * aux2;

      pontos.push_back(Ponto(actX,altura,actZ));
      pontos.push_back(Ponto(nexX,altura,nexZ));
      pontos.push_back(Ponto(cimaActX,alturaCima,cimaActZ));
      normalV.push_back(Ponto(sin(i*passoH),altura/raio,cos(i*passoH)));
      normalV.push_back(Ponto(sin((i+1)*passoH),altura/raio,cos((i+1)*passoH)));
      normalV.push_back(Ponto(sin(i*passoH),alturaCima/raio,cos(i*passoH)));

      pontos.push_back(Ponto(cimaActX,alturaCima,cimaActZ));
      pontos.push_back(Ponto(nexX,altura,nexZ));
      pontos.push_back(Ponto(cimaNexX,alturaCima,cimaNexZ));
      normalV.push_back(Ponto(sin(i*passoH),alturaCima/raio,cos(i*passoH)));
      normalV.push_back(Ponto(sin((i+1)*passoH),altura/raio,cos((i+1)*passoH)));
      normalV.push_back(Ponto(sin((i+1)*passoH),alturaCima/raio,cos((i+1)*passoH)));

      //Passa o valor de altura para alturaCima, e actualiza o valor de altura, para desenhar os triangulos abaixo.
      alturaCima = altura;
      altura = raio * sin((M_PI/2) - (passoV*j));
    }
    //Repoes as alturas iniciais iniciais     
    altura = raio * sin((M_PI/2) - passoV);
    alturaCima = raio;
  }

  for(int i = 0; i < pontos.size(); i+=3){
    float x,y,x2,y2,x3,y3;

    x = (-atan2(-pontos[i].getX(),pontos[i].getZ())+ M_PI) /  (2*M_PI);
    y = 1-(((-(pontos[i].getY()/raio))+1)/2.0);
    
    x2 = (-atan2(-pontos[i+1].getX(),pontos[i+1].getZ())+ M_PI) /  (2*M_PI);
    y2 = 1-(((-(pontos[i+1].getY()/raio))+1)/2.0);

    x3 = (-atan2(-pontos[i+2].getX(),pontos[i+2].getZ())+ M_PI) /  (2*M_PI);
    y3 = 1-(((-(pontos[i+2].getY()/raio))+1)/2.0);

    if(x > x2 && fabs(x - x2) > 0.8)
          x2 = 1.0;
        if(x > x3 && fabs(x - x3) > 0.8)
          x3 = 1.0;
        if (x2 > x && fabs(x2 - x) > 0.8)
          x = 1.0;
        if (x2 > x3 && fabs(x2 - x3) > 0.8)
          x3 = 1.0;
        if (x3 > x && fabs(x3 - x) > 0.8)
          x = 1.0;
        if (x3 > x2 && fabs(x3 - x2) > 0.8)
          x2 = 1.0;

    textures.push_back(Ponto(x,y,0));
    textures.push_back(Ponto(x2,y2,0));
    textures.push_back(Ponto(x3,y3,0));
  }

  for(i = 0; i < pontos.size(); i++){
    fprintf(file, "%f %f %f %f %f %f %f %f %f\n", 
            pontos[i].getX(), pontos[i].getY(), pontos[i].getZ(), 
            normalV[i].getX(), normalV[i].getY(), normalV[i].getZ(), 
            textures[i].getX(), textures[i].getY(), textures[i].getZ());
  }

  fclose(file);
}

void create_Cone(float raio, float altura, int cmdv, int cmdh, char* filename){

  FILE* file = fopen(filename, "w");

  vector<Ponto> pontos;
  vector<Ponto> normalV;
  vector<Ponto> textures;

  float alfa,x,z;
  float h = altura;
  float l = sqrt(pow(h,2) + pow(raio,2))/cmdh;
  float t = raio/cmdh;
  float dimLado = (2*M_PI)/cmdv;

  for (int i = 0; i < cmdh; i++) {   
    for (int j = 0; j < cmdv; j++) {
      alfa = j * dimLado;
      if (i == 0){
        // desenhar a base
        pontos.push_back(Ponto(0,0,0));
        normalV.push_back(Ponto(0,-1,0));

        x = raio * sin(alfa + dimLado);
        z = raio * cos(alfa + dimLado);
        pontos.push_back(Ponto(x,0,z));
        normalV.push_back(Ponto(0,-1,0));

        x = raio * sin(alfa);
        z = raio * cos(alfa);
        pontos.push_back(Ponto(x,0,z));
        normalV.push_back(Ponto(0,-1,0));

      }
      if (i < cmdh - 1) {
        // desenhar 2 triangulos para um lado (cmdv)
        x = (raio - ((i+1)*t)) * sin(alfa + dimLado);
        z = (raio - ((i+1)*t)) * cos(alfa + dimLado);
        pontos.push_back(Ponto(x,(i+1)*l,z));
        normalV.push_back(Ponto(sin(alfa + dimLado),l,cos(alfa + dimLado)));
        
        x = (raio - ((i+1)*t)) * sin(alfa);
        z = (raio - ((i+1)*t)) * cos(alfa);
        pontos.push_back(Ponto(x,(i+1)*l,z));
        normalV.push_back(Ponto(sin(alfa),l,cos(alfa)));
        
        x = (raio - (i*t)) * sin(alfa);
        z = (raio - (i*t)) * cos(alfa);
        pontos.push_back(Ponto(x,i*l,z));
        normalV.push_back(Ponto(sin(alfa),l,cos(alfa)));

        pontos.push_back(Ponto(x,i*l,z));
        normalV.push_back(Ponto(sin(alfa),l,cos(alfa)));
        
        x = (raio - (i*t)) * sin(alfa + dimLado);
        z = (raio - (i*t)) * cos(alfa + dimLado);
        pontos.push_back(Ponto(x,i*l,z));
        normalV.push_back(Ponto(sin(alfa + dimLado),l,cos(alfa + dimLado)));
        
        x = (raio - ((i+1)*t)) * sin(alfa + dimLado);
        z = (raio - ((i+1)*t)) * cos(alfa + dimLado);
        pontos.push_back(Ponto(x,(i+1)*l,z));
        normalV.push_back(Ponto(sin(alfa + dimLado),l,cos(alfa + dimLado)));

      }
      else {
        // desenhar o topo do cone
        x = (raio - (i*t)) * sin(alfa);
        z = (raio - (i*t)) * cos(alfa);
        pontos.push_back(Ponto(x,i*l,z));
        normalV.push_back(Ponto(0,-1,0));

        x = (raio - (i*t)) * sin(alfa + dimLado);
        z = (raio - (i*t)) * cos(alfa + dimLado);
        pontos.push_back(Ponto(x,i*l,z));
        normalV.push_back(Ponto(0,-1,0));

        pontos.push_back(Ponto(0,(i+1)*l,0));
        normalV.push_back(Ponto(0,-1,0));

      }
    }
  }
  fclose(file);
}

void createTorus(float raioIn, float raioOut, int lados, int aneis, char* filename){

  FILE* file = fopen(filename, "w");

  vector<Ponto> pontos;
  vector<Ponto> normalV;
  vector<Ponto> textures;

  float dimLado = (2*M_PI)/lados;
  float dimAnel = (2*M_PI)/aneis;

  float textureLado = float(1)/float(lados);
  float textureAnel = float(1)/float(aneis);

  for (int i = 0; i < aneis; i++) {   
    double a0 = i*dimAnel;
    double a1 = a0 + dimAnel;

    float x0 = cos(a0);
    float y0 = sin(a0);
    float x1 = cos(a1);
    float y1 = sin(a1);

    for (int j = 0; j < lados+1; j++){

      //current
      float c = cos(j*dimLado);
      float r = raioIn * c + raioOut;
      float z = raioIn * sin(j*dimLado);
      
      //next
      float nc = cos((j+1)*dimLado);
      float nr = raioIn * nc + raioOut;
      float nz = raioIn * sin((j+1)*dimLado);

      pontos.push_back(Ponto(x0*r,y0*r,z));
      pontos.push_back(Ponto(x1*r,y1*r,z));
      pontos.push_back(Ponto(x0*nr,y0*nr,nz));
      normalV.push_back(Ponto(0, 0, sin(j*dimLado)));
      normalV.push_back(Ponto(0, 0, sin(j*dimLado)));
      normalV.push_back(Ponto(0, 0, sin((j+1)*dimLado)));
      textures.push_back(Ponto(i*textureAnel,j*textureLado,0));
      textures.push_back(Ponto((i+1)*textureAnel,j*textureLado,0));
      textures.push_back(Ponto(i*textureAnel,(j+1)*textureLado,0));
      printCoords(file, pontos, normalV, textures);
      pontos.clear(); normalV.clear(); textures.clear();

      pontos.push_back(Ponto(x0*nr,y0*nr,nz));
      pontos.push_back(Ponto(x1*r,y1*r,z));
      pontos.push_back(Ponto(x1*nr,y1*nr,nz));
      normalV.push_back(Ponto(0, 0, sin((j+1)*dimLado)));
      normalV.push_back(Ponto(0, 0, sin(j*dimLado)));
      normalV.push_back(Ponto(0, 0, sin((j+1)*dimLado)));
      textures.push_back(Ponto(i*textureAnel,(j+1)*textureLado,0));
      textures.push_back(Ponto((i+1)*textureAnel,j*textureLado,0));
      textures.push_back(Ponto((i+1)*textureAnel,(j+1)*textureLado,0));  
      printCoords(file, pontos, normalV, textures);
      pontos.clear(); normalV.clear(); textures.clear();
    }
  }
    
  fclose(file);
}


void create_Cylinder(float raio, float altura, int cmdv, int cmdh, string filename){

  vector<Ponto> pontos;
  vector<Ponto> normalV;
  vector<Ponto> textures;

  float alfa,x,z;
  float h = altura;
  float l = sqrt(pow(h,2) + pow(raio,2))/cmdh;
  float t = raio/cmdh;
  float dimLado = (2*M_PI)/cmdv;
  float aux = float(0.625f)/float(cmdh);

  for (int i = 0; i < cmdh; i++) {   
    for (int j = 0; j < cmdv; j++) {
      alfa = j * dimLado;
      if (i == 0){
        //base
        pontos.push_back(Ponto(0,0,0));
        normalV.push_back(Ponto(0,-1,0));
        textures.push_back(Ponto(0.8125,0.1875,0));
        
        x = raio * sin(alfa + dimLado);
        z = raio * cos(alfa + dimLado);
        pontos.push_back(Ponto(x,0,z));
        normalV.push_back(Ponto(0,-1,0));
        textures.push_back(Ponto( 0.8125 + 0.1875 * sin(alfa + dimLado),0.1875 + 0.1875 * cos(alfa + dimLado),0));
        
        x = raio * sin(alfa);
        z = raio * cos(alfa);
        pontos.push_back(Ponto(x,0,z));
        normalV.push_back(Ponto(0,-1,0));
        textures.push_back(Ponto( 0.8125 + 0.1875 * sin(alfa),0.1875 + 0.1875 * cos(alfa),0));
        
        
      }
      if (i < cmdh - 1) {
        // desenhar 2 triangulos para um lado (cmdv)
        x = raio * sin(alfa + dimLado);
        z = raio * cos(alfa + dimLado);
        pontos.push_back(Ponto(x,(i+1)*l,z));
        normalV.push_back(Ponto( sin(alfa + dimLado), 0, cos(alfa + dimLado)));
        textures.push_back(Ponto(float(j+1)/float(cmdv),(float(i+1)*aux)+0.375f,0));

        x = raio  * sin(alfa);
        z = raio  * cos(alfa);
        pontos.push_back(Ponto(x,(i+1)*l,z));
        pontos.push_back(Ponto(x,i*l,z));
        normalV.push_back(Ponto( sin(alfa), 0, cos(alfa)));
        normalV.push_back(Ponto( sin(alfa), 0, cos(alfa)));
        textures.push_back(Ponto(float(j)/float(cmdv),(float(i+1)*aux)+0.375f,0));
        textures.push_back(Ponto(float(j)/float(cmdv),(float(i)*aux)+0.375f,0));
        
        pontos.push_back(Ponto(x,i*l,z));
        normalV.push_back(Ponto( sin(alfa), 0, cos(alfa)));
        textures.push_back(Ponto(float(j)/float(cmdv),(float(i)*aux)+0.375f,0));

        x = raio * sin(alfa + dimLado);
        z = raio * cos(alfa + dimLado);
        pontos.push_back(Ponto(x,i*l,z));
        pontos.push_back(Ponto(x,(i+1)*l,z));
        normalV.push_back(Ponto( sin(alfa + dimLado), 0, cos(alfa + dimLado)));
        normalV.push_back(Ponto( sin(alfa + dimLado), 0, cos(alfa + dimLado)));
        textures.push_back(Ponto(float(j+1)/float(cmdv),(float(i)*aux)+0.375f,0));
        textures.push_back(Ponto(float(j+1)/float(cmdv),(float(i+1)*aux)+0.375f,0));

      }
      else {
        //top
        x = raio * sin(alfa);
        z = raio * cos(alfa);
        pontos.push_back(Ponto(x,i*l,z));
        normalV.push_back(Ponto(0,1,0));
        textures.push_back(Ponto( 0.4375 + 0.1875 * sin(alfa),0.1875 + 0.1875 * cos(alfa),0));
        
        
        x = raio * sin(alfa + dimLado);
        z = raio * cos(alfa + dimLado);
        pontos.push_back(Ponto(x,i*l,z));
        pontos.push_back(Ponto(0,i*l,0));
        normalV.push_back(Ponto(0,1,0));
        normalV.push_back(Ponto(0,1,0));
        textures.push_back(Ponto( 0.4375 + 0.1875 * sin(alfa + dimLado),0.1875 + 0.1875 * cos(alfa + dimLado),0));
        textures.push_back(Ponto( 0.4375, 0.1875, 0));
        
      }
    }
  }
  fclose(file);
}



void readPatchFile(string patchFile){

  int i, j, indice, nrPatches, hop, nrPoints;
  float point[3], n, coord;
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
          
          coord = stof(currCoord);
          cout << currCoord << "->" << coord << endl;
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

      // escrever pontos no ficheiro
      file << p0.getX() << " " << p0.getY() << " " << p0.getZ() << endl;
      file << p2.getX() << " " << p2.getY() << " " << p2.getZ() << endl;
      file << p3.getX() << " " << p3.getY() << " " << p3.getZ() << endl;

      file << p0.getX() << " " << p0.getY() << " " << p0.getZ() << endl;
      file << p3.getX() << " " << p3.getY() << " " << p3.getZ() << endl;
      file << p1.getX() << " " << p1.getY() << " " << p1.getZ() << endl;

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

 else if(strcmp(argv[1], "torus") == 0 && argc == 6)
      create_cone(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
      
 else if(strcmp(argv[1], "cylinder") == 0 && argc == 7)
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


