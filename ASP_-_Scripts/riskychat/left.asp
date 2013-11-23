<HTML>
<HEAD>
	<TITLE><!--#include file="version.inc"--></TITLE>
<SCRIPT LANGUAGE="Javascript">

function cambia(){
	document.location.href="http://<%=Request.ServerVariables("SERVER_NAME")%>/chatchat/left.asp?random=<%=Second(Now)%><%=Minute(Now)%><%=Hour(Now)%>"
}

</SCRIPT>
</HEAD>
<!--META HTTP-EQUIV="Refresh" CONTENT="6"-->
<BODY BGCOLOR="#ffffff" TEXT="#000000" OnLoad="timerID=setTimeout('cambia()',7000)">
<!--#include file="fonts.inc"-->
<%

If Session("nome_utente") <> "" Then
	If Request("frase") <> "" Then

		If InStr(Request("frase"),"<") = 0 Then
			If Session("ultimo") <> Request("frase") Then
				LocalArray = Application("StoredArray")
				y = 19
				While y >=1
					LocalArray(y) = LocalArray(y-1)
					y = y - 1
				Wend
				LocalArray(0) = "<B>" & Session("nome_utente") & ":</B> <FONT COLOR=#" & Session("colore_utente") & ">" & Request("frase") & " </FONT><FONT SIZE=1>- (" & Now & ")</FONT><BR>"
				Application.Lock
				Application("StoredArray") = LocalArray
				Application.Unlock
			End If
			Session("ultimo") = Request("frase")
		Else
			LocalEvent=Application("StoredEvent")
			LocalEvent = "<B></I><FONT SIZE=2>" & Session("nome_utente") & "</FONT></B><BR><I>ha provato a<BR>scrivere codice<BR> HTML...<BR><FONT COLOR=#0000ff>has tried to<BR>write HTML code...<BR></FONT>:-)"

			Application.Lock
			Application("StoredEvent") = LocalEvent
			Application.Unlock
		End If

	End If
End If
%>
<%
	For u = 0 To 19
		LocalArray = Application("StoredArray")
		%><%=LocalArray(u)%><BR><%
	Next

%>

</BODY>
</HTML>

