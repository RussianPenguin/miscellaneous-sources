//---------------------------------------------------------------------------

#ifndef UEditVarsH
#define UEditVarsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFEditVars : public TForm
{
__published:	// IDE-managed Components
  TListBox *LBVars;
  TMainMenu *MainMenu1;
  TMenuItem *N1;
  TStatusBar *StatusBar1;
  TTreeView *TVVars;
  TComboBox *CBUsers;
private:	// User declarations
public:		// User declarations
  __fastcall TFEditVars(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFEditVars *FEditVars;
//---------------------------------------------------------------------------
#endif
