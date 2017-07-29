OBJ = lexer.o parser.o emitter.o symbol.o init.o error.o main.o stack.o example.tab.o
CFLAGS += -Wall -c
EXE = lab3c

lab3c:		$(OBJ)
	gcc -Wall -o lab3c $(OBJ)

main.o: 	main.c global.h
	gcc $(CFLAGS) main.c

lexer.o: 	lexer.c global.h example.tab.h
	gcc $(CFLAGS) lexer.c

parser.o: 	parser.c global.h
	gcc $(CFLAGS) parser.c

emitter.o: 	emitter.c global.h
	gcc $(CFLAGS) emitter.c

symbol.o: 	symbol.c global.h
	gcc $(CFLAGS) symbol.c

init.o: 	init.c global.h
	gcc $(CFLAGS) init.c

error.o: 	error.c global.h
	gcc $(CFLAGS) error.c

stack.o:	stack.c stack.h
	gcc $(CFLAGS) stack.c
	
example.tab.c example.tab.h:	example.y
	bison -d example.y

clean: 
	rm -f $(EXE) $(OBJ) example.tab.c example.tab.h 29.tar.gz 29.zip *~
