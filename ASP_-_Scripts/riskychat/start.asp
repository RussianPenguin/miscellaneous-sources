<HTML>
<HEAD>
	<TITLE><!--#include file="version.inc"--></TITLE>
</HEAD>
<BODY>
<%
	'NB in left.asp la variabile y non e' parametrizzata
	'lo stesso in right.asp per la variabile di scansione dell'array utenti
	'lo stesso in users.asp

	' INIZIALIZZA ARRAY DELLE FRASI
	Dim MyArray(20)
	For i = 0 To 19
		MyArray(i) = "..."
	Next
	Application.Lock
	Application("StoredArray") = MyArray
	Application.Unlock
	
	
	' INIZIALIZZA ARRAY UTENTI
	Dim LocalLista(10,2)
	For p = 0 to 9
		LocalLista(p,0) = "none"
		LocalLista(p,1) = "none"
	Next
	LocalContatoreLista = 0
	Application.Lock
	Application("StoredLista") = LocalLista
	Application("StoredContatoreLista") = LocalContatoreLista
	Application.Unlock
	
	percorso = Server.MapPath("/") & "/chatchat/conta_file.txt"
		
		Set CF = CreateObject("Scripting.FileSystemObject") 
		Set conta_file = CF.CreateTextFile(percorso, True)
		conta_file.WriteLine("0")
	conta_file.Close
	
	Application("Status") = 1
	
%>
Riskychat has been started. <A HREF="javascript:window.close()">Close this window</A> and reload the page in the father-window
</BODY>
</HTML>