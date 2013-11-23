
(*
 * MiniCrt - simplified version of Borland's CRT unit.
 * Does not EVER do direct video.  The standard crt unit
 * locks up multi-taskers with its direct video checking before
 * the user program can turn it off.
 *
 * Samuel H. Smith, 20-dec-87
 *
 *)

{$i prodef.inc}

unit MiniCrt;

interface

   uses
      Dos;

   var
      stdout:  text;  {output through dos for ANSI compatibility}

   function KeyPressed: Boolean;
   function ReadKey: Char;

   procedure Window(X1,Y1,X2,Y2: Byte);  {only partial support}

   procedure GotoXY(X,Y: Byte);
   function WhereX: Byte;
   function WhereY: Byte;

   procedure ClrScr;
   procedure ClrEol;

   procedure NormalVideo;
   procedure ReverseVideo;
   procedure BlinkVideo;


   (* -------------------------------------------------------- *)
   procedure ScrollUp;
   {$F+} function ConFlush(var F: TextRec): integer; {$F-}
   {$F+} function ConOutput(var F: TextRec): integer; {$F-}
   {$F+} function ConOpen(var F: TextRec): Integer; {$F-}


(* -------------------------------------------------------- *)
implementation

   const
      window_y1  : byte = 1;
      window_y2  : byte = 25;
      TextAttr   : byte = $0f;
      key_pending: char = #0;


   (* -------------------------------------------------------- *)
   function ReadKey: Char;
   var
      reg: registers;
   begin
      if key_pending <> #0 then
      begin
         ReadKey := key_pending;
         key_pending := #0;
         exit;
      end;

      reg.ax := $0100;   {check for character}
      intr($16,reg);
      if (reg.flags and FZero) = 0 then
      begin
         reg.ax := $0000;   {wait for character}
         intr($16,reg);
         if reg.al = 0 then
            key_pending := chr(reg.ah);
      end
      else

      begin
         reg.ax := $0700;   {direct console input}
         msdos(reg);
      end;

      ReadKey := chr(reg.al);
   end;


   (* -------------------------------------------------------- *)
   function KeyPressed: Boolean;
   var
      reg: registers;
   begin
      reg.ax := $0b00;   {ConInputStatus}
      msdos(reg);
      KeyPressed := (reg.al = $FF) or (key_pending <> #0);
   end;


   (* -------------------------------------------------------- *)
   procedure Window(X1,Y1,X2,Y2: Byte);
   begin
      window_y1 := y1;
      window_y2 := y2;
   end;


   (* -------------------------------------------------------- *)
   procedure GotoXY(X,Y: Byte);
   var
      reg: registers;
   begin
      reg.ah := 2;   {set cursor position}
      reg.bh := 0;   {page}
      reg.dh := y-1;
      reg.dl := x-1;
      intr($10,reg);
   end;


   (* -------------------------------------------------------- *)
   function WhereX: Byte;
   var
      reg: registers;
   begin
      reg.ah := 3;
      reg.bh := 0;
      intr($10,reg);
      WhereX := reg.dl+1;
   end;

   function WhereY: Byte;
   var
      reg: registers;
   begin
      reg.ah := 3;
      reg.bh := 0;
      intr($10,reg);
      WhereY := reg.dh+1;
   end;


   (* -------------------------------------------------------- *)
   procedure ClrScr;
   var
      reg: registers;
   begin
      reg.ax := $0600;  {scroll up, blank window}
      reg.cx := 0;      {upper left}
      reg.dx := $194F;  {line 24, col 79}
      reg.bh := TextAttr;
      intr($10,reg);
      GotoXY(1,1);
   end;


   (* -------------------------------------------------------- *)
   procedure ClrEol;
   var
      reg: registers;
   begin
      reg.ax := $0600;  {scroll up, blank window}
      reg.ch := wherey-1;
      reg.cl := wherex-1;
      reg.dh := reg.ch;
      reg.dl := 79; {lower column}
      reg.bh := TextAttr;
      intr($10,reg);
   end;


   (* -------------------------------------------------------- *)
   procedure NormalVideo;
   begin
      TextAttr := $0f;
   end;

   procedure ReverseVideo;
   begin
      TextAttr := $70;
   end;

   procedure BlinkVideo;
   begin
      TextAttr := $F0;
   end;


   (* -------------------------------------------------------- *)
   procedure ScrollUp;
   var
      reg: registers;
   begin
      reg.ah := 6;            {scroll up}
      reg.al := 1;            {lines}
      reg.cx := 0;            {upper left}
      reg.dh := window_y2-1;  {lower line}
      reg.dl := 79;           {lower column}
      reg.bh := TextAttr;
      intr($10,reg);
   end;


   (* -------------------------------------------------------- *)
   {$F+} function ConFlush(var F: TextRec): integer; {$F-}
   var
      P:   Word;
      reg: registers;
      x,y: byte;

   begin
      {get present cursor position}
      reg.ah := 3;
      reg.bh := 0;
      intr($10,reg);
      y := reg.dh+1;
      x := reg.dl+1;

      {process each character in the buffer}
      P := 0;
      while P < F.BufPos do
      begin
         reg.al := ord(F.BufPtr^[P]);

         case reg.al of
             7:  write(stdout,^G);

            10:  if y >= window_y2 then   {scroll when needed}
                    ScrollUp
                 else
                    inc(y);

            13:  x := 1;

            else 
            begin
                 reg.ah := 9;  {display character with TextAttr}
                 reg.bx := 0;  {... does not move the cursor}
                 reg.cx := 1;
                 reg.bl := TextAttr;
                 intr($10,reg);

                 if x = 80 then   {line wrap?}
                 begin
                    x := 1;
                    if y >= window_y2 then   {scroll during wrap?}
                       ScrollUp
                    else
                       inc(y);
                 end
                 else
                    inc(x);
            end;
         end;

         {position physical cursor}
         reg.ah := 2;   {set cursor position}
         reg.bh := 0;   {page}
         reg.dh := y-1;
         reg.dl := x-1;
         intr($10,reg);

         inc(P);
      end;

      F.BufPos:=0;
      ConFlush := 0;
   end;


   {$F+} function ConOutput(var F: TextRec): integer; {$F-}
   begin
      ConOutput := ConFlush(F);
   end;


   {$F+} function ConOpen(var F: TextRec): Integer; {$F-}
   begin
      F.InOutFunc := @ConOutput;
      F.FlushFunc := @ConFlush;
      F.CloseFunc := @ConFlush;
      F.BufPos := 0;
      ConOpen := 0;
   end;


   (* -------------------------------------------------------- *)
var
   e: integer;
   
begin

{$IFDEF DEBUGGING}
   writeln('minicrt init');
{$ENDIF}

   with TextRec(output) do
   begin
      InOutFunc := @ConOutput;
      FlushFunc := @ConFlush;
      OpenFunc  := @ConOpen;
      BufPos := 0;
   end;

   {error #18 has been reported here when operating under desqview}
   {what is 18, anyway??}
   assign(stdout,'');
   {$i-} rewrite(stdout); {$i+}
   e := ioresult;
   if e <> 0 then 
      writeln('[error ',e,' on stdout]');
end.

