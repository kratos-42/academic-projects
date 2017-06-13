# Declaration of variables
CC = gcc
CC_FLAGS = -Wall -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wno-unused-parameter -g

all: controlador.o const filter spawn window utils.o
	$(CC) $(CC_FLAGS) controlador.o utils.o -o Controlador $(CC_FLAGS)


const: const.o
	$(CC) $(CC_FLAGS) const.o -o const
filter: filter.o utils.o
	$(CC) $(CC_FLAGS) utils.o filter.o -o filter
spawn: spawn.o utils.o
	$(CC) $(CC_FLAGS) utils.o spawn.o -o spawn
window: window.o
	$(CC) $(CC_FLAGS) window.o -o window

%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@
clean:
	rm -f Controlador const filter spawn window *.o
