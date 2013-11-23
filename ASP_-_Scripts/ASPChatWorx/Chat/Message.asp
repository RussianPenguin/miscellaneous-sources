<%@ Language=VBScript %>
<%
Option Explicit

Dim Text, TempArray

If Not Request("Message") = "" Or Not Request("Emotion") = "" Then
	Text = CStr(Replace(Request("Message"),"'","`"))
	If Application("TPlace") > 49 Then
		Application("TPlace") = 0
	End If
	If (Left(UCase(Text),2) = "/H") Or (Left(Text,2) = "/?") Or (UCase(Text) = "HELP") Then
%>
<script language="JavaScript">
<!--
//
{
	window.open("Help.htm","Help","width=130,height=300,screenX=50,screenY=0,scrollbars=no,toolbar=no,menubar=no,resizable=no,locationbar=no,hotkeys=no");
}
// -->
</script>
<% 
	ElseIf Left(UCase(Text),2) = "/Q" Then
		Application.LOCK
			If Application("TPlace") > 49 Then
				Application("TPlace") = 0
			End If
			TempArray                        = Application("Talk")
			TempArray(Application("TPLACE")) = "<img src=Images/Exit.gif> " & "<b>" & Session("ID") & "</b><font color=red> has left. " & Now() & "</font>"
			Application("Talk")              = TempArray
			Application("TPlace")            = Application("TPlace")+1
		Application.Unlock
		Session.Abandon()
%>
<script language="JavaScript">
<!--
{
	parent.close();
}
//-->
</script>
<%
	ElseIf Left(UCase(Text),2) = "/R" Then
		'Change the refresh rate
		Dim Refresh
		Refresh = UCase(Text)
		Refresh = Replace(Refresh, "/R", "")
		'We should be left with a number
		If IsNumeric(Refresh) Then
			Session("Refresh") = Refresh
		End If
	Else
		Application.LOCK
			Text = CheckProfanity( Text )	'Check for Profanity
			If Left(UCase(text),3) = "ZZZ" Then text = "I'm falling asleep here. Is anyone home?!"
			text = CStr(Replace(text,"<","&lt;"))
			text = CStr(Replace(text,">","&gt;"))
			text = CStr(Replace(text,":-)",  "<img src='images/symbols/1.gif'>"))
			text = CStr(Replace(text,";-)",  "<img src='images/symbols/2.gif'>"))
			text = CStr(Replace(text,":-(",  "<img src='images/symbols/3.gif'>"))
			text = CStr(Replace(text,":-|",  "<img src='images/symbols/4.gif'>"))
			text = CStr(Replace(text,":-@",  "<img src='images/symbols/5.gif'>"))
			text = CStr(Replace(text,":-?",  "<img src='images/symbols/6.gif'>"))
			text = CStr(Replace(text,":-!",  "<img src='images/symbols/7.gif'>"))
			text = CStr(Replace(text,"Hello","<img src='images/symbols/8.gif'> Hello "))
			text = CStr(Replace(text,":*",   "<img src='images/symbols/9.gif'>"))
			'Replace words with symbols
			'text = CStr(Replace(UCase(text), "LOVE", "<img src='images/symbols/9.gif'>"))
			TempArray                        = Application("Talk")
			TempArray(Application("TPLACE")) ="<img src=images/Person.jpg><font face=tahoma size=1><b> " & Session("ID") & "</b>: </font><font face=tahoma color=maroon size=1>" & Request.Form("emotion") & "</b></font>" & text & "</b></font>"
			Application("Talk")              = TempArray
			Application("TPlace")            = Application("TPlace")+1
		Application.Unlock
	End If
End If
%>
<html>
<head>
	<title> Message Page </title>
</head>
<body BGCOLOR="#efefef" LANGUAGE="javascript" onload="document.SENDMSG.Message.focus();">
<form METHOD="POST" ACTION="Message.asp" name="SENDMSG">
<table width="640" cellspacing="0" cellpadding="0" border="0" height="0">
	<tr>
		<td width="470">
			<input NAME="Message" TYPE="TEXT" VALUE SIZE="45">
			<input src="Images/Go.gif" type="image" value="Submit" name="I3" alt="Send Page!" WIDTH="20" HEIGHT="20">
			<font size="1">
				&nbsp;&nbsp;
				<a href="Message.asp?Message=/Q" target="_self">
					<img border="0" src="Images/Out.gif" WIDTH="30" HEIGHT="20">
				</a>
			</font>
		</td>
		<td width="170" rowspan="4" valign="top" align="center">
			<font face="Tahoma" size="2" color="maroon">Send an emotion</font>
			<table border="0" cellspacing="0" cellpadding="0" width="30">
				<tr>
					<td><input type="radio" value="smiles " name="emotion"></td>
					<td><font face="Tahoma" size="1" color="#000080">smile</font></td>
				</tr>
				<tr>
					<td><input type="radio" name="emotion" value="frowns "></td>
					<td><font face="Tahoma" size="1" color="#000080">frown</font></td>
				</tr>
				<tr>
					<td><input type="radio" name="emotion" value="laughs "></td>
					<td><font face="Tahoma" size="1" color="#000080">laugh</font></td>
				</tr>
				<tr>
					<td><input type="radio" name="emotion" value="shouts "></td>
					<td><font face="Tahoma" size="1" color="#000080">shouting</font></td>
				</tr>
				<tr>
					<td><input type="radio" name="emotion" value="whispers "></td>
					<td><font face="Tahoma" size="1" color="#000080">whisper</font></td>
				</tr>
			</table>
</form>
		</td>
	</tr>
	<tr>
		<td width="470" background="images/stripesgray.gif" valign="middle" align="left"><font face="Tahoma" size="1" color="#339966"><div style="letter-spacing:0.3em;">Advertising</div></font></td>
	</tr>
	<tr>
		<td width="470" valign="middle" align="center">
			<!-- Start:	Advertising -->
			<a href="http://Web.FailSafe.co.za/BannerWorX/Banner.asp?a=click<%="&"%>c=SafeChat<%="&"%>n=1" Target="_new">
				<img border="0" width="468" height="60" alt="Support our Sponsors" src="http://Web.FailSafe.co.za/BannerWorX/Banner.asp?a=banner<%="&"%>c=SafeChat<%="&"%>n=1">
			</a>
			<!-- End:	Advertising -->
		</td>
	</tr>
	<tr>
		<td width="470" background="images/stripesgray.gif" align="right" valign="middle">
			<font face="Tahoma" size="1" color="#339966">
			<div style="letter-spacing:0.3em;">
				Created By <a href="http://www.failsafe.co.za" target="_blank">FailSafe Systems</a>
			</div>
			</font>
		</td>
	</tr>
</table>
</body>
</html>
<%
Function CheckProfanity( Text )
	Dim arrSwear, x, n
	'Get the Arrays
	arrSwear = Application("SwearWords")
	Text = Split(Text, " ")
	For x  = LBound(Text) To UBound(Text)
		'Check if it is profane
		For n = LBound(arrSwear) To UBound(arrSwear)
			If InStr(UCase(Text(x)), arrSwear(n)) > 0 Then
				Text(x) = "@#$"
				Exit For
			End If
		Next
	Next
	CheckProfanity = Join(Text, " ")
End Function
%>