#ifndef CLIENTES_C
#define CLIENTES_C

#define _XOPEN_SOURCE 500

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

struct avl_node_clientes {
	
	struct avl_node_clientes *esq;
	struct avl_node_clientes *dir;
	char *codigo_cliente;
	int altura;

};

typedef struct avl_node_clientes avl_node_c;

struct avl_tree_clientes {
	
	struct avl_tree_clientes *raiz;

};

typedef struct avl_tree_clientes avl_tree_c;

#endif