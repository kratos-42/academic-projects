%{
	#include "y.tab.h"
	//void yyerror(char *);
%}

num 		[0-9]+
pal  		[a-zA-Z]+
op  		"+"|"-"|"||"     
opM			"&&"|"*"|"/"
opR			">>"|"<<"|">="|"<="|"=="|"|=|"
inicio 		"INICIO"
corpo 		"CORPO"
fim			"FIM" 
condicao 	"IF"
else		"ELSE" 
fimCond		"ENDIF"
ciclo		"WHILE"
fimciclo	"ENDWHILE"
inteiro		"INT"
lista		"ARRAY"
read		"READ"
write		"WRITE"
string		"STRING"



%option yylineno

%%

[,()={}]            { return yytext[0]; }
{inicio}			{ return INICIO; }
{corpo}				{ return CORPO; }
{fim}				{ return FIM; }
{condicao}			{ return IF; } 
{else}				{ return ELSE; }
{fimCond}			{ return ENDIF; }
{ciclo}				{ return WHILE; }
{fimciclo}			{ return ENDWHILE; }
{op}				{ yylval.vals = strdup(yytext);return (OP); }
{opR}				{ yylval.vals = strdup(yytext);return (OPR); }
{opM}				{ yylval.vals = strdup(yytext);return (OPM);}
{lista}				{ yylval.vals = strdup(yytext);return (ARRAY);}
{inteiro}			{ yylval.vals = strdup(yytext);return (INT);}
{read}				{ return (READ);}
{write}				{ return (WRITE);}
{num}     			{ yylval.vali = atoi(yytext); return num; }
{pal} 	    		{ yylval.vals = strdup(yytext); return pal; }
\"[^"]*\"			{ yylval.vals = strdup(yytext); return (STRING);}
.|\n      			{ ; }



%%


int yywrap(){ 
	return(1);
}


