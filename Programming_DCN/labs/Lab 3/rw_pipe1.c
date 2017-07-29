


/* rw_pipe.c (1 child-process) */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "vt200.h"
#include <unistd.h>
#include <string.h>

char *strrev(char *str)
{
	char *p1, *p2;

	if (!str || !*str)
		return str;
	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
	{
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}

	return str;
}


main()
{
	int pid, fd[2];
	char buf[100], str[100];


	CLRSCR; HOME;
	POS(10, 20); printf("FORKTEST, type Ctrl/D to exit!");
	fflush(stdout);

	pipe(fd);


	pid = fork(); 	 /* Try to fork!  */
	if (pid == -1)
	{
		perror("Forking");	 /* Couldn't fork! */
		exit(1);
	}
	else if (pid == 0)	//1st child process
	{
		while (1)
		{
			read(fd[0], buf, sizeof(buf));
			SAVE_CURSOR;
			POS(15, 10); printf("The string was: %s", buf); CLRLINE;
			RESTORE_CURSOR;
			fflush(stdout);
		}
	}

	/* This is parent process.               */
	POS(15, 10); printf("A string please: "); CLRLINE;
	fflush(stdout);
	while (scanf("%s", str) != EOF)
	{

		POS(17, 10); printf("New string please: "); CLRLINE;
		fflush(stdout);
		write(fd[1], str, strlen(str) + 1);
	}

	kill(pid, SIGTERM);
	CLRSCR; HOME; CURSOR_ON;
	fflush(stdout);

}
