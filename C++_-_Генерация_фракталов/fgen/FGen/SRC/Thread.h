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
        //границы области фрактала
        double xmin;
        double ymin;
        double xmax;
        double ymax;

        //процент завершения
        double Progress;
        //максимальное количество итераций
        int MaxIter;
        //палитра, число, на которое умножается число итераций для конкретной точки области фрактала
        int Pallete;
protected:
        void __fastcall Execute();
public:
        //истина, если идет расчет
        bool Active;
        __fastcall TCalcThread(Graphics::TBitmap* aMap, double _xmin, double _ymin, double _xmax, double _ymax,int aMaxIter,int aPallete);
        TMyProgressEvent OnProgress;//эта функция вызывается из Execute используется для отображения прцента выполнения
};
//---------------------------------------------------------------------------
#endif
