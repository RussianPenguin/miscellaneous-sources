
function ljust(s: string; w: integer): string;
begin
   repeat
      s := s + ' ';
   until length(s) >= w;

   ljust := s;
end;

