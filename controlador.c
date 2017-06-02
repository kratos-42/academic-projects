#include "controlador.h"

ssize_t readln(int fd, void* buf, size_t bsize){
	int n = 0, r;
	char* p = (char*) buf;

	while(n < bsize && (r = read(fd, p+n, 1) == 1) && p[n++] != '\n'){
		;
	}

	return r == -1 ? -1 : n;
}



char** split(char* string){

    char** strings = NULL;
    char* p = strtok(string, " ");
    int n_spaces = 0;

    while (p) {
        n_spaces++;
        strings = realloc(strings, sizeof(char*) * n_spaces);
    
        if (strings == NULL)
            exit (-1); /* memory allocation failed */
    
        strings[n_spaces - 1] = strdup(p);
    
        p = strtok(NULL, " ");
    }

    strings = realloc(strings, sizeof(char*) * (n_spaces + 1));
    strings[n_spaces] = 0;

    return strings;
}


void run(struct node* node){

	struct node* dest_node;
	int idDestNode;

	for(int i = 0; i < node -> nrConnections; i++){
		idDestNode = node -> connected_nodes[i];
		printf("%d\n", idDestNode);
		HASH_FIND_INT(rede, &idDestNode, dest_node);
		run(dest_node);

		if(node -> running == 0){
			close(node -> pd[1]);
			if(fork() == 0){
				node -> running = 1;
				execvp(node -> cmd[0], node -> cmd+1);
			}

			close(node -> pd[0]);
		}
		else
			return;
	}
}


void inject(int idnode, char* args[]){

	int i = 0, idCurrDestNode;
	struct node* node;
	//struct node* dest;

	HASH_FIND_INT(rede, &idnode, node);
	
/*
	while(i < node -> nrConnections){

		idCurrDestNode = node -> connected_nodes[i];
		HASH_FIND_INT(rede, &idCurrDestNode, dest);
		
	}*/
	

	run(node);


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
	
	dup2(nodes -> pd[1], 1);
	printf("pd[0]: %d pd[1]: %d\n", node->pd[0], node->pd[1]);

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
				dup2(node_to_connect -> pd[0], node -> pd[1]);

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
	printf("Node %d adicionado\n", s->id);
}




int main(int argc, char* argv[]){

	int n, idnode;

	// line para ler do stdin || buffer para fazer uma copia da line e fazer os strtok  
	// command para verificar o comando do controlador || comp para verificar cada um dos componentes do comando do controlador
	char line[MAX_SIZE];
	char** args;

	while((n = readln(1, line, MAX_SIZE)) > 0){

		//strcpy(buffer, line);
		args = split(line);

		if(strcmp(args[0], "node") == 0){

			idnode = atoi(args[1]);
			
			createNode(idnode, args+2);
			
			
		}

		else if(strcmp(args[0], "connect") == 0){

			idnode = atoi(args[1]);

			connectNodes(idnode, args+2);
		}

		else if(strcmp(args[0], "disconnect") == 0){

			idnode = atoi(args[1]);

			disconnect(idnode, atoi(args[2]));
		}

		else if(strcmp(args[0], "inject")){
			idnode = atoi(args[1]);

			inject(idnode, args+2);
		}
	}

	return 0;
}