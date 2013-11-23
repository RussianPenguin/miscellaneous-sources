object Author: TAuthor
  Left = 413
  Top = 134
  BorderStyle = bsToolWindow
  Caption = 'Об авторе'
  ClientHeight = 175
  ClientWidth = 206
  Color = clAqua
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 120
    Width = 182
    Height = 20
    Cursor = crHandPoint
    Caption = 'cooluser@ngs.ru (с) 2002'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = Label1Click
  end
  object Memo1: TMemo
    Left = 16
    Top = 16
    Width = 185
    Height = 105
    Color = clAqua
    Lines.Strings = (
      'Автор программы - Маслов '
      'Вячеслав.'
      ''
      'Если у Вас есть '
      'какие-либо предложения или '
      'замечания, то напишите письмо '
      'по адресу cooluser@ngs.ru')
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Button1: TButton
    Left = 72
    Top = 152
    Width = 65
    Height = 17
    Caption = 'Хорошо'
    TabOrder = 1
    OnClick = Button1Click
  end
end
