unit CrossSelectLevelUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Buttons, StdCtrls, ComCtrls, ImgList, ExtCtrls, Placemnt, Menus, SpeedBar;

type
  TCrossSelectLevelForm = class(TForm)
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    FormStorage1: TFormStorage;
    LargeImageList: TImageList;
    PopupMenu1: TPopupMenu;
    LargeItem: TMenuItem;
    ListItem: TMenuItem;
    DetailItem: TMenuItem;
    SmallItem: TMenuItem;
    Panel1: TPanel;
    ListView1: TListView;
    TreeView1: TTreeView;
    Splitter1: TSplitter;
    SpeedBar1: TSpeedBar;
    SpeedbarSection1: TSpeedbarSection;
    LevelUpBtn: TSpeedItem;
    SmallBtn: TSpeedItem;
    LargeBtn: TSpeedItem;
    ListBtn: TSpeedItem;
    DetailBtn: TSpeedItem;
    N5: TMenuItem;
    N6: TMenuItem;
    SpeedbarSection2: TSpeedbarSection;
    PropertyBtn: TSpeedItem;
    SmallImageList: TImageList;
    N1: TMenuItem;
    N2: TMenuItem;
    N3: TMenuItem;
    procedure FormCreate(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure TreeView1Click(Sender: TObject);
    procedure LargeItemClick(Sender: TObject);
    procedure ListView1Click(Sender: TObject);
    procedure PropertyBtnClick(Sender: TObject);
    procedure LevelUpBtnClick(Sender: TObject);
    procedure ListView1Compare(Sender: TObject; Item1, Item2: TListItem;
      Data: Integer; var Compare: Integer);
    procedure ListView1ColumnClick(Sender: TObject; Column: TListColumn);
  private
    SimpleEasy: TTreeNode;
    SimpleMedium: TTreeNode;
    SimpleHard:TTreeNode;
    SimpleImposible:TTreeNode;
    ColorEasy: TTreeNode;
    ColorMedium: TTreeNode;
    ColorHard:TTreeNode;
    ColorImposible:TTreeNode;
    SimpleSaved:TTreeNode;
    ColorSaved:TTreeNode;
    Saved,Simple,Color:TTreeNode;

    NewPath:string;
    SavedPath:string;
    ColumnToSort: Integer;
//    function GetSelectedItem:string;
    procedure AddFiles(GroupNum:integer; AllFiles:boolean);
    function GetGroupNum:integer;
    procedure AddFolders(F:boolean);
  public
    SelectedItem:string;
  end;

var
  CrossSelectLevelForm: TCrossSelectLevelForm;
const
  NamesArray : array[1..4] of string = ('Легко','Средне',
                                        'Сложно','Невыполнимо');
  SaveNamesArray : array[1..2] of string = ('Простые','Цветные');
  TopFoldersNames : array[1..3] of string = ('Цветные',
                                             'Простые',
                                             'Сохранённые решения');
const
  CountWorkedFolders = 9;

implementation
uses CrossTypesUnit, CrossMainUnit;

{$R *.DFM}

procedure TCrossSelectLevelForm.FormCreate(Sender: TObject);

begin
  Simple         :=TreeView1.Items[5];
  SimpleEasy     :=TreeView1.Items[6];
  SimpleMedium   :=TreeView1.Items[7];
  SimpleHard     :=TreeView1.Items[8];
  SimpleImposible:=TreeView1.Items[9];

  Color          :=TreeView1.Items[0];
  ColorEasy      :=TreeView1.Items[1];
  ColorMedium    :=TreeView1.Items[2];
  ColorHard      :=TreeView1.Items[3];
  ColorImposible :=TreeView1.Items[4];

  Saved          :=TreeView1.Items[10];
  SimpleSaved    :=TreeView1.Items[11];
  ColorSaved     :=TreeView1.Items[12];

  ListView1.Items.Clear;

  NewPath:=ExtractFilePath(Application.ExeName)+'games\';
  SavedPath:=ExtractFilePath(Application.ExeName)+'SAVE\';
end;

procedure TCrossSelectLevelForm.BitBtn2Click(Sender: TObject);
var Path:string;
begin
  if (ListView1.ItemFocused<>nil) and (GetGroupNum<CountWorkedFolders) and
     (GetGroupNum>-1) then
  begin
    if GetGroupNum<8 then Path:=NewPath else Path:=SavedPath;
    SelectedItem:=Path+ListView1.ItemFocused.Caption+ExtArray[Longint(ListView1.ItemFocused.Data)];
    ModalResult:=mrOk;
  end;
end;

function TCrossSelectLevelForm.GetGroupNum:integer;
begin
  Result:=-1;
  if TreeView1.Selected=SimpleEasy then Result:=0 else
  if TreeView1.Selected=SimpleMedium then Result:=1 else
  if TreeView1.Selected=SimpleHard then Result:=2 else
  if TreeView1.Selected=SimpleImposible then Result:=3 else
  if TreeView1.Selected=ColorEasy then Result:=4 else
  if TreeView1.Selected=ColorMedium then Result:=5 else
  if TreeView1.Selected=ColorHard then Result:=6 else
  if TreeView1.Selected=ColorImposible then Result:=7 else
  if TreeView1.Selected=SimpleSaved then Result:=8 else
  if TreeView1.Selected=ColorSaved then Result:=9 else
  if TreeView1.Selected=Simple then Result:=10 else
  if TreeView1.Selected=Color then Result:=11 else
  if TreeView1.Selected=Saved then Result:=12;
end;

procedure TCrossSelectLevelForm.AddFolders(F:boolean);
var ListItem:TListItem;
    I:integer;
begin
  ListView1.Items.Clear;
  if F then
    for i:=1 to 4 do
    begin
      ListItem :=ListView1.Items.Add;
      ListItem.Caption := NamesArray[i];
      ListItem.ImageIndex:=0;
    end
  else
    for i:=1 to 2 do
    begin
      ListItem :=ListView1.Items.Add;
      ListItem.Caption := SaveNamesArray[i];
      ListItem.ImageIndex:=0;
    end
end;

procedure TCrossSelectLevelForm.TreeView1Click(Sender: TObject);
begin
  CrossMainForm.PlaySound('CLICK');
  if (TreeView1.Selected=Simple) or (TreeView1.Selected=Color) or
     (TreeView1.Selected=Saved) then
    AddFolders(TreeView1.Selected<>Saved)
  else AddFiles(GetGroupNum,
                 (TreeView1.Selected=SimpleSaved) or(TreeView1.Selected=ColorSaved));
end;

procedure TCrossSelectLevelForm.LargeItemClick(Sender: TObject);
begin
  CrossMainForm.PlaySound('CLICK');
  case (Sender as TComponent).Tag of
    0:ListView1.ViewStyle:=vsIcon;
    1:ListView1.ViewStyle:=vsList;
    2:ListView1.ViewStyle:=vsReport;
    3:ListView1.ViewStyle:=vsSmallIcon;
  end;
  if (Sender is TMenuItem) then
  begin
    (Sender as TMenuItem).Checked:=true;
    case (Sender as TComponent).Tag of
      0:LargeBtn.Down:=true;
      3:SmallBtn.Down:=true;
      1:ListBtn.Down:=true;
      2:DetailBtn.Down:=true;
    end;
  end
  else
  begin
    TSpeedItem(Sender).Down:=true;
    case (Sender as TComponent).Tag of
      0:LargeItem.Checked:=true;
      3:SmallItem.Checked:=true;
      1:ListItem.Checked:=true;
      2:DetailItem.Checked:=true;
    end;
  end;
end;

procedure TCrossSelectLevelForm.AddFiles(GroupNum:integer; AllFiles:boolean);
var A:string;
    ListItem:TListItem;
    C:integer;
    R:TSearchRec;
    S:TFileStream;
    Buf:TBoardSize;
    Sz:TBoardSize;
    Path:string;
    LL:Longint;
begin
  if (GetGroupNum<0) or (GroupNum>CountWorkedFolders) then exit;
  ListView1.Items.Clear;
  case GroupNum of
    0..3:LL:=0;
    4..7:begin
           LL:=1;
           Dec(GroupNum,4)
         end;
    8   :LL:=2;
    9   :LL:=3;
  else
    LL:=0;
  end;
  if LL<2 then Path:=NewPath
  else Path:=SavedPath;
  C:=FindFirst(Path+'*'+ExtArray[LL], faAnyFile, R);
  while C=0 do
  begin
    S:=TFileSTream.Create(Path+R.Name, fmOpenRead);
    if GetTag(S,idSizeBoard, Buf) then
      if (Buf.Difficult=GroupNum) or AllFiles then
      begin
        ListItem :=ListView1.Items.Add;
        ListItem.Caption := Copy(R.Name,1,Pos('.',R.Name)-1);
        ListItem.ImageIndex:=2+ord((LL=3) or (LL=1));
        ListItem.Data:=Pointer(LL);
        S.Seek(0,soFromBeginning);
        FillChar(Sz,SizeOf(Sz), 0);
        GetTag(S, idSizeBoard, Sz);
        ListItem.SubItems.Add(Format('%d x %d', [Sz.X, Sz.Y]));
        S.Seek(0,soFromBeginning);
        A:='';
        GetStringTag(S, idBoardAutor, A);
        ListItem.SubItems.Add(A);
      end;
    S.Free;
    C:=FindNext(R)
  end;
  FindClose(R);
end;

procedure TCrossSelectLevelForm.ListView1Click(Sender: TObject);
var Path:string;
begin
  if ListView1.ItemFocused=nil then exit;
  CrossMainForm.PlaySound('CLICK');
  if TreeView1.Selected=nil then
  begin
    if ListView1.ItemFocused.Caption='Цветные' then TreeView1.Selected:=Color
    else
    if ListView1.ItemFocused.Caption='Сохранённые решения' then
       TreeView1.Selected:=Saved
    else TreeView1.Selected:=Simple;
  end
  else
  if TreeView1.Selected=Simple then
  begin
    case ListView1.ItemFocused.Caption[3] of
      'г':TreeView1.Selected:=SimpleEasy;
      'е':TreeView1.Selected:=SimpleMedium;
      'о':TreeView1.Selected:=SimpleHard;
      'в':TreeView1.Selected:=SimpleImposible;
    else
      exit;
    end;
  end
  else
  if TreeView1.Selected=Color then
  begin
    case ListView1.ItemFocused.Caption[3] of
      'г':TreeView1.Selected:=ColorEasy;
      'е':TreeView1.Selected:=ColorMedium;
      'о':TreeView1.Selected:=ColorHard;
      'в':TreeView1.Selected:=ColorImposible;
    else
      exit;
    end;
  end
  else
  if TreeView1.Selected=Saved then
  begin
    case ListView1.ItemFocused.Index of
      0:TreeView1.Selected:=SimpleSaved;
      1:TreeView1.Selected:=ColorSaved;
    end;
  end
  else
  begin
    if Longint(ListView1.ItemFocused.Data)<2 then Path:=NewPath
    else Path:=SavedPath;
    SelectedItem:=Path+ListView1.ItemFocused.Caption+ExtArray[Longint(ListView1.ItemFocused.Data)];
    ModalResult:=mrOk;
    exit;
  end;
  TreeView1.Selected.Expand(false);
  TreeView1Click(Sender);
end;

procedure TCrossSelectLevelForm.PropertyBtnClick(Sender: TObject);
begin
//
end;

procedure TCrossSelectLevelForm.LevelUpBtnClick(Sender: TObject);
procedure AddTopFolders;
var ListItem:TListItem;
    I:integer;
begin
  ListView1.Items.Clear;
  for i:=1 to 3 do
  begin
    ListItem :=ListView1.Items.Add;
    ListItem.Caption := TopFoldersNames[i];
    ListItem.ImageIndex:=0;
  end;
  TreeView1.Selected:=nil;
  TreeView1.FullCollapse;
end;
begin
  CrossMainForm.PlaySound('CLICK');
  case GetGroupNum of
    0..3:begin
          AddFolders(true);
          TreeView1.Selected:=Simple;
         end;
    4..7:begin
          AddFolders(true);
          TreeView1.Selected:=Color;
         end;
    8..9:begin
          AddFolders(false);
          TreeView1.Selected:=Saved;
         end;
    10..12:AddTopFolders;
  end;
  if TreeView1.Selected<>nil then TreeView1.Selected.Collapse(false);
end;

procedure TCrossSelectLevelForm.ListView1Compare(Sender: TObject; Item1,
  Item2: TListItem; Data: Integer; var Compare: Integer);
var
  ix: Integer;
begin
  if ColumnToSort = 0 then
    Compare := CompareText(Item1.Caption,Item2.Caption)
  else
  begin
    ix := ColumnToSort - 1;
    Compare := CompareText(Item1.SubItems[ix],Item2.SubItems[ix]);
  end;
end;

procedure TCrossSelectLevelForm.ListView1ColumnClick(Sender: TObject;
  Column: TListColumn);
begin
  if (GetGroupNum > CountWorkedFolders) or
     (GetGroupNum < 0) then exit;
  ColumnToSort := Column.Index;
  (Sender as TCustomListView).AlphaSort;
end;

end.
