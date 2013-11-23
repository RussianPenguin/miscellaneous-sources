
#include "types.h"

/*
 * This program demonstrates some weaknesses in TPC 1.4 and TPC 1.5.  Unless
 * otherwise noted, all failed translations are in 1.4 and corrected in 1.5.
 *
 */ 

 /* program Test  */ 


   Integer      *vector = MK_FP(0x0000,0x03c4); 
                        /* absolute variables not translated in tpc 1.5 */ 

   Char         Ch; 
   Boolean      IbmAt; 
   Boolean      Control; 


  typedef char Longstring[256]; 

  typedef integer Lookup[7][2]; 
                        /* multi-dimension array declarations not translated
                           in tpc 1.5 */ 

  typedef integer NestedArray[7][2]; 
                        /* nested arrays not translated in tpc 1.5 */ 

  typedef char mytype1; 
  typedef byte mytype2; 
  typedef integer mytype3; 
  typedef char mytype4[81]; 

  typedef struct myrec { 
     longstring   astr; 
     real         areal; 
     integer      aint; 
     char         achar; 
  } myrec; 


  Lookup       tab   /*  this goes haywire here       */ 
                      = {{10, 824}, {9, 842}, {9, 858}, {9, 874}, 
                      {10, 890}, {9, 908}, {9, 924}}; 


void         InvVid(char *       m)  /* added */ 
{ 
   printf("%s\n",m); 
} 


void         call_a(void)
{ 
   char         s1[STRSIZ], s2[STRSIZ]; 

   strcpy(s1,"filename"); 
   sbld(s2,"#include \"%s\"  ",s1); 
} 


void         call_b(Integer      L,
                    Lookup       table)
{ 
   #define seg_addr 0x0040    /* constants added */ 
   #define filter_ptr 0x200  
   #define Vert '|'  
   #define Dbl  "=="  


  
/* Compiler: TEST.PAS(67): Error: Identifier expected (plvalue), tok=: */
  printf("%d",memw[filter_ptr] + 1); GotoXY 



