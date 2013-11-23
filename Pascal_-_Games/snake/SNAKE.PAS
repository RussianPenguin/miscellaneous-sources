program Snake;

  uses
    New_Crt;

  type
    TPoint = record
      x , y : Byte;
    end;

  const
    PointX                               = 60;
    PointColor                           = 14;
    AppleColor                           = 12;
    BorderColor                          = 15;
    ColorSn     : array [0 .. 1] of Byte = (10 , 9);

  var
    a , a2 , i , j        : Byte;
    Sn                    : array [1 .. 4000] of TPoint;
    Speed , curTime , Len : Word;
    Points                : LongInt;
    Apple                 : TPoint;
    Err                   : Integer;

  label
    m1;

  function Key : Byte;
    var
      tmp : Byte;
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

  procedure Die;
    begin
      Delay (Speed * 2);
      ClrScr;
      TextColor (Red);
      WriteLn ('You Lose!!!');
      TextColor (Green);
      Write (Points);
      TextColor (Blue);
      WriteLn (' points');
      TextColor (7);
      ReadKey;
      Halt;
    end;

  function GetA (a1 , a2 : TPoint) : Byte;
    begin
      GetA := 1;
      if a1 . x < a2 . x then GetA := 2;
      if a1 . x > a2 . x then GetA := 4;
      if a1 . y < a2 . y then GetA := 3;
    end;

  procedure DrawSnake;
    var
      fI : Word;
      fC : Byte;
    begin
      case GetA (Sn [2] , Sn [1]) of
        1: DrawSym (Sn [1] . x , Sn [1] . y , $1E , ColorSn [0]);
        2: DrawSym (Sn [1] . x , Sn [1] . y , $10 , ColorSn [0]);
        3: DrawSym (Sn [1] . x , Sn [1] . y , $1F , ColorSn [0]);
        4: DrawSym (Sn [1] . x , Sn [1] . y , $11 , ColorSn [0]);
      end;
      for fI := 2 to Len - 1 do begin
        case GetA (Sn [fI] , Sn [fI - 1]) + GetA (Sn [fI] , Sn [fI + 1]) * 5 of
           9 , 21: fC := $BC;
          19 , 23: fC := $BB;
           7 , 11: fC := $C8;
          13 , 17: fC := $C9;
           8 , 16: fC := $BA;
          14 , 22: fC := $CD;
        end;
        DrawSym (Sn [fI] . x , Sn [fI] . y , fC , ColorSn [(fI + 1) mod 2]);
      end;
      case GetA (Sn [Len] , Sn [Len - 1]) of
        1: DrawSym (Sn [Len] . x , Sn [Len] . y , $1E , ColorSn [(Len + 1) mod 2]);
        2: DrawSym (Sn [Len] . x , Sn [Len] . y , $10 , ColorSn [(Len + 1) mod 2]);
        3: DrawSym (Sn [Len] . x , Sn [Len] . y , $1F , ColorSn [(Len + 1) mod 2]);
        4: DrawSym (Sn [Len] . x , Sn [Len] . y , $11 , ColorSn [(Len + 1) mod 2]);
      end;
    end;

  procedure DrawPoints;
    var
      fS : string;
      fI : Byte;
    begin
      Str (Points , fS);
      for fI := 1 to 9 - Ord (fS [0]) do fS := '0' + fS;
      for fI := 1 to 9 do DrawSym (PointX + fI , 24 , Ord (fS [fI]) , PointColor);
    end;

  procedure CreateApple;
    var
      fX , fY : Byte;
    begin
      fX := 0;
      fY := 0;
      while not (Mem [$B800 : (fX + fY * 80) * 2] in [0 , 15 , 32]) do begin
        fX := Random (78) + 1;
        fY := Random (22) + 1;
      end;
      Apple . x := fX;
      Apple . y := fY;
      DrawSym (Apple . x , Apple . y , $0F , AppleColor);
    end;

  procedure Init;
    var
      fI : Word;
    begin
      Randomize;
      ClrScr;
      Crt_Init;
      GotoXY (80 , 25);
      for fI := 0 to 3999 do Mem [$B800 : i] := 0;
      DrawSym (0 , 0 , $DA , BorderColor);
      DrawSym (79 , 0 , $BF , BorderColor);
      DrawSym (0 , 23 , $C0 , BorderColor);
      DrawSym (79 , 23 , $D9 , BorderColor);
      for fI := 1 to 78 do DrawSym (fI , 0 , $C4 , BorderColor);
      for fI := 1 to 78 do DrawSym (fI , 23 , $C4 , BorderColor);
      for fI := 1 to 22 do DrawSym (0 , fI , $B3 , BorderColor);
      for fI := 1 to 22 do DrawSym (79 , fI , $B3 , BorderColor);
      Len := 3;
      a := 2;
      a2 := 2;
      Sn [1] . x := 41;
      Sn [1] . y := 10;
      Sn [2] . x := 40;
      Sn [2] . y := 10;
      Sn [3] . x := 39;
      Sn [3] . y := 10;
      DrawSnake;
      DrawPoints;
      CreateApple;
    end;

  procedure MoveSnake;
    var
      fI : Word;
      fX : TPoint;
    begin
      fX := Sn [Len];
      DrawSym (Sn [Len] . x , Sn [Len] . y , 0 , 0);
      for fI := Len downto 2 do Sn [fI] := Sn [fI - 1];
      case a of
        1: Dec (Sn [1] . y);
        2: Inc (Sn [1] . x);
        3: Inc (Sn [1] . y);
        4: Dec (Sn [1] . x);
      end;
      if not (Mem [$B800 : (Sn [1] . x + 80 * Sn [1] . y) * 2] in [0 , 15 , 32]) then Die;
      if (Sn [1] . x = Apple . x) and (Sn [1] . y = Apple . y) then begin
        Inc (Points , 100);
        if (Points mod 100) = 0 then Speed := (Speed * 100000) div (100000 + Speed);
        Inc (Len);
        Sn [Len] := fX;
        DrawPoints;
        CreateApple;
      end;
    end;

  begin
    Init;
    curTime := 0;
    Speed := 700;
    if ParamCount <> 0 then Val (ParamStr (1) , Speed , Err);
    if Err <> 0 then Speed := 700;
    while True do begin
      Delay (1);
      case Key of
         27: goto m1;
        200: if a <> 3 then a2 := 1;
        203: if a <> 2 then a2 := 4;
        205: if a <> 4 then a2 := 2;
        208: if a <> 1 then a2 := 3;
      end;
      Inc (curTime);
      if curTime = Speed then begin
        a := a2;
        MoveSnake;
        curTime := 0;
      end;
      DrawSnake;
    end;
m1:
  end.