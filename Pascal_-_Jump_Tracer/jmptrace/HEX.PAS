unit Hex;
interface

   Type
      THexStr=     string[9];

   Const
      HexD         :array[0..15] of Char='0123456789ABCDEF';

   function HexByte(x                  :Byte)    :THexStr;
   function HexWord(x                  :Word)    :THexStr;
   function HexLong(x                  :LongInt) :THexStr;
   function HexPointer(x               :Pointer) :THexStr;

implementation

   function HexByte;
   begin
      HexByte:=HexD[(x and $F0) shr 4]+HexD[x and $0F]
   end;

   function HexWord;
   begin
      HexWord:=HexByte(Hi(x))+HexByte(Lo(x))
   end;

   function HexLong;
   type
      LongRec=
      record
         Lo, Hi    :Word;
      end;
   begin
      HexLong:=HexWord(LongRec(x).Hi)+HexWord(LongRec(x).Lo);
   end;

   function HexPointer;
   begin
      HexPointer:=HexWord(seg(x^))+':'+HexWord(ofs(x^))
   end;

end.

