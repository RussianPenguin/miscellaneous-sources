//---------------------------------------------------------------------------

#ifndef ThreadH
#define ThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TMyProgressEvent)(double);
class TCalcThread : public TThread
{
private:
        Graphics::TBitmap* Map;
        //������� ������� ��������
        double xmin;
        double ymin;
        double xmax;
        double ymax;

        //������� ����������
        double Progress;
        //������������ ���������� ��������
        int MaxIter;
        //�������, �����, �� ������� ���������� ����� �������� ��� ���������� ����� ������� ��������
        int Pallete;
protected:
        void __fastcall Execute();
public:
        //������, ���� ���� ������
        bool Active;
        __fastcall TCalcThread(Graphics::TBitmap* aMap, double _xmin, double _ymin, double _xmax, double _ymax,int aMaxIter,int aPallete);
        TMyProgressEvent OnProgress;//��� ������� ���������� �� Execute ������������ ��� ����������� ������� ����������
};
//---------------------------------------------------------------------------
#endif
