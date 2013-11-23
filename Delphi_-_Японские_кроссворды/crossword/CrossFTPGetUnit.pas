unit CrossFTPGetUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons, ComCtrls, Psock, NMFtp;

type
  TFTPGetForm = class(TForm)
    NMFTP1: TNMFTP;
    UserID: TEdit;
    Password: TEdit;
    Host: TEdit;
    RemoteDir: TEdit;
    Animate1: TAnimate;
    GetDirBtn: TButton;
    ListBox1: TListBox;
    CheckBox1: TCheckBox;
    GetFilesBtn: TButton;
    BitBtn1: TBitBtn;
    LabelServ: TLabel;
    Label2: TLabel;
    Animate2: TAnimate;
    Label3: TLabel;
    Label4: TLabel;
    Label1: TLabel;
    GetFileName: TLabel;
    procedure GetDirBtnClick(Sender: TObject);
    procedure NMFTP1Connect(Sender: TObject);
    procedure NMFTP1ListItem(Listing: String);
    procedure NMFTP1Success(Trans_Type: TCmdType);
    procedure NMFTP1Failure(var Handled: Boolean; Trans_Type: TCmdType);
    procedure FormCreate(Sender: TObject);
    procedure GetFilesBtnClick(Sender: TObject);
    procedure NMFTP1Disconnect(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
  private
    Conect:boolean;
    HomePath:string;
    CurFileNum:integer;
    function GetNextFileName:string;
    { Private declarations }
  public
    { Public declarations }
  end;

var
  FTPGetForm: TFTPGetForm;

implementation

{$R *.DFM}

procedure TFTPGetForm.GetDirBtnClick(Sender: TObject);
begin
  NMFTP1.Host:=Host.Text;
  NMFTP1.UserID:=UserID.Text;
  NMFTP1.Password:=Password.Text;
  ListBox1.Items.Clear;
  Animate1.Active := true;
  try
    Conect:=true;
    NMFTP1.Connect;
  except
//    CancelBtn.Kind:=bkCancel;
//    OkBtn.Enabled:=true;
    Animate1.Active := false;
  end;
end;

procedure TFTPGetForm.NMFTP1Connect(Sender: TObject);
begin
  if Conect then NMFTP1.ChangeDir(RemoteDir.Text);
end;

procedure TFTPGetForm.NMFTP1ListItem(Listing: String);
begin
  if not FileExists(HomePath+Listing) then
     ListBox1.Items.Add(Listing);
end;

procedure TFTPGetForm.NMFTP1Success(Trans_Type: TCmdType);
var S:string;
begin
  case Trans_Type of
    cmdChangeDir:   Label1.Caption:='ChangeDir success';
    cmdMakeDir:     Label1.Caption:='MakeDir success';
    cmdDelete:      Label1.Caption:='Delete success';
    cmdRemoveDir:   Label1.Caption:='RemoveDir success';
    cmdList:        Label1.Caption:='List success';
    cmdRename:      Label1.Caption:='Rename success';
    cmdUpRestore:   Label1.Caption:='UploadRestore success';
    cmdDownRestore: Label1.Caption:='DownloadRestore success';
    cmdDownload:    Label1.Caption:='Download success';
    cmdUpload:      Label1.Caption:='Upload success';
    cmdAppend:      Label1.Caption:='UploadAppend success';
    cmdReInit:      Label1.Caption:='Reinitialize success';
    cmdAllocate:    Label1.Caption:='Allocate success';
    cmdNList:       Label1.Caption:='NList success';
    cmdDoCommand:   Label1.Caption:='DoCommand success';
    cmdCurrentDir: Label1.Caption:='CurrentDir success';
  else
    Label1.Caption:='';
  end;
  case Trans_Type of
     cmdChangeDir:if Conect then NMFTP1.Nlist;
     cmdUpload,
     cmdDownload:begin
                   S:=GetNextFileName;
                   if S<>'' then NMFTP1.Download(S,HomePath+S)
                   else NMFTP1.Disconnect;
                 end;
     cmdNList:if ListBox1.Items.Count>0 then
              begin
                GetFilesBtn.Enabled:=true;
                GetDirBtn.Enabled:=false;
                Animate1.Active := false;
              end
              else NMFTP1.Disconnect;
  else
  end;
end;

procedure TFTPGetForm.NMFTP1Failure(var Handled: Boolean;
  Trans_Type: TCmdType);
begin
  case Trans_Type of
    cmdChangeDir:   Label1.Caption:='ChangeDir failure';
    cmdMakeDir:     Label1.Caption:='MakeDir failure';
    cmdDelete:      Label1.Caption:='Delete failure';
    cmdRemoveDir:   Label1.Caption:='RemoveDir failure';
    cmdList:        Label1.Caption:='List failure';
    cmdRename:      Label1.Caption:='Rename failure';
    cmdUpRestore:   Label1.Caption:='UploadRestore failure';
    cmdDownRestore: Label1.Caption:='DownloadRestore failure';
    cmdDownload:    Label1.Caption:='Download failure';
    cmdUpload:      Label1.Caption:='Upload failure';
    cmdAppend:      Label1.Caption:='UploadAppend failure';
    cmdReInit:      Label1.Caption:='Reinitialize failure';
    cmdAllocate:    Label1.Caption:='Allocate failure';
    cmdNList:       Label1.Caption:='NList failure';
    cmdDoCommand:   Label1.Caption:='DoCommand failure';
    cmdCurrentDir:  Label1.Caption:='CurrentDir failure';
  else
    Label1.Caption:='';
  end;
  NMFTP1.Disconnect;
{  CancelBtn.Kind:=bkCancel;
  OkBtn.Enabled:=true;
  Animate1.Active := false;
  Conect:=false;}
end;

procedure TFTPGetForm.FormCreate(Sender: TObject);
begin
  Conect:=false;
  HomePath:=ExtractFilePath(Application.ExeName)+'GAMES\';;
end;

procedure TFTPGetForm.GetFilesBtnClick(Sender: TObject);
var S:string;
begin
  CurFileNum:=-1;
  S:=GetNextFileName;
  if S<>'' then
  begin
    Animate2.Active := true;
    NMFTP1.Download(S,HomePath+S);
  end
  else NMFTP1.Disconnect;
end;

function TFTPGetForm.GetNextFileName:string;
begin
  Result:='';
  inc(CurFileNum);
  while (CurFileNum<ListBox1.Items.Count) and
        not ListBox1.Selected[CurFileNum] do inc(CurFileNum);
  if CurFileNum<ListBox1.Items.Count then
    Result:=ListBox1.Items[CurFileNum];
  GetFileName.Caption:=Result;
end;

procedure TFTPGetForm.NMFTP1Disconnect(Sender: TObject);
begin
  Animate1.Active := false;
  Animate2.Active := false;
  GetFilesBtn.Enabled:=false;
  GetDirBtn.Enabled:=true;
  Conect:=false;
  GetFileName.Caption:='';
end;

procedure TFTPGetForm.BitBtn1Click(Sender: TObject);
begin
  if Conect then NMFTP1.Disconnect;
end;

end.
