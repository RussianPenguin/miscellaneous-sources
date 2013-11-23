object FTPGetForm: TFTPGetForm
  Left = 207
  Top = 159
  BorderStyle = bsDialog
  Caption = 'Загрузка новых игр'
  ClientHeight = 325
  ClientWidth = 492
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object LabelServ: TLabel
    Left = 72
    Top = 16
    Width = 37
    Height = 13
    Caption = 'Сервер'
  end
  object Label2: TLabel
    Left = 72
    Top = 40
    Width = 32
    Height = 13
    Caption = 'Папка'
  end
  object Label3: TLabel
    Left = 0
    Top = 72
    Width = 73
    Height = 13
    Caption = 'Пользователь'
  end
  object Label4: TLabel
    Left = 256
    Top = 72
    Width = 38
    Height = 13
    Caption = 'Пароль'
  end
  object Label1: TLabel
    Left = 8
    Top = 304
    Width = 3
    Height = 13
  end
  object GetFileName: TLabel
    Left = 208
    Top = 168
    Width = 3
    Height = 13
  end
  object UserID: TEdit
    Left = 120
    Top = 64
    Width = 121
    Height = 21
    TabOrder = 2
    Text = 'anonymous'
  end
  object Password: TEdit
    Left = 304
    Top = 64
    Width = 89
    Height = 21
    PasswordChar = '*'
    TabOrder = 3
  end
  object Host: TEdit
    Left = 120
    Top = 8
    Width = 121
    Height = 21
    TabOrder = 0
    Text = 'ls10'
  end
  object RemoteDir: TEdit
    Left = 120
    Top = 32
    Width = 273
    Height = 21
    TabOrder = 1
    Text = 'GAMES/JCROSWORD/UP_GAMES'
  end
  object Animate1: TAnimate
    Left = 8
    Top = 8
    Width = 48
    Height = 50
    Active = False
    CommonAVI = aviFindFile
    StopFrame = 23
  end
  object GetDirBtn: TButton
    Left = 408
    Top = 16
    Width = 75
    Height = 25
    Caption = 'Оглавление'
    TabOrder = 5
    OnClick = GetDirBtnClick
  end
  object ListBox1: TListBox
    Left = 8
    Top = 96
    Width = 185
    Height = 201
    ItemHeight = 13
    MultiSelect = True
    TabOrder = 6
  end
  object CheckBox1: TCheckBox
    Left = 272
    Top = 8
    Width = 97
    Height = 17
    Caption = 'Только новые'
    TabOrder = 4
  end
  object GetFilesBtn: TButton
    Left = 408
    Top = 168
    Width = 75
    Height = 25
    Caption = 'Получить'
    Enabled = False
    TabOrder = 7
    OnClick = GetFilesBtnClick
  end
  object BitBtn1: TBitBtn
    Left = 408
    Top = 264
    Width = 75
    Height = 25
    TabOrder = 9
    OnClick = BitBtn1Click
    Kind = bkCancel
  end
  object Animate2: TAnimate
    Left = 200
    Top = 96
    Width = 272
    Height = 60
    Active = False
    CommonAVI = aviCopyFile
    StopFrame = 26
  end
  object NMFTP1: TNMFTP
    Port = 21
    ReportLevel = 0
    OnDisconnect = NMFTP1Disconnect
    OnConnect = NMFTP1Connect
    UserID = 'anonymous'
    OnFailure = NMFTP1Failure
    OnSuccess = NMFTP1Success
    OnListItem = NMFTP1ListItem
    Vendor = 2411
    ParseList = False
    ProxyPort = 0
    Passive = False
    FirewallType = FTUser
    FWAuthenticate = False
    Left = 312
    Top = 104
  end
end
