object GroupConvForm: TGroupConvForm
  Left = 245
  Top = 128
  Width = 464
  Height = 418
  Caption = 'Групповое преобразование формата'
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
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 49
    Height = 13
    Caption = 'Исходное'
  end
  object Label2: TLabel
    Left = 296
    Top = 8
    Width = 48
    Height = 13
    Caption = 'Конечное'
  end
  object SourseListBox: TFileListBox
    Left = 8
    Top = 144
    Width = 145
    Height = 193
    ItemHeight = 13
    Mask = '*.jcw'
    MultiSelect = True
    TabOrder = 0
  end
  object FilterComboBox1: TFilterComboBox
    Left = 8
    Top = 344
    Width = 145
    Height = 21
    FileList = SourseListBox
    Filter = 'Файлы решений JCW|*.jcw'
    TabOrder = 1
  end
  object DirectoryListBox1: TDirectoryListBox
    Left = 8
    Top = 48
    Width = 145
    Height = 89
    FileList = SourseListBox
    ItemHeight = 16
    TabOrder = 2
  end
  object DirectoryListBox2: TDirectoryListBox
    Left = 296
    Top = 48
    Width = 145
    Height = 89
    FileList = DestFileListBox
    ItemHeight = 16
    TabOrder = 3
  end
  object DriveComboBox1: TDriveComboBox
    Left = 8
    Top = 24
    Width = 145
    Height = 19
    DirList = DirectoryListBox1
    TabOrder = 4
  end
  object DriveComboBox2: TDriveComboBox
    Left = 296
    Top = 24
    Width = 145
    Height = 19
    DirList = DirectoryListBox2
    TabOrder = 5
  end
  object DestFileListBox: TFileListBox
    Left = 296
    Top = 144
    Width = 145
    Height = 193
    Enabled = False
    ItemHeight = 13
    Mask = '*.cwg'
    TabOrder = 6
  end
  object FilterComboBox2: TFilterComboBox
    Left = 296
    Top = 344
    Width = 145
    Height = 21
    FileList = DestFileListBox
    Filter = 'Файлы япоского кросворда|*.cwg'
    TabOrder = 7
  end
  object ProgressBar1: TProgressBar
    Left = 0
    Top = 375
    Width = 456
    Height = 16
    Align = alBottom
    Min = 0
    Max = 100
    TabOrder = 8
  end
  object BitBtn1: TBitBtn
    Left = 168
    Top = 48
    Width = 113
    Height = 25
    Caption = 'Преобразовать'
    TabOrder = 9
    OnClick = BitBtn1Click
    Kind = bkOK
  end
  object BitBtn2: TBitBtn
    Left = 168
    Top = 80
    Width = 113
    Height = 25
    Caption = '&Преобр. все'
    TabOrder = 10
    OnClick = BitBtn2Click
    Kind = bkAll
  end
  object BitBtn3: TBitBtn
    Left = 168
    Top = 112
    Width = 113
    Height = 25
    Caption = 'Параметры'
    Enabled = False
    TabOrder = 11
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00555550FF0559
      1950555FF75F7557F7F757000FF055591903557775F75557F77570FFFF055559
      1933575FF57F5557F7FF0F00FF05555919337F775F7F5557F7F700550F055559
      193577557F7F55F7577F07550F0555999995755575755F7FFF7F5570F0755011
      11155557F755F777777555000755033305555577755F75F77F55555555503335
      0555555FF5F75F757F5555005503335505555577FF75F7557F55505050333555
      05555757F75F75557F5505000333555505557F777FF755557F55000000355557
      07557777777F55557F5555000005555707555577777FF5557F55553000075557
      0755557F7777FFF5755555335000005555555577577777555555}
    NumGlyphs = 2
  end
  object BitBtn4: TBitBtn
    Left = 168
    Top = 304
    Width = 113
    Height = 25
    TabOrder = 12
    Kind = bkCancel
  end
  object BitBtn5: TBitBtn
    Left = 168
    Top = 336
    Width = 113
    Height = 25
    TabOrder = 13
    Kind = bkHelp
  end
  object ReplaseExists: TCheckBox
    Left = 168
    Top = 152
    Width = 121
    Height = 17
    Caption = 'Замещать существ.'
    TabOrder = 14
  end
end
