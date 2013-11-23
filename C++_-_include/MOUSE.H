void delmouse()
{
 union REGS r;
 r.x.ax=0;
 int86(0x33,&r,&r);
}


void mouse_show(void)
{
union REGS r;
r.x.ax=1;
int86(0x33,&r,&r);
}

void hidemouse()
{
 union REGS r;
 r.x.ax=2;
 int86(0x33,&r,&r);
}

int getmouse(int *x,int *y)
{
int ax;
union REGS r,rout;
r.x.ax=3;
int86(0x33,&r,&rout);
*x=rout.x.cx;
*y=rout.x.dx;
return(rout.x.bx);
}

   int mousestatys(int x,int y,int x1,int y1)
{

   int number;
   int  n,m;
   number=getmouse(&n,&m);
   if(number==0)
   {
   if(n>=x && n<=x1 && m>=y && m<=y1)return(1);
   else
       return(-1);
   }
   if(number==1)
   {
   if(n>=x && n<=x1 && m>=y && m<=y1)return(1);
   else
       return(-1);
   }
}