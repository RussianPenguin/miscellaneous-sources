
<html>
<head>
  <Title>ASP Chat</title>

<SCRIPT LANGUAGE="JavaScript">

  function enter(){
        chatWin = window.open("main.asp","chatWin","toolbar=no,location=no,directories=no,status=no,menubar=no,scrollbars=no,resizable=no,WIDTH=630,HEIGHT=540");
        chatWin.location.href = "main.asp"
        if(navigator.appVersion.indexOf("4") != -1){
            chatWin.moveTo(0,0);
        }
  }

     function closeWin(){
           chatWin.close();
     }
</SCRIPT>
</head>

<body  Bgcolor="#476895" link=#000000 vlink=#000000>
<CENTER>
<img src="images/chat.gif">
</center><br>
<center>
<table width=620><tr><td>
<font face="Trebuchet MS, ms sans serif, Verdana,Arial" size=2 color=#f0f0f0>
ASP Chat is a simple web based chat written in ASP. ASP Chat offers real time chat,
who's online, private messages, and multiple rooms. Give it a try. Download the
freeware version <a href="http://www.tippedcow.com/downloads.asp?what=asp-chat1.zip">here</a>.
<ul><font size=2>
To join a chat room click the 'Enter' button below. If you would like to create
your own chat room go <a href="create_room.html">here</a>.
<br><br>
</td></tr>
<tr><td align=right>
<form onSubmit="enter()"><input type=image src="images/enter.gif" border=0 value="Enter ASP Chat" ></form>
</td></tr>
<tr><td align=right>
<a href="/default.asp"><font face="ms sans serif" size=2 color=#ffffff>Back to Adrenalin Labs</font></a>
</td></tr>
</table>







