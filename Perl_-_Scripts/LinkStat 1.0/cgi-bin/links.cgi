#!/usr/local/bin/perl

# Получаем ссылку
$link="$ENV{'QUERY_STRING'}";
$link=~tr/A-Z/a-z/;
$file="links.txt";

# Получаем время и дату
($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst)=localtime(time);
$mon++;
$year+=1900;
if ($mday<10) { $mday="0$mday"; }
if ($mon<10) { $mon="0$mon"; }
if ($min<10) { $min="0$min"; }
$date="$hour:$min $mday-$mon-$year";

# Читаем файл
open(DB,"$file");
@totals=<DB>;
close(DB);

# Сохраняем статистику
if ($link ne '') {
 $i=0;
 $ok=0;
 foreach $str (@totals) {
  ($count,$cur_link,$tmp,$start_date)=split(/\|/,$str);
  if ($cur_link eq "$link") {
   $count++;
   $newtotals[$i]="$count\|$cur_link\|$date\|$start_date\|\n";
   $ok=1;
  }
  else {
   $newtotals[$i]="$str";
  }
  $i++;
 }
 open(DB,">$file");
 flock(DB,2);
 truncate(DB,0);
 if ($ok==0) {
  print DB "1\|$link\|$date\|$date\|\n";
 }
 print DB @newtotals;
 flock(DB,8);
 close(DB);
# Переход по ссылке
 print "Location: $link\n\n";
}
else {
# Выводим статистику
 print "Content-type: text/html\n\n";
 print << "[HEAD]";
  <html><head>
  <title>LinkStat v1.0 FREEWARE</title>
  <link rel="STYLESHEET" href="/style.css">
  <style type="text/css">
  <!--
  -->
  </style>
  </head>
  <body>
  <div align=center><center>
  <table border="1" cellspacing="0" cellpadding="2">
  <tr><td align=center rowspan="2" class="head"><u>№</u></td>
  <td align=center rowspan="2" class="head"><u>Ссылки</u></td>
  <td align=center colspan="3" class="head"><u>Обращения</u></td></tr>
  <tr><td align=center class="head"><u>Кол-во</u></td>
  <td align=center class="head"><u>Последнее</u></td>
  <td align=center class="head"><u>Первое</u></td></tr>
[HEAD]
 $i=1;
 foreach $str (sort {$b <=> $a} @totals) {
  ($count,$cur_link,$old_date,$start_date)=split(/\|/,$str);
  print "<tr><td align=center>$i</td>";
  print "<td><a href=\"$cur_link\" target=\"_blank\">$cur_link</a></td>";
  print "<td align=center>$count</td>";
  print "<td align=center>$old_date</td>";
  print "<td align=center>$start_date</td></tr>";
  $i++;
 }
 print << "[END]";
  </table></center></div>
  <p align="center">Программное обеспечение: &quot;<a href="http://allbbs.virtualave.net/scripts.htm">LinkStat v1.0 FREEWARE</a>&quot;</p>
  </body></html>
[END]
}

exit;
