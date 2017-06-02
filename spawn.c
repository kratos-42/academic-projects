#include "spawn.h"


int main(int argc, char* argv[]){

	char line[MAX_SIZE];
    char** args;
    argv++; argc--;
    argv[argc] = NULL;

    int n;
    while((n = readln(1, line, MAX_SIZE)) > 0){
        line[n - 1] = '\0';
        args = split(line, ":");

        for (int i = 1; i < argc; i++) {
            if (argv[i][0] == '$'){
                argv[i] = args[atoi(argv[i] + 1)];
            }
        }

        pid_t pid = fork();
        if (pid == 0){
            int dev1 = open("/dev/null", O_WRONLY);
            int dev0 = open("/dev/null", O_RDONLY);

            dup2(dev1, 1);
            dup2(dev0, 0);
            execvp(argv[0], argv);
            assert(0);
            _exit(1);
        }

        int status;
        char statusStr[10];
        waitpid(-1, &status, 0);

        for(int i = 0; args[i] != NULL; i++){
            write(1, args[i], strlen(args[i]));
            write(1, ":", 1);
        }
        sprintf(statusStr, "%d\n", status);
        write(1, statusStr, strlen(statusStr));
        args[0] = NULL;
    }

    return 0;

}
