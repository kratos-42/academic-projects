#include <stdio.h>
#include <string.h>

void add_point(FILE* f, float x, float y, float z){
	fprintf(f, "%f %f %f\n", x, y, z);
}



void criar_plano(FILE* f){


	float top_left_X = -100;
	float top_left_Y = 100;

	float top_right_X = 100;
	float top_right_Y = 100;

	float bottom_left_X = -100;
	float bottom_left_Y = -100;

	float bottom_right_X = 100;
	float bottom_right_Y = -100;

	add_point(f, top_left_X, 0, top_left_Y);
	add_point(f, bottom_left_X, 0, bottom_left_Y);
	add_point(f, bottom_right_X, 0, bottom_right_Y);

	add_point(f, top_left_X, 0, top_left_Y);
	add_point(f, bottom_right_X, 0, bottom_right_Y);
	add_point(f, top_right_X, 0, top_right_Y);

}

int main(int argc, char** argv){

	if (argc < 3) {
		printf("Argumentos errados");
	}
	char* model = argv[1];

	if (strcmp("plano", model) == 0){
		FILE* f = fopen(argv[2], "a");
		criar_plano(f);
	}
	



}
