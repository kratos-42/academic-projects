# Declaration of variables
CC = gcc
CC_FLAGS = -Wall -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wno-unused-parameter -g

all: controlador.o const filter spawn # window
	$(CC) $(CC_FLAGS) controlador.o -o Controlador $(CC_FLAGS)


const: const.o
	$(CC) $(CC_FLAGS) const.o -o const
filter: filter.o
	$(CC) $(CC_FLAGS) filter.o -o filter
spawn: spawn.o
	$(CC) $(CC_FLAGS) spawn.o -o spawn
# window: window.o
# 	$(CC) $(CC_FLAGS) window.o -o window

%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o $@
clean:
	rm -f Controlador const filter spawn window *.o
