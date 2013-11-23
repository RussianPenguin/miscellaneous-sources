//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "CGAUGES.h"
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPaintBox *PaintBox;
        TMainMenu *MainMenu1;
        TMenuItem *mFile;
        TMenuItem *mSave;
        TMenuItem *N4;
        TMenuItem *mStart;
        TMenuItem *mStop;
        TMenuItem *mReset;
        TStatusBar *StatusBar;
        TPanel *Panel1;
        TToolBar *ToolBar1;
        TImageList *ImageList1;
        TSavePictureDialog *SavePictureDialog;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *StartButton;
        TToolButton *StopButton;
        TToolButton *ResetButton;
        TCGauge *Gauge;
        TToolButton *ToolButton6;
        TMenuItem *mAbout;
        TMenuItem *N1;
        TToolButton *ZoomIn;
        TToolButton *ZoomOut;
        TTrackBar *IterBar;
        TLabel *IterLabel;
        TScrollBar *PalScroll;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *N5;
        TMenuItem *N6;
        TMenuItem *N7;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall PaintBoxPaint(TObject *Sender);
        void __fastcall StartButtonClick(TObject *Sender);
        void __fastcall StopButtonClick(TObject *Sender);
        void __fastcall mStartClick(TObject *Sender);
        void __fastcall mStopClick(TObject *Sender);
        void __fastcall ResetButtonClick(TObject *Sender);
        void __fastcall mResetClick(TObject *Sender);
        void __fastcall mSaveClick(TObject *Sender);
        void __fastcall ToolButton1Click(TObject *Sender);
        void __fastcall N1Click(TObject *Sender);
        void __fastcall ZoomInClick(TObject *Sender);
        void __fastcall ZoomOutClick(TObject *Sender);
        void __fastcall IterBarChange(TObject *Sender);
        void __fastcall N6Click(TObject *Sender);
        void __fastcall N7Click(TObject *Sender);
        void __fastcall N2Click(TObject *Sender);
        void __fastcall N3Click(TObject *Sender);

private:
        void __fastcall Progress(double Percent);
        void __fastcall ThreadDone(TObject* Sender);
        double x0,y0,x1,y1;
        void UpdateStatus();

public:		// User declarations
        void Reset();
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

