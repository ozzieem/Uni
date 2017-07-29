OBJ = lexer.o parser.o emitter.o symbol.o init.o error.o main.o stack.o example.tab.o
CFLAGS += -Wall -c
EXE = lab3d

lab3d:		$(OBJ)
	g++ -Wall -o lab3d $(OBJ)

main.o: 	main.cpp global.h
	g++ $(CFLAGS) main.cpp

lexer.o: 	lexer.cpp global.h example.tab.hpp
	g++ $(CFLAGS) lexer.cpp

parser.o: 	parser.cpp global.h
	g++ $(CFLAGS) parser.cpp

emitter.o: 	emitter.cpp global.h
	g++ $(CFLAGS) emitter.cpp

symbol.o: 	symbol.cpp global.h
	g++ $(CFLAGS) symbol.cpp

init.o: 	init.cpp global.h
	g++ $(CFLAGS) init.cpp

error.o: 	error.cpp global.h
	g++ $(CFLAGS) error.cpp

stack.o:	stack.cpp stack.h
	g++ $(CFLAGS) stack.cpp
	
example.tab.cpp example.tab.hpp:	example.ypp
	bison -d example.ypp

clean: 
	rm -f $(EXE) $(OBJ) example.tab.cpp example.tab.hpp 29.tar.gz 29.zip *~
