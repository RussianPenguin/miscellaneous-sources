{$N+}
program olump;
  var a,b,c,d,e,f,g,h: LongInt;
  var numb:Real;
  var sqrtn: Real;
begin
  for a := 1 to 9 do
  begin
    for b := 0 to 9 do
    begin
      if(a = b) then continue;
      for c := 0 to 9 do
      begin
        if((b = c) or (a = c)) then continue;
        for d := 0 to 9 do
        begin
          if((c = d) or (a = d) or (d = b)) then continue;
          for e := 0 to 9 do
          begin
            if((d = e) or (a = e) or (b = e) or (c = e)) then continue;
            for f := 0 to 9 do
            begin
              if((e = f) or (a = f) or (b = f) or (c = f) or (d = f)) then continue;
              for g := 0 to 9 do
              begin
                if((f = g) or (a = g) or (b = g) or (c = g) or (d = g) or (e = g)) then continue;
                for h := 0 to 9 do
                begin
                  if((g = h) or (a = h) or (b = h) or (c = h) or (d = h) or (e = h) or (f = h)) then continue;
                  numb := 10000000*a + 1000000*b + 100000*c + 10000*d + 1000*e + 100*f + 10*g + h;
                  sqrtn := sqrt(numb);
                  if(sqrtn = trunc(sqrtn)) then
                  begin
                    WriteLn(numb:8:0,':',sqrtn:4:0);
                    {WriteLn(a,' ',b,' ',c,' ',d,' ',e,' ',f,' ',g,' ',h);}
                  end
                end;
              end;
            end;
          end;
        end;
      end;
    end;
  end;
  Write('Press <Enter>');
  ReadLn;
end.
