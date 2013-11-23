<%@ Language=VBScript %>
<%
Option Explicit

Dim ErrMsg, ReqID, Clr, ColorChoice
Dim TempArray, i, localStats

ErrMsg = Request("ErrMsg")
ReqID  = Request("ReqID")
If ErrMsg = "" Then
	If ReqID <> "" Then
		Clr           = Request.Form("color")
		If Clr = "" Then Clr = "000000"
		ColorChoice   = "<font color='#"& Clr &"'>"
		Session("ID") = ColorChoice & ReqID & "</font>"

		Application.Lock
			localStats = Application("Stats")
		Application.UnLock

		For i = 0 To UBound( localStats, 2 )
			If localStats( 0, i ) = Session("ID") Then
				Response.Redirect ("Login.asp?ReqID=" & ReqID & "&ErrMsg=InUse")
			End If
		Next

		Application.LOCK
			If Application("TPlace") > 49 Then
				Application("TPlace") = 0
			End If
			TempArray                        = Application("Talk")
			TempArray(Application("TPLACE")) = "<img src=images/Enter.gif> " & "<b>" & Session("ID") & "</b><font color=blue> has entered. " & Now() & "</font>"
			Application("Talk")              = TempArray
			Application("TPlace")            = Application("TPlace") + 1
		Application.Unlock
		Response.Redirect("Frames.asp")
	End If
	ErrMsg = "Enter a login ID"
Else
	Select Case UCase(ErrMsg)
		Case "INUSE":	ErrMsg = "<b>" & ReqID & "</b> is already in use - please choose another"
	End Select
End If
%>
<html>
<head>
	<meta http-equiv="Content-Language" content="en-us">
	<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
	<title>ASPChatWorX Login</title>
</head>
<body>

<script Language="JavaScript">
<!--//Hide from cjallenged browsers
function CheckEntry(theForm)
{
	if (theForm.ReqID.value == "")
	{
		alert("Please enter a value for the \"ReqID\" field.");
		theForm.ReqID.focus();
		return (false);
	}
	if (theForm.ReqID.value.length < 4)
	{
		alert("Please enter at least 4 characters in the \"ReqID\" field.");
		theForm.ReqID.focus();
		return (false);
	}
	if (theForm.ReqID.value.length > 10)
	{
		alert("Please enter at most 10 characters in the \"ReqID\" field.");
		theForm.ReqID.focus();
		return (false);
	}
	return (true);
}
//-->
</script>

<p align="center">&nbsp;</p>
<p align="center">&nbsp;</p>
<div align="center">
<center>
<table width="400" border="1" cellspacing="0" bordercolor="#000000" bgcolor="#FFFF99" cellpadding="5">
	<tr>
		<td valign="middle" align="center">
			<font face="Tahoma" size="4">
				ASPChatWorx Login Page
			</font>
			<font face="Tahoma" size="2"><br>
				<%=ErrMsg%>.<br>
				Name MUST be between 4 and 10 characters.<br>
			</font>
			<p>
			<font face="Tahoma" size="2">
			To access help at any time type /help or /?
			</font>
			</p>
		</td>
	</tr>
</table>
<br>
</center>
</div>
<center>
<form method="POST" action="Login.asp" onsubmit="return CheckEntry(this)" name="LoginForm">
	<select size="1" name="color">
		<option VALUE="000000" SELECTED>Black</option>
		<option VALUE="330099">Dark Blue</option>
		<option VALUE="FF0000">Red</option>
		<option VALUE="0000FF">Blue</option>
		<option VALUE="008000">Green</option>
		<option VALUE="757575">Gray</option>
		<option VALUE="b5b5b5">Silver</option>
		<option VALUE="FF80C0">Pink</option>
		<option VALUE="3399ff">Aqua</option>
		<option VALUE="33cc33">Lime</option>
		<option VALUE="CD5A19">Orange</option>
		<option VALUE="408080">Teal</option>
		<option VALUE="800000">Maroon</option>
		<option VALUE="808000">Olive</option>
		<option VALUE="FF0080">Rosa</option>
	</select>
	<input type="text" name="ReqID" size="20" maxlength="10">
	<input type="submit" value="Join" name="B1">
</form>
</center>

<p align="center">&nbsp;</p>
<div align="center">
<center>
</center>
</div>
</body>
</html>
