object Form1: TForm1
  Left = 268
  Top = 155
  Width = 457
  Height = 475
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object EFile: TEdit
    Left = 8
    Top = 8
    Width = 265
    Height = 21
    TabOrder = 0
  end
  object BOpen: TButton
    Left = 280
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Open'
    TabOrder = 1
    OnClick = BOpenClick
  end
  object BStart: TButton
    Left = 360
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Start'
    TabOrder = 2
    OnClick = BStartClick
  end
  object REOut: TRichEdit
    Left = 8
    Top = 40
    Width = 433
    Height = 401
    ScrollBars = ssBoth
    TabOrder = 3
  end
  object ODFile: TOpenDialog
    Left = 192
    Top = 48
  end
end
