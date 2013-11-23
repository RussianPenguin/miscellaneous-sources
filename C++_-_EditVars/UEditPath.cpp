//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UEditPath.h"
#include <registry.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFEditPath *FEditPath;
TRegistry *Reg = new TRegistry;
AnsiString PathStr;
AnsiString AddedPath;
//---------------------------------------------------------------------------
__fastcall TFEditPath::TFEditPath(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFEditPath::FormCreate(TObject *Sender)
{
  Reg->RootKey = HKEY_LOCAL_MACHINE;
  if(Reg->KeyExists("\\SYSTEM\\ControlSet001\\Control\\Session Manager\\Environment"))
  {
    Reg->OpenKey("\\SYSTEM\\ControlSet001\\Control\\Session Manager\\Environment",false);
    PathStr = Reg->ReadString("Path");
    ECurPath->Text = PathStr;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFEditPath::FormDestroy(TObject *Sender)
{
  delete Reg;
}
//---------------------------------------------------------------------------
void __fastcall TFEditPath::BUpdateClick(TObject *Sender)
{
  FormCreate(Sender);  
}
//---------------------------------------------------------------------------

void __fastcall TFEditPath::BAddDirClick(TObject *Sender)
{
  PathStr = ECurPath->Text;
  if(SelectDirectory("Select folder","",AddedPath))
  {
    int i = PathStr.Length();
    if(PathStr.SubString(i,i) == ";")
    {
      PathStr = PathStr + AddedPath;
    }
    else
    {
      PathStr = PathStr + ";" + AddedPath;
    }
    ECurPath->Text = PathStr;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFEditPath::BApplyClick(TObject *Sender)
{
  PathStr = ECurPath->Text;
  Reg->OpenKey("\\SYSTEM\\ControlSet001\\Control\\Session Manager\\Environment",false);
  Reg->WriteExpandString("Path",PathStr);
  Reg->OpenKey("\\SYSTEM\\ControlSet\\Control\\Session Manager\\Environment",false);
  Reg->WriteExpandString("Path",PathStr);
  Reg->OpenKey("\\SYSTEM\\ControlSet003\\Control\\Session Manager\\Environment",false);
  Reg->WriteExpandString("Path",PathStr);
}
//---------------------------------------------------------------------------

