object FTPSendForm: TFTPSendForm
  Left = 248
  Top = 163
  BorderStyle = bsDialog
  Caption = 'FTPSendForm'
  ClientHeight = 203
  ClientWidth = 467
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 168
    Width = 3
    Height = 13
  end
  object Label2: TLabel
    Left = 8
    Top = 136
    Width = 96
    Height = 13
    Caption = 'Имя пользователя'
  end
  object Label3: TLabel
    Left = 8
    Top = 88
    Width = 82
    Height = 13
    Caption = 'Игровой сервер'
  end
  object Label4: TLabel
    Left = 8
    Top = 112
    Width = 84
    Height = 13
    Caption = 'Путь на сервере'
  end
  object Label5: TLabel
    Left = 264
    Top = 136
    Width = 38
    Height = 13
    Caption = 'Пароль'
  end
  object OkBtn: TBitBtn
    Left = 224
    Top = 168
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    TabOrder = 0
    OnClick = OkBtnClick
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      3333333333333333333333330000333333333333333333333333F33333333333
      00003333344333333333333333388F3333333333000033334224333333333333
      338338F3333333330000333422224333333333333833338F3333333300003342
      222224333333333383333338F3333333000034222A22224333333338F338F333
      8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
      33333338F83338F338F33333000033A33333A222433333338333338F338F3333
      0000333333333A222433333333333338F338F33300003333333333A222433333
      333333338F338F33000033333333333A222433333333333338F338F300003333
      33333333A222433333333333338F338F00003333333333333A22433333333333
      3338F38F000033333333333333A223333333333333338F830000333333333333
      333A333333333333333338330000333333333333333333333333333333333333
      0000}
    NumGlyphs = 2
  end
  object CancelBtn: TBitBtn
    Left = 304
    Top = 168
    Width = 75
    Height = 25
    TabOrder = 1
    OnClick = CancelBtnClick
    Kind = bkCancel
  end
  object BitBtn3: TBitBtn
    Left = 384
    Top = 168
    Width = 75
    Height = 25
    Caption = 'BitBtn3'
    TabOrder = 2
  end
  object Animate1: TAnimate
    Left = 96
    Top = 8
    Width = 272
    Height = 60
    Active = False
    CommonAVI = aviCopyFile
    StartFrame = 5
    StopFrame = 26
  end
  object Edit1: TEdit
    Left = 112
    Top = 80
    Width = 345
    Height = 21
    TabOrder = 4
    Text = 'ls10'
  end
  object Edit2: TEdit
    Left = 112
    Top = 104
    Width = 345
    Height = 21
    TabOrder = 5
    Text = 'GAMES/JCROSWORD/UP_GAMES'
  end
  object UserID: TEdit
    Left = 112
    Top = 128
    Width = 121
    Height = 21
    TabOrder = 6
    Text = 'anonymous'
  end
  object Edit4: TEdit
    Left = 336
    Top = 128
    Width = 121
    Height = 21
    PasswordChar = '*'
    TabOrder = 7
  end
  object NMFTP1: TNMFTP
    Port = 21
    ReportLevel = 0
    OnConnect = NMFTP1Connect
    UserID = 'anonymous'
    OnFailure = NMFTP1Failure
    OnSuccess = NMFTP1Success
    Vendor = 2411
    ParseList = False
    ProxyPort = 0
    Passive = False
    FirewallType = FTUser
    FWAuthenticate = False
    Left = 424
    Top = 8
  end
end
