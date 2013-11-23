unit CrossOptUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons, Spin, RxCombos, ExtCtrls, ComCtrls, Placemnt;

type
  TCrossOptForm = class(TForm)
    OkBtn: TBitBtn;
    BitBtn2: TBitBtn;
    BitBtn3: TBitBtn;
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    Label3: TLabel;
    Label4: TLabel;
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    SizeX: TSpinEdit;
    SizeY: TSpinEdit;
    GameAutor: TEdit;
    GameName: TEdit;
    TabSheet2: TTabSheet;
    GameDescription: TMemo;
    TabSheet3: TTabSheet;
    GroupBox2: TGroupBox;
    Label8: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label9: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    BackgroundColor: TColorComboBox;
    UnchekedColor: TColorComboBox;
    ChekedColor: TColorComboBox;
    EmptyColor: TColorComboBox;
    NumberColor: TColorComboBox;
    SplitColor: TColorComboBox;
    UnknowColor: TColorComboBox;
    Label5: TLabel;
    FontComboBox1: TFontComboBox;
    FontSize: TSpinEdit;
    Label6: TLabel;
    Label7: TLabel;
    GridSize: TSpinEdit;
    Difficult: TRadioGroup;
    FormStorage1: TFormStorage;
    CheckBox1: TCheckBox;
    OpenDialog1: TOpenDialog;
    TabSheet4: TTabSheet;
    GroupBox3: TGroupBox;
    Color1: TColorComboBox;
    Label15: TLabel;
    Label16: TLabel;
    Color2: TColorComboBox;
    Label17: TLabel;
    Color3: TColorComboBox;
    Label18: TLabel;
    Color4: TColorComboBox;
    Label19: TLabel;
    Color5: TColorComboBox;
    Label20: TLabel;
    Color6: TColorComboBox;
    Label21: TLabel;
    Color7: TColorComboBox;
    Label22: TLabel;
    Color8: TColorComboBox;
    procedure FormCreate(Sender: TObject);
    procedure OkBtnClick(Sender: TObject);
    procedure CheckBox1Click(Sender: TObject);
  private
    //MIDIFIleName:string;
    { Private declarations }
  public
    { Public declarations }
  end;

var
  CrossOptForm: TCrossOptForm;

implementation

uses CrossMainUnit, CrossTypesUnit;

{$R *.DFM}

procedure TCrossOptForm.FormCreate(Sender: TObject);
begin
  SizeX.Value:=CrossMainForm.SizeX;
  SizeY.Value:=CrossMainForm.SizeY;
  FontComboBox1.FontName:=CrossMainForm.FontName;
  FontSize.Value:=CrossMainForm.FontSize;
  GameName.Text:=CrossMainForm.GameName;
  GameAutor.Text:=CrossMainForm.GameAutor;
  GridSize.Value:=CrossMainForm.CellSize;
  //настройка цветовой палитры
  BackgroundColor.ColorValue:=CrossMainForm.DrawGrid1.Color;
  NumberColor.ColorValue:=CrossMainForm.NumberColor;
  SplitColor.ColorValue:=CrossMainForm.SplitColor;
  UnchekedColor.ColorValue:=CrossMainForm.CrossPalette[csUncheked];
  ChekedColor.ColorValue:=CrossMainForm.CrossPalette[csCheced];
  EmptyColor.ColorValue:=CrossMainForm.CrossPalette[csEmpty];
  UnknowColor.ColorValue:=CrossMainForm.CrossPalette[csUnknow];
  Color1.ColorValue:=CrossMainForm.CrossPalette[csColor1];
  Color2.ColorValue:=CrossMainForm.CrossPalette[csColor2];
  Color3.ColorValue:=CrossMainForm.CrossPalette[csColor3];
  Color4.ColorValue:=CrossMainForm.CrossPalette[csColor4];
  Color5.ColorValue:=CrossMainForm.CrossPalette[csColor5];
  Color6.ColorValue:=CrossMainForm.CrossPalette[csColor6];
  Color7.ColorValue:=CrossMainForm.CrossPalette[csColor5];
  Color8.ColorValue:=CrossMainForm.CrossPalette[csColor6];

  Difficult.ItemIndex:=CrossMainForm.Difficult;
  GameDescription.Text:=CrossMainForm.GameDescription;
  OpenDialog1.FileName:=CrossMainForm.MidiFile;
  //запрещ€ем редактирование
  SizeX.Enabled:=CrossMainForm.EditItem.Checked;
  SizeY.Enabled:=CrossMainForm.EditItem.Checked;
  GameName.Enabled:=CrossMainForm.EditItem.Checked;
  GameAutor.Enabled:=CrossMainForm.EditItem.Checked;
  Difficult.Enabled:=CrossMainForm.EditItem.Checked;
  GameDescription.Enabled:=CrossMainForm.EditItem.Checked;
  CheckBox1.Enabled:=CrossMainForm.EditItem.Checked;
  Color1.Enabled:=CrossMainForm.EditItem.Checked and CrossMainForm.ColoredCross.Checked;
  Color2.Enabled:=CrossMainForm.EditItem.Checked and CrossMainForm.ColoredCross.Checked;
  Color3.Enabled:=CrossMainForm.EditItem.Checked and CrossMainForm.ColoredCross.Checked;
  Color4.Enabled:=CrossMainForm.EditItem.Checked and CrossMainForm.ColoredCross.Checked;
  Color5.Enabled:=CrossMainForm.EditItem.Checked and CrossMainForm.ColoredCross.Checked;
  Color6.Enabled:=CrossMainForm.EditItem.Checked and CrossMainForm.ColoredCross.Checked;
  Color7.Enabled:=CrossMainForm.EditItem.Checked and CrossMainForm.ColoredCross.Checked;
  Color8.Enabled:=CrossMainForm.EditItem.Checked and CrossMainForm.ColoredCross.Checked;
end;

procedure TCrossOptForm.OkBtnClick(Sender: TObject);
var SourseMID, DestMID:TFileStream;
begin
  CrossMainForm.FontName:=FontComboBox1.FontName;
  CrossMainForm.FontSize:=FontSize.Value;
  CrossMainForm.GameName:=GameName.Text;
  CrossMainForm.GameAutor:=GameAutor.Text;
  CrossMainForm.CellSize:=GridSize.Value;
  //настройка цветовой палитры
  CrossMainForm.DrawGrid1.Color:=BackgroundColor.ColorValue;
  CrossMainForm.NumberColor:=NumberColor.ColorValue;
  CrossMainForm.SplitColor:=SplitColor.ColorValue;
  CrossMainForm.CrossPalette[csUncheked]:=UnchekedColor.ColorValue;
  CrossMainForm.CrossPalette[csCheced]:=ChekedColor.ColorValue;
  CrossMainForm.CrossPalette[csEmpty]:=EmptyColor.ColorValue;
  CrossMainForm.CrossPalette[csUnknow]:=UnknowColor.ColorValue;
  CrossMainForm.CrossPalette[csColor1]:=Color1.ColorValue;
  CrossMainForm.CrossPalette[csColor2]:=Color2.ColorValue;
  CrossMainForm.CrossPalette[csColor3]:=Color3.ColorValue;
  CrossMainForm.CrossPalette[csColor4]:=Color4.ColorValue;
  CrossMainForm.CrossPalette[csColor5]:=Color5.ColorValue;
  CrossMainForm.CrossPalette[csColor6]:=Color6.ColorValue;
  CrossMainForm.CrossPalette[csColor7]:=Color7.ColorValue;
  CrossMainForm.CrossPalette[csColor8]:=Color8.ColorValue;


  CrossMainForm.Difficult:=Difficult.ItemIndex;
//  CrossMainForm.InfoLinesWidth:=InfoLinesWidth.Value;
  CrossMainForm.GameDescription:=GameDescription.Text;
  CrossMainForm.Modified:=true;
  CrossMainForm.SetSize(SizeX.Value,SizeY.Value);
  if CheckBox1.Checked then
  begin
    SourseMID:=TFileStream.Create(OpenDialog1.FileName, fmOpenRead);
    DestMID:=TFileStream.Create('temp.mid', fmCreate);
    DestMID.CopyFrom(SourseMID,SourseMID.Size);
    DestMID.Free;
    SourseMID.Free;
    CrossMainForm.MidiFile:='temp.mid';
  end
  else CrossMainForm.MIDIFile:='';
  CrossMainForm.UpdateColors;
end;

procedure TCrossOptForm.CheckBox1Click(Sender: TObject);
begin
  if CheckBox1.Checked then OpenDialog1.Execute;
end;

end.
