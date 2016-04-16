Prod_Tree analise_ficheiro_produtos(char *file){

	char linha[MAX_TAM_PROD];
	char *codigo;
	FILE *ficheiro;
	Prod_Tree tree = NULL;

	ficheiro = fopen(file, "r");

	if(ficheiro = NULL){
		fprintf(stderr, "Erro\n");

	}


}