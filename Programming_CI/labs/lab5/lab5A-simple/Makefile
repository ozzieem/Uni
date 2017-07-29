OBJ = lexer.o  symbol.o error.o parser.tab.o
CFLAGS += -Wall -c
EXE = lab3d

lab5a:		$(OBJ)
	g++ -Wall -o lab3d $(OBJ)

lexer.o: 	lexer.cpp global.h parser.tab.hpp
	g++ $(CFLAGS) lexer.cpp

symbol.o: 	symbol.cpp global.h
	g++ $(CFLAGS) symbol.cpp

error.o: 	error.cpp global.h
	g++ $(CFLAGS) error.cpp

parser.tab.cpp parser.tab.hpp:	parser.ypp
	bison -d parser.ypp

clean: 
	rm -f $(EXE) $(OBJ) parser.tab.cpp parser.tab.hpp *~
