#include "validar.h"
#

int vazio(char *linha){

	if(linha[0] == '\0')
		return 1;

return 0;	
}



int validar_letra(char *letra){

	if(vazio(letra) == 1){
		fprintf(stderr, "Nada foi inserido. Insira uma letra, por favor.\n");
	}

	if(isalpha(letra[0]) == 0){
		fprintf(stderr, "O caracter é inválido. Insira uma letra, por favor.\n");
	}

	if(letra[1] != '\0'){
		fprintf(stderr, "Inseriu mais que uma letra. Insira APENAS uma letra, por favor.\n");
	}
}

int dentro_alcance(int nr, int max, int min){
//Verificar se um número está entre o limite máximo e limite mínimo.

	if(nr > max){
		fprintf(stderr, "O número introduzido está acima do alcance.\n");
	}

	if(nr < min){
		fprintf(stderr, "O número introduzido está abaixo do alcance.\n");
	}

	else return 1;
}

int validar_produto(char *linha){
//Código de produto válido: 2 letra MAIÚSCULAS, seguido de 4 digitos entre 1000-1999.

	int i;

	while(linha[i] != '\0'){

		if(i < 2){

			if(isupper(linha[i]) == 0){ //caso este teste falhe, ou seja, return 0, significa que estamos perante uma letra minuscula
				fprintf(stderr, "O código do produto inicia-se com 2 letra maiúsculas!\n");
				return 0;
			}
		}

		if(i >= 2 && i <= 5){

			if(isdigit(linha[i]) == 0){
				fprintf(stderr, "Após as duas primeiras letras têm de lhe suceder 4 digitos!\n");

				return 0;
			}
		}

		if(i > 6){
			fprintf(stderr, "O código introduzido é demasiado longo%s\n");
			return 0;
		}

	}

	if(i != 6){
		fprintf(stderr, "O código introduzido não tem caracteres suficientes.%s\n");
		return 0;
	}

	return 1; //código validado e correto!
}


int main(){

	char *letra = malloc(sizeof(char));

	printf("introduzir letra\n");
	scanf("%s", letra);
	validar_letra(letra);

	return 0;
}