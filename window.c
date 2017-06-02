#include "window.h"

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


void average(int col, int nrlinhas){

	int n, i, j, accumulate, currLine;
	char line[MAX_SIZE], aux[MAX_SIZE];
	char arg1[MAX_SIZE];
	char buffer[MAX_SIZE];
	int linhas[nrlinhas]; 

	while((n = read(0, line, MAX_SIZE)) > 0){
		line[n-1] = '\0';

		strcpy(aux, line);
		getCollumn(aux, col, arg1, MAX_SIZE);

		currLine = nrlinhas;	
		for(i = 0; i < currLine; i++, currLine--){
			if(i - currLine >= 0){
				printf("%d\n", currLine);
				linhas[i] = atoi(arg1);

			}
			else 
				linhas[i] = 0;
		}

		j = 0;
		accumulate = 0;
		while(j < i){
			accumulate += linhas[j++];
		}

		snprintf(buffer, MAX_SIZE, "%s:%d\n", line, (accumulate/j));
		write(1, buffer, strlen(buffer));
	}
}







int main(int argc, char* argv[]){


	int col = atoi(argv[1]);
	int lin = atoi(argv[3]);

	char operador[128];
	strcpy(operador, argv[2]);


	if(strcmp(operador, "avg") == 0){
		average(col, lin);
	}
}