#define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux. See feature_test_macros(7) */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

typedef struct avl_node_produtos {
	
	avl_node_produtos *esq;
	avl_node_produtos *dir;
	char codigo;
	int height;

}*avl_node_p;


typedef struct avl_tree_produtos {
	
	avl_tree_produtos *raiz;

}*avl_tree_p;

avl_node_p new_node(char codigo, )

/* Create a new AVL tree. */
avl_tree_p *avl_create_tree() {
	avl_tree_p *tree = NULL;

	if ((tree = malloc(sizeof(avl_tree_p))) == NULL) {
		return NULL;
	}

	tree -> root = NULL;

	return tree;
}

/* Initialize a new node. */
avl_node_p *avl_create_node() {
	avl_node_p *node = NULL;
	
	if((node = malloc(sizeof(avl_node_p))) == NULL) {
		return NULL;
	}

	node -> esq = NULL;
	node -> dir = NULL;
	node -> value = 0;

	return node;	
}

/*calcular a altura de um dado nodo */
int avl_node_altura(avl_node_p *node) {

	int altura_esq = 0;
	int altura_dir = 0;

	if(node -> esq) altura_esq = avl_node_altura(node -> esq );
	if(node -> dir) altura_dir = avl_node_altura(node -> dir);

	return altura_dir > altura_esq ? ++altura_dir : ++altura_esq;
}

/*fazer um balanço de alturas entre as subarvores que sucedem um dado nodo*/
int avl_balance_factor(avl_node_p *node) {

	int bf = 0;

	if (node -> esq) bf += avl_node_height(node -> esq);
	if (node -> dir) bf -= avl_node_height(node -> dir);

	return bf ;
}

avl_node_p *avl_rotate_esqEsq(avl_node_p *node) {
 	
 	avl_node_p *a = node;
	avl_node_p *b = a -> esq;
	
	a -> esq = b -> dir;
	b -> dir = a;

	return(b);
}


avl_node_p *avl_rotate_esqDir(avl_node_p *node) {

	avl_node_p *a = node;
	avl_node_p *b = a -> esq;
	avl_node_p *c = b -> dir;
	
	a -> esq = c -> dir;
	b -> dir = c -> esq; 
	c -> esq = b;
	c -> dir = a;

	return(c);
}

/* dir esq Rotate */
avl_node_p *avl_rotate_dirEsq(avl_node_p *node) {
	
	avl_node_p *a = node;
	avl_node_p *b = a -> dir;
	avl_node_p *c = b -> esq;
	
	a -> dir = c -> esq;
	b -> esq = c -> dir; 
	c -> dir = b;
	c -> esq = a;

	return(c);
}

/* dir dir Rotate */
avl_node_p *avl_rotate_dirDir(avl_node_p *node) {

	avl_node_p *a = node;
	avl_node_p *b = a -> dir;
	
	a -> dir = b -> esq;
	b -> esq = a; 

	return(b);
}

/*balancear um nodo dá AVL*/
avl_node_t *avl_balance_node(avl_node_t *node) {

	avl_node_t *novaRaiz = NULL;
	int bf;

	if (node -> esq)
		node -> esq = avl_balance_node(node -> esq);
	
	if (node -> dir) 
		node -> dir = avl_balance_node(node -> dir);

	bf = avl_balance_factor(node);

	if (bf >= 2) {
		/*  */	

		if (avl_balance_factor(node -> esq) <= -1 ) 
			novaRaiz = avl_rotate_leftright( node );
		else 
			novaRaiz = avl_rotate_leftleft( node );

	} 

	else if( bf <= -2 ) {
		
		if( avl_balance_factor(node -> dir) >= 1 )
			novaRaiz = avl_rotate_rightleft(node);
		
		else 
			novaRaiz = avl_rotate_rightright(node);

	} 

	else {
		/*nodo já está balanceado*/
		novaRaiz = node;
	}

	return(novaRaiz);	
}


// recalcular a altura de um dado nodo/produto

void nova_altura(avl_node_p *produto) {

    produto -> altura = 1 + max(altura(produto -> esq), altura(produto -> dir));
}

//rodar à direita




/* Balancear uma árvore*/
void avl_balance_tree(avl_tree_p *tree) {

	avl_node_p *novaRaiz = NULL;

	novaRaiz = avl_balance_node(tree -> raiz);

	if (novaRaiz != tree -> raiz) {
		tree -> raiz = novaRaiz; 
	}
}

/* Insert a new node. */
void avl_insert(avl_tree_p *tree, char codigo) {

	avl_node_p *node = NULL;
	avl_node_p *next = NULL;
	avl_node_p *last = NULL;

	/* Well, there must be a first case */ 	
	if (tree -> raiz == NULL ) {
		node = avl_create_node();
		node -> codigo = codigo;

		tree -> raiz = node;

	/* Okay.  We have a  raiz already.  Where do we put this? */
	} else {
		next = tree-> raiz;

		while( next != NULL ) {
			last = next;

			if( value < next->value ) {
				next = next->esq;
dir
			} else if( value > next->value ) {
				next = next->dir;

			/* Have we already inserted this node? */
			} else if( value == next->value ) {
				/* This shouldn't happen. */	
			}
		}

		node = avl_create_node();
		node->value = value;

		if( value < last->value ) last->esq = node;
		if( value > last->value ) last->dir = node;
		
	}

	avl_balance( tree );
}

/* Find the node containing a given value */
avl_node_p *avl_find( avl_tree_p *tree, int value ) {
	avl_node_p *current = tree-> raiz;

	while( current && current->value != value ) {
		if( value > current->value )
			current = current->dir;
		else
			current = current->esq;
	dir
	return current;
}

/* Do a depth first traverse of a node. */
void avl_traverse_node_dfs( avl_node_p *node, int depth ) {
	int i = 0;

	if( node->esq ) avl_traverse_node_dfs( node->esq, depth + 2 );
dir
	for( i = 0; i < depth; i++ ) putchar( ' ' );
	printf( "%d: %d\n", node->value, avl_balance_factor( node ) );

	if( node->dir ) avl_traverse_node_dfs( node->dir, depth + 2 );
}

/* Do a depth first traverse of a tree. */
void avl_traverse_dfs( avl_tree_p *tree ) {
	avl_traverse_node_dfs( tree->root, 0 );
}

int main( int argc, char **argv ) {
	avl_tree_p *tree = NULL;
	int i = 0; 
	int r = 0;


	tree = avl_create();

	/* Insert 1-20 in random order -- this is suboptimal, but easy */
	srand( time( NULL ) );

	for( i = 0; i < 20; i++ ) {
		do {
			r = rand() % 20 + 1;
		} while( avl_find( tree, r ) );

		avl_insert( tree, r );
	}

	avl_traverse_dfs( tree );

	return 0;
}


