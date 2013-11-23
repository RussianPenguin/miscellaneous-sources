//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AuthorForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAuthor *Author;
//---------------------------------------------------------------------------
__fastcall TAuthor::TAuthor(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAuthor::Label1Click(TObject *Sender)
{
 ShellExecute(Application->Handle,"open","mailto:cooluser@ngs.ru",NULL,NULL,0);        
}
//---------------------------------------------------------------------------
void __fastcall TAuthor::Button1Click(TObject *Sender)
{
 ModalResult=mrOk;        
}
//---------------------------------------------------------------------------
