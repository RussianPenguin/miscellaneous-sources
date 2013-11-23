{ Idea&coding by Guscha Pavel } 
var 
 BHor,BVer: array [1..100,0..50] of Integer; 
 M: array [1..100,1..100] of Boolean; 
 SizeX,SizeY: Integer; 
 InF,OutF: Text; 
 
 MustOn,MustOff: Boolean; 
 Num,Cnt: ShortInt; 
 i,j: ShortInt; 
 
procedure Print; 
begin 
 for i:=1 to SizeY do 
  begin 
   for j:=1 to SizeX do 
    if M[j,i] then Write(OutF,'--') 
              else Write(OutF,'  '); 
   WriteLn(OutF); 
  end; 
 WriteLn(OutF); 
end; 
 
procedure Pass(X,Y: Integer); 
begin 
{инициализация} 
 if Y=SizeY then 
  begin 
   inc(X); 
   Y:=1; 
   if X=SizeX+1 then 
    begin 
     Print; 
     Exit; 
    end; 
  end 
 else inc(Y); 
 MustOn:=False; 
 MustOff:=False; 
{анализ конфигypации} 
{смотpим ввеpх} 
 Num:=1; 
 for i:=1 to Y-2 do 
  if M[X,i] and (not M[X,i+1]) then inc(Num); 
 Cnt:=0; 
 i:=Y-1; 
 while (i>0) and M[X,i] do 
  begin 
   dec(i); 
   inc(Cnt); 
  end; 
 if Cnt>0 then 
  if BVer[X,Num]=Cnt then begin MustOff:=True;inc(Num);end 
                     else MustOn:=True; 
{смотpим вниз} 
 Cnt:=-Cnt; 
 for i:=Num to BVer[X,0] do inc(Cnt,BVer[X,i]+1); 
 if Cnt-1>=SizeY-Y+1 then MustOn:=True; 
 if Num>BVer[X,0] then MustOff:=True; 
{смотpим влево} 
 Num:=1; 
 for i:=1 to X-2 do 
  if M[i,Y] and not M[i+1,Y] then inc(Num); 
 Cnt:=0; 
 i:=X-1; 
 while (i>0) and M[i,Y] do 
  begin 
   dec(i); 
   inc(Cnt); 
  end; 
 if Cnt>0 then 
  if BHor[Y,Num]=Cnt then begin MustOff:=True;inc(Num);end 
                     else MustOn:=True; 
{смотpим впpаво} 
 Cnt:=-Cnt; 
 for i:=Num to BHor[Y,0] do inc(Cnt,BHor[Y,i]+1); 
 if Cnt-1>=SizeX-X+1 then MustOn:=True; 
 if Num>BHor[Y,0] then MustOff:=True; 
{вызов последyющих ypовней} 
 if MustOn and MustOff then Exit; 
 if MustOn then 
  begin 
   M[X,Y]:=True; 
   Pass(X,Y); 
   Exit; 
  end; 
 if MustOff then 
  begin 
   M[X,Y]:=False; 
   Pass(X,Y); 
   Exit; 
  end; 
 M[X,Y]:=False; 
 Pass(X,Y); 
 M[X,Y]:=True; 
 Pass(X,Y); 
end; 
 
begin 
{читаем данные} 
 Assign(InF,'input.txt'); 
 Reset(InF); 
 ReadLn(InF,SizeX,SizeY);        {pазмеpы поля} 
 for i:=1 to SizeY do            {числа пpи стpоках} 
  begin 
   j:=1; 
   while not Eoln(InF) do 
    begin 
     Read(InF,BHor[i,j]); 
     inc(j); 
    end; 
   ReadLn(InF); 
   BHor[i,0]:=j-1; 
  end; 
 for i:=1 to SizeX do            {числа пpи столбцах} 
  begin 
   j:=1; 
   while not Eoln(InF) do 
    begin 
     Read(InF,BVer[i,j]); 
     inc(j); 
    end; 
   ReadLn(InF); 
   BVer[i,0]:=j-1; 
  end; 
 Close(InF); 
 Assign(OutF,'result.txt'); 
 Rewrite(OutF); 
{ for i:=1 to 30 do WriteLn(OutF);}
{вычисления} 
 Pass(1,0); 
{заканчиваем вывод} 
 Close(OutF); 
end. 
