%{
	#include <stdio.h>
	#include <string.h>
	
	#define inteiro 1
	#define vetor	2

	FILE *file;
	char *varAtual;
	int cont = 0;
	int f;
	int aux;
	int proxReg = 0;
	int registo;
	int tipo;
	int tamanho = 1;

	int yylex();
	int yylineno;

	int yyerror(char *s) {
    	fprintf(stderr, "%s, line %d\n", s, yylineno);
    	return 0;
	}

%}

%union {
	int vali;
	char *vals;
}



%token <vali> num 
%token <vals> pal OP OPM OPR STRING 
%token INICIO CORPO IF ENDIF WHILE ENDWHILE ELSE WRITE READ INT ARRAY FIM



%%

programa	: 	INICIO declaracoes { fprintf(file,"INICIAR\n"); } CORPO	instrucoes	FIM { fprintf(file,"FIM\n"); fclose(file); }	

declaracoes	: 
			| 	declaracoes  declaracao 
			;

declaracao	: 	INT var 						 	{tipo = inteiro;}
			| 	ARRAY pal '[' num ']'				{tipo = vetor;}
			;	


var 		:	pal 								

instrucoes	:	 
			|	instrucoes  instrucao 
			;

instrucao	:	atribuicao					
			| 	condicao					
			| 	ciclo						
			|	READ '(' pal ')'
			| 	READ '(' pal '[' expressao ']' ')' 									
			|	WRITE '(' expressao ')'
			|	WRITE '(' STRING ')'	 
			;

atribuicao 	:	pal '=' expressao 			
			|	pal '[' expressao ']' '=' expressao					
			;


cond		:	expressao					
			| 	expressao OPR expressao 	
			;

expressao	: 	termo						
			| 	expressao '+' termo	
			|	expressao '-' termo		
			|	expressao '|''|' termo
			;


termo		: 	fator						
			| 	termo '*' fator
			|	termo '/' fator
			| 	termo '&''&' fator				
			;

fator		: 	pal		
			|	pal '[' expressao ']'														
			| 	num				
			|	'(' cond ')'
			| 	'!' fator				
			;

condicao	: 	IF '(' cond ')'   instrucoes   ENDIF  	
			| 	IF '(' cond ')'   instrucoes   ELSE instrucoes  ENDIF 
			;

ciclo 		:	WHILE '('cond')' instrucoes ENDWHILE 
			;


%%

#include "lex.yy.c"

int yyerror(char *s) {
	fprintf(stderr, "Erro na linha ( %d! ) %s\n", yylineno, s);
	return 0;
}

int main(int argc, char* argv[]){


	return 0;

}

