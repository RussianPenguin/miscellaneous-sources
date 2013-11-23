Uses Crt, Dos, Rs232Int;

Begin
 {callback нам не нужна, передаем nil вторым параметром}
 InitRS232(2, nil, 9600, 3);

 While (True) do begin

  {При нажатии клавиши <1> передаем символ $31}
  {При нажатии клавиши <2> передаем символ $32}
  If KeyPressed then
   Case ReadKey of
    '1': OutByteToRS232($31);
    '2': OutByteToRS232($32);
    #27: Break;
   End;

 End;

 CloseRS232;
End.