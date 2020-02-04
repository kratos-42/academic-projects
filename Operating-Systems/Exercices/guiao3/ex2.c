#include <unistd.h>

int main(int argc, char* argv[]){
	execpl("./a.out", "o que me apetecer", "a", "b", NULL);
	return 0;
}