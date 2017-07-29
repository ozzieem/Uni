/*
******* STUDENT VERSION ****** STUDENT VERSION ****** STUDENT VERSION ******
============================================================================
  File:             bounce.c
  Synopsis:      bounce TCP-port [host]
  Description: This is a simple client for test of the simple echo server
                     bounced (Bounce daemon).
  Version:       1.0
  Authour:      Christer Lindkvist [CLT]
  Copyright:    Christer Lindkvist
============================================================================
*/

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "INETutils.h"

#define PROMPT(s) { printf(s); fflush(stdout); }

clearbuf(char* buf, int size)
{
   int i = 0;
   for(i; i < size; i++)
   {
	buf[i] = '\0';
   }
}

int main(int argc, char *argv[])
{
  int  sock;                                    /* Socket file descriptor */
  int  rcc, wcc;                    /* Check code and character count */
  int  port;                              /* TCP port in host byte order */
  char sbuf[2048];                                     /* Send buffer */
  char rbuf[2048];                                  /* Receive buffer */
  char *host = NULL;           /* Remote host name or IP address */

/*
----------------------------------------------------------------------------
  Parse command line for TCP port number and remote host name.
----------------------------------------------------------------------------
*/
  if (argc < 2) {
    fprintf(stderr, "TCP port number is missing\n");
    return 1;
  }
  if (sscanf(argv[1], "%d", &port) != 1) {
    fprintf(stderr, "TCP port number is invalid\n");
    return 1;
  }
  if (argc > 2)
    host = argv[2];

/*
----------------------------------------------------------------------------
  Connect to bounce echo service on host, write command and read ansver.
---------------------------------------------------------------------------
*/
  /***********************************************************/
  /***  Make your changes here.                            ***/
  /***  Replace all INETutils calls by /sys/socket calls!  ***/
  /***********************************************************/
  
  struct sockaddr_in sin;
  struct hostent *hp;                /* Pointer to host data structure    */
  struct servent *sp;               /* Pointer to service data structure */

  char buf[100];

  bzero(&sin, sizeof(sin));

  gethostname(rbuf, sizeof(rbuf));
  host = rbuf;

  hp = gethostbyname(host);
  bcopy(hp->h_addr, &sin.sin_addr, hp->h_length);
  
  sin.sin_port = htons(port);
  sin.sin_family = AF_INET;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  connect(sock, (struct sockaddr *) &sin, sizeof(sin));

  printf("Connected on port %d, hopefully an echo server!\n", port);
  printf("Type some text. Exit with Ctrl/D (end of file).\n");
  PROMPT("S: ");
  while ((wcc = read(0, sbuf, sizeof(sbuf))) > 0 ) 	/* Read from stdin */
  {   
    write(sock, sbuf, wcc);                                       /* Write to socket */
    rcc = read(sock, rbuf, sizeof(rbuf));              /* Read echo from socket */
    PROMPT("R: ");                                                     /* Received */
    write(1, rbuf, rcc);                                /* Write echo to stdout  */
    PROMPT("S: ");                                                    /* Sent */
    clearbuf(rbuf, rcc);
    
  }

  shutdown(sock, 2);                    /* Disallow both send and receive */
  close(sock);                                        /* Close socket */
}





