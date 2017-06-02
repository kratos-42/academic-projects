#include "controlador.h"

void run(struct node* node){

	struct node* dest_node;
	int idDestNode;

	if(node -> nrConnections == 0){

		if(node -> running == 0){
			if(fork() == 0){
				close(node -> pd[1]);
				node -> running = 1;
				execv(node -> cmd[0], node -> cmd+1);
				perror(node -> cmd[0]);
				_exit(1);
			}
		}
	}

	else{
		for(int i = 0; i < node -> nrConnections; i++){
			idDestNode = node -> connected_nodes[i];
			HASH_FIND_INT(rede, &idDestNode, dest_node);
			run(dest_node);
		}
			
		if(node -> running == 0){
			printf("A correr node %d com pd[0] = %d\n", node -> id, node -> pd[0]);
			if(fork() == 0){
				node -> running = 1;
				execv(node -> cmd[0], node -> cmd+1);
				perror(node -> cmd[0]);
				_exit(1);
			}
		}
	}
}

void inject(int idnode, char* args[]){

	struct node* node;

	HASH_FIND_INT(rede, &idnode, node);
	
	int pd[2];
	pipe(pd);

	if(fork() == 0){
		close(pd[0]);
		dup2(pd[0], 1);
		run(node);
		execvp(args[0], args+1);
		perror(args[0]);
		exit(1);
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

	int pointer = node -> nrConnections;
	int idDestNode;
	int i = 0;

		for(i = 0; nodes[i] != NULL; i++){
			idDestNode = atoi(nodes[i]); 
			HASH_FIND_INT(rede, &idDestNode, node_to_connect); // VERIFICAR EXISTÊNCIA
			if(node_to_connect == NULL){
				printf("Node %d não existe.\n", atoi(nodes[i]));

			}
			else{ // CASO NÃO EXISTA
				node -> connected_nodes[pointer++] = atoi(nodes[i]);			
				node -> nrConnections++;
				
				printf("fd output de %d para %d\n", node -> pd[1], node_to_connect -> pd[0]);
				dup2(node -> pd[1], node_to_connect -> pd[0]); //DUPLICAÇÃO DA SAIDA DO NODE PARA A ENTRADA DO NODE DESTINO

			}
	}
}

void createNode(int idnode, char* args[]){
	struct node* s = malloc(sizeof(struct node));
	s -> id = idnode;
	s -> cmd = args;
	s -> nrConnections = 0;
	s -> running = 0;
	pipe(s -> pd);


	HASH_ADD_INT(rede, id, s);

}

int main(int argc, char* argv[]){

    int n, idnode;

    char line[MAX_SIZE];
    char** args;

    while((n = readln(1, line, MAX_SIZE)) > 0){
        args = split(line, " ");

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

			inject(idnode, args+2);
		}

	}

    return 0;
}
