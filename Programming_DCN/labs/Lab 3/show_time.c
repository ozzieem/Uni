/* show_time.c */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "vt200.h"



void show_time()		/* This function shows actual time in	  */
{						/* upper right corner on screen.	  */
   long sec;
   struct tm *now;

   sleep(2);
   for(;;)				/* Repeat forever! */
   {				
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


int main()
{

show_time();

}
