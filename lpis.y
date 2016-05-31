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
        }
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

programa    :   INICIO                                  {file = fopen("log.txt", "w"); fprintf(file,"INICIAR\n");}
                declaracoes                             
                CORPO   
                instrucoes  
                FIM                                     { fprintf(file,"FIM\n"); fclose(file); }   

declaracoes : 
            |   declaracoes  declaracao 
            ;

declaracao  :   INT  {tipo = inteiro;} var                                
            |   ARRAY  {tipo = vetor;} var '(' num ')'                  
            ;   

var         :   pal                                     { varAtual = $1; 
                                                          if (find_var(varAtual)) { 
                                                              yyerror("A variável já foi declarada!"); exit(0);
                                                          } else { 
                                                              add_var(varAtual, tipo, registo);  fprintf(file, "PUSHN %d\n", registo++);
                                                          }}
                                                        
instrucoes  :    
            |   instrucoes  instrucao                   { ; }
            ;

instrucao   :   atribuicao                              { ; }
            |   condicao                                { ; }
            |   ciclo                                   { ; }
            |   READ '(' pal ')'                        { if (find_var(varAtual)) { 
                                                              yyerror("A variável não foi declarada!"); exit(0); 
                                                        } else { 
                                                            add_var(varAtual, tipo, registo); fprintf(file,"READ\nATOI\nSTOREG %d\n",registo++);} }
            |   READ '(' pal '(' expressao ')' ')'      { if (find_var(varAtual)) {
                                                              yyerror("A variável não foi declarada"); exit(0);
                                                        } else {
                                                              registo=var->registo; fprintf(file, "PUSH\n PUSHI %d\nPADD\n", registo);}
                                                        }                            
            |   WRITE '(' expressao ')'
            |   WRITE '(' STRING ')'     
            ;

atribuicao  :   pal '=' expressao                       { if (find_var(varAtual)) {
                                                                yyerror("A variável não foi declarada!"); exit(0); 
                                                        }  else { 
                                                                add_var(varAtual, tipo, registo); fprintf(file,"STOREG %d\n",registo);} 
                                                        }
            |   pal                                     { if (var=find_var(varAtual)) { 
                                                                yyerror("A variável não foi declarada!"); exit(0); 
                                                            } else { 
                                                                tipo= var -> tipo; if(tipo!=vetor) { yyerror("A variável não é um array!"); exit(0);} 
                                                                    else { registo=var->registo; fprintf(file,"PUSHGP\nPUSHI %d\nPADD\n",registo); } } }
                '(' expressao ')' '=' expressao         { fprintf(file,"STOREN\n"); } 
                                                                        
            ;


cond        :   expressao                               { ; }
            |   expressao '<' expressao                 { fprintf(file,"INF\n"); }
            |   expressao '>' expressao                 { fprintf(file,"SUP\n"); }
            |   expressao '>''=' expressao              { fprintf(file,"SUPEQ\n"); }
            |   expressao '<''=' expressao              { fprintf(file,"INFEQ\n"); }
            |   expressao '=''=' expressao              { fprintf(file,"INFEQ\n"); }
            |   expressao '!''=' expressao              { fprintf(file,"EQUAL\nNOT\n"); }          
            ;

expressao   :   termo                                   { ; }
            |   expressao '+' termo                     { fprintf(file,"ADD\n"); }
            |   expressao '-' termo                     { fprintf(file,"SUB\n"); }
            |   expressao '|''|' termo                  { fprintf(file,"ADD\n"); }
            ;


termo       :   fator                                   { ; }
            |   termo '*' fator                         { fprintf(file,"MUL\n"); }
            |   termo '/' fator                         { fprintf(file,"DIV\n"); }
            |   termo '&''&' fator                      { fprintf(file,"MUL\n"); }
            ;

fator       :   pal                                     { if (var=find_var(varAtual)) {
                                                                yyerror("A variável não foi declarada!"); exit(0); 
                                                            } else { 
                                                                registo=var->registo; fprintf(file,"LOADG %d\n",registo);}
                                                        } 
            |   pal                                     { if (var=find_var(varAtual)) { 
                                                                yyerror("A variável não foi declarada!"); exit(0); 
                                                            } else { 
                                                                tipo=var->tipo; if(tipo!=vetor) { yyerror("A variável não é um array!"); exit(0);} 
                                                                    else { registo=var->registo; fprintf(file,"PUSHGP\nPUSHI %d\nPADD\n",registo);} } }
                '(' expressao ')'                       { fprintf(file,"LOADN\n");}                                    
            |   num                                     { fprintf(file,"PUSHI %d\n",$1); }                                    
            |   '(' cond ')'
            |   '!' fator                               { ; }             
            ;

condicao    :   IF '(' cond ')'                         //{ fprintf(file,"JZ eif%d\n",cont);}  
                instrucoes                              
                ENDIF    
            |   IF '(' cond ')'   instrucoes            //{ fprint(file, "JZ lab%d\n",cont);}
                    ELSE instrucoes  
                ENDIF 
            ;

ciclo       :   WHILE                                   //{ fprintf(file,"iwhl%d: NOP\n",cont);} 
                '('cond')'                              //{ fprintf(file,"JZ fwhl%d\n",cont); } 
                instrucoes 
                ENDWHILE                                //{ fprintf(file,"JUMP iwhl%d\nfwhl%d: NOP\n",cont,cont++);}
            ;


%%



int main(int argc, char* argv[]){


    yyparse();
    return 0;

}

