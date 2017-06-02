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
    int destNode;
    for(int i = 0; nodes[i] != NULL; i++){
        destNode = atoi(nodes[i]);
        assert(destNode != 0);
        HASH_FIND_INT(rede, &destNode, node_to_connect);

        if (node_to_connect == NULL) {
            printf("Node %d não existe.\n", destNode);
        } else {
            node -> connected_nodes[pointer++] = destNode;			
            node -> nrConnections++;
        }
    }
}

void createNode(int idnode, char* args[]){

    struct node* s = malloc(sizeof(struct node));
    s -> id = idnode;
    s -> cmd = args;
    s -> nrConnections = 0;

    HASH_ADD_INT(rede, id, s);
}

int main(int argc, char* argv[]){

    int n, idnode;

    char line[MAX_SIZE];
    char** args;

    while((n = readln(1, line, MAX_SIZE)) > 0){
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
    }

    return 0;
}
