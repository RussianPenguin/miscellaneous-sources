unit UParse;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, AxCtrls, OleCtrls, VCF1, ComCtrls;

type
  TForm1 = class(TForm)
    EFile: TEdit;
    BOpen: TButton;
    BStart: TButton;
    ODFile: TOpenDialog;
    REOut: TRichEdit;
    procedure BOpenClick(Sender: TObject);
    procedure BStartClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
  // ������ � �������
  magazine = record
    mdate: String;
    mname :String;
  end;
  //������ � ��������
  mentry = record
  //�������� ���������
    ename: String;
  //URL
    eurl: String;
  //���������� �� �����
    epath: String;
  //������ ���������
    estatus: String;
  //������ ;-)))
    eauthor: String;
  //������ � �������
    eabout: array[1..100] of String;
  end;


var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.BOpenClick(Sender: TObject);
begin
  if(ODFile.Execute()) then
  begin
    EFile.Text := ODFile.FileName;
  end;
 end;
//������ ��������� �������� ������������.
//�������� ������ - ������� ����� � ����� ������.
procedure TForm1.BStartClick(Sender: TObject);
var
//���� ��� "��������"
  FFP:TextFile;
//��������� ����� ���������
  CurLine:String;
//�������� ��������
  CurEnt: mentry;
//�������� �������
  CurMag: magazine;
//�������� ��������������� ����� CD(DVD)
  CurBlock: String;
//������� �������
  CurRazdel :String;
//��������� �� ������� ������ textline
  CurTextLine :Integer;
//�������... ������ �������.
  i: Integer;
begin
  //��������� ����
  AssignFile(FFP,EFile.Text);
  //������������� ��������� � ������ �����
  Reset(FFP);
  //���������, ���� �� �������� ����� �����
  while not EOF(FFP) do
  begin
    ReadLn(FFP, CurLine);
    CurLine := Trim(CurLine);
    if CurLine = 'Main' then
      begin
        ReadLn(FFP, CurLine);
        CurLine := Trim(CurLine);
        if CurLine = '{' then
        begin
          while true do
          begin
            ReadLn(FFP, CurLine);
            CurLine := Trim(CurLine);
            if CurLine = '}' then
              break;
            if Pos('number',CurLine) = 1 then
            begin
              //������������� ��������
              CurMag.mname := '][akep';
              //�������� ���� �������
              CurMag.mdate := Copy(CurLine,10,Length(Curline)-9);
              //�������� �� �����������������
              //(����� ������� �� ��������� �����)
              //REOut.Lines.Add(CurMag.mdate);
              //����� �������� ;-)
            end;
          end;
        end;
      end;
    if CurLine = 'Block' then
    begin
      //����� ������ ���-�� ���� ;-)))
      ReadLn(FFP, CurLine);
      if (CurLine = '{') then
      begin
        //�������� ������ ������� ���� ;-)
        while not EOF(FFP) do
        begin
          ReadLn(FFP, CurLine);
          if CurLine = '}' then
            break;
          CurLine := Trim(CurLine);
          //��� ��� � ����� Article �� ���������� �������� ��� ���
          //����������, �� �� ��� ������ ����������.
          //������ ���� Block
          if (CurLine = 'Block') then
          begin
            ReadLn(FFP, CurLine);
            CurLine := Trim(CurLine);
            if (CurLine = '{') then
            begin
              //�������� ������ ������� ���� � ������
              while true do
              begin
                ReadLn(FFP, CurLine);
                CurLine := Trim(CurLine);
                if (Pos('name = ',CurLine) = 1) then
                //���� ��� �������� �������, �� �������� ���... ��� ��������...
                begin
                  CurRazdel := Copy(CurLine,8,Length(CurLine)-7);
                end;
                if CurLine = '}' then
                  break;
                if (CurLine = 'Block') then
                begin
                  ReadLn(FFP,CurLine);
                  CurLine := Trim(CurLine);
                  if CurLine = '{' then
                  begin
                    while true do
                    begin
                      ReadLn(FFP,CurLine);
                      CurLine := Trim(CurLine);
                      if (Pos('name = ',CurLine) = 1) then
                      //���� ��� �������� �������, �� �������� ���... ��� ��������...
                      begin
                        CurBlock := Copy(CurLine,8,Length(CurLine)-7);
                      end;
                      if CurLine = '}' then
                        break;
                      //����� ��������� �����? ������!!!
                      if (CurLine = 'Entry') then
                      begin
                        CurTextLine := 0;
                        ReadLn(FFP, CurLine);
                        CurLine := Trim(CurLine);
                        if CurLine = '{' then
                        begin
                          CurTextLine := 1;
                          while true do
                          begin
                            ReadLn(FFP, CurLine);
                            CurLine := Trim(CurLine);
                            if CurLine = '}' then
                              break;
                            if (Pos('name = ',CurLine) = 1) then
                            begin
                              CurEnt.ename := Copy(CurLine,8,Length(CurLine)-7);
                            end;
                            if (Pos('url = ',CurLine) = 1) then
                            begin
                              CurEnt.eurl := Copy(CurLine,7,Length(CurLine)-6);
                            end;
                            if (Pos('executable = ',CurLine) = 1) then
                            begin
                              CurEnt.epath := Copy(CurLine,14,Length(CurLine)-13);
                            end;
                            if (Pos('textline = ',CurLine) = 1) then
                            begin
                              CurEnt.eabout[CurTextLine] := Copy(CurLine,12,Length(CurLine)-11);
                              Inc(CurTextLine);
                            end;
                            if (Pos('status = ',CurLine) = 1) then
                            begin
                              CurEnt.estatus := Copy(CurLine,10,Length(CurLine)-9);
                            end;
                            if (Pos('author = ',CurLine) = 1) then
                            begin
                              CurEnt.eauthor := Copy(CurLine,10,Length(CurLine)-9);
                            end;
                          end;
                          //���������� ���
                          //������ ���� ������� �� ��� ���������� � ��
                          REOut.Lines.Add(CurRazdel);
                          REOut.Lines.Add(' ');
                          REOut.Lines.Add(CurBlock);
                          REOut.Lines.Add(' ');
                          REOut.Lines.Add('['+CurEnt.ename+']');
                          REOut.Lines.Add(' ');
                          REOut.Lines.Add(CurEnt.estatus);
                          REOut.Lines.Add(' ');
                          REOut.Lines.Add(CurEnt.eauthor);
                          REOut.Lines.Add(' ');
                          REOut.Lines.Add(CurEnt.eurl);
                          REOut.Lines.Add(' ');
                          REOut.Lines.Add(CurEnt.epath);
                          REOut.Lines.Add(' ');
                          for i:= 1 to CurTextLine - 1 do
                            REOut.Lines.Add(CurEnt.eabout[i]);
                          REOut.Lines.Add(' ');
                          //����� ����������� ����
                          for i:= 1 to CurTextLine - 1 do
                            CurEnt.eabout[i] := '';
                          CurEnt.ename := '';
                          CurEnt.eurl := '';
                          CurEnt.epath := '';
                          CurEnt.estatus := '';
                          CurEnt.eauthor := '';
                        end;
                      end;
                    end;
                  end;
                end;//������� ������� ���� � ������
              end;
            end;
          end;
        end;//������� ������ ������� ����
      end;
    end;
  end;
end;
//�����-����� ����� ;-)
//������� ���� - ��, ��� ��� ������ ��������. :-)
end.
