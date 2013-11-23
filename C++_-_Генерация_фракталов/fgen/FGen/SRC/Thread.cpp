//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Thread.h"
#include "Main.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
//конструктор, инициализация
__fastcall TCalcThread::TCalcThread(Graphics::TBitmap* aMap, double _xmin, double _ymin, double _xmax, double _ymax,int aMaxIter,int aPallete)
        : TThread(false)
{
 Map=aMap;
 xmin=_xmin;ymin=_ymin;xmax=_xmax;ymax=_ymax;
 FreeOnTerminate=true;
 MaxIter=aMaxIter;
 Pallete=aPallete;

}
//---------------------------------------------------------------------------
//ключевой метод расчета цвета точки
void __fastcall TCalcThread::Execute()
{
 Active=true;
 double xstep = (xmax - xmin)/Map->Width;
 double ystep = (ymax - ymin)/Map->Height;
 Progress=0;
 int x=0;

 for(int y=0;y<Map->Height;y++)
 {
  Application->ProcessMessages();
  Progress=(double)(x+1)*(y+1)/(Map->Height*Map->Width);

  if (OnProgress)
   OnProgress(Progress);

  DWORD* ptr = (DWORD*)Map->ScanLine[y];
  if (Terminated) return;
  for(x=0;x<Map->Width;x++)
  {
   int Iter=0;
   double a,b,an,bn,nx,ny;
   a=nx=xmin+x*xstep;
   b=ny=ymin+y*ystep;
   do
   {
    an=a*a-b*b+nx;
    bn=2*a*b+ny;
    a=an;b=bn;
    Iter++;
   } while( ((a*a+b*b)<25) && Iter<MaxIter);

    ptr[x]=TColor(Pallete*Iter);
  }
 }
 Active=false;
}

//---------------------------------------------------------------------------




