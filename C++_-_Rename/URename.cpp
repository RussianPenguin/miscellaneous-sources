//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "URename.h"
#include <FileCtrl.hpp>
#include <SysUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "CSPIN"
#pragma resource "*.dfm"
TFRenameFiles *FRenameFiles;
//
AnsiString Case[2][33] = {{"a", "b", "v", "g", "d", "e", "yo", \
                          "zh", "z", "i", "j", "k", "l", "m", \
                          "n", "o", "p", "r", "s", "t", "u", "f", \
                          "x", "c", "ch", "sh", "sj", "~", "y", \
                          "'", "e'", "yu", "ya"},{"A", "B", "V", \
                          "G", "D", "E", "YO", "ZH", "Z", "I", \
                          "J", "K", "L", "M", "N", "O", "P", "R",\
                          "S", "T", "U", "F", "X", "C", "CH", \
                          "SH", "SJ", "~", "Y", "'", "E'", "YU", "YA"}};
AnsiString BackUpDir; //����� ��� ���������� BackUp'��
//���������, � ������� ������� ����� ��������������
struct options
{
  AnsiString PreviousName;//���������� ��� ����� (����������)
  AnsiString NextName;    //��������������� ��� ����� (����������)
  AnsiString WorkingDir;  //������� ���������� ������
  AnsiString RemoveSpace; //�������� ������ �� ...
  AnsiString Prefix;      //�������� ����� � �������� ...
  bool translit;          //��������������
  bool reg;               //������������ ���������� � ������������� ��������
  bool lowhight;          //������� (������� ��� ������)
  bool fileofnames;       //������������ ���� � ������ �������
  bool saveext;           //��������� �������� ����������
  bool searchin;          //������ � ������������
  bool usenumname;        //������������ �����
  bool rensub;            //��������������� ����������
  bool delspace;          //�������� ��� ��� �������
  bool prefix;            //��������� �� �������
  int statrnum;           //��������������� �����, ��������� ��������� �����
};
options*Pref = new options;
//---------------------------------------------------------------------------
void RenameFiles(); //������� ������
void Edit();        //������� ��������� ���� ������
//---------------------------------------------------------------------------
__fastcall TFRenameFiles::TFRenameFiles(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFRenameFiles::DrivesChange(TObject *Sender)
{
  TreeOfFolders->Drive = Drives->Drive;
}
//---------------------------------------------------------------------------

void __fastcall TFRenameFiles::CBUsePrefixClick(TObject *Sender)
{
  EPrefix->Enabled = EPrefix->Enabled == true ? false : true;
}
//---------------------------------------------------------------------------

void __fastcall TFRenameFiles::CBUseNumbClick(TObject *Sender)
{
  CSENumber->Enabled = CSENumber->Enabled == true ? false : true;
}
//---------------------------------------------------------------------------

void __fastcall TFRenameFiles::CBRemoveSpaceClick(TObject *Sender)
{
  ESpaceAlternative->Enabled = ESpaceAlternative->Enabled == true ? false : true;
}
//---------------------------------------------------------------------------

void __fastcall TFRenameFiles::RBFromFileClick(TObject *Sender)
{
  EFileOfNames->Enabled = true;
  BFileOfNames->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFRenameFiles::RBFromParamsClick(TObject *Sender)
{
  EFileOfNames->Enabled = false;
  BFileOfNames->Enabled = false;
}
//---------------------------------------------------------------------------
// :)
void __fastcall TFRenameFiles::CBUseRegistersClick(TObject *Sender)
{
  RBLow->Enabled = RBLow->Enabled == true ? false : true;
  RBHight->Enabled = RBHight->Enabled == true ? false : true;
}
//---------------------------------------------------------------------------
//������� �� ����� ��� ��������������
void __fastcall TFRenameFiles::BOKClick(TObject *Sender)
{
  BOK->Enabled = false; //��������� ������
  Pref->WorkingDir = LPath->Caption; //������������� ��������� �������
  //���������, ������ �� ���� � ������� ��� ��������������
  //���� ���������� ��������������� ����
  if(RBFromFile->Checked)
  {
    if((FileOpen(EFileOfNames->Text,S_IREAD | S_IWRITE)) == -1)
    {
      //����� ���� �� ����������. �� �������� � ������ �� ������
      Application->MessageBox("��������� ������������ �������� ����� �����",\
                              "������!",MB_ICONSTOP);
      goto EXIT;
    }
  }
  //����� ���������������, ��������� ������������� �����
  else
  {

    Pref->translit = CBTranslit->Checked;   //���������� ����� �������������� ��� ���
    Pref->usenumname = CBUseNumb->Checked;  //������������ �������� ���
    if(Pref->usenumname == true)            //���� ��, ��
      Pref->statrnum = CSENumber->Value;    //������������� ��������� ��������
    Pref->saveext = CBNotUseExt->Checked;   //��������� ���������� ��� ���
    Pref->reg = CBUseRegisters->Checked;    //��������� � �������� ��� ������� ��������
    Pref->lowhight = RBLow->Checked;        //������ ��� ������� �������
    Pref->rensub = CBRenameSubF->Checked;   //��������������� �������� (Yes/No/Cancel =)))
    Pref->delspace = CBRemoveSpace->Checked;//�������� ������ (yes/no/cancel)
    Pref->prefix = CBUsePrefix->Checked;    //�������� �������?
    Pref->Prefix = EPrefix->Text;           //�������
    Pref->searchin = CBSubFolders->Checked; //�������� � �����������
  }
  RenameFiles(); //���������������
  EXIT:
  BOK->Enabled = true; //������������ ������
}
//---------------------------------------------------------------------------

void RenameFiles()
{
  AnsiString Dir;
  Dir = Pref->WorkingDir;
  TSearchRec sr; //��������� ��� ���������
  SetCurrentDir(Dir); //������������� ������� �������
  //�������� ������
  if(FindFirst("*.*",faAnyFile | faDirectory, sr) == 0)
  {
    //������� � ��������� options ������� ��� �����
    Pref->PreviousName = sr.Name;
    //���������� �����
    while(FindNext(sr) == 0)
    {
      if((sr.Name == "..") or (sr.Name == "."))
        continue;
      if(sr.Attr != faDirectory)
      {
        //��� �������. =))
        Pref->PreviousName = sr.Name;
        Edit();
      }
      if((Pref->rensub == true) && (sr.Attr == faDirectory))
        Edit();
      //���� ���������� ���� ������ � ����������. �� ���������� � ��� �����
      if((Pref->searchin == true) && (sr.Attr == faDirectory))
      {
        Pref->WorkingDir = sr.Name;
        RenameFiles();
        SetCurrentDir(Dir);
      }
    }
  }
  //����������� �����
  FindClose(sr);
}
//---------------------------------------------------------------------------

void __fastcall TFRenameFiles::BFileOfNamesClick(TObject *Sender)
{
  if(OpenDialog1->Execute())
  {
    EFileOfNames->Text = OpenDialog1->FileName;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFRenameFiles::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  delete Pref;
}
//---------------------------------------------------------------------------
void Edit()
{
  //�������� ���������
  Pref->NextName = Pref->PreviousName;
  if(Pref->delspace == true)
  {
    if(AnsiPos(" ",Pref->NextName) != 0)
    {
      Pref->NextName = StringReplace(Pref->NextName," ",Pref->RemoveSpace,\
                                     TReplaceFlags()<<rfReplaceAll);
    }
  }
  if(Pref->reg == true)
  {
    if(Pref->lowhight == true)
    {
      Pref->NextName = AnsiLowerCase(Pref->NextName);
    }
    else
    {
      Pref->NextName = AnsiUpperCase(Pref->NextName);
    }
  }
  if(Pref->prefix == true)
  {
    Pref->NextName = Pref->Prefix + Pref->NextName;
  }
  ShowMessage("����: " + Pref->PreviousName + " | ����� " + Pref->NextName);
}
