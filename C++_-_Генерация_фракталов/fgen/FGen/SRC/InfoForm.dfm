object Info: TInfo
  Left = 243
  Top = 133
  BorderStyle = bsToolWindow
  Caption = '� ���������'
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
      '�������-��������� (FGen) ver 0.01beta'
      ''
      '��������� ������ �� ������ ���� �� ����� '
      '������� ��������� - ��������� '
      '�������������. ������������ ������������ '
      '������� Z[i+1]=Z[i]*Z[i]+C, ��� Z,C - '
      '����������� �����. � - ������� ����� ��� '
      '������� ������������� ����. ���������� '
      '������� �� ��� ���, ���� |Z| ������ ��������� '
      '��������, ���������� �������� ����������� �� '
      '���� �����.'
      '��� ������� ������� � ��������� ����� '
      'TCalcThread, ��� ��������� ������� ��������� '
      '����� �����������. ������������� '
      '���������� �������� � ���� JPG, GIF ��� BMP, '
      '���������� � ����������, ��������� �������. '
      '��������� ������ �������� ��������� �����, '
      '��������� ������, ������ ��������� '
      '����������. ����� ������������� ������, '
      '����� ����� ��� ���������. ������ ����� '
      '������������� �������� ������ �������� (�� '
      '������������ ��� ������).'
      '������������ ����������: C++ Builder 5.'
      ''
      '�������� cooluser@ngs.ru')
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Button1: TButton
    Left = 88
    Top = 184
    Width = 65
    Height = 17
    Caption = '������'
    TabOrder = 1
    OnClick = Button1Click
  end
end
