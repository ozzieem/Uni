CC = gcc
CFLAGS += -Wall -std=c99 -g
OBJ = lab5.tab.o lex.yy.o node.o
  
lab5:	$(OBJ)
	$(CC) $(CFLAGS) -o lab5 $(OBJ)
  
symbol.o:	symbol.c symbol.h
	$(CC) $(CFLAGS) -c symbol.c
  
lab5.tab.c lab5.tab.h:	lab5.y
	bison -d lab5.y
  
lex.yy.c:	lab5.l
	flex lab5.l
  
lex.yy.o:	lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c
  
clean:
	$(RM) lab5 lab5.tab.o lab5.tab.c lab5.tab.h lex.yy.o lex.yy.c symbol.o node.o
