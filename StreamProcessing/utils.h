#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

ssize_t readln(int fd, void* buf, size_t bsize);
char** split(char* string, char* sep);
int getCollumn(char* str, int index, char* collumn, int n);
