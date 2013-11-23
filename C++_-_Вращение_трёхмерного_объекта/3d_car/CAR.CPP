/* This program is made by Gaurav Dhup */
/* Please donot use the code without my permission */

/* For any queries or more 3D programs please visit

	 /*    www.question.chatbook.com    */

/* Visit my other 2 sites also  */

   /*   www.homepage.chatbook.com  &   www.bestofc.chatbook.com */


#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

# define pi 3.141592736

/* Used For Rotation */


float cosa,cosb,sina,sinb;

void ini(float cos1,float cos2)
{
 cosa=cos(cos1*pi/180);
 cosb=cos(cos2*pi/180);
 sina=sin(cos1*pi/180);
 sinb=sin(cos2*pi/180);
}

/* Converts 2D to 3D */

void plot(int x,int y,int z,int &x1,int &y1)
{
 x1=x*cosa-y*sina;
 y1=x*sina*sinb+y*cosa*sinb+z*cosb;
 x1=300+int(.5+x1);
 y1=240-int(.5+y1);
}

/* Plots 3D points */

void plot3d(int x,int y,int z,int col)
{
 int p,q;
 plot(x,y,z,p,q);
 putpixel(p,q,col);
}

/* Wheels of the car */

void plotout(int x,int y,int z)
{
 int p,q;
 plot(x,y,z,p,q);
 outtextxy(p,q,"");
}

void out(int x,int y,int z,int r)
{
 for(float xp=x-r;xp<x+r;xp+=1.5)
 {
  int t;
  plotout(xp,z,y-ceil(sqrt(r*r-(xp-x)*(xp-x))-y));
  plotout(xp,z,y+ceil(sqrt(r*r-(xp-x)*(xp-x))+y));
 }
}

void main()
 {
  int gd=DETECT,gm;
  initgraph(&gd,&gm,"c:\\tc\\bgi");
  int p=0;
  randomize();
  while(!kbhit())
  {
  ini(p,p);
  static int x[40];
  static int y[40];
  plot(-60,0,1,x[0],y[0]);
  plot(25,5,1,x[1],y[1]);
  plot(-60,100,1,x[3],y[3]);
  plot(25,95,1,x[4],y[4]);
  plot(-40,0,35,x[2],y[2]);
  plot(-40,100,35,x[6],y[6]);
  plot(40,95,45,x[7],y[7]);
  plot(120,95,80,x[8],y[8]);
  plot(225,95,80,x[9],y[9]);
  plot(40,5,45,x[10],y[10]);
  plot(120,5,80,x[11],y[11]);
  plot(225,5,80,x[12],y[12]);
  plot(285,5,45,x[13],y[13]);
  plot(285,95,45,x[14],y[14]);
  plot(330,95,45,x[15],y[15]);
  plot(330,5,45,x[16],y[16]);
  plot(330,95,1,x[17],y[17]);
  plot(330,5,1,x[18],y[18]);
  plot(25,5,1,x[19],y[19]);
  plot(50,5,25,x[20],y[20]);
  plot(80,5,25,x[21],y[21]);
  plot(105,5,1,x[22],y[22]);
  plot(210,5,1,x[23],y[23]);
  plot(235,5,25,x[24],y[24]);
  plot(265,5,25,x[25],y[25]);
  plot(290,5,1,x[26],y[26]);
  plot(25,95,1,x[27],y[27]);
  plot(50,95,25,x[28],y[28]);
  plot(80,95,25,x[29],y[29]);
  plot(105,95,1,x[30],y[30]);
  plot(210,95,1,x[31],y[31]);
  plot(235,95,25,x[32],y[32]);
  plot(265,95,25,x[33],y[33]);
  plot(290,95,1,x[34],y[34]);
  plot(120,5,45,x[35],y[35]);
  plot(120,95,45,x[36],y[36]);
  plot(225,5,45,x[37],y[37]);
  plot(225,95,45,x[38],y[38]);

  /* Body of the car */

  setcolor(9);     //COLORS
  line(x[3],y[3],x[4],y[4]);
  line(x[1],y[1],x[4],y[4]);
  line(x[0],y[0],x[3],y[3]);
  line(x[0],y[0],x[1],y[1]);
  line(x[0],y[0],x[2],y[2]);
  line(x[3],y[3],x[6],y[6]);
  line(x[6],y[6],x[7],y[7]);
  line(x[7],y[7],x[8],y[8]);
  line(x[8],y[8],x[9],y[9]);
  line(x[6],y[6],x[2],y[2]);
  line(x[2],y[2],x[10],y[10]);
  line(x[10],y[10],x[11],y[11]);
  line(x[11],y[11],x[12],y[12]);
  line(x[12],y[12],x[13],y[13]);
  line(x[9],y[9],x[14],y[14]);
  line(x[14],y[14],x[15],y[15]);
  line(x[13],y[13],x[16],y[16]);
  line(x[15],y[15],x[17],y[17]);
  line(x[16],y[16],x[18],y[18]);
  line(x[16],y[16],x[15],y[15]);
  line(x[9],y[9],x[12],y[12]);
  line(x[7],y[7],x[10],y[10]);
  line(x[6],y[6],x[2],y[2]);
  line(x[7],y[7],x[14],y[14]);
  line(x[10],y[10],x[13],y[13]);
  line(x[8],y[8],x[11],y[11]);
  line(x[19],y[19],x[20],y[20]);
  line(x[20],y[20],x[21],y[21]);
  line(x[21],y[21],x[22],y[22]);
  line(x[23],y[23],x[24],y[24]);
  line(x[24],y[24],x[25],y[25]);
  line(x[25],y[25],x[26],y[26]);
  line(x[17],y[17],x[18],y[18]);
  line(x[27],y[27],x[28],y[28]);
  line(x[28],y[28],x[29],y[29]);
  line(x[29],y[29],x[30],y[30]);
  line(x[31],y[31],x[32],y[32]);
  line(x[32],y[32],x[33],y[33]);
  line(x[33],y[33],x[34],y[34]);
  line(x[30],y[30],x[31],y[31]);
  line(x[22],y[22],x[23],y[23]);
  line(x[34],y[34],x[17],y[17]);
  line(x[26],y[26],x[18],y[18]);
  line(x[26],y[26],x[34],y[34]);
  line(x[22],y[22],x[23],y[23]);
  line(x[22],y[22],x[30],y[30]);
  line(x[23],y[23],x[31],y[31]);
  line(x[13],y[13],x[14],y[14]);
  line(x[23],y[23],x[31],y[31]);
  line(x[13],y[13],x[14],y[14]);
  line(x[11],y[11],x[35],y[35]);
  line(x[8],y[8],x[36],y[36]);
  line(x[38],y[38],x[9],y[9]);
  line(x[12],y[12],x[37],y[37]);
  out(67,-3,100,25);
  out(251,-3,100,25);
  out(67,-3,10,25);
  out(251,-3,10,25);
  out(115,15,10,1);
  out(135,15,10,1);
  out(155,15,10,1);
  out(175,15,10,1);
  out(195,15,10,1);
  out(115,15,100,1);
  out(135,15,100,1);
  out(155,15,100,1);
  out(175,15,100,1);
  out(195,15,100,1);
  p+=2;
  delay(10);
  cleardevice();
 }
}


