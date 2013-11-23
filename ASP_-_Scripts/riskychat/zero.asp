<HTML>
<HEAD>
	<TITLE><!--#include file="version.inc"--></TITLE>
	<SCRIPT LANGUAGE="Javascript">
		function logout(){
				Sito = window.open("","RiskYChat",'width=10,height=10,toolbar=0,location=0,directories=0,status=0,menubar=0,resizable=0,scrollbars=0');
				Sito.location = "http://<%=Request.ServerVariables("SERVER_NAME")%>/chatchat/logout.asp?nome_utente=<%=Session("nome_utente")%>";
	    }
	
</SCRIPT>	
</HEAD>
<%
If Session("nome_utente") <> "" Then
	stringa_unload = "OnUnload=""logout()"""
End If

%>
<BODY <%=stringa_unload%>>
</BODY>
</HTML>