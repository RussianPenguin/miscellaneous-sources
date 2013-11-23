object Info: TInfo
  Left = 243
  Top = 133
  BorderStyle = bsToolWindow
  Caption = 'О программе'
  ClientHeight = 204
  ClientWidth = 269
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 0
    Top = 8
    Width = 265
    Height = 169
    Lines.Strings = (
      'Фрактал-генератор (FGen) ver 0.01beta'
      ''
      'Программа рисует на экране один из самых '
      'простых фракталов - множество '
      'Манедельброта. Используется реккурентная '
      'формула Z[i+1]=Z[i]*Z[i]+C, где Z,C - '
      'комплексные числа. С - текущая точка для '
      'которой расчитывается цвет. Вычисления '
      'ведутся до тех пор, пока |Z| меньше заданного '
      'значения, количество итераций принимается за '
      'цвет точки.'
      'Код расчета вынесен в отдельный поток '
      'TCalcThread, что позволяет сделать программу '
      'более управляемой. Предусмотрено '
      'сохранение картинки в файл JPG, GIF или BMP, '
      'увеличение и уменьшение, изменение палитры. '
      'Поскольку расчет занимает некоторое время, '
      'несколько секунд, введен индикатор '
      'выполнения. Можно приостановить расчет, '
      'затем вновь его продолжив. Кнопка сброс '
      'устанавливает исходный размер фрактала (не '
      'пересчитывая его заново).'
      'Используемый компилятор: C++ Builder 5.'
      ''
      'Вячеслав cooluser@ngs.ru')
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Button1: TButton
    Left = 88
    Top = 184
    Width = 65
    Height = 17
    Caption = 'Хорошо'
    TabOrder = 1
    OnClick = Button1Click
  end
end
