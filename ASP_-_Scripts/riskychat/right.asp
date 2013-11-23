<html>
<head>
	<title><!--#include file="version.inc"--></title>
<script LANGUAGE="Javascript">	
function switch_frase(){
	document.inputazione.frase.value = document.inputazione.prefrase.value;
	document.inputazione.prefrase.value = "";
}

</script>	
</head>
<!--BASE TARGET="_top"-->
<%
	flag_login = 0
	If (Request("nome_utente")) <> "" OR Request("logoff") = 1 Then
		LocalLista = Application("StoredLista")
		LocalContatoreLista = Application("StoredContatoreLista")


			If Request("logoff") = 1 Then
				LocalEvent =  "<B><I>" & Session("nome_utente") & "</B><BR> has logged OUT<BR>at " & Now & "</I>"

				' QUI LA ROUTINE PER IL LOGOUT
				a = 0
					While a <= 8
						If LocalLista(a,0) = Session("nome_utente") Then
							c = a
							While c <= 8
								LocalLista(c,0) = LocalLista(c+1,0)
								LocalLista(c,1) = LocalLista(c+1,1)
								c = c + 1
							Wend
						End If
					a = a + 1
				Wend
				Session("logged_in") = "false"
				Session("nome_utente") = ""
				Session("colore_utente") = ""
				%><body BGCOLOR="#ffffff">
					<!--#include file="fonts.inc"-->
					<%Call FormLogin()%>
				<%
			Else
				flag_prova_login = "false"
				If LocalContatoreLista < 9 Then
					
					
					If InStr(Request("nome_utente"),"<") = 0 Then
						If InStr(Request("nome_utente"),"+") = 0 Then
							If InStr(Request("nome_utente"),"%") = 0  Then
								If InStr(Request("nome_utente"),"""") = 0 Then
									If InStr(Request("nome_utente"),"/") = 0 Then
										If InStr(Request("nome_utente"),"'") = 0 Then
											If InStr(Request("nome_utente"),"\") = 0  Then
												If InStr(Request("nome_utente"),"*") = 0 Then
													If InStr(Request("nome_utente"),";") = 0 Then
														If InStr(Request("nome_utente"),":") = 0 Then
															If InStr(Request("nome_utente"),"&") = 0 Then
															
																flag_prova_login = "true"
																
															Else
																flag_prova_login = "false"
																flag_reason_login = "carattere"
															End If
														Else
															flag_prova_login = "false"
															flag_reason_login = "carattere"
														End If
													Else
														flag_prova_login = "false"
														flag_reason_login = "carattere"
													End If
												Else
													flag_prova_login = "false"
													flag_reason_login = "carattere"
												End If
											Else
												flag_prova_login = "false"
												flag_reason_login = "carattere"
											End If
										Else
											flag_prova_login = "false"
											flag_reason_login = "carattere"
										End If
									Else
										flag_prova_login = "false"
										flag_reason_login = "carattere"
									End If
								Else
									flag_prova_login = "false"
									flag_reason_login = "carattere"
								End If
							Else
								flag_prova_login = "false"
								flag_reason_login = "carattere"
							End If
						Else
							flag_prova_login = "false"
							flag_reason_login = "carattere"
						End If
					Else
						flag_prova_login = "false"
						flag_reason_login = "carattere"
					End If
					
					b = 0
					While b <= 9
						If LocalLista(b,0) = "<FONT COLOR=#" & Request("colore_utente") & ">" & Request("nome_utente") & "</FONT>" Then
							flag_prova_login = "false"
							flag_reason_login = "existing"
						End If
						
						b = b + 1
					Wend
					
					If flag_prova_login = "true" Then
									
						y = 9
						While y >=1
							LocalLista(y,0) = LocalLista(y-1,0)
							LocalLista(y,1) = LocalLista(y-1,1)
							y = y - 1
						Wend
						LocalEvent = Application("StoredEvent")
						Session("nome_utente") = Request("nome_utente")
						Session("logo_utente") = Request("logo_utente")

						LocalEvent = "<FONT SIZE=2 COLOR=#" & Request("colore_utente") & "><B>" & Request("nome_utente") & "</B></FONT><BR> has logged IN<BR>at " & Now
						LocalLista(0,0) = "<FONT COLOR=#" & Request("colore_utente") & ">" & Request("nome_utente") & "</FONT>"
						LocalLista(0,1) = Session("logo_utente")
						Session("colore_utente") = Request("colore_utente")
						LocalContatoreLista = LocalContatoreLista + 1
						Session("logged_in") = "true"
						Reloada_zero = "OnLoad=""top.window.parent.frames[9].location.href='zero.asp?nome_utente=" & Session("nome_utente") & "'"""
						%><body BGCOLOR="#ffffff" <%=Reloada_zero%>>
							<!--#include file="fonts.inc"-->
						<%


						
					Else
					
						Select Case flag_reason_login
							Case "carattere"
								LocalEvent=Application("StoredEvent")
								LocalEvent = "<FONT COLOR=#000000><I>Non sono ammessi<BR>nel Nome Utente<BR>caratteri come...<BR><B>&,<,*,;,:,/,|,"",',+</B><BR><FONT COLOR=#0000ff>...are not <BR>allowed in user<BR>names</FONT><BR>>;-)"
								Application.Lock
								Application("StoredEvent") = LocalEvent
								Application.Unlock
								%><body BGCOLOR="#ffffff">
								<!--#include file="fonts.inc"-->
								<font SIZE="1"><center><font COLOR="#000000">Non sono ammessi i seguenti caratteri nel Nome Utente: &amp;,<,*,;,:,/,|,"",',+ <FONT COLOR="#0000ff">...these characters are not allowed in User Names</font></center><br>
									
								<%Call FormLogin()%>
								<%
							Case "existing"
								%><body BGCOLOR="#ffffff">
									<!--#include file="fonts.inc"-->
									<font SIZE="1"><center><font COLOR="#000000">Login name gia' utilizzato, riprova - <font COLOR="#0000ff">Login name already in use, please try again</font></center><br>
									<%Call FormLogin()%>
								<%
						End Select
							
					End If
						
				Else
							%><body BGCOLOR="#ffffff">
								<!--#include file="fonts.inc"-->
								<font COLOR="#000000">Numero massimo di utenti consentiti - <font COLOR="#0000ff">Maximum users connected
							<%
				End If
			End If

			If flag_login = 0 Then
				Application.Lock
				Application("StoredEvent") = LocalEvent
				Application("StoredLista") = LocalLista
				Application.Unlock
			End If


	Else
		If(Session("nome_utente")) = "" Then
		%><body BGCOLOR="#ffffff">
		<!--#include file="fonts.inc"-->
		<%Call FormLogin()%>
		<%
		End If

	End If

	
	
	
	
	If (Session("nome_utente")) <> "" Then
			%><body BGCOLOR="#ffffff">
			<center><table WIDTH="100%"><tr><td BGCOLOR="#eeeeee"><center><!--#include file="fonts.inc"--><font SIZE="1"><font COLOR="#000000">Nome utente - <font COLOR="#0000ff">User logged as:</font><font SIZE="2"> <b><%=Session("nome_utente")%></b>&nbsp;&nbsp; <font SIZE="3">* * *</font> &nbsp;&nbsp;<font SIZE="1"><font COLOR="#000000">Colore carattere- <font COLOR="#0000ff">Font color: <img SRC="gif/colore_<%=Session("colore_utente")%>.gif"><br>
				<table BORDER="0">
					<tr>
						<td BGCOLOR="#eeeeee">
							<table BORDER="0">
								<tr>
									<td VALIGN="TOP" BGCOLOR="#eeeeee"><form NAME="inputazione" TARGET="left" ACTION="left.asp" METHOD="GET" onSubmit="switch_frase()">
										<input TYPE="HIDDEN" NAME="frase" VALUE>
										<input TYPE="TEXT" NAME="prefrase" SIZE="50" VALUE></td>
									<td VALIGN="TOP" BGCOLOR="#eeeeee"><input TYPE="SUBMIT" VALUE="Invia - Send">
										</form></td>
								</tr>
								
							</table>
						</td>
					</tr>
						<tr>
							<td BGCOLOR="#eeeeee" VALIGN="TOP"><center><!--#include file="fonts.inc"--><font SIZE="1"><font COLOR="#000000">Per uscire basta chiudere la finestra - <font COLOR="#0000ff">To log out just close this window
							</td>
						</tr>
				</table>
			</td><tr></table>
			
			<%
	End if
	
	
	' ROUTINE PER SCRIVERE SU UN FILE QUANTI UTENTI CE STANNO ON LINE @NOW
	ContaLista = Application("StoredLista")
	LocalContaUtenti = 0
	For u = 0 To 9
		If ContaLista(u,0) <> "none" Then
			If ContaLista(u,0) <> "" Then
				LocalContaUtenti = LocalContaUtenti + 1
			End If
		End If
	Next
	percorso = Server.MapPath("/") & "/chatchat/conta_file.txt"
	
	Set CF = CreateObject("Scripting.FileSystemObject") 
	Set conta_file = CF.CreateTextFile(percorso, True)
	conta_file.WriteLine(LocalContaUtenti)
	conta_file.Close
	
	' FINE ROUTINE


Sub FormLogin()
	Response.Write("<TABLE BORDER=0><TR><TD VALIGN=TOP WIDTH=250 BGCOLOR=#eeeeee><FORM NAME=login ACTION=right.asp TARGET=right METHOD=POST>" & chr(13))
	Response.Write("<CENTER><TABLE><TR><TD BGCOLOR=#eeeeee><FONT SIZE=1 FACE=ARIAL COLOR=#000000>Utente non identificato. Inserire nome utente:</TD><TD BGCOLOR=#eeeeee><FONT SIZE=1 FACE=ARIAL COLOR=#0000ff>User not logged in. Please login:</TD></TR></TABLE><INPUT TYPE=TEXT NAME=nome_utente> - <INPUT TYPE=SUBMIT VALUE=login></TD>" & chr(13))
	Response.Write("<TD VALIGN=TOP><FONT FACE=ARIAL SIZE=2><CENTER><FONT SIZE=1 FACE=ARIAL COLOR=#000000>Profilo Utente - <FONT SIZE=1 FACE=ARIAL COLOR=#0000ff>Personal Profile:<BR></CENTER>LOGO: <INPUT TYPE=RADIO CHECKED NAME=logo_utente VALUE=wave><IMG SRC=gif/user_wave.gif ALT=Wave>" & chr(13))
	Response.Write("<INPUT TYPE=RADIO NAME=logo_utente VALUE=pugno><IMG SRC=gif/user_pugno.gif ALT=Hasta>" & chr(13))
	Response.Write("<INPUT TYPE=RADIO NAME=logo_utente VALUE=waldo><IMG SRC=gif/user_waldo.gif ALT=Waldo>" & chr(13))
	Response.Write("<INPUT TYPE=RADIO NAME=logo_utente VALUE=surfer><IMG SRC=gif/user_surfer.gif ALT=Surfer>" & chr(13))
	Response.Write("<INPUT TYPE=RADIO NAME=logo_utente VALUE=windsurfer><IMG SRC=gif/user_windsurfer.gif ALT=Windsurfer>" & chr(13))
	Response.Write("<INPUT TYPE=RADIO NAME=logo_utente VALUE=snow><IMG SRC=gif/user_snow.gif ALT=Snowboarder>" & chr(13))
	Response.Write("<INPUT TYPE=RADIO NAME=logo_utente VALUE=para><IMG SRC=gif/user_para.gif ALT=Parachuter>" & chr(13))
	Response.Write("<BR>FONT:" & chr(13))
	Response.Write("<INPUT TYPE=RADIO NAME=colore_utente CHECKED VALUE=ff0000><IMG SRC=gif/colore_ff0000.gif>" & chr(13))
	Response.Write("<INPUT TYPE=RADIO NAME=colore_utente VALUE=0000ff><IMG SRC=gif/colore_0000ff.gif>" & chr(13))
	Response.Write("<INPUT TYPE=RADIO NAME=colore_utente VALUE=b57315><IMG SRC=gif/colore_b57315.gif>" & chr(13))
	Response.Write("<INPUT TYPE=RADIO NAME=colore_utente VALUE=219c21><IMG SRC=gif/colore_219c21.gif>" & chr(13))
	Response.Write("<INPUT TYPE=RADIO NAME=colore_utente VALUE=9a2686><IMG SRC=gif/colore_9a2686.gif>" & chr(13))	
	Response.Write("<INPUT TYPE=RADIO NAME=colore_utente VALUE=ff9805><IMG SRC=gif/colore_ff9805.gif>" & chr(13))	
	Response.Write("<INPUT TYPE=RADIO NAME=colore_utente VALUE=848484><IMG SRC=gif/colore_848484.gif>" & chr(13))	
	Response.Write("<INPUT TYPE=RADIO NAME=colore_utente VALUE=8c8cff><IMG SRC=gif/colore_8c8cff.gif>" & chr(13))	
	Response.Write("<INPUT TYPE=RADIO NAME=colore_utente VALUE=000000><IMG SRC=gif/colore_000000.gif></TD></TR></TABLE>" & chr(13))
	Response.Write("</FORM>" & chr(13))
End Sub
%>
</body>
</html>