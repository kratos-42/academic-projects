%{
    #include <stdio.h>
    #include <string.h>
    #include "hashtable.h"
    #include <stdlib.h>
    
    #define inteiro 1
    #define vetor   2


    FILE *FF;
    char *varAtual;

    int f;
    int aux;
 
    int registo = 0;
    int tipo = 0;
   

    hashtable_t *ht;

    int yylex();
    int yylineno;

    int yyerror(char *s) {
        fprintf(stderr, "Erro na linha ( %d! ) %s\n", yylineno, s);
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

programa    :   INICIO                                  {FF = fopen("log.txt", "w");
                                                         ht = ht_create( 65536 );} 
                declaracoes                             { fprintf(FF,"INICIAR\n"); } 
                CORPO   
                instrucoes  
                FIM                                     { fprintf(FF,"FIM\n"); fclose(FF); }   

declaracoes : 
            |   declaracoes  declaracao 
            ;

declaracao  :   INT  {tipo = inteiro;} var                                
            |   ARRAY  {tipo = vetor;} var '(' num ')'                  
            ;   


var         :   pal                                     { 
                                                          /* varAtual = $1; printf("%d\n", ht_find(ht, varAtual)); */ 
                                                          varAtual = $1; ht_find(ht, varAtual);
                                                          if (ht_find(ht, varAtual)) { 
                                                                yyerror("A variável já foi declarada!"); exit(0); }
                                                          else { 
                                                                ht_set(ht, varAtual, tipo, registo);  fprintf(FF, "PUSHN %d\n", registo++);} }
                                                        
instrucoes  :    
            |   instrucoes  instrucao                   { ; }
            ;

instrucao   :   atribuicao                              { ; }
            |   condicao                                { ; }
            |   ciclo                                   { ; }
            |   READ '(' pal ')'                        
            |   READ '(' pal '(' expressao ')' ')'      /*{aux=ht_find(ht,$3); if(aux==0) {yyerror("A variável não foi declarada"); exit(0);} 
                                                                            else        {registo=ht_get_registo(ht, $3); fprintf(FF, "PUSH\n PUSHI %d\nPADD\n", registo);}
                                                        } */                           
            |   WRITE '(' expressao ')'
            |   WRITE '(' STRING ')'     
            ;

atribuicao  :   pal '=' expressao                       { }
            |   pal '(' expressao ')' '=' expressao                 
            ;


cond        :   expressao                   
            |   expressao OPR expressao
            |   expressao ""
            ;

expressao   :   termo                       
            |   expressao '+' termo 
            |   expressao '-' termo     
            |   expressao '|''|' termo
            ;


termo       :   fator                       
            |   termo '*' fator
            |   termo '/' fator
            |   termo '&''&' fator              
            ;

fator       :   pal     
            |   pal '(' expressao ')'                                                       
            |   num             
            |   '(' cond ')'
            |   '!' fator               
            ;

condicao    :   IF '(' cond ')'   instrucoes   ENDIF    
            |   IF '(' cond ')'   instrucoes   ELSE instrucoes  ENDIF 
            ;

ciclo       :   WHILE '('cond')' instrucoes ENDWHILE 
            ;


%%



int main(int argc, char* argv[]){


    yyparse();
    return 0;

}

