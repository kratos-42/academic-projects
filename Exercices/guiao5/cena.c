#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(){

	int pd[2];
	pipe(pd);
	int n;
	char* buffer[1024];

	if(fork() == 0){

		//char* msg = "cenario\n";
		close(pd[0]);
		dup2(pd[1], 1);
		//write(pd[1], msg, strlen(msg));
		close(pd[1]);
		execlp("date", "date", NULL);
		perror("date");
		_exit(1);
	}

	close(pd[1]);
	n = read(pd[0], buffer, sizeof(buffer));
	write(1, buffer, n);

	return 0;
}