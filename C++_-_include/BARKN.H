
void  colorpalette(int numcolor,int  fistcolor,int secondcolor,int thirdcolor)
 {
int k;
 outp(0x3c8,numcolor);
for(k=0;k<100;k++);
 outp(0x3c9,fistcolor/4); /* 0..63  (color/4)*/
for(k=0;k<100;k++);
 outp(0x3c9,secondcolor/4);
 for(k=0;k<100;k++);
outp(0x3c9,thirdcolor/4);
 setcolor(numcolor);
 }


 void palette()
{
colorpalette(3,80,80,80);
colorpalette(5,200,200,200);
colorpalette(1,0,0,130);
}
 void linex(int x,int y,int x1,int y1,int color)
 {
 setcolor(color);
 line(x,y,x1,y1);
 }

void font(char *names,int size)
{
int userfont;
userfont=installuserfont(names);
settextstyle(userfont,HORIZ_DIR,size);
}
       void krug(int x,int y,int radius)
       {
       setcolor(3);
       arc(x,y,60,240,radius);
       setcolor(15);
       arc(x,y,280,60,radius);
       }

       void circ(int x,int y,int radius,int color)
       {
       setcolor(color);
       for(;radius>0;radius--)circle(x,y,radius);
       putpixel(x,y,color);
       putpixel(x-1,y-1,color);
       putpixel(x+1,y+1,color);
       putpixel(x-1,y+1,color);
       putpixel(x+1,y-1,color);
       }
	void colorcir(int x,int y,int radius,int color)
	{
	setcolor(3);
       arc(x,y,60,240,radius);
       setcolor(15);
       arc(x,y,280,60,radius);
	 setcolor(color);
	 radius=radius-3;
       for(;radius>0;radius--)circle(x,y,radius);
       putpixel(x,y,color);
       putpixel(x-1,y-1,color);
       putpixel(x+1,y+1,color);
       putpixel(x-1,y+1,color);
       putpixel(x+1,y-1,color);
	}
 void cur_down(int x,int y,int color)
{
int a=x,b=x+8;

setcolor(color);
/*ZIP LINES
/*
line(x+3,y+2,x+3,y+5);
line(x+4,y+2,x+4,y+5);
line(x+5,y+2,x+5,y+5);
line(x+6,y+2,x+6,y+5);
  */
	while(a<=b)
	{
	line(a,y+4,b,y+4);
	y++;a++;b--;
	}
}
void cur_right(int x,int y,int color)
{
 int a=y,b=y+9;
 setcolor(color);
 while(a<b)
 {
 line(x,a,x,b);
 x++;a++;b--;
 }
}



void ten_textxy(int x,int y,char far *textstring ,int firstcolor,int secondcolor)
{

setcolor(secondcolor);
outtextxy(x+4,y+4,textstring);
setcolor(firstcolor);
outtextxy(x,y,textstring);
}
void rect(int x,int y,int x1,int y1,int color)
{
setcolor(color);
line(x,y,x1,y);
line(x,y,x,y1);
line(x,y1,x1,y1);
line(x1,y1,x1,y);
}
       void ret(int x,int y,int x1,int y1)
  {
  rect(x+1,y+1,x1+1,y1+1,15);
  rect(x,y,x1,y1,0);
  }
void rect_bar(int x,int y,int x1,int y1,int colorrect,int colorbar)
{
rect(x,y,x1,y1,colorrect);
setfillstyle(SOLID_FILL,colorbar);
bar(x+1,y+1,x1-1,y1-1);
}
 void button_rect(int x,int y,int x1,int y1,int lin,int rightcolor,int leftcolor)
{
int c;
 /*white bar*/
int n=y+1;
int i=x+1;
int p=y1-1;
int y2=x1-1;
/*gray bar */
int nn=y1-1;
int ii=x1-1;
int pp=y+1;
int yy=x+1;
/*white up right bar*/
for(c=1;c<=lin;c++)
 {
 setcolor(rightcolor);
line(x+1,n,y2,n);
line(i,y+1,i,p);
i++;
p--;
y2--;
n++;
/*grey down left bar*/
setcolor(leftcolor);
line(x1-1,nn,yy,nn);
line(ii,y1-1,ii,pp);
ii--;
pp++;
yy++;
nn--;
 }
}
  void button (int x,int y,int x1,int y1,int lin,int rectcolor,int knoprightcolor,int knopleftcolor ,int function)
  {
int n;
setcolor(7);
setfillstyle(SOLID_FILL,7);

button_rect(x,y,x1,y1,lin,knoprightcolor,knopleftcolor);
bar(x+lin+1,y+lin+1,x1-lin-1,y1-lin-1);
if(function==1)cur_down((x+x1)/2-5,(y+y1)/2-6,0);
}
 void vnutr_rect(int x,int y,int x1,int y1, int right,int right1,int left)
{
setcolor(right1);
line(x,y,x1,y);
line(x,y,x,y1);
setcolor(right);
line(x+1,y+1,x1,y+1);
line(x+1,y+1,x+1,y1);

setcolor(left);
line(x1,y1,x+1,y1);
line(x1,y1,x1,y+1);
line(x1-1,y1-1,x+2,y1-1);
line(x1-1,y1-1,x1-1,y+2);

}
  void vnutr(int x,int y,int x1,int y1,int color,int right,int right1,int left)
{
int n;
vnutr_rect(x,y,x1,y1,right,right1,left);
setcolor(color);
setfillstyle(SOLID_FILL,color);
bar(x+2,y+2,x1-2,y1-2);
}
 void ready_button(int x,int y,int x1,int y1,int color)
{

rect(x,y,x1,y1,8);
setfillstyle(SOLID_FILL,color);
bar(x+1,y+1,x1-1,y1-1);
}



 void big_bar3d(int x,int y,int x1 ,int y1,int lin,int rectcolor,int right,int left)
{
/*black bar */
rect(x,y,x1,y1,rectcolor);
button_rect(x,y,x1,y1,lin,right,left);
}
void play_button(int x,int y,int x1,int y1,int lin,int rectcolor,int knoprightcolor,int knopleftcolor ,int function,int color)
{
int n;
int i;
char  c;
button(x,y,x1,y1,lin,rectcolor,knoprightcolor,knopleftcolor,function);
ready_button(x,y,x1,y1,color);
for(i=0;i<=4;i++)for(n=0;n<=30000;n++);
button(x,y,x1,y1,lin,rectcolor,knoprightcolor,knopleftcolor,function);
}
