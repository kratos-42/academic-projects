#include "engine.h"

char* filenames[10];

Group ggroup;

void draw_group(Group g){
    glPushMatrix();
    glRotatef(g.getRotacao().getAngulo(), g.getRotacao().getX(), g.getRotacao().getY(), g.getRotacao().getZ());
    glTranslatef(g.getTranslacao().getX(), g.getTranslacao().getY(), g.getTranslacao().getZ());
    glScalef(g.getEscala().getX(), g.getEscala().getY(), g.getEscala().getZ());

    glBegin(GL_TRIANGLES);
    for(Model it: g.getModels()){
    	auto v = it.getPontos();
		for(int i = 0; i < v.size(); i +=3){
	        	//printf("%s\n", "cria vertices");
	            glVertex3f(v[i], v[i + 1], v[i + 2]);
	            
	        }
       
    }
    glEnd();
    for(auto it: g.getGroups()){
        draw_group(it);
    }

    glPopMatrix();
}

//read xml file.
/*void read3DFiles(char* filename) {

    xmlDocPtr doc;
    xmlNodePtr node;
    xmlChar *modelFile;
    xmlAttrPtr attr;

    int n = 0;

    // TODO: DTD
    doc = xmlParseFile(filename);
    if (doc == NULL ) {
        fprintf(stderr,"Error!\n");
        return;
    }

    // Get scene node
    node = xmlDocGetRootElement(doc);
    if (node == NULL) {
        fprintf(stderr,"Document is Empty\n");
        xmlFreeDoc(doc);
        return;
    }

    

    node = node->xmlChildrenNode;
    while (node != NULL) {

        attr = xmlHasProp(node, (const xmlChar*)"file");
        if (attr != NULL){
            modelFile = xmlGetProp(node, (const xmlChar*)"file");
            filenames[n++] = strdup((char*) modelFile);
            xmlFree(modelFile);
        }

        node = node->next;
    }

    /*free the document 
    xmlFreeDoc(doc);
    xmlCleanupParser();

    filenames[n] = NULL;

}
*/


string xmlfile = "models.xml";
float xx = 0;
float yy = 0;
float zz = 0;
float angle = 0;
//char* xmlfile = "models.xml";



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


/*
void draw(string filename){


	float x, y, z;
	FILE* f;

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
*/
void parseGroup(XMLElement* grupo, Group& gr){

	Translacao tr;
	Rotacao rot;
	Escala escala;
	float angle1, 
		  rotX, rotY, rotZ, 
    	  transX, transY, transZ, 
    	  escX, escY, escZ;

   	vector<Group> vGroups;


   	angle1 = rotX = rotY = transX = transY = transZ = escX = escY = escZ = 1;

   	
   	int i = 0;

    /*XMLElement* transform = grupo -> FirstChildElement("models");
    cout << transform -> Value() << endl;
    XMLElement* transf2 = transform -> FirstChildElement("model");
   

   	for(transform = transform -> FirstChildElement("model"); transform; transform = transform -> NextSiblingElement()){
   		gr.addModel(transform -> Attribute("file"));
   	}
	*/
  	XMLElement* transform;

   		
   	for(transform = grupo -> FirstChildElement(); transform; transform = transform -> NextSiblingElement()){

		//cout << transform -> Value() << endl;
   		
   		if(strcmp(transform -> Value(), "translate") == 0){
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

   		if (strcmp(transform -> Value(), "rotate") == 0){
				if (transform -> Attribute("angle")) 
					angle1 = stof(transform -> Attribute("angle"));
					else angle1 = 0;
				
				if (transform -> Attribute("X")) 
					rotX = stof(transform -> Attribute("X"));
					else rotX = 0;
				
				if (transform -> Attribute("Y")) 
					rotY = stof(transform -> Attribute("Y"));
					else rotY = 0;
				
				if (transform -> Attribute("Z")) 
					rotZ = stof(transform -> Attribute("Z"));
					else rotZ = 0;

				rot = Rotacao(angle1, rotX, rotY, rotZ);
				gr.setRotacao(rot);
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
				gr.addModel(transform2 -> Attribute("file"));	
				transform2 = transform2 -> NextSiblingElement();	
			}

			/*for(transform2 = transform -> FirstChildElement(); transform2; transform2 = transform2 -> NextSiblingElement()){	
   				//gr.addModel(transform2 -> Attribute("file"));
   				cout << transform -> Attribute("file") << endl;
   			
			}*/

		}
		

		if(strcmp(transform -> Value(), "group") == 0){
			Group g;
			parseGroup(transform, g);
			gr.addGroup(g);
		}
	}
}

void readXMLFile(string file){

	XMLDocument doc;
	doc.LoadFile(file.c_str());

	XMLElement* scene = doc.FirstChildElement("scene");
	
	
	XMLElement* group = scene -> FirstChildElement("group");
	

	//XMLElement* model = group -> FirstChildElement("models");
	//cout << model -> Attribute("X") << endl;
	//XMLElement* smodel = model -> FirstChildElement("model");
	//cout << smodel -> Attribute("file") << endl;

	parseGroup(group, ggroup);


}




void renderScene(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glLoadIdentity();
	gluLookAt(0.0f, 3.0f, 30.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f);

	glRotatef(angle, 0, 1, 0);
	glTranslatef(xx, yy, zz);

	
    draw_group(ggroup);
	//for(int i = 0; filenames[i] != NULL; i++){
	//	draw(filenames[i]);	
	//}
	glutSwapBuffers();
}

void keyFunc(unsigned char key, int x, int y){
	int speed = 10;

	switch(key){

		case 'a' :
			xx -= 0.1*speed;
			break;
		case 'w' :
			yy -=0.1*speed;
			break;
		case 's' : 
			yy += 0.1*speed;
			break;
		case 'd' :
			xx += 0.1*speed;
			break;
		case 'e' :
			angle += 10*speed;
			break;
		case 'q' :
			angle -= 10*speed;
			break;

		default:
			break;


	}
	glutPostRedisplay();

}

void specialKeyFunc(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			zz -= 0.1;
			break;
		case GLUT_KEY_DOWN:
			zz += 0.1;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}


int main(int argc, char **argv){

	float x, y, z;
	x = y = z = 0;

	if(argc =! 2){
		return 0;
	}

	string xmlfile = argv[1];
	readXMLFile(xmlfile);
	//ggroup.print();
	
	/* readXMLFile(argv[1]); */
	//init GLUT and the Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@PROJETO");

	//register the functions that will process the events(callbacks)
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize); 


	glutKeyboardFunc(keyFunc);	
	glutSpecialFunc(specialKeyFunc);

	//opemGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//enter Glut's main cycle
	glutMainLoop();		
	return 1;

}
