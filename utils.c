#include "utils.h"

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

ssize_t readln(int fd, void* buf, size_t bsize){
	int n = 0, r;
	char* p = (char*) buf;

	while(n < bsize && (r = read(fd, p+n, 1) == 1) && p[n++] != '\n'){
		;
	}

	return r == -1 ? -1 : n;
}

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
