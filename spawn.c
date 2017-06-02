#include "spawn.h"

int getCollumn(char* str, int index, char* collumn, int n) {

	int i = 1;
	char* s;
	for (s = strtok(str, ":\n"); s && i < index; s = strtok(NULL, ":\n"), i++);

	if (s) {
		strncpy(collumn, s, n);
		return strlen(s);
	}

	return 0;

}


int main(int argc, char* argv[]){

	char line[MAX_SIZE], aux[MAX_SIZE];
	char colValue[MAX_SIZE];
	

	int i = 0;
	int index, argvIndex;
	char cpy[MAX_SIZE];
	char string[MAX_SIZE];

	//PROCURAR O VALOR SEGUIDO DE $ 
	// Percorrer todos os indices de argv, seguidamente de cada um dos caracteres aí contidos. 
	// No caso de encontrar $, guarda em index o valor que o procede até ao delimeter " ".
	while(i <= argc){
		int j = 0;
		strcpy(string, argv[i]);
		while(string[j] != '\0'){
			if(string[j] == '$'){
				index = atoi(strtok(string+1, " "));
				argvIndex = i; // É PRECISO ALTERAR O ARGV[i] COM O VALOR DA COLUNA CORRESPONDENTE 
				//printf("%d\n", index);
				break;
			}
			j++;
		}
		if(index != 0)
			break;
		i++;
	}


	int n;
	char writeBuffer[MAX_SIZE];

	while((n = read(0, line, MAX_SIZE)) > 0){
		line[n-1] = '\0';

		strcpy(aux, line);
		getCollumn(aux, index, colValue, MAX_SIZE);
		strcpy(argv[argvIndex], colValue);
		argv[argc] = NULL;

		pid_t pid = fork();

		if(pid == 0){
			execvp(argv[1], argv+2);
			perror(argv[1]);
			_exit(1);

		}

		int status;
		waitpid(-1, &status, 0);
		
		snprintf(writeBuffer, MAX_SIZE, "%s:%d\n", line, status);
		write(1, writeBuffer, strlen(writeBuffer));


	}

	return 0;

}