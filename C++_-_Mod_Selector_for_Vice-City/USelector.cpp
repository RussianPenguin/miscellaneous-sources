//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "USelector.h"
#include <process.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
AnsiString GTADir;
AnsiString Dir;
TStringList *Orig = new TStringList;
TStringList *NewMod;
TStringList *Params = new TStringList;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormCreate(TObject *Sender)
{
  Dir = GetCurrentDir();
  bool yes = true;
  while(yes)
  {
    if(!FileExists("Settings"))
    {
      while(true)
      {
        while(SelectDirectory("Выберите директорию Vice-City","",GTADir) != true);
        SetCurrentDir(GTADir);
        if(FileExists("gta-vc.exe"))
        {
          Params->Add(GTADir);
          Params->Add(" ");
          Params->SaveToFile(Dir + "\\Settings");
          yes = false;
          break;
        }
      }
    }
    else
    {
      Params->LoadFromFile("Settings");
      GTADir = Params->Strings[0];
      if(FileExists(GTADir + "\\gta-vc.exe"))
      {
        yes = false;
      }
      else
        DeleteFile("Settings");
    }
  }
  SetCurrentDir(GTADir + "\\mods");
  TSearchRec sr;
  if(FindFirst("*.*", faAnyFile | faDirectory , sr) == 0)
  {
    while(FindNext(sr) == 0)
    {
      if(sr.Name != "..")
        CBMods->Items->Add(sr.Name);
    }
  }
  FindClose(sr);
  Orig->LoadFromFile(GTADir+"\\mods\\orig\\files");
  LLast->Caption = "Последний мод, который вы использовали: " + Params->Strings[1];
  CBMods->ItemIndex = 0;
  CBModsChange(Sender);
  Params->SaveToFile(Dir + "\\Settings");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CBModsChange(TObject *Sender)
{
  REAbout->Lines->LoadFromFile(GTADir+"\\mods\\"+CBMods->Text+"\\about");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BApplyClick(TObject *Sender)
{
  NewMod = new TStringList;
  Params->Strings[1] = CBMods->Text;
  Params->SaveToFile(Dir + "\\Settings");
  NewMod->LoadFromFile(GTADir+"\\mods\\"+CBMods->Text+"\\files");
  int i = 0;
  int j = Orig->Count;
  while(i < j)
  {
    //DeleteFile(GTADir + Orig->Strings[i]);
    CopyFile((GTADir + "\\mods\\orig" + Orig->Strings[i]).c_str(),(GTADir + Orig->Strings[i]).c_str(),false);
    i++;
  }
  i = 0;
  j = NewMod->Count;
  while(i < j)
  {
    //DeleteFile(GTADir + NewMod->Strings[i]);
    CopyFile((GTADir + "\\mods\\" + CBMods->Text + NewMod->Strings[i]).c_str(),(GTADir +  NewMod->Strings[i]).c_str(),false);
    i++;
  }
  LLast->Caption = "Последний мод, который вы использовали: " + CBMods->Text;
}
//---------------------------------------------------------------------------


