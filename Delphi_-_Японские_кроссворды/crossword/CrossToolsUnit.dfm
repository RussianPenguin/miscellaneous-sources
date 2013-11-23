object CrossToolsForm: TCrossToolsForm
  Left = 204
  Top = 189
  BorderStyle = bsDialog
  Caption = 'Параметры'
  ClientHeight = 204
  ClientWidth = 453
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object BitBtn1: TBitBtn
    Left = 208
    Top = 168
    Width = 75
    Height = 25
    TabOrder = 0
    OnClick = BitBtn1Click
    Kind = bkOK
  end
  object BitBtn2: TBitBtn
    Left = 288
    Top = 168
    Width = 75
    Height = 25
    TabOrder = 1
    Kind = bkCancel
  end
  object BitBtn3: TBitBtn
    Left = 368
    Top = 168
    Width = 75
    Height = 25
    TabOrder = 2
    Kind = bkHelp
  end
  object ShowStartupNewCheckBox: TCheckBox
    Left = 16
    Top = 16
    Width = 209
    Height = 17
    Caption = 'Показывать выбор игры при старте'
    TabOrder = 3
  end
  object EmptyCheck: TCheckBox
    Left = 16
    Top = 40
    Width = 217
    Height = 17
    Caption = 'Помечать X пустые клетки'
    TabOrder = 4
  end
  object PlaySoundsCheck: TCheckBox
    Left = 248
    Top = 16
    Width = 97
    Height = 17
    Caption = 'Звуки'
    TabOrder = 5
  end
end
