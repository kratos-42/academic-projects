
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int i = 0;

int main(){

	pid_t pid1 = fork();
	

	if(pid1 == -1){
		printf("erro\n");
	}

	while(i <= 10){
			if(i == 1) exit(0);
			printf("pid = %d\n pid do pai = %d\n", getpid(), getppid());
			i++;
			fork();
		}
	
	
	
	

	}
