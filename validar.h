#ifndef VALIDAR_C
#define VALIDAR_C
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXBUFFERVENDAS 128
#define MAXBUFFERPRODUTOS 64
#define MAXBUFFERCLIENTES 32


int vazio(char *linha);

int validar_letra(char *letra);

int dentro_alcance(int nr, int max, int min);

int validar_produto(char *linha);
















#endif