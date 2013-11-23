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
AnsiString BackUpDir; //Папка для сохранения BackUp'ов
//Структура, в которой указаны опции переименования
struct options
{
  AnsiString PreviousName;//Предыдущее имя файла (директории)
  AnsiString NextName;    //Преобразованное имя файла (директории)
  AnsiString WorkingDir;  //Текущая директория поиска
  AnsiString RemoveSpace; //Заменять прбелы на ...
  AnsiString Prefix;      //Начинать имена с префикса ...
  bool translit;          //Транслитерация
  bool reg;               //Использовать приведение к определенному регистру
  bool lowhight;          //Регистр (Верхний или нижний)
  bool fileofnames;       //Использовать файл с новыми именами
  bool saveext;           //Сохранять исходные расширения
  bool searchin;          //Искать в подкаталогах
  bool usenumname;        //Использовать числа
  bool rensub;            //Переименовывать директории
  bool delspace;          //Заменять или нет пробеды
  bool prefix;            //Добавлять ли префикс
  int statrnum;           //Переименовывать файлы, используя стартовый номер
};
options*Pref = new options;
//---------------------------------------------------------------------------
void RenameFiles(); //Функция поиска
void Edit();        //Функция обработки имен файлов
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
//Клацаем на копке для переименования
void __fastcall TFRenameFiles::BOKClick(TObject *Sender)
{
  BOK->Enabled = false; //Блокируем кнопку
  Pref->WorkingDir = LPath->Caption; //Устанавливаем стартовый каталог
  //Проверяем, создан ли файл с именами для переименования
  //если установлен соответствующий флаг
  if(RBFromFile->Checked)
  {
    if((FileOpen(EFileOfNames->Text,S_IREAD | S_IWRITE)) == -1)
    {
      //Ежели файл не существует. то вылетаем с криком об ошибке
      Application->MessageBox("Проверьте правильность указания имени файла",\
                              "Ошибка!",MB_ICONSTOP);
      goto EXIT;
    }
  }
  //Иначе переименовываем, используя установленные опции
  else
  {

    Pref->translit = CBTranslit->Checked;   //Подвергать имена транслитерации или нет
    Pref->usenumname = CBUseNumb->Checked;  //Использовать числовое имя
    if(Pref->usenumname == true)            //Если да, то
      Pref->statrnum = CSENumber->Value;    //устанавливаем стартовое значение
    Pref->saveext = CBNotUseExt->Checked;   //Сохранять расширение или нет
    Pref->reg = CBUseRegisters->Checked;    //Приводить к верхнему или нижнему регистру
    Pref->lowhight = RBLow->Checked;        //Нижний или верхний регистр
    Pref->rensub = CBRenameSubF->Checked;   //Переименовывать подпапки (Yes/No/Cancel =)))
    Pref->delspace = CBRemoveSpace->Checked;//Заменить побелы (yes/no/cancel)
    Pref->prefix = CBUsePrefix->Checked;    //Добавить префикс?
    Pref->Prefix = EPrefix->Text;           //Префикс
    Pref->searchin = CBSubFolders->Checked; //Заходить в подкаталоги
  }
  RenameFiles(); //Переименовываем
  EXIT:
  BOK->Enabled = true; //Разблокируем кнопку
}
//---------------------------------------------------------------------------

void RenameFiles()
{
  AnsiString Dir;
  Dir = Pref->WorkingDir;
  TSearchRec sr; //Структура для обработки
  SetCurrentDir(Dir); //Устанавливаем рабочий каталог
  //Начинаем искать
  if(FindFirst("*.*",faAnyFile | faDirectory, sr) == 0)
  {
    //Заносим в структуру options текущее имя файла
    Pref->PreviousName = sr.Name;
    //Продолжаем поиск
    while(FindNext(sr) == 0)
    {
      if((sr.Name == "..") or (sr.Name == "."))
        continue;
      if(sr.Attr != faDirectory)
      {
        //Ежу понятно. =))
        Pref->PreviousName = sr.Name;
        Edit();
      }
      if((Pref->rensub == true) && (sr.Attr == faDirectory))
        Edit();
      //Если установлен флаг поиска в директории. то производим в ней поиск
      if((Pref->searchin == true) && (sr.Attr == faDirectory))
      {
        Pref->WorkingDir = sr.Name;
        RenameFiles();
        SetCurrentDir(Dir);
      }
    }
  }
  //Заканчиваем поиск
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
  //Начинаем обработку
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
  ShowMessage("Было: " + Pref->PreviousName + " | Стало " + Pref->NextName);
}
