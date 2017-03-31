#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	execlp("./a.out", "o que me apetecer", "a", "b", NULL);
	perror("./g03-a")
	return 1;
}