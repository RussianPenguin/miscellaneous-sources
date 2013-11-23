unit CrossToolsUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons;

type
  TCrossToolsForm = class(TForm)
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    BitBtn3: TBitBtn;
    ShowStartupNewCheckBox: TCheckBox;
    EmptyCheck: TCheckBox;
    PlaySoundsCheck: TCheckBox;
    procedure FormCreate(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  CrossToolsForm: TCrossToolsForm;

implementation

uses CrossTypesUnit;

{$R *.DFM}

procedure TCrossToolsForm.FormCreate(Sender: TObject);
begin
  EmptyCheck.Checked:=ShowEmptyCheck;
  PlaySoundsCheck.Checked:=PlaySounds;
  ShowStartupNewCheckBox.Checked:=ShowStartupNew;
end;

procedure TCrossToolsForm.BitBtn1Click(Sender: TObject);
begin
  ShowEmptyCheck:=EmptyCheck.Checked;
  PlaySounds:=PlaySoundsCheck.Checked;
  ShowStartupNew:=ShowStartupNewCheckBox.Checked;
///
  StoreIniFile;
end;

end.
