object Form1: TForm1
  Left = 188
  Top = 141
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'a*x*x + b*x + c = 0'
  ClientHeight = 260
  ClientWidth = 504
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
    Left = 45
    Top = 5
    Width = 432
    Height = 20
    Caption = 'Программа для решения квадратных уравненений'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 136
    Top = 29
    Width = 44
    Height = 20
    Caption = 'x*x + '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 304
    Top = 29
    Width = 29
    Height = 20
    Caption = 'x + '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 456
    Top = 29
    Width = 31
    Height = 20
    Caption = ' = 0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label5: TLabel
    Left = 16
    Top = 68
    Width = 19
    Height = 20
    Caption = '1x'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label6: TLabel
    Left = 16
    Top = 141
    Width = 19
    Height = 20
    Caption = '2x'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Edit1: TEdit
    Left = 16
    Top = 29
    Width = 121
    Height = 21
    Hint = 'Число "a"'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
  end
  object Edit2: TEdit
    Left = 184
    Top = 29
    Width = 121
    Height = 21
    Hint = 'Число "b"'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
  end
  object Edit3: TEdit
    Left = 336
    Top = 29
    Width = 121
    Height = 21
    Hint = 'Число "c"'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
  end
  object Panel1: TPanel
    Left = 16
    Top = 93
    Width = 473
    Height = 40
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
  end
  object Panel2: TPanel
    Left = 16
    Top = 165
    Width = 473
    Height = 41
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
  end
  object Button1: TButton
    Left = 215
    Top = 222
    Width = 75
    Height = 26
    Hint = 'Щёлкните для решения вашего уравнения'
    Caption = 'Рассчёт'
    Default = True
    ParentShowHint = False
    ShowHint = True
    TabOrder = 5
    OnClick = Button1Click
  end
end
