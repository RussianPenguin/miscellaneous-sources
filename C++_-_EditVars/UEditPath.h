//---------------------------------------------------------------------------

#ifndef UEditPathH
#define UEditPathH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFEditPath : public TForm
{
__published:	// IDE-managed Components
        TButton *BUpdate;
        TButton *BAddDir;
  TEdit *ECurPath;
  TButton *BApply;
        void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall BUpdateClick(TObject *Sender);
  void __fastcall BAddDirClick(TObject *Sender);
  void __fastcall BApplyClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFEditPath(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFEditPath *FEditPath;
//---------------------------------------------------------------------------
#endif
