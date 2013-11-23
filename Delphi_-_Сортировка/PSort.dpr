program PSort;

uses
  Forms,
  Sort in 'Sort.pas' {FSort};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TFSort, FSort);
  Application.Run;
end.
