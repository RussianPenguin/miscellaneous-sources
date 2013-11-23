             Program
                  Checkers;
             Uses
                  Graph,Crt;
             Type
                  Position = record
                                x,y : integer;
                             end;

                  ChessType = (W,WD,B,BD,N,G);
                  DeskType  = array[-3..12,-3..12] of ChessType;

                 TPlayer = object
                    Start,Finish   : Position;
                    Color          : boolean;{.t. если белые}
                    Fight          : boolean;{.t. если нужно бить}
                    Fool           : boolean;{.t. если проиграл}
                    procedure      Init (_Color : Boolean);
                  end;

                 TDesk = object
                    Desk        : DeskType;
                    sx,sy       : word;
                    procedure   Init;
                    procedure   Draw;
                    procedure   DrawFigure(x,y:Word;f:ChessType);
                    function    MoveFrom  (Player:TPlayer):boolean;
                    function    StepFrom  (Player:TPlayer):boolean;
                    function    FightFrom (Player:TPlayer):boolean;
                    function    NoFight   (Player:TPlayer):boolean;
                    function    NoStep    (Player:TPlayer):boolean;
                    function    KillFrom  (Player:TPlayer):boolean;
                    function    CompMoveFrom  (Player:TPlayer):boolean;
                    function    CompKillFrom  (Player:TPlayer):boolean;
                    function    EscCompFrom   (Player:TPlayer):boolean;
                    function    Analise   (var Player:TPlayer):boolean;
                    procedure   ScanDamk;
                  end;

                  TGame = object
                   Desk         : TDesk;
                   GameOver     : boolean;
                   Player1      : TPlayer;
                   Player2      : TPlayer;
                   procedure    Init;
                   procedure    Run;
                   procedure    Play (var Player : TPlayer);
                   procedure    CompPlay (var Player : TPlayer);
                   procedure    Done;
                  end;

             Const
                  DeskInit : DeskType = ((G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G),
                                         (G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G),
                                         (G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G),
                                         (G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G),
                                         (G,G,G,G,N,W,N,W,N,W,N,W,G,G,G,G),
                                         (G,G,G,G,W,N,W,N,W,N,W,N,G,G,G,G),
                                         (G,G,G,G,N,W,N,W,N,W,N,W,G,G,G,G),
                                         (G,G,G,G,N,N,N,N,N,N,N,N,G,G,G,G),
                                         (G,G,G,G,N,N,N,N,N,N,N,N,G,G,G,G),
                                         (G,G,G,G,B,N,B,N,B,N,B,N,G,G,G,G),
                                         (G,G,G,G,N,B,N,B,N,B,N,B,G,G,G,G),
                                         (G,G,G,G,B,N,B,N,B,N,B,N,G,G,G,G),
                                         (G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G),
                                         (G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G),
                                         (G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G),
                                         (G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G));

             Var    Game : TGame;


          procedure Tdesk.ScanDamk;
          {превращает шашку в дамку если она достигла нужной позиции}
            var
               i : byte;
            begin
               for i := 1 to 8 do
                begin
                 if Desk[1,i] = B then Desk[1,i] := BD;
                 if Desk[8,i] = W then Desk[8,i] := WD;
                end;
            end;


          procedure Beep;
          {пищит}
             begin
                  write(#7);
             end;

          procedure TGame.Init;
          {инициализация графики}
            var
               Gd,Gm : Integer;
            begin
               Gd := Detect;
               InitGraph(Gd,Gm,'');
               if GraphResult<> 0
                  then begin
                        writeln('Ошибка инициализации графики');
                        halt(0);
                       end;
               GameOver := False;
               Desk.Init;
            end;


          procedure TDesk.Init;
          {установка размера игрового поля и всех графических объектов кроме текста}
            begin
                 Desk:=DeskInit;
                 sx := 50;
            end;


          procedure TGame.Done;
          {завершение графического режима}
            begin
               CloseGraph;
            end;


          procedure TGame.Run;
          {выдача сообщений, инициализация игроков и запуск др. модулей}
          var Compflag : Boolean;
            begin
               SetTextStyle(1,0,2);
               SetColor(12);
               OutTextXY(130,50,'Game CHECKS by Alekhin A. gr. AP-11');
               SetColor(9);
               OutTextXY(130,90,'Keyboards keys :');
               SetColor(15);
               OutTextXY(130,110,'Esc           - exit');
               OutTextXY(130,130,'Enter,Space  - choice/move');
               OutTextXY(130,150,'Pointers      - move cursor');
               OutTextXY(130,170,'q,Q          - cancel');
               SetColor(9);
               OutTextXY(130,210,'Enter for the play : ');
               SetColor(15);
               OutTextXY(150,230,'1 - Human - Human');
               OutTextXY(150,250,'2 - Human - Computer');
               SetColor(4);
               OutTextXY(130,280,'Problem :');
               SetColor(15);
               OutTextXY(150,300,'PC beeps');
               SetColor(4);
               OutTextXY(130,330,'Decision :');
               SetColor(15);
               OutTextXY(150,350,'1. Press "q".');
               OutTextXY(150,370,'2. Player must beat.');
               repeat until keypressed;
                 case readkey of
                 '1' : Compflag := true;
                 '2' : Compflag := false;
                 end;

                 Desk.Draw;
               Player1.Init(True);
               Player2.Init(False);

            repeat
                Desk.DrawFigure(30,30,W);
                if Desk.NoStep(Player1)
                   then
                    begin
                     Player1.Fool:=True;
                     GameOver := True;
                    end;
                if Compflag then Play(Player1)  else CompPlay(Player1);
                Desk.DrawFigure(30,30,B);
                if Desk.NoStep(Player2)
                   then
                    begin
                     Player2.Fool:=True;
                     GameOver := True;
                    end;
                Play(Player2);
            until GameOver;
                         {блок вывода итогов игры}
               SetWriteMode(CopyPut);
               SetColor(9);
               SetTextStyle(0,0,2);
               if Player1.Fool then OutTextXY(170,1,'Black Player Win !!!');
               if Player2.Fool then OutTextXY(170,1,'White Player Win !!!');

               SetTextStyle(0,0,7);
               SetColor(4);
               OutTextXY(75,155,'GAME OVER');
               SetColor(12);
               OutTextXY(70,150,'GAME OVER');

               repeat until keypressed; readkey;
          end;


          procedure TGame.CompPlay;
          {Основная процедура, осуществляющая общую координацию
          в случае если ходит компьютер}
            var i     : Integer;
                P,Q   : Position;
                D     : DeskType;
                flag  : Boolean;

          begin
              if GameOver then exit;
              flag:=true;
              with Player,Desk,Game,P do
              begin
                 if NoFight(Player) then   {бить нечего}
                              begin
          {                    if NoFight(Player2) then {шашек под боем нет}
                                   begin
                                       for y:=8 downto 1 do
                                       begin
                                          for x:=1 to 8 do
                                          begin
                                          start.x := x;  start.y := y;
                                          if flag then
                                              begin
                                              if  Killfrom(Player) then flag:=false;
                                              end
                                          end
                                       end
                                   end

          {                      else {шашки под боем есть}
                              end
                           else   {будем бить}
                              begin
                                    for y:=8 downto 1 do
                                       begin
                                          for x:=1 to 8 do
                                          begin
                                          start.x := x;  start.y := y;
                                          if flag then
                                              begin
                                              if  CompKillfrom(Player) then flag:=false;
                                              end
                                          end
                                       end
                              end;
               {эта секция выполняется если других ходов нет и придется идти под бой}
                       if flag then
                                 begin
                                    for y:=1 to 8 do
                                       begin
                                          for x:=1 to 8 do
                                          begin
                                          start.x := x;  start.y := y;
                                          if flag then
                                              begin
                                              if  CompMoveFrom(Player) then flag:=false;
                                              end
                                          end
                                       end
                                 end;
                 {закончили ход. проверяем на дамки и перерисовываем экран}
                  ScanDamk;  Draw;
              end
          end;

          function   TDesk.EscCompFrom;
          begin
          end;

          function  TDesk.CompMoveFrom;
          {отдает шашку под бой когда нет других ходов и возвращает .t. когда походит}
          var
             f       : boolean;
          begin
             f:=false;
             with Player,Start do
             begin
                 case Desk[y][x] of
                 W  : begin
                         if (Desk[y+1][x+1] = N) and (not f) then
                         begin
                           Desk[y][x]:=N;  Desk[y+1][x+1]:=W;
                           f:=true;
                         end;

                         if (Desk[y+1][x-1] = N) and (not f) then
                         begin
                           Desk[y][x]:=N;  Desk[y+1][x-1]:=W;
                           f:=true;
                         end;
                      end;
                 end;
             end;
             CompMoveFrom:=f;
          end;

          function TDesk.CompKillFrom;
          {убивает одну или несколько шашек противника, а так же возвращает .t. когда
           ход закончен}
          var
             f,f1     : boolean;
             i       : integer;

          begin
           f:=false;
           with Player,Start do
           begin
               While  FightFrom(Player) do
               begin
               f1:=false;
                 case Desk[y][x] of
                 W  : begin
                         if (Desk[y+2][x+2] = N) and (Desk[y+1][x+1] in [B,BD])
                         and (not f1)  then
                         begin
                           Desk[y][x]:=N;  Desk[y+2][x+2]:=W;  Desk[y+1][x+1]:=N;
                           x:=x+2;  y:=y+2;  draw; f1:=true; delay(200);
                           start.x := x;  start.y := y;
                         end;

                         if (Desk[y+2][x-2] = N) and (Desk[y+1][x-1] in [B,BD])
                         and (not f1)  then
                         begin
                           Desk[y][x]:=N;  Desk[y+2][x-2]:=W;  Desk[y+1][x-1]:=N;
                           x:=x-2;  y:=y+2;  draw; f1:=true; delay(200);
                           start.x := x;  start.y := y;
                         end;

                         if (Desk[y-2][x-2] = N) and (Desk[y-1][x-1] in [B,BD])
                         and (not f1)  then
                         begin
                           Desk[y][x]:=N;  Desk[y-2][x-2]:=W;  Desk[y-1][x-1]:=N;
                           x:=x-2;  y:=y-2;  draw; f1:=true; delay(200);
                           start.x := x;  start.y := y;
                         end;

                         if (Desk[y-2][x+2] = N) and (Desk[y-1][x+1] in [B,BD])
                         and (not f1)  then
                         begin
                           Desk[y][x]:=N;  Desk[y-2][x+2]:=W;  Desk[y-1][x+1]:=N;
                           x:=x+2;  y:=y-2;  draw; f1:=true; delay(200);
                           start.x := x;  start.y := y;
                         end;
                      end;

                WD  : begin
                         i:=1;
                         while Desk[y+i][x+i] = N do inc (i);
                         if (Desk[y+i][x+i] in [B,BD]) and (Desk[y+i+1][x+i+1] = N)
                         and not(f1) then
                         begin
                           Desk[y][x]:=N;
                           Desk[y+i][x+i]:=N;  Desk[y+i+1][x+i+1]:=WD;
                           x:=x+i+1;   y:=y+i+1;  draw;  f1:=true;
                           start.x := x;  start.y := y;  delay(200);
                         end;

                         i:=1;
                         while Desk[y-i][x+i] = N do inc (i);
                         if (Desk[y-i][x+i] in [B,BD]) and (Desk[y-i-1][x+i+1] = N)
                         and not(f1) then
                         begin
                           Desk[y][x]:=N;
                           Desk[y-i][x+i]:=N;  Desk[y-i-1][x+i+1]:=WD;
                           x:=x+i+1;   y:=y-i-1;  draw;  f1:=true;
                           start.x := x;  start.y := y;  delay(200);
                         end;

                         i:=1;
                         while Desk[y-i][x-i] = N do inc (i);
                         if (Desk[y-i][x-i] in [B,BD]) and (Desk[y-i-1][x-i-1] = N)
                         and not(f1) then
                         begin
                           Desk[y][x]:=N;
                           Desk[y-i][x-i]:=N;  Desk[y-i-1][x-i-1]:=WD;
                           x:=x-i-1;   y:=y-i-1;  draw;  f1:=true;
                           start.x := x;  start.y := y;  delay(200);
                         end;

                         i:=1;
                         while Desk[y+i][x-i] = N do inc (i);
                         if (Desk[y+i][x-i] in [B,BD]) and (Desk[y+i+1][x-i-1] = N)
                         and not(f1) then
                         begin
                           Desk[y][x]:=N;
                           Desk[y+i][x-i]:=N;  Desk[y+i+1][x-i-1]:=WD;
                           x:=x-i-1;   y:=y+i+1;  draw;  f1:=true;
                           start.x := x;  start.y := y;  delay(200);
                         end;
                      end

                  end;  {case}
                  f:=f or f1;
               end  {while}
           end;  {with}
           CompKillFrom:=f;
          end;

          function TDesk.KillFrom;
          {возвращает .t. если из данной позиции можно походить и не попасть под бой,
           а так же ходит если эти условия выполнены}
          var
             f : boolean;
          begin
               with Player, Start do
                if Color
                   then
                    case Desk[y][x] of
                    W   :if (Desk[y+1][x-1] = N) and
                            (Desk[y+2][x-2] <> B) and (Desk[y+2][x-2] <> BD) and
                            (Desk[y+2][x] <> B) and (Desk[y+2][x] <> BD) and
                            (Desk[y][x-2] <> B) and (Desk[y][x-2] <> BD)
                           then
                           begin
                             f:=true;  Desk[y][x] := N;   Desk[y+1][x-1] := W;
                           end
                         else
                         if (Desk[y+1][x+1] = N) and
                            (Desk[y+2][x+2] <> B) and (Desk[y+2][x+2] <> BD) and
                            (Desk[y+2][x] <> B) and (Desk[y+2][x] <> BD) and
                            (Desk[y][x+2] <> B) and (Desk[y][x+2] <> BD)
                              then
                           begin
                             f:=true;  Desk[y][x] := N;   Desk[y+1][x+1] := W;
                           end;
          { Здесь может быть аналогичная секция для просчета ходов WD }
                     else f := False
                    end;
               KillFrom := f;
          end;


          procedure TGame.Play;
          {основная процедура игры. Осуществляет координацию модулей и движение курсора
          выполняется когда ход принадлежит человеку}
          procedure Select (p:position);{рисует курсор по передаваемым координатам}
          var
             dx,dy : word;
          begin
               SetWriteMode(XorPut);
               SetLineStyle(0,0,3); {стиль линии курсора}
               SetColor(15);

               with p, Desk do
                begin
                 x:=x-1;y:=y-1;
                 dx := GetMaxX div 2 - 4 * sx;
                 dy := GetMaxY div 2 - 4 * sy;
                 Graph.MoveTo(x*sx+dx,y*sy+dy);
                 LineTo((x+1)*sx+dx,y*sy+dy);
                 LineTo((x+1)*sx+dx,(y+1)*sy+dy);
                 LineTo(x*sx+dx,(y+1)*sy+dy);
                 LineTo(x*sx+dx,y*sy+dy);
                end;
          end;

          const
               SelectStart  = 1;
               SelectNext   = 2;

          var
               State : byte;
               P,Q   : Position;
               D     : DeskType;
               F     : Boolean;

          begin
                  if GameOver then exit;

                  with Player, Desk, P do
                   begin
                    P:=Start;
                    D := Desk;
                    F := Fight;
                    Q := P;
                    State := SelectStart;
                    Select(P);  {нарисовали курсор}

                    repeat

                    if keypressed
                       then
                        case readkey of
                         #0  : begin {обработка стрелок - перемещение курсора}
                                Select(P); {стерли курсор}
                                case readkey of
                                 'K' : x:=x-1;
                                 'M' : x:=x+1;
                                 'H' : y:=y-1;
                                 'P' : y:=y+1;
                                end;
                                if x<1 then x:=1;
                                if y<1 then y:=1;
                                if x>8 then x:=8;
                                if y>8 then y:=8;
                                Select(P); {нарисовали новый}
                               end;
                      ' ', #13 : case State of
                                SelectStart : begin
                                               Start := P;
                                               if MoveFrom (Player)
                                                 then
                                                  begin
                                                   Fight:=False;
                                                   State:=SelectNext;
                                                   Q:=P
                                                  end
                                               else Beep;
                                              end;
                                SelectNext : begin
                                              Finish := P;
                                              if Analise (Player)
                                                 then
                                                  if Fight
                                                     then
                                                      begin
                                                       Start := Finish;
                                                       if FightFrom(Player)
                                                          then Select(P)
                                                          else break
                                                      end
                                                     else break
                                                 else beep;
                                             end;
                               end;
                        'Q','q' : begin
                                State := SelectStart;
                                Fight := F;
                                Desk := D;
                                P := Q;
                                Draw;
                                Select(P);
                               end;
                           #27  : begin
                                   GameOver := True;
                                   break;
                                  end;
                        end;
                    until False;
                    Fight := False;
                    ScanDamk;
                   end;
          end;

          function TDesk.Analise;
          {возвращает .f. если введенный ход не соответствует правилам игры
           использует нач. и кон. коорд. положения курсора, а так же
           расположение шашек на доске}
          var
             f,f_                  : boolean;
             dx,dy,ix,iy,x,y,cw,cb : Integer;
          begin
             with Player do
              if Color
                 then
                  begin
                   case Desk[Start.y][Start.x] of
                    W   : begin
                           if Fight then f := False else
                           f := (Finish.y-Start.y=1) and
                                 (abs(Finish.x-Start.x)=1) and
                                 (Desk[Finish.y][Finish.x] = N);
                           x := (Start.x+Finish.x) div 2;
                           y := (Start.y+Finish.y) div 2;
                           Fight := (abs(Finish.y-Start.y)=2) and
                                    (abs(Finish.x-Start.x)=2) and
                                    (Desk[Finish.y][Finish.x]=N) and
                                    (Desk[y][x] in [B,BD]);
                          end;
                    WD  : begin
                           if Finish.x>Start.x then dx := 1
                                               else dx := -1;
                           if Finish.y>Start.y then dy := 1
                                               else dy := -1;
                           ix:=Start.x+dx;
                           iy:=Start.y+dy;
                           f_ := (abs(Finish.x-Start.x) = abs(Finish.y-Start.y)) and
                                 (Desk[Finish.y][Finish.x]=N);
                           cw:=0;
                           cb:=0;
                           if f_ then repeat
                             if Desk[iy][ix] in [W,WD] then inc(cw);
                             if Desk[iy][ix] in [B,BD]
                                then
                                 begin
                                  inc(cb);
                                  x:=ix;
                                  y:=iy;
                                 end;
                             if (ix=Finish.x) or (iy=Finish.y) then break;
                             ix :=ix + dx;
                             iy :=iy + dy;
                           until (ix=Finish.x) or (iy=Finish.y);
                           if Fight then f := false
                                    else f := (cb=0) and (cw=0) and f_;
                           Fight := (cb=1) and (cw=0) and f_;
                          end
                    else f := False
                   end;
                   if f or Fight
                      then begin
                            Desk[Finish.y][Finish.x]:=Desk[Start.y][Start.x];
                            Desk[Start.y][Start.x] := N;
                            if (Finish.y = 8)
                               then Desk[Finish.y][Finish.x]:=WD;
                            if Fight then Desk[y][x]:=N;
                            Draw;
                           end
                  end
                 else
                  begin
                   case Desk[Start.y][Start.x] of
                    B   : begin
                           if Fight then f := False else
                           f := (Start.y-Finish.y=1) and
                               (abs(Finish.x-Start.x)=1) and
                               (Desk[Finish.y][Finish.x] = N);
                           x := (Start.x+Finish.x) div 2;
                           y := (Start.y+Finish.y) div 2;
                           Fight := (abs(Finish.y-Start.y)=2) and
                                    (abs(Finish.x-Start.x)=2) and
                                    (Desk[Finish.y][Finish.x]=N) and
                                    (Desk[y][x] in [W,WD]);
                          end;
                    BD  : begin
                           if Finish.x>Start.x then dx := 1
                                               else dx := -1;
                           if Finish.y>Start.y then dy := 1
                                               else dy := -1;
                           ix:=Start.x+dx;
                           iy:=Start.y+dy;
                           f_ := (abs(Finish.x-Start.x) = abs(Finish.y-Start.y)) and
                                 (Desk[Finish.y][Finish.x]=N);
                           cw:=0;
                           cb:=0;
                           if f_ then repeat
                             if Desk[iy][ix] in [B,BD] then inc(cb);
                             if Desk[iy][ix] in [W,WD]
                                then
                                 begin
                                  inc(cw);
                                  x:=ix;
                                  y:=iy;
                                 end;
                             if (ix=Finish.x) or (iy=Finish.y) then break;
                             ix :=ix + dx;
                             iy :=iy + dy;
                           until (ix=Finish.x) or (iy=Finish.y);
                           if Fight then f := false
                                    else f:= (cb=0) and (cw=0) and f_;
                           Fight := (cw=1) and (cb=0) and f_;
                          end
                    else f := False
                   end;
                   if f or Fight
                      then begin
                            Desk[Finish.y][Finish.x]:=Desk[Start.y][Start.x];
                            Desk[Start.y][Start.x] := N;
                            if (Finish.y = 1)
                               then Desk[Finish.y][Finish.x]:=BD;
                            if Fight then Desk[y][x]:=N;
                            Draw;
                           end;
                  end;
                Analise := f or Player.Fight;
          end;


          function TDesk.MoveFrom;{проверяет возможность хода из данной клетки}
          begin
               if NoFight(Player) then MoveFrom := StepFrom(Player)
                                  else MoveFrom := FightFrom(Player)
          end;


          function TDesk.NoFight;
          {возвращает .t. если бить нечего}
          var
             f    : boolean;
          begin
               f := False;
               with Player.Start do
                for y:=1 to 8 do
                 for x:=1 to 8 do
                  f := f or FightFrom(Player);
               NoFight := not f;
          end;

          function TDesk.FightFrom;
          {возвращает .t. если в текущей позиции есть фишка и она должна что - то бить}
          var
             f       : boolean;
             i       : integer;
          begin
               with Player, Start do
                if Color
                   then
                    case Desk[y][x] of
                     W   : f := ((Desk[y+2][x+2] = N) and (Desk[y+1][x+1] in [B,BD])) or
                                ((Desk[y+2][x-2] = N) and (Desk[y+1][x-1] in [B,BD])) or
                                ((Desk[y-2][x-2] = N) and (Desk[y-1][x-1] in [B,BD])) or
                                ((Desk[y-2][x+2] = N) and (Desk[y-1][x+1] in [B,BD]));
                     WD  : begin
                            i:=1;
                            while Desk[y+i][x+i] = N do inc (i);
          {ищем ближайшую шашку в этом направлении}
                            f:=(Desk[y+i][x+i] in [B,BD]) and (Desk[y+i+1][x+i+1] = N);
          {если эта шашка черных и за ней нет ничего - надо бить (f=.t.)}
                            i:=1;
                            while Desk[y-i][x+i] = N do inc (i);
                            f:=f or (Desk[y-i][x+i] in [B,BD]) and (Desk[y-i-1][x+i+1] = N);

                            i:=1;
                            while Desk[y-i][x-i] = N do inc(i);
                            f:=f or (Desk[y-i][x-i] in [B,BD]) and (Desk[y-i-1][x-i-1] = N);

                            i:=1;
                            while Desk[y+i][x-i] = N do inc(i);
                            f:=f or (Desk[y+i][x-i] in [B,BD]) and (Desk[y+i+1][x-i-1] = N);
                           end;
                     else f:= False;
                    end
                  else
                   case Desk[y][x] of
                     B   : f := ((Desk[y+2][x+2] = N) and (Desk[y+1][x+1] in [W,WD])) or
                                ((Desk[y+2][x-2] = N) and (Desk[y+1][x-1] in [W,WD])) or
                                ((Desk[y-2][x-2] = N) and (Desk[y-1][x-1] in [W,WD])) or
                                ((Desk[y-2][x+2] = N) and (Desk[y-1][x+1] in [W,WD]));
                     BD  : begin
                            i:=1;
                            while Desk[y+i][x+i] = N do inc (i);
                            f:=(Desk[y+i][x+i] in [W,WD]) and (Desk[y+i+1][x+i+1] = N);

                            i:=1;
                            while Desk[y-i][x+i] = N do inc (i);
                            f:=f or (Desk[y-i][x+i] in [W,WD]) and (Desk[y-i-1][x+i+1] = N);

                            i:=1;
                            while Desk[y-i][x-i] = N do inc(i);
                            f:=f or (Desk[y-i][x-i] in [W,WD]) and (Desk[y-i-1][x-i-1] = N);

                            i:=1;
                            while Desk[y+i][x-i] = N do inc(i);
                            f:=f or (Desk[y+i][x-i] in [W,WD]) and (Desk[y+i+1][x-i-1] = N);
                           end
                     else f := False
                    end;
               FightFrom := f;
          end;


          function TDesk.NoStep;
          {возвращает .T. если у игрока (Color=.t. - W; Color=.f. - B) нет ходов}
          var
             p    : Position;
             f    : boolean;
          begin
               p := Player.Start;
               f := False;
               with Player.Start do
                for y:=1 to 8 do
                 for x:=1 to 8 do
                  f := f or StepFrom(Player);
               Player.Start := p;
               NoStep := not f;
          end;


          function TDesk.StepFrom;
          {возвращает .t. если в текущей клетке есть шашка и ею можно походить}
          var
             f : boolean;
          begin
               with Player, Start do
                if Color
                   then
                    case Desk[y][x] of
                     W   : f := (Desk[y+1][x+1] = N) or (Desk[y+1][x-1] = N);
                     WD  : f := (Desk[y+1][x+1] = N) or (Desk[y+1][x-1] = N) or
                                (Desk[y-1][x+1] = N) or (Desk[y-1][x-1] = N)
                     else f := False
                    end
                   else
                    case Desk[y][x] of
                     B   : f := (Desk[y-1][x+1] = N) or (Desk[y-1][x-1] = N);
                     BD  : f := (Desk[y+1][x+1] = N) or (Desk[y+1][x-1] = N) or
                                (Desk[y-1][x+1] = N) or (Desk[y-1][x-1] = N)
                     else f := False
                    end;
               StepFrom := f;
          end;


          procedure TPlayer.Init;{инициализация игроков}
          begin
               Fool := False;
               Fight:=False;
               Color:=_Color; {передается как параметр (T/F)}
               if Color
                  then
                   begin
                    Start.x:=4;  {нач установка курсора}
                    Start.y:=3;
                   end
                  else
                   begin
                    Start.x:=5;
                    Start.y:=6;
                   end
          end;


          procedure TDesk.Draw;{рисует доску и фигуры по данным массива фигур}
          var
             i,j   : byte;
             f     : boolean;
             ax,ay : word;
             dx,dy : word;
          begin
             f:=True;
             GetAspectRatio(ax,ay);
             SetWriteMode(CopyPut);
             SetLineStyle(0,0,1);
             sy := round(sx/ay*ax);
             dx := GetMaxX div 2 - 4 * sx;
             dy := GetMaxY div 2 - 4 * sy;
             SetWriteMode(CopyPut);
             for j:=0 to 7 do
              begin
               for i:=0 to 7 do
                begin
                 if f then SetFillStyle(1,14)
                      else SetFillStyle(1,6);
                 bar(i*sx+dx,j*sy+dy,(i+1)*sx+dx,(j+1)*sy+dy);
                 DrawFigure(i*sx+dx+sx div 2,j*sy+dy+sy div 2,Desk[j+1][i+1]);
                 f:= not f;
                end;
               f := not f;
              end;
          end;

          procedure TDesk.DrawFigure;
          {рисует шашаку используя передаваемые координаты и параметры -
           - цвет, дамка/не дамка}
          var
             rx,ry : word;
          begin
             rx := 2 * sx div 5;
             ry := 2 * sy div 5;

             SetWriteMode(CopyPut);
             SetLineStyle(0,0,1);

             case f of
              W,WD   : begin
                       SetFillStyle(1,15);
                       SetColor(15);
                       end;
              B,BD   : begin
                       SetFillStyle(1,0);
                       SetColor(0);
                       end;
             end;

             case f of
              W,B   : begin
                       FillEllipse(x,y,rx,ry);
                       SetColor(7);
                       Arc(x,y,45,225,rx+1);
                       Arc(x,y,45,225,2 * rx div 3 + 1);
                       Arc(x,y,45,225,rx div 3 + 1);
                       Arc(x,y,225,45,rx-1);
                       Arc(x,y,225,45,2 * rx div 3 - 1);
                       Arc(x,y,225,45,rx div 3 - 1);
                       SetColor(8);
                       Arc(x,y,45,225,rx-1);
                       Arc(x,y,45,225,2 * rx div 3 - 1);
                       Arc(x,y,45,225,rx div 3 - 1);
                       Arc(x,y,225,45,rx+1);
                       Arc(x,y,225,45,2 * rx div 3 + 1);
                       Arc(x,y,225,45,rx div 3 + 1);
                      end;
              WD,BD : begin
                       FillEllipse(x,y,rx,ry);
                       SetColor(7);
                       Arc(x,y,45,225,rx+1);
                       Arc(x,y,225,45,rx-2);
                       SetColor(8);
                       Arc(x,y,45,225,rx-2);
                       Arc(x,y,225,45,rx+1);
                      end;
             end;

          end;


          BEGIN
                 Game.Init;
                 Game.Run;
                 Game.Done;
          END .
