#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct buffer{
	char* buf;
	int size;
	int fd;

}buffer_t;


int create_buffer(int filedes, buffer_t *buffer, int nbyte){


	buffer -> buf;
	buffer -> size = nbyte;
	buffer -> fd = filedes;
	return 1;

}


int destroy_buffer(buffer_t *buffer){

	free(buffer);
	return 1;
}

ssize_t readline(buffer_t *buffer, void **buf){

	int i = 0;
	int nbtyes = 0;
	int r;
	(char*) buf[10];
	printf("%d\n", buffer -> fd);
	if(r = read(buffer -> fd, buffer -> buf, buffer -> size) >= 1 &&  !feof(stdin)){
		
		write(1, buffer -> buf, buffer -> size);
		printf("%s\n", buffer -> buf);
		buf[i++] = buffer -> buf;
		nbtyes += r;
	}
	

	printf("chegou\n");
	return r == -1 ? -1 : nbtyes;
}

int main(int argc, char* argv[]){

	buffer_t *buf = malloc(sizeof(buffer_t));
	void **buff;
	int fd = open(argv[1], O_RDONLY);
	printf("%d\n", fd);
	create_buffer(fd, buf, 256);
	printf("%d\n", buf -> size);
	int r = readline(buf, buff);
	printf("%d\n", r);
	}
	

	//int fd = open("ficheiro", O_WRONLY);
	
