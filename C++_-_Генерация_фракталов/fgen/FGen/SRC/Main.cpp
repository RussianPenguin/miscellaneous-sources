//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Thread.h"
#include "gifimage.hpp"
#include "jpeg.hpp"
#include "AuthorForm.h"
#include "InfoForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGAUGES"
#pragma resource "*.dfm"
TForm1 *Form1;
Graphics::TBitmap* pMap;
TCalcThread* CalcThread;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------
//обработчик OnProgress класса TCalcThread
void __fastcall TForm1::Progress(double Percent)
{
 Gauge->Progress=Gauge->MinValue+Percent*(Gauge->MaxValue-Gauge->MinValue);
}

void TForm1::Reset()
{
 pMap->Height=PaintBox->Height;;
 pMap->Width=PaintBox->Width;
 pMap->PixelFormat=pf32bit;
 StartButton->Enabled=true;
 StopButton->Enabled=false;
 x0=-2;x1=2;y0=-1;y1=1;

 Gauge->Progress=0;

 if (CalcThread)
 {
  CalcThread->Terminate();
  CalcThread=NULL;
 }

 DWORD* ptr;
 for (int y = 0; y < pMap->Height; y++)
 {
  ptr = (DWORD *)pMap->ScanLine[y];

  for (int x = 0; x < pMap->Width; x++)
  {
       ptr[x] =clBlack;
  }
 }

 IterBar->Position=15;

 Invalidate();
}

//инициализация
void __fastcall TForm1::FormCreate(TObject *Sender)
{
  //в этом объекте хранится картинка
  pMap = new Graphics::TBitmap();
  //установить начальные значения
  Reset();

 //создать панели
  for(int i=0;i<5;i++)
  {
   TStatusPanel* Panel=StatusBar->Panels->Add();
   Panel->Width=40;
   Panel->Bevel=pbRaised;
   Panel->Alignment=taCenter;

  }
 StatusBar->Panels->Items[4]->Bevel=pbNone;

 //начальные значение области фрактала
 //обновить содержимое панелей
 UpdateStatus();

}
//---------------------------------------------------------------------------
//рисует объект pMap
void __fastcall TForm1::PaintBoxPaint(TObject *Sender)
{
 PaintBox->Canvas->Draw(0,0,pMap);
}
//---------------------------------------------------------------------------
//начнем прорисовку
void __fastcall TForm1::StartButtonClick(TObject *Sender)
{
 StartButton->Enabled=false;
 ResetButton->Enabled=false;
 StopButton->Enabled=true;
 if (CalcThread)
  CalcThread->Resume();
 else
  {
   pMap->Width=PaintBox->Width;
   pMap->Height=PaintBox->Height;
   CalcThread = new TCalcThread(pMap,x0,y0,x1,y1,IterBar->Position*10,PalScroll->Position);
   CalcThread->OnProgress=Progress;
   CalcThread->OnTerminate=ThreadDone;
  }
}
//---------------------------------------------------------------------------
//приостановка
void __fastcall TForm1::StopButtonClick(TObject *Sender)
{
 StopButton->Enabled=false;
 StartButton->Enabled=true;
 CalcThread->Suspend();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mStartClick(TObject *Sender)
{
 StartButton->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mStopClick(TObject *Sender)
{
 StopButton->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ResetButtonClick(TObject *Sender)
{
 Reset();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mResetClick(TObject *Sender)
{
 ResetButton->Click();
}
//---------------------------------------------------------------------------

//эта функция вызывается когда поток завершает работу
void __fastcall TForm1::ThreadDone(TObject* Sender)
{
 Invalidate();
 StartButton->Enabled=true;
 StopButton->Enabled=false;
 ResetButton->Enabled=true;
 CalcThread=NULL;
}
//сохранение картинки в файл
void __fastcall TForm1::mSaveClick(TObject *Sender)
{
 if (!SavePictureDialog->Execute() ) return ;

 String FileName = SavePictureDialog->FileName;

 static TGIFImage* pGif = new TGIFImage();
 static TJPEGImage* pJpeg = new TJPEGImage();

 switch (SavePictureDialog->FilterIndex)
 {
  case 1:
  pGif->Assign(pMap);
  FileName=ChangeFileExt(FileName,".gif");

  if (FileExists(FileName))
   if (Application->MessageBox("Файл сущесвтует. Перезаписать?","Внимание!",MB_OKCANCEL)!=ID_OK)
       return;

  pGif->SaveToFile(FileName);
  delete pGif;

  break;
  case 2:
  pJpeg->Assign(pMap);
  FileName=ChangeFileExt(FileName,".jpg");

  if (FileExists(FileName))
   if (Application->MessageBox("Файл сущесвтует. Перезаписать?","Внимание!",MB_OKCANCEL)!=ID_OK)
       return;

  pJpeg->SaveToFile(FileName);
  delete pJpeg;

  break;
  case 3:
  FileName=ChangeFileExt(FileName,".bmp");

  if (FileExists(FileName))
   if (Application->MessageBox("Файл сущесвтует. Перезаписать?","Внимание!",MB_OKCANCEL)!=ID_OK)
       return;

  pMap->SaveToFile(FileName);
  break;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton1Click(TObject *Sender)
{
 mSave->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N1Click(TObject *Sender)
{
 Application->Terminate();
}
//---------------------------------------------------------------------------
void TForm1::UpdateStatus()
{
 StatusBar->Panels->Items[0]->Text="x0="+FloatToStr(x0);
 StatusBar->Panels->Items[1]->Text="y0="+FloatToStr(y0);
 StatusBar->Panels->Items[2]->Text="x1="+FloatToStr(x1);
 StatusBar->Panels->Items[3]->Text="y1="+FloatToStr(y1);

}
//увеличение
void __fastcall TForm1::ZoomInClick(TObject *Sender)
{
 x0/=2;
 y0/=2;
 x1/=2;
 y1/=2;
 StartButton->Click();
 UpdateStatus();
}
//---------------------------------------------------------------------------
//уменьшение
void __fastcall TForm1::ZoomOutClick(TObject *Sender)
{
 x0*=2;
 y0*=2;
 x1*=2;
 y1*=2;
 StartButton->Click();
 UpdateStatus();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::IterBarChange(TObject *Sender)
{
 IterLabel->Caption=IntToStr(IterBar->Position*10);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender)
{
 ZoomIn->Click();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N7Click(TObject *Sender)
{
 ZoomOut->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{
 Author->ShowModal();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject *Sender)
{
 Info->ShowModal();        
}
//---------------------------------------------------------------------------

