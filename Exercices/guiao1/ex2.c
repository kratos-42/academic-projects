
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int cat_fd(int fd){

	char buffer[512];
	ssize_t nbytes;
	while((nbytes = read(0, buffer, sizeof(buffer))) > 0){
		write(fd, buffer, nbytes);
		
	}
}



int main(int argc, char* argv[]){
	
	//int fd = open("ficheiro", O_WRONLY);

	int n, r, p;

	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	cat_fd(fd);
	close(fd);

	return 0;
}