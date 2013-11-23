
#include "types.h"

/*
 * Example of multi-dimensional array manipulation
 */ 

 /* program Puzzle  */ 


  #define XSize 511    /*  d*d*d-1 */ 
  #define ClassMax 3  
  #define TypeMax 12  
  #define D    8  


  typedef int  /* 0..3 */ PieceClass; 
  typedef int  /* 0..12 */ PieceType; 
  typedef int  /* 0..511 */ Position; 


  int          /* 0..13 */ PieceCount[ /* PieceClass */ 4]; 
  PieceClass   Class[ /* PieceType */ 13]; 
  Position     PieceMax[ /* PieceType */ 13]; 
  Boolean      Puzzle[ /* Position */ 512]; 
  Boolean      P[ /* PieceType */ 13][ /* Position */ 512]; 
  Boolean      P2[ /* PieceType */ 13][ /* Position */ 512];   /* alternate form */ 
  Position     M, N; 
  int          /* 0..13 */ I, J, K; 
  Integer      Kount; 

  
Boolean      Fit(PieceType    I,
                 Position     J)
  { 
  
    Position     K; 
  
    return false; 
    for (K = 0; K <= PieceMax[I]; K++) 
      if (P[I][K]) 
        if (Puzzle[J + K]) 
          goto label_1;
    return true; 

label_1: 
  } 

  

Position     Place(PieceType    I,
                   Position     J)
  { 
    
  
    Position     K; 
  
    for (K = 0; K <= PieceMax[I]; K++) 
      if (P[I][K]) 
        Puzzle[J + K] = true; 
    PieceCount[Class[I]] = PieceCount[Class[I]] - 1; 
    for (K = J; K <= XSize; K++) 
      if (!Puzzle[K]) 
        { 
          return K; 
          goto label_1;
        } 
    printf("Puzzle filled\n"); 
    return 0; 

label_1: 
  } 

  

void         Remove(PieceType    I,
                    Position     J)
  { 
    Position     K; 
  
    for (K = 0; K <= PieceMax[I]; K++) 
      if (P[I][K]) 
        Puzzle[J + K] = false; 
    PieceCount[Class[I]] = PieceCount[Class[I]] + 1; 
  } 

  

Boolean      Trial(Position     J)
  { 
    PieceType    I; 
    Position     K; 
  
    for (I = 0; I <= TypeMax; I++) 
      if (PieceCount[Class[I]] != 0) 
        if (Fit(I,J)) 
          { 
            K = Place(I,J); 
            if (Trial(K) || (K == 0)) 
              { 
                  /* writeln( 'Piece', i + 1, ' at', k + 1); */ 
                return true; 
                return;
              } 
            else 
              Remove(I,J); 
          } 
    return false; 
    Kount = Kount + 1; 
  } 


void main(int argc,  char **argv)
{ 
  printf("Solving puzzle...\n"); 
  for (M = 0; M <= XSize; M++) 
    Puzzle[M] = true; 
  for (I = 1; I <= 5; I++) 
    for (J = 1; J <= 5; J++) 
      for (K = 1; K <= 5; K++) 
        Puzzle[I + D * (J + D * K)] = false; 

  for (I = 0; I <= TypeMax; I++) 
    for (M = 0; M <= XSize; M++) 
      P[I][M] = false; 

  for (I = 0; I <= 3; I++) 
    for (J = 0; J <= 1; J++) 
      for (K = 0; K <= 0; K++) 
        P[0][I + D * (J + D * K)] = true; 

  Class[0] = 0; 
  PieceMax[0] = 3 + D * 1 + D * D * 0; 
  for (I = 0; I <= 1; I++) 
    for (J = 0; J <= 0; J++) 
      for (K = 0; K <= 3; K++) 
        P[1][I + D * (J + D * K)] = true; 

  Class[1] = 0; 
  PieceMax[1] = 1 + D * 0 + D * D * 3; 
  for (I = 0; I <= 0; I++) 
    for (J = 0; J <= 3; J++) 
      for (K = 0; K <= 1; K++) 
        P[2][I + D * (J + D * K)] = true; 

  Class[2] = 0; 
  PieceMax[2] = 0 + D * 3 + D * D * 1; 
  for (I = 0; I <= 1; I++) 
    for (J = 0; J <= 3; J++) 
      for (K = 0; K <= 0; K++) 
        P[3][I + D * (J + D * K)] = true; 

  Class[3] = 0; 
  PieceMax[3] = 1 + D * 3 + D * D * 0; 
  for (I = 0; I <= 3; I++) 
    for (J = 0; J <= 0; J++) 
      for (K = 0; K <= 1; K++) 
        P[4][I + D * (J + D * K)] = true; 

  Class[4] = 0; 
  PieceMax[4] = 3 + D * 0 + D * D * 1; 
  for (I = 0; I <= 0; I++) 
    for (J = 0; J <= 1; J++) 
      for (K = 0; K <= 3; K++) 
        P[5][I + D * (J + D * K)] = true; 

  Class[5] = 0; 
  PieceMax[5] = 0 + D * 1 + D * D * 3; 
  for (I = 0; I <= 2; I++) 
    for (J = 0; J <= 0; J++) 
      for (K = 0; K <= 0; K++) 
        P[6][I + D * (J + D * K)] = true; 

  Class[6] = 1; 
  PieceMax[6] = 2 + D * 0 + D * D * 0; 
  for (I = 0; I <= 0; I++) 
    for (J = 0; J <= 2; J++) 
      for (K = 0; K <= 0; K++) 
        P[7][I + D * (J + D * K)] = true; 

  Class[7] = 1; 
  PieceMax[7] = 0 + D * 2 + D * D * 0; 
  for (I = 0; I <= 0; I++) 
    for (J = 0; J <= 0; J++) 
      for (K = 0; K <= 2; K++) 
        P[8][I + D * (J + D * K)] = true; 

  Class[8] = 1; 
  PieceMax[8] = 0 + D * 0 + D * D * 2; 
  for (I = 0; I <= 1; I++) 
    for (J = 0; J <= 1; J++) 
      for (K = 0; K <= 0; K++) 
        P[9][I + D * (J + D * K)] = true; 

  Class[9] = 2; 
  PieceMax[9] = 1 + D * 1 + D * D * 0; 
  for (I = 0; I <= 1; I++) 
    for (J = 0; J <= 0; J++) 
      for (K = 0; K <= 1; K++) 
        P[10][I + D * (J + D * K)] = true; 

  Class[10] = 2; 
  PieceMax[10] = 1 + D * 0 + D * D * 1; 
  for (I = 0; I <= 0; I++) 
    for (J = 0; J <= 1; J++) 
      for (K = 0; K <= 1; K++) 
        P[11][I + D * (J + D * K)] = true; 

  Class[11] = 2; 
  PieceMax[11] = 0 + D * 1 + D * D * 1; 
  for (I = 0; I <= 1; I++) 
    for (J = 0; J <= 1; J++) 
      for (K = 0; K <= 1; K++) 
        P[12][I + D * (J + D * K)] = true; 

  Class[12] = 3; 
  PieceMax[12] = 1 + D * 1 + D * D * 1; 
  PieceCount[0] = 13; 
  PieceCount[1] = 3; 
  PieceCount[2] = 1; 
  PieceCount[3] = 1; 
  M = 1 + D * (1 + D * 1); 
  Kount = 0; 

  if (Fit(0,M)) 
    N = Place(0,M); 
  else 
    printf(" error 1\n"); 

  if (Trial(N)) 
    printf(" success in %d trials\n",Kount); 
  else 
    printf(" failure\n"); 
}



