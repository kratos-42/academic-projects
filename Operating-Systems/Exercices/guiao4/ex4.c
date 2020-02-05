#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char* argv[]){

	//redirecionar o fd do input
	int i, oi = 0, oo = 0;
	for(i = 0; i < argc && argv[i][0] == '-'; i += 2){
		if(strcmp("-i", argv[i]) == 0){
			int fd = open(argv[i+1], O_RDONLY);
			if (fd == -1){
				perror(argv[i+1]);
				continue;
			}
			dup2(fd, 0);
			close(fd);
			i++;
		}

		else
			if(strcmp("-o", argv[i]) == 0){
				int fd = open(argv[i+1], O_CREAT | O_TRUNC | O_WRONLY, 0666);
				if(fd == -1){
					perror(argv[i+1]);
					continue;
				}
				dup2(fd, 1);
				close(fd);
				
			}

			else{
				fprintf(stderr, "%s: opção '%s' inválida..", argv[0], argv[i]);
				fprintf(stderr, "utilização: %s [-i fich] [-o fich]" " / " "[-o fich] cmd arg1 ... argN\n", argv[0]);
			}
	}
	if(i == argc){
		fprintf(stderr, "utilização: %s [-i fich] [-o fich]" "/" "[-o fich] cmd arg1 ... argN\n", argv[0]);

	}
	execvp(argv[i], &argv[i]);
	return 1; //INSUCESO
}
