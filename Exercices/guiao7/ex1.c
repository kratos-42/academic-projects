#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int time = 0;
int count = 0;

void ctrlC_detected(int sig){

	count++;
	printf("time: %d\n", time);


}

void ctrl_pressed(int sig){

	printf("number of presses: %d\n", count);
	_exit(1);
}

void tic(){
	time++;
	alarm(1);
}

int main(){


	
	signal(SIGINT, ctrlC_detected);
	signal(SIGQUIT, ctrl_pressed);
	signal(SIGALRM, tic);
	alarm(1);

	while(1){
	
		pause();	

	}

	return 1;

}