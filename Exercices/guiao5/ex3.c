#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){


	int pd[2];
	pipe(pd);
	int i = 0;
	char buffer[1024];
	int n = 0;

	if(fork() == 0){

		close(pd[1]);
		dup2(pd[0], 0);
		close(pd[0]);
		execlp("wc", "wc", NULL);
		_exit(1);
	
	}

	close(pd[0]);
	while((n = read(0, buffer, sizeof(buffer))) > 0)
		write(pd[1], buffer, n);

	close(pd[1]);
	return 0;
}