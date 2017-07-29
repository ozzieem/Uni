/*
============================================================================
  File:            INETutils.h
  Description: High level socket utility library for TCP/IP protocol family
                    (ARPA Internet protocol family).
  Version:       1.0
  Authour:      Christer Lindkvist [CLT]
  Copyright:    Christer Lindkvist
============================================================================
*/

#ifndef _INET_UTILS_H
#define _INET_UTILS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

/*
============================================================================
*/

extern int INETget_sockaddr(struct sockaddr_in *sin, char *host, char *serv,
                            char *proto, unsigned short int port);
/*
----------------------------------------------------------------------------
  Get the Internet socket address (binary IP address and port number)

  Parameters:  sin - Internet socket address structure
              host - Host name (short or fully qualified domain name)
                     or host address in decimal dot notation.
                     If host is NULL, the local host is assumed.
              serv - Socket service name.
                     If serv is NULL, port number is used instead.
             proto - Socket service protocol, "tcp" or "udp".
                     Ignored if socket service name is NULL.
              port - TCP port number in host byte order (LSB first).
                     Ignored if socket service name is not NULL.
 
  Return value:  0 - Success
                -1 - Failure
============================================================================
*/

extern int TCPconnect(char *host, char *serv, unsigned short int port);

/*
----------------------------------------------------------------------------
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

extern int TCPlisten(char *serv, unsigned short int port, int qlim);

/*
----------------------------------------------------------------------------
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

extern int TCPaccept(int sock);

/*
----------------------------------------------------------------------------
  Accept an incoming connection

  Paraneters: sock - Listening socket file descriptor

  Return value: new_sock - New socket fd for accepted connection
                      -1 - Failure
============================================================================
*/

extern void TCPclose(int sock);

/*
----------------------------------------------------------------------------
  Shut down socket, remove references and locks.

  Parameters: sock - Socket file descriptor
============================================================================
*/
#endif /* _INET_UTILS_H */
