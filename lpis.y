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
    struct Variavel *var = NULL;

    void add_var(char *name, int tipo, int registo) {
        struct Variavel *var;

        HASH_FIND_STR(vars, name, var);
        if (var == NULL) {
            var = malloc(sizeof(struct Variavel));
            strcpy(var -> name, name);
            var -> tipo = tipo;
            var -> registo = registo;

            HASH_ADD_STR(vars, name, var);  
            return;
        }

        var -> tipo = tipo;
        var -> registo = registo;
    }


    struct Variavel *find_var(char* name) {
        struct Variavel *var;

        HASH_FIND_STR(vars, name, var);
        return var;
    }

    
    #define inteiro 1
    #define vetor   2


    FILE *file;
    char *varAtual;

    int f;
    int aux;
    int cont = 0;
 
    int registo = 0;
    int tipo = 0;
   


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
%token <vals> pal STRING 
%token INICIO CORPO IF ENDIF WHILE ENDWHILE ELSE WRITE READ INT ARRAY FIM



%%

programa    :   INICIO                                  {file = fopen("log.txt", "w"); fprintf(file,"start\n");}
                declaracoes                             
                CORPO   
                instrucoes  
                FIM                                     { fprintf(file,"stop\n"); fclose(file); }   

declaracoes : 
            |   declaracoes  declaracao 
            ;

declaracao  :   INT    {tipo = inteiro;} var                                
            |   ARRAY  {tipo = vetor;  } var '(' num ')'                  
            ;   

var         :   pal                                     { varAtual = $1; 
                                                          if (find_var(varAtual)) { 
                                                              yyerror("A variável já foi declarada!"); exit(0);
                                                          } else { 
                                                              add_var(varAtual, tipo, registo);  fprintf(file, "pushn %d\n", registo++);
                                                          }}
                                                        
instrucoes  :    
            |   instrucoes  instrucao  ';'               { ; }
            ;

instrucao   :   atribuicao                              { ; }
            |   condicao                                { ; }
            |   ciclo                                   { ; }
            |   READ '(' pal ')'                        { varAtual = $3;
                                                          if (!(var = find_var(varAtual))) { 
                                                              yyerror("A variável não foi declarada!"); exit(0); 
                                                        } else { 
                                                              fprintf(file,"read\natoi\nstoreg %d\n", var -> registo);} }
            |   READ '(' pal '(' expressao ')' ')'      { if (!(var = find_var(varAtual))) {
                                                              yyerror("A variável não foi declarada"); exit(0);
                                                        } else {
                                                              fprintf(file, "push\n pushi %d\npadd\n", var -> registo);} //
                                                        }                            
            |   WRITE '(' expressao ')'
            |   WRITE '(' STRING ')'     
            ;

atribuicao  :   pal '=' expressao                       {  varAtual = $1; 
                                                           if (!(var = find_var(varAtual))) {
                                                                printf("%s\n", var -> name); fflush(stdout);
                                                                yyerror("A variável não foi declarada!"); exit(0); 
                                                        }  else { 
                                                                fprintf(file,"storeg %d\n", var -> registo);} 
                                                        }
            |   pal                                     {   varAtual = $1;
                                                            if (!(var=find_var(varAtual))) { 
                                                                yyerror("A variável não foi declarada!"); exit(0); 

                                                            } else { 
                                                                tipo = var -> tipo;
                                                                if(tipo != vetor) { 
                                                                        yyerror("A variável não é um array!"); exit(0);} 
                                                                    else {  
                                                                        fprintf(file,"pushgp\npushi %d\npadd\n",var -> registo); 
                                                                } } }

                '(' expressao ')' '=' expressao         { fprintf(file,"storen\n"); } 
                                                                        
            ;


cond        :   expressao                               { ; }
            |   expressao '<' expressao                 { fprintf(file,"inf\n"); }
            |   expressao '>' expressao                 { fprintf(file,"sup\n"); }
            |   expressao '>''=' expressao              { fprintf(file,"supeq\n"); }
            |   expressao '<''=' expressao              { fprintf(file,"infeq\n"); }
            |   expressao '=''=' expressao              { fprintf(file,"infeq\n"); }
            |   expressao '!''=' expressao              { fprintf(file,"equal\nnot\n"); }          
            ;

expressao   :   termo                                   { ; }
            |   expressao '+' termo                     { fprintf(file,"add\n"); }
            |   expressao '-' termo                     { fprintf(file,"sub\n"); }
            |   expressao '|''|' termo                  { fprintf(file,"add\n"); }
            ;


termo       :   fator                                   { ; }
            |   termo '*' fator                         { fprintf(file,"mul\n"); }
            |   termo '/' fator                         { fprintf(file,"div\n"); }
            |   termo '&''&' fator                      { fprintf(file,"mul\n"); }
            ;

fator       :   pal                                     { if (!(var = find_var(varAtual))) {
                                                                yyerror("A variável não foi declarada!"); exit(0); 
                                                            } else { 
                                                                fprintf(file,"loadg %d\n", var -> registo);}
                                                        } 
            |   pal                                     { if (!(var = find_var(varAtual))) { 
                                                                yyerror("A variável não foi declarada!"); exit(0); 
                                                            } else { 
                                                                tipo = var -> tipo; 
                                                                if (tipo != vetor) { 
                                                                    yyerror("A variável não é um array!"); exit(0);
                                                                }  else { 
                                                                    fprintf(file,"pushgp\npushi %d\npadd\n", var -> registo);} } }
                '(' expressao ')'                       { fprintf(file,"loadn\n");}                                    
            |   num                                     { fprintf(file,"pushi %d\n",$1); }                                    
            |   '(' cond ')'
            |   '!' fator                               { ; }             
            ;

condicao    :   IF '(' cond ')'                         { fprintf(file,"jz eif%d\n",cont);}  
                    instrucoes                              
                ENDIF                                   { fprintf(file, "eif%d:k\nnop\n", cont);}
            |   IF '(' cond ')'   
                    instrucoes                          { fprintf(file, "jz els%d\n",cont);}
                ELSE                                    { fprintf(file, "els%d:\nnop\n", cont);}
                    instrucoes  
                ENDIF 
            ;

ciclo       :   WHILE                                   { fprintf(file,"iwhl%d:\nnop\n", cont); } 
                '(' cond ')'                            { fprintf(file,"jz fwhl%d\n", cont); } 
                instrucoes 
                ENDWHILE                                { fprintf(file,"jump iwhl%d\nfwhl%d:\nnop\n", cont, cont++);}
            ;


%%



int main(int argc, char* argv[]){


    yyparse();
    return 0;

}

