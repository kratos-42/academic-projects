#include "const.h"

void addColumn(char* args){

	int n;
	char line[MAX_SIZE];
	char buffer[1024];

	while((n = read(0, line, MAX_SIZE)) > 0) {

		//printf("%s", line);
		line[n-1] = '\0';
		snprintf(buffer, MAX_SIZE, "%s:%s\n", line, args);
		//printf("%s\n", buffer);
		write(1, buffer, strlen(buffer));	
	}
}



int main(int argc, char* argv[]){


	addColumn(argv[1]);
	return 0;
}