<%
FoundUser = False
Application.Lock
	localStats = Application( "Stats" )
	For k = 0 To UBound( localStats, 2 )
		If localStats( 0, k ) = Session("ID") Then
			FoundUser = True
			Exit For
		End If
	Next
	If FoundUser = False Then
		For k = 0 To UBound( localStats, 2 )
			If localStats( 0, k ) = "" Then
				localStats( 0, k ) = Session("ID")
				Exit For
			End If
		Next
	End If
	Application( "Stats" ) = localStats
Application.UnLock
%>
<html>
<head>
	<meta http-equiv="Content-Language" content="en-us">
	<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
	<meta name="GENERATOR" content="Microsoft FrontPage 4.0">
	<meta name="ProgId" content="FrontPage.Editor.Document">
	<meta http-equiv="REFRESH" content="10;<%=MySelf%>">
	<title>Users</title>
</head>
<BODY BGCOLOR="#efefef">
<center><br>
	<font face="Tahoma" size="1" color="Green"><b>Active Users</b></font><br>
<%
Application.Lock
   	localStats=Application("Stats")
Application.UnLock
%>
<%
For i = 0 To UBound( localStats, 2 )
	If localStats( 0, i ) <> "" Then
%>	<font face="tahoma" size="1" color="blue"><%=localStats( 0, i )%></font><br>
<%	End If
Next
%>
<p><br></p>
</center>
</body>
</html>