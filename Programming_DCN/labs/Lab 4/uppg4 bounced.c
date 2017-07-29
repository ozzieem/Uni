/*
******* STUDENT VERSION ****** STUDENT VERSION ****** STUDENT VERSION ******
============================================================================
  File:             bounced.c
  Synopsis:      bounced TCP-port
  Description: This is a simple implementation of a echo server named 
                     bounced (bounce daemon). It's a demo designed to run in
                     the foreground, logging every connection on stdout.
                     If you want to run it in the background, redirect output
                     to a log file or /dev/null (bounced 12345 > /dev/null).
  Version:       1.0
  Authour:      Christer Lindkvist [CLT]
  Copyright:    Christer Lindkvist
============================================================================
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include "INETutils.h"

/*
============================================================================
  int take_call(int sock, int n)

  This function is the implementation of the echo server. It's called ones
  every incoming call (connection) from the child process handling the
  connection in question.

  Parameters: sock - Socket file descriptor for incoming connection
                 n - The number of the connection

  Return value:  0 - Success
                -1 - Failure
============================================================================
*/ 

int take_call(int sock, int n)
{ 
  int    cc;                            /* Check code and character count */
  char buf[2048];                    /* Send - receive (echo) buffer */ 
  char siffror[] = "0123456789\n";
  char letters[100];

  printf("Child process %d is now running\n", n);
	
  while((cc = read(sock, buf, sizeof(buf))) > 0)
  { 

    if(buf[0] == 'P' || buf[0] == 'p' || (buf[0] == '\n'))
    {
	int i;
	for(i = 32; i <= 126; i++)
	{
		letters[i-32] = i;
	}
	letters[127-32] = '\n';
	write(sock, letters, sizeof(letters) - 4);
    }
    else if(buf[0] == 'D' || buf[0] == 'd')
    {

	write(sock, siffror, sizeof(siffror));
    }
    else
    {	
	write(sock, buf, cc);
    }

  }
	
  if(cc = 0)
  {
    printf("Connection %d closed by client\n", n);
  }
  else
  {
    fprintf(stderr, "Read call failed on connection %d. " ,n);
  }
	
  TCPclose(sock);
  printf("Child process %d is closing down\n", n);
	
  return cc;
}


/*
============================================================================
  Main program
============================================================================
*/

int main(int argc, char *argv[])
{
  int n = 0;                                       /* Connection counter */
  int lsock;                                    /* Socket fd to listen on */
  int tsock;                                    /* Socket fd to talk on   */
  int port;                       /* TCP port number in host byte order */
  int pid;

/*
----------------------------------------------------------------------------
  Ignore child exit signals to avoid zombies.
----------------------------------------------------------------------------
*/
  signal(SIGCHLD, SIG_IGN);

/*
----------------------------------------------------------------------------
  Parse command line for TCP port number.
----------------------------------------------------------------------------
*/
  if (argc < 2) {
    fprintf(stderr, "TCP port is number missing\n");
    return 1;
  }
  if (sscanf(argv[1], "%d", &port) != 1) {
    fprintf(stderr, "TCP port number is invalid\n");
    return 1;
  }

/*
----------------------------------------------------------------------------
  Start listening on the requested TCP port. This is a nonblocking call!
----------------------------------------------------------------------------
*/
  if ((lsock = TCPlisten(NULL, port, 3)) < 0) {
    fprintf(stderr, "TCPlisten call failed\n");
    return 1;
  }
  printf("Listening on port %d\n", port);

/*
----------------------------------------------------------------------------
  Accept is default a blocking call, waiting for an incoming connection.
  If we want to handle more than one connection at the time, we have
  to create one child process per connection (fork). 
----------------------------------------------------------------------------
*/
  while (1) {
    if ((tsock = TCPaccept(lsock)) < 0) {
      fprintf(stderr, "TCPaccept call failed\n");
      continue;                               /* Do't weep over lost milk */
    }
    n++;
    printf("Connection %d accepted, creating child process %d\n", n, n);

/*
----------------------------------------------------------------------------
  Incoming connection accepted. Time to fork. The child process takes over
  the connection and the mother returnes to accept, waiting for a new call.
----------------------------------------------------------------------------
*/
    if ((pid = fork()) == -1) {
      perror("Fork call failed");
      TCPclose(tsock);
      continue;
    }
    else if (pid == 0) {  
      exit(take_call(tsock, n));
    }
  }
  TCPclose(lsock);
}
