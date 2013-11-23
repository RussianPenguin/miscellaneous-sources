object Form1: TForm1
  Left = 192
  Top = 107
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Тетрис'
  ClientHeight = 240
  ClientWidth = 318
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 224
    Top = 96
    Width = 65
    Height = 17
    AutoSize = False
    Caption = 'Очки: 0'
  end
  object Label2: TLabel
    Left = 208
    Top = 120
    Width = 89
    Height = 17
    AutoSize = False
    Caption = 'Скорость: 1'
  end
  object Label3: TLabel
    Left = 187
    Top = 200
    Width = 77
    Height = 17
    AutoSize = False
  end
  object Panel1: TPanel
    Left = 16
    Top = 16
    Width = 153
    Height = 217
    BevelInner = bvLowered
    TabOrder = 0
    object Image1: TImage
      Left = 13
      Top = 9
      Width = 124
      Height = 192
    end
  end
  object Panel2: TPanel
    Left = 200
    Top = 0
    Width = 89
    Height = 89
    BevelInner = bvLowered
    TabOrder = 1
    object Image2: TImage
      Left = 8
      Top = 8
      Width = 65
      Height = 73
    end
  end
  object MainMenu1: TMainMenu
    Left = 200
    Top = 152
    object mnuGame: TMenuItem
      Caption = '&Игра'
      object mnuNew: TMenuItem
        Caption = '&Новая'
        ShortCut = 113
        OnClick = mnuNewClick
      end
      object mnuS1: TMenuItem
        Caption = '-'
      end
      object mnuExit: TMenuItem
        Caption = 'Вы&ход'
        OnClick = mnuExitClick
      end
    end
    object mnuHelp: TMenuItem
      Caption = '&Справка'
      object mnuAbout: TMenuItem
        Caption = '&О программе'
        OnClick = mnuAboutClick
      end
    end
  end
  object Timer1: TTimer
    Interval = 500
    OnTimer = Timer1Timer
    Left = 264
    Top = 144
  end
end
