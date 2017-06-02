#include "cliente.h"

void create_pipes(){

    int err = mkfifo(pp_cs, 0666); 

    if (err != 0 && errno != EEXIST){
        print_error_and_exit();
    }

    err = mkfifo(pp_sc, 0666); 

    if (err != 0 && errno != EEXIST){
        print_error_and_exit();
    }
}

void write_to_server(char* message){

    int open_pp;
    int ret;
    open_pp = open(pp_cs, O_WRONLY);

    if (open_pp <= 0){
        printf("Couldn't open server-to-client pipe!\n");
    }

    ret = write(open_pp, message, strlen(message));
    close(open_pp);

    if (ret == -1) print_error_and_exit();
}

char* wait_for_server(){

    int size = MAX_SIZE;
    char* buffer = malloc(sizeof(char) * size);
    int open_pp;
    open_pp = open(pp_sc, O_RDONLY);
    read(open_pp, buffer, size);
    close(open_pp);

    return buffer;
}


void addColumn(char* args[]){

	char message[PIPE_BUF];
	
	int constValue = atoi(args[0]);

	char* server_response;
	

}

int main(int argc, char* argv){




}