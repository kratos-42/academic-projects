#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(){

	pid_t pidFilho = fork();

	if(pidFilho == -1){
		printf("erro\n");
	}

	printf("pid = %d\npid do pai = %d\n", getpid(), getppid());

	}