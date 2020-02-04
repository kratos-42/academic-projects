#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_SIZE 1024

char** split(char* string, char* seps){

    char** strings = NULL;
    char* p = strtok(string, seps);
    int n_spaces = 0;

    while (p) {
        n_spaces++;
        strings = realloc(strings, sizeof(char*) * n_spaces);
    
        if (strings == NULL)
            exit (-1); /* memory allocation failed */
    
    	
        strings[n_spaces - 1] = strdup(p);

        p = strtok(NULL, seps);
    }

    strings = realloc(strings, sizeof(char*) * (n_spaces + 1));
    strings[n_spaces] = 0;
    

    return strings;
}



int main(int argc, char* argv[]){

	int n;

	
	char line[MAX_SIZE];

	while((n = read(0, line, MAX_SIZE)) > 0){
		char** args; line[n-1] = '\0';
		int index = 0;
		args = split(line, " \n");
		

		while(args[index] != '\0'){
			index++;
		}

		if(strcmp(args[0], "exit") == 0){
			exit(1);

		}

		if(fork() == 0){
			args[index] = NULL;
			
			execvp(args[0], args);
			perror(args[0]);
			_exit(1);
		}
	}

	return 0;
}