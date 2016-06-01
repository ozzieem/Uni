#ifndef _QRB_H
#define _QRB_H

//Size = 2^N, 
#define QRB_SIZE (128)
#define QRB_MASK (QRB_SIZE-1)

typedef struct
{                 
  volatile char wrPtr;    /*Write pointer*/
  volatile char rdPtr;    /*Read pointer*/
  char b[QRB_SIZE];       /*Character buffert*/
} qrb;
 
void qrbInit(qrb *o);
 int qrbEmpty(qrb *o);
 int qrbFull(qrb *o);
void qrbEnqueue(qrb *o, char c);
void qrbEnqueueIsr(qrb *o, char c);
 int qrbDequeue(qrb *o);
 int qrbDequeueIsr(qrb *o);
 int qrbFindCharacter(qrb *o, char c);
#endif
