unit CrossTypesUnit;

interface
uses Graphics, Classes;

type
  TGameState = (gsGame, gsEditing, gsLoadNew, gsLoadUserGame,
                gsSaveUserGame);
  TCrossItemState = (csUncheked, csCheced, csEmpty, csUnknow,
                     csColor1, csColor2, csColor3,
                     csColor4, csColor5, csColor6,
                     csColor7, csColor8);
  TCrossBoard = array [0..50,0..50] of TCrossItemState;

  TInfoLineItem = record
    Color:TCrossItemState;
    Count:integer;
    Checked:boolean;
  end;

  PInfoLineItems = ^TInfoLineItems;
  TInfoLineItems = array [0..100] of TInfoLineItem;

type
  TILClearState = (csColor, csCount, csChecked);
  TILClearStates = set of TILClearState;
const
  ClearAll : TILClearStates = [csColor, csCount, csChecked];
type
  TInfoLines = class(TObject)
  private
    InfoLineArray:PInfoLineItems;
    X,Y:integer;
    function GetItem(AX,AY:integer):TInfoLineItem;
    procedure SetItem(AX,AY:integer; Item:TInfoLineItem);
    function GetChecked(AX,AY:integer):boolean;
    procedure SetChecked(AX,AY:integer; AChecked:boolean);
    function GetColor(AX,AY:integer):TCrossItemState;
    procedure SetColor(AX,AY:integer; AColor:TCrossItemState);
    function GetCount(AX,AY:integer):integer;
    procedure SetCount(AX,AY:integer; ACount:integer);
    function GetSize:integer;
  public
    constructor Create(AX,AY:integer);
    destructor Destroy; override;
    procedure SetSize(NewX,NewY:integer);
    procedure Store(S:TStream);
    procedure Load(S:TStream);
    procedure Clear(State:TILClearStates);
    property Items[X,Y:integer]:TInfoLineItem read GetItem write SetItem; default;
    property Checked[X,Y:integer]:boolean read GetChecked write SetChecked;
    property Color[X,Y:integer]:TCrossItemState read GetColor write SetColor;
    property Count[X,Y:integer]:integer read GetCount write SetCount;
    property Size:integer read GetSize;
  end;

  TTopLine = array [0..50,0..20] of TInfoLineItem;
  TLeftLine = array [0..20,0..50] of TInfoLineItem;

  TTopLineCheck = array [0..50,0..20] of boolean;
  TLeftLineCheck = array [0..20,0..50] of boolean;
  TCrossPalette = array [TCrossItemState] of TColor;

type
  PMainBoardItems = ^TMainBoardItems;
  TMainBoardItems = array [0..10000] of TCrossItemState;
  TMainBoard = class(TObject)
  private
    fItems:PMainBoardItems;
    X,Y:integer;
    procedure SetItem(AX,AY:integer; AItem:TCrossItemState);
    function GetItem(AX,AY:integer):TCrossItemState;
    function GetSize:integer;
  public
    constructor Create(AX,AY:integer);
    destructor Destroy; override;
    procedure SetSize(NewX,NewY:integer);
    procedure Store(S:TStream);
    procedure Load(S:TStream);
    procedure Assign(Sourse:TMainBoard);
    procedure Clear;
    property Items[X,Y:integer]:TCrossItemState read GetItem write SetItem; default;
    property Size:integer read GetSize;
  end;

const
//эти структуры идут в файле сохранялке
  idBoardSign    = $0000;
  idBoardName    = $0001;
  idBoardAutor   = $0002;
  idFontName     = $0003;
  idFontSize     = $0004;
  idMainBoard    = $0005;
  idSizeBoard    = $0008;
  idColors       = $0009;
  idCellSize     = $000A;
  idGameDesc     = $000B;
{  idInfoLinesW   = $000C;}
  idMIDISound    = $000D;
  idTimeCount    = $000E; //only for cur game save
  idCurBoard     = $000F; //only for cur game save
  idTopLine      = $0010;
  idLeftLine     = $0011;
  idNewMainBoard = $0012;
  idNewCurBoard  = $0013;

type
  TInfoTag = packed record
    ID:integer;
    Size:integer;
  end;

type
  TBoardSize = record
    X,Y:integer;
    Difficult:integer;
    Version:integer;
  end;

type
  TColorRec = record
    BackgroundColor: TColor;
    UnchekedColor: TColor;
    ChekedColor: TColor;
    EmptyColor: TColor;
    NumberColor: TColor;
    SplitColor: TColor;
    UnknowColor: TColor;
    Color1: TColor;
    Color2: TColor;
    Color3: TColor;
    Color4: TColor;
    Color5: TColor;
    Color6: TColor;
    Color7: TColor;
    Color8: TColor;
  end;

const
  ExtArray:array[0..3] of string = ('.cwg','.ccw','.scg','.scc');
const
  ShowEmptyCheck: boolean = true;
  ShowStartupNew: boolean = true;
  PlaySounds    : boolean = true;

function GetTag(S:TStream; ID:integer; var Buf):boolean;
function GetStringTag(S:TStream; ID:integer; var R:string):boolean;

procedure StoreIniFile;
implementation
uses Math, SysUtils, IniFiles;

function GetStringTag(S:TStream; ID:integer; var R:string):boolean;
var fEof:boolean;
    T:TInfoTag;
begin
//  fEof:=false;
  Result:=false;
  repeat
    fEof:=S.Read(T,SizeOf(TInfoTag))<>SizeOf(TInfoTag);
    if (not fEof) then
      if T.ID=ID then
      begin
        SetLength(R,T.Size);
        S.Read(R[1],T.Size);
        Result:=true;
        exit;
      end
      else S.Seek(T.Size,soFromCurrent);
  until fEof;
end;

function GetTag(S:TStream; ID:integer; var Buf):boolean;
var fEof:boolean;
    T:TInfoTag;
begin
//  fEof:=false;
  Result:=false;
  repeat
    fEof:=S.Read(T,SizeOf(TInfoTag))<>SizeOf(TInfoTag);
    if (not fEof) then
      if T.ID=ID then
      begin
        S.Read(Buf,T.Size);
        Result:=true;
        exit;
      end
      else S.Seek(T.Size,soFromCurrent);
  until fEof;
end;
  { TInfoLines }
constructor TInfoLines.Create(AX,AY:integer);
begin
  inherited Create;
  X:=AX;
  Y:=AY;
  GetMem(InfoLineArray, SizeOf(TInfoLineItem)*X*Y);
  FillChar(InfoLineArray^, SizeOf(TInfoLineItem)*X*Y, 0)
end;

destructor TInfoLines.Destroy;
begin
  FreeMem(InfoLineArray, SizeOf(TInfoLineItem)*X*Y);
  inherited Destroy;
end;

procedure TInfoLines.SetSize(NewX,NewY:integer);
var
  A:PInfoLineItems;
  i,j:integer;
begin
  if (NewX<=X) and (NewY<=Y) then exit;
  GetMem(A, SizeOf(TInfoLineItem)*NewX*NewY);
  FillChar(A^, SizeOf(TInfoLineItem)*NewX*NewY, 0);
  for j:=0 to Min(NewY,Y)-1 do
    for i:=0 to Min(NewX,X)-1 do
      A^[i+j*NewX]:=InfoLineArray^[i+j*X];
  FreeMem(InfoLineArray, SizeOf(TInfoLineItem)*X*Y);
  InfoLineArray:=A;
  X:=NewX;
  Y:=NewY;
end;

procedure TInfoLines.Store(S:TStream);
begin
  S.Write(X,SizeOf(Integer));
  S.Write(Y,SizeOf(Integer));
  S.Write(InfoLineArray^, SizeOf(TInfoLineItem)*X*Y);
end;

procedure TInfoLines.Load(S:TStream);
var AX,AY:integer;
begin
  S.Read(AX,SizeOf(Integer));
  S.Read(AY,SizeOf(Integer));
  SetSize(AX,AY);
  S.Read(InfoLineArray^, SizeOf(TInfoLineItem)*X*Y);
end;

function TInfoLines.GetItem(AX,AY:integer):TInfoLineItem;
begin
  if (AX>=X) or (AY>=Y) then raise Exception.Create('Выход за границы диапазона')
  else
  Result:=InfoLineArray^[AX+AY*X];
end;

procedure TInfoLines.SetItem(AX,AY:integer; Item:TInfoLineItem);
begin
  if (AX>=X) or (AY>=Y) then raise Exception.Create('Выход за границы диапазона')
  else
  InfoLineArray^[AX+AY*X]:=Item;
end;

procedure TInfoLines.SetChecked(AX,AY:integer; AChecked:boolean);
begin
  if (AX>=X) or (AY>=Y) then raise Exception.Create('Выход за границы диапазона')
  else
  InfoLineArray^[AX+AY*X].Checked:=AChecked;
end;

function TInfoLines.GetChecked(AX,AY:integer):boolean;
begin
  if (AX>=X) or (AY>=Y) then raise Exception.Create('Выход за границы диапазона')
  else
  Result:=InfoLineArray^[AX+AY*X].Checked;
end;

function TInfoLines.GetColor(AX,AY:integer):TCrossItemState;
begin
  if (AX>=X) or (AY>=Y) then raise Exception.Create('Выход за границы диапазона')
  else
  Result:=InfoLineArray^[AX+AY*X].Color;
end;

procedure TInfoLines.SetColor(AX,AY:integer; AColor:TCrossItemState);
begin
  if (AX>=X) or (AY>=Y) then raise Exception.Create('Выход за границы диапазона')
  else
  InfoLineArray^[AX+AY*X].Color:=AColor;
end;

function TInfoLines.GetCount(AX,AY:integer):integer;
begin
  if (AX>=X) or (AY>=Y) then raise Exception.Create('Выход за границы диапазона')
  else
  Result:=InfoLineArray^[AX+AY*X].Count;
end;

procedure TInfoLines.SetCount(AX,AY:integer; ACount:integer);
begin
  if (AX>=X) or (AY>=Y) then raise Exception.Create('Выход за границы диапазона')
  else
  InfoLineArray^[AX+AY*X].Count:=ACount;
end;

procedure TInfoLines.Clear(State:TILClearStates);
var i:integer;
begin
  for i:=0 to X*Y-1 do
  with InfoLineArray^[i] do
  begin
    if csColor in State then Color:=csUncheked;
    if csCount in State then Count:=0;
    if csChecked in State then Checked:=false;
  end;
//  FillChar(InfoLineArray^, SizeOf(TInfoLineItem)*X*Y, 0)
end;

function TInfoLines.GetSize:integer;
begin
  Result:=SizeOf(integer)*2+SizeOf(TInfoLineItem)*X*Y;
end;

{TMainBoard}
constructor TMainBoard.Create(AX,AY:integer);
begin
  inherited Create;
  X:=AX;
  Y:=AY;
  GetMem(fItems, SizeOf(TCrossItemState)*X*Y);
  FillChar(fItems^, SizeOf(TCrossItemState)*X*Y, 0)
end;

destructor TMainBoard.Destroy;
begin
  FreeMem(fItems, SizeOf(TCrossItemState)*X*Y);
  inherited Destroy;
end;

procedure TMainBoard.SetSize(NewX,NewY:integer);
var A:PMainBoardItems;
    i,J:integer;
begin
  if (NewX=X) and (NewY=Y) then exit;
  GetMem(A, SizeOf(TCrossItemState)*NewX*NewY);
  FillChar(A^, SizeOf(TCrossItemState)*NewX*NewY, 0);
  for j:=0 to Min(NewY,Y)-1 do
    for i:=0 to Min(NewX,X)-1 do
      A^[i+j*NewX]:=fItems^[i+j*X];
  FreeMem(fItems, SizeOf(TCrossItemState)*X*Y);
  fItems:=A;
  X:=NewX;
  Y:=NewY;
end;

procedure TMainBoard.Store(S:TStream);
begin
  S.Write(X,SizeOf(Integer));
  S.Write(Y,SizeOf(Integer));
  S.Write(fItems^, SizeOf(TCrossItemState)*X*Y);
end;

procedure TMainBoard.Load(S:TStream);
var AX,AY:integer;
begin
  S.Read(AX,SizeOf(Integer));
  S.Read(AY,SizeOf(Integer));
  SetSize(AX,AY);
  S.Read(fItems^, SizeOf(TCrossItemState)*X*Y);
end;

procedure TMainBoard.Clear;
begin
  FillChar(fItems^, SizeOf(TCrossItemState)*X*Y, 0)
end;

procedure TMainBoard.SetItem(AX,AY:integer; AItem:TCrossItemState);
begin
  if (AX>=X) or (AY>=Y) then raise Exception.Create('Выход за границы диапазона')
  else fItems^[AX+AY*X]:=AItem;
end;

function TMainBoard.GetItem(AX,AY:integer):TCrossItemState;
begin
  if (AX>=X) or (AY>=Y) then raise Exception.Create('Выход за границы диапазона')
  else Result:=fItems^[AX+AY*X];
end;

function TMainBoard.GetSize:integer;
begin
  Result:=SizeOf(integer)*2+SizeOf(TCrossItemState)*X*Y;
end;

procedure TMainBoard.Assign(Sourse:TMainBoard);
begin
  SetSize(Sourse.X, Sourse.Y);
  Move(Sourse.fItems^, fItems^, SizeOf(TCrossItemState)*X*Y);
end;

function ApplicationIniFile:TIniFile;
begin
  Result:=TIniFile.Create(ChangeFileExt(ExtractFileName(ParamStr(0)),'.ini'));
end;

procedure StoreIniFile;
var I:TIniFile;
begin
  I:=ApplicationIniFile;
  I.WriteBool('SYSTEM','ShowEmptyCheck',ShowEmptyCheck);
  I.WriteBool('SYSTEM','PlaySounds',PlaySounds);
  I.WriteBool('SYSTEM','ShowStartupNew',ShowStartupNew);
  I.Free;
end;

procedure LoadIniFile;
var I:TIniFile;
begin
  I:=ApplicationIniFile;
  ShowEmptyCheck:=I.ReadBool('SYSTEM','ShowEmptyCheck',ShowEmptyCheck);
  PlaySounds:=I.ReadBool('SYSTEM','PlaySounds',PlaySounds);
  ShowStartupNew:=I.ReadBool('SYSTEM','ShowStartupNew',ShowStartupNew);
  I.Free;
end;

initialization
  LoadIniFile;
end.
