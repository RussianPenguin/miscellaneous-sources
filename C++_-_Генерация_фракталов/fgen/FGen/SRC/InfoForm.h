//---------------------------------------------------------------------------

#ifndef InfoFormH
#define InfoFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TInfo : public TForm
{
__published:	// IDE-managed Components
        TMemo *Memo1;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TInfo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInfo *Info;
//---------------------------------------------------------------------------
#endif
