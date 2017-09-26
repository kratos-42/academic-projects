#include "controlador.h"

void run(struct node* node, int fd_in){

	struct node* dest_node;
	int idDestNode;

	if(node -> nrConnections == 0){

		if(node -> running == 0){
			if(fork() == 0){
				int log = open("log.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

				dup2(fd_in, 0);
				dup2(log, 1);

				close(fd_in);
				close(log);

				printf("Running %d with pd[0] = %d; sending to %d\n", node -> id, fd_in, log);

				execv(node -> cmd[0], node -> cmd);
				perror(node -> cmd[0]);
				_exit(1);
			}

			else{
				node -> running = 1;
				close(node -> pd[0]);
				close(node -> pd[1]);
			}
		}

	}

	else{

		pipe(node -> pd);
		for(int i = 0; i < node -> nrConnections; i++){
			idDestNode = node -> connected_nodes[i];
			HASH_FIND_INT(rede, &idDestNode, dest_node);
			run(dest_node, node -> pd[0]);
		}

		if(node -> running == 0){
			if(fork() == 0){

				if(fd_in != 0){
					dup2(fd_in, 0);
					close(fd_in);
				}

				dup2(node -> pd[1], 1);
				close(node -> pd[1]);

				printf("node %d sending through %d, hearing from %d\n", node -> id, node -> pd[1], fd_in);
				execv(node -> cmd[0], node -> cmd);
				perror(node -> cmd[0]);
				_exit(1);
			}

			else{
				close(fd_in);
				node -> running = 1;
				close(node -> pd[0]);
				close(node -> pd[1]);
			}
		}
	}
}
/*
void inject(int idnode, char* args[]){

	struct node* node;

	HASH_FIND_INT(rede, &idnode, node);

	int pd[2];
	pipe(pd);
	run(node);

	if(fork() == 0){
		printf("pd[0] do primeiro node: %d\n", node -> pd[0]);
		dup2(pd[1], 1);
		dup2(node -> pd[0], pd[1]);
		close(pd[0]);
		close(pd[1]);
		////close(pd[1]);
		////close(node -> pd[0]);
		execvp(args[0], args);
		perror(args[0]);
		exit(1);
	}
	close(pd[0]);
	close(pd[1]);
}*/

void inject(int idnode, char* args[], int* pd){

	struct node* node;

	HASH_FIND_INT(rede, &idnode, node);


	//int pd[2];
	//pipe(pd);
	//printf("%d | %d\n", pd[0], pd[1]);
	printf("inject sending to %d, through %d\n", pd[0], pd[1]);
	run(node, pd[0]);


	if(fork()==0){
		//printf("node -> pd[1] = %d, node -> pd[0] = %d\n", node -> pd[1], node -> pd[0]);
		dup2(pd[1], 1);
		dup2(pd[0], 0);

		close(pd[0]);
		close(pd[1]);


		execvp(args[0], args);
		perror(args[0]);
		_exit(1);
	}
}

void disconnect(int idnode, int idnode2){
	struct node* node;
	int i = 0, j = 0;
	HASH_FIND_INT(rede, &idnode, node);
	int newArray[node -> nrConnections];

	if(node != NULL){
		int* connected_nodes = node -> connected_nodes;
		while(i < node -> nrConnections){

			if(connected_nodes[i] == idnode2){
				i++;
			}
			else {
				newArray[j++] = connected_nodes[i++];
			}
		}

		if(j != i)
			node -> nrConnections = j;

		memmove(connected_nodes, newArray, sizeof(newArray));
	}
}

void connectNodes(int idnode, char* nodes[]){

	struct node* node;
	HASH_FIND_INT(rede, &idnode, node);
	if(node == NULL){
		printf("Node %d não existe.\n", idnode);
		return;
	}


	struct node* node_to_connect;

	int next = node -> nrConnections;
	int idDestNode;
	int i;
	//int pd_in = node -> pd[0];
		for(i = 0; nodes[i] != NULL; i++){
			idDestNode = atoi(nodes[i]);
			HASH_FIND_INT(rede, &idDestNode, node_to_connect); // VERIFICAR EXISTÊNCIA
			if(node_to_connect == NULL){
				printf("Node %d não existe.\n", atoi(nodes[i]));

			}
			else{ // CASO NÃO EXISTA NA LISTA DE CONEXÕES
				node -> connected_nodes[next++] = atoi(nodes[i]);
				node -> nrConnections++;

				//dup2(node_to_connect -> pd[0], pd_in); //DUPLICAÇÃO DA SAIDA DO NODE PARA A ENTRADA DO NODE DESTINO
				//printf("node %d has now pd[0] = %d instead of %d\n", idDestNode, pd_in, node_to_connect -> pd[0]);
				//close(node_to_connect -> pd[0]);
				//printf("input de %d com fd = %d, mudado para o output de %d com saida %d\n", idDestNode, node_to_connect -> pd[0], idnode, node -> pd[1]);
			}
	}
}

void createNode(int idnode, char* args[]){
	struct node* s = malloc(sizeof(struct node));
	s -> id = idnode;
	s -> cmd = args;
	s -> nrConnections = 0;
	s -> running = 0;
	//pipe(s -> pd);



	HASH_ADD_INT(rede, id, s);

}

int main(int argc, char* argv[]){

    int n, idnode;

    char line[MAX_SIZE];
    char** args;
    int pd[2];
    pipe(pd);

    while((n = readln(1, line, MAX_SIZE)) > 0){
        args = split(line, " \n");

        if(strcmp(args[0], "node") == 0){
            idnode = atoi(args[1]);
            createNode(idnode, args + 2);
        }


        else if(strcmp(args[0], "connect") == 0){
            idnode = atoi(args[1]);
            connectNodes(idnode, args + 2);
        }


		else if(strcmp(args[0], "disconnect") == 0){

			idnode = atoi(args[1]);

			disconnect(idnode, atoi(args[2]));
		}

		else if(strcmp(args[0], "inject") == 0){
			idnode = atoi(args[1]);
			args[argc] = NULL;

			inject(idnode, args+2, pd);
		}

		else if(strcmp(args[0], "net") == 0){
			struct node *s = rede;

		    for(s=rede; s != NULL; s=s->hh.next) {
        		printf("user id %d:\n name %s\n in: %d\n out: %d\n", s->id, s->cmd[0], s->pd[0], s->pd[1]);
    		}
		}

	}

    return 0;
}
