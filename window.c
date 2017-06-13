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

/*
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
*/


float average(float* values, int n){

	float avg=0;
	int i;
	for(i = 0; i < n; i++){
		avg += values[i];
	}

	return avg/i;
}

float max(float* values, int n){

	float max = 0;
	for(int i = 0; i < n; i++){
		if(max < values[i])
			max = values[i];
	}

	return max;
}

float min(float* values, int n){

	float min = 0;
	for(int i = 0; i < n; i++){
		if(min > values[i])
			min = values[i];
	}

	return min;
}

float sum(float* values, int n){

	float sum;

	for(int i = 0; i < n; i++){
		sum += values[i];
	}

	return sum;
}



int main(int argc, char* argv[]){


	int col = atoi(argv[1]);
	int lin = atoi(argv[3]);

	char operador[128];
	strcpy(operador, argv[2]);


	/*if(strcmp(operador, "avg") == 0){
		average(col, lin);
	}

	if(strcmp(operador, "max") == 0){
	}*/
	return 0;

}