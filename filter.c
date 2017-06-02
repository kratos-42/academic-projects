#include "filter.h"

void filterEq(int col, int col2){

	int n;
	char line[MAX_SIZE], aux[MAX_SIZE];
	char arg1[MAX_SIZE], arg2[MAX_SIZE];
	char buffer[MAX_SIZE]; 

	while((n = read(0, line, MAX_SIZE)) > 0){
		line[n-1] = '\0';

		strcpy(aux, line);
		getCollumn(aux, col, arg1, MAX_SIZE);
		strcpy(aux, line);
		getCollumn(aux, col2, arg2, MAX_SIZE); 

		if(strcmp(arg1, arg2) != 0){
			snprintf(buffer, MAX_SIZE, "%s\n", line);
			write(1, buffer, strlen(buffer));
		}
	}
}


void filterEqGreater(int col, int col2){


	int n;
	char line[MAX_SIZE], aux[MAX_SIZE];
	char arg1[MAX_SIZE], arg2[MAX_SIZE];

	while((n = read(0, line, MAX_SIZE)) > 0){
		line[n-1] = '\0';

		strcpy(aux, line);
		getCollumn(aux, col, arg1, MAX_SIZE);
		strcpy(aux, line);
		getCollumn(aux, col2, arg2, MAX_SIZE); 
		
		if(strcmp(arg1, arg2) < 0 || strcmp(arg1, arg2) == 0){
			write(1, line, strlen(line));
		}
	}
}

void filterEqLess(int col, int col2){


	int n;
	char line[MAX_SIZE], aux[MAX_SIZE];
	char arg1[MAX_SIZE], arg2[MAX_SIZE];

	while((n = read(0, line, MAX_SIZE)) > 0){
		line[n-1] = '\0';

		strcpy(aux, line);
		getCollumn(aux, col, arg1, MAX_SIZE);
		strcpy(aux, line);
		getCollumn(aux, col2, arg2, MAX_SIZE); 
		
		if(strcmp(arg1, arg2) > 0 || strcmp(arg1, arg2) == 0){
			write(1, line, strlen(line));
		}
	}
}

void filterGreater(int col, int col2){


	int n;
	char line[MAX_SIZE], aux[MAX_SIZE];
	char arg1[MAX_SIZE], arg2[MAX_SIZE];

	while((n = read(0, line, MAX_SIZE)) > 0){
		line[n-1] = '\0';

		strcpy(aux, line);
		getCollumn(aux, col, arg1, MAX_SIZE);
		strcpy(aux, line);
		getCollumn(aux, col2, arg2, MAX_SIZE); 
		
		if(strncmp(arg1, arg2, MAX_SIZE) < 0){
			write(1, line, strlen(line));
		}
	}
}

void filterLess(int col, int col2){


	int n;
	char line[MAX_SIZE], aux[MAX_SIZE];
	char arg1[MAX_SIZE], arg2[MAX_SIZE];

	while((n = read(0, line, MAX_SIZE)) > 0){
		line[n-1] = '\0';

		strcpy(aux, line);
		getCollumn(aux, col, arg1, MAX_SIZE);
		strcpy(aux, line);
		getCollumn(aux, col2, arg2, MAX_SIZE); 
		
		if(strncmp(arg1, arg2, MAX_SIZE) > 0){
			write(1, line, strlen(line));
		}
	}
}

void filterDiff(int col, int col2){


	int n;
	char line[MAX_SIZE], aux[MAX_SIZE];
	char arg1[MAX_SIZE], arg2[MAX_SIZE];

	while((n = read(0, line, MAX_SIZE)) > 0){
		line[n-1] = '\0';

		strcpy(aux, line);
		getCollumn(aux, col, arg1, MAX_SIZE);
		strcpy(aux, line);
		getCollumn(aux, col2, arg2, MAX_SIZE); 
		
		if(!(strcmp(arg1, arg2) == 0)){
			write(1, line, strlen(line));
		}
	}
}

int main(int argc, char* argv[]){

	int col = atoi(argv[1]);
	int col2 = atoi(argv[3]);

	if(strcmp(argv[2], "=") == 0){
		filterEq(col, col2);
	}

	else if(strcmp(argv[2], ">=") == 0){
		filterEqGreater(col, col2);
	}

	else if(strcmp(argv[2], "<=") == 0){
		filterEqLess(col, col2);
	}

	else if(strcmp(argv[2], ">") == 0){
		filterGreater(col, col2);
	}

	else if(strcmp(argv[2], "<") == 0)
		filterLess(col, col2);

	else if(strcmp(argv[2], "!=") == 0)
		filterDiff(col, col2);

	return 0;



}
