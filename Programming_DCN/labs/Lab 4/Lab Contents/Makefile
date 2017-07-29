#===========================================================================
#  File:             Makefile
#  Version:       1.2
#  Description: This is the makefile for INETutils 
#  Authour:       Christer Lindkvist [CLT]
#  Copyright:     Christer Lindkvist
#  Modified:      Jack Pencz [JPZ]
#===========================================================================

PROJHOME =

BIN =
OBJ =
INC =

CC = cc
LD = cc
CFLAGS = -c
IFLAGS =
LIBS =

all:		INETutils.o bounce bounced

clean:	# Empty rule
		rm INETutils.o bounce.o bounced.o

veryclean:	# Empty rule
		rm *.o *.c~ *.h~ Makefile~

INETutils.o:	INETutils.c INETutils.h Makefile
		$(CC) $(CFLAGS) $(IFLAGS) INETutils.c

bounce:	bounce.o INETutils.o
		$(LD) bounce.o INETutils.o $(LIBS) -o bounce

bounce.o:	bounce.c INETutils.h Makefile
		$(CC) $(CFLAGS) $(IFLAGS) bounce.c

bounced:	bounced.o INETutils.o
		$(LD) bounced.o INETutils.o $(LIBS) -o bounced

bounced.o:	bounced.c INETutils.h Makefile
		$(CC) $(CFLAGS) $(IFLAGS) bounced.c
