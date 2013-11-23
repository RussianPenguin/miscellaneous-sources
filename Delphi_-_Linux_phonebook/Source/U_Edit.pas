unit U_Edit;

interface

uses
  SysUtils, Types, Classes, Variants, QTypes, QGraphics, QControls, QForms, 
  QDialogs, QStdCtrls, QButtons, xmldom, XMLIntf,
  {$IFDEF LINUX} xercesxmldom, {$ENDIF}
  {$IFDEF MSWINDOWS} msxmldom, {$ENDIF}
  XMLDoc;

type
  TEditForm = class(TForm)
    edFio: TEdit;
    edOccupation: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    edPhones: TEdit;
    Label3: TLabel;
    btPhAdd: TButton;
    btPhDel: TButton;
    edElAddress: TEdit;
    Label4: TLabel;
    btElAdd: TButton;
    btElDel: TButton;
    Label5: TLabel;
    mePostAddress: TMemo;
    Label6: TLabel;
    meAddInf: TMemo;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    lbPhones: TListBox;
    lbElAddress: TListBox;
    procedure btPhAddClick(Sender: TObject);
    procedure btElAddClick(Sender: TObject);
    procedure btPhDelClick(Sender: TObject);
    procedure btElDelClick(Sender: TObject);
    procedure btPhEdClick(Sender: TObject);
    procedure btElEdClick(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  EditForm: TEditForm;

implementation
{$R *.xfm}

uses U_main;

procedure TEditForm.btPhAddClick(Sender: TObject);
begin
 If edPhones.Text <> '' then
  lbPhones.Items.Add(edPhones.Text);
 edPhones.Text := '';
end;

procedure TEditForm.btElAddClick(Sender: TObject);
begin
 If EdElAddress.Text <> '' then
  lbElAddress.Items.Add(EdElAddress.Text);
 EdElAddress.Text := '';
end;

procedure TEditForm.btPhDelClick(Sender: TObject);
begin
 lbPhones.Items.Delete(lbPhones.ItemIndex);
end;

procedure TEditForm.btElDelClick(Sender: TObject);
begin
  lbElAddress.Items.Delete(lbElAddress.ItemIndex);
end;

procedure TEditForm.btPhEdClick(Sender: TObject);
begin
 if lbPhones.ItemIndex >= 0 then
  edphones.Text := lbPhones.Items[lbPhones.ItemIndex];

end;

procedure TEditForm.btElEdClick(Sender: TObject);
begin
 if lbElAddress.ItemIndex >= 0 then
  edElAddress.Text := lbElAddress.Items[lbElAddress.ItemIndex];
end;

procedure TEditForm.BitBtn2Click(Sender: TObject);
var TmpRec : IXMLNode;
i:integer;
begin
 if EdFlag = Edit then
   begin
  // если редактирование записи
    MainForm.AlfList.Items.Delete(MainForm.AlfList.ItemIndex);
    MainForm.AlfList.Refresh;
    NameList.Delete(NameList.IndexOf(CurrRec.ChildNodes['Name'].Text));
    XML.DocumentElement.DOMNode.removeChild(CurrRec.DOMNode);
  end
  else
    //если добавление записи
    inc(RecCounter);

   NewRec:= XML.DocumentElement.AddChild('record');

       Newrec.AddChild('Name');
     Newrec.AddChild('Occupation');

  Newrec.ChildNodes.Nodes['Name'].Text := edFio.Text;

  Newrec.ChildNodes.Nodes['Occupation'].Text := edOccupation.Text;

   tmpRec:=NewRec.AddChild('Phones');
    for i:= 0 to lbPhones.Items.Count-1 do
     begin
      tmpRec.AddChild('phone');
      tmpRec.ChildNodes[i].Text := lbPhones.Items[i];
     end;
   tmpRec:=NewRec.AddChild('ElAddresses');
    for i:= 0 to lbElAddress.Items.Count-1 do
     begin
      tmpRec.AddChild('ElAddress');
      tmpRec.ChildNodes[i].Text := lbElAddress.Items[i];
     end;
   Newrec.AddChild('PostAddress');
   NewRec.ChildNodes['PostAddress'].Text := mePostAddress.Text;
   Newrec.AddChild('AddInf');
   NewRec.ChildNodes['AddInf'].Text := meAddInf.Text;

   XML.SaveToFile('phonebook.xml');
   XML.LoadFromFile('phonebook.xml');
  CurrRec := XML.DocumentElement.ChildNodes.Last;//[recCounter+1];
  nameList.Add(CurrRec.ChildNodes['Name'].Text);

  MainForm.AlfList.Items.Add(nameList[NameList.count-1]);
  MainForm.AlfList.ItemIndex := -1;
  MainForm.AlfList.ItemIndex := MainForm.AlfList.Items.IndexOf(nameList[nameList.Count-1]);

end;

procedure TEditForm.FormCreate(Sender: TObject);
var
 i:integer;
 tmpRec : IXMLNode;
begin
   If EdFlag = Edit then
   begin
     edFio.Text := CurrRec.ChildNodes['Name'].Text;
     edOccupation.Text := CurrRec.ChildNodes['Occupation'].Text;
     mePostAddress.Text := CurrRec.ChildNodes['PostAddress'].Text;
     meAddInf.Text := CurrRec.ChildNodes['AddInf'].Text;
       tmpRec := CurrRec.ChildNodes['Phones'];
        For i:= 0 to tmprec.ChildNodes.Count - 1 do
          lbPhones.Items.Add(tmpRec.ChildNodes[i].Text);
       tmpRec := CurrRec.ChildNodes['ElAddresses'];
        For i:= 0 to tmprec.ChildNodes.Count - 1 do
          lbElAddress.Items.Add(tmpRec.ChildNodes[i].Text);

   end;
end;

end.
