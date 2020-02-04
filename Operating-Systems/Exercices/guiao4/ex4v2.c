#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv){

	int fd_in, fd_out;
	int i;
	int index = 1;

	for(i = 0; i < argc; i++){
		if(strcmp(argv[i], "-i") == 0){
			fd_in = open(argv[i+1], O_RDONLY);
			dup2(fd_in, 0);
			close(fd_in);
			i++;
		}

		
		if(strcmp(argv[i], "-o") == 0){
			fd_out = open(argv[i+1], O_CREAT | O_TRUNC | O_WRONLY, 0666);
			if(fd_out == -1){
				perror(argv[i+1]);
				continue;
			}

			dup2(fd_out, 1);
			close(fd_out);
			i++;
		}
	}


	// UMA FORMA MUITA JAVARDA DE SABER O INDICE DO COMANDO A EXECUTAR
	if(fd_in != 0)
		index += 2;

	if(fd_out != 0)
		index += 2;

	argv[argc] = NULL;
	execvp(argv[index], argv+index);
	perror(argv[i]);
	return 1;
}