#include "client_process.h"

/* Create a new AVL tree. */
avl_tree_c *avl_create_tree() {
	avl_tree_c *tree = NULL;

	if ((tree = malloc(sizeof(avl_tree_c))) == NULL) {
		return NULL;
	}

	tree -> raiz = NULL;

	return tree;
}

/* Initialize a new node. */
avl_node_c *avl_create_node() {
	avl_node_c *node = NULL;
	
	if((node = malloc(sizeof(avl_node_c))) == NULL) {
		return NULL;
	}

	node -> esq = NULL;
	node -> dir = NULL;
	node -> codigo_cliente = 0;

	return node;	
}

/*calcular a altura de um dado nodo */
int avl_node_altura(avl_node_c *node) {

	int altura_esq = 0;
	int altura_dir = 0;

	if(node -> esq) altura_esq = avl_node_altura(node -> esq );
	if(node -> dir) altura_dir = avl_node_altura(node -> dir);

	return altura_dir > altura_esq ? ++altura_dir : ++altura_esq;
}

/*fazer um balanço de alturas entre as subarvores que sucedem um dado nodo*/
int avl_balance_factor(avl_node_c *node) {

	int bf = 0;

	if (node -> esq) bf += avl_node_altura(node -> esq);
	if (node -> dir) bf -= avl_node_altura(node -> dir);

	return bf ;
}

avl_node_c *avl_rotate_esqEsq(avl_node_c *node) {
 	
 	avl_node_c *a = node;
	avl_node_c *b = a -> esq;
	
	a -> esq = b -> dir;
	b -> dir = a;

	return(b);
}


avl_node_c *avl_rotate_esqDir(avl_node_c *node) {

	avl_node_c *a = node;
	avl_node_c *b = a -> esq;
	avl_node_c *c = b -> dir;
	
	a -> esq = c -> dir;
	b -> dir = c -> esq; 
	c -> esq = b;
	c -> dir = a;

	return(c);
}

/* dir esq Rotate */
avl_node_c *avl_rotate_dirEsq(avl_node_c *node) {
	
	avl_node_c *a = node;
	avl_node_c *b = a -> dir;
	avl_node_c *c = b -> esq;
	
	a -> dir = c -> esq;
	b -> esq = c -> dir; 
	c -> dir = b;
	c -> esq = a;

	return(c);
}

/* dir dir Rotate */
avl_node_c *avl_rotate_dirDir(avl_node_c *node) {

	avl_node_c *a = node;
	avl_node_c *b = a -> dir;
	
	a -> dir = b -> esq;
	b -> esq = a; 

	return(b);
}

/*balancear um nodo dá AVL*/
avl_node_c *avl_balance_node(avl_node_c *node) {

	avl_node_c *novaRaiz = NULL;
	int bf;

	if (node -> esq)
		node -> esq = avl_balance_node(node -> esq);
	
	if (node -> dir) 
		node -> dir = avl_balance_node(node -> dir);

	bf = avl_balance_factor(node);

	if (bf >= 2) {
		/*  */	

		if (avl_balance_factor(node -> esq) <= -1 ) 
			novaRaiz = avl_rotate_esqDir( node );
		else 
			novaRaiz = avl_rotate_esqEsq( node );

	} 

	else if( bf <= -2 ) {
		
		if( avl_balance_factor(node -> dir) >= 1 )
			novaRaiz = avl_rotate_dirEsq(node);
		
		else 
			novaRaiz = avl_rotate_dirDir(node);

	} 

	else {
		/*nodo já está balanceado*/
		novaRaiz = node;
	}

	return(novaRaiz);	
}


// recalcular a altura de um dado nodo/produto

void nova_altura(avl_node_c *cliente) {

    cliente -> altura = 1 + max(altura(cliente -> esq), altura(cliente -> dir));
}

//rodar à direita




/* Balancear uma árvore*/
void avl_balance_tree(avl_tree_c *tree) {

	avl_node_c *novaRaiz = NULL;

	novaRaiz = avl_balance_node(tree -> raiz);

	if (novaRaiz != tree -> raiz) {
		tree -> raiz = novaRaiz; 
	}
}

/* Insert a new node. */
void insere_cliente(avl_tree_c *tree, char codigo) {

	avl_node_c *node = NULL;
	avl_node_c *next = NULL;
	avl_node_c *last = NULL;

	/* Well, there must be a first case */ 	
	if (tree -> raiz == NULL ) {
		node = avl_create_node();
		node -> codigo_cliente = codigo_cliente;
		node -> altura = nova_altura(node);

		tree -> raiz = node;

	/* Okay.  We have a  raiz already.  Where do we put this? */
	} 

	else {

		next = tree-> raiz;

		while( next != NULL ) {
			last = next;

			if (codigo_cliente < next -> codigo_cliente) {
				next = next -> esq;

			} else if (codigo_cliente > next -> codigo_cliente) {
				next = next -> dir;

			/* Have we already inserted this node? */
			} else if (codigo_cliente == next -> codigo_cliente) {
				/* This shouldn't happen. */	
			}
		}

		node = avl_create_node();
		node -> codigo_cliente = codigo_cliente;

		if (codigo_cliente < last -> codigo_cliente) last -> esq = node;
		if (codigo_cliente > last -> codigo_cliente) last -> dir = node;
		
	}

	avl_balance( tree );
}

/* Find the node containing a given codigo_cliente */
avl_node_c *avl_procura_cliente(avl_tree_c *tree, int codigo_cliente) {

	avl_node_c *current_node = tree -> raiz;

	while(current_node && current_node -> codigo_cliente != codigo_cliente) {

		if (codigo_cliente > current_node -> codigo_cliente)
			current_node = current_node->dir;

		else
			current_node = current_node -> esq;
	
	return current_node;
}

void inOrder(avl_node_c raiz) {

    if (raiz != NULL) {
        inOrder(raiz -> esq);
        printf("%s ", raiz -> codigo_cliente);
        inOrder(raiz -> right);
    }
}

int main(){


}