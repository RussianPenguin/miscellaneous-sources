<%
If Session("ID") = "" Then Response.Redirect("Login.asp")
%>
<html>
<head>
	<title>FailSafe ASPChatWorX</title>
	<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
</head>
<script language="JavaScript">
<!--
//
function Logout()
{
	self.close()
}
//-->
</script>

<frameset framespacing="0" border="0" frameborder="0" rows="30,*,153" onUnload="Logout();">
	<frame name="top" scrolling="no" noresize target="contents" src="Title.asp">
	<frameset marginwidth="0" marginheight="0" framespacing="0" Border="1" frameborder="1" cols="530,110*">
		<frame name="contents" marginwidth="4" marginheight="0" target="main" src="Display.asp" scrolling="auto" noresize>
		<frame name="main" marginwidth="2" marginheight="0" src="UserList.asp" scrolling="auto" noresize>
	</frameset>
	<frame name="bottom" scrolling="no" noresize target="contents" src="Message.asp" Marginwidth="5" Marginheight="0" Framespacing="0" Border="0" Frameborder="NO">
	<noframes>
		<body onUnload="Logout();">
		<p>This page uses frames, but your browser doesn't support them.</p>
		</body>
	</noframes>
</frameset>
</html>
