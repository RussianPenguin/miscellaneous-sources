<%

    User = Request.Form("User")
    From = Request.Form("From")
    Msg = Request.Form("Msg")

    'If IsEmpty(Application("PrivateMessages")) Then
    '       Set privmsgs = Server.CreateObject("Scripting.Dictionary")
    '       Set Application("PrivateMessages") = privmsgs
    'End If
    'Application("PrivateMessages").Add User, "Private Message From " & From & ":" & Msg

    PrivRcpt = Application("PrivateRcpt")
    If IsArray(PrivRcpt) Then
           PrivateMsgs = Application("PrivateMsgs")
           NumOfRcpt = UBound(PrivRcpt) +1
           ReDim Preserve UpdatedPrivRcpt(NumOfRcpt)
           ReDim Preserve UpdatedPrivMsg(NumOfRcpt)
           UpdatedPrivRcpt(NumOfRcpt-1) = User
           UpdatedPrivMsg(NumOfRcpt-1) = "<font face=verdana color=#008080>Private Message From " & From & ":</font>" & Msg
           Application("PrivateRcpt") = UpdatedPrivRcpt
           Application("PrivateMsgs") = UpdatedPrivMsg
   Else
           ReDim UpdatedPrivRcpt(1)
           ReDim UpdatedPrivMsg(1)
           UpdatedPrivRcpt(0) = User
           UpdatedPrivMsg(0) = "Private Message From " & From & ":" & Msg
           Application("PrivateRcpt") = UpdatedPrivRcpt
           Application("PrivateMsgs") = UpdatedPrivMsg

   End If

    Response.Redirect "privatemsg.asp"

%>