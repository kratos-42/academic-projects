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
    int contIf = 0;
    int contWh = 0;
 
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

programa    :   INICIO                                  {file = fopen("out.wm", "w"); fprintf(file,"start\n");}
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
                                                              add_var(varAtual, tipo, registo++); 
                                                          }}
                                                        
instrucoes  :    
            |   instrucao  ';' instrucoes               { ; }
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
                                                                yyerror("A variável não foi declarada!"); exit(0); 
                                                        }  else { 
                                                                tipo = var -> tipo;
                                                                if(tipo != inteiro){
                                                                    yyerror("A variável não é um inteiro"); exit(0);}
                                                                else {
                                                                    fprintf(file,"storeg %d\n", var -> registo);
                                                                } 
                                                        } } 

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

fator       :   pal                                     { varAtual = $1;
                                                          if (!(var = find_var(varAtual))) {
                                                                yyerror("A variável não foi declarada!"); exit(0); 
                                                            } else { 
                                                                tipo = var -> tipo;
                                                                if(tipo != inteiro){
                                                                    yyerror("A variável não é um inteiro"); exit(0);}
                                                                
                                                                else {
                                                                    fprintf(file,"pushg\nloadg %d\n", var -> registo);}
                                                        } }
            |   pal                                     { varAtual = $1;  
                                                          if (!(var = find_var(varAtual))) { 
                                                                yyerror("A variável não foi declarada!"); exit(0); 
                                                            } else { 
                                                                tipo = var -> tipo; 
                                                                if (tipo != vetor) { 
                                                                     printf("%d\n", tipo); fflush(stdout);
                                                                    yyerror("A variável não é um array!"); exit(0);
                                                                }  else { 
                                                                    fprintf(file,"pushgp\npushi %d\npadd\n", var -> registo);} } }
                '(' expressao ')'                       { fprintf(file,"loadn\n");}                                    
            |   num                                     { fprintf(file,"pushi %d\n",$1); }                                    
            |   '(' cond ')'
            |   '!' fator                               { ; }             
            ;

condicao    :   IF '(' cond ')'                         { fprintf(file,"jz els%d\n",contIf);}  
                    instrucoes                              
                else
            ;

else       :    ELSE instrucoes ENDIF                   { fprintf(file, "els%d:\nnop\n", contIf); contIf++;} 
           |    ENDIF                                   { fprintf(file, "els%d:\nnop\n", contIf); contIf++;} 

ciclo       :   WHILE                                   { fprintf(file,"iwhl%d:\nnop\n", contWh);}
                                              
                '(' cond ')'                            { fprintf(file,"jz fwhl%d\n", contWh); } 
                        instrucoes 
                ENDWHILE                                { fprintf(file,"jump iwhl%d\nfwhl%d:\nnop\n", contWh, contWh); contWh++;}
            ; 

%%



int main(int argc, char* argv[]){


    yyparse();
    return 0;

}

