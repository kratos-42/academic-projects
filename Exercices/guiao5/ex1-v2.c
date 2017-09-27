#include <unistd.h>
#include <stdio.h>
#include <string.h>



int main(){

	int pd[2];
	char* msg = "yeah!! ";
	char* msg2 = "tchuz\n";
	pipe(pd);

	if(fork() == 0){ //filhote
		char buffer[1024];
		int n;
		close(pd[1]);
		
		while(1){
			n = read(pd[0], buffer, sizeof(buffer));
			
			if(n <= 0) break;

			write(1, buffer, n);
		}
		close(pd[0]);
		_exit(0);
	}

	close(pd[0]);
	write(pd[1], msg, strlen(msg));
	sleep(5);
	write(pd[1], msg2, strlen(msg2));
	close(pd[1]);
	return 0;
}