all:
	@echo "\"make cmodels\" ou \"make engine\""

cmodels: cmodels.c
	gcc cmodels.c -o cmodels -lm

engine: parserXML.c engine.c
	gcc engine.c parserXML.c -o engine -lGL -lGLU -lglut -I/usr/include/libxml2 -lxml2 -lz -lm -ldl

# To remove generated files
clean:
	rm -f *.o a.out engine cmodels
