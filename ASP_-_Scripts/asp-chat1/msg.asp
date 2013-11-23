<HTML>
<HEAD>

<script language="javascript">

   function handle(form){
       var text = form.visMsg.value
       if(text == "") return false;
       form.Msg.value = text;
       form.RefreshRate.value = document.forms[1].intreval[document.forms[1].intreval.selectedIndex].value
       form.visMsg.value="";
       form.visMsg.focus();
       return true;
   }

  function exitChat(){
       parent.frames.location.href='exit.asp';
       return false;
  }

</script>

</HEAD>
<BODY BGCOLOR="cccccc" TEXT=#000000 onLoad="document.message.visMsg.focus()">

<TABLE><TR><TD  ALIGN=CENTER VALIGN=TOP>
<FORM NAME="message" TARGET="chat" ACTION="chat.asp" METHOD="POST" onSubmit="return handle(this)">
<font face="ms sans serif" size=2>Message:</font>
<input type="text" size=40 name="visMsg">
<input type="hidden" Name="Msg" value="">
<input type="hidden" Name="RefreshRate">
<input type="hidden" Name="Add" value="TRUE">
</TD>
</form>
<form onSubmit="return exitChat()">
<td valign=top>
<font face='ms sans serif' size=2 color=#000000>
Refresh Rate: <select name="intreval">
<option value="10000">10 secs.
<option value="20000">20 secs.
<option value="30000">30 secs.
<option value="45000">45 secs.
</select>
</td><td valign=bottom>
<INPUT type="image" border=0 src="images/logoff.gif">
</FORM>

</TD></TR></TABLE>
</CENTER>
</BODY>
</HTML>