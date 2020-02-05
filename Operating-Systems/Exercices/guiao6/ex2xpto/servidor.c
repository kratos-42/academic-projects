#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(){

	int fd;
	int log;
	mkfifo("./fifo", 0666);

	while((fd = open("./fifo", O_RDONLY)) != -1){
		char buffer[512];
		int n;

		if((log = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1){
			perror("log.txt");
			continue;
		}

		n = read(fd, buffer, sizeof(buffer));
		//write(1, buffer, n);
		write(log, buffer, n);
		close(log);
		close(fd);

	}

	perror("./fifo");
	return 1;
}