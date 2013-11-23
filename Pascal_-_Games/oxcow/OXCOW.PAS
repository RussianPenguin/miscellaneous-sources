{$A+,B-,D-,E-,F-,G+,I-,L-,N+,O-,P-,Q-,R-,S-,T-,V-,X+}
{$M 65520,0,655360}
{$DEFINE DEBUG1}
program OxCow;

  type
    TNum = array [1 .. 4] of Byte;

  const
    ScanCode : Byte = 0;

  var
    Ask , CNum        : TNum;
    i , j , Cnt , Ans : Word;

  function CheckValid (r : TNum) : Boolean;
    begin
      CheckValid := (r [1] <> r [2]) and (r [1] <> r [3]) and (r [1] <> r [4])
                                     and (r [2] <> r [3]) and (r [2] <> r [4])
                                                          and (r [3] <> r [4]);
    end;

  function Check (f1 , f2 : TNum) : Byte;
    var
      fI , fJ, fRes : Byte;
    begin
      fRes := 0;
      for fI := 1 to 4 do if f1 [fI] = f2 [fI] then begin
        Inc (fRes , 8);
        f1 [fI] := 10;
        f2 [fI] := 10;
      end;
      for fI := 1 to 4 do for fJ := 1 to 4 do if fI <> fJ then if f1 [fI] in [0 .. 9] then if f2 [fJ] in [0 .. 9] then
          if f1 [fI] = f2 [fJ] then begin
            Inc (fRes);
            f1 [fI] := 10;
            f2 [fJ] := 10;
          end;
      Check := fRes;
    end;

  procedure GotoXY (x , y : Byte);
    begin
      asm
        mov     ah,2
        xor     bh,bh
        mov     dl,x
        mov     dh,y
        int     10h
      end;
    end;

  function Key : Byte;
    var
      tmp : Byte;
    function KeyPressed : Boolean; assembler;
      asm
	cmp	ScanCode,0
	jne	@@1
	mov	ah,1
	int	16h
	mov	al,0
	je	@@2
@@1:	mov	al,1
@@2:
      end;

    function ReadKey : Char; assembler;
      asm
	mov	al,ScanCode
	mov	ScanCode,0
	or	al,al
	jne	@@1
	xor	ah,ah
	int	16h
	or	al,al
	jne	@@1
	mov	ScanCode,ah
	or	ah,ah
	jne	@@1
	mov	al,3
@@1:
      end;

    begin
      Key := 0;
      if not KeyPressed then Exit;
      tmp := Ord (ReadKey);
      Key := tmp;
      if tmp = 0 then Key := Ord (ReadKey) + 128;
    end;

  procedure DrawSym (x , y , s , c : Byte);
    begin
      Mem [$B800 : (x + 80 * y) * 2] := s;
      Mem [$B800 : (x + 80 * y) * 2 + 1] := c;
    end;

  procedure DrawStr (x , y : Byte; s : string; c : Byte);
    var
      fI : Byte;
    begin
      for fI := 1 to Ord (s [0]) do DrawSym (x - 1 + fI , y , Ord (s [fI]) , c);
    end;

  procedure ReadNum (var Res : TNum);
    var
      tmp , Len : Byte;
    begin
      tmp := 0;
      Len := 0;
      GotoXY (0 , 1);
      DrawStr (0 , 1 , #0#0#0#0 , 7);
      while (tmp <> 13) or (Len <> 4) do begin
        tmp := Key;
        case tmp of
          0       :;
          8       : begin
                      if Len <> 0 then begin
                        Dec (Len);
                        DrawSym (Len , 1 , 0 , 7);
                        GotoXY (Len , 1);
                      end;
                    end;
          27      : Halt;
          48 .. 57: begin
                      if Len <> 4 then begin
                        Inc (Len);
                        Res [Len] := tmp - 48;
                        DrawSym (Len - 1 , 1 , tmp , 10);
                        GotoXY (Len , 1);
                      end;
                    end;
        end;
      end;
    end;

  procedure ClrScr;
    var
      fI : Word;
    begin
      for fI := 0 to 3999 do Mem [$B800 : fI] := 7 * (fI mod 2);
      GotoXY (0 , 0);
    end;

{$I AI.INC}

  begin
    Randomize;
    ClrScr;
    Cnt := 0;
    for i := 1 to 4 do CNum [i] := 0;
    while not CheckValid (CNum) do for i := 1 to 4 do CNum [i] := Random (10);
    {$IFDEF DEBUG}
    for i := 1 to 4 do DrawSym (40 + i , 0 , 48 + CNum [i] , 9);
    {$ENDIF}
    DrawStr (0 , 0 , '----' , 12);
    repeat
      ReadNum (Ask);
      Ans := Check (Ask , CNum);
      DrawStr (0 , 0 , Chr (Ans div 8 + 48) + ' oxes, ' + Chr (Ans mod 8 + 48) + ' cows' , 12);
      for i := 1 to 4 do DrawSym (60 + i , Cnt , Ask [i] + 48 , 14);
      DrawSym (66 , Cnt , 48 + Ans div 8 , 13);
      DrawSym (67 , Cnt , Ord ('-') , 11);
      DrawSym (68 , Cnt , 48 + Ans mod 8 , 13);
      AI;
      Inc (Cnt);
    until (Check (Ask , CNum) = 32) or (Asks [Cnt] . Ans = 32);
    if Asks [Cnt] . Ans <> 32 then DrawStr (0 , 10 , 'Congratulations, you win!' , 15) else if Ans <> 32 then begin
      DrawStr (0 , 10 , 'You lose! Anser is' , 15);
      for i := 1 to 4 do DrawSym (18 + i , 10 , CNum [i] + 48 , 10);
    end else DrawStr (0 , 10 , 'Nobody wins' , 15);
    ReadLn;
  end.