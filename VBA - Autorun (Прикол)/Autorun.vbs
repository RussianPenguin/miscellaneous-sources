Set oWMP = CreateObject("WMPlayer.OCX.7")
Set colCDROMs = oWMP.cdromCollection
if colCDROMs.Count>=1 then
  For i=0 to colCDROMs.Count-1
    colCDROMs.item(i).Eject
  next
  MsgBox("        �� �����������... ���... �������� � ������ ���       :P       ")
end if
WScript.DisconnectObject(oWMP)