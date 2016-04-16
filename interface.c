#include "interface.h"

void getFicheiro(){

	char *nome_ficheiro;
	char *buffer;

	nome_ficheiro = fgets(buffer, 1024, stdin);

}


void query1(){

	char *produtos;
	char *clientes;
	char *vendas;
	char *buffer;

	puts("Ficheiro dos produtos ");
	produtos = getFicheiro();

	puts("Ficheiro dos clientes ");
	clientes = getFicheiro();


	puts("Ficheiro das vendas ");
	vendas = getFicheiro();


	printf("O ficheiro dos produtos que foi lido é %s", produtos);
	printf("O ficheiro dos clientes que foi lido é %s", clientes);
	printf("O ficheiro das vendas que foi lido é %s", vendas);
	
}

void query2(){

	char *listaProdutos;

	puts("Procurar produtos começados por ");
	


}

void queries(int n){

    switch (n) {
        case 1:
            query1();
            break;
        case 2:
            query2();
            break;
        case 3:
            query3();
            break;
        }
}

