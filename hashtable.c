#define _XOPEN_SOURCE 500 

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

struct entry_s {
	char *nome;
	int tipo;
    void* valor;
	
	struct entry_s *next;
};

typedef struct entry_s entry_t;

struct hashtable_s {
	int size;
	struct entry_s **table;	
};

typedef struct hashtable_s hashtable_t;



hashtable_t *ht_create (int size) {

	hashtable_t *hashtable = NULL;
	int i;

	if ( size < 1 ) return NULL;

	
	if (( hashtable = malloc(sizeof(hashtable_t ))) == NULL) {
		return NULL;
	}

	
	if (( hashtable -> table = malloc(sizeof(entry_t *) * size)) == NULL ) {
		return NULL;
	}
	for (i = 0; i < size; i++) {
		hashtable -> table[i] = NULL;
	}

	hashtable -> size = size;

	return hashtable;	
}


int ht_hash (hashtable_t *hashtable, char *nome) {

	unsigned long int hashval;
	int i = 0;

	
	while (hashval < ULONG_MAX && i < strlen(nome)) {
		hashval = hashval << 8;
		hashval += nome[i];
		i++;
	}

	return hashval % hashtable -> size;
}


entry_t *ht_newpair(char *nome, int tipo, void* valor) {

	entry_t *newpair;

	if ((newpair = malloc(sizeof(entry_t))) == NULL) {
		return NULL;
	}

	if ((newpair -> nome = strdup(nome)) == NULL) {
		return NULL;
	}

	if ((newpair -> tipo = tipo) > 0) {
		return NULL;
	}


	if ((newpair -> valor = valor) == NULL) {
		return NULL;
	}

	newpair -> next = NULL;

	return newpair;
}

/* Insert a nome-valor pair into a hash table. */
void ht_set(hashtable_t *hashtable, char *nome, int tipo, void* valor) {
	int bin = 0;
	entry_t *newpair = NULL;
	entry_t *next = NULL;
	entry_t *last = NULL;

	bin = ht_hash(hashtable, nome);

	next = hashtable -> table[bin];

	while (next != NULL && next -> nome != NULL && strcmp(nome, next -> nome) > 0) {
		last = next;
		next = next->next;
	}

	
	if (next != NULL && next -> nome != NULL && strcmp(nome, next -> nome) == 0) {
		free(next -> valor);
		next -> valor = valor;

	} else {
		newpair = ht_newpair(nome, tipo, valor);

		/* We're at the start of the linked list in this bin. */
		if( next == hashtable -> table[bin]) {
			newpair -> next = next;
			hashtable -> table[bin] = newpair;
	
		/* We're at the end of the linked list in this bin. */
		} else if ( next == NULL ) {
			last -> next = newpair;
	
		/* We're in the middle of the list. */
		} else  {
			newpair -> next = next;
			last -> next = newpair;
		}
	}
}

/* Retrieve a nome-valor pair from a hash table. */
void* ht_get_valor(hashtable_t *hashtable, char *nome) {
	int bin = 0;
	entry_t *pair;

	bin = ht_hash(hashtable, nome);

	/* Step through the bin, looking for our valor. */
	pair = hashtable -> table[bin];
	while (pair != NULL && pair -> nome != NULL && strcmp(nome, pair -> nome) > 0) {
		pair = pair -> next;
	}

	/* Did we actually find anything? */
	if (pair == NULL || pair -> nome == NULL || strcmp(nome, pair -> nome) != 0) {
		return NULL;

	} else {
		return pair -> valor;
	}
	
}

int ht_get_tipo(hashtable_t *hashtable, char *nome) {
	int bin = 0;
	entry_t *pair;

	bin = ht_hash(hashtable, nome);

	/* Step through the bin, looking for our valor. */
	pair = hashtable -> table[bin];
	while (pair != NULL && pair -> nome != NULL && strcmp(nome, pair -> nome) > 0) {
		pair = pair -> next;
	}

	/* Did we actually find anything? */
	if (pair == NULL || pair -> nome == NULL || strcmp(nome, pair -> nome) != 0) {
		return -1;

	} else {
		return pair -> tipo;
	}
	
}


/*
int main( int argc, char **argv ) {

	hashtable_t *hashtable = ht_create( 65536 );

	ht_set( hashtable, "z1", "kratos" );
	ht_set( hashtable, "key2", "pinky" );
	ht_set( hashtable, "key3", "blinky" );
	ht_set( hashtable, "key4", "floyd" );

	printf( "%s\n", ht_get( hashtable, "z1" ) );
	printf( "%s\n", ht_get( hashtable, "key2" ) );
	printf( "%s\n", ht_get( hashtable, "key3" ) );
	printf( "%s\n", ht_get( hashtable, "key4" ) );

	return 0;
}
*/
