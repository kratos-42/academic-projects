#include <unistd.h>
#include <string.h>
#include <stdio.h>

FILE* mypopen(const char* command, const char* mode){

	int dir = (strcmp(mode, "w") == 0);
	int pd[2];
	pipe(pd);

	if(fork() == 0){

		close(pd[dir]);
		dup2(pd[1-dir], 1-dir);
		close(pd[1-dir]);
		execlp("sh", "sh", "-c", command, NULL);
		_exit(1); // EXIT_FAILURE

	}

	close(pd[1-dir]);
	return fdopen(pd[dir], mode);

}


int myfclose()

int main(){

	pid_t 

	FILE* fp = mypopen("wc -l", "w");
	fprintf(fp, "cenas\n", );
	fclose(fp);
}
