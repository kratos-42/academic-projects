#include "controller.h"




/*void writeToPipe(int idnode, char* fifo_path){
	if(fork() == 0){
		int fd; 
		char buffer[MAX_SIZE];
		if((fd = open(fifo_path, O_RDONLY)) != -1){
			dup2(pd[1], 1);
			close(pd[0]);
			close(pd[1]);

			int nbytes;
			while(1){
				if((nbytes = readln(fd, buffer, MAX_SIZE)) > 0){
					write(1, buffer, MAX_SIZE);
				}
			}
			close(fd);
		}
		perror("FIFO in %s doesn't exist", fifo_path);
		_exit(1);
	}
}*/

// fifo path dest = fpd || fifo path source = fps
/*void writeToFifo(int idnode, char* fpd, char* fps){
	int fd;
	if((fd = open(fpd, O_WRONLY)) != -1){
		dup2(fd, 1);
		close(fd);

		fd = open(fps, O_RDONLY);
		int nbytes;

		if((nbytes = readln(fd, buffer, MAX_SIZE)) > 0){
			write(1, buffer, MAX_SIZE);
		}		

	else{
		perror("FIFO %s doesn't exist!", fpd);
		_exit(1);
	}
	close(fd);
}
}
*/
// AUXILIAR TO READ FROM PIPE BEFORE GOES TO THE NODE
void readFromFifo(int pd[], char* fifo_path){

	if(fork() == 0){
		int fd; 
		char buffer[MAX_SIZE];
		while((fd = open(fifo_path, O_RDONLY)) == -1);
		
		printf("Reading from fifo with fd: %d to pd[1]: %d\n", fd, pd[1]);
		dup2(fd, 0);
		//dup2(pd[1], 1);
		close(fd);
		close(pd[0]);
		close(pd[1]);

		int nbytes;
		while(1){
			if((nbytes = readln(0, buffer, MAX_SIZE)) > 0){
				buffer[nbytes] = '\n';
				buffer[nbytes+1] = '\0';	
				printf("%d\n", nbytes);
				write(1, buffer, strlen(buffer));
			}
		}
	}
	else 
		printf("Already reading from FIFO\n");
}


// fps = FIFO path source
void deliver(int idnode, char* fps){

	if(fork() == 0){
		struct node* node;
		struct node* dest_node;
		HASH_FIND_INT(net, &idnode, node);
		int fd_src;
		int fd_dest;
		char fpd[30];
		int nbytes;
		int idDestNode;


		
		while((fd_src = open(fps, O_RDONLY)) == -1); //WAIT TILL THE FIRST MESSAGE BE WROTE
		
		dup2(fd_src, 0);
		close(fd_src);
		
		char buffer[MAX_SIZE];
		while(1){
			if((nbytes = readln(0, buffer, MAX_SIZE)) > 0){
				//buffer[nbytes] = '\0';
				printf("message to print: %s\n", buffer);
				if(node -> nrConnections == 0){
					fd_dest = open("./collector", O_CREAT | O_APPEND | O_WRONLY, 0666);
					write(fd_dest, buffer, MAX_SIZE);
					close(fd_dest);
				}
				else{
					for(int i = 0; i < node -> nrConnections; i++){
						idDestNode = node -> connected_nodes[i];
						HASH_FIND_INT(net, &idDestNode, dest_node);
						sprintf(fpd, "./pipes/FIFOin%d", idDestNode);
						fd_dest = open(fpd, O_WRONLY);
						write(fd_dest, buffer, MAX_SIZE);
						close(fd_dest);
					}
				}

			}
		}
	}
	else
		printf("going on\n");;
}

void createNode(int idnode, char** args){
	
	struct node* s = malloc(sizeof(struct node));
	char fifonamein[30], fifonameout[30];
	s -> id = idnode;
	s -> cmd = args;
	s -> nrConnections = 0;
	s -> running = 0;
	HASH_ADD_INT(net, id, s);
	
	umask(0);
	sprintf(fifonamein, "./pipes/FIFOin%d", idnode);
	sprintf(fifonameout, "./pipes/FIFOout%d", idnode);
	mkfifo(fifonamein, 0666);
	mkfifo(fifonameout, 0666);

	int pd[2];
	pipe(pd);
	
	deliver(idnode, fifonameout);
	
	if(fork()==0){
		int fd = open(fifonameout, O_CREAT | O_APPEND | O_WRONLY, 0666);
		dup2(pd[0], 0);
		dup2(fd, 1);
		close(fd);
		close(pd[0]);
		close(pd[1]);

		execv(args[0], args);
		perror(args[0]);
		_exit(1);
	}
	else{
		readFromFifo(pd, fifonamein);
		close(pd[0]);
		close(pd[1]);
	}
	printf("Node %d registered\n", idnode);
}


void connectNodes(int idnode, char* nodes[]){

	struct node* node;
	HASH_FIND_INT(net, &idnode, node);
	if(node == NULL){
		printf("Node %d não existe.\n", idnode);
		return;
	}

	struct node* node_to_connect;
	int next = node -> nrConnections;
	int idDestNode;
	int i;

	for(i = 0; nodes[i] != NULL; i++){
		idDestNode = atoi(nodes[i]);
        HASH_FIND_INT(net, &idDestNode, node_to_connect); // VERIFICAR EXISTÊNCIA
        
        if(node_to_connect == NULL){
        	printf("Node %d não existe.\n", atoi(nodes[i]));

        }
        else{ // CASO NÃO EXISTA NA LISTA DE CONEXÕES
        	node -> connected_nodes[next++] = atoi(nodes[i]);
        	node -> nrConnections++;
        }
    }
}

void inject(int idnode, char* args[]){
	struct node* node;
	HASH_FIND_INT(net, &idnode, node);
	int fd;
	char fifonamein[30];
	sprintf(fifonamein, "./pipes/FIFOin%d", idnode);
	
	if(fork() == 0){
		if((fd = open(fifonamein, O_WRONLY)) != -1){
			//printf("my fd to output now is: %d from fifo: %s\n", fd, fifonamein);
			dup2(fd, 1);
			close(fd);

			execvp(args[0], args);
			perror(args[0]);
			_exit(1);
		}
		else{
			perror(fifonamein);
			_exit(1);
		}
	}
}


int main(int argc, char* argv[]){

	int n, idnode;
	char line[MAX_SIZE];
	char** args;
	int pd[2];
	pipe(pd);

	while(1){
		if((n = readln(0, line, MAX_SIZE)) > 0){
		args = split(line, " \n");

			if(strcmp(args[0], "node") == 0){
				idnode = atoi(args[1]);
				args[argc] = NULL;
				createNode(idnode, args + 2);
			}


			else if(strcmp(args[0], "connect") == 0){
				idnode = atoi(args[1]);
				connectNodes(idnode, args + 2);
			}

			else if(strcmp(args[0], "disconnect") == 0){
				idnode = atoi(args[1]);
				//disconnect(idnode, atoi(args[2]));
			}

			else if(strcmp(args[0], "inject") == 0){
				idnode = atoi(args[1]);
				args[argc] = NULL;
				inject(idnode, args+2);
				
			}

			else if(strcmp(args[0], "net") == 0){
				struct node *s = net;

				for(s=net; s != NULL; s=s->hh.next) {
	        		printf("user id %d:\n name %s\n, conncted to %d\n", s->id, s->cmd[0], s->connected_nodes[0]);
				}
			}

		}
	}
	return 0;
}