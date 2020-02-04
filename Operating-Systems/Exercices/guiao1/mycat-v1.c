#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(){

	char linha[128];
	int n;
	while(getChar() != EOF)
		n = read(0, linha, sizeof(linha));
		write(1, linha, n);

}