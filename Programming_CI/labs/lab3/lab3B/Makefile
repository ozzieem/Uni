CC = gcc
CFLAGS += -Wall -std=c99 -g

lab3B: lab3B.tab.o lab3B.tab.h lex.yy.o
	gcc $(CFLAGS) -o lab3B lab3B.tab.o lex.yy.o

lab3B.tab.c lab3B.tab.h: lab3B.y
	bison -d lab3B.y

lex.yy.c: lab3B.l
	flex lab3B.l

clean:
	$(RM) lab3B lab3B.tab.o lab3B.tab.c lab3B.tab.h lex.yy.o lex.yy.c
