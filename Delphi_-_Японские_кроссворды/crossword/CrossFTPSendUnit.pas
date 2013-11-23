unit CrossFTPSendUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ComCtrls, StdCtrls, Buttons, Psock, NMFtp;

type
  TFTPSendForm = class(TForm)
    NMFTP1: TNMFTP;
    OkBtn: TBitBtn;
    CancelBtn: TBitBtn;
    BitBtn3: TBitBtn;
    Animate1: TAnimate;
    Edit1: TEdit;
    Label1: TLabel;
    Edit2: TEdit;
    UserID: TEdit;
    Edit4: TEdit;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    procedure OkBtnClick(Sender: TObject);
    procedure CancelBtnClick(Sender: TObject);
    procedure NMFTP1Success(Trans_Type: TCmdType);
    procedure NMFTP1Failure(var Handled: Boolean; Trans_Type: TCmdType);
    procedure NMFTP1Connect(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  FTPSendForm: TFTPSendForm;

implementation

uses CrossMainUnit;

{$R *.DFM}

procedure TFTPSendForm.OkBtnClick(Sender: TObject);
begin
  Animate1.Show;
  Animate1.Active := True;
  OkBtn.Enabled:=false;
  CancelBtn.Kind:=bkAbort;
  NMFTP1.Host:=Edit1.Text;
  NMFTP1.UserID:=UserID.Text;
  try
    NMFTP1.Connect;
  except
    CancelBtn.Kind:=bkCancel;
    OkBtn.Enabled:=true;
    Animate1.Active := false;
  end;
end;

procedure TFTPSendForm.CancelBtnClick(Sender: TObject);
begin
  if CancelBtn.Kind=bkAbort then
  begin
    NMFTP1.Abort;
    ModalResult:=mrNone;
    CancelBtn.Kind:=bkCancel;
    OkBtn.Enabled:=true;
    Animate1.Active := false;
  end;
end;

procedure TFTPSendForm.NMFTP1Success(Trans_Type: TCmdType);
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
  CancelBtn.Kind:=bkCancel;
  OkBtn.Enabled:=true;
  Animate1.Active := false;
  if Trans_Type=cmdUpload then
  begin
    NMFTP1.Disconnect;
    ModalResult:=mrOk;
  end;
end;

procedure TFTPSendForm.NMFTP1Failure(var Handled: Boolean;
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
  CancelBtn.Kind:=bkCancel;
  OkBtn.Enabled:=true;
  Animate1.Active := false;
end;

procedure TFTPSendForm.NMFTP1Connect(Sender: TObject);
begin
  NMFTP1.ChangeDir(Edit2.Text);
  NMFTP1.Upload(CrossMainForm.FileName,ExtractFileName(CrossMainForm.FileName));
end;

end.
