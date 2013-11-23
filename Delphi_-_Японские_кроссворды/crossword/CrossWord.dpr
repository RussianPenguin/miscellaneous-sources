program CrossWord;

uses
  Forms,
  CrossMainUnit in 'CrossMainUnit.pas' {CrossMainForm},
  CrossOptUnit in 'CrossOptUnit.pas' {CrossOptForm},
  CrossSelectLevelUnit in 'CrossSelectLevelUnit.pas' {CrossSelectLevelForm},
  CrossTypesUnit in 'CrossTypesUnit.pas',
  CrossAboutUnit in 'CrossAboutUnit.pas' {AboutBox},
  CrossRulesUnit in 'CrossRulesUnit.pas' {CrossRulesForm},
  CrossGroupConv in 'CrossGroupConv.pas' {GroupConvForm},
  CrossToolsUnit in 'CrossToolsUnit.pas' {CrossToolsForm},
  CrossFTPSendUnit in 'CrossFTPSendUnit.pas' {FTPSendForm},
  CrossFTPGetUnit in 'CrossFTPGetUnit.pas' {FTPGetForm},
  UndoClassUnit in 'UndoClassUnit.pas',
  CrossColorRulesUnit in 'CrossColorRulesUnit.pas' {CrossColorRulesForm};

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'японский кроссворд';
  Application.CreateForm(TCrossMainForm, CrossMainForm);
  Application.Run;
end.
