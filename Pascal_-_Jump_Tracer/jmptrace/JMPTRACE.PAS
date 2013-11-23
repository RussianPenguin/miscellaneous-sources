{$M 2048,0,655360}
{$G+,N-,E-,B-,R-,S-,I-,O-,A+}
uses
   DOS, Memory,
   Hex;

const
   VStr =          '1.3';

   DumpFile        :String[12] =
   'DUMP0000.TMP';

   DumpsKind       :Array ['1'..'2'] of Boolean =
   (False, False);

   FlagName        :Array [1..3] of Char =
   '?NY';

   BaseInt =       $C0;

   IRET            :Byte = $CF;

   Running         :Boolean= False;

type
   TJumpDump =     Array [0..60*1024-1] of Byte;
   TAllInts =      Array [0..$FF] of Pointer;

var
   Jumps           :TJumpDump;

   Pattern         :Array [0..15] of Byte;
   PatternFound    :Boolean;

   PatternAddr     :Pointer;

   PatternOffset   :Word;

   Dumps           :Array ['0'..'7'] of Char;
   Chr             :Char;

   PrgParams       :ComStr;

   Last1           :Pointer;

   f               :File;

   Stack           :Array [0..$1F] of Byte;
   PSP             :Word;

   AllInts         :TAllInts absolute 0:0;
   SaveAllInts     :TAllInts;

procedure New1; assembler;
asm
   db   0, 0, 0
end;

procedure Default1; assembler;
asm
   db   0, 0, 0
end;

procedure SaveStack; assembler;
asm
   db   0, 0, 0
end;

procedure Int1; assembler;
asm
   nop

   mov  word ptr cs:SaveStack,sp
   mov  word ptr cs:SaveStack+2,ss

   mov  sp,seg @DATA
   mov  ss,sp
   mov  sp,offset Stack +type Stack

   push bp
   push es
   push ax
   pushf
   les  bp,dword ptr cs:SaveStack
   les  bp,es:[bp]
   mov  ax,word ptr es:[bp]

   cmp  al,0E0h
   jb   @@CheckJump
   cmp  al,0E3h
   ja   @@NoJump
   jmp  @@JumpOrLoop

@@CheckJump:
   cmp  al,70h
   jb   @@NoJump
   cmp  al,7Fh
   ja   @@NoJump

@@JumpOrLoop:
   popf
   pusha
   push ds

   push ss
   pop  ds

   mov  al,byte ptr es:[bp]
   mov  byte ptr cs:@@Jump,al
   mov  ah,80h
   jmp  @@Jump
@@Jump:
   jz   @@ReallyJump
   xor  ah,40h
@@ReallyJump:

   mov  bx,es
   sub  bx,PSP
   jc   @@Done
   add  bx,bx
   jc   @@Done

   mov  cx,bp
   mov  di,bp
   shr  di,3
   add  bx,di
   jc   @@Done

   cmp  bx,type Jumps
   ja   @@Done

   shr  cx,1
   and  cl,3
   add  cx,cx

   mov  al,byte ptr [Jumps+bx]
   shl  al,cl
   and  al,0C0h
   jz   @@LeaveIt
   cmp  al,ah
   je   @@LeaveIt
   mov  al,3Fh
   ror  al,cl
   and  byte ptr [Jumps+bx],al
   mov  ah,40h
@@LeaveIt:

   shr  ah,cl
   or   byte ptr [Jumps+bx],ah

   cmp  bx,PatternOffset
   jne  @@Done
   mov  PatternFound,True
   mov  word ptr PatternAddr,bp
   mov  ax,es
   sub  ax,PSP
   mov  word ptr PatternAddr+2,ax
   push ds
   push es
   pop  ds
   pop  es
   mov  di,offset Pattern
   mov  si,bp
   mov  cx,8
   cld
   rep  movsw

@@Done:
   pop  ds
   popa

@@Exit:
   pop  ax
   pop  es
   pop  bp

   mov  sp,word ptr cs:SaveStack
   mov  ss,word ptr cs:SaveStack+2
   iret

@@NoJump:
   mov  bp,es
   cmp  bp,seg @CODE
   jle  @@NoEmulation

   cmp  al,9Ch
   je   @@PushF

   cmp  ax,01CDh
   je   @@Int1

@@NoEmulation:
   popf
   jmp  @@Exit

@@PushF:
   les  bp,dword ptr cs:SaveStack
   inc  word ptr es:[bp]
   and  byte ptr es:[bp+1+4],not 1
   popf
   pop  ax
   pop  es
   pop  bp

   mov  sp,word ptr cs:SaveStack
   mov  ss,word ptr cs:SaveStack+2
   retf

@@Int1:
   popf
   pop  ax
   pop  es
   pop  bp

   mov  sp,word ptr cs:SaveStack
   mov  ss,word ptr cs:SaveStack+2
   jmp  dword ptr cs:New1
end;

procedure UpdateFlag; assembler;
asm
   push ax
   push ds

   push 0
   pop  ds

   pushf
   pop  ax
   and  ah,not 1
   test byte ptr ds:[417h],40h
   jz   @@Off
   cmp  word ptr ds:[1*4+2],seg @CODE
   je   @@On

   push es
   push seg @DATA
   pop  es
   cmp  es:Running,0
   pop  es
   jz   @@Off
   push es
   push cx
   les  cx,dword ptr ds:[1*4]
   mov  word ptr ds:[1*4],offset Int1 +1
   mov  word ptr ds:[1*4+2],cs
   mov  word ptr cs:New1,cx
   mov  word ptr cs:New1+2,es
   pop  cx
   pop  es

@@On:
   or   ah,1

   cmp  word ptr ds:[1*4],offset Int1
   jne  @@UseNew
   push ax
   lds  ax,dword ptr cs:Default1
   mov  word ptr cs:New1,ax
   mov  word ptr cs:New1+2,ds
   pop  ax
@@UseNew:

@@Off:
   push ax
   popf

   pop  ds
   pop  ax
end;

procedure Last21; assembler;
asm
   db   0, 0, 0
end;

procedure Int21; assembler;
asm
   cmp  ax,3501h
   jne  @@Last

   les  bx,dword ptr cs:New1
   jmp  @@Done

@@Last:
   pushf
   call dword ptr cs:Last21

@@Done:
   pusha
   push ds
   pushf
   mov  ah,62h
   pushf
   call dword ptr cs:Last21
   push seg @DATA
   pop  ds
   mov  PSP,bx
   popf
   pop  ds
   popa

   call UpdateFlag

   sti
   retf 2
end;

procedure Last16; assembler;
asm
   db   0, 0, 0
end;

procedure Int16; assembler;
asm
   pushf
   call dword ptr cs:Last16

   call UpdateFlag

   sti
   retf 2
end;

procedure Last9; assembler;
asm
   db   0, 0, 0
end;

procedure IRQ0; assembler;
asm
   int  8
   iret
end;

procedure IRQ1; assembler;
asm
   pushf
   push ax
   in   al,60h
   cmp  al,3Ah
   je   @@Press
   cmp  al,3Ah + 80h
   je   @@Release
   cmp  al,2Ah
   je   @@Abort

@@Last:
   pop  ax
   popf
   int  9
   iret

@@Press:
   xor  ax,ax
   out  60h,al

   push ds
   push 0
   pop  ds
   mov  al,byte ptr ds:[417h]

   pushf
   call dword ptr cs:Last9

   xor  al,byte ptr ds:[417h]
   and  al,40h
   jnz  @@Worked
   xor  byte ptr ds:[417h],40h
@@Worked:

   pop  ds
   pop  ax
   popf

   call UpdateFlag

   sti
   retf 2

@@Release:
   pop  ax
   popf
   jmp  dword ptr cs:Last9

@@Abort:
   push ds
   push seg @DATA
   pop  ds
   mov  ax,PSP
   cmp  ax,PrefixSeg
   mov  ax,ds
   pop  ds
   je   @@Last

   mov  si,offset SaveAllInts
   mov  ds,ax
   xor  di,di
   mov  es,di
   mov  cx,100h*4/2
   cld
   rep  movsw

   mov  al,20h
   out  20h,al

   mov  ax,3
   int  10h

   mov  ah,4Ch
   int  21h

   int  19h
end;

procedure IRQ2; assembler;
asm
   int  0Ah
   iret
end;

procedure IRQ3; assembler;
asm
   int  0Bh
   iret
end;

procedure IRQ4; assembler;
asm
   int  0Ch
   iret
end;

procedure IRQ5; assembler;
asm
   int  0Dh
   iret
end;

procedure IRQ6; assembler;
asm
   int  0Eh
   iret
end;

procedure IRQ7; assembler;
asm
   int  0Fh
   iret
end;

const
   IRQs            :Array [BaseInt..BaseInt+7] of Word = (
   Ofs(IRQ0), Ofs(IRQ1), Ofs(IRQ2), Ofs(IRQ3),
   Ofs(IRQ4), Ofs(IRQ5), Ofs(IRQ6), Ofs(IRQ7));
var
   SaveInts        :Array [BaseInt..BaseInt+7] of Pointer;
   IntNum          :Byte;

procedure SetIRQ(Base                  :Byte); assembler;
asm
   xor  bx,bx
   mov  bh,Base
   mov  dx,20h
   cli
   in   al,0A0h
   inc  al
   jz   @@1
   mov  bl,2
@@1:
   mov  al,15h
   or   al,bl
   xor  al,2
   out  dx,al
   inc  dx
   mov  al,bh
   out  dx,al
   or   bl,bl
   jz   @@2
   mov  al,4
   test dl,80h
   jz   @@3
   mov  al,2
@@3:
   out  dx,al
@@2:
   mov  al,19h
   test dx,80h
   jnz  @@4
   or   al,4
@@4:
   out  dx,al
   sti
end;

function  GetChar(const Msg, List      :String)  :Char;
var
   Key             :Word;
begin
   Write(Msg);
   repeat
      asm
         xor  ax,ax
         int  16h
         mov  Key,ax
      end;
      Chr:=UpCase(Char(Key));
   until (Pos(Chr, List)<>0);
   WriteLn(' ', Chr, #13#10);
   GetChar:=Chr;
end;

procedure Init;
begin
   WriteLn(#13#10'Jump Tracer  Version '+VStr+'  Copyright (c) 1995-96 by Solar Designer \ BPC'#13#10);

   if ParamCount<>1 then
   begin
      WriteLn('Usage: JMPTRACE.EXE <program to crack>'); Halt;
   end;

   InitMemory;

   PSP:=PrefixSeg;

   GetIntVec(1, Pointer(@Default1^));

   SetIntVec($23, @IRET);
   GetIntVec(9, Pointer(@Last9^));

   for IntNum:=BaseInt to BaseInt+7 do
   begin
      GetIntVec(IntNum, SaveInts[IntNum]);
      SetIntVec(IntNum, Ptr(CSeg, IRQs[IntNum]));
   end;
   SetIRQ(BaseInt);

   asm
      push 0
      pop  es
      and  byte ptr es:[417h],not 40h
   end;
end;

procedure Done;
begin
   asm
      push 0
      pop  es
      and  byte ptr es:[417h],not 40h
   end;

   SetIRQ(8);
   for IntNum:=BaseInt to BaseInt+7 do
   SetIntVec(IntNum, SaveInts[IntNum]);

   DoneMemory;

   while DumpFile[8]>='0' do
   begin
      InOutRes:=0;
      Assign(f, DumpFile); Erase(f);

      Dec(DumpFile[8]);
   end;
end;

function  Trace                        :Boolean;
begin
   Write('Enter program parameters: '); ReadLn(PrgParams);

   FillChar(Jumps, SizeOf(Jumps)+SizeOf(Pattern)+SizeOf(PatternFound), 0);

   DoneDosMem;
   SwapVectors;

   GetIntVec(1, Last1);
   SetIntVec(1, @Int1);

   GetIntVec($21, Pointer(@Last21^));
   SetIntVec($21, @Int21);

   GetIntVec($16, Pointer(@Last16^));
   SetIntVec($16, @Int16);

   asm cli end; SaveAllInts:=AllInts; asm sti end;
   Running:=True;
   Exec(ParamStr(1), PrgParams);
   Running:=False; PSP:=PrefixSeg;
   asm cli end; AllInts:=SaveAllInts;
   asm
      in   al,61h
      and  al,0FCh
      out  61h,al

      mov  al,36h
      out  43h,al
      xor  ax,ax
      out  40h,al
      out  40h,al

      out  21h,al

      mov  al,20h
      out  20h,al

      sti
   end;

   SetIntVec($16, Pointer(@Last16^));

   SetIntVec($21, Pointer(@Last21^));

   asm
      pushf
      pop  ax
      and  ah,not 1
      push ax
      popf
   end;

   SetIntVec(1, Last1);

   SwapVectors;
   InitDosMem;

   if DosError<>0 then
   if DosError=8 then WriteLn('Not enough memory')
   else WriteLn('Unable to execute ', FExpand(ParamStr(1)));

   Trace:=(DosError<>0);
end;

function  WriteDump                    :Boolean;
begin
   WriteDump:=False;
   if DumpFile[8]>'7' then Exit;

   if GetChar(
      'Please, identify this state as:'#13#10+
      '1st, 2nd, Nothing?', '12N')='N' then Exit;
   Dumps[DumpFile[8]]:=Chr;
   DumpsKind[Chr]:=True;

   Assign(f, DumpFile); Rewrite(f, 1);
   BlockWrite(f, Jumps, SizeOf(Jumps));
   Close(f);

   if IOResult<>0 then
   begin
      WriteLn('Unable to write the dump'); WriteDump:=True; Exit;
   end;

   Inc(DumpFile[8]);
end;

function  GetFlags(Value, Index        :Byte)    :Byte; assembler;
asm
   mov  al,Value
   imul cx,word ptr Index,2
   shr  al,cl
   and  al,3
end;

function  Compare                      :Boolean;
label
   PatchShown;
var
   Buf             :Array ['0'..'7'] of ^TJumpDump;
   V               :Array ['0'..'7'] of Byte;
   i, j            :Word;
   B, B1, B2       :Byte;
   Found, Sure     :Boolean;
   MatchCount,
   State           :Char;
   PatternOfsS     :String[5];
const
   StateStr        :Array ['1'..'2'] of String[3] =
   ('1st', '2nd');
begin
   Compare:=True;

   Buf['0']:=@Jumps;
   for Chr:='1' to Pred(DumpFile[8]) do
   begin
      Buf[Chr]:=MemAlloc(SizeOf(TJumpDump));
      if Buf[Chr]=nil then
      begin
         WriteLn('Not enough memory'); Exit;
      end;
   end;

   for Chr:='0' to Pred(DumpFile[8]) do
   begin
      Assign(f, 'DUMP000'+Chr+'.TMP'); Reset(f, 1);
      BlockRead(f, Buf[Chr]^, SizeOf(TJumpDump));
      Close(f);

      if IOResult<>0 then
      begin
         WriteLn('Unable to read dump #', Succ(Chr)); Exit;
      end;
   end;

   WriteLn('Smartly comparing and filtering...'#13#10);

   Found:=False;
   for i:=Low(TJumpDump) to High(TJumpDump) do
   if Buf['0']^[i]<>0 then
   for j:=0 to 3 do
   begin
      MatchCount:='1'; Sure:=True;

      for Chr:='1' to Pred(DumpFile[8]) do
      if (Dumps[Chr]=Dumps[Pred(Chr)]) xor
         (Buf[Chr]^[i]<>Buf[Pred(Chr)]^[i]) then
      begin
         B1:=GetFlags(Buf[Chr]^[i], j); B2:=GetFlags(Buf[Pred(Chr)]^[i], j);

         if (Dumps[Chr]=Dumps[Pred(Chr)]) then
         if (B1=B2) then Inc(MatchCount) else Break else
         if ((B1<>B2) and (B1<>0) and (B2<>0)) then
         begin
            Sure:=Sure and ((B1 and B2) and 2 <> 0);
            Inc(MatchCount)
         end else Break;
      end;

      if MatchCount=DumpFile[8] then
      begin
         if Sure then Write('!') else Write('?');
         Write(': Internal offset ', HexWord(i), ':');
         for Chr:='0' to Pred(DumpFile[8]) do
            Write(' ', FlagName[GetFlags(Buf[Chr]^[i], j)]);
         WriteLn;
         Found:=True;
      end;
   end;

   for Chr:='1' to Pred(DumpFile[8]) do FreeMem(Buf[Chr], SizeOf(TJumpDump));

   if Found then
   begin
      WriteLn;
      repeat
         GetChar('Return, Display?', 'RD');

         case Chr of
            'D':
            begin
               Write(
                  'The program will now be traced once more, you may have to enable saving for a'#13#10+
                  'long time to find the desired jump'#13#10#13#10+
                  'Enter offset: ');
               ReadLn(PatternOfsS);
               Val('$'+PatternOfsS, PatternOffset, i);
               if i<>0 then
               begin
                  WriteLn; Continue;
               end;

               if Trace then Exit;

               if PatternFound then
               begin
                  for Chr:='0' to Pred(DumpFile[8]) do
                  begin
                     Assign(f, 'DUMP000'+Chr+'.TMP'); Reset(f, 1);
                     Seek(f, PatternOffset); BlockRead(f, V[Chr], 1);
                     Close(f);

                     if IOResult<>0 then
                     begin
                        WriteLn('Unable to read dump #', Succ(Chr)); Exit;
                     end;
                  end;

                  Write(#13#10'PSP+', HexPointer(PatternAddr), ':');
                  for PatternOffset:=0 to High(Pattern) do
                     Write(' ', HexByte(Pattern[PatternOffset]));
                  WriteLn;

                  for State:='1' to '2' do
                  begin
                     Write('Use ', StateStr[State], ' state: ');

                     for Chr:='0' to Pred(DumpFile[8]) do
                     for j:=0 to 3 do
                     if (Dumps[Chr]=State) and (GetFlags(V[Chr], j) and 2<>0) then
                     begin
                        if GetFlags(V[Chr], j) and 1 = 0
                        then WriteLn('EB')
                        else WriteLn('90 90');
                        goto PatchShown;
                     end;
                     WriteLn('PATCH NOT AVAILABLE');
PatchShown:
                  end;

                  WriteLn;
               end else WriteLn(#13#10'Specified offset not found'#13#10);

               if WriteDump then Exit;
            end;
         end;
      until Chr='R';
   end else WriteLn('No significant differences found'#13#10);

   Compare:=False;
end;

procedure Run;
begin
   if GetChar(
      'Use <Caps Lock> to turn saving on/off while tracing, left <Shift> to abort'#13#10+
      'Trace, Quit?', 'TQ')='Q' then Exit;

   repeat
      case Chr of
         'T':
         begin
            PatternOffset:=0;
            if Trace or WriteDump then Break;
         end;
         'C':
            if Compare then Break;
      end;

      if DumpFile[8]>'0' then
      begin
         Write('You''ve saved ', DumpFile[8], ' dump');
         if DumpFile[8]>'1' then Write('s');
         if DumpsKind['1'] and DumpsKind['2']
         then WriteLn(' by now; you can compare them'#13#10)
         else WriteLn(' by now; at least 2 different dumps are required to crack'#13#10);
      end;

      if (DumpFile[8]<'2') or not
         (DumpsKind['1'] and DumpsKind['2']) then GetChar('Trace, Quit?', 'TQ') else
      if DumpFile[8]>'7' then GetChar('Compare, Quit?', 'CQ') else
      GetChar('Trace, Compare, Quit?', 'TCQ');
   until Chr='Q';
end;

begin
   Init;
   Run;
   Done;
end.

