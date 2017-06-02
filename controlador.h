#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"
#include "utils.h"

#define MAX_SIZE 1024

struct node{
	int id;
	char** cmd;
	int nrConnections;
	int pd[2];
	int running;
	int connected_nodes[100];
	UT_hash_handle hh;
};

struct node* rede = NULL;

