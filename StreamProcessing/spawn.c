#include "spawn.h"


int main(int argc, char* argv[]){

	char line[MAX_SIZE]; char aux[MAX_SIZE];
    char argCol[MAX_SIZE];

    int i;
    

    int n;
    while((n = read(0, line, MAX_SIZE)) > 0){
        line[n - 1] = '\0';
        char* cmd[MAX_SIZE];

        for (i = 1; i < argc; i++) {
            
           
            if (argv[i][0] == '$'){
                char* str;
                
                
                str = strdup(&argv[i][1]);

                
                
                int indexColumn = atoi(str);
                strcpy(aux, line);
                getCollumn(aux, indexColumn, argCol, MAX_SIZE);
                cmd[i-1] = strdup(argCol);

            }

            else{
                cmd[i-1] = strdup(argv[i]);
                
            }
        } 
 
        cmd[argc] = NULL;

        pid_t pid = fork();
        if (pid == 0){
            int log = open("log.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
            //printf("valor de log: %d\n", log = open("log.txt", O_CREAT | O_APPEND | O_WRONLY, 0666));
      
            dup2(log, 1);
            close(log);
                
            execvp(cmd[0], cmd);
            assert(0 && "msg");
            _exit(1);
            
        }

       
        int status;
        char statusStr[10];
        waitpid(-1, &status, 0);
/*
        for(i = 0; args[i] != NULL; i++){
            write(1, args[i], strlen(args[i]));
            write(1, ":", 1);
        }*/
        sprintf(statusStr, "%s:%d\n", line, status);
        write(1, statusStr, strlen(statusStr));

    }

    return 0;

}
