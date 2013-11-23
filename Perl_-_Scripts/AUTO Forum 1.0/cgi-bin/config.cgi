############################################################################
#                                  ���� ��������                           #
############################################################################

# ������� � ������� ������ ������
$dirforum = "forum/";
# ��� ����� � �������
$host="http://127.0.0.1";

# �������� ��������� ������
sub read_get {
 $buffer = "$ENV{'QUERY_STRING'}";
 @pairs = split(/&/, $buffer);
 foreach $pair (@pairs) {
   ($name, $value) = split(/=/, $pair);
   $name =~ tr/+/ /;
   $name =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;
   $name =~ s/<!--(.|\n)*-->//g;
   $name =~ s/<([^>]|\n)*>//g;
   $value =~ tr/+/ /;
   $value =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;
   $value =~ s/<!--(.|\n)*-->//g;
   $value =~ s/</&lt;/g;
   $value =~ s/>/&gt;/g;
   $value =~ s/\cM/ /g;
   $value =~ s/\n/ /g;
   $value =~ s/\|/ /g;
   $value =~ tr/ / /s;
   $value =~ s/<([^>]|\n)*>//g;
   $value =~ s/"/&quot;/g;
   $FORM{$name} = $value;
 }
}

# �������� ������� �����
sub get_time {
 ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst)=localtime(time);
 $mon++;
 $year+=1900;
 if ($mday<10) { $mday="0$mday"; }
 if ($mon<10) { $mon="0$mon"; }
 if ($min<10) { $min="0$min"; }
 $cur_date = "$mday.$mon.$year";
 $cur_time = "$hour:$min";
 $cur_year = "$year";
 $cur_mon = "$mon";
 $cur_day = "$mday";
}

# ���������� ����� (�� �������� � Windows)
sub filelock {
 flock(DB,2);
}

# ������������� ����� (�� �������� � Windows)
sub fileunlock {
 flock(DB,8);
}

# ������ ���� HTML �������
sub html_head {
 print << "[END]";
 <html><head><title>AUTO Forum v1.0 Freeware</title></head>
 <link rel="STYLESHEET" href="/styles.css">
 <style type="text/css">
 <!--
 -->
 </style>
 <body>
 <p align="center"><font size="4"><b>�����</b></font></p>
[END]
}

# �������� ���������� � ����
sub html_message {
 print << "[END]";
  <table border="1" cellpadding="1" cellspacing="0" width="100%">
  <tr><td class="tab"><p><u>��������� ����</u>: <b>$title</b><br>
  <u>����������� ���</u>: $ttl ����<br>$name, $time $date�.</td>
  <td align="center" width="60" class="tab"><a href="/cgi-bin/forum.cgi?read=0&file=$file">������</a><br><a
  href="/cgi-bin/forum.cgi?add=0&file=$file">��������</a></td></tr>
[END]
}

# �������� ���������� �� �������
sub html_submessage {
 print << "[END]";
  <tr><td><table border="0" cellpadding="0" cellspacing="0"><tr>
  <td width="0">$space</td>
  <td><u>�����</u>: <b>$message</b><br>$name, $time $date�.</font></td></tr></table></td>
  <td align="center"><a href="/cgi-bin/forum.cgi?add=0&file=$file&id=$id">��������</a></font></td></tr>
[END]
}

# ��������� ������ ���� ����
sub html_messagefull {
 print << "[END]";
  <table border="1" cellpadding="1" cellspacing="0" width="100%">
  <tr><td class="tab"><p><u>��������� ����</u>: <b>$title</b><br>
  <u>������������ ����</u>: <b>$message</b><br>
  <u>����������� ���</u>: $ttl ����<br>
  $name, $time $date�.</td>
  <td align="center" width="60" class="tab"><a href="/cgi-bin/forum.cgi?add=0&file=$file">��������</a></font></td></tr>
[END]
}

# ������ �������
sub html_end {
 print << "[END]";
 <hr width="85%">
 <p align="center">����������� �����������: <a href="http://allbbs.virtualave.net/scripts.htm">&quot;AUTO Forum v1.0 Freeware&quot;</a><br>
 Copyright � 2000</p>
 </body>
 </html>
[END]
}

# ����� ���������� ����� ����
sub html_new {
 print << "[END]";
 <p align="center"><font size="4"><b>���������� ����� ����</b></font></p>
 <form action="/cgi-bin/forum.cgi" method="GET">
 <input type="hidden" name="new" value="1">
  <div align="center"><center>
  <table border="0" cellpadding="1" cellspacing="0">
  <tr><td align="right"><u>��������� ����:</u></td>
  <td colspan="2"><input type="text" name="title" size="25" class="forms"></td></tr>
  <tr><td align="right"><u>���� ���:</u></td>
  <td colspan="2"><input type="text" name="name" size="20" class="forms"></td></tr>
  <tr><td align="right"><u>������� �����:</u></td>
  <td colspan="2"><input type="text" name="period" value="14" size="3" class="forms"> ���� (�� ����� 30)</td></tr>
  <tr><td valign="top" align="right"><u>������������ ����:</u></td>
  <td colspan="2"><textarea rows="6" name="message" cols="30" class="forms"></textarea></td></tr>
  <tr><td>&nbsp;</td><td align="center"><input type="submit" value="���������" class="forms"></td>
  <td align="center"><input type="reset" value=" �������� " class="forms"></td></tr>
 </table>
 </center></div>
 </form>
[END]
}

# ����� ������ �� ���������
sub html_add {
 print << "[END]";
 <form method="GET" action="/cgi-bin/forum.cgi">
  <input type="hidden" name="add" value="1">
  <input type="hidden" name="file" value="$file">
  <input type="hidden" name="id" value="$id">
  <div align="center"><center>
  <table border="0" cellpadding="1" cellspacing="0">
  <tr><td align="right"><u>���� ���:</u></td>
  <td colspan="2"><input type="text" name="name" size="20" class="forms"></td></tr>
  <tr><td valign="top" align="right"><u>��� �����:</u></td>
  <td colspan="2"><textarea rows="6" name="message" cols="34" class="forms"></textarea></td></tr>
  <tr><td>&nbsp;</td><td align="center"><input type="submit" value="���������" class="forms"></td>
  <td align="center"><input type="reset" value=" �������� " class="forms"></td></tr>
 </table>
 </center></div>
 </form>
[END]
}

1;
