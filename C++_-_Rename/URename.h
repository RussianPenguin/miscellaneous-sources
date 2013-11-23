//---------------------------------------------------------------------------

#ifndef URenameH
#define URenameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <Dialogs.hpp>
#include <SysUtils.hpp>
#include "CSPIN.h"
#include <sys/stat.h>
//---------------------------------------------------------------------------
class TFRenameFiles : public TForm
{
__published:	// IDE-managed Components
        TCheckBox *CBSubFolders;
        TGroupBox *GBAddParam;
        TCheckBox *CBCreateBack;
        TGroupBox *GBParams;
        TRadioGroup *RGTypeOfRename;
        TRadioButton *RBFromFile;
        TRadioButton *RBFromParams;
        TEdit *EFileOfNames;
        TButton *BFileOfNames;
        TCheckBox *CBTranslit;
        TCheckBox *CBRenameSubF;
        TCheckBox *CBUseNumb;
        TCSpinEdit *CSENumber;
        TCheckBox *CBUsePrefix;
        TEdit *EPrefix;
        TCheckBox *CBUseRegisters;
        TRadioGroup *RGRegister;
        TRadioButton *RBLow;
        TRadioButton *RBHight;
        TCheckBox *CBRemoveSpace;
        TEdit *ESpaceAlternative;
  TFileListBox *FilesBox;
  TDirectoryListBox *TreeOfFolders;
  TDriveComboBox *Drives;
        TButton *BOK;
        TButton *BCancel;
  TLabel *LPath;
  TLabel *LStatus;
  TCheckBox *CBNotUseExt;
  TOpenDialog *OpenDialog1;
  void __fastcall DrivesChange(TObject *Sender);
  void __fastcall CBUsePrefixClick(TObject *Sender);
  void __fastcall CBUseNumbClick(TObject *Sender);
  void __fastcall CBRemoveSpaceClick(TObject *Sender);
  void __fastcall RBFromFileClick(TObject *Sender);
  void __fastcall RBFromParamsClick(TObject *Sender);
  void __fastcall CBUseRegistersClick(TObject *Sender);
  void __fastcall BOKClick(TObject *Sender);
  void __fastcall BFileOfNamesClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TFRenameFiles(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFRenameFiles *FRenameFiles;
//---------------------------------------------------------------------------
#endif
