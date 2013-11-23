unit CrossGroupConv;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons, ComCtrls, FileCtrl;

type
  TGroupConvForm = class(TForm)
    SourseListBox: TFileListBox;
    FilterComboBox1: TFilterComboBox;
    DirectoryListBox1: TDirectoryListBox;
    DirectoryListBox2: TDirectoryListBox;
    DriveComboBox1: TDriveComboBox;
    Label1: TLabel;
    Label2: TLabel;
    DriveComboBox2: TDriveComboBox;
    DestFileListBox: TFileListBox;
    FilterComboBox2: TFilterComboBox;
    ProgressBar1: TProgressBar;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    BitBtn3: TBitBtn;
    BitBtn4: TBitBtn;
    BitBtn5: TBitBtn;
    ReplaseExists: TCheckBox;
    procedure BitBtn1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
  private
    procedure Convert(FileName:string);
  public
    { Public declarations }
  end;

var
  GroupConvForm: TGroupConvForm;

implementation

uses CrossMainUnit;

{$R *.DFM}

procedure TGroupConvForm.Convert(FileName:string);
var
  S1,S2:string;
begin
  ProgressBar1.Position:=ProgressBar1.Position+1;
  S1:=DirectoryListBox1.Directory+'\'+FileName;
  S2:=DirectoryListBox2.Directory+'\'+ChangeFileExt(FileName, '.cwg');
  if FileExists(S2) and not ReplaseExists.Checked then exit;
  FileName:=Copy(FileName,1,Pos('.',FileName)-1);
  CrossMainForm.CustomLoadFromJCW(S1);
  CrossMainForm.GameName:=FileName;
  CrossMainForm.SaveToFile(S2);
end;

procedure TGroupConvForm.BitBtn1Click(Sender: TObject);
var i: Integer;
begin
  ProgressBar1.Max:=SourseListBox.SelCount;
  ProgressBar1.Position:=0;
  for i := 0 to (SourseListBox.Items.Count - 1) do
    if SourseListBox.Selected[i] then Convert(SourseListBox.Items[i]);
  CrossMainForm.DrawGrid1.Refresh;
end;

procedure TGroupConvForm.FormCreate(Sender: TObject);
begin
  DirectoryListBox2.Directory:=ExtractFilePath(Application.ExeName)+'games';
end;

procedure TGroupConvForm.BitBtn2Click(Sender: TObject);
var i: Integer;
begin
  ProgressBar1.Max:=SourseListBox.Items.Count;
  ProgressBar1.Position:=0;
  for i := 0 to (SourseListBox.Items.Count - 1) do
    Convert(SourseListBox.Items[i]);
  CrossMainForm.DrawGrid1.Refresh;
end;

end.
