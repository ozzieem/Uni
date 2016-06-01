#include "qrb.h"

/** \struct qrb
    \brief Ring buffert queue.
*/

/** \ingroup qrb
    Init of the ring buffert queue. The buffert element is a character.
  */
void qrbInit(qrb *o)
{
  o->wrPtr=0;
  o->rdPtr=0;
} 
 
/** \ingroup qrb
    Test if the ring buffert queue is empty or not.
    \param o Object pointer to the ring buffert.
    \return True if the queue is empty otherwise false.
  */
int qrbEmpty(qrb *o)
{ 
  return (o->wrPtr == o->rdPtr); 
}

/** \ingroup qrb
    Test if the ring buffert queue is full or not.
    \param o Object pointer to the ring buffert.
    \return True if the queue is full otherwise false.
  */
int qrbFull(qrb *o)
{
  int d=o->wrPtr - o->rdPtr;
   
  if ( d < 0 )
  { d=QRB_SIZE+d; }
  
  return d == (QRB_SIZE-1);
}


/** \ingroup qrb
    Write of a character to the ring buffert. The write is done only if the queue is not full.
    \param o Object pointer to the ring buffert.
    \param c Character to be passed to the ring buffer.
  */
void qrbEnqueue(qrb *o, char c)
{
  asm("cli");
  if ( ! qrbFull(o) )
  {    
    o->b[(int)o->wrPtr]=c;
	o->wrPtr = (o->wrPtr + 1) & QRB_MASK;  
  }/*if*/ 
  asm("sei");
}

/** \ingroup qrb
    Write of a character to the ring buffert. The write is done only if the queue is not full.
    \param o Object pointer to the ring buffert.
    \param c Character to be passed to the ring buffer.
  */
void qrbEnqueueIsr(qrb *o, char c)
{
  
  if ( ! qrbFull(o) )
  {   
    o->b[(int)o->wrPtr]=c;
	o->wrPtr = (o->wrPtr + 1) & QRB_MASK;  
  }/*if*/ 
}

/** \ingroup qrb
    Read of a character from the ring buffert queue.
    \param o Object pointer to the ring buffert.
    \return The character read, if the queue is empty the return value is -1.
  */
int qrbDequeue(qrb *o)
{   
  asm("cli");
  int c=-1; 
  if ( ! qrbEmpty(o) )
  { 
    c = o->b[(int)o->rdPtr];
    o->rdPtr = (o->rdPtr + 1) & QRB_MASK;      
  } /*if*/
  asm("sei");
  return c;
}

/** \ingroup qrb
    Read of a character from the ring buffert queue.
    \param o Object pointer to the ring buffert.
    \return The character read, if the queue is empty the return value is -1.
  */
int qrbDequeueIsr(qrb *o)
{   
  
  int c=-1; 
  if ( ! qrbEmpty(o) )
  { 
    c = o->b[(int)o->rdPtr];
    o->rdPtr = (o->rdPtr + 1) & QRB_MASK;      
  } /*if*/
  
  return c;
}

/** \ingroup qrb
    Check if a specified character can be found in the queue.
    \param o Object pointer to the ring buffert.
    \param c Search buffert for the character.
    \return True if the character is found else false
  */
int qrbFindCharacter(qrb *o, char c)
{   
  volatile char wrPtr = o->wrPtr;
  volatile char rdPtr = o->rdPtr;

  while ( wrPtr != rdPtr )
  { 
  	 if ( c == o->b[(int)rdPtr] ) 
	 	return 1; 
	 rdPtr = (rdPtr+1) & QRB_MASK;
  } 

  return 0;
}

