YACC = lpis.y
FLEX = lpis.l
EXECUTABLE = lpis
CC = gcc

all: lex.yy.c y.tab.c
	$(CC) y.tab.c lex.yy.c -o $(EXECUTABLE)

lex.yy.c: $(FLEX)
	flex $(FLEX)

y.tab.c: $(YACC)
	yacc $(YACC)

output: $(YACC)
	yacc -v $(YACC) && rm y.tab.c

clean:
	-rm y.tab.c
	-rm lex.yy.c
	-rm $(EXECUTABLE)
	-rm y.output
