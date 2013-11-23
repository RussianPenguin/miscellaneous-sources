object CrossOptForm: TCrossOptForm
  Left = 248
  Top = 160
  BorderStyle = bsDialog
  Caption = 'Параметры'
  ClientHeight = 271
  ClientWidth = 453
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
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 453
    Height = 233
    ActivePage = TabSheet3
    Align = alTop
    TabOrder = 3
    object TabSheet1: TTabSheet
      Caption = 'Общие'
      object Label3: TLabel
        Left = 8
        Top = 144
        Width = 30
        Height = 13
        Caption = 'Автор'
      end
      object Label4: TLabel
        Left = 8
        Top = 176
        Width = 50
        Height = 13
        Caption = 'Название'
      end
      object GroupBox1: TGroupBox
        Left = 8
        Top = 8
        Width = 169
        Height = 89
        Caption = 'Размер сетки'
        TabOrder = 0
        object Label1: TLabel
          Left = 16
          Top = 24
          Width = 79
          Height = 13
          Caption = 'по горизонтале'
        end
        object Label2: TLabel
          Left = 16
          Top = 56
          Width = 68
          Height = 13
          Caption = 'по вертикале'
        end
        object SizeX: TSpinEdit
          Left = 104
          Top = 16
          Width = 57
          Height = 22
          MaxValue = 500
          MinValue = 2
          TabOrder = 0
          Value = 10
        end
        object SizeY: TSpinEdit
          Left = 104
          Top = 48
          Width = 57
          Height = 22
          MaxValue = 500
          MinValue = 2
          TabOrder = 1
          Value = 10
        end
      end
      object GameAutor: TEdit
        Left = 72
        Top = 136
        Width = 367
        Height = 21
        TabOrder = 1
      end
      object GameName: TEdit
        Left = 70
        Top = 168
        Width = 371
        Height = 21
        TabOrder = 2
      end
      object Difficult: TRadioGroup
        Left = 252
        Top = 8
        Width = 161
        Height = 89
        Caption = 'Сложность'
        Items.Strings = (
          'Легко'
          'Средне'
          'Сложно'
          'Невыполнимо')
        TabOrder = 3
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Отображение'
      ImageIndex = 2
      object Label5: TLabel
        Left = 16
        Top = 8
        Width = 34
        Height = 13
        Caption = 'Шрифт'
      end
      object Label6: TLabel
        Left = 16
        Top = 32
        Width = 81
        Height = 13
        Caption = 'Размер шрифта'
      end
      object Label7: TLabel
        Left = 16
        Top = 56
        Width = 77
        Height = 13
        Caption = 'Размер ячейки'
      end
      object GroupBox2: TGroupBox
        Left = 8
        Top = 76
        Width = 433
        Height = 121
        Caption = 'Цвета'
        TabOrder = 0
        object Label8: TLabel
          Left = 8
          Top = 24
          Width = 23
          Height = 13
          Caption = 'Фон'
        end
        object Label10: TLabel
          Left = 8
          Top = 48
          Width = 74
          Height = 13
          Caption = 'Непровереная'
        end
        object Label11: TLabel
          Left = 232
          Top = 24
          Width = 56
          Height = 13
          Caption = 'Отмечаная'
        end
        object Label12: TLabel
          Left = 232
          Top = 48
          Width = 36
          Height = 13
          Caption = 'Пустая'
        end
        object Label9: TLabel
          Left = 232
          Top = 72
          Width = 36
          Height = 13
          Caption = 'Цифры'
        end
        object Label13: TLabel
          Left = 8
          Top = 72
          Width = 66
          Height = 13
          Caption = 'Разделитель'
        end
        object Label14: TLabel
          Left = 8
          Top = 96
          Width = 74
          Height = 13
          Caption = 'Неопределено'
        end
        object BackgroundColor: TColorComboBox
          Left = 88
          Top = 16
          Width = 129
          Height = 22
          TabOrder = 0
        end
        object UnchekedColor: TColorComboBox
          Left = 88
          Top = 40
          Width = 129
          Height = 22
          TabOrder = 2
        end
        object ChekedColor: TColorComboBox
          Left = 296
          Top = 16
          Width = 129
          Height = 22
          TabOrder = 1
        end
        object EmptyColor: TColorComboBox
          Left = 296
          Top = 40
          Width = 129
          Height = 22
          TabOrder = 3
        end
        object NumberColor: TColorComboBox
          Left = 296
          Top = 64
          Width = 129
          Height = 22
          TabOrder = 5
        end
        object SplitColor: TColorComboBox
          Left = 88
          Top = 64
          Width = 129
          Height = 22
          TabOrder = 4
        end
        object UnknowColor: TColorComboBox
          Left = 88
          Top = 88
          Width = 129
          Height = 22
          TabOrder = 6
        end
      end
      object FontComboBox1: TFontComboBox
        Left = 56
        Top = 0
        Width = 209
        Height = 20
        TabOrder = 1
      end
      object FontSize: TSpinEdit
        Left = 168
        Top = 24
        Width = 97
        Height = 22
        MaxValue = 0
        MinValue = 0
        TabOrder = 2
        Value = 0
      end
      object GridSize: TSpinEdit
        Left = 168
        Top = 48
        Width = 97
        Height = 22
        MaxValue = 0
        MinValue = 0
        TabOrder = 3
        Value = 0
      end
      object CheckBox1: TCheckBox
        Left = 280
        Top = 24
        Width = 97
        Height = 17
        Caption = 'Музыка'
        TabOrder = 4
        OnClick = CheckBox1Click
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Цветной кросворд'
      ImageIndex = 3
      object GroupBox3: TGroupBox
        Left = 8
        Top = 8
        Width = 425
        Height = 145
        Caption = 'Цвета'
        TabOrder = 0
        object Label15: TLabel
          Left = 16
          Top = 24
          Width = 34
          Height = 13
          Caption = 'Цвет 1'
        end
        object Label16: TLabel
          Left = 240
          Top = 24
          Width = 34
          Height = 13
          Caption = 'Цвет 2'
        end
        object Label17: TLabel
          Left = 16
          Top = 56
          Width = 34
          Height = 13
          Caption = 'Цвет 3'
        end
        object Label18: TLabel
          Left = 240
          Top = 56
          Width = 34
          Height = 13
          Caption = 'Цвет 4'
        end
        object Label19: TLabel
          Left = 16
          Top = 88
          Width = 34
          Height = 13
          Caption = 'Цвет 5'
        end
        object Label20: TLabel
          Left = 240
          Top = 88
          Width = 34
          Height = 13
          Caption = 'Цвет 6'
        end
        object Label21: TLabel
          Left = 16
          Top = 120
          Width = 34
          Height = 13
          Caption = 'Цвет 7'
        end
        object Label22: TLabel
          Left = 240
          Top = 120
          Width = 34
          Height = 13
          Caption = 'Цвет 8'
        end
        object Color1: TColorComboBox
          Left = 64
          Top = 16
          Width = 121
          Height = 22
          TabOrder = 0
        end
        object Color2: TColorComboBox
          Left = 288
          Top = 16
          Width = 121
          Height = 22
          TabOrder = 1
        end
        object Color3: TColorComboBox
          Left = 64
          Top = 48
          Width = 121
          Height = 22
          TabOrder = 2
        end
        object Color4: TColorComboBox
          Left = 288
          Top = 48
          Width = 121
          Height = 22
          TabOrder = 3
        end
        object Color5: TColorComboBox
          Left = 64
          Top = 80
          Width = 121
          Height = 22
          TabOrder = 4
        end
        object Color6: TColorComboBox
          Left = 288
          Top = 80
          Width = 121
          Height = 22
          TabOrder = 5
        end
        object Color7: TColorComboBox
          Left = 64
          Top = 112
          Width = 121
          Height = 22
          TabOrder = 6
        end
        object Color8: TColorComboBox
          Left = 288
          Top = 112
          Width = 121
          Height = 22
          TabOrder = 7
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Описание'
      ImageIndex = 1
      object GameDescription: TMemo
        Left = 0
        Top = 0
        Width = 445
        Height = 205
        Align = alClient
        TabOrder = 0
      end
    end
  end
  object OkBtn: TBitBtn
    Left = 208
    Top = 240
    Width = 75
    Height = 25
    TabOrder = 0
    OnClick = OkBtnClick
    Kind = bkOK
  end
  object BitBtn2: TBitBtn
    Left = 288
    Top = 240
    Width = 75
    Height = 25
    TabOrder = 1
    Kind = bkCancel
  end
  object BitBtn3: TBitBtn
    Left = 368
    Top = 240
    Width = 75
    Height = 25
    TabOrder = 2
    Kind = bkHelp
  end
  object FormStorage1: TFormStorage
    StoredProps.Strings = (
      'PageControl1.ActivePage')
    StoredValues = <>
    Left = 400
    Top = 8
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = 'mid'
    Filter = 'MIDI файлы|*.mid;*.midi;*.rmi'
    Left = 364
    Top = 8
  end
end
