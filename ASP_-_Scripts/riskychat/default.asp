<HTML>
<HEAD>
	<TITLE><!--#include file="version.inc"--></TITLE>

</HEAD>
<!--

R I S K Y C H A T
c r e a t e d   b y   f i l i p p o   d e   v i t a
w a v e @ f l a s h n e t . i t 
" m o n e y   w i l l   n e v e r   b u y   a   w a v e "

-->
<%
If (Request.ServerVariables("HTTP_COOKIE")) = "" Then
	%><CENTER>
	<BR><BR>
	<FONT FACE="garamond" SIZE=2>
	<BR><TABLE WIDTH=80% border=0>
		<TR>
			<TD VALIGN=TOP WIDTH=48%><FONT FACE="garamond" SIZE=3><P STYLE="TEXT-ALIGN=JUSTIFY"><FONT COLOR="#000000">Il vostro browser e' stato 
			configurato in maniera tale da non consentire l'invio di <B>cookies</B>. In tal caso non e' possibile accedere alla RiskyChat in quanto il server 
			deve in qualche maniera riconoscere chi scrive quale messaggio sulla chat (tecnicamente utilizziamo le <I>Session Variables</I>). Se cosi' non fosse i messaggi 
			che voi scrivereste sulla chat sarebbero anonimi.
			Vi consigliamo, quindi, di cambiare la vostra configurazione del browser e di accettare i <B>cookies</B>, non fanno male... se non li si usa male... 
			<BR><BR>
			<B>Premere F5 per assicurarsi che il vostro browser non accetta i cookies
			</FONT></TD>
			<TD>&nbsp;&nbsp</TD>
			<TD VALIGN=TOP><FONT FACE="garamond" SIZE=3><P STYLE="TEXT-ALIGN=JUSTIFY"><FONT COLOR="#0000ff">Your browser is currently configured NOT to accept <B>cookies</B>.
			RiskyChat needs such <B>cookies</B> to 
			work, for a user who writes a message has to be recognized in some way by the server(technically we use Session Variables) with his username.
			Otherwise all messages would be nameless. Reconfigure your browser and try again. <B>Cookies</B> are bad only if one missuses them...
			<BR><BR><B>Press F5 to make sure your browser does not accept cookies
			</FONT></TD>
		</TR>
	</TABLE>
	<%
Else
	' OK C'HAI I COOKIES!
		
		If Application("Status") = 1 Then
			Session("nome_utente") = ""
			%>
			<FRAMESET FRAMEBORDER=no BORDER=0 COLS="630,*,1" FRAMESPACING=0>
				<FRAMESET FRAMEBORDER=no BORDER=0 ROWS="50,*,98" framespacing=0>
					<FRAME MARGINHEIGHT=0 MARGINWIDTH=00 SRC="big_top.asp" NAME="big_top" NORESIZE FRAMEBORDER=no BORDER=0 SCROLLING=no>
					<FRAMESET FRAMEBORDER=no BORDER=0 COLS="147,483" framespacing=0>
						<FRAME MARGINHEIGHT=0 MARGINWIDTH=10 SRC="users.asp" NAME="users" NORESIZE FRAMEBORDER=no BORDER=0>
						<FRAMESET FRAMEBORDER=no BORDER=0 ROWS="21,*,8" framespacing=0>
							<FRAME MARGINHEIGHT=0 MARGINWIDTH=10 SRC="top.asp" NAME="top" NORESIZE FRAMEBORDER=no BORDER=0 SCROLLING=no>
							<FRAMESET FRAMEBORDER=no BORDER=0 COLS="17,451,15" framespacing=0>
								<FRAME MARGINHEIGHT=0 MARGINWIDTH=10 SRC="sx.asp" NAME="sx" NORESIZE FRAMEBORDER=no BORDER=0 SCROLLING=no>
								<FRAME MARGINHEIGHT=0 MARGINWIDTH=10 SRC="left.asp" NAME="left" NORESIZE FRAMEBORDER=no BORDER=0>
								<FRAME MARGINHEIGHT=0 MARGINWIDTH=10 SRC="dx.asp" NAME="dx" NORESIZE FRAMEBORDER=no BORDER=0 SCROLLING=no>
							</FRAMESET>	
							<FRAME MARGINHEIGHT=0 MARGINWIDTH=10 SRC="bottom.asp" NAME="bottom" NORESIZE FRAMEBORDER=no BORDER=0 SCROLLING=no>
						</FRAMESET>
					</FRAMESET>
					<FRAME MARGINHEIGHT=0 MARGINWIDTH=10 SRC="right.asp" NAME="right" NORESIZE FRAMEBORDER=no BORDER=0 SCROLLING=no>
				</FRAMESET>
				<FRAME MARGINHEIGHT=0 MARGINWIDTH=0 SRC="destra.htm" NAME="destra" NORESIZE FRAMEBORDER=no BORDER=0 SCROLLING=no>
				<FRAME MARGINHEIGHT=0 MARGINWIDTH=0 SRC="zero.asp" NAME="zero" NORESIZE FRAMEBORDER=no BORDER=0 SCROLLING=no>
			</FRAMESET>
			<%
		Else
			%>
			Riskychat is to be started... <A HREF="start.asp" TARGET="_new">click here</A> to start the service!
			<%
		End If
End If
%>


</HTML>