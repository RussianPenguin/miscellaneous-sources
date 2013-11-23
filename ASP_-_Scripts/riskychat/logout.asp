<HTML>
<HEAD>
	<TITLE><!--#include file="version.inc"--></TITLE>
</HEAD>


<%
		'If Session("logged_in") = "true" Then ---- STO PROVANDO A BECCARE STO CAZZO DE ESSERE ON LINE O NO!!!!!
		
		nome_utente = Request("nome_utente")
		colore_utente = Session("colore_utente")
		
		If nome_utente <> "" Then
			LocalLista = Application("StoredLista")
			LocalContatoreLista = Application("StoredContatoreLista")
			LocalEvent =  "<I><B>" & nome_utente & "</B><BR> has logged OUT<BR>at " & Now & "</I>"

					' QUI LA ROUTINE PER IL LOGOUT
					a = 0
						While a <= 8
							If LocalLista(a,0) = "<FONT COLOR=#" & colore_utente & ">" & nome_utente & "</FONT>" Then
								c = a
								While c <= 8
									LocalLista(c,0) = LocalLista(c+1,0)
									LocalLista(c,1) = LocalLista(c+1,1)
									c = c + 1
								Wend
							End If
						a = a + 1
					Wend
					Session("nome_utente") = ""
					Session("logged_in") = "false"
					Session("colore_utente") = ""
				
					Application.Lock
					Application("StoredEvent") = LocalEvent
					Application("StoredLista") = LocalLista
					Application.Unlock
					
					ContaLista = Application("StoredLista")
					LocalContaUtenti = 0
					For u = 0 To 9
						If ContaLista(u,0) <> "none" Then
							If ContaLista(u,0) <> "" Then
								LocalContaUtenti = LocalContaUtenti + 1
							End If
						End If
					Next
					percorso = Server.MapPath("/")& "/chatchat/conta_file.txt"
					Set CF = CreateObject("Scripting.FileSystemObject") 
					Set conta_file = CF.CreateTextFile(percorso, True)
					conta_file.WriteLine(LocalContaUtenti)
					conta_file.Close
	
		End If
		ContaLista = Application("StoredLista")
		LocalContaUtenti = 0
		For u = 0 To 9
			If ContaLista(u,0) <> "none" Then
				If ContaLista(u,0) <> "" Then
					LocalContaUtenti = LocalContaUtenti + 1
				End If
			End If
		Next
		Application.Lock
		Application("StoredContaUtenti") = LocalContaUtenti
		Application.Unlock
	
%>
<BODY OnLoad="window.close()">
</BODY>
</HTML>