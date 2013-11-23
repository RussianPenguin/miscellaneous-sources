object CrossRulesForm: TCrossRulesForm
  Left = 243
  Top = 123
  BorderStyle = bsDialog
  Caption = 'Правила заполнения простого кросворда'
  ClientHeight = 298
  ClientWidth = 443
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object BitBtn1: TBitBtn
    Left = 360
    Top = 16
    Width = 75
    Height = 25
    TabOrder = 0
    Kind = bkOK
  end
  object Memo1: TMemo
    Left = 0
    Top = 0
    Width = 345
    Height = 298
    Align = alLeft
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    Lines.Strings = (
      '          Правила заполнения'
      '         японского кроссворда'
      '    В японском кроссворде защифрованы  не'
      'слова, а изображения.  Задача - составить'
      'изображение по числам, которые проставле-'
      'ны слева от строк  и на колонками.  Числа'
      'показывают, сколько групп  чёрных  клеток'
      'на  ходится   в  соответсвующей  линии  и'
      'сколько слитых чёрных клеток содержит ка-'
      'ждая группа.'
      '    Например, числа 3,7 и 2 означают, что'
      'в  этом  ряду есть три группы, состоящие:'
      'первая - из трёх, вторая- из семи, третья'
      'из двух чёрных клеток. Группы разделяются'
      'как минимум одной пустой клеткой.  Пустые'
      'клетки могут быть и по краям рядов. Самое'
      'трудное - это определить,  сколько пустых'
      'клеток находится между чёрными  группами.')
    ParentFont = False
    ReadOnly = True
    TabOrder = 1
  end
end
