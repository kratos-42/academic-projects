#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "utils.h"

#define PIPE_BUF 1024

char* pp_cs = ".pipe_cs";
char* pp_sc = ".pipe_sc";

void write_to_server(char* message);

void create_pipes();

void print_help();

int main(int argc, char* argv[]);