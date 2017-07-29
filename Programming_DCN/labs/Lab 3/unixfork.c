/* unixfork.c */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "vt200.h"
#include <unistd.h>


void show_time()		/* This function shows actual time in	  */
{				/* upper right corner on screen.	  */
   long sec;
   struct tm *now;

   sleep(2);
   for(;;) {			/* Repeat forever!		          */
      time(&sec);		/* Time in seconds since January 1, 1970  */
      now = localtime(&sec);    /* Time in hours, minutes, seconds, ...   */
      CURSOR_OFF;
      SAVE_CURSOR;
      POS(1,70);
      printf("%02d:%02d:%02d", now->tm_hour, now->tm_min, now->tm_sec);
      RESTORE_CURSOR;
      CURSOR_ON;
      fflush(stdout);
      sleep(1);
   }
}

void interaction()		/* This function asks for a string and	  */
{				/* prints it out again, until Ctrl/D is   */
   char str[60];		/* pressed (EOF).                         */

   POS(15,10); printf("A string please: "); CLRLINE;
   fflush(stdout);
   while(scanf("%s", str) != EOF) {
      POS(15,10); printf("The string was: %s", str); CLRLINE;
      POS(17,10); printf("New string please: "); CLRLINE;
      fflush(stdout);
   }
}

main()
{
   int pid;

   CLRSCR; HOME;
   POS(10,20); printf("FORKTEST, type Ctrl/D to exit!");
   fflush(stdout);


   switch (pid = fork()) {	 /* Try to fork!  */
      case -1:
		  perror("Forking");	 /* Couldn't fork!	  */
		  exit(1);
      case 0:	/* This is child process. */
		  execlp("./show_time", "show_time", NULL);	// show_time();
		  break;
      default:	/* This is parent process.  */
		  interaction();		 /* Child has process id = pid   */
		  kill(pid, SIGTERM);     /* Kill child process.   */
		  break;
   }

   CLRSCR; HOME; CURSOR_ON;
   fflush(stdout);
}
