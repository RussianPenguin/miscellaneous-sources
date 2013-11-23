{$N+}
program bisection;

type
  real_function = function (x :Real) :Real;

function G(x :Real):Real; far;
begin
  G := Sqr(x) - 2.0;
end;

function zero(F :real_function; x, y :Real) :Real;
const
  eps = 1.0E-12;
var
  mid, fx, fy, fm :Real;
begin
  fx := F(x);
  fy := F(y);
  if fx*fy > 0.0 then
    Halt;
  repeat
    if Abs(fy) < eps then
    begin
      zero := x;
      Exit;
    end
    else if Abs(fy) < eps then
    begin
      zero := y;
      Exit;
    end
    else
    begin
      mid := 0.5*(x+y);
      fm := F(mid);
      if fx*fm <= 0 then
      begin
        y := mid;
        fy := fm;
      end
      else
      begin
        x := mid;
        fx := fm;
      end
    end
  until false;
end;

begin
  WriteLn('G(',zero(G,1.0,2.0):10:10,') = 0');
  WriteLn('Press "Enter"');
  ReadLn;
end.