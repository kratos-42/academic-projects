#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){

	int fd;
	char buffer[512];
	if((fd = open("/tmp/fifo", O_WRONLY)) == -1){
		perror("/tmp/fifo");
		return 1;
	}

	snprintf(buffer, sizeof(buffer), "%s\n", argv[1]);
	write(fd, buffer, strlen(buffer));
	close(fd);

	return 0;
}