const
  Answers : array [1 .. 14] of Byte = (0 , 1 , 2 , 3 , 4 , 8 , 9 , 10 , 11 , 16 , 17 , 18 , 24 , 32);

var
  Asks : array [1 .. 10] of record
    Ask : TNum;
    Ans : Byte;
  end;
  Count : Word;
  Vars  : array [1 .. 5041] of TNum;
  h,m,s,s1:word;

procedure AI;

  var
    Max , Min , i , j , k : Word;
    FI                    : Text;
    P                     : TNum;

  function CheckValidAnswer (fA : Byte) : Boolean;
    begin
      CheckValidAnswer := fA in [0 , 1 , 2 , 3 , 4 , 8 , 9 , 10 , 11 , 16 , 17 , 18 , 24 , 32];
    end;

  function TNumEq (f1 , f2 : TNum) : Boolean;
    begin
      TNumEq := (f1 [1] = f2 [1]) and
                (f1 [2] = f2 [2]) and
                (f1 [3] = f2 [3]) and
                (f1 [4] = f2 [4]);
    end;

  procedure BuildVars;
    var
      fI , fJ : Word;
    label
      m1;
    begin
      Count := 0;
      for fI := 0 to 9999 do begin
        P [1] := fI div 1000;
        P [2] := (fI div 100) mod 10;
        P [3] := (fI div 10) mod 10;
        P [4] := fI mod 10;
        if not CheckValid (P) then goto m1;
        for fJ := 1 to Cnt + 1 do if Check (P , Asks [fJ] . Ask) <> Asks [fJ] . Ans then goto m1;
        Inc (Count);
        Vars [Count] := P;
m1:
      end;
    end;

  function GetCountVars : Word;
    var
      fC , fI , fJ : Word;
    label
      m1;
    begin
      fC := 0;
      for fI := 1 to Count do begin
        P := Vars [fI];
        for fJ := 1 to Cnt + 1 do if Check (P , Asks [fJ] . Ask) <> Asks [fJ] . Ans then goto m1;
        Inc (fC);
m1:
      end;
      GetCountVars := fC;
    end;

  procedure CompAsk;
    var
      UsAns , K , Len , fI : Byte;
    label
      m1;
    begin
      for fI := 1 to 4 do DrawSym (30 + fI , 0 , 48 + Asks [Cnt + 1] . Ask [fI] , 11);
      DrawSym (35 , 0 , Ord ('?') , 13);
m1:
      K := 0;
      Len := 0;
      GotoXY (31 , 1);
      DrawStr (31 , 1 , #0#0 , 7);
      while (K <> 13) or (Len <> 2) do begin
        K := Key;
        case K of
          48 .. 52: begin
                      if Len <> 2 then begin
                        Inc (Len);
                        DrawSym (30 + Len , 1 , K , 9);
                        GotoXY (31 + Len , 1);
                      end;
                    end;
          27      : Halt;
          8       : begin
                      if Len <> 0 then begin
                        Dec (Len);
                        DrawSym (31 + Len , 1 , 0 , 7);
                        GotoXY (31 + Len , 1);
                      end;
                    end;
        end;
      end;
      UsAns := (Mem [$B800 : 222] - 48) * 8 + Mem [$B800 : 224] - 48;
      if not CheckValidAnswer (UsAns) then goto m1;
      for fI := 1 to 4 do DrawSym (70 + fI , Cnt , 48 + Asks [Cnt + 1] . Ask [fI] , 12);
      DrawSym (76 , Cnt , 48 + UsAns div 8 , 9);
      DrawSym (77 , Cnt , Ord ('-') , 13);
      DrawSym (78 , Cnt , 48 + UsAns mod 8 , 9);
      Asks [Cnt + 1] . Ans := UsAns;
    end;

  begin
    case Cnt of
      0: begin
           for i := 1 to 4 do for j := 1 to 10 do Asks [j] . Ask [i] := 0;
           for i := 1 to 10 do Asks [i] . Ans := 0;
           while not CheckValid (Asks [1] . Ask) do for i := 1 to 4 do Asks [1] . Ask [i] := Random (10);
           CompAsk;
         end;
      1: if not (Asks [1] . Ans in [4 , 11 , 18]) then begin
           while (not CheckValid (Asks [2] . Ask)) or (Check (Asks [1] . Ask , Asks [2] . Ask) <> 0) do for i := 1 to 4 do
               Asks [2] . Ask [i] := Random (10);
           CompAsk;
           BuildVars;
           if Count = 0 then begin
             DrawStr (0 , 10 , 'You are f*ckin cheater! You give wrong information!' , 15);
             ReadLn;
             Halt;
           end;
         end else begin
           Dec (Cnt);
           BuildVars;
           Inc (Cnt);
           P := Asks [1] . Ask;
           while TNumEq (P , Asks [1] . Ask) do P := Vars [Random (Count) + 1];
           Asks [2] . Ask := P;
           CompAsk;
           BuildVars;
           if Count = 0 then begin
             DrawStr (0 , 10 , 'You are f*ckin cheater! You give wrong information!' , 15);
             ReadLn;
             Halt;
           end;
         end;
      2 .. 6: begin
                Dec (Cnt);
                BuildVars;
                Inc (Cnt);
               {P := Vars [Random (Count) + 1];}
                Min := 65535;
                P := Vars [1];
                for i := 1 to Count do begin
                  Asks [Cnt + 1] . Ask := Vars [i];
                  Max := 0;
                  for j := 1 to 14 do begin
                    if Key = 27 then begin
                      Halt;
                    end;
                    Asks [Cnt + 1] . Ans := Answers [j];
                    Inc (Cnt);
                    k := GetCountVars;
                    if Max < k then Max := k;
                    Dec (Cnt);
                  end;
                  if Min > Max then begin
                    Min := Max;
                    P := Vars [i];
                  end;
                end;
                Asks [Cnt + 1] . Ask := P;
                CompAsk;
                BuildVars;
                if Count = 0 then begin
                  DrawStr (0 , 10 , 'You are f*ckin cheater! You give wrong information!' , 15);
                  ReadLn;
                  Halt;
                end;
              end;
    end;
  end;