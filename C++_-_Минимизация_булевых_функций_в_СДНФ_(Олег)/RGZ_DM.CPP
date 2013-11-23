#include <stdio.h>
#include <conio.h>
#include <mem.h>
#include <alloc.h>
#include <stdlib.h>
#define MAXLET 10
typedef struct
  { 
    char NUM[MAXLET];
    char INV[MAXLET];                     
    char PRIZNAK;
    char *next;
  } conjun;

conjun *PutInMemory(int N,int k)
{
  int i;
  conjun *p;
  p = new conjun;
  for(i=k-1;i>=0;i--)
  {
    if(N % 2 ==0) p->INV[i] = 1;
    else p->INV[i] = 0;
    N/=2;
    p->NUM[i] = 1;
  }
  for(i=MAXLET-1;i>=k;i--)
    p->NUM[i] = 0;
  p->PRIZNAK = 0;
  return p;
}

int ReadFile(char *s,conjun **start)
{
  FILE *f;
  int Z,KOL,N=0,i=0;
  conjun *p=NULL,*start_DNF=NULL;
  f = fopen("SOURCE.txt","rt");
  fscanf(f,"%d",&KOL);
  while(!feof(f))
  {
   fscanf(f,"%d",&Z);
   if(Z==1)
   {
     if(start_DNF==0)
     {
       start_DNF = PutInMemory(N,KOL);
       p = start_DNF;
     }
     else
     {
       p->next = (char *)PutInMemory(N,KOL);
       p = (conjun *)p->next;
     }
   }
   N++;
  }
  if(p!=NULL) p->next = NULL;
  *start = start_DNF;
  return KOL;
}

int ConjIn(conjun *p,conjun *start)
{
  int i,flag=0;
  while(start!=NULL)
  {
    for(i=0;i<=MAXLET-1 && p->NUM[i]==start->NUM[i];i++)
    {
	    if(p->NUM[i]==1)
	      if(p->INV[i]!=start->INV[i])
          break;
    }
	  if (i==MAXLET)
      return 1;
	  start = (conjun *)start->next;
  }
  return 0;
}

conjun *Sklej(conjun *p1,conjun *p2,int k)
{
  int i,j=0,k1=0,k2=0,flag=0;
  conjun *p;
  for(i=0;i<=MAXLET-1;i++)
  {
    if(p1->NUM[i]==1 && p2->NUM[i]==1)
      if(p1->INV[i]==p2->INV[i])
        j++;
      else
        flag = 1;
    if(p1->NUM[i]==1) k1++;
    if(p2->NUM[i]==1) k2++;
  }	
  if(k-1==j && k1==k2 && k1==k && flag==1)
  {
    if(k==1)
    {
      printf("\n\nF=1");
      getch();
      exit(0);
    }
    p = new conjun;
    for(i=0;i<=MAXLET-1;i++)
      if(p1->INV[i]==p2->INV[i] && p1->NUM[i]==1 && p2->NUM[i]==1)
      {
        p->INV[i] = p1->INV[i];
        p->NUM[i] = 1;
      }
      else p->NUM[i] = 0;
    p->PRIZNAK = 0;
    p1->PRIZNAK = 1;
    p2->PRIZNAK = 1;
	  p->next = NULL;
    return p;
  }
  return NULL;
}

conjun *Shorting(conjun *start_DNF,int k)
{
  int i = 0;
  conjun *p=NULL,*p1,*p2,*start_SDNF=NULL,*r;
  p1 = start_DNF;
  while(p1->next!=NULL)
  {
    p2 = (conjun *)p1->next;
    while(p2!=NULL)
    {
      if(start_SDNF==NULL)
      {
		    start_SDNF = Sklej(p1,p2,k);
		    p = start_SDNF;
      }
      else
      {
		    r = Sklej(p1,p2,k);
		    if(r!=NULL)
		      if(ConjIn(r,start_SDNF)!=0)
		      {
		        delete r;
		        r = NULL;
		      }
		    if(r!=NULL)
		    {
		      p->next = (char *)r;
		      p = (conjun *)p->next;
		    }
      }
      p2 = (conjun *)p2->next;
    }
    p1 = (conjun *)p1->next;
  }
  p1 = start_DNF;
  while(p1!=NULL)
  {
    if(p1->PRIZNAK==0)
    {
      if(p==NULL)
      {
	      p = new conjun;
	      start_SDNF = p;
	      memcpy(p,p1,sizeof(conjun));
      }
      else
      {
	 	    p->next = (char *)new conjun;
		    memcpy(p->next,p1,sizeof(conjun));
		    p = (conjun *)p->next;
      }
    }
    p1 = (conjun *)p1->next;
  }
  p->next = NULL;
  return start_SDNF;
}

int is_input(conjun *p1,conjun *p2)
{
  int i;
  for(i=0;i<=MAXLET-1;i++)
    if(p1->NUM[i]==p2->NUM[i] && p1->NUM[i]==1)
      if(p1->INV[i]!=p2->INV[i])
        return 0;
  return 1;
}

char **CreateMatrix(conjun *start_DNF,conjun *start_SDNF,int *ROW,int *COL)
{
  int i,j,k;
  char **m;
  conjun *DNF,*SDNF;
  DNF = start_DNF;
  SDNF = start_SDNF;
  for(i=0;SDNF->next!=NULL;i++)
    SDNF = (conjun *)SDNF->next;
  for(j=0;DNF->next!=NULL;j++)
    DNF = (conjun *)DNF->next;
  m = (char **)malloc(i*2);
  for(k=0;k<=i;k++)
    m[k] = (char *)malloc(j*2);
  SDNF = start_SDNF;
  for(i=0;SDNF!=NULL;i++)
  {
    DNF = start_DNF;
    for(j=0;DNF!=NULL;j++)
    {
      m[i][j] = is_input(DNF,SDNF);
      DNF = (conjun *)DNF->next;
    }
    SDNF = (conjun *)SDNF->next;
  }
  *ROW = i;
  *COL = j;
  return m;
}

void Sochet(int N,int K,char *C)
{
  int i,j;
  j = K;
  while(C[j]>=N-K+j)
    j--;
  C[j]++;
  for(i=j+1;i<=K;i++)
    C[i] = C[i-1]+1;
}

conjun **CreateTDNF(conjun *start_SDNF,char **m,int ROW,int COL)
{
  char *C;
  int i,j,k,l=0;
  conjun **Array_TDNF,*start_TDNF=NULL,*p,*r;
  C = (char *)malloc(ROW+1);
  Array_TDNF = (conjun **)malloc(1000);
  for(k=1;k<=ROW-1 && start_TDNF==NULL;k++)
  {  
    for(i=1;i<=k;i++) C[i] = i;C[0] = -1;
    while(C[0]!=0)
    {
      i = 0;
      for(j=0;j<=COL-1 && i!=k+1;j++)
        for(i=1;i<=k && m[C[i]-1][j]==0;)
          i++;
      if(j==COL && i!=k+1)
      {
	      i = 1;
	      r = start_SDNF;
	      for(j=0;r!=NULL;j++)
	      {
	        if(j==C[i]-1)
	        {
	          if(i==1)
	          {
	            start_TDNF = new conjun;
	            p = start_TDNF;
	            memcpy(p,start_SDNF,sizeof(conjun));
	          }
	          else
	          {
	            p->next = (char *)new conjun;
	            memcpy(p->next,r,sizeof(conjun));
	            p = (conjun *)p->next;
	          }
	          i++;
	          p->next = NULL;
	        }
	        r = (conjun *)r->next;
	      }
	      Array_TDNF[l++] = start_TDNF;	
        }
      Sochet(ROW,k,C);
    }
  }
  Array_TDNF[l] = 0;
  if(Array_TDNF[0]==0)
    return 0;
  else
    return Array_TDNF;
}

void OtputDNF(conjun *p)
{
  int i,x,y;
  printf("\n\nF=");
  if(p==NULL)
  {
    printf("0");
    getch();
    exit(0);
  }
  while(p!=NULL)
  {
    for(i=0;i<=MAXLET-1;i++)
    {
      if(p->NUM[i]==1)
      {
        printf("X%d",i+1);
        if(p->INV[i]==1)
        {
	        x=wherex();y=wherey();
	        gotoxy(x-2,y-1);
	        printf("__");
	        gotoxy(x,y);
        }
      }
    }
    x=wherex();y=wherey();
    if(x>=75-MAXLET)
      gotoxy(1,y+2);
    printf("\\/");
    p = (conjun *)p->next;
  }
  x=wherex();
  y=wherey();
  gotoxy(x-2,y);
  printf("  ");
}

void main(void)
{
  clrscr();
  int i,j,KOL,ROW,COL;
  char **m;
  conjun *start_SDNF,*start_DNF,**start_TDNF,*p;
  KOL = ReadFile("  ",&start_DNF);
  OtputDNF(start_DNF);
  start_SDNF = start_DNF;
  for(i=KOL;i>=1;i--)
  {
    start_SDNF = Shorting(start_SDNF,i);
    OtputDNF(start_SDNF);
    getch();
  }
  m = CreateMatrix(start_DNF,start_SDNF,&ROW,&COL);
  printf("\n");
  for(i=0;i<=ROW-1;i++)
  {
    printf("\n");
    for(j=0;j<=COL-1;j++)
      printf("%d ",m[i][j]);
  }
  getch();
  start_TDNF = CreateTDNF(start_SDNF,m,ROW,COL);
  if(start_TDNF!=NULL)
  {
    for(i=0;start_TDNF[i]!=0;i++)
    { 
      OtputDNF(start_TDNF[i]);
      getch();
    } 
  }
}