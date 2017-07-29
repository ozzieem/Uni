/*
============================================================================
  File:            INETutils.c
  Description: High level socket utility library for TCP/IP protocol family
                    (ARPA Internet protocol family).
  Version:       1.1
  Authour:      Christer Lindkvist [CLT]
  Copyright:    Christer Lindkvist
============================================================================
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include "INETutils.h"

/*
============================================================================
  int INETget_sockaddr(struct sockaddr_in *sin, char *host, char *serv,
                       char *proto, unsigned short int port)

  Get the Internet socket address (binary IP address and port number)

  Parameters:  sin - Internet socket address structure
              host - Host name (short or fully qualified domain name)
                     or host address in decimal dot notation.
                     If host is NULL, the local host is assumed.
              serv - Socket service name using protocol proto.
                     If serv is NULL, port number is used instead.
             proto - Socket service protocol, "tcp" or "udp".
                     Ignored if socket service name is NULL.
              port - TCP port number in host byte order (LSB first).
                     Ignored if socket service name is not NULL.
 
  Return value:  0 - Success
                -1 - Failure
============================================================================
*/

int INETget_sockaddr(struct sockaddr_in *sin, char *host, char *serv,
                     char *proto, unsigned short int port)
{
  char buf[100];
  struct in_addr sin_addr;        /* Temporary Internet socket address */
  struct hostent *hp;                /* Pointer to host data structure    */
  struct servent *sp;               /* Pointer to service data structure */

/*
----------------------------------------------------------------------------
 Clear Internet socket address structure
----------------------------------------------------------------------------
*/
  bzero(sin, sizeof(*sin));

/*
----------------------------------------------------------------------------
 Get local host name as default host name   
----------------------------------------------------------------------------
*/
  if (host == NULL) {
    gethostname(buf, sizeof(buf));
    host = buf;
  }

/*
----------------------------------------------------------------------------
  Get host binary IP address in network byte order    
----------------------------------------------------------------------------
*/
  if (inet_aton(host, &sin_addr)) {                /* Try decimal dot to notation */
    sin->sin_addr = sin_addr;
  }
  else if ((hp = gethostbyname(host)) != NULL) {         /* Try host name */
    bcopy(hp->h_addr, &sin->sin_addr, hp->h_length);
  }
  else {
    perror("Get host failed");
    return -1;
  }

/*
----------------------------------------------------------------------------
  Get binary port number in network byte order    
----------------------------------------------------------------------------
*/
  if (serv != NULL) {
    if ((sp = getservbyname(serv, proto)) == NULL) {
      perror("Get service failed");
      return -1;
    }
    sin->sin_port = sp->s_port;
  }
  else {
     sin->sin_port = htons(port);        /* Convert to network byte order */
  }

/*
----------------------------------------------------------------------------
 Set family to ARPA Internet protocol family (TCP/IP protocol family)
----------------------------------------------------------------------------
*/
  sin->sin_family = AF_INET;

/*
----------------------------------------------------------------------------
 All done, successful return
----------------------------------------------------------------------------
*/
  return 0;
}


/*
============================================================================
  int TCPconnect(char *host, char *serv, unsigned short int port)

  Create a socket and connect to a socket service (TCP port) on a host.

  Parameters: host - Host name (short or fully qualified domain name)
                     or host address in decimal dot notation.
                     If host is NULL, the local host is assumed.
              serv - Socket service name.
                     If serv is NULL, port number is used instead.
              port - TCP port number in host byte order (LSB first).
                     Ignored if socket service name is not NULL.
 
  Return value: sock - The file descriptor of the connected socket
                  -1 - Failure
============================================================================
*/

int TCPconnect(char *host, char *serv, unsigned short int port)
{
  int sock;                                           /* Socket file descriptor  */
  struct sockaddr_in sin;                       /* Internet socket address */

/*
----------------------------------------------------------------------------
  Get the Internet socket address (binary IP address and port number)
----------------------------------------------------------------------------
*/
  if (INETget_sockaddr(&sin, host, serv, "tcp", port) < 0) {
    fprintf(stderr, "Illegal port number\n");
    return -1;
  }

/*
----------------------------------------------------------------------------
  Create TCP socket (ARPA Internet protocol family default stream socket)   
----------------------------------------------------------------------------
*/
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Socket call failed");
    return -1;
  }

/*
----------------------------------------------------------------------------
  Connect to the server   
----------------------------------------------------------------------------
*/
  if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
    perror("Connect failed");
    close(sock);
    return -1;
  }
  
/*
----------------------------------------------------------------------------
  We are connected, return socket file descriptor   
----------------------------------------------------------------------------
*/
  return sock;  
}


/*
============================================================================
  int TCPlisten(char *serv, unsigned short int port, int qlim)

  Create a socket and start listen on it.

  Parameters: serv - Socket service name.
                     If serv is NULL, port number is used instead.
              port - TCP port number in host byte order (LSB first).
                     Ignored if socket service name is not NULL.
              qlim - Queue limit for incoming connections.
 
  Return value: sock - The file descriptor of the listening socket
                  -1 - Failure
============================================================================
*/

int TCPlisten(char *serv, unsigned short int port, int qlim)
{
  int sock;                                          /* Socket file descriptor  */
  int on = 1;                                        /* Option value, turn on   */
  struct sockaddr_in sin;                      /* Internet socket address */

/*
----------------------------------------------------------------------------
  Get the Internet socket address (binary IP address and port number)
----------------------------------------------------------------------------
*/
  if (INETget_sockaddr(&sin, NULL, serv, "tcp", port) < 0) {
    fprintf(stderr, "Illegal port number\n");
    return -1;
  }

/*
----------------------------------------------------------------------------
  Create TCP socket (ARPA Internet protocol family default stream socket)   
----------------------------------------------------------------------------
*/
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Socket call failed");
    return -1;
  }

/*
----------------------------------------------------------------------------
  Set socket options, reuse address   
----------------------------------------------------------------------------
*/
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
    perror("Set socket options call failed");
    /* Never mind, continue anyway */
  }

/*
----------------------------------------------------------------------------
  Bind socket to address   
----------------------------------------------------------------------------
*/
  if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
    perror("Bind call failed");
    close(sock);
    return -1;
  }

/*
----------------------------------------------------------------------------
  Start listen on socket   
----------------------------------------------------------------------------
*/
  if (listen(sock, qlim) < 0) {
    perror("Listen call failed");
    close(sock);
    return -1;
  }

/*
----------------------------------------------------------------------------
  We are listening on socket, return socket file descriptor   
----------------------------------------------------------------------------
*/
  return sock;
}


/*
============================================================================
  int TCPaccept(int sock)

  Accept an incoming connection

  Paraneters: sock - Listening socket file descriptor

  Return value: new_sock - New socket fd for accepted connection
                      -1 - Failure
============================================================================
*/
int TCPaccept(int sock)
{
  int new_sock;                              /* New socket file descriptor   */
  struct sockaddr_in sin;                 /* Peer Internet socket address */
  int sinsize = sizeof(sin);
  
/*
----------------------------------------------------------------------------
  Accept new connection request and get new socket for connection  
----------------------------------------------------------------------------
*/
  if ((new_sock = accept(sock, (struct sockaddr *) &sin, &sinsize)) < 0) {
    perror("Accept call faild");
    return -1;
  }

/*
----------------------------------------------------------------------------
  New connection accepted, return the new socket file descriptor   
----------------------------------------------------------------------------
*/
  return new_sock;
}


/*
============================================================================
  void TCPclose(int sock)

  Shut down socket, remove references and locks.

  Parameters: sock - Socket file descriptor
============================================================================
*/

void TCPclose(int sock)
{
  shutdown(sock, 2);                    /* Disallow both send and receive */
  close(sock);                             /* Close socket and remove locks  */
}
