#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <math.h>
#include <string.h>



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


  int main(int argc, char** argv){

  
  char* file = argv[2];

  if(strcmp((argv[1]), "plane") == 0 && argc == 7){
      create_plane(atof(argv[2]), atoi(argv[3]), atof(argv[4]), atoi(argv[5]), argv[6]);
  }
  
  else if(strcmp((argv[1]), "box") == 0 && argc == 9)
      create_box(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atoi(argv[6]), atoi(argv[7]), argv[8]);

  else if(strcmp(argv[1], "sphere") == 0 && argc == 6)
      create_sphere(atof(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);

  else if(strcmp(argv[1], "cone") == 0 && argc == 7)
      create_cone(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
    
  else{
    printf("The arguments are invalid. Try one of these:\n");
    printf("\nplane <comprimento> <largura> <nº camada horizontais> <nº camadas verticais>  <filename>\n");
    printf("\nbox <comprimento> <largura> <altura> <nº camadas horizontais> <nº camadas verticais> <nº camadas laterais> <filename>\n");
    printf("\nsphere <raio> <nº camadas horizontais> <nº camadas verticais> <filename>\n");
    printf("\ncone <raio> <altura> <nº camadas horizontais> <nº camadas verticais> <filename>\n");

  }  
  return 0;
}


