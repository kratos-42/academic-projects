#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	int fd, n;
	
	char line[512];


	while(1) {

		char buffer[512];
		

		if((fd = open("/tmp/fifo", O_WRONLY)) == -1){
			perror("/tmp/fifo");
			return 1;
		}

		printf("%d\n", n = read(0, line, sizeof(line)));
		snprintf(buffer, sizeof(buffer), "%s\n", line);
		write(fd, buffer, strlen(buffer));
		close(fd);


	}

	return 0;
}