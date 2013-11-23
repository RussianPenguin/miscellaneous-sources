############################################################################
#                                  Файл настроек                           #
############################################################################

# Каталог с файлами данных форума
$dirforum = "forum/";
# Имя сайта с форумом
$host="http://127.0.0.1";

# Получаем введенные данные
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

# Получаем текущее время
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

# Блокировка файла (не работает в Windows)
sub filelock {
 flock(DB,2);
}

# Разблокировка файла (не работает в Windows)
sub fileunlock {
 flock(DB,8);
}

# Начало всех HTML страниц
sub html_head {
 print << "[END]";
 <html><head><title>AUTO Forum v1.0 Freeware</title></head>
 <link rel="STYLESHEET" href="/styles.css">
 <style type="text/css">
 <!--
 -->
 </style>
 <body>
 <p align="center"><font size="4"><b>ФОРУМ</b></font></p>
[END]
}

# Короткая информация о теме
sub html_message {
 print << "[END]";
  <table border="1" cellpadding="1" cellspacing="0" width="100%">
  <tr><td class="tab"><p><u>Заголовок темы</u>: <b>$title</b><br>
  <u>Обсуждается еще</u>: $ttl дней<br>$name, $time $dateг.</td>
  <td align="center" width="60" class="tab"><a href="/cgi-bin/forum.cgi?read=0&file=$file">Читать</a><br><a
  href="/cgi-bin/forum.cgi?add=0&file=$file">Ответить</a></td></tr>
[END]
}

# Короткая информация об ответах
sub html_submessage {
 print << "[END]";
  <tr><td><table border="0" cellpadding="0" cellspacing="0"><tr>
  <td width="0">$space</td>
  <td><u>Ответ</u>: <b>$message</b><br>$name, $time $dateг.</font></td></tr></table></td>
  <td align="center"><a href="/cgi-bin/forum.cgi?add=0&file=$file&id=$id">Ответить</a></font></td></tr>
[END]
}

# Полностью читать одну тему
sub html_messagefull {
 print << "[END]";
  <table border="1" cellpadding="1" cellspacing="0" width="100%">
  <tr><td class="tab"><p><u>Заголовок темы</u>: <b>$title</b><br>
  <u>Предлагаемая тема</u>: <b>$message</b><br>
  <u>Обсуждается еще</u>: $ttl дней<br>
  $name, $time $dateг.</td>
  <td align="center" width="60" class="tab"><a href="/cgi-bin/forum.cgi?add=0&file=$file">Ответить</a></font></td></tr>
[END]
}

# Нижние баннеры
sub html_end {
 print << "[END]";
 <hr width="85%">
 <p align="center">Программное обеспечение: <a href="http://allbbs.virtualave.net/scripts.htm">&quot;AUTO Forum v1.0 Freeware&quot;</a><br>
 Copyright © 2000</p>
 </body>
 </html>
[END]
}

# Форма добавления новой темы
sub html_new {
 print << "[END]";
 <p align="center"><font size="4"><b>Добавление новой темы</b></font></p>
 <form action="/cgi-bin/forum.cgi" method="GET">
 <input type="hidden" name="new" value="1">
  <div align="center"><center>
  <table border="0" cellpadding="1" cellspacing="0">
  <tr><td align="right"><u>Заголовок темы:</u></td>
  <td colspan="2"><input type="text" name="title" size="25" class="forms"></td></tr>
  <tr><td align="right"><u>Ваше имя:</u></td>
  <td colspan="2"><input type="text" name="name" size="20" class="forms"></td></tr>
  <tr><td align="right"><u>Удалить через:</u></td>
  <td colspan="2"><input type="text" name="period" value="14" size="3" class="forms"> дней (не более 30)</td></tr>
  <tr><td valign="top" align="right"><u>Предлагаемая тема:</u></td>
  <td colspan="2"><textarea rows="6" name="message" cols="30" class="forms"></textarea></td></tr>
  <tr><td>&nbsp;</td><td align="center"><input type="submit" value="Сохранить" class="forms"></td>
  <td align="center"><input type="reset" value=" Очистить " class="forms"></td></tr>
 </table>
 </center></div>
 </form>
[END]
}

# Форма ответа на сообщение
sub html_add {
 print << "[END]";
 <form method="GET" action="/cgi-bin/forum.cgi">
  <input type="hidden" name="add" value="1">
  <input type="hidden" name="file" value="$file">
  <input type="hidden" name="id" value="$id">
  <div align="center"><center>
  <table border="0" cellpadding="1" cellspacing="0">
  <tr><td align="right"><u>Ваше имя:</u></td>
  <td colspan="2"><input type="text" name="name" size="20" class="forms"></td></tr>
  <tr><td valign="top" align="right"><u>Ваш ответ:</u></td>
  <td colspan="2"><textarea rows="6" name="message" cols="34" class="forms"></textarea></td></tr>
  <tr><td>&nbsp;</td><td align="center"><input type="submit" value="Сохранить" class="forms"></td>
  <td align="center"><input type="reset" value=" Очистить " class="forms"></td></tr>
 </table>
 </center></div>
 </form>
[END]
}

1;
