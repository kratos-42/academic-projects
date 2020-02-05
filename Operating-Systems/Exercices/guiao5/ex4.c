#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(){

	int pd[2];
	pipe(pd);
	
	

	if(fork() == 0){

		//char* msg = "cenario\n";
		close(pd[0]);
		dup2(pd[1], 1);
		//write(pd[1], msg, strlen(msg));
		close(pd[1]);
		execlp("ls", "ls", "/etc", NULL);
		perror("ls");
		_exit(1);
	}

	close(pd[1]);
	dup2(pd[0], 0);
	close(pd[0]);
	execlp("wc", "wc", "-l", NULL);
	perror("wc");

	return 1;
}