object FEditPath: TFEditPath
  Left = 192
  Top = 107
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'Edit Path String'
  ClientHeight = 63
  ClientWidth = 467
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object BUpdate: TButton
    Left = 304
    Top = 32
    Width = 75
    Height = 25
    Caption = 'Update'
    TabOrder = 0
    OnClick = BUpdateClick
  end
  object BAddDir: TButton
    Left = 224
    Top = 32
    Width = 75
    Height = 25
    Caption = 'Add Directory'
    TabOrder = 1
    OnClick = BAddDirClick
  end
  object ECurPath: TEdit
    Left = 0
    Top = 8
    Width = 465
    Height = 21
    TabOrder = 2
  end
  object BApply: TButton
    Left = 384
    Top = 32
    Width = 75
    Height = 25
    Caption = 'Apply'
    TabOrder = 3
    OnClick = BApplyClick
  end
end
