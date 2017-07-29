CC = g++
CFLAGS += -Wall -std=c++11 -g
OBJ = lab7.tab.o lex.yy.o node.o
  
lab7:	$(OBJ)
	$(CC) $(CFLAGS) -o lab7 $(OBJ) ./StackMachine/StackMachine.cpp
  
lab7.tab.cpp lab7.tab.hpp:	lab7.ypp
	bison -d lab7.ypp
  
lex.yy.c:	lab7.l
	flex lab7.l
  
lex.yy.o:	lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

node.o: node.cpp node.h
	$(CC) $(CFLAGS) -c node.cpp
  
clean:
	$(RM) lab7 lab7.tab.o lab7.tab.cpp lab7.tab.hpp lex.yy.o lex.yy.c node.o


