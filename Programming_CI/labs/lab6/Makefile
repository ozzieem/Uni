CC = g++
CFLAGS += -Wall -std=c++11 -g
OBJ = lab6.tab.o lex.yy.o node.o
  
lab6:	$(OBJ)
	$(CC) $(CFLAGS) -o lab6 $(OBJ)
  
lab6.tab.cpp lab6.tab.hpp:	lab6.ypp
	bison -d lab6.ypp
  
lex.yy.c:	lab6.l
	flex lab6.l
  
lex.yy.o:	lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

node.o: node.cpp node.h
	$(CC) $(CFLAGS) -c node.cpp
  
clean:
	$(RM) lab6 lab6.tab.o lab6.tab.cpp lab6.tab.hpp lex.yy.o lex.yy.c node.o
