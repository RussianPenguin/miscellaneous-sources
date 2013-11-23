<html>
<head>
	<title><!--#include file="version.inc"--></title>

<script LANGUAGE="Javascript">

function cambia1(){
	document.location.href="http://<%=Request.ServerVariables("SERVER_NAME")%>/chatchat/users.asp?random=<%=Second(Now)%><%=Minute(Now)%><%=Hour(Now)%>"
}

</script>
</head>
<!--META HTTP-EQUIV="Refresh" CONTENT="15"-->
<body BGCOLOR="#ffffff" OnLoad="timerID1=setTimeout('cambia1()',15000)">
<!--#include file="fonts.inc"-->
<font SIZE="1"><center>
<table WIDTH="100%">
	<tr>
		<td BGCOLOR="#dddddd"><!--#include file="fonts.inc"--><font SIZE="1"><center>L a s t &nbsp; E v e n t :</center></td>
	</tr>
	<tr>
		<td BGCOLOR="#efefef"><center><i><!--#include file="fonts.inc"--><font SIZE="1">
		<%
		LocalEvent = Application("StoredEvent")
		%>
		<%=LocalEvent%>
		</i></td>
	</tr>
</table>
<br><br>

<table WIDTH="100%">
<tr>
	<td BGCOLOR="#dddddd" COLSPAN="2"><center><!--#include file="fonts.inc"--><font SIZE="1">O n L i n e &nbsp; N o w:
	</center>
</tr>
	
<%
	LocalLista = Application("StoredLista")
	flag_someone = 0
	
	For u = 0 To 9
		If LocalLista(u,0) <> "none" Then
			If LocalLista(u,0) <> "" Then
				%><tr><td BGCOLOR="#ffffff" WIDTH="1%"><img SRC="gif/user_<%=LocalLista(u,1)%>.gif"></td><td BGCOLOR="#eeeeee"><!--#include file="fonts.inc"--><b><%=LocalLista(u,0)%></b></td></tr><%
				flag_someone = 1
			End If
		End If
	Next
	If flag_someone = 0 Then
		%><tr><td COLSPAN="2"><!--#include file="fonts.inc"--><font SIZE="1"><br><br><center><i><font COLOR="#000000">Nessuno in linea alle <%=Now%><hr WIDTH="5" SIZE="1"></font><font COLOR="#0000ff">No-one on line at <%=Now%>
		<hr WIDTH="5" SIZE="1"><font COLOR="#000000">Scegliere un nome...<br><font COLOR="#0000ff">Please login...</i></td></tr>
		<%
	End If
	
%>

</table>
</html>