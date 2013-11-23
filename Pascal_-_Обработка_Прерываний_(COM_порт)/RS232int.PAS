Unit RS232Int;

INTERFACE
uses crt;

{Тип для call-back функции, вызываемой при}
{получении нового байта. Программы могут  }
{регистрировать свои функции обработки.   }
Type
 TCallBackRS = Procedure(Status : Byte; b : Byte);

{              ОСНОВНЫЕ ФУНКЦИИ                 }

{Инициализация порта                            }
{  ComIndex - номер порта                       }
{  Proc     - адрес callback функции или nil    }
{  Speed    - скорость работы порта             }
{  ComPar   - настройки порта                   }
Procedure InitRS232(ComIndex : Byte; Proc : TCallBackRS; Speed : Longint; COMPar : Byte);
{Закрытие порта, восстановление обработчиков INT}
procedure CloseRS232;
{Передача байта в порт }
procedure OutByteToRS232(b:Byte);

{              ОТЛАДОЧНЫЕ ФУНКЦИИ               }
{Счетчик вызовов прерывания}
function  GetIntRSCount : Longint;

{           ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ              }
{Позволяет задавать call-back адрес вручную }
procedure SetCallBackRS(Proc : TCallBackRS);
{Разрешает IRQ-прерывания }
Procedure EnableIRQ;
{Запрещает IRQ-прерывания }
Procedure DisableIRQ;
{Очистка порта. Просто холостое чтение}
Procedure ClearRSPort;
{Задание параметров порта}
Procedure SetPortState(Speed : Longint; COMPar : Byte);

IMPLEMENTATION

Uses Dos;

Var { старый адрес Int 0Ch/0BH }
 SerOldVec: Pointer;

Const { служебные переменные }
 Save_ds  : Word = 0;
 Int_sts  : Byte = 0;
 Count    : Word = 0;
 Src_ptr  : Word = 0;
 AddrPr   : Word = 0;
 tmp      : Word = 0;

Var
 BaseAdr  : Word;
 EOI      : Byte;
 IRQ      : Byte;
 IRQMask  : Byte;
 INTVect  : Byte;

Const { число входов в Int }
 CountInt : Longint = 0;

Const { адрес call-back функции }
 CallBackPtr : TCallBackRS = nil;

{ Подпрограмма обработки прерываний от COM-порта }
Procedure Ser_Int; interrupt;
Var B : Byte; COMStatus : Byte;
Begin
  Inc(CountInt); {счетчик вхождений в INT }

  B:= 0;
  Asm
   mov  dx, BaseAdr { регистр идентификации прерываний }
   add  dx, 2       { BaseAdr+2                        }
   in   al,dx
   mov  Int_Sts,al { сохраним его содержимое       }
   test al,1       { есть отложенные прерывания?   }
   jz   @Is_Int    { да                            }
   pushf           { нет, передаем управление      }
   call SerOldVec  { старому обработчику Int       }
@Is_Int:
   mov  al,EOI     { послать EOI для IRQ           }
   out  20h,al     { в 1-й контроллер прерываний   }
   test Int_Sts,4  { прерывание по приему?         }
   jnz  @Read_Char { да                            }
   mov  B, 1
@Read_Char:
   inc  B
  End;

  if (B <> 2) then begin

   Asm
    mov  dx, BaseAdr { регистр состояния линии }
    add  dx, 5       { BaseAdr + 5}
    in   al,dx
    and  al, 1EH
    mov  COMStatus,al { COMStatus<>0, если была ошибка приема }
   End;

   Asm
    mov  dx, BaseAdr { регистр данных }
    in   al, dx      { вводим символ  }
    mov  B , al
   End;

   {Вызов callback, если она задана}
   If @CallBackPtr<>nil then CallBackPtr(COMStatus, B);
  End;
End;

{Запрещение IRQ прерываний}
Procedure DisableIRQ;
Begin
 Asm
  in   al,21h     { IMR 1-го контролера прерываний  }
  or   al,IRQMask { запретить прерывание IRQ от COM }
  out  21h,al
 End;
End;

{Разрешение IRQ прерываний}
Procedure EnableIRQ;
var NIRQMask : Byte;
Begin
 NIRQMask:= not IRQMask;
 Asm
  in   al,21h    { IMR 1-го контроллера прерываний }
  and  al,NIRQMask
  out  21h,al    { разрешить прерывания от COM }
 End;
End;

{ Возвращает базовый адрес порта с номером PortIndex }
Function GetBaseAdr(PortIndex : Byte) : Word;
Var LowAdr : Word;
Begin
 { вычисляем младшую часть адреса в таблице }
 LowAdr := (PortIndex-1)*2;
 { получаем базовый адрес порта из таблицы }
 GetBaseAdr:= MemW[$0040:LowAdr];
End;

{Чистка порта. Холостое чтение порта.}
Procedure ClearRSPort;
Begin
 Asm
  mov  dx, BaseAdr { регистр данных         }
  in   al, dx      { сбросить буфер приема  }
 End;
End;

{Установка скорости обмена и характеристик порта }
Procedure SetPortState(Speed : Longint; COMPar : Byte);
Var Freq : Word; FreqH, FreqL : Byte;
Begin
 Freq:= 115200 div Speed;
 FreqH:= Freq shr 8;
 FreqL:= Freq and $00FF;

 Asm
  mov  dx, BaseAdr { регистр управления линией }
  add  dx, 3       { BaseAdr + 3}
  in   al,dx
  or   al,80h      { установить бит DLAB }
  out  dx,al

  mov  dx, BaseAdr
  mov  al, FreqL
  out  dx,al      { младший байт скорости }

  inc  dx          { BaseAdr+1  }
  mov  al,FreqH
  out  dx,al       { старший байт скорости }

  mov  dx, BaseAdr { регистр управления линией }
  add  dx, 3       { BaseAdr + 3               }
  mov  al, COMPar
  out  dx,al

  mov  dx, BaseAdr { регистр разрешения прерываний  }
  add  dx, 1       { BaseAdr+1                      }
  mov  al, 1       { разрешить прерывания по приему }
  out  dx, al
 End;
End;

{ Инициализация COM порта }
Procedure InitRS232(ComIndex : Byte; Proc : TCallBackRS; Speed : Longint; COMPar : Byte);
Begin
 CallBackPtr:= Proc; {сохранить адрес call-back}

 {Получить базовый адрес порта}
 BaseAdr:= GetBaseAdr(ComIndex);

 {Порт не найден - выход}
 If BaseAdr = 0 then Exit;

 {Инициализация переменных, зависящих от номера COM}
 Case ComIndex of {Номер IRQ порта}
  1: IRQ:= 4; {для COM1/IRQ4}
  2: IRQ:= 3; {для COM2/IRQ3}
 End;
 Case IRQ of {Номер INT вектора прерываний }
  3: INTVect:= $0B; {для IRQ3}
  4: INTVect:= $0C; {для IRQ4}
 End;
 Case IRQ of {Сигнал EOI контроллеру прерываний}
  3: EOI:= $63; {для IRQ3}
  4: EOI:= $64; {для IRQ4}
 End;
 Case IRQ of {Сигнал EOI контроллеру прерываний}
  3: IRQMask:= $08; {для IRQ3}
  4: IRQMask:= $10; {для IRQ4}
 End;

 Asm
  cli { запретить прерывания }
 End;

 {запретить IRQ прерывания }
 DisableIRQ;

 {Получить текущий обработчик INT}
 GetIntVec(INTVect, SerOldVec);
 {Установить новый обработчик INT}
 SetIntVec(INTVect, Addr(Ser_Int));

 {Разрешить IRQ прерывания}
 EnableIRQ;

 {Задание скорости обмена и характеристик порта}
 SetPortState(Speed, COMPar);

 Asm
  sti { разрешить прерывания }
 End;

 {Чистка порта}
 ClearRSPort;
End;

{ Закрытие порта. Восстановление обработчиков INT }
Procedure CloseRS232;
Begin
 Asm
@Wait_Free:
   mov  dx, BaseAdr { регистр состояния линии }
   add  dx, 5       { BaseAdr+5               }
   in   al, dx
   nop
   nop
   test al,60h     { передача окончена?            }
   jz   @Wait_Free { ждем, если нет                }
   mov  dx, BaseAdr{ регистр разрешения прерываний }
   add  dx, 1      { BaseAdr+1                     }
   mov  al,0       { запретить прерывания          }
   out  dx,al
   nop
   nop
   nop
   nop
   mov  dx, BaseAdr  { регистр управления модемом }
   add  dx,4         { BaseAdr+4}
   mov  al,00000011b { активировать DTR и RTS }
   out  dx,al
   nop
   nop
   nop
   nop
  End;

  {Вернуть старый обработчик INT}
  SetIntVec(INTVect, SerOldVec);

  Asm
   cli            { запрет прерываний }
   in   al,21h    { читать маску прерываний }
   nop
   nop
   or   al,IRQMask { запретить IRQ прерывания }
   out  21h,al
   sti             { разрешение прерываний    }
  End;
End;

{ Подпрограмма вывода символа AL в порт.    }
{ При ошибке возвращает CF=1, иначе CF=0.   }
Procedure OutByteToRS232(b:Byte); assembler;
Asm
@Wait_Line:
  mov  dx, BaseAdr { регистр состояния линии }
  add  dx, 5       { BaseAdr+5               }
  in   al,dx
  test al,20h     { стык готов к передаче? }
  jnz  @Output    { да }
  nop
  loop @Wait_Line { нет, ждем }
  ret

@Output:
  mov  al, B
  mov  dx, BaseAdr  { регистр данных }
  out  dx,al        { вывести символ }
  nop
End;


{Доступ к счетчику вхождений в INT }
function  GetIntRSCount : Longint;
begin
 GetIntRSCount:= CountInt;
end;

{Установка callback вне функции инициализации}
procedure SetCallBackRS(Proc : TCallBackRS);
begin
 CallBackPtr:= Proc;
end;

END.