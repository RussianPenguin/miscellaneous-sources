//---------------------------------------------------------------------------

#ifndef USelectorH
#define USelectorH
//---------------------------------------------------------------------------
#include <Forms.hpp>
#include <FileCtrl.hpp>
#include <ComCtrls.hpp>
#include <StdCtrls.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TComboBox *CBMods;
  TLabel *Label1;
  TLabel *Label2;
  TRichEdit *REAbout;
  TButton *BApply;
  TLabel *LLast;
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall CBModsChange(TObject *Sender);
  void __fastcall BApplyClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
