unit U_main;

interface

uses
  SysUtils, Types, Classes, Variants, QTypes, QGraphics, QControls, QForms, 
  QDialogs, QStdCtrls, QButtons, U_Edit, xmldom, XMLIntf,
  {$IFDEF LINUX} xercesxmldom, {$ENDIF}
  {$IFDEF MSWINDOWS} msxmldom, {$ENDIF}
  XMLDoc;

type
  TMainForm = class(TForm)
    AlfList: TComboBox;
    Phones: TMemo;
    Address: TMemo;
    Fio: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    ElAddr: TLabel;
    AddInf: TMemo;
    Label6: TLabel;
    btAdd: TButton;
    btDel: TButton;
    btEdit: TButton;
    BitBtn1: TBitBtn;
    procedure btAddClick(Sender: TObject);
    procedure btEditClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure AlfListChange(Sender: TObject);
    procedure btDelClick(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
  private
    Procedure FillAlfList;
    { Private declarations }
  public
    { Public declarations }
  end;
TEdFlag = (New, Edit);
var
  MainForm: TMainForm;
  NewRec, CurrRec :IXMlNode;   //Узлы для представленяи новой и текущей записей
  EdFlag :TEdFlag; // Флаг редактирования или добавления записи
  recCounter:integer; //счетчик текущей записи
  NameList : TStrings; //Список имен
  LineBreak :string;  //Символ окончания строки

  XML:TXMLDocument;
implementation

 {$R *.xfm}

Procedure ShowRec (RecCounter :integer);
//Процедура отображения записи в текущем окне

var
tmpRec:IXMLNode;
    i:integer;
    AddrHref:string;
begin
  with MainForm do
  begin

 CurrRec := XML.DocumentElement.ChildNodes[RecCounter];
  Fio.Caption := CurrRec.ChildNodes['Name'].Text +' ' + CurrRec.ChildNodes['Occupation'].Text;
   tmpRec := CurrRec.ChildNodes['Phones'];
  Phones.Clear;
    for i:= 0 to TmpRec.ChildNodes.Count-1 do
      Phones.Lines.Add(TmpRec.ChildNodes[i].Text);
  tmpRec := CurrRec.ChildNodes['ElAddresses'];
  elAddr.Caption := '';
    for i:= 0 to TmpRec.ChildNodes.Count-1 do
    begin
     AddrHref := '<a href=';
      if pos('@', TmpRec.ChildNodes[i].Text)>0 then
     AddrHref := AddrHref+'mailto:';
     AddrHref := AddrHref+TmpRec.ChildNodes[i].Text +'>' +TmpRec.ChildNodes[i].Text +'</a>';
     ElAddr.Caption := ElAddr.Caption + AddrHref + LineBreak;
    end;
   Address.Clear;
   Address.Text := CurrRec.ChildNodes['PostAddress'].Text;
   AddInf.Clear;
   AddInf.Text := CurrRec.ChildNodes['AddInf'].Text;
  end;
end;


procedure TmainForm.FillAlfList;
//Процедура заполнения алфавитного списка имен

 var i:integer;
 tmpnode:IXMLNode;
begin
  NameList := TStringlist.Create;
   with  {MainForm.}XML.DocumentElement do
    For i:= 1 to ChildNodes.Count-1 do
      begin
      tmpNode := ChildNodes[i];
      nameList.Add(TmpNode.ChildNodes['Name'].Text);
      Mainform.AlfList.Items.Add(ChildNodes[i].ChildNodes['Name'].Text);
      end;
   end;

procedure TMainForm.btAddClick(Sender: TObject);
//Добавление записи
var edForm : TEditForm;
begin
  EdFlag := New;
  EditForm := TEditForm.Create(self);
  EditForm.ShowModal;
  ShowRec(RecCounter+1);
end;

procedure TMainForm.btEditClick(Sender: TObject);
//Редактирование записи
 var edForm : TEditForm;
begin
  EdFlag := Edit;
  EditForm := TEditForm.Create(self);
  EditForm.ShowModal;
  ShowRec(RecCounter+1);
  AlfList.Refresh;
end;

procedure TMainForm.FormCreate(Sender: TObject);
begin

{$IFDEF LINUX}
Application.Font.Name := 'cronyx-helvetica';
Application.Font.CharSet := fcsCP1251;
LineBreak := #10;
{$ENDIF}

{$IFDEF MSWINDOWS}
LineBreak := #10#13;
{$ENDIF}

XML:= TXMLDocument.Create(self);
XML.Active := true;
if fileExists('phonebook.xml') then
begin
recCounter := 1;
 XML.LoadFromFile('phonebook.xml');
  FillAlfList;
 AlfList.ItemIndex := 0;
 end;
end;

procedure TMainForm.AlfListChange(Sender: TObject);
//Отображение новой записи при выборе имени из списка
begin
if AlfList.ItemIndex >=0 then
begin
recCounter := NameList.IndexOf(AlfList.Items[AlFList.itemIndex]);
ShowRec(recCounter +1);
end;
end;

procedure TMainForm.btDelClick(Sender: TObject);
//Удаление записи
Var i:integer;
begin
   i:=AlfList.ItemIndex;
   XML.DocumentElement.DOMNode.removeChild(XML.DocumentElement.ChildNodes[RecCounter+1].DOMNode);
   XML.SaveToFile('phonebook.xml');
   NameList.Delete(NameList.IndexOf(AlfList.Items[i]));
   AlfList.Items.Delete(i);
   AlfList.ItemIndex := -1;
   AlfList.ItemIndex :=1;
   If RecCounter = 0 then inc(RecCounter)
   else
   dec(RecCounter);

   ShowRec(recCounter);

end;

procedure TMainForm.BitBtn1Click(Sender: TObject);
begin
 NameList.Free;
end;

end.
