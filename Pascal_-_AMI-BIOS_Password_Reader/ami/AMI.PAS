{$A-,B-,D-,E-,F-,G-,I-,L-,N-,O-,P-,Q-,R-,S-,T-,V-,X-}
{$M $400,0,0}

var
    I, Last, Next, Pwd : Byte;

Procedure ReadPort; assembler;
asm
     mov   al, Next
     mov   Last, al
     xor   ah, ah
     mov   al, I
     mov   dx, $070
     out   dx, al
     mov   dx, $071
     in    al, dx
     mov   Next, al
     inc   I
end;

begin
     WriteLn('AMI-BIOS CMOS password reader by SVV.');
     Write('=> ');
     Pwd:=$FF;
     I:=$037;
     ReadPort;
     While Pwd <> 0 do
          begin
           ReadPort;
           asm
                   xor    bl, bl
                   mov    al, Next
                   cbw
                   or     ax, ax
                   jne    @loc5
                   jmp    @loc6
           @loc5:  test   al, $80
                   je     @loc1
                   test   al, $61
                   jnp    @loc2
                   stc
           @loc2:  rcl    al, 1
                   jmp    @loc3
           @loc1:  test   al, $61
                   jp     @loc4
                   stc
           @loc4:  rcl    al, 1
           @loc3:  inc    bl
                   cmp    al, Last
                   jne    @loc5
                   mov    Pwd, bl
                   jmp    @loc7
           @loc6:  mov    Pwd, 0
           @loc7:
           end;
           if Pwd <> 0 then Write(Chr(Pwd));
          end;
     WriteLn;
end.