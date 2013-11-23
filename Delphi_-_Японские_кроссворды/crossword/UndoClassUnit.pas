unit UndoClassUnit;

interface
uses Classes, CrossTypesUnit;
type
  TUndoRecord = record
    X,Y:integer;
    OldaState:TCrossItemState;
    NewState:TCrossItemState;
  end;
  PUndoArray = ^TUndoArray;
  TUndoArray = array [0..100] of TUndoRecord;

type
  TUndoClass = class(TObject)
  private
    fUndoArray:PUndoArray;
    fMaxItems:integer;
    fMaxUserItems:integer;
    fCurItem:integer;
    procedure SetSize(ASize:integer);
  public
    constructor Create;
    destructor Destroy; override;
    procedure Clear;
    procedure Push(X,Y:integer; OldaState, NewState:TCrossItemState);
    function Undo(var X,Y:integer; var OldaState, NewState:TCrossItemState):boolean;
    function Redo(var X,Y:integer; var OldaState, NewState:TCrossItemState):boolean;
    function UndoEnabled:boolean;
    function RedoEnabled:boolean;
  end;

implementation
uses Math;

  { TUndoClass }
constructor TUndoClass.Create;
begin
  inherited Create;
  SetSize(20);
  Clear;
end;

destructor TUndoClass.Destroy;
begin
  SetSize(0);
  inherited Destroy;
end;

procedure TUndoClass.Clear;
begin
  fCurItem:=-1;
  fMaxUserItems:=-1;
  if fUndoArray<>nil then
     FillChar(fUndoArray^, SizeOf(TUndoRecord)*fMaxItems, 0);
end;

procedure TUndoClass.Push(X,Y:integer; OldaState, NewState:TCrossItemState);
begin
  inc(fCurItem);
  fMaxUserItems:=fCurItem;
  if fMaxUserItems>=fMaxItems-1 then SetSize(fMaxUserItems+100);
  fUndoArray^[fCurItem].X:=X;
  fUndoArray^[fCurItem].Y:=Y;
  fUndoArray^[fCurItem].OldaState:=OldaState;
  fUndoArray^[fCurItem].NewState:=NewState;
end;

function TUndoClass.Undo(var X,Y:integer; var OldaState, NewState:TCrossItemState):boolean;
begin
  Result:=UndoEnabled;
  if not Result then exit;
  X:=fUndoArray^[fCurItem].X;
  Y:=fUndoArray^[fCurItem].Y;
  OldaState:=fUndoArray^[fCurItem].OldaState;
  NewState:=fUndoArray^[fCurItem].NewState;
  Dec(fCurItem);
end;

function TUndoClass.Redo(var X,Y:integer; var OldaState, NewState:TCrossItemState):boolean;
begin
  Result:=RedoEnabled;
  if not Result then exit;
  inc(fCurItem);
  X:=fUndoArray^[fCurItem].X;
  Y:=fUndoArray^[fCurItem].Y;
  OldaState:=fUndoArray^[fCurItem].OldaState;
  NewState:=fUndoArray^[fCurItem].NewState;
end;

procedure TUndoClass.SetSize(ASize:integer);
var P:PUndoArray;
    i:integer;
begin
  GetMem(P, SizeOf(TUndoRecord)*ASize);
  FillChar(P^, SizeOf(TUndoRecord)*ASize, 0);
  for i:=0 to Min(ASize, fMaxItems)-1 do P^[i]:=fUndoArray^[i];
  FreeMem(fUndoArray, SizeOf(TUndoRecord)*fMaxItems);
  fUndoArray:=P;
  fMaxItems:=ASize;
end;

function TUndoClass.UndoEnabled:boolean;
begin
  Result:=fCurItem>-1;
end;

function TUndoClass.RedoEnabled:boolean;
begin
  Result:=fCurItem<fMaxUserItems;
end;

end.
