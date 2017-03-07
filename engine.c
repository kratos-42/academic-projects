#ifdef __APPLE__q
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>


char* filenames[10];

//read xml file.
void read3DFiles(char* filename) {

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

    /*free the document */
    xmlFreeDoc(doc);
    xmlCleanupParser();

    filenames[n] = NULL;

}



float xx = 0;
float yy = 0;
float zz = 0;
float angle = 0;

char* xmlfile = "models.xml";



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



void draw(char* filename){


	float x, y, z;
	FILE *f;

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


void renderScene(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glLoadIdentity();
	gluLookAt(0.0f, 5.0f, 30.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f);

	glRotatef(angle, 0, 1, 0);
	glTranslatef(xx, yy, zz);


	for(int i = 0; filenames[i] != NULL; i++){
		draw(filenames[i]);	
	}
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

int main(int argc, char **argv){

	float x, y, z;
	x = y = z = 0;

	read3DFiles(xmlfile);

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

	//opemGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//enter Glut's main cycle
	glutMainLoop();		
	return 1;

}
