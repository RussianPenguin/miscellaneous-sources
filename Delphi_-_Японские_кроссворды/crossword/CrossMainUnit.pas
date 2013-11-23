unit CrossMainUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Menus, ExtCtrls, SpeedBar, Grids, StdCtrls, Printers, ImgList,
  CrossTypesUnit, ComCtrls, RxCombos, Spin, Placemnt, MPlayer, UndoClassUnit;

type
  TCrossMainForm = class(TForm)
    ToolBar: TSpeedBar;
    MainMenu: TMainMenu;
    N1: TMenuItem;
    EditItem: TMenuItem;
    N3: TMenuItem;
    ExitItem: TMenuItem;
    N5: TMenuItem;
    SaveItem: TMenuItem;
    LoadItem: TMenuItem;
    OpenCurGameDialog: TOpenDialog;
    SaveCurGameDialog: TSaveDialog;
    GamePropItems: TMenuItem;
    PrintItem: TMenuItem;
    ImageList1: TImageList;
    SpeedbarSection1: TSpeedbarSection;
    CloseGameBtn: TSpeedItem;
    NewGameBtn: TSpeedItem;
    SpeedbarSection2: TSpeedbarSection;
    SpeedItem3: TSpeedItem;
    NewGame: TMenuItem;
    GamePropBtn: TSpeedItem;
    SpeedbarSection3: TSpeedbarSection;
    OpenGameBtn: TSpeedItem;
    SaveGameBtn: TSpeedItem;
    StatusBar1: TStatusBar;
    N2: TMenuItem;
    TollBarItem: TMenuItem;
    PopupMenu1: TPopupMenu;
    FlatBtnLocalItem: TMenuItem;
    ToolBarLocalItem: TMenuItem;
    FlatBtnItem: TMenuItem;
    FtpSend: TSpeedItem;
    FormStorage1: TFormStorage;
    HelpItems: TMenuItem;
    AboutItem: TMenuItem;
    InverItem: TMenuItem;
    CrossRulesItem: TMenuItem;
    N6: TMenuItem;
    N10: TMenuItem;
    N11: TMenuItem;
    N4: TMenuItem;
    BackToGame: TMenuItem;
    N12: TMenuItem;
    SaveCurGameItem: TMenuItem;
    OpenCurGameItem: TMenuItem;
    N13: TMenuItem;
    EksportItems: TMenuItem;
    N15: TMenuItem;
    N16: TMenuItem;
    N18: TMenuItem;
    OpenDialog1: TOpenDialog;
    SaveDialog1: TSaveDialog;
    SaveCurGBtn: TSpeedItem;
    LoadCurGBtn: TSpeedItem;
    Timer1: TTimer;
    MIDISound: TMenuItem;
    N14: TMenuItem;
    N20: TMenuItem;
    DrawGrid1: TDrawGrid;
    MediaPlayer1: TMediaPlayer;
    SpeedbarSection4: TSpeedbarSection;
    ColorBtn1: TSpeedItem;
    ColorBtn2: TSpeedItem;
    ColorBtn3: TSpeedItem;
    ColorBtn4: TSpeedItem;
    ColorBtn5: TSpeedItem;
    ColorBtn6: TSpeedItem;
    N21: TMenuItem;
    SimpleCross: TMenuItem;
    ColoredCross: TMenuItem;
    OpenColorGame: TOpenDialog;
    SaveColorGame: TSaveDialog;
    ColorOffBtn: TSpeedItem;
    OpenUserColor: TOpenDialog;
    SaveUserColor: TSaveDialog;
    N22: TMenuItem;
    FtpSendItem: TMenuItem;
    N8: TMenuItem;
    CustomToolBarLocalItem: TMenuItem;
    N7: TMenuItem;
    CustomToolBarItem: TMenuItem;
    ColorBtn7: TSpeedItem;
    ColorBtn8: TSpeedItem;
    N17: TMenuItem;
    FtpGetItem: TMenuItem;
    SpeedbarSection5: TSpeedbarSection;
    SpeedItem1: TSpeedItem;
    SpeedItem2: TSpeedItem;
    UndoBtn: TSpeedItem;
    RedoBtn: TSpeedItem;
    N19: TMenuItem;
    UndoItem: TMenuItem;
    RedoItem: TMenuItem;
    CrossColorRulesItem: TMenuItem;
    Help1: TMenuItem;
    procedure DrawGrid1DrawCell(Sender: TObject; ACol, ARow: Integer;
      Rect: TRect; State: TGridDrawState);
    procedure DrawGrid1MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure FormCreate(Sender: TObject);
    procedure DrawGrid1MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure EditItemClick(Sender: TObject);
    procedure LoadItemClick(Sender: TObject);
    procedure SaveItemClick(Sender: TObject);
    procedure GamePropItemsClick(Sender: TObject);
    procedure PrintItemClick(Sender: TObject);
    procedure ExitItemClick(Sender: TObject);
    procedure NewGameClick(Sender: TObject);
    procedure TollBarItemClick(Sender: TObject);
    procedure FlatBtnItemClick(Sender: TObject);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure AboutItemClick(Sender: TObject);
    procedure CrossRulesItemClick(Sender: TObject);
    procedure InverItemClick(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure MIDISoundClick(Sender: TObject);
    procedure SaveCurGameItemClick(Sender: TObject);
    procedure OpenCurGameItemClick(Sender: TObject);
    procedure N18Click(Sender: TObject);
    procedure SimpleCrossClick(Sender: TObject);
    procedure ColoredCrossClick(Sender: TObject);
    procedure ColorBtnClick(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure N20Click(Sender: TObject);
    procedure FtpSendClick(Sender: TObject);
    procedure CustomToolBarLocalItemClick(Sender: TObject);
    procedure FtpGetItemClick(Sender: TObject);
    procedure UndoBtnClick(Sender: TObject);
    procedure RedoBtnClick(Sender: TObject);
  private
    TopLine:TInfoLines;
    LeftLine:TInfoLines;
    MainArray:TMainBoard;
    OriginalArray:TMainBoard;
    Undo:TUndoClass;
    fModified:boolean;
    fCellSize:integer;
    fDifficult:integer;
    fGameName:string;
    fCountSecond:integer;
    fInfoLinesWidth:integer;
    fMidiFile:string;
    CurState:TCrossItemState;
    CurClickX,
    CurClickY:integer;
    function fSizeX:integer;
    function fSizeY:integer;
    procedure RecalcInfoLines;
    function CheckWinner:boolean;
    function GetModified:boolean;
    procedure SetModified(AModified:boolean);
    procedure SetCellSize(ACellSize:integer);
    procedure SetDifficult(ADifficult:integer);
    procedure SetGameName(AGameName:string);
    procedure SetCountSecond(ACountSecond:integer);
    procedure SetInfoLinesWidth(AInfoLinesWidth:integer);
    procedure SetMidiFile(AMidiFile:string);
    //this handler for colored crossword
    procedure ColorQueryMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure UpdateUndoRedoBtn;
  public
    FontName:TFontName;
    FontSize:integer;
    GameAutor:string;
    GameDescription:string;
   //цветная раскраска
    SplitColor: TColor;
    NumberColor: TColor;
    CrossPalette:  TCrossPalette;
    GameState:TGameState;
    FileName:string;
    property Difficult:integer read fDifficult write SetDifficult;
    property SizeX:integer read fSizeX;
    property SizeY:integer read fSizeY;
    property Modified:boolean read GetModified write SetModified;
    property CellSize:integer read fCellSize write SetCellSize;
    property GameName:string read fGameName write SetGameName;
    property CountSecond:integer read fCountSecond write SetCountSecond;
    property InfoLinesWidth:integer read fInfoLinesWidth write SetInfoLinesWidth;
    property MidiFile:string read fMidiFile write SetMidiFile;
    procedure SetSize(ASizeX, ASizeY:integer);
    procedure LoadFromFile(AFileName:string);
    procedure SaveToFile(AFileName:string);
    procedure LoadFromJCW(AFileName:string);
    procedure CustomLoadFromJCW(AFileName:string);
    procedure SetVisibleColoredBtn(AVisible:boolean);
    procedure UpdateColors;
    procedure UpdateCaption;
    procedure PlaySound(Name:string);
  end;

var
  CrossMainForm: TCrossMainForm;
  DeltaX,DeltaY:integer;
implementation

uses CrossSelectLevelUnit, CrossOptUnit, Math, CrossAboutUnit, MMSystem,
  CrossRulesUnit, CrossGroupConv, CrossToolsUnit, CrossFTPSendUnit,
  CrossFTPGetUnit, CrossColorRulesUnit;

{$R *.DFM}
{$R sounds.RES}

procedure TCrossMainForm.SetMidiFile(AMidiFile:string);
begin
  if fMidiFile<>'' then
  begin
    if MIDISound.Checked then MediaPlayer1.Close;
    DeleteFile(fMidiFile);
    if (fMidiFile<>'') then MIDISound.Checked:=false;
  end;
  fMidiFile:=AMidiFile;
  MediaPlayer1.FileName:=fMidiFile;
  if (fMidiFile<>'') and MIDISound.Checked then MediaPlayer1.Open;
end;

procedure TCrossMainForm.SetDifficult(ADifficult:integer);
begin
  fDifficult:=ADifficult;
  case ADifficult of
    0:StatusBar1.Panels[2].Text:='Легко';
    1:StatusBar1.Panels[2].Text:='Средне';
    2:StatusBar1.Panels[2].Text:='Сложно';
    3:StatusBar1.Panels[2].Text:='Невыполнимо';
  else
  end;
end;

procedure TCrossMainForm.SetCountSecond(ACountSecond:integer);
var L:integer;
    S:string;
begin
  fCountSecond:=ACountSecond;
  if ACountSecond=0 then StatusBar1.Panels[1].Text:=''
  else
  begin
    L:=ACountSecond mod 60;
    S:=IntToStr(L); if L<10 then S:='0'+S;
    L:=(ACountSecond div 60) mod 60;
    S:=IntToStr(L)+':'+S; if L<10 then S:='0'+S;
    L:=(ACountSecond div 3600);
    S:=IntToStr(L)+':'+S; if L<10 then S:='0'+S;
    StatusBar1.Panels[1].Text:=S;
  end;
end;

procedure TCrossMainForm.SetGameName(AGameName:string);
begin
  fGameName:=AGameName;
  StatusBar1.Panels[3].Text:=fGameName;
end;

function TCrossMainForm.fSizeX:integer;
begin
  Result:=DrawGrid1.ColCount-InfoLinesWidth;
end;

function TCrossMainForm.fSizeY:integer;
begin
  Result:=DrawGrid1.RowCount-InfoLinesWidth;
end;

procedure TCrossMainForm.SetSize(ASizeX, ASizeY:integer);
begin
  DrawGrid1.ColCount:=ASizeX+fInfoLinesWidth;
  DrawGrid1.RowCount:=ASizeY+fInfoLinesWidth;
  TopLine.SetSize(ASizeX,fInfoLinesWidth);
  LeftLine.SetSize(fInfoLinesWidth,ASizeY);
  OriginalArray.SetSize(ASizeX, ASizeY);
  MainArray.SetSize(ASizeX, ASizeY);
end;

procedure TCrossMainForm.SetInfoLinesWidth(AInfoLinesWidth:integer);
var TempX,TempY:integer;
begin
  TempX:=SizeX;
  TempY:=SizeY;
  fInfoLinesWidth:=AInfoLinesWidth;
  SetSize(TempX, TempY);
end;

procedure TCrossMainForm.SetCellSize(ACellSize:integer);
begin
  fCellSize:=ACellSize;
  DrawGrid1.DefaultColWidth:=fCellSize;
  DrawGrid1.DefaultRowHeight:=fCellSize;
  DeltaX:=(fCellSize+1);
  DeltaY:=(fCellSize+1);
end;

function TCrossMainForm.GetModified:boolean;
begin
  Result:=false;
  if not EditItem.Checked then exit;
  Result:=fModified;
end;

procedure TCrossMainForm.SetModified(AModified:boolean);
begin
  if not EditItem.Checked then AModified:=false;
  fModified:=AModified;
  if fModified then StatusBar1.Panels[1].Text:='Изменён'
  else StatusBar1.Panels[1].Text:=''
end;

procedure TCrossMainForm.DrawGrid1DrawCell(Sender: TObject; ACol, ARow: Integer;
  Rect: TRect; State: TGridDrawState);
var X,Y,L:integer;
    S:string;

procedure FillLefTop;
begin
  DrawGrid1.Canvas.Brush.Color := DrawGrid1.Color;
  DrawGrid1.Canvas.FillRect(Rect);
end;

procedure OutTaskText(Item:TInfoLineItem); //(C:integer; AColor:TCrossItemState);
var Color:TColor;
begin
  if ColoredCross.Checked and (Item.Count>0) then Color:=CrossPalette[Item.Color]
  else Color:=NumberColor;
  DrawGrid1.Canvas.Brush.Color:=Color;
  if ColoredCross.Checked then Color:=TColor((not Color) and $00FFFFFF)
  else Color:=clBlack;
  DrawGrid1.Canvas.Font.Color:=Color;
  DrawGrid1.Canvas.FillRect(Rect);
  if Item.Count>0 then
  begin
    S:=IntToStr(Item.Count);
    L:=((Rect.Right-Rect.Left)-DrawGrid1.Canvas.TextWidth(S)) div 2;
    DrawGrid1.Canvas.TextRect(Rect, Rect.Left+L, Rect.Top, S);
  end;
  if Item.Checked then
  begin
    DrawGrid1.Canvas.Pen.Color:=Color;
    DrawGrid1.Canvas.MoveTo(Rect.Left,Rect.Top);
    DrawGrid1.Canvas.LineTo(Rect.Right,Rect.Bottom);
    DrawGrid1.Canvas.MoveTo(Rect.Right, Rect.Top);
    DrawGrid1.Canvas.LineTo(Rect.Left,Rect.Bottom);
  end;
end;

begin
  X:=ACol-InfoLinesWidth;
  Y:=ARow-InfoLinesWidth;
  with DrawGrid1 do
  begin
//    Canvas.Pen.Color:=SplitColor;
    Canvas.Pen.Width:=(fCellSize div 20) + 1;
    Canvas.Font.Name:=FontName;
    Canvas.Font.Size:=FontSize;
    Canvas.Font.Style:=Canvas.Font.Style+[fsItalic];
    if (ARow<InfoLinesWidth) and (ACol<InfoLinesWidth) then FillLefTop
    else
    if (ARow<InfoLinesWidth) and (ACol>=InfoLinesWidth) then //рисуем верхнюю линию
    begin
      Canvas.Brush.Color := NumberColor;
      OutTaskText(TopLine[X, ARow]);
    end
    else
    if (ARow>=InfoLinesWidth) and (ACol<InfoLinesWidth) then // рисуем боковинку
    begin
      Canvas.Brush.Color := NumberColor;
      OutTaskText(LeftLine[ACol,Y]);
    end
    else
    if (ARow>=InfoLinesWidth) and (ACol>=InfoLinesWidth) then
    begin
      Canvas.Brush.Color := CrossPalette[MainArray[X,Y]];
      Canvas.FillRect(Rect);
      if MainArray[X,Y]=csUnknow then //отрисовка вопроса
      begin
        Canvas.Font.Style:=Canvas.Font.Style-[fsItalic];
        L:=((Rect.Right-Rect.Left)-Canvas.TextWidth('?')) div 2;
        Canvas.TextRect(Rect, Rect.Left+L, Rect.Top, '?');
      end
      else
      if (ShowEmptyCheck) and (MainArray[X,Y]=csEmpty) then //отрисовка креста
      begin
        Canvas.Font.Color:=clBlack;
        Canvas.Font.Name:='Wingdings';
        Canvas.Font.Style:=Canvas.Font.Style-[fsItalic];
        L:=((Rect.Right-Rect.Left)-Canvas.TextWidth('ь')) div 2;
        Canvas.TextRect(Rect, Rect.Left+L, Rect.Top, 'ь');
      end;
    end;
    if (ACol>InfoLinesWidth) and (X mod 5=0) then
    begin
      Canvas.Pen.Color:=SplitColor;
      Canvas.Pen.Width:=(fCellSize div 20) + 1;
      Canvas.MoveTo(Rect.Left,Rect.Top);
      Canvas.LineTo(Rect.Left,Rect.Bottom);
    end;
    if (ARow>InfoLinesWidth) and ((Y+1) mod 5=0) then
    begin
      Canvas.Pen.Color:=SplitColor;
      Canvas.Pen.Width:=2;
      Canvas.MoveTo(Rect.Left,Rect.Bottom);
      Canvas.LineTo(Rect.Right,Rect.Bottom);
    end;
  end;
end;

procedure TCrossMainForm.ColorQueryMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
var X1,Y1:integer;
    Temp:TCrossItemState;
procedure UpdateCell;
var Rect: TRect;
begin
  Rect.Left:=DeltaX*(X1-DrawGrid1.LeftCol);
  Rect.Top:=DeltaY*(Y1-DrawGrid1.TopRow);
  Rect.Right:=Rect.Left+DeltaX-1;
  Rect.Bottom:=Rect.Top+DeltaY-1;
  DrawGrid1DrawCell(Sender, X1,Y1, Rect, []);
end;
begin
  DrawGrid1.MouseToCell(X,Y,X1,Y1);
  X:=X1-InfoLinesWidth;
  Y:=Y1-InfoLinesWidth;
  if (X1>=InfoLinesWidth) and (Y1>=InfoLinesWidth) then
  begin
    Temp:=MainArray[X,Y];
    if Button = mbLeft then
    begin
      if (CurState=csUncheked) or ((CurClickX=X) and (CurClickY=Y))
          or (MainArray[X,Y]=CurState) then
      begin
        if MainArray[X,Y]=csUncheked then MainArray[X,Y]:=csColor1
        else
        if MainArray[X,Y]=High(TCrossItemState)then MainArray[X,Y]:=csUncheked
        else MainArray[X,Y]:=TCrossItemState(byte(MainArray[X,Y])+1);
      end
      else MainArray[X,Y]:=CurState;
      CurClickX:=X;
      CurClickY:=Y;
    end
    else
    if EditItem.Checked then MainArray[X,Y]:=csUncheked
    else
    begin
      if MainArray[X,Y]=csUncheked then MainArray[X,Y]:=csCheced;
      MainArray[X,Y]:=TCrossItemState(Byte(MainArray[X,Y])+1);
      if MainArray[X,Y]>csUnknow then MainArray[X,Y]:=csUncheked;
    end;
    Undo.Push(X,Y,Temp,MainArray[X,Y]);
    UpdateUndoRedoBtn;
    if EditItem.Checked then
    begin
      RecalcInfoLines;
      Modified:=true;
      DrawGrid1.Refresh;
    end
    else UpdateCell;
    if (not EditItem.Checked) and CheckWinner then
    begin
      Timer1.Enabled:=false;
      CountSecond:=0;
      if Application.MessageBox('Вы сложили этот кроссворд. Продолжите?','Поздравляем',
            MB_YESNO+MB_ICONEXCLAMATION)=IDYES then NewGameClick(Sender);
    end;
  end
  else
  if (not EditItem.Checked) then
  begin
    if (Y1<InfoLinesWidth) and (TopLine[x,y1].Count>0) then
    begin
       TopLine.Checked[X,Y1]:=not TopLine.Checked[X,Y1];
       UpdateCell;
    end
    else
    if (X1<InfoLinesWidth) and (LeftLine[x1,y].Count>0) then
    begin
       LeftLine.Checked[X1,Y]:=not LeftLine.Checked[x1,y];
       UpdateCell;
    end;
  end;
end;

procedure TCrossMainForm.DrawGrid1MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var X1,Y1:integer;
    Temp:TCrossItemState;
procedure UpdateCell;
var Rect: TRect;
begin
  Rect.Left:=DeltaX*(X1-DrawGrid1.LeftCol);
  Rect.Top:=DeltaY*(Y1-DrawGrid1.TopRow);
  Rect.Right:=Rect.Left+DeltaX-1;
  Rect.Bottom:=Rect.Top+DeltaY-1;
  DrawGrid1DrawCell(Sender, X1,Y1, Rect, []);
end;

begin
  if Button in [mbLeft,mbRight] then
  begin
    DrawGrid1.MouseToCell(X,Y,X1,Y1);
    X:=X1-InfoLinesWidth;
    Y:=Y1-InfoLinesWidth;
    if (X1>=InfoLinesWidth) and (Y1>=InfoLinesWidth) then
    begin
      Temp:=MainArray[X,Y];
      if (Button = mbLeft) or EditItem.Checked then
      begin
        if MainArray[X,Y]=csUncheked then MainArray[X,Y]:=csCheced
        else MainArray[X,Y]:=csUncheked;
      end
      else
      begin
        if MainArray[X,Y]=csUncheked then MainArray[X,Y]:=csCheced;
        MainArray[X,Y]:=TCrossItemState(Byte(MainArray[X,Y])+1);
        if MainArray[X,Y]>csUnknow then MainArray[X,Y]:=csUncheked;
      end;
      Undo.Push(X,Y,Temp,MainArray[X,Y]);
      UpdateUndoRedoBtn;
      if EditItem.Checked then
      begin
        RecalcInfoLines;
        Modified:=true;
        DrawGrid1.Refresh;
      end
      else UpdateCell;
      if (not EditItem.Checked) and CheckWinner then
      begin
        Timer1.Enabled:=false;
        CountSecond:=0;
        if Application.MessageBox('Вы сложили этот кроссворд. Продолжите?','Поздравляем',
            MB_YESNO+MB_ICONEXCLAMATION)=IDYES then NewGameClick(Sender);
      end;
    end
    else
    if (not EditItem.Checked) then
    begin
      if (Y1<InfoLinesWidth) and (TopLine[x,y1].Count>0) then
      begin
         TopLine.Checked[X,Y1]:=not TopLine.Checked[x,y1];
         UpdateCell;
      end
      else
      if (X1<InfoLinesWidth) and (LeftLine[x1,y].Count>0) then
      begin
         LeftLine.Checked[X1,Y]:=not LeftLine.Checked[x1,y];
         UpdateCell;
      end;
    end;
  end;
end;

procedure TCrossMainForm.FormCreate(Sender: TObject);
var i:integer;
    ItemInfo:TMenuItemInfo;
    B:BOOL;
    L:DWORD;
begin
  ItemInfo.fMask:=MIIM_TYPE;
  B:=GetMenuItemInfo(MainMenu.Handle,Help1.Command,False,ItemInfo);
  L:=GetLastError;
  ItemInfo.fMask:=MIIM_TYPE;
  ItemInfo.fType:=MFT_RIGHTJUSTIFY or MFT_STRING;
  ItemInfo.cch:=4;
  ItemInfo.dwTypeData:='Help';
  B:=SetMenuItemInfo(MainMenu.Handle,Help1.Command,False,ItemInfo);
  L:=GetLastError;
  DrawMenuBar(CrossMainForm.Handle);
{  with MainMenu do
    for i:=0 to Items.Count - 1 do
      if Items[i].Caption='&Help' then begin
        ItemInfo.fMask:=MIIM_TYPE;
        B:=GetMenuItemInfo(Handle,Items[i].Command,False,ItemInfo);
        L:=GetLastError;
        ItemInfo.fMask:=MIIM_TYPE;
        ItemInfo.fType:=MFT_RIGHTJUSTIFY or MFT_STRING;
        ItemInfo.cch:=4;
        ItemInfo.dwTypeData:='Help';
        B:=SetMenuItemInfo(Handle,Items[i].Command,False,ItemInfo);
      end;}
  DrawMenuBar(CrossMainForm.Handle);

  GameState:=gsGame;
  MIDISound.Checked:=PlaySounds;
  TopLine:=TInfoLines.Create(1,1);
  LeftLine:=TInfoLines.Create(1,1);
  MainArray:=CrossTypesUnit.TMainBoard.Create(1,1);
  OriginalArray:=CrossTypesUnit.TMainBoard.Create(1,1);
  Undo:=TUndoClass.Create;
  OpenDialog1.InitialDir:=ExtractFilePath(Application.ExeName)+'games';
  SaveDialog1.InitialDir:=OpenDialog1.InitialDir;
  OpenCurGameDialog.InitialDir:=ExtractFilePath(Application.ExeName)+'SAVE';
  SaveCurGameDialog.InitialDir:=OpenCurGameDialog.InitialDir;
  CellSize:=20;
  InfoLinesWidth:=1;
  SetSize(15, 15);
  FontName:='Arial';
  FontSize:=12;
  NumberColor:=clTeal;
  SplitColor:=clRed;
  CrossPalette[csUncheked]:=clWhite;
  CrossPalette[csCheced]:=clBlue;
  CrossPalette[csEmpty]:=clLime;
  CrossPalette[csUnknow]:=clAqua;
  CrossPalette[csColor1]:=clBlack;
  CrossPalette[csColor2]:=clRed;
  CrossPalette[csColor3]:=clBlue;
  CrossPalette[csColor4]:=clYellow;
  CrossPalette[csColor5]:=clGreen;
  CrossPalette[csColor6]:=clLime;
  CrossPalette[csColor7]:=clTeal;
  CrossPalette[csColor8]:=clSilver;
  SetVisibleColoredBtn(false);
  NewGameClick(Sender);
  DrawGrid1.Refresh;
  UpdateUndoRedoBtn;
end;

procedure TCrossMainForm.DrawGrid1MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
var X1,Y1:integer;
begin
   DrawGrid1.MouseToCell(X,Y,X1,Y1);
   X:=Max(X1-InfoLinesWidth,0);
   Y:=Max(Y1-InfoLinesWidth,0);
   StatusBar1.Panels[0].Text:='X - '+IntToSTr(X)+'  Y - '+IntToSTr(Y);
end;

procedure TCrossMainForm.EditItemClick(Sender: TObject);
begin
  EditItem.Checked:=not EditItem.Checked;
  BackToGame.Enabled:=EditItem.Checked;
  SaveItem.Enabled:=EditItem.Checked;
  SaveGameBtn.Visible:=EditItem.Checked;
  OpenGameBtn.Visible:=EditItem.Checked;
  InverItem.Enabled:=EditItem.Checked;
  SaveCurGBtn.Visible:=not EditItem.Checked;
  LoadCurGBtn.Visible:=not EditItem.Checked;
  EksportItems.Enabled:=EditItem.Checked;
  LoadItem.Enabled:=EditItem.Checked;
  FtpSend.Visible:=EditItem.Checked;
  FtpSendItem.Enabled:=EditItem.Checked;
  Undo.Clear;
  if EditItem.Checked then
  begin
    MainArray.Assign(OriginalArray);
    Timer1.Enabled:=false;
    CountSecond:=0;
    CurClickX:=-1;
    CurClickY:=-1;
    GameState:=gsEditing;
  end
  else
  begin
    GameState:=gsGame;
    OriginalArray.Assign(MainArray);
    MainArray.Clear;
  end;
  RecalcInfoLines;
  UpdateCaption;
  DrawGrid1.Refresh;
end;

procedure TCrossMainForm.LoadItemClick(Sender: TObject);
var Ext:string;
begin
  if ColoredCross.Checked then
  begin
    if OpenColorGame.Execute then
       LoadFromFile(OpenColorGame.FileName);
  end
  else
  if OpenDialog1.Execute then
  begin
    Ext:=ExtractFileExt(OpenDialog1.FileName);
    if Ext='.cwg' then LoadFromFile(OpenDialog1.FileName) else
    if (Ext='.jcw') and EditItem.Checked then LoadFromJCW(OpenDialog1.FileName);
  end;
  DrawGrid1.Refresh;
end;

procedure TCrossMainForm.LoadFromFile(AFileName:string);
var
  S:TFileStream;
  T:TInfoTag;
  fEof:boolean;

procedure LoadBoardSize;
var R:TBoardSize;
begin
  fEof:=S.Read(R,T.Size)<>T.Size;
  if not fEof then
  begin
    SetSize(R.X, R.Y);
    Difficult:=R.Difficult;
  end;
end;

procedure LoadBoardAutor;
begin
  if T.Size=0 then exit;
  SetLength(GameAutor,T.Size);
  S.Read(GameAutor[1],T.Size);
end;

procedure LoadBoardName;
var R:string;
begin
  if T.Size=0 then exit;
  SetLength(R,T.Size);
  fEof:=S.Read(R[1],T.Size)<>T.Size;
  if not fEof then GameName:=R;
end;

procedure LoadFontName;
begin
  if T.Size=0 then exit;
  SetLength(FontName,T.Size);
  S.Read(FontName[1],T.Size);
end;

procedure LoadFontSize;
var R:integer;
begin
  fEof:=S.Read(R,SizeOf(Integer))<>T.Size;
  if not fEof then FontSize:=R;
end;

procedure LoadMainBoard;
var R:TCrossBoard;
    i,j:integer;
begin
  fEof:=S.Read(R,T.Size)<>T.Size;
  if not fEof then
  begin
    MainArray.SetSize(50,50);
    for j:=0 to 49 do
       for i:=0 to 49 do
         MainArray[i,j]:=R[i,j];
  end;
end;

procedure LoadOriginalBoard;
var R:TCrossBoard;
    i,j:integer;
begin
  fEof:=S.Read(R,T.Size)<>T.Size;
  if not fEof then
  begin
    OriginalArray.SetSize(50,50);
    for j:=0 to 49 do
       for i:=0 to 49 do
         OriginalArray[i,j]:=R[i,j];
  end;
end;

procedure LoadNewMainBoard;
begin
  if GameState<>gsLoadUserGame then OriginalArray.Load(S)
  else MainArray.Load(S);
end;

procedure LoadNewOriginalBoard;
begin
//  if GameState=gsLoadUserGame then
   OriginalArray.Load(S)
//  else MainArray.Load(S);
end;

procedure LoadColors;
var R:TColorRec;
begin
  fEof:=S.Read(R,T.Size)<>T.Size;
  if not fEof then
  begin
    CrossPalette[csUncheked]:=R.UnchekedColor;
    CrossPalette[csCheced]:=R.ChekedColor;
    CrossPalette[csEmpty]:=R.EmptyColor;
    DrawGrid1.Color:=R.BackgroundColor;
    NumberColor:=R.NumberColor;
    SplitColor:=R.SplitColor;
    CrossPalette[csUnknow]:=R.UnknowColor;
    CrossPalette[csColor1]:=R.Color1;
    CrossPalette[csColor2]:=R.Color2;
    CrossPalette[csColor3]:=R.Color3;
    CrossPalette[csColor4]:=R.Color4;
    CrossPalette[csColor5]:=R.Color5;
    CrossPalette[csColor6]:=R.Color6;
    CrossPalette[csColor7]:=R.Color7;
    CrossPalette[csColor8]:=R.Color8;
  end;
end;

procedure LoadCellSize;
var R:integer;
begin
  fEof:=S.Read(R,T.Size)<>T.Size;
  if not fEof then CellSize:=R;
end;

procedure LoadTimeCount;
var R:integer;
begin
  fEof:=S.Read(R,T.Size)<>T.Size;
  if not fEof then CountSecond:=R;
end;

procedure LoadGameDescription;
var R:string;
begin
  if T.Size=0 then exit;
  SetLength(R,T.Size);
  fEof:=S.Read(R[1],T.Size)<>T.Size;
  if not fEof then GameDescription:=R;
end;

procedure LoadMIDISound;
var MM:TFileStream;
begin
  MidiFile:='';
  if T.Size<>0 then
  begin
    MM:=TFileStream.Create('temp.mid',fmCreate);
    MM.CopyFrom(S,T.Size);
    MM.Free;
    MidiFile:='temp.mid';
  end;
end;

procedure LoadTopLine;
begin
  TopLine.Load(S);
end;

procedure LoadLeftLine;
begin
  LeftLine.Load(S);
end;

var Ext:string;
begin
  Ext:=ExtractFileExt(AFileName);
  if (Ext= '.ccw') or (Ext='.scc') then ColoredCrossClick(nil)
  else SimpleCrossClick(nil);
  S:=TFileStream.Create(AFileName,fmOpenRead);
  fEof:=false;
  repeat
    fEof:=S.Read(T,SizeOf(T))<>SizeOf(T);
    if not fEof then
    case T.ID of
      idBoardName:LoadBoardName;
      idBoardAutor:LoadBoardAutor;
      idFontName:LoadFontName;
      idFontSize:LoadFontSize;
      idMainBoard:if EditItem.Checked then LoadMainBoard else LoadOriginalBoard;
      idSizeBoard:LoadBoardSize;
      idColors:LoadColors;
      idCellSize:LoadCellSize;
      idGameDesc:LoadGameDescription;
      idMIDISound:LoadMIDISound;
      idTimeCount:if not EditItem.Checked then LoadTimeCount;
      idCurBoard:if not EditItem.Checked then LoadMainBoard;
      idTopLine:if not EditItem.Checked then LoadTopLine;
      idLeftLine:if not EditItem.Checked then LoadLeftLine;
      idNewMainBoard:if EditItem.Checked then LoadNewMainBoard else LoadNewOriginalBoard;
      idNewCurBoard:if not EditItem.Checked then LoadNewMainBoard;
    else
      S.Seek(T.Size,soFromCurrent);
    end;
  until fEof;
  S.Free;
  CrossMainForm.UpdateColors;
  RecalcInfoLines;
  UpdateCaption;
  FileName:=AFileName;
end;

procedure TCrossMainForm.SaveItemClick(Sender: TObject);
var S:string;
begin
  S:=FileName;
  if ColoredCross.Checked then
  begin
    if S='' then SaveColorGame.FileName:=GameName+'.ccw'
    else  SaveColorGame.FileName:=S;
    if SaveColorGame.Execute then
    begin
      S:=SaveColorGame.FileName;
      SaveToFile(S);
    end;
  end
  else
  begin
    if S='' then SaveDialog1.FileName:=GameName+'.cwg'
    else SaveDialog1.FileName:=S;
    if SaveDialog1.Execute then
    begin
      S:=SaveDialog1.FileName;
      SaveToFile(S);
    end;
  end;
end;

procedure TCrossMainForm.SaveToFile(AFileName:string);
var
  S:TFileStream;
  T:TInfoTag;

procedure StoreBoardSize;
var R:TBoardSize;
begin
  T.ID:=idSizeBoard;
  T.Size:=SizeOf(TBoardSize);
  S.Write(T,SizeOf(T));
  R.X:=SizeX;R.Y:=SizeY;R.Difficult:=Difficult;
  S.Write(R,SizeOf(TBoardSize));
end;

procedure StoreBoardAutor;
begin
  T.ID:=idBoardAutor;
  T.Size:=Length(GameAutor);
  S.Write(T,SizeOf(T));
  if T.Size>0 then S.Write(GameAutor[1],T.Size);
end;

procedure StoreBoardName;
begin
  T.ID:=idBoardName;
  T.Size:=Length(GameName);
  S.Write(T,SizeOf(T));
  if T.Size>0 then S.Write(GameName[1],T.Size);
end;

procedure StoreFontName;
begin
  T.ID:=idFontName;
  T.Size:=Length(FontName);
  S.Write(T,SizeOf(T));
  if T.Size>0 then S.Write(FontName[1],T.Size);
end;

procedure StoreFontSize;
begin
  T.ID:=idFontSize;
  T.Size:=SizeOf(Integer);
  S.Write(T,SizeOf(T));
  S.Write(FontSize,SizeOf(Integer));
end;

procedure StoreCellSize;
begin
  T.ID:=idCellSize;
  T.Size:=SizeOf(Integer);
  S.Write(T,SizeOf(T));
  S.Write(fCellSize,SizeOf(Integer));
end;

procedure StoreTimeCount;
begin
  T.ID:=idTimeCount;
  T.Size:=SizeOf(Integer);
  S.Write(T,SizeOf(T));
  S.Write(fCountSecond,SizeOf(Integer));
end;

procedure StoreMainBoard;
begin
  T.ID:=idNewMainBoard;
  T.Size:=MainArray.Size;
  S.Write(T,SizeOf(T));
  if GameState=gsSaveUserGame then OriginalArray.Store(S)
  else MainArray.Store(S);
end;

procedure StoreTestBoard;
begin
  T.ID:=idNewCurBoard;
  T.Size:=MainArray.Size;
  S.Write(T,SizeOf(T));
  MainArray.Store(S);
end;

procedure StoreColors;
var R:TColorRec;
begin
  R.UnchekedColor:=CrossPalette[csUncheked];
  R.ChekedColor:=CrossPalette[csCheced];
  R.EmptyColor:=CrossPalette[csEmpty];
  R.BackgroundColor:=DrawGrid1.Color;
  R.NumberColor:=NumberColor;
  R.SplitColor:=SplitColor;
  R.UnknowColor:=CrossPalette[csUnknow];
  R.Color1:=CrossPalette[csColor1];
  R.Color2:=CrossPalette[csColor2];
  R.Color3:=CrossPalette[csColor3];
  R.Color4:=CrossPalette[csColor4];
  R.Color5:=CrossPalette[csColor5];
  R.Color6:=CrossPalette[csColor6];
  R.Color7:=CrossPalette[csColor7];
  R.Color8:=CrossPalette[csColor8];
  T.ID:=idColors;
  T.Size:=SizeOf(TColorRec);
  S.Write(T,SizeOf(T));
  S.Write(R, SizeOf(TColorRec));
end;

procedure StoreGameDescription;
begin
  T.ID:=idGameDesc;
  T.Size:=Length(GameDescription);
  S.Write(T,SizeOf(T));
  if T.Size>0 then S.Write(GameDescription[1],T.Size);
end;

procedure StoreMIDISound;
var MM:TFileStream;
begin
  if MidiFile<>'' then
  begin
    MM:=TFileStream.Create(MidiFile,fmOpenRead);
    T.ID:=idMIDISound;
    T.Size:=MM.Size;
    S.Write(T,SizeOf(T));
    if T.Size>0 then S.CopyFrom(MM,T.Size);
    MM.Free;
  end;
end;

procedure StoreLeftLine;
begin
  T.ID:=idLeftLine;
  T.Size:=LeftLine.Size;
  S.Write(T,SizeOf(T));
  LeftLine.Store(S);
end;

procedure StoreTopLine;
begin
  T.ID:=idTopLine;
  T.Size:=TopLine.Size;
  S.Write(T,SizeOf(T));
  TopLine.Store(S);
end;

begin
  S:=TFileStream.Create(AFileName,fmCreate);
  StoreBoardSize;
  StoreBoardAutor;
  StoreBoardName;
  StoreFontName;
  StoreFontSize;
  StoreMainBoard;
  StoreColors;
  StoreCellSize;
  StoreGameDescription;
  if not EditItem.Checked then StoreTimeCount;
  if not EditItem.Checked then StoreTestBoard;
  if not EditItem.Checked then StoreLeftLine;
  if not EditItem.Checked then StoreTopLine;
  StoreMIDISound;
  S.Free;
  Modified:=false;
  FileName:=AFileName;
end;

procedure TCrossMainForm.GamePropItemsClick(Sender: TObject);
begin
  CrossOptForm:=TCrossOptForm.Create(Application);
  if CrossOptForm.ShowModal=mrOk then
     DrawGrid1.Refresh;
  CrossOptForm.Free;
end;

procedure TCrossMainForm.PrintItemClick(Sender: TObject);
var LeftMargin,
    CrosSize, CurTextLine:integer;
    S:string;

procedure DrawGrid;
var i, Step, RC, BC, TC:integer;
begin
  //Draw horisontal lines
  RC:=(InfoLinesWidth+SizeX)*CrosSize+LeftMargin;
  Step:=CurTextLine;
  for i:=0 to InfoLinesWidth+SizeY do
  begin
    if i=InfoLinesWidth then Printer.Canvas.Pen.Width:=4 else
    if (i>InfoLinesWidth) and  ((I-InfoLinesWidth) mod 5=0) then Printer.Canvas.Pen.Width:=4
    else Printer.Canvas.Pen.Width:=1;
    Printer.Canvas.MoveTo(LeftMargin, Step);
    Printer.Canvas.LineTo(RC, Step);
    Step:=Step+CrosSize;
  end;
  //Draw vertical lines
  TC:=CurTextLine;
  BC:=CurTextLine+(InfoLinesWidth+SizeY)*CrosSize;
  Step:=LeftMargin;
  for i:=0 to InfoLinesWidth+SizeX do
  begin
    if i=InfoLinesWidth then Printer.Canvas.Pen.Width:=4 else
    if (i>InfoLinesWidth+1) and ((I-InfoLinesWidth) mod 5=0) then Printer.Canvas.Pen.Width:=4
    else Printer.Canvas.Pen.Width:=1;
    Printer.Canvas.MoveTo(Step, TC);
    Printer.Canvas.LineTo(Step, BC);
    Step:=Step+CrosSize;
  end;
end;

procedure FillTask;
var i,j, CSW, CSH, EmptyCros:integer;
begin
  EmptyCros:=InfoLinesWidth*CrosSize;
  for J:=0 to InfoLinesWidth-1 do
    for i:=0 to SizeX-1 do //пишем числа верхней шапки
      if TopLine[i,j].Count<>0 then
      begin
          S:=IntToStr(TopLine[i,j].Count);
          CSW:=(CrosSize - Printer.Canvas.TextWidth(S)) div 2;
          CSH:=(CrosSize - Printer.Canvas.TextHeight(S)) div 2;
          Printer.Canvas.TextOut(EmptyCros+LeftMargin+i*CrosSize+CSW,
            CurTextLine+CrosSize*j+CSH,S);
      end;
  for J:=0 to SizeY-1 do //пишем левые числа
    for i:=0 to InfoLinesWidth-1 do
      if LeftLine[i,j].Count<>0 then
      begin
        S:=IntToStr(LeftLine[i,j].Count);
        CSW:=(CrosSize - Printer.Canvas.TextWidth(S)) div 2;
        CSH:=(CrosSize - Printer.Canvas.TextHeight(S)) div 2;
          Printer.Canvas.TextOut(LeftMargin+i*CrosSize+CSW,
            CurTextLine+EmptyCros+CrosSize*j+CSH,S);
      end;
end;

begin
  with Printer do
  begin
    S:='ЯПОНСКИЙ КРОССВОРД';
    BeginDoc;
    Title:=GameName;
    Font.Name:='Arial';
    Font.Size:=12;
    LeftMargin:=20;
    CurTextLine:=10;
    Canvas.TextOut((PageWidth-Canvas.TextWidth(S)) div 2, CurTextLine, S);
    CurTextLine:=CurTextLine+Canvas.TextHeight(S)+Canvas.TextHeight(S) div 2;
    S:='название: '+GameName;
    Canvas.TextOut((PageWidth-Canvas.TextWidth(S)) div 2, CurTextLine, S);
    CurTextLine:=CurTextLine+Canvas.TextHeight(S)+Canvas.TextHeight(S) div 2;
    S:='Автор: '+GameAutor;
    Canvas.TextOut((PageWidth-Canvas.TextWidth(S)) div 2, CurTextLine, S);
    CurTextLine:=CurTextLine+Canvas.TextHeight(S)+Canvas.TextHeight(S) div 2;
    CrosSize:=Canvas.TextWidth('000');
    DrawGrid;
    FillTask;
    EndDoc;
  end;
end;

procedure TCrossMainForm.ExitItemClick(Sender: TObject);
begin
  Close;
end;

function TCrossMainForm.CheckWinner:boolean;
var i,j:integer;
begin
  Result:=false;
  if EditItem.Checked then exit;
  for j:=0 to SizeY-1 do
    for i:=0 to SizeX-1 do
      if (MainArray[i,j]<>OriginalArray[i,j]) then
        if not ((MainArray[i,j] in [csUncheked, csEmpty]) and
               (OriginalArray[i,j]=csUncheked)) then
         exit;
  Result:=true;
  PlaySound('APPLAUSE');
end;

procedure TCrossMainForm.NewGameClick(Sender: TObject);
var S:string;
begin
  if not EditItem.Checked then
  begin
    PlaySound('NEW');
    CrossSelectLevelForm:=TCrossSelectLevelForm.Create(Application);
    if CrossSelectLevelForm.ShowModal=mrOk then
    begin
      if CrossSelectLevelForm.SelectedItem<>'' then
      begin
        S:=ExtractFileExt(CrossSelectLevelForm.SelectedItem);
        if (S='.scg') or (S='.scc') then GameState:=gsLoadUserGame
        else GameState:=gsLoadNew;
        MainArray.Clear;
        TopLine.Clear(ClearAll);
        LeftLine.Clear(ClearAll);
        Undo.Clear;
        MidiFile:='';
        LoadFromFile(CrossSelectLevelForm.SelectedItem);
        GameState:=gsGame;
        DrawGrid1.Refresh;
        CountSecond:=0;
        Timer1.Enabled:=true;
      end;
    end;
    CrossSelectLevelForm.Free;
  end
  else
  begin
    MainArray.Clear;
    Undo.Clear;
    InfoLinesWidth:=1;
    GamePropItemsClick(Sender);
  end;
  UpdateCaption;
end;

procedure TCrossMainForm.TollBarItemClick(Sender: TObject);
begin
  TollBarItem.Checked:=not TollBarItem.Checked;
  ToolBarLocalItem.Checked:=TollBarItem.Checked;
  ToolBar.Visible:=TollBarItem.Checked;
end;

procedure TCrossMainForm.FlatBtnItemClick(Sender: TObject);
begin
  FlatBtnItem.Checked:=not FlatBtnItem.Checked;
  FlatBtnLocalItem.Checked:=FlatBtnItem.Checked;
  if FlatBtnItem.Checked then ToolBar.Options:=ToolBar.Options+[sbFlatBtns]
  else ToolBar.Options:=ToolBar.Options-[sbFlatBtns];
end;

procedure TCrossMainForm.FormCloseQuery(Sender: TObject;
  var CanClose: Boolean);
begin
  CanClose:=true;
  if Modified then
    CanClose:=Application.MessageBox('Данные были изменены. Сохраните?','Внимание.',
    MB_YESNO+MB_ICONQUESTION)=IDNO;
end;

procedure TCrossMainForm.AboutItemClick(Sender: TObject);
begin
  PlaySound('ABOUT');
  AboutBox:=TAboutBox.Create(Application);
  AboutBox.ShowModal;
  AboutBox.Free;
end;

procedure TCrossMainForm.CrossRulesItemClick(Sender: TObject);
var Form:TForm;
begin
  PlaySound('CASHREG');
  if (Sender as TComponent).Tag=0 then
    Form:=TCrossRulesForm.Create(Application)
  else
    Form:=TCrossColorRulesForm.Create(Application);
  Form.ShowModal;
  Form.Free;
end;

procedure TCrossMainForm.LoadFromJCW(AFileName:string);
begin
  CustomLoadFromJCW(AFileName);
  DrawGrid1.Refresh;
  GamePropItemsClick(nil);
end;

procedure TCrossMainForm.CustomLoadFromJCW(AFileName:string);
var
  S:TFileStream;
  X,Y:byte;
  P:PByteArray;
  i,j,k:integer;
begin
  S:=TFileStream.Create(AFileName, fmOpenRead);
  S.Read(X, SizeOf(Byte));
  S.Read(Y, SizeOf(Byte));
  SetSize(X, Y);
  GetMem(P,X*Y);
  S.Read(P^,x*y);
  k:=0;
  MainArray.Clear;
  for i:=0 to x-1 do
    for j:=0 to y-1 do
    begin
      MainArray[i,j]:=TCrossItemState(P^[k]=2);
      inc(k);
    end;
  FreeMem(P,x*y);
  S.Free;
  case x*y of
    0..225   :Difficult:=0;
    226..625 :Difficult:=1;
    626..1225:Difficult:=2;
  else
    Difficult:=3;
  end;
  RecalcInfoLines;
  GameName:='';
end;

procedure TCrossMainForm.InverItemClick(Sender: TObject);
var i,j:integer;
begin
  for j:=0 to SizeY-1 do
    for i:=0 to SizeX-1 do
      MainArray[i,j]:=TCrossItemState(not Boolean(MainArray[i,j]));
  Modified:=true;
  RecalcInfoLines;
  DrawGrid1.Refresh;
end;

procedure TCrossMainForm.Timer1Timer(Sender: TObject);
begin
  CountSecond:=CountSecond+1;
end;

procedure TCrossMainForm.MIDISoundClick(Sender: TObject);
begin
  if fMIDIFile='' then exit;
  MIDISound.Checked:=not MIDISound.Checked;
  PlaySounds:=MIDISound.Checked;
  if MIDISound.Checked then
  begin
    MediaPlayer1.Open;
    MediaPlayer1.Play
  end
  else
  begin
    MediaPlayer1.Stop;
    MediaPlayer1.Close;
  end;
end;

procedure TCrossMainForm.SaveCurGameItemClick(Sender: TObject);
begin
  if ColoredCross.Checked then
  begin
    if SaveUserColor.Execute then
    begin
      GameState:=gsSaveUserGame;
      SaveToFile(SaveUserColor.FileName);
      GameState:=gsGame;
    end;
  end
  else
  begin
    if SaveCurGameDialog.Execute then
    begin
      GameState:=gsSaveUserGame;
      SaveToFile(SaveCurGameDialog.FileName);
      GameState:=gsGame;
    end;
  end;
end;

procedure TCrossMainForm.OpenCurGameItemClick(Sender: TObject);
procedure DoOpen(AName:string);
begin
  GameState:=gsLoadUserGame;
  TopLine.Clear(ClearAll);
  LeftLine.Clear(ClearAll);
  LoadFromFile(AName);
  GameState:=gsGame;
  DrawGrid1.Refresh;
  Timer1.Enabled:=true;
end;
begin
  if ColoredCross.Checked then
    if OpenUserColor.Execute then DoOpen(OpenUserColor.FileName)
    else
  else
    if OpenCurGameDialog.Execute then DoOpen(OpenCurGameDialog.FileName);
end;

procedure TCrossMainForm.N18Click(Sender: TObject);
begin
  GroupConvForm:=TGroupConvForm.Create(Application);
  GroupConvForm.ShowModal;
  GroupConvForm.Free;
end;

procedure TCrossMainForm.SimpleCrossClick(Sender: TObject);
begin
  if EditItem.Checked then exit;
  SimpleCross.Checked:=true;
  SetVisibleColoredBtn(false);
  DrawGrid1.OnMouseDown:=DrawGrid1MouseDown;
end;


procedure TCrossMainForm.ColoredCrossClick(Sender: TObject);
begin
  if EditItem.Checked then exit;
  ColoredCross.Checked:=true;
  SetVisibleColoredBtn(true);
  UpdateColors;
  DrawGrid1.OnMouseDown:=ColorQueryMouseDown;
  CurClickX:=-1;
  CurClickY:=-1;
end;

procedure TCrossMainForm.SetVisibleColoredBtn(AVisible:boolean);
begin
  ColorBtn1.Visible:=AVisible;
  ColorBtn2.Visible:=AVisible;
  ColorBtn3.Visible:=AVisible;
  ColorBtn4.Visible:=AVisible;
  ColorBtn5.Visible:=AVisible;
  ColorBtn6.Visible:=AVisible;
  ColorBtn7.Visible:=AVisible;
  ColorBtn8.Visible:=AVisible;
  ColorOffBtn.Visible:=AVisible;
end;

procedure TCrossMainForm.UpdateColors;
begin
  ColorBtn1.Font.Color:=CrossPalette[csColor1];
  ColorBtn2.Font.Color:=CrossPalette[csColor2];
  ColorBtn3.Font.Color:=CrossPalette[csColor3];
  ColorBtn4.Font.Color:=CrossPalette[csColor4];
  ColorBtn5.Font.Color:=CrossPalette[csColor5];
  ColorBtn6.Font.Color:=CrossPalette[csColor6];
  ColorBtn7.Font.Color:=CrossPalette[csColor7];
  ColorBtn8.Font.Color:=CrossPalette[csColor8];
end;

procedure TCrossMainForm.RecalcInfoLines;
var i, j, k, TempW, TempSizeX, TempSizeY:integer;
    LastState:TCrossItemState;
    Test:TMainBoard;

procedure SkipZerroTop;
begin
  while (j<TempSizeY) and (Test[i,j] in [csUncheked, csEmpty, csUnknow]) do
    inc(j);
end;

procedure SkipZerroLeft;
begin
  while (i<TempSizeX) and (Test[i,j] in [csUncheked, csEmpty, csUnknow]) do
    inc(i);
end;

var CS:TILClearStates;
begin
  CS:=ClearAll;
  if GameState=gsLoadUserGame then CS:=CS-[csChecked];
  if EditItem.Checked then Test:=MainArray else Test:=OriginalArray;

  TopLine.Clear(CS);
  LeftLine.Clear(CS);

  TempSizeX:=SizeX;
  TempSizeY:=SizeY;
  TempW:=1;
  for i:=0 to TempSizeX-1 do
  begin
    J:=0;
    k:=-1;
    while J<TempSizeY do
    begin
      SkipZerroTop;
      if j<TempSizeY then
      begin
        inc(k);
        TempW:=Max(TempW,K+1);
        TopLine.SetSize(SizeX,TempW);
        LastState:=Test[i,j];
        if ColoredCross.Checked then TopLine.Color[i,k]:=LastState;
        while (J<TempSizeY) and (Test[i,j]=LastState) do
        begin
          inc(j);
          TopLine.Count[i,k]:=TopLine.Count[i,k]+1;
        end;
      end;
    end;
  end;

  for j:=0 to TempSizeY-1 do
  begin
    i:=0;
    k:=-1;
    while i<TempSizeX do
    begin
      SkipZerroLeft;
      if i<TempSizeX then
      begin
        inc(k);
        TempW:=Max(TempW,K+1);
        LeftLine.SetSize(TempW,SizeY);
        LastState:=Test[i,j];
        if ColoredCross.Checked then LeftLine.Color[k,j]:=LastState;
        while (i<TempSizeX) and (Test[i,j]=LastState) do
        begin
          inc(i);
          LeftLine.Count[k,j]:=LeftLine.Count[k,j]+1;
        end;
      end;
    end;
  end;
  InfoLinesWidth:=TempW;
  SetSize(TempSizeX,TempSizeY);
end;

procedure TCrossMainForm.UpdateCaption;
begin
  if EditItem.Checked then
  begin
    if ColoredCross.Checked then Caption:='Цветной японский кроссворд - РЕДАКТОР'
    else Caption:='Японский кроссворд - РЕДАКТОР'
  end
  else
  begin
    if ColoredCross.Checked then Caption:='Цветной японский кроссворд'
    else Caption:='Японский кроссворд';
  end;
end;

procedure TCrossMainForm.ColorBtnClick(Sender: TObject);
begin
  if (Sender as TComponent).Tag=0 then CurState:=csUncheked
  else CurState:=TCrossItemState((Sender as TComponent).Tag+
                 byte(csColor1)-1);
end;

procedure TCrossMainForm.FormDestroy(Sender: TObject);
begin
  TopLine.Free;
  LeftLine.Free;
  Undo.Free;
  MidiFile:='';
end;

procedure TCrossMainForm.N20Click(Sender: TObject);
begin
  CrossToolsForm:=TCrossToolsForm.Create(Application);
  CrossToolsForm.ShowModal;
  CrossToolsForm.Free;
end;

procedure TCrossMainForm.PlaySound(Name:string);
var WaveHandle  : THandle;
    WavePointer : pointer;
begin
  if not PlaySounds then exit;
  WaveHandle  := FindResource(hInstance,PChar(Name),RT_RCDATA);
  if WaveHandle<>0 then
  begin
    WaveHandle:= LoadResource(hInstance,WaveHandle);
    if WaveHandle<>0 then
    begin
      WavePointer := LockResource(WaveHandle);
      sndPlaySound(WavePointer,snd_Memory OR SND_ASYNC);
      UnlockResource(WaveHandle);
      FreeResource(WaveHandle);
    end;
  end;
end;

procedure TCrossMainForm.FtpSendClick(Sender: TObject);
begin
  if fModified then SaveItemClick(Sender);
  FTPSendForm:=TFTPSendForm.Create(Application);
  FTPSendForm.ShowModal;
  FTPSendForm.Free;
end;

procedure TCrossMainForm.CustomToolBarLocalItemClick(Sender: TObject);
begin
  ToolBar.Customize(0);
end;

procedure TCrossMainForm.FtpGetItemClick(Sender: TObject);
begin
  FTPGetForm:=TFTPGetForm.Create(Application);
  FTPGetForm.ShowModal;
  FTPGetForm.Free;
end;

procedure TCrossMainForm.UndoBtnClick(Sender: TObject);
var X,Y:integer;
    OldS,NewS:TCrossItemState;
begin
  PlaySound('UNDO');
  if not Undo.Undo(X,Y,OldS,NewS) then exit;
  MainArray[X,Y]:=OldS;
  DrawGrid1.Refresh;
  UpdateUndoRedoBtn;
end;

procedure TCrossMainForm.RedoBtnClick(Sender: TObject);
var X,Y:integer;
    OldS,NewS:TCrossItemState;
begin
  PlaySound('REDO');
  if not Undo.Redo(X,Y,OldS,NewS) then exit;
  MainArray[X,Y]:=NewS;
  DrawGrid1.Refresh;
  UpdateUndoRedoBtn;
end;

procedure TCrossMainForm.UpdateUndoRedoBtn;
begin
  UndoBtn.Enabled:=Undo.UndoEnabled;
  RedoBtn.Enabled:=Undo.RedoEnabled;
  UndoItem.Enabled:=Undo.UndoEnabled;
  RedoItem.Enabled:=Undo.RedoEnabled;
end;

end.

