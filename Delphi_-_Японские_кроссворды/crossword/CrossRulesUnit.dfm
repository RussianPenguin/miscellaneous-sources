object CrossRulesForm: TCrossRulesForm
  Left = 243
  Top = 123
  BorderStyle = bsDialog
  Caption = '������� ���������� �������� ���������'
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
      '          ������� ����������'
      '         ��������� ����������'
      '    � �������� ���������� �����������  ��'
      '�����, � �����������.  ������ - ���������'
      '����������� �� ������, ������� ���������-'
      '�� ����� �� �����  � �� ���������.  �����'
      '����������, ������� �����  ������  ������'
      '��  �������   �  ��������������  �����  �'
      '������� ������ ������ ������ �������� ��-'
      '���� ������.'
      '    ��������, ����� 3,7 � 2 ��������, ���'
      '�  ����  ���� ���� ��� ������, ���������:'
      '������ - �� ���, ������- �� ����, ������'
      '�� ���� ������ ������. ������ �����������'
      '��� ������� ����� ������ �������.  ������'
      '������ ����� ���� � �� ����� �����. �����'
      '������� - ��� ����������,  ������� ������'
      '������ ��������� ����� �������  ��������.')
    ParentFont = False
    ReadOnly = True
    TabOrder = 1
  end
end
