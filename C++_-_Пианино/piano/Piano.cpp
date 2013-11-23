/*------------------------------------------------------------------------*/
/*			           PIANO                                  */
/*------------------------------------------------------------------------*/
/*                    SOURCE CODE WRITTEN BY GAURAV DHUP                  */
/*		          www.question.chatbook.com    			  */
/*  DATE:  14/11/99                                                       */
/*------------------------------------------------------------------------*/

/* HEADER FILES */

#include<graphics.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<dos.h>

/*FUNCTION TITLE FOR PIANO */

void title()
   {
       /* DISPLAY PIANO */

       settextstyle(4,0,10);
       setcolor(9);
       outtextxy(100,1,"P");
       settextstyle(4,0,10);
       setcolor(11);
       outtextxy(170,1,"I");
       settextstyle(4,0,10);
       setcolor(14);
       outtextxy(240,1,"A");
       settextstyle(4,0,10);
       setcolor(13);
       outtextxy(340,1,"N");
       settextstyle(4,0,10);
       setcolor(10);
       outtextxy(430,1,"O");
       settextstyle(3,1,1);
       setcolor(14);
       outtextxy(600,70,"Copyright 1999-2000 GAURAV CREATIONS");

       /* START OF WHITE BARS */

       setcolor(15);
       setfillstyle(SOLID_FILL,15);
       bar3d(60,180,85,310,6,7);
       bar3d(90,180,115,310,6,7);
       bar3d(120,180,145,310,6,7);
       bar3d(150,180,175,310,6,7);
       bar3d(180,180,205,310,6,7);
       bar3d(210,180,235,310,6,7);
       bar3d(240,180,265,310,6,7);
       bar3d(270,180,295,310,6,7);
       bar3d(300,180,325,310,6,7);
       bar3d(330,180,355,310,6,7);
       bar3d(360,180,385,310,6,7);
       bar3d(390,180,415,310,6,7);
       bar3d(420,180,445,310,6,7);
       bar3d(450,180,475,310,6,7);
       bar3d(480,180,505,310,6,7);
       bar3d(510,180,535,310,6,7);

       /* END OF WHITE BARS */

       /* START OF BLACK BARS */

       setcolor(0);
       setfillstyle(SOLID_FILL,0);
       bar3d(75,180,95,250,6,7);
       bar3d(105,180,125,250,6,7);
       bar3d(135,180,155,250,6,7);
       bar3d(165,180,185,250,6,7);
       bar3d(195,180,215,250,6,7);
       bar3d(225,180,245,250,6,7);
       bar3d(255,180,275,250,6,7);
       bar3d(285,180,305,250,6,7);
       bar3d(315,180,335,250,6,7);
       bar3d(345,180,365,250,6,7);
       bar3d(375,180,395,250,6,7);
       bar3d(405,180,425,250,6,7);
       bar3d(435,180,455,250,6,7);
       bar3d(465,180,485,250,6,7);
       bar3d(495,180,515,250,6,7);

       /* END OF BLACK BARS */

       settextstyle(2,0,7);
       setcolor(11);
       outtextxy(5,390,"PRESS '+' FOR HELP");
       settextstyle(1,0,3);
       setcolor(12);
       outtextxy(5,430,"RECORDING (press 'SPC BAR' to PLAY)");

  }//end of title

/* FUNCTION PLAY FOR PIANO */

void play(char c)
 {
  c=tolower(c);
  setcolor(15);

  /* 32 KEYS FOR PIANO */

  if(c=='a')
    {
     sound(256);
     setfillstyle(SOLID_FILL,0);
     bar3d(60,180,85,310,6,7);
     delay(110);
     setcolor(15);
     setfillstyle(SOLID_FILL,15);
     bar3d(60,180,85,310,6,7);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(75,180,95,250,6,7);
     nosound();
    }
  if(c=='s')
    {
     sound(288);
     setfillstyle(SOLID_FILL,0);
     bar(90,250,115,310);
     delay(110);
     setcolor(15);
     setfillstyle(SOLID_FILL,15);
     bar(90,250,115,310);
     nosound();
    }
  if(c=='d')
    {
     sound(320);
     setfillstyle(SOLID_FILL,0);
     bar(120,250,145,310);
     delay(110);
     setcolor(15);
     setfillstyle(SOLID_FILL,15);
     bar(120,250,145,310);
     nosound();
    }
  if(c=='f')
    {
     sound(344);
     setfillstyle(SOLID_FILL,0);
     bar(150,250,175,310);
     delay(110);
     setcolor(15);
     setfillstyle(SOLID_FILL,15);
     bar(150,250,175,310);
     nosound();
    }
  if(c=='g')
    {
     sound(384);
     setfillstyle(SOLID_FILL,0);
     bar(180,250,205,310);
     delay(110);
     setcolor(15);setfillstyle(SOLID_FILL,15);
     bar(180,250,205,310);
     nosound();
    }
  if(c=='h')
    {
     sound(427);
     setfillstyle(SOLID_FILL,0);
     bar(210,250,235,310);
     delay(110);
     setcolor(15);
     setfillstyle(SOLID_FILL,15);
     bar(210,250,235,310);
     nosound();
    }
  if(c=='j')
    {
     sound(480);
     setfillstyle(SOLID_FILL,0);
     bar(240,250,265,310);
     delay(110);
     setcolor(15);
     setfillstyle(SOLID_FILL,15);
     bar(240,250,265,310);
     nosound();
    }
  if(c=='k')
    {
     sound(512);
     setfillstyle(SOLID_FILL,0);
     bar(270,250,295,310);
     delay(110);
     setcolor(15);
     setfillstyle(SOLID_FILL,15);
     bar(270,250,295,310);
     nosound();
    }
  if(c=='l')
    {
     sound(640);
     setfillstyle(SOLID_FILL,0);
     bar(300,250,325,310);
     delay(110);
     setcolor(15);
     setfillstyle(SOLID_FILL,15);
     bar(300,250,325,310);
     nosound();
    }
  if(c=='z')
    {
     sound(720);
     setfillstyle(SOLID_FILL,0);
     bar(330,250,355,310);
     delay(110);
     setcolor(15);
     setfillstyle(SOLID_FILL,15);
     bar(330,250,355,310);
     nosound();
    }
  if(c=='x')
    {
     sound(800);
     setfillstyle(SOLID_FILL,0);
     bar(360,250,385,310);
     delay(110);
     setcolor(15);
     setfillstyle(SOLID_FILL,15);
     bar(360,250,385,310);
     nosound();
    }
  if(c=='c')
    {
     sound(860);
     setfillstyle(SOLID_FILL,0);
     bar(390,250,415,310);
     delay(110);
     setcolor(15);
     setfillstyle(SOLID_FILL,15);
     bar(390,250,415,310);
     nosound();
    }
  if(c=='v')
    {
     sound(960);
     setfillstyle(SOLID_FILL,0);
     bar(420,250,445,310);
     delay(110);
     setcolor(15);
     setfillstyle(SOLID_FILL,15);
     bar(420,250,445,310);
     nosound();
    }
  if(c=='b')
    {
     sound(1068);
     setfillstyle(SOLID_FILL,0);
     bar(450,250,475,310);
     delay(110);
     setcolor(15);
     setfillstyle(SOLID_FILL,15);
     bar(450,250,475,310);
     nosound();
    }
  if(c=='n')
    {
     sound(1200);
     setfillstyle(SOLID_FILL,0);
     bar(480,250,505,310);
     delay(110);
     setcolor(15);
     setfillstyle(SOLID_FILL,15);
     bar(480,250,505,310);
     nosound();
    }
  if(c=='m')
    {
     sound(1280);
     setfillstyle(SOLID_FILL,0);
     bar3d(510,180,535,310,6,7);
     delay(110);
     setcolor(15);
     setfillstyle(SOLID_FILL,15);
     bar3d(510,180,535,310,6,7);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(495,180,515,250,6,7);
     nosound();
    }
  if(c=='1')
    {
     sound(768);
     setfillstyle(SOLID_FILL,15);
     bar3d(75,180,95,250,6,7);
     delay(110);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(75,180,95,250,6,7);
     nosound();
    }
  if(c=='2')
    {
     sound(864);
     setfillstyle(SOLID_FILL,15);
     bar3d(105,180,125,250,6,7);
     delay(110);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(105,180,125,250,6,7);
     nosound();
    }
  if(c=='3')
    {
     sound(960);
     setfillstyle(SOLID_FILL,15);
     bar3d(135,180,155,250,6,7);
     delay(110);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(135,180,155,250,6,7);
     nosound();
    }
  if(c=='4')
    {
     sound(1032);
     setfillstyle(SOLID_FILL,15);
     bar3d(165,180,185,250,6,7);
     delay(110);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(165,180,185,250,6,7);
     nosound();
    }
  if(c=='5')
    {
     sound(1152);
     setfillstyle(SOLID_FILL,15);
     bar3d(195,180,215,250,6,7);
     delay(110);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(195,180,215,250,6,7);
     nosound();
    }
  if(c=='6')
    {
     sound(1281);
     setfillstyle(SOLID_FILL,15);
     bar3d(225,180,245,250,6,7);
     delay(110);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(225,180,245,250,6,7);
     nosound();
    }
  if(c=='7')
    {
     sound(1440);
     setfillstyle(SOLID_FILL,15);
     bar3d(255,180,275,250,6,7);
     delay(110);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(255,180,275,250,6,7);
     nosound();
    }
  if(c=='8')
    {
     sound(1536);
     setfillstyle(SOLID_FILL,15);
     bar3d(285,180,305,250,6,7);
     delay(110);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(285,180,305,250,6,7);
     nosound();
    }
  if(c=='9')
    {
     sound(1024);
     setfillstyle(SOLID_FILL,15);
     bar3d(315,180,335,250,6,7);
     delay(110);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(315,180,335,250,6,7);
     nosound();
    }
  if(c=='0')
    {
     sound(1152);
     setfillstyle(SOLID_FILL,15);
     bar3d(345,180,365,250,6,7);
     delay(110);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(345,180,365,250,6,7);
     nosound();
    }
  if(c=='q')
    {
     sound(1280);
     setfillstyle(SOLID_FILL,15);
     bar3d(375,180,395,250,6,7);
     delay(110);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(375,180,395,250,6,7);
     nosound();
    }
  if(c=='w')
    {
     sound(1376);
     setfillstyle(SOLID_FILL,15);
     bar3d(405,180,425,250,6,7);
     delay(110);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(405,180,425,250,6,7);
     nosound();
    }
  if(c=='e')
    {
     sound(1536);
     setfillstyle(SOLID_FILL,15);
     bar3d(435,180,455,250,6,7);
     delay(110);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(435,180,455,250,6,7);
     nosound();
    }
  if(c=='r')
    {
     sound(1708);
     setfillstyle(SOLID_FILL,15);
     bar3d(465,180,485,250,6,7);
     delay(110);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(465,180,485,250,6,7);
     nosound();
    }
  if(c=='t')
    {
     sound(1920);
     setfillstyle(SOLID_FILL,15);
     bar3d(495,180,515,250,6,7);
     delay(110);
     setcolor(0);
     setfillstyle(SOLID_FILL,0);
     bar3d(495,180,515,250,6,7);
     nosound();
    }
  if(c=='y')
    {
     sound(2048);
     delay(110);
     nosound();
    }
  }//end of play

/************************* END OF KEYS FOR PIANO ***************************/

 void main()
   {
       FILE *fp,*ft;
       char c;
       int driver,mode;
       driver=DETECT;
       initgraph(&driver,&mode,"\\tc\\bgi");
       title();
       ft=fopen("SONG.PNO","w"); /* FILE FOR TEMPORARY RECORDING */
       do
	{
	 c=getch();
	 setcolor(15);
	 play(c);
	 fputc(c,ft);

	 /* SPC BAR TO START PLAYING */

	 if(c==32)
	   {
	    fclose(ft);
	    settextstyle(1,0,3);
	    setcolor(0);
	    outtextxy(5,430,"RECORDING (press 'SPC BAR' to PLAY)");
	    settextstyle(1,0,5);
	    setcolor(10);
	    outtextxy(5,430,"PLAYING...");
	    setcolor(15);
	    ft=fopen("SONG.PNO","r");
	    do
	     {
	      c=fgetc(ft);
	      play(c);
	      delay(100);
	     }while(c!=EOF);
	    fclose(ft);
	    settextstyle(1,0,5);
	    setcolor(0);
	    outtextxy(5,430,"PLAYING...");
	    settextstyle(1,0,3);
	    setcolor(12);
	    outtextxy(5,430,"RECORDING (press 'SPC BAR' to PLAY)");
	    settextstyle(1,0,5);
	    setcolor(15);
	    ft=fopen("SONG.PNO","a"); /* START WRITING AGAIN */
	   }

	 /* INITIALIZE RECORDING TO START FROM BEGINNING */

	 if(c=='*')
	   {
	    fclose(ft);
	    ft=fopen("SONG.PNO","w");
	   }

	 /* RECORD SONG */

	 if(c=='/')
	   {
	    fclose(ft);
	    char *f;
	    cleardevice();
	    settextstyle(1,0,6);
	    setcolor(14);
	    outtextxy(100,140,"NAME YOUR SONG");
	    gotoxy(30,15);
	    scanf("%s",f);
	    fp=fopen(f,"w");
	    cleardevice();
	    title();
	    settextstyle(2,0,7);
	    setcolor(0);
	    outtextxy(5,390,"PRESS '+' FOR HELP");
	    settextstyle(1,0,3);
	    setcolor(0);
	    outtextxy(5,430,"RECORDING (press 'SPC BAR' to PLAY)");
	    setcolor(12);
	    setusercharsize(1.4,1,1,1);
	    outtextxy(5,390,"RECORDING SONG ");
	    setcolor(9);
	    outtextxy(275,390,f);
	    do
	     {
	      c=getch();
	      play(c);
	      fputc(c,fp);
	     }while(c!='.');
	    setcolor(0);
	    setusercharsize(1.4,1,1,1);
	    outtextxy(5,390,"RECORDING SONG ");
	    outtextxy(275,390,f);
	    setcolor(12);
	    setusercharsize(1.4,1,1,1);
	    outtextxy(5,390,"CLOSING SONG ");
	    setcolor(9);
	    outtextxy(235,390,f);
	    fclose(fp);
	    delay(500);
	    setcolor(0);
	    setusercharsize(1.4,1,1,1);
	    outtextxy(5,390,"CLOSING SONG ");
	    outtextxy(235,390,f);
	    title();
	   }

	 /* LISTEN TO SONGS */

	 if(c==',')
	   {
	    fclose(ft);
	    char *f;
	    SONG:cleardevice(); /* GOTO STATEMENT IF SONG NOT FOUND */
	    settextstyle(1,0,3);
	    setcolor(14);
	    outtextxy(90,140,"WHICH SONG DO YOU WANT TO LISTEN TO");
	    gotoxy(30,15);
	    scanf("%s",f);
	    fp=fopen(f,"r");
	    if(fp==NULL)
	      {
	       fclose(fp);
	       cleardevice();
	       setcolor(12);
	       setusercharsize(2,1,1,1);
	       outtextxy(60,200,"SONG NOT FOUND");
	       sound(200);
	       delay(200);
	       nosound();
	       delay(1000);
	       goto SONG;
	      }
	    cleardevice();
	    title();
	    settextstyle(2,0,7);
	    setcolor(0);
	    outtextxy(5,390,"PRESS '+' FOR HELP");
	    settextstyle(1,0,3);
	    setcolor(0);
	    outtextxy(5,430,"RECORDING (press 'SPC BAR' to PLAY)");
	    setcolor(10);
	    setusercharsize(1.4,1,1,1);
	    outtextxy(5,390,"PLAYING SONG ");
	    setcolor(9);
	    outtextxy(235,390,f);
	    do
	     {
	      c=fgetc(fp);
	      play(c);
	      delay(100);
	     }while(c!=EOF);
	    fclose(fp);
	    setcolor(0);
	    setusercharsize(1.4,1,1,1);
	    outtextxy(5,390,"PLAYING SONG ");
	    outtextxy(235,390,f);
	    setcolor(12);
	    setusercharsize(1.4,1,1,1);
	    outtextxy(5,390,"CLOSING SONG ");
	    setcolor(9);
	    outtextxy(235,390,f);
	    delay(500);
	    setcolor(0);
	    setusercharsize(1.4,1,1,1);
	    outtextxy(5,390,"CLOSING SONG ");
	    outtextxy(235,390,f);
	    title();
	   }

	 /* HELP SCREEN */

	 if(c=='+')
	   {
	    cleardevice();
	    setbkcolor(0);
	    setcolor(14);
	    settextstyle(1,0,6);
	    outtextxy(190,20,"KEYS USED");
	    settextstyle(1,0,3);
	    setcolor(LIGHTGREEN);
	    outtextxy(1,120,"Spc bar ------------Play temporary recorded Song");
	    outtextxy(1,160,"* ----------------Erase temporary recorded Song");
	    outtextxy(1,200,"/ --------------------------------Save Song");
	    outtextxy(1,240,". ------------------Closing Song After Recording");
	    outtextxy(1,280,", -----------------------Listen Recorded Songs");
	    outtextxy(1,320,"Esc -----------------------------------QUIT");
	    getch();
	    cleardevice();
	    title();
	   }
	}while(c!=27);
	fclose(ft);  /* CLOSE TEMPORARY RECORDING FILE */
	closegraph();
	restorecrtmode();
      }
/******************************* END OF PIANO *******************************/
