all:
	@echo "\"make gerador\" ou \"make engine\""

gerador: gerador.c
	gcc gerador.c -o gerador -lm

engine: engine.c
	gcc engine.c -o engine -lGL -lGLU -lglut -I/usr/include/libxml2 -lxml2 -lz -lm -ldl

# To remove generated files
clean:
	rm -f *.o a.out engine gerador
