<HTML>
<HEAD>
	<TITLE></TITLE>
</HEAD>
<BODY>
<%
	LocalLista = Application("StoredLista")
	LocalContaUtenti = 0
	
	For u = 0 To 9
		If LocalLista(u,0) <> "none" Then
			If LocalLista(u,0) <> "" Then
				LocalContaUtenti = LocalContaUtenti + 1
			End If
		End If
	Next
%>

<%=LocalContaUtenti%>


</TABLE>
</HTML>