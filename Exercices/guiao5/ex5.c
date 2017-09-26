#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

typedef struct Commands{

	const char** argv;
	
}Command;


int spawn_proc(int in, int out, Command *cmd){

	pid_t pid;


	if((pid = fork()) == 0){
		if(in != 0){
			dup2(in, 0);
			close(in);
		}

		if(out != 1){
			dup2(out, 1);
			close(out);
		}

		execvp(cmd -> argv[0], (char * const *) cmd ->argv);
		perror(cmd -> argv[0]);
		_exit(1);
	}

	return pid;
}


int exec_cmds(int n, Command *cmd){


	int pd[2];
	int i, fd_in = 0;
	//pid_t pid;

	for(i = 0; i < n-1; ++i){
		pipe(pd);

		spawn_proc(fd_in, pd[1], cmd + i);

		close(pd[1]);

		fd_in = pd[0];

	}

	if(fd_in != 0){
		dup2(fd_in, 0);
	}

	execvp(cmd[i].argv[0], (char * const *)cmd[i].argv);
	perror(cmd[i].argv[0]);
	exit(1);
}

int main(int argc, char** argv){

	const char* grep[] = {"grep", "-v", "^#", "/etc/passwd", NULL};
	const char* cut[] = {"cut", "-f7", "-d:", NULL};
	const char* uniq[] = {"uniq", NULL};
	const char* wc[] = {"wc", "-l", NULL}; 


	Command cmd[] = {{grep}, {cut}, {uniq}, {wc}};

	return exec_cmds(4, cmd);


}


/*
int main(int argc, char** argv){


	int pd[2];
	pid_t pid = fork();
	pipe(pd);

	if(pid == -1){
		exit(1);
	}

	if(pid == 0){

		if(fork() == 0){

			if(fork() == 0){
				close(pd[0]);
				//dup2(pd[1], 1);
				close(pd[1]);
				printf("%d\n", pd[1]);
				execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);
				perror("grep");
				_exit(1);
			}

			printf("%d\n", pd[1]);
			//dup2(pd[1], 1);
			close(pd[1]);
			dup2(pd[0], 0);
			close(pd[0]);
			execlp("cut", "cut", "-f7", "-d:", NULL);
			perror("cut");
			_exit(1);
		}

		dup2(pd[1], 1);
		close(pd[1]);
		dup2(pd[0], 0);
		close(pd[0]);
		execlp("uniq", "uniq", NULL);
		perror("uniq");
		_exit(1);
	}

	close(pd[1]);
	dup2(pd[0], 0);
	close(pd[0]);
	execlp("wc", "wc", "-l", NULL);
	perror("wc");
	exit(1);
}
*/