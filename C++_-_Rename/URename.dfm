object FRenameFiles: TFRenameFiles
  Left = 223
  Top = 89
  AutoSize = True
  BorderIcons = [biSystemMenu, biMinimize, biHelp]
  BorderStyle = bsSingle
  Caption = #1055#1077#1088#1077#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077
  ClientHeight = 457
  ClientWidth = 529
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object LPath: TLabel
    Left = 0
    Top = 8
    Width = 187
    Height = 13
    Caption = 'H:\Experiments\Projects\CPP\Rename'
  end
  object LStatus: TLabel
    Left = 0
    Top = 408
    Width = 529
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Caption = #1057#1090#1072#1090#1091#1089': '#1054#1078#1080#1076#1072#1085#1080#1077
  end
  object GBAddParam: TGroupBox
    Left = 208
    Top = 320
    Width = 321
    Height = 81
    Caption = #1044#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1099#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099' '#1087#1077#1088#1077#1080#1084#1077#1085#1086#1074#1072#1085#1080#1103
    TabOrder = 0
    object CBCreateBack: TCheckBox
      Left = 8
      Top = 48
      Width = 145
      Height = 17
      Caption = #1057#1086#1079#1076#1072#1074#1072#1090#1100' '#1092#1072#1081#1083' '#1086#1090#1082#1072#1090#1072
      TabOrder = 0
    end
    object CBSubFolders: TCheckBox
      Left = 8
      Top = 24
      Width = 233
      Height = 17
      Caption = #1048#1089#1082#1072#1090#1100' '#1074' '#1087#1086#1076#1082#1072#1090#1072#1083#1086#1075#1072#1093
      Checked = True
      State = cbChecked
      TabOrder = 1
    end
  end
  object GBParams: TGroupBox
    Left = 208
    Top = 0
    Width = 321
    Height = 321
    Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099
    TabOrder = 1
    object RGTypeOfRename: TRadioGroup
      Left = 16
      Top = 16
      Width = 289
      Height = 97
      TabOrder = 0
    end
    object RBFromFile: TRadioButton
      Left = 32
      Top = 32
      Width = 193
      Height = 17
      Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100' '#1092#1072#1081#1083' '#1089' '#1080#1084#1077#1085#1072#1084#1080
      Enabled = False
      TabOrder = 1
      OnClick = RBFromFileClick
    end
    object RBFromParams: TRadioButton
      Left = 32
      Top = 88
      Width = 217
      Height = 17
      Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100' '#1091#1082#1072#1079#1072#1085#1085#1099#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099
      Checked = True
      TabOrder = 2
      TabStop = True
      OnClick = RBFromParamsClick
    end
    object EFileOfNames: TEdit
      Left = 32
      Top = 56
      Width = 145
      Height = 21
      Enabled = False
      TabOrder = 3
    end
    object BFileOfNames: TButton
      Left = 200
      Top = 56
      Width = 89
      Height = 25
      Caption = #1059#1082#1072#1079#1072#1090#1100' '#1092#1072#1081#1083
      Enabled = False
      TabOrder = 4
      OnClick = BFileOfNamesClick
    end
    object CBTranslit: TCheckBox
      Left = 8
      Top = 120
      Width = 113
      Height = 17
      Caption = #1058#1088#1072#1085#1089#1083#1080#1090#1077#1088#1072#1094#1080#1103
      TabOrder = 5
    end
    object CBRenameSubF: TCheckBox
      Left = 120
      Top = 120
      Width = 185
      Height = 17
      Caption = #1055#1077#1088#1077#1080#1084#1077#1085#1086#1074#1099#1074#1072#1090#1100' '#1087#1086#1076#1082#1072#1090#1072#1083#1086#1075#1080
      TabOrder = 6
    end
    object CBUseNumb: TCheckBox
      Left = 8
      Top = 144
      Width = 241
      Height = 17
      Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100' '#1095#1080#1089#1083#1086#1074#1099#1077' '#1080#1084#1077#1085#1072' '#1085#1072#1095#1080#1085#1072#1103' '#1089':'
      TabOrder = 7
      OnClick = CBUseNumbClick
    end
    object CSENumber: TCSpinEdit
      Left = 248
      Top = 136
      Width = 57
      Height = 22
      Enabled = False
      TabOrder = 8
    end
    object CBUsePrefix: TCheckBox
      Left = 8
      Top = 168
      Width = 193
      Height = 17
      Caption = #1053#1072#1095#1080#1085#1072#1090#1100' '#1080#1084#1103' '#1092#1072#1081#1083#1072' '#1089' '#1087#1088#1077#1092#1080#1082#1089#1072':'
      TabOrder = 9
      OnClick = CBUsePrefixClick
    end
    object EPrefix: TEdit
      Left = 208
      Top = 160
      Width = 97
      Height = 21
      Enabled = False
      TabOrder = 10
    end
    object CBUseRegisters: TCheckBox
      Left = 8
      Top = 240
      Width = 281
      Height = 17
      Caption = #1055#1088#1080#1074#1077#1089#1090#1080' '#1080#1084#1077#1085#1072' '#1082' '#1074#1077#1088#1093#1085#1077#1084#1091'/'#1085#1080#1078#1085#1077#1084#1091' '#1088#1077#1075#1080#1089#1090#1088#1091
      TabOrder = 11
      OnClick = CBUseRegistersClick
    end
    object CBRemoveSpace: TCheckBox
      Left = 8
      Top = 192
      Width = 137
      Height = 17
      Caption = #1047#1072#1084#1077#1085#1103#1090#1100' '#1087#1088#1086#1073#1077#1083' '#1085#1072':'
      TabOrder = 12
      OnClick = CBRemoveSpaceClick
    end
    object ESpaceAlternative: TEdit
      Left = 144
      Top = 184
      Width = 161
      Height = 21
      Enabled = False
      TabOrder = 13
    end
    object CBNotUseExt: TCheckBox
      Left = 8
      Top = 216
      Width = 145
      Height = 17
      Caption = #1054#1089#1090#1072#1074#1083#1103#1090#1100' '#1088#1072#1089#1096#1080#1088#1077#1085#1080#1103
      Checked = True
      Ctl3D = True
      ParentCtl3D = False
      State = cbChecked
      TabOrder = 14
    end
  end
  object FilesBox: TFileListBox
    Left = 0
    Top = 272
    Width = 201
    Height = 129
    FileType = [ftReadOnly, ftHidden, ftSystem, ftVolumeID, ftDirectory, ftArchive, ftNormal]
    ItemHeight = 13
    TabOrder = 2
  end
  object TreeOfFolders: TDirectoryListBox
    Left = 0
    Top = 32
    Width = 201
    Height = 209
    DirLabel = LPath
    FileList = FilesBox
    ItemHeight = 16
    TabOrder = 3
  end
  object Drives: TDriveComboBox
    Left = 0
    Top = 248
    Width = 201
    Height = 19
    TabOrder = 4
    OnChange = DrivesChange
  end
  object BOK: TButton
    Left = 135
    Top = 432
    Width = 107
    Height = 25
    Caption = #1055#1077#1088#1077#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077
    TabOrder = 5
    OnClick = BOKClick
  end
  object BCancel: TButton
    Left = 287
    Top = 432
    Width = 107
    Height = 25
    Caption = #1054#1090#1082#1072#1090
    Enabled = False
    TabOrder = 6
  end
  object RGRegister: TRadioGroup
    Left = 224
    Top = 264
    Width = 289
    Height = 41
    Caption = #1056#1077#1075#1080#1089#1090#1088
    TabOrder = 7
  end
  object RBHight: TRadioButton
    Left = 384
    Top = 280
    Width = 113
    Height = 17
    Caption = #1042#1077#1088#1093#1085#1080#1081
    Enabled = False
    TabOrder = 8
  end
  object RBLow: TRadioButton
    Left = 232
    Top = 280
    Width = 113
    Height = 17
    Caption = #1053#1080#1078#1085#1080#1081
    Checked = True
    Enabled = False
    TabOrder = 9
    TabStop = True
  end
  object OpenDialog1: TOpenDialog
    FileName = 'E:\Experiments\Projects\CPP\Rename\URename.ddp'
    Filter = 'All Files(*.*)|*.*'
    Left = 496
    Top = 424
  end
end
