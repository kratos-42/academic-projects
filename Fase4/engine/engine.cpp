#include "engine.h"

char* filenames[10];

Group ggroup;






float refX = 0;
float refY = 0;
float refZ = 0;
float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;
float camX = 0, camY = 20, camZ = 70;
int imageWidth;
unsigned char *imageData;
unsigned int texture;
vector<float> position;



// MOUSE //
int startX, startY, tracking = 0;
int alpha = 0, beta = 0;
int r = 50;


// FRAMES //

int timebase = 0, frame = 0;

// VBOs //


float nVertexComponents;




void changeSize(int w, int h){

	//h can't be ZERO
	if(h==0) h=1;

	float ratio = w * 1.0f / h;

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
}

void renderCatmullRomCurve(float* res, float* der, Translacao tr) {

	float gt = 0.0f;
	glBegin(GL_LINE_LOOP);
	
	while(gt < 1.0f){
		vector<Ponto> ts = tr.getTransPoints();
		tr.getGlobalCatmullRomPoint(gt, tr.getTransPoints(), res, der);
		glVertex3f(res[0], res[1], res[2]);
		

		gt += 0.0001f;
	}
	glEnd();

}


// Desenhar um grupo de modelos

void draw_group(Group g){

	float gt;

    glPushMatrix();
    // Escala
    glScalef(g.getEscala().getX(), g.getEscala().getY(), g.getEscala().getZ());

    //Rotacao com tempo
    if(g.getRotacao().getTime() != 0){ 
    	Rotacao r = g.getRotacao();
    	float ang = fmod((glutGet(GLUT_ELAPSED_TIME)*360.0f ) / (r.getTime()*1000.0f), 360.0f);
    	glRotatef(ang, r.getX(), r.getY(), r.getZ());
    	r.setAngulo(ang);
    }
    //Rotacao normal
    else
		glRotatef(g.getRotacao().getAngulo(), g.getRotacao().getX(), g.getRotacao().getY(), g.getRotacao().getZ());
    
    //Translacao numa curva
    if(g.getTranslacao().getTime() != 0){
    	float der[3];
		float res[3];
  		Translacao tr = g.getTranslacao();
		renderCatmullRomCurve(res, der, tr);
  		

		gt = fmod(glutGet(GLUT_ELAPSED_TIME) / (tr.getTime()*1000.0f), 1);
    	tr.updateGt(gt);
		vector<Ponto> vp = tr.getTransPoints();
		tr.getGlobalCatmullRomPoint(tr.getGt(), vp, res, der);
		glTranslatef(res[0], res[1], res[2]);
		
    }
    //Rotacao normal
    else{
    	glTranslatef(g.getTranslacao().getX(), g.getTranslacao().getY(), g.getTranslacao().getZ());
	}
	


    //Desenhar modelos existentes c/ VBOs

	   	for(Model it: g.getModels()){
	    	auto v = it.getPontos();
	    
		    if(it.getTexture() != NULL){
		    	unsigned int t, tw, th;
		    	unsigned char* texData;
				ilGenImages(1, &t);
				ilBindImage(t);
				ilLoadImage((ILstring)it.getTexture());
				tw = ilGetInteger(IL_IMAGE_WIDTH);
				th = ilGetInteger(IL_IMAGE_HEIGHT);
				ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
				it.setTexData(ilGetData());

				glBindTexture(GL_TEXTURE_2D, it.getTexID());
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
				glGenerateMipmap(GL_TEXTURE_2D);
		    }

		    nVertexComponents = v.size();
		    
		    glBindBuffer(GL_ARRAY_BUFFER, it.getPontosBuffer());
		    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nVertexComponents, &v[0], GL_STATIC_DRAW);  
		    glVertexPointer(3, GL_FLOAT, 0, 0);
		    glDrawArrays(GL_TRIANGLES, 0, nVertexComponents);

		    glBindTexture(GL_TEXTURE_2D, 0);

    }

    for(auto it: g.getGroups()){
    	cout << it.getGroups().size() << endl;
        draw_group(it);
		
    }

    glPopMatrix();
}





void parseGroup(XMLElement* grupo, Group& gr){

	Translacao tr;
	Rotacao rot;
	Escala escala;
	float angle1, 
		  rotX, rotY, rotZ, 
    	  transX, transY, transZ, 
    	  escX, escY, escZ;

   	vector<Group> vGroups;
   	float time;

   	angle1 = rotX = rotY = transX = transY = transZ = escX = escY = escZ = 1;


  	XMLElement* transform;

   		
   	for(transform = grupo -> FirstChildElement(); transform; transform = transform -> NextSiblingElement()){

		
   		
   		if(strcmp(transform -> Value(), "translate") == 0){

   			if(transform -> Attribute("time")){
   				time = stof(transform->Attribute("time"));
   				vector<Ponto> trPoints;
   				int j;
   				
   				for(XMLElement* point = transform->FirstChildElement("point"); point; point = point->NextSiblingElement("point")){
   					if(point->Attribute("X"))
   						transX = stof(point->Attribute("X"));
   						else transX = 0;
   					if(point->Attribute("Y"))
   						transY = stof(point->Attribute("Y"));	
   						else transY = 0;
					if (point->Attribute("Z")) 
						transZ = stof(point->Attribute("Z"));
						else transZ = 0;

					Ponto p = Ponto(transX, transY, transZ);
					trPoints.push_back(p);
				}

				tr = Translacao(time, trPoints, trPoints.size(), 0);	
				gr.setTranslacao(tr);
   			}

	   		else{
		   		if(transform -> Attribute("X")) 
		   			transX = stof(transform->Attribute("X"));
					else transX = 0;

				if (transform->Attribute("Y")) 
					transY = stof(transform->Attribute("Y"));
					else transY = 0;
				
				if (transform->Attribute("Z")) 
					transZ = stof(transform->Attribute("Z"));
					else transZ = 0;

				tr = Translacao(transX, transY, transZ);
				gr.setTranslacao(tr);
				
	   		}
   	}

   		if (strcmp(transform -> Value(), "rotate") == 0){
				
				if(transform -> Attribute("time")){
					time = stof(transform -> Attribute("time"));

					if (transform -> Attribute("axisX")){
						rotX = stof(transform -> Attribute("axisX"));
					}
						else rotX = 0;
					
					if (transform -> Attribute("axisY")) 
						rotY = stof(transform -> Attribute("axisY"));
						else rotY = 0;
					
					if (transform -> Attribute("axisZ")) 
						rotZ = stof(transform -> Attribute("axisZ"));
						else rotZ = 0;


					rot = Rotacao(0, rotX, rotY, rotZ);
					rot.setTime(time);
					gr.setRotacao(rot);
				}


				else{
					if (transform -> Attribute("angle")) 
						angle1 = stof(transform -> Attribute("angle"));
						else angle1 = 0;
					
					if (transform -> Attribute("axisX")) 
						rotX = stof(transform -> Attribute("axisX"));
						else rotX = 0;
					
					if (transform -> Attribute("axisY")) 
						rotY = stof(transform -> Attribute("axisY"));
						else rotY = 0;
					
					if (transform -> Attribute("axisZ")) 
						rotZ = stof(transform -> Attribute("axisZ"));
						else rotZ = 0;

					rot = Rotacao(angle1, rotX, rotY, rotZ);
					gr.setRotacao(rot);
				}
		}


		if (strcmp(transform -> Value(), "scale") == 0){
				if (transform->Attribute("X")) 
					escX = stof(transform -> Attribute("X"));
					else escX = 1;
				
				if (transform -> Attribute("Y")) 
					escY = stof(transform -> Attribute("Y"));
					else escY = 1;
				
				if (transform -> Attribute("Z")) 
					escZ = stof(transform -> Attribute("Z"));
					else escZ = 1;
				
				escala.setX(escX);
				escala.setY(escY);
				escala.setZ(escZ);
				gr.setEscala(escala);
		}


		if(strcmp(transform -> Value(), "models") == 0){
			XMLElement* transform2 = transform -> FirstChildElement();

			while(transform2 && strcmp(transform2 -> Value(), "model") == 0){
				Model m = Model(transform2 -> Attribute("file"));	
				GLuint buffer[3];
				m.loadModel();
				auto v = m.getPontos();
				auto n = m.getNormalV();
				auto t = m.getTextures();

				glGenBuffers(3, buffer); 

				glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
        		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nVertexComponents, &(v[0]), GL_STATIC_DRAW); 

        		glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n.size(), &(n[0]), GL_STATIC_DRAW);
				
				glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * t.size(), &(t[0]), GL_STATIC_DRAW);

				m.setArrayBuffers(buffer);


				if(transform2 -> Attribute("texture")){
					m.setTexture((char*)(transform2 -> Attribute("texture")));
					//cout << transform2 -> Attribute("texture") << endl;
				}

				else{
					if(transform2 -> Attribute("diffR"))
						m.setDiffR(stof(transform2 -> Attribute("diffR")));
						//cout << transform2 -> Attribute("diffR") << endl;
					
					if(transform2 -> Attribute("diffG"))
						m.setDiffG(stof(transform2 -> Attribute("diffG")));
						//cout << transform2 -> Attribute("diffR") << endl;

					if(transform2 -> Attribute("diffB"))
						m.setDiffB(stof(transform2 -> Attribute("diffB")));
						//cout << transform2 -> Attribute("diffR") << endl;
				}
				gr.addModel(m);
				transform2 = transform2 -> NextSiblingElement();	
			}
		}

		if(strcmp(transform -> Value(), "lights") == 0){
			XMLElement* transform2 = transform -> FirstChildElement();

			while(transform2 && strcmp(transform2 -> Value(), "light") == 0){
				Light l = Light();
				float posX = 0;
				float posY = 0;
				float posZ = 0;

				if(transform2 -> Attribute("posX"))
					posX = stof(transform2 -> Attribute("posX"));

				if(transform2 -> Attribute("posY"))
					posY = stof(transform2 -> Attribute("posY"));

				if(transform2 -> Attribute("posZ"))
					posZ = stof(transform2 -> Attribute("posZ"));
				
				Ponto p = Ponto(posX, posY, posZ);
				

				if(strcmp(transform2 -> Attribute("type"), "POINT"))
					l.setLpoint(p);
					else 
						l.setLvector(posX, posY, posZ);

				gr.addLight(l);
				transform2 = transform2 -> NextSiblingElement();
				}
		}


		if(strcmp(transform -> Value(), "group") == 0){
			Group g;
			parseGroup(transform, g);
			gr.addGroup(g);
		}
	}
}

void prepareModels(Model m){

        m.loadModel();
        vector<float> pontos = m.getPontos();
        
        int nVertexComponents = pontos.size();
		GLuint* gl = m.getArrayBuffers();        

        glGenBuffers(1, gl);  

        glBindBuffer(GL_ARRAY_BUFFER, gl[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nVertexComponents, &(pontos[0]), GL_STATIC_DRAW);  
}

void readXMLFile(string file){

	XMLDocument doc;
	doc.LoadFile(file.c_str());

	XMLElement* scene = doc.FirstChildElement("scene");
	
	
	XMLElement* group = scene -> FirstChildElement("group");
	
	parseGroup(group, ggroup);

}



void showFrames() {
	float fps;
	int time;
	char buffer[64];

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		fps = frame*1000.0 / (time - timebase);
		timebase = time;
		frame = 0;
		sprintf(buffer, "FPS: %f6.2", fps);
		glutSetWindowTitle(buffer);
	}
}



void renderScene(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f);


	glRotatef(angleX, 1, 0, 0);
	glRotatef(angleY, 0, 1, 0);
	glRotatef(angleZ, 0, 0, 1);
	glTranslatef(refX, refY, refZ);

    draw_group(ggroup);
	

    showFrames();
	glutSwapBuffers();
}


/*


********************************************************
*													   *
*		              Camera						   *	
*													   *
********************************************************



*/

void resetCamara() {
	angleX = angleY = angleZ = 0.0f;
	refX = refY = refZ = 0;
	alpha = 0.0f;
	beta = 0.5f;
}

void normalKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 'W':;
	case 'w': angleX += 5; break;
	case 'S':;
	case 's': angleX -= 5; break;
	case 'A':;
	case 'a': angleY += 5; break;
	case 'D':;
	case 'd': angleY -= 5; break;
	case 'q':;
	case 'Q': angleZ += 5; break;
	case 'e':;
	case 'E': angleZ -= 5; break;
	case 'R':;
	case 'r': resetCamara(); break;
	case '+': refZ += 5.0f; break;
	case '-': refZ -= 5.0f; break;
	}
	glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
	switch (key) {
		
		case GLUT_KEY_UP: refY += 5; break;
		
		case GLUT_KEY_DOWN: refY -= 5; break;
		
		case GLUT_KEY_LEFT: refX -= 5; break;
		
		case GLUT_KEY_RIGHT: refX += 5; break;
	}

	glutPostRedisplay();
}

// Funções de processamento do rato
void processMouseButtons(int button, int state, int xx, int yy) {

	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {

			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
	//glutPostRedisplay();
}

void processMouseMotion(int xx, int yy) {

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {

		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * sin(betaAux * 3.14 / 180.0);

	glutPostRedisplay();
}



void menu(int op)
{
	switch (op) {
		case 1: glPolygonMode(GL_FRONT, GL_FILL); break;
		case 2: glPolygonMode(GL_FRONT, GL_LINE); break;
		case 3: glPolygonMode(GL_FRONT, GL_POINT); break;
	}
	glutPostRedisplay();
}


void defineMenu() {
	glutCreateMenu(menu);

	glutAddMenuEntry("GL_FILL", 1);
	glutAddMenuEntry("GL_LINE", 2);
	glutAddMenuEntry("GL_POINT", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv){

	float x, y, z;
	x = y = z = 0;

	if(argc != 2){
		cout << "Usage:" << endl;
		cout << "./engine " << "file.xml" << endl;
		return 0; 
	}

	
	//createMenu();
	string xmlfile = argv[1];
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@PROJETO");

	glewInit();
	readXMLFile(xmlfile);
	

	
	//init GLUT and the Window

	//register the functions that will process the events(callbacks)
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize); 

	//  ****  KEYBOARD **** 
	glutKeyboardFunc(normalKeys);	
	glutSpecialFunc(specialKeys);

	// **** MOUSE MOTION ****

	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	

	defineMenu();
	

	//opemGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_VERTEX_ARRAY);

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	//init();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//enter Glut's main cycle
	glutMainLoop();		
	
	
	return 1;

}
