Uses Crt, Dos, Rs232Int;

   { Эта процедура будет вызвана при получении байта }
   procedure COMCallBack(Status : Byte; b : byte); far;
   begin
    {В реальной программе так делать не рекомендуется! }
    {Вывоз на экран - очень долгая операция для ее     }
    {использования в обработчике аппаратного прерывания}
    WriteLn(b);
   End;

Begin
 {Инициализация порта и регистрация callback процедуры}
 InitRS232(1, COMCallBack, 9600, 3);

 {Холостой цикл}
 While (True) do begin

  {Никаких обращений к порту!}
  If KeyPressed then
   If ReadKey = #27 then Break;

 End;

 CloseRS232;
End.