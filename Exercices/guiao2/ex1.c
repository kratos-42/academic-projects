#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(){

	printf("%d\n", getpid());
	printf("%d\n", getppid());

	return 0;
}