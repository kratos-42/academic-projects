struct entry_s {
	char *nome;
	int tipo;
    int reg;
	struct entry_s *next;
};

typedef struct entry_s entry_t;

struct hashtable_s {
	int size;
	struct entry_s **table;	
};

typedef struct hashtable_s hashtable_t;

/**
 * Inicializa uma arvore binaria de pesquisa.
 * Retorna a arvore inicializada.
 */
hashtable_t *ht_create(int size);

/**
 * Verifica se o elemento e existe na arvore t.
 * Retorna 1 caso exista, 0 caso nao exista e -1 em caso de erro.
 */
void ht_set (hashtable_t *hashtable, char *nome, int tipo, int reg);

/**
 * Insere o elemento e na arvore t.
 * Retorna -1 em caso de erro e 0 caso corra tudo bem.
 */
entry_t *ht_newpair(char *nome, int tipo, int reg);

int ht_get_registo(hashtable_t *hashtable, char *nome);

int ht_get_tipo(hashtable_t *hashtable, char *nome);

int ht_find(hashtable_t *hashtable, char *nome);
