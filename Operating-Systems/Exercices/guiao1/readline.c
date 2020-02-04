#include <unistd.h>


//typedef int ssize_t;
//typedef unsigned size_t;

ssize_t readln(int fd, void* buf, size_t bsize){
	int n = 0, r;
	char* p = (char*) buf;

	while(n < bsize && (r = read(fd, p+n, 1) == 1) && p[n] != '\n'){
		n++;
	}

	return r == -1 ? -1 : n;
}

#ifdef __TEST

int main(){
	char linha[512];
	int n;
	n = readln(0, linha, sizeof(linha));
	write(1, linha, n);
	return 0; //EXIT_SUCCESS
}

#endif