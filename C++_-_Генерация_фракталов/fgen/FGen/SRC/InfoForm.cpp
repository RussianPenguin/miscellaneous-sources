//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "InfoForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInfo *Info;
//---------------------------------------------------------------------------
__fastcall TInfo::TInfo(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TInfo::Button1Click(TObject *Sender)
{
 ModalResult=mrOk;        
}
//---------------------------------------------------------------------------

