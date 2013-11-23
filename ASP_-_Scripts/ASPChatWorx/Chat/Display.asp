<!-- Display.asp -->
<%
MyServer  = Request.ServerVariables("SERVER_NAME")
MyPath    = Request.ServerVariables("SCRIPT_NAME")
MySelf    = "HTTP://"&MyServer&MyPath
LineColor = "#ffffff"
%>
<HTML>
<HEAD>
	<META HTTP-EQUIV="REFRESH" CONTENT="<%=Session("Refresh")%>;<%=MySelf%>">
	<TITLE>Display Page</TITLE>
	<base target="main">
</HEAD>
<BODY BGCOLOR="#efefef">
<table width="100%" border="0" align="center" cellspacing="1" cellpadding="0">
<%
TempArray=Application("Talk")
For i = Application("TPlace")-1 To 0 Step -1
	If i Mod 2 = 0 Then
		LineColor = "#ffffff"
	Else
		LineColor = "#efefef"
	End If
	Response.Write("	<tr width=""100%"">") & vbCrLf
	Response.Write("		<td bgcolor=""" & LineColor & """ valign=""middle"" align=""left"">") & vbCrLf
	Response.Write("			<font face=""arial"" size=""1"">"&Temparray(i)&"</font>") & vbCrLf
	Response.Write("		</td>") & vbCrLf
	Response.Write("	</tr>") & vbCrLf
Next
%>
</table>
</BODY>
</HTML>