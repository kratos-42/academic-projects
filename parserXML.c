#include "parserXML.h"

void load_scene(char* filename);

char** read3DFiles(char* filename) {

    xmlDocPtr doc;  
    xmlNodePtr node;
    xmlChar *modelFile;
    xmlAttrPtr attr;

    int n = 0;
    char** filenames;

    // TODO: DTD
    doc = xmlParseFile(filename);
    if (doc == NULL ) {
        fprintf(stderr,"Error!\n");
        return NULL;
    }

    // Get scene node
    node = xmlDocGetRootElement(doc);
    if (node == NULL) {
        fprintf(stderr,"Document is Empty\n");
        xmlFreeDoc(doc);
        return NULL;
    }
    
    filenames = malloc(sizeof(char*) * 1024); 

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

    return filenames;
} 
