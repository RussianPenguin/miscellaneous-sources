
#include "types.h"

/*
 *   Ackerman function
 */ 

 /* program Acker  */ 


  integer      R; 

  
integer      A(integer      M,
               integer      N)
  { 
    if (M == 0) 
      return N + 1; 
    else 
      if (N == 0) 
        return A(M - 1,1); 
      else 
        return A(M - 1,A(M,N - 1)); 
  } 


void main(int argc,  char **argv)
{ 
  printf("Ackerman function...\n"); 
  R = A(3,6); 
  printf("finished, R=%d\n",R); 
}



