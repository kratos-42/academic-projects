#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


int main(int argc, char* argv[]){

	//redirecionar o fd do input
	char buffer[1024];
	int fdPasswd = open("/etc/passwd", O_RDONLY);
	close(0);
	dup(fdPasswd);
	close(fdPasswd);

	//redirecionar o fd do output
	int fdSaida = open("saida.txt", O_CREAT |O_TRUNC |O_WRONLY, 0666);
	close(1);
	dup(fdSaida);
	close(fdSaida);

	//redirecionar o fd dos erros
	int fdErros = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
	close(2);
	dup(fdErros);
	close(fdErros);

	if(fork() == 0){
			fgets(buffer, sizeof(buffer), stdin);
			fprintf(stdout, "%s\n", buffer);
			fprintf(stderr, "%s\n", "teste 42\n");
	}
	//int n = read(0, buffer, sizeof(buffer));
	//write(1, buffer, n);
	//write(2, "teste\n", 6);

	return 0;
}
