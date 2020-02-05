#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){

	char buffer[512];
	int fd;
	int n;

	while((n = read(0, buffer, sizeof(buffer))) > 0){
			buffer[n-1] = '\0';
		if((fd = open("./fifo", O_WRONLY)) != -1){
			char rd_buffer[512];

			snprintf(rd_buffer, sizeof(rd_buffer), "%s\n", buffer);
			write(fd, rd_buffer, strlen(rd_buffer));
			close(fd);
		}

		else{
			perror("./fifo");
			return 1;
		}
	}

	return 0;
}