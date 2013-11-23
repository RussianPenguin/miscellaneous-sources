program Phonebook;

uses
  QForms,
  U_main in 'U_main.pas' {MainForm},
  U_Edit in 'U_Edit.pas' {EditForm};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TMainForm, MainForm);
  Application.Run;
end.
