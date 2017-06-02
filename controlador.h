#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "uthash.h"

#define MAX_SIZE 1024
#define MAX_NODES 100

struct node {
	int id;
	char** cmd;
	int nrConnections;
	int pd[2];
	int running;
	int connected_nodes[MAX_NODES];
	UT_hash_handle hh;
};

struct node* rede = NULL;

