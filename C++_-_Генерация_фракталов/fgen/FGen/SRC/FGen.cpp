//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("FGen.res");
USEFORM("Main.cpp", Form1);
USEUNIT("Thread.cpp");
USEUNIT("gifimage.pas");
USEFORM("AuthorForm.cpp", Author);
USEFORM("InfoForm.cpp", Info);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TAuthor), &Author);
                 Application->CreateForm(__classid(TInfo), &Info);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
