{$A+,B-,D-,E-,F-,G+,I-,L-,N+,O-,P-,Q-,R-,S-,T-,V-,X+}
{$M 65520,0,655360}
program Tetris;

  const
    ScanCode : Byte = 0;
    DelayCnt : LongInt = 0;
    Walls    : array [1 .. 6] of Byte = ($D5 , $B8 , $D4 , $BE , $CD , $B3);
    Colors   : array [0 .. 5] of Byte = (9 , 10 , 11 , 12 , 13 , 14);
    GO       : array [0 .. 5 , 0 .. 9] of Byte = (($3C , $C0 , $33 , $CC , $3F , $F0 , $30 , $CC , $3F , $3F) ,
                                                  ($C3 , $30 , $73 , $CE , $00 , $0C , $33 , $CC , $00 , $C3) ,
                                                  ($03 , $0C , $B3 , $CD , $0F , $0C , $33 , $CC , $0F , $C3) ,
                                                  ($F3 , $0C , $33 , $CC , $00 , $0C , $33 , $CC , $00 , $3F) ,
                                                  ($C3 , $FC , $33 , $CC , $00 , $0C , $63 , $C6 , $00 , $33) ,
                                                  ($FC , $0C , $33 , $CC , $3F , $F0 , $80 , $C1 , $3F , $C3));
    Figures  : array [0 .. 27] of Word = ($4444 , $0F00 , $4444 , $0F00 ,
                                          $0660 , $0660 , $0660 , $0660 ,
                                          $4620 , $06C0 , $0462 , $0360 ,
                                          $0C60 , $0264 , $0630 , $2640 ,
                                          $4640 , $4E00 , $4C40 , $0E40 ,
                                          $6440 , $8E00 , $44C0 , $0E20 ,
                                          $C440 , $E800 , $4460 , $2E00);

  type
    TAr    = array [0 .. 15 , 0 .. 24] of Byte;
    TState = record
      Ar     : TAr;
      Points : LongInt;
    end;

  var
    i , j , NextN , NextC     : Integer;
    Ar                        : TAr;
    CurN , CurC , CurX , CurY : Integer;
    Speed                     : Word;
    Points , Level            : LongInt;
    FileSave                  : file of TState;
    State                     : TState;

  label
    m1;

  procedure DelayLoop; near; assembler;
    asm
@1:	sub	ax , 1
	sbb	dx , 0
	jc	@2
	cmp	bl , es:[di]
	je	@1
@2:
    end;

  procedure Delay(MS: Word); assembler;
    type
      LongRec = record
        Lo, Hi : Word
      end;
    asm
	mov	es , Seg0040
	mov	ax , DelayCnt.LongRec.Lo
	add	ax , DelayCnt.LongRec.Hi
	or	ax , ax
	jne	@2
	mov	di , $6c
	mov	bl , es:[di]
@1:	cmp	bl , es:[di]
	je	@1
	mov	bl , es:[di]
	mov	ax , -28
	cwd
	call	DelayLoop
	not	ax
	not	dx
	mov	bx , ax
	mov	ax , dx
	xor	dx , dx
	mov	cx , 55
	div	cx
	mov	DelayCnt.LongRec.Hi,ax
	mov	ax , bx
	div	cx
	mov	DelayCnt.LongRec.Lo,ax
@2:	mov	cx , MS
	jcxz	@3
	xor	di , di
	mov	bl , es:[di]
@4:	mov	ax , DelayCnt.LongRec.Lo
	mov	dx , DelayCnt.LongRec.Hi
	call	DelayLoop
	loop	@4
@3:
    end;


  function KeyPressed : Boolean; assembler;
    asm
      cmp	ScanCode , 0
      jne	@@1
      mov	ah , 1
      int	16h
      mov	al , 0
      je	@@2
      @@1:
      mov	al , 1
      @@2:
    end;

  function ReadKey : Char; assembler;
    asm
      mov	al , ScanCode
      mov	ScanCode , 0
      or	al , al
      jne	@@1
      xor	ah , ah
      int	16h
      or	al , al
      jne	@@1
      mov	ScanCode , ah
      or	ah , ah
      jne	@@1
      mov	al , 3
      @@1:
    end;

  function Key : Byte;
    var
      tmp : Byte;
    begin
      Key := 0;
      if not KeyPressed then Exit;
      tmp := Ord (ReadKey);
      if tmp = 0 then tmp := Ord (ReadKey) + 128;
      Key := tmp;
    end;

  procedure GotoXY (x , y : Byte); assembler;
    asm
      mov       ah , 2
      mov       bh , 0
      mov       dl , x
      mov       dh , y
      int       10h
    end;

  procedure DrawSym (x , y , s , c : Byte);
    begin
      Mem [$B800 : (x + 80 * y) * 2] := s;
      Mem [$B800 : (x + 80 * y) * 2 + 1] := c;
    end;

  procedure DrawStr (x , y : Byte; s : string; c : Byte);
    var
      fi : Byte;
    begin
      for fi := 1 to Ord (s [0]) do DrawSym (x + fi - 1 , y , Ord (s [fi]) , c);
    end;

  procedure ClrScr (b : Byte);
    var
      fi : Word;
    begin
      for fi := 0 to 3999 do Mem [$B800 : fi] := b * (fi mod 2);
    end;

  function Str (fd : LongInt) : string;
    var
      fs : string;
    begin
      System . Str (fd , fs);
      while fs [0] < #8 do fs := #32 + fs;
      Str := fs;
    end;

  procedure DrawTable;
    var
      fi , fj : Byte;
    begin
      for fi := 1 to 14 do for fj := 1 to 23 do begin
        DrawSym (24 + fi * 2 , fj , 0 , 16 * Ar [fi , fj]);
        DrawSym (25 + fi * 2 , fj , 0 , 16 * Ar [fi , fj]);
      end;
      if Points >= 1000 * Sqr (Level) then begin
        Inc (Level);
        Speed := Sqr (Speed) div (Speed + 30);
      end;
      DrawStr (10 , 10 , Str (Points) , 206);
      DrawStr (10 , 12 , Str (Level) , 206);
    end;

  procedure Halt;
    begin
      ClrScr (7);
      GotoXY (0 , 0);
      System . Halt;
    end;

  procedure GameOver;
    var
      fi , fj : Byte;
    begin
      ClrScr (16);
      for fi := 0 to 79 do for fj := 0 to 5 do begin
        DrawSym (fi , 6 + fj , 0 , 32 + 160 * ((GO [fj , fi div 8] and (1 shl (fi mod 8))) shr (fi mod 8)));
      end;
      DrawStr (28 , 16 , 'Your score is: ' + Str (Points) , 172);
      while Key <> 27 do;
      Halt;
    end;

  procedure Check;
    var
      fi : Byte;

    procedure DelR (fd : Byte);
      var
        fq , fw : Byte;
      begin
        Inc (fi);
        for fq := fd downto 2 do for fw := 1 to 14 do Ar [fw , fq] := Ar [fw , fq - 1];
        Inc (Points , 100);
        DrawTable;
      end;

    procedure CheckR (fd : Byte);
      var
        fj : Byte;
        fb : Boolean;
      begin
        fb := True;
        for fj := 1 to 14 do fb := fb and (Ar [fj , fd] <> 0);
        if fb then DelR (fd);
      end;

    begin
      fi := 23;
      while fi > 1 do begin
        CheckR (fi);
        Dec (fi);
      end;
    end;

  procedure CreateFigure;
    var
      fi , fj : Integer;
    begin
      Check;
      CurN := NextN;
      CurC := NextC;
      CurX := Random (10) + 1;
      CurY := 1;
      NextN := Random (28);
      NextC := Colors [Random (6)];
      for fi := 0 to 3 do for fj := 0 to 3 do begin
        DrawSym (60 + fi * 2 , 3 + fj , 0 , 16 * NextC * (Figures [NextN] and (1 shl (fi + 4 * fj)) shr (fi + 4 * fj)));
        DrawSym (61 + fi * 2 , 3 + fj , 0 , 16 * NextC * (Figures [NextN] and (1 shl (fi + 4 * fj)) shr (fi + 4 * fj)));
      end;
      for fi := 0 to 3 do for fj := 0to 3 do if ((Figures [CurN] and (1 shl (fi + 4 * fj)) shr (fi + 4 * fj)) = 1) then
        begin
          if (Ar [CurX + fi , CurY + fj] <> 0) then GameOver else
            Ar [CurX + fi , CurY + fj] := CurC;
        end;
      DrawTable;
    end;

  function MoveFigure (dx , dy : ShortInt) : Boolean;
    var
      fi , fj : Byte;
    begin
      MoveFigure := False;
      for fi := 0 to 3 do for fj := 0 to 3 do if (Figures [CurN] and (1 shl (fi + 4 * fj)) div (1 shl (fi + 4 * fj))) = 1 then
        Ar [CurX + fi , CurY + fj] := 0;
      CurX := CurX + dx;
      CurY := CurY + dy;
      for fi := 0 to 3 do for fj := 0 to 3 do if (Figures [CurN] and (1 shl (fi + 4 * fj)) div (1 shl (fi + 4 * fj))) = 1 then
        if (Ar [CurX + fi , CurY + fj] <> 0) then begin
          CurX := CurX - dx;
          CurY := CurY - dy;
          for fi := 0 to 3 do for fj := 0 to 3 do if (Figures [CurN] and (1 shl (fi + 4 * fj)) div (1 shl (fi + 4 * fj))) = 1
            then Ar [CurX + fi , CurY + fj] := CurC;
          if dy <> 0 then CreateFigure;
          Exit;
        end;
      for fi := 0 to 3 do for fj := 0 to 3 do if (Figures [CurN] and (1 shl (fi + 4 * fj)) div (1 shl (fi + 4 * fj))) = 1 then
        Ar [CurX + fi , CurY + fj] := CurC;
      DrawTable;
      MoveFigure := True;
    end;

  procedure RotateFigure;
    var
      OldN    : Byte;
      fi , fj : Byte;
    begin
      for fi := 0 to 3 do for fj := 0 to 3 do if (Figures [CurN] and (1 shl (fi + 4 * fj)) div (1 shl (fi + 4 * fj))) = 1 then
        Ar [CurX + fi , CurY + fj] := 0;
      OldN := CurN;
      CurN := (CurN div 4) * 4 + (CurN + 1) mod 4;
      for fi := 0 to 3 do for fj := 0 to 3 do if (Figures [CurN] and (1 shl (fi + 4 * fj)) div (1 shl (fi + 4 * fj))) = 1 then
        if (Ar [CurX + fi , CurY + fj] <> 0) then begin
          CurN := OldN;
          for fi := 0 to 3 do for fj := 0 to 3 do if (Figures [CurN] and (1 shl (fi + 4 * fj)) div (1 shl (fi + 4 * fj))) = 1
            then Ar [CurX + fi , CurY + fj] := CurC;
          Exit;
        end;
      for fi := 0 to 3 do for fj := 0 to 3 do if (Figures [CurN] and (1 shl (fi + 4 * fj)) div (1 shl (fi + 4 * fj))) = 1 then
        Ar [CurX + fi , CurY + fj] := CurC;
      DrawTable;
    end;

  procedure Init;
    var
      fi , fj : Byte;
    begin
      Randomize;
      Points := 0;
      Level := 1;
      for fi := 0 to 15 do Ar [fi , 0] := 1;
      for fi := 0 to 15 do Ar [fi , 24] := 1;
      for fi := 0 to 24 do Ar [0 , fi] := 1;
      for fi := 0 to 24 do Ar [15 , fi] := 1;
      if ParamCount <> 0 then if ParamStr (1) = '-r' then begin
        Assign (FileSave , 'tetris.dat');
        ReSet (FileSave);
        Read (FileSave , State);
        Points := State . Points;
        Ar := State . Ar;
        Close (FileSave);
      end;
      ClrScr (39);
      GotoXY (79 , 24);
      DrawSym (25 , 0 , Walls [1] , 30);
      DrawSym (54 , 0 , Walls [2] , 30);
      DrawSym (25 , 24 , Walls [3] , 30);
      DrawSym (54 , 24 , Walls [4] , 30);
      for fi := 26 to 53 do DrawSym (fi , 0 , Walls [5] , 30);
      for fi := 26 to 53 do DrawSym (fi , 24 , Walls [5] , 30);
      for fi := 1 to 23 do DrawSym (25 , fi , Walls [6] , 30);
      for fi := 1 to 23 do DrawSym (54 , fi , Walls [6] , 30);
      for fi := 26 to 53 do for fj := 1 to 23 do DrawSym (fi , fj , 0 , 7);
      Speed := 400;
      DrawStr (0 , 10 , 'Score:    ' , 217);
      DrawStr (0 , 12 , 'Level:    ' , 217);
      NextN := Random (28);
      NextC := Colors [Random (6)];
      CreateFigure;
    end;

  begin
    Init;
    while true do begin
      for i := 1 to Speed do begin
        case Key of
          27 : goto m1;
          200: RotateFigure;
          203: MoveFigure (-1 , 0);
          205: MoveFigure (1 , 0);
          208: begin
                 MoveFigure (0 , 1);
                 Inc (Points);
               end;
        end;
        Delay (1);
      end;
      MoveFigure (0 , 1);
    end;
m1:
    for i := 0 to 3 do for j := 0 to 3 do if (Figures [CurN] and (1 shl (i + 4 * j)) div (1 shl (i + 4 * j))) = 1 then
      Ar [CurX + i , CurY + j] := 0;
    Assign (FileSave , 'tetris.dat');
    ReWrite (FileSave);
    State . Ar := Ar;
    State . Points := Points;
    Write (FileSave , State);
    Close (FileSave);
    Halt;
  end.