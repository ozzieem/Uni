/* rw_pipe.c (2 child processes) */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "vt200.h"
#include <unistd.h>
#include <string.h>


char *strrev(char *str) /* Se Bilaga 5 */
{
      char *p1, *p2;

      if (! str || ! *str)
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
    int pid, pid2, fd[2], fd1[2], n;
    char buf[100], str[100];

   
	CLRSCR; HOME;
    POS(10,20); printf("FORKTEST, type Ctrl/D to exit!");
    fflush(stdout);

	pipe(fd1);
	pipe(fd);

	
	pid = fork(); 	 /* Try to fork!                          */
    if  (pid ==-1)
    {
       perror("Forking");	 /* Couldn't fork!	                  */
       exit(1);
    }
    else if (pid == 0)	//1st child process
    {
    	while(1)
	{	
		read(fd[0], buf, sizeof(buf));
		SAVE_CURSOR;
		POS(15,10); printf("The string was: %s", buf); CLRLINE;
		RESTORE_CURSOR;
		fflush(stdout);
	}
    }
       
   	
	pid2 = fork();  
	
	if  (pid2 ==-1)
	{
		 perror("Forking");	 /* Couldn't fork!	                  */
		 exit(1);
	}
	else if (pid2 == 0)	//2nd Child process
	{
	
		while(1)
		{	
	
			n = read(fd1[0], buf, sizeof(buf));
			strrev(buf);	
			strcpy(str,buf);
			write(fd[1], str, strlen(str) +1);
						
		}
		
	}

	/* Se bilaga 1 */


    /* This is parent process.               */
	POS(15,10); printf("A string please: "); CLRLINE;
   	fflush(stdout);
    while(scanf("%s", str) != EOF) 
    {
      
      POS(17,10); printf("New string please: "); CLRLINE;
      fflush(stdout);
      write(fd1[1], str, strlen(str) +1);
    } 
    
	kill(pid, SIGTERM); 
    CLRSCR; HOME; CURSOR_ON;
    fflush(stdout);

}








