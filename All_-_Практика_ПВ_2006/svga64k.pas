 
{ ************************************************************* } 
{ -=Svga64k Module ver2.03=- (Last update 22.04.1999)                  } 
{ Supporting Modes:640x480x16bit; All other possible w update;  } 
{ Languages: English, Russian!!! in GraphMode!                  } 
{ Mouse support: PresenT!                                    } 
{ Stack size 32768 is *strongly* recomended!                    } 
{ Writen by [AsP]-UncoNNecteD -=Greatest Unc=-                      } 
{ ************************************************************* } 
{$M 32768,0,65535} 
unit svga64k; 
  
{---------------------------------------------------------------------------} 
INTERFACE 
{---------------------------------------------------------------------------} 
  
uses DOS; 
  
type 
  gl_color = record gb:byte;rg:byte;end; 
  gl_Tpalette = array[0..256] of gl_color; 
  
  {Матьричные шрифты!} 
  TChar8 = array [1..8] of byte; 
  TFont8 = array [0..255] of TChar8; 
  
  TChar16 = array [1..16] of byte; 
  TFont16 = array [0..255] of TChar16; 
  
  TChar14 = array [1..14] of byte; 
  TFont14 = array [0..255] of TChar14; 
  
  Font8File = file of TFont8; 
  Font16File = file of TFont16; 
  Font14File = file of Tfont14; 
  {Конец типизации МШ-oB} 
  
  {Векторные шрифты Ё NO!} 
  
  {Спрайты-Ж} 
  gl_Sprite = record 
              xsize,ysize,fnum:byte; 
              size:word; 
              Pstart:^byte; 
              end; 
  
  gl_SpriteFile = file of byte; 
  
  
  
const 
  gl_lenline:word = 640; 
  {Color Constants} 
  gl_Black:byte = 0; 
  gl_Blue:byte = 1; 
  gl_Green:byte = 2; 
  gl_Cyan:byte = 3; 
  gl_Red:byte = 4; 
  gl_Magenta:byte = 5; 
  gl_Brown:byte = 6; 
  gl_LightGray:byte = 7; 
  gl_DarkGray:byte = 8; 
  gl_LightBlue:byte = 9; 
  gl_LightGreen:byte = 10; 
  gl_LightCyan:byte = 11; 
  gl_LightRed:byte = 12; 
  gl_LightMagenta:byte = 13; 
  gl_Yellow:byte = 14; 
  gl_White:byte = 15; 
  
  f8x8:byte = 1; 
  f8x16:byte = 2; 
  f8x14:byte = 3; 
  
var gbank,current_fontsize:integer; 
    gl_gbcolors,gl_rgcolors:byte; 
    gl_font8:TFont8; 
    gl_font16:TFont16; 
    gl_font14:TFont14; 
    gl_palette:gl_Tpalette; 
    M_Sprite:gl_sprite; 
    M_oldx,M_oldy:integer; 
  
procedure vidbank(b:integer); 
procedure setvideo(mode:integer); 
procedure closevideo; 
{64k function(GL)} 
procedure uncpixel(x,y:integer); 
procedure uncline(x1,y1,x2,y2:word); 
procedure gl_setcolor(r,g,b:byte); 
procedure gl_savecolor(num:byte); 
procedure gl_restorecolor(num:byte); 
procedure gl_putchar(chn:byte;x,y:integer); 
procedure gl_fontinit(size:integer;name:string); 
procedure gl_puttextxy(x,y:integer; txt:string); 
{Sprite support} 
procedure gl_putsprite(spr:gl_Sprite; frame:byte; x,y:integer); 
function LoadSprite(var sv:gl_Sprite;filename:string):boolean; 
procedure FreeSprite(var sv:gl_sprite); 
procedure gl_makesprite(infile,outfile:string; xsize,ysize,frames:byte); 
{Mouse support !} 
function m_init(sv:gl_sprite):byte; {Returns NumOfButtons} 
procedure M_GetMove (var GetX, GetY); 
procedure M_State (var Buttons, PosX, PosY); 
function M_Pressed (var Buttons, PosX, PosY): Word; 
procedure M_Show; 
procedure M_GoToXY (X, Y: Word); 
procedure M_RangeX(Left,Right : Word); 
procedure M_RangeY(Up,Down : Word); 
  
  
{---------------------------------------------------------------------------} 
IMPLEMENTATION 
{---------------------------------------------------------------------------} 
procedure VidBank(b:integer);assembler; 
asm 
  mov dx,b 
  cmp dx,gbank 
  je @end 
  mov ax,4f05h 
  mov bx,0 
  mov gbank,dx 
  push dx 
  int $6d 
  mov bx,1 
  pop dx 
  int $6d 
  @end: 
end; 
  
procedure uncpixel(x,y:integer); 
var 
  bank,offs :word; 
  err       :byte; 
begin 
  x:=x*2;
  y:=y*2;
  err:=0; 
  asm 
    mov ax,x  {Checking range validation} 
    cmp x,1278 
    ja @endpixel 
    mov ax,y 
    cmp y,958 
    ja @endpixel 
    {64k} 
    xor bx,bx 
    mov ax,y 
    mul gl_lenline 
    add ax,x 
    adc dx,bx 
    mov bank,dx 
    mov offs,ax 
    {Setting video Bank} 
    cmp dx,gbank 
    je @setok 
    mov gbank,dx 
    mov ax,4f05h 
    mov bx,0 
    mov dx,bank 
    push dx 
    int $6d 
    mov bx,1 
    pop dx 
    int $6d 
    @setok:{Video Bank} 
    jmp @end 
  @endpixel: 
    mov al,1 
    mov err,al 
  @end: 
  end; 
  if (err=0) then
  begin 
    mem[$a000:offs]:=gl_gbcolors; 
    mem[$a000:offs+1]:=gl_rgcolors; 
  end; 
end; 
  
procedure uncline(x1,y1,x2,y2:word); 
var 
  b, x, y, oldy, oldx, gaddr :Integer;
  bank, del, delx, dely, a   :Integer;
  del1, del2, xchngd, offs   :integer; 
  dz, gaddrxy, bankxy, yxch  :Integer;
begin 
  asm 
    mov ax,x1 
    mov bx,x2 
    cmp ax,bx 
    jl @chkxok 
    mov x1,bx 
    mov x2,ax 
    mov ax,y1 
    mov bx,y2 
    mov y2,ax 
    mov y1,bx 
  @chkxok: 
    mov ax,y1 
    mov bx,y2 
    cmp ax,bx 
    mov cx,0 
    mov yxch,cx 
    jl @chkyok 
    inc cx 
    mov yxch,cx 
    mov y1,bx 
    mov y2,ax 
  @chkyok: 
    cmp x2,641 
    jl @x2menshe 
    mov ax,640 
    mov x2,ax 
  @x2menshe: 
    cmp y2,481 
    jl @y2menshe 
    mov ax,480 
    mov y2,ax 
  @y2menshe: 
    cmp x1,0 
    jge @x1bolshe 
    mov ax,0 
    mov x1,ax 
  @x1bolshe: 
    cmp y1,0 
    jge @y1bolshe 
    mov ax,0 
    mov y1,ax 
  @y1bolshe: {End range adjustments} 
    mov ax,x2 
    sub ax,x1 
    mov delx,ax 
    mov ax,y2 
    sub ax,y1 
    mov dely,ax 
    cmp ax,delx 
    mov ax,0 
    mov xchngd,ax 
    jb @okey 
    mov ax,1 
    mov xchngd,ax 
    mov bx,delx 
    mov ax,dely 
    mov delx,ax 
    mov dely,bx 
    mov ax,x1 
    mov bx,y1 
    mov x1,bx 
    mov y1,ax 
    mov ax,x2 
    mov bx,y2 
    mov x2,bx 
    mov y2,ax 
  @okey: 
    mov ax,2 
    mov bx,dely 
    mul bx 
    mov del1,ax 
    sub ax,delx 
    mov del,ax 
    mov ax,dely 
    sub ax,delx 
    mov bx,2 
    mul bx 
    mov del2,ax {let's draw it!} 
  end; 
  if (yxch=0) then
  begin 
    b:=y1;
    dz:=1;
  end 
  else
  begin 
    b:=y2;
    dz:=-1;
  end; 
  for a:=x1+1 to x2 do
  begin 
    if del>0 then
    begin 
      del := del + del2;
      b := b + dz;
    end
    else 
      del := del + del1; 
    if (xchngd = 0) then
      uncpixel(a,b)
    else
      uncpixel(b,a); 
  end; 
end; 
  
procedure setvideo(mode:integer); 
begin{Palette Initialization} 
  gl_palette[0].gb:=0;    gl_palette[0].rg:=0;{Black} 
  gl_palette[1].gb:=21;   gl_palette[1].rg:=0;{Blue} 
  gl_palette[2].gb:=64;  gl_palette[2].rg:=5;{Green} 
  gl_palette[3].gb:=85;   gl_palette[3].rg:=5;{Cyan} 
  gl_palette[4].gb:=0;   gl_palette[4].rg:=168;{Red} 
  gl_palette[5].gb:=21;   gl_palette[5].rg:=168;{Magenta} 
  gl_palette[6].gb:=0;   gl_palette[6].rg:=130;{Brown} 
  gl_palette[7].gb:=85;   gl_palette[7].rg:=173;{LightGray} 
  gl_palette[8].gb:=12;    gl_palette[8].rg:=99;{DarkGray} 
  gl_palette[9].gb:=31;   gl_palette[9].rg:=0;{LightBlue} 
  gl_palette[10].gb:=224;  gl_palette[10].rg:=7;{LightGreen} 
  gl_palette[11].gb:=255;   gl_palette[11].rg:=7;{LightCyan} 
  gl_palette[12].gb:=0;   gl_palette[12].rg:=248;{LightRed} 
  gl_palette[13].gb:=31;   gl_palette[13].rg:=248;{LightMagenta} 
  gl_palette[14].gb:=224;   gl_palette[14].rg:=255;{Yellow} 
  gl_palette[15].gb:=255;   gl_palette[15].rg:=255;{White} 
  asm {Setting VESA mode} 
    cmp mode,0 
    jne @n111 
    mov bx,$111 
    mov mode,bx 
  @n111: 
    mov ax,4f02h 
    mov bx,mode 
    int $6d 
  end; 
end; 
  
procedure closevideo;assembler; 
asm 
  mov ax,4f02h 
  mov bx,$3 
  int $6d 
end; 
  
procedure gl_setcolor(r,g,b:byte); 
begin 
  r:=r div 8;
  g:=g div 4;
  b:=b div 8; 
  asm {128 64 32 /BLUE/16 8 4 2 1} {/RED/128 64 32 16 8 /GREEN/4 2 1} 
    mov al,b 
    mov ah,g 
    shl ah,5 
    or al,ah 
    mov gl_gbcolors,al 
    mov al,r 
    shl al,3 
    mov ah,g 
    shr ah,3 
    or ah,al 
    mov gl_rgcolors,ah 
  end; 
end; 
  
procedure gl_savecolor(num:byte); 
begin 
  gl_palette[num].gb := gl_gbcolors; 
  gl_palette[num].rg := gl_rgcolors; 
end; 
  
procedure gl_restorecolor(num:byte); 
begin 
  gl_gbcolors := gl_palette[num].gb; 
  gl_rgcolors := gl_palette[num].rg; 
end; 
  
  
  
procedure gl_putchar8(chn:byte;x,y:integer); 
var 
  chr :TChar8; 
  draw, yes, i, j, invi :byte; 
begin 
  chr := gl_font8[chn]; 
  for j:=1 to 8 do
  begin 
    draw:=chr[j]; 
    for i:=0 to 7 do
    begin 
      asm 
        xor ax,ax 
        mov ah,draw 
        mov cl,i 
        shl ah,cl 
        shr ah,7 
        mov yes,ah 
      end; 
      if (yes=1) then
        uncpixel(x+i,y+j); 
    end; 
  end; 
end; 
  
procedure gl_putchar16(chn:byte;x,y:integer); 
var 
  chr :TChar16; 
  draw, yes, i, j, invi :byte; 
begin 
  chr := gl_font16[chn]; 
  for j:=1 to 16 do
  begin 
    draw := chr[j]; 
    for i:=0 to 7 do
    begin 
      asm 
        xor ax,ax 
        mov ah,draw 
        mov cl,i 
        shl ah,cl 
        shr ah,7 
        mov yes,ah 
      end; 
      if (yes=1) then
        uncpixel(x+i,y+j); 
    end; 
  end; 
end; 
  
procedure gl_putchar14(chn:byte;x,y:integer); 
var 
  chr:TChar14; 
  draw,yes,i,j,invi:byte; 
  oldgb,oldrg:byte; 
begin 
  oldgb := gl_gbcolors;
  oldrg := gl_rgcolors; 
  chr := gl_font14[chn]; 
  for j:=1 to 14 do
  begin 
    draw:=chr[j]; 
    for i:=0 to 7 do
    begin 
      asm 
        xor ax,ax 
        mov ah,draw 
        mov cl,i 
        shl ah,cl 
        shr ah,7 
        mov yes,ah 
      end; 
      if (yes=1) then
      begin
        gl_gbcolors := oldgb;
        gl_rgcolors := oldrg;
      end
      else 
      begin
        gl_gbcolors := 0;
        gl_rgcolors := 0
      end; 
      uncpixel(x+i,y+j); 
      gl_gbcolors := oldgb;
      gl_rgcolors := oldrg; 
    end; 
  end; 
end; 
  
  
procedure gl_putchar(chn:byte;x,y:integer); 
begin 
  case current_fontsize of 
    1: gl_putchar8(chn,x,y); 
    2: gl_putchar16(chn,x,y); 
    3: gl_putchar14(chn,x,y); 
  end; 
end; 
  
procedure gl_puttextxy(x,y:integer; txt:string); 
var
  i:integer; 
begin 
  for i := 1 to length(txt) do 
    gl_putchar(ord(txt[i]),x+i*8,y); 
end; 
  
procedure gl_fontinit(size:integer;name:string); 
var 
  ffile8 :font8file; 
  ffile16:font16file; 
  ffile14:font14file; 
begin 
  case size of 
    1: 
    begin 
      assign(ffile8,name); reset(ffile8); read(ffile8,gl_font8); 
      current_fontsize:=f8x8; 
    end; 
    2: 
    begin 
      assign(ffile16,name); reset(ffile16); read(ffile16,gl_font16); 
      current_fontsize:=f8x16; 
    end; 
    3:
    begin 
      assign(ffile14,name); reset(ffile14); read(ffile14,gl_font14); 
      current_fontsize:=f8x14; 
    end; 
  end; 
end; 
  
  
procedure gl_putsprite(spr:gl_Sprite; frame:byte; x,y:integer); 
var 
  iy, rx, ry, dsh :integer; 
  bank, offs :word; 
begin 
  for iy:=0 to spr.ysize-1 do
  begin 
    ry := (y+iy)*2; 
    rx := x*2; 
    dsh := (spr.xsize*2)*iy+frame*spr.size; 
    asm 
      xor bx,bx 
      mov ax,ry 
      mul gl_lenline 
      add ax,rx 
      adc dx,bx 
      mov bank,dx 
      mov offs,ax 
      {Set Bank->} 
      mov dx,bank 
      cmp dx,gbank 
      je @end 
      mov ax,4f05h 
      mov bx,0 
      mov gbank,dx 
      push dx 
      int $6d 
      mov bx,1 
      pop dx 
      int $6d 
    @end: 
    {Move string} 
      push ds 
      lds si,spr.Pstart 
      add si,dsh 
      mov ax,$A000 
      mov es,ax 
      mov di,offs 
      xor cx,cx 
      mov cl,spr.xsize 
      cld 
      rep movsw 
      pop ds 
    end; 
  end; 
end; 
  
function LoadSprite(var sv:gl_Sprite;filename:string):boolean; 
var
  p    :pointer; 
  f0   :gl_SpriteFile; 
  f    :File; 
  i    :integer; 
  x, y :byte; 
  readed, size :word; 
begin 
  assign(f0,filename); 
  reset(f0); 
  read(f0,sv.xsize); 
  read(f0,sv.ysize); 
  read(f0,sv.fnum); 
  assign(f,filename); 
  reset(f,1); 
  sv.size := 2 * sv.xsize * sv.ysize; 
  size := sv.fnum * sv.size; 
  getmem(sv.Pstart,size); 
  blockread(f,sv.Pstart^,3,readed);{Loosing first three(size bytes)} 
  blockread(f,sv.Pstart^,size,readed); 
  close(f);
  close(f0); 
  if (size = readed) and (size<>0) then
    LoadSprite := true
  else 
    LoadSprite:=false 
end; 
  
procedure FreeSprite(var sv:gl_sprite); 
begin 
  freemem(sv.Pstart,sv.size*sv.fnum); 
  sv.ysize := 0;
  sv.xsize := 0;
  sv.size := 0;
  sv.Pstart := nil;
  sv.fnum := 0; 
end; 
  
procedure gl_makesprite(infile,outfile:string; xsize,ysize,frames:byte); 
var       
  inf, outf :file of byte; 
  ix, iy, i, headlen      :LongInt;
  infdatalen, inflen      :longint; 
  xsizel, ysizel, framesl :longint; 
  r, g, b, buff :byte; 
begin 
  inflen:=0; 
  assign(inf,infile); 
  assign(outf,outfile); 
  reset(inf); 
  rewrite(outf); 
  write('Analyzing file:',infile); 
  inflen := FileSize(INF); 
  xsizel := xsize;
  ysizel := ysize;
  framesl := frames; 
  infdatalen := (3*xsizel*ysizel*framesl); 
  headlen := inflen - infdatalen; 
  writeln('File length:',inflen,' bytes','. Header:',headlen,' bytes'); 
  writeln('Data Size:',infdatalen); 
  writeln('Writing sprite ',outfile); 
  reset(inf); 
  for i:=1 to headlen do 
    read(inf,buff); 
  write(outf,xsize);
  write(outf,ysize);
  write(outf,frames); 
  for iy:=1 to ysize do 
    for ix:=1 to (xsize*frames) do
    begin 
      read(inf,r);
      read(inf,g);
      read(inf,b); 
      gl_setcolor(r,g,b); 
      write(outf,gl_gbcolors);
      write(outf,gl_rgcolors); 
    end; 
  writeln('Completed!'); 
  close(inf);
  close(outf); 
end; 
  
function m_init(sv:gl_sprite):byte; {Returns NumOfButtons} 
var 
  Vector : Pointer; 
  Regs   : Registers; 
begin 
  GetIntVec($33, Vector); 
  If ((Vector = nil) or (Word (Vector^) = $CF)) then begin 
    m_init:= 0; 
  end 
  else begin 
    Regs.AX := 0; 
    Regs.BX := 0; 
    Intr ($33, Regs); 
    If (Regs.AX=0) then begin 
      m_init := 0 
    end 
    else begin 
      If (Regs.BX=0) then
        m_init := 1; 
      If (Regs.BX=2) then
        m_init := 2; 
      If (Regs.BX=3) then
        m_init := 3; 
      m_Sprite:=sv; 
    end; 
  end; 
end; 
  
procedure M_GetMove (var GetX, GetY); assembler; 
asm 
  mov ax, 0Bh 
  int 33h 
  les di, GetX 
  mov word ptr es:[di], cx 
  les di, GetY 
  mov word ptr es:[di], dx 
end; 
  
procedure M_State (var Buttons, PosX, PosY); assembler; 
asm 
  mov ax, 3 
  int 33h 
  les di, PosX 
  mov word ptr es:[di], cx 
  les di, PosY 
  mov word ptr es:[di], dx 
  les di, Buttons 
  mov word ptr es:[di], bx 
end; 
  
function M_Pressed (var Buttons, PosX, PosY): Word; assembler; 
asm 
  mov ax, 5 
  les di, Buttons 
  mov bx, word ptr es:[di] 
  int 33h 
  mov word ptr es:[di], ax 
  les di, PosX 
  mov word ptr es:[di], cx 
  les di, PosY 
  mov word ptr es:[di], dx 
  mov ax, bx 
end; 
  
  
procedure M_Show; 
var 
  b,x,y:word; 
begin 
  M_State(b,x,y); 
  gl_putsprite(M_Sprite,1,m_oldx,m_oldy); 
  gl_putsprite(M_Sprite,0,x,y); 
  m_oldx := x;
  m_oldy := y; 
end; 
  
procedure M_GoToXY (X, Y: Word); assembler; 
asm 
  mov ax, 4 
  mov cx, X 
  mov dx, Y 
  int 33h 
end; 
  
procedure M_RangeX(Left,Right : Word); assembler; 
asm 
  mov ax, 7 
  mov cx, Left 
  mov dx, Right 
  int 33h 
end; 
  
procedure M_RangeY (Up, Down: Word); assembler; 
asm 
  mov ax, 8 
  mov cx, Up 
  mov dx, Down 
  int 33h 
end; 
  
end.{1999}