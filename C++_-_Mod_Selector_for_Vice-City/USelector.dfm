object Form1: TForm1
  Left = 192
  Top = 113
  Width = 488
  Height = 375
  Caption = 'Mod Selector for GTA_III Vice-City'
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
  object Label1: TLabel
    Left = 201
    Top = 48
    Width = 79
    Height = 13
    Caption = #1054#1087#1080#1089#1072#1085#1080#1077' '#1084#1086#1076#1072
  end
  object Label2: TLabel
    Left = 13
    Top = 16
    Width = 107
    Height = 13
    Caption = #1059#1089#1090#1072#1085#1086#1074#1083#1077#1085#1085#1099#1081' '#1084#1086#1076':'
  end
  object LLast: TLabel
    Left = 10
    Top = 296
    Width = 3
    Height = 13
    Align = alCustom
    Alignment = taCenter
  end
  object CBMods: TComboBox
    Left = 128
    Top = 16
    Width = 345
    Height = 21
    ItemHeight = 13
    TabOrder = 0
    OnChange = CBModsChange
  end
  object REAbout: TRichEdit
    Left = 8
    Top = 72
    Width = 465
    Height = 209
    HideScrollBars = False
    ScrollBars = ssVertical
    TabOrder = 1
  end
  object BApply: TButton
    Left = 181
    Top = 312
    Width = 118
    Height = 25
    Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1084#1086#1076
    TabOrder = 2
    OnClick = BApplyClick
  end
end
