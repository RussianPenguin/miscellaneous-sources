//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "UQuadratics.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
  double Arg1;
  double Arg2;
  double Arg3;
  try
  {
    Arg1 = (double)StrToFloat(Edit1->Text);
  }
  catch(EConvertError&)
  {
    Arg1 = 0;
    Edit1->Text = "0";
  };
  try
  {
    Arg2 = (double)StrToFloat(Edit2->Text);
  }
  catch(EConvertError&)
  {
    Arg2 = 0;
    Edit2->Text = "0";
  };
  try
  {
    Arg3 = (double)StrToFloat(Edit3->Text);
  }
  catch(EConvertError&)
  {
    Arg3 = 0;
    Edit3->Text = "0";
  };
  double Descr;
  if(Arg1 != 0)
  {
    if(Arg2 != 0)
    {
      if(Arg3 != 0)
      {
        Descr = Arg2*Arg2-4*Arg1*Arg3;
        if(Descr < 0)
        {
          Panel1->Caption = "X не найден:";
          Panel2->Caption = "D<0";
          return;
        }
        double D1 = sqrt(Descr);
        double x1 = (-Arg2+D1)/(2*Arg1);
        double x2 = (-Arg2-D1)/(2*Arg1);
        Panel1->Caption = FloatToStr((float)x1);
        Panel2->Caption = FloatToStr((float)x2);
      }
      else
      {
        double x = -Arg2/Arg1;
        Panel1->Caption = "0";
        Panel2->Caption = FloatToStr((float)x);
      }
    }
    else
    {
      if(Arg3 !=0)
      {
        double x = (-Arg3/Arg1);
        if(x < 0)
        {
          Panel1->Caption = "X не найден";
          Panel2->Caption = "D < 0";
          return;
        }
        double x1 = sqrt(x);
        Panel1->Caption = FloatToStr((float)x1);
        Panel2->Caption = FloatToStr((float)x1);
      }
      else
      {
        Panel1->Caption = "0";
        Panel2->Caption = "0";
      }
    }
  }
  else
  {
    if(Arg2 !=0)
    {
      if(Arg3 != 0)
      {
        double x = -Arg3/Arg2;
        Panel1->Caption = FloatToStr((float)x);
        Panel2->Caption = FloatToStr((float)x);
      }
      else
      {
        Panel1->Caption = "X = 0";
        Panel2->Caption = "X = 0";
      }
    }
    else
    {
      Panel1->Caption = "X - любое число";
      Panel2->Caption = "X - любое число";
    }
  }
}
//---------------------------------------------------------------------------

