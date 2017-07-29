CC = gcc
CFLAGS += -Wall -std=c99 -g
OBJ = lab4b.tab.o lex.yy.o
  
lab4b:	$(OBJ)
	gcc $(CFLAGS) -o lab4b $(OBJ)
  
symbol.o:	symbol.c symtable.h
	gcc $(CFLAGS) -c symbol.c
  
lab4b.tab.c lab4b.tab.h:	lab4b.y 
	bison -d lab4b.y
  
lex.yy.c:	lab4b.l
	flex lab4b.l
  
lex.yy.o:	lex.yy.c
	gcc $(CFLAGS) -c lex.yy.c
  
  
clean:
	$(RM) lab4b lab4b.tab.o lab4b.tab.c lab4b.tab.h lex.yy.o lex.yy.c symbol.o
