CC = g++
CFLAGS += -Wall -std=c++11 -g
OBJ = lab5.tab.o lex.yy.o node.o
  
lab5:	$(OBJ)
	$(CC) $(CFLAGS) -o lab5 $(OBJ)
  
lab5.tab.cpp lab5.tab.hpp:	lab5.ypp
	bison -d lab5.ypp
  
lex.yy.c:	lab5.l
	flex lab5.l
  
lex.yy.o:	lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

node.o: node.cpp node.h
	$(CC) $(CFLAGS) -c node.cpp
  
clean:
	$(RM) lab5 lab5.tab.o lab5.tab.cpp lab5.tab.hpp lex.yy.o lex.yy.c node.o
