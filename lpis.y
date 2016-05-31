%{

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "uthash.h"

    struct Variavel {
        char name[100];
        int tipo;
        int registo;

        UT_hash_handle hh;
    };

    struct Variavel *vars = NULL;

    void add_var(char *name, int tipo, int registo) {
        struct Variavel *var;

        HASH_FIND_STR(vars, name, var);
        if (var == NULL) {
            var = malloc(sizeof(struct Variavel));
            strcpy(var -> name, name);
            var -> tipo = tipo;
            var -> registo = registo;

            HASH_ADD_STR(vars, name, var);  
        }
    }


    struct Variavel *find_var(char* name) {
        struct Variavel *var;

        HASH_FIND_STR(vars, name, var);
        return var;
    }

    
    #define inteiro 1
    #define vetor   2


    FILE *FF;
    char *varAtual;

    int f;
    int aux;
 
    int registo = 0;
    int tipo = 0;
   


    int yylex();
    int yylineno;

    int yyerror(char *s) {
        fprintf(stderr, "Erro na linha ( %d! ) %s\n", yylineno, s);
        return 0;
    }

    struct Variavel* var;

%}

%union {
    int vali;
    char *vals;
}



%token <vali> num 
%token <vals> pal OP OPM OPR STRING 
%token INICIO CORPO IF ENDIF WHILE ENDWHILE ELSE WRITE READ INT ARRAY FIM



%%

programa    :   INICIO                                  {FF = fopen("log.txt", "w");}
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

var         :   pal                                     { varAtual = $1; 
                                                          if (var = find_var(varAtual)) { 
                                                              yyerror("A variável já foi declarada!"); exit(0);
                                                          } else { 
                                                              add_var(varAtual, tipo, registo);  fprintf(FF, "PUSHN %d\n", registo++);
                                                          }}
                                                        
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

