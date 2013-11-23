<HTML>
<HEAD>
	<TITLE><!--#include file="version.inc"--></TITLE>
</HEAD>
<BODY>
<%

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
	
	
	Application("Status") = 0

%>
<A HREF="default.asp">restart</A>...
</BODY>
</HTML>