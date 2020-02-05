#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(){

	int fd;
	umask(0);
	mkfifo("/tmp/fifo", 0666);
	
	while((fd = open("/tmp/fifo", O_RDONLY)) != -1){
		int log, n;
		char buffer[512];
		
		printf("valor de log: %d\n", log = open("tmp/log", O_CREAT | O_APPEND | O_WRONLY, 0666));
		if((log = open("/tmp/log.txt", O_CREAT | O_APPEND | O_WRONLY, 0666) == -1)){
			perror("/tmp/log.txt");
			continue;
		}
		n = read(fd, buffer, sizeof(buffer));
		write(log, buffer, n);
		close(log);
		close(fd);
	}

	perror("/tmp/fifo");
	return 1;

}