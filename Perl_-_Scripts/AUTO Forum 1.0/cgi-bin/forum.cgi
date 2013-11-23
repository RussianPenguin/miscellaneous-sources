#!/usr/bin/perl

# Подключаем файл с HTML кодами
require "config.cgi";

# Получаем данные
&read_get;

# Получаем текущее время
&get_time;

# Добавление новой темы - форма
if ($FORM{'new'} eq '0') {
 print "Content-type: text/html\n\n";
 &html_head;
 &html_new;
 &html_end;
 exit;
}

# Сохранение новой темы
if ($FORM{'new'} eq '1') {
 if ($FORM{'name'} eq '') { $FORM{'name'}="Кто-то"; }
 if ($FORM{'period'} eq '' || $FORM{'period'} > 30) { $FORM{'period'}="30"; }
 if ($FORM{'title'} eq '' || $FORM{'message'} eq '') {
  print "Location: $host/cgi-bin/forum.cgi?new=0\n\n";
  exit;
 }
 open(DB,"$dirforum/base.txt");
 @base = <DB>;
 close(DB);
 foreach $str (@base) {
  ($date,$time,$file,$period,$name,$title,$message)=split(/\|/,$str);
  $all_file[$file]="1";
 }
 for($i=0; $i<9999; $i++) {
  if ($all_file[$i] eq '') { last; }
 }
 $id=substr("0000$i",length("$i"),4);
 open(DB,">>$dirforum/base.txt");
 &filelock;
 truncate(DB,0);
 print DB "$cur_date\|$cur_time\|$id\|$FORM{'period'}\|$FORM{'name'}\|$FORM{'title'}\|$FORM{'message'}\|\n";
 print DB @base;
 &fileunlock;
 close(DB);
 open(DB,">$dirforum/$id.txt");
 close(DB);
 print "Location: $host/cgi-bin/forum.cgi\n\n";
 exit;
}

# Форма ответа на сообщение
if ($FORM{'add'} eq '0') {
 print "Content-type: text/html\n\n";
 &html_head;
 print "<p align=center><font size=4><b>Ответ на сообщение</b></font></p>";
 open(DB,"$dirforum/base.txt");
 @base = <DB>;
 close(DB);
 foreach $str (@base) {
  ($date,$time,$file,$period,$name,$title,$message)=split(/\|/,$str);
  if ($FORM{'file'} eq "$file") {
   ($day,$mon,$year) = split(/\./,$date);
   $ttl = $year*365 + $mon*30 + $day;
   $ttl = $period - ($cur_year*365 + $cur_mon*30 + $cur_day - $ttl);
   &html_message;
   open(DB,"$dirforum/$file.txt");
   @totals = <DB>;
   close(DB);
   foreach $tmp (@totals) {
    ($id,$name,$time,$date,$message)=split(/\|/,$tmp);
    if ($FORM{'id'} eq "$id") {
     $message =~ s/\S*\w+@\w+\S*/<a href=\"mailto:$&\">$&<\/a>/gi;
     $message =~ s/\s*http:\/\/\S*/ <a href=\"$&\" target=\"_blank\">$&<\/a>/gi;
     $message =~ s/\s*ftp:\/\/\S*/ <a href=\"$&\" target=\"_blank\">$&<\/a>/gi;
     for($c=0, $space=""; $c<length($id); $c++) { $space="$space&nbsp;&nbsp;";  }
     &html_submessage;
    }
   }
  }
 }
 $file=$FORM{'file'};
 $id=$FORM{'id'};
 print "</table><br>";
 &html_add;
 &html_end;
 exit;
}

# Сохранение ответа на сообщение
if ($FORM{'add'} eq '1') {
 if ($FORM{'name'} eq '') { $FORM{'name'}="Кто-то"; }
 if ($FORM{'message'} eq '') {
  print "Location: $host/cgi-bin/forum.cgi\n\n";
  exit;
 }
 $file=$FORM{'file'};
 $cur_id=$FORM{'id'};
 open(DB,"$dirforum/$file.txt");
 @totals = <DB>;
 close(DB);
 foreach $str (@totals) {
  ($id,$name,$time,$date,$message)=split(/\|/,$str);
  $all_id{$id}="1"; 
 }
 for($i=1; ; $i++) {
  $index_name="$cur_id\.$i";
  if ($all_id{$index_name} eq '') { last; }
 }
 open(DB,">$dirforum/$file.txt");
 &filelock;
 if ($cur_id eq '') {
  truncate(DB,0);
  print DB "$index_name\|$FORM{'name'}\|$cur_time\|$cur_date\|$FORM{'message'}\|\n";
  print DB @totals;
 }
 else {
  $i=0;
  foreach $str (@totals) {
   ($id,$name,$time,$date,$message)=split(/\|/,$str);
   if ($cur_id eq "$id") {
    $newtotals[$i]="$id\|$name\|$time\|$date\|$message\|\n";
    $i++;
    $newtotals[$i]="$index_name\|$FORM{'name'}\|$cur_time\|$cur_date\|$FORM{'message'}\|\n";
    $i++;
   }
   else {
    $newtotals[$i]="$id\|$name\|$time\|$date\|$message\|\n";
    $i++;
   }
  }
  truncate(DB,0);
  print DB @newtotals;
 }
 &fileunlock;
 close(DB);
 print "Location: $host/cgi-bin/forum.cgi\n\n";
 exit;
}

# Читаем одну тему
if ($FORM{'read'} eq '0') {
 print "Content-type: text/html\n\n";
 &html_head;
 print "<p align=center><b><a href=\"/cgi-bin/forum.cgi\">Все обсуждаемые темы</a></b></p>";
 open(DB,"$dirforum/base.txt");
 @base = <DB>;
 close(DB);
 foreach $str (@base) {
  ($date,$time,$file,$period,$name,$title,$message)=split(/\|/,$str);
  if ($FORM{'file'} eq "$file") {
   ($day,$mon,$year) = split(/\./,$date);
   $ttl = $year*365 + $mon*30 + $day;
   $ttl = $period - ($cur_year*365 + $cur_mon*30 + $cur_day - $ttl);
   &html_messagefull;
   open(DB,"$dirforum/$file.txt");
   @totals = <DB>;
   close(DB);
   foreach $tmp (@totals) {
    ($id,$name,$time,$date,$message)=split(/\|/,$tmp);
    $message =~ s/\S*\w+@\w+\S*/<a href=\"mailto:$&\">$&<\/a>/gi;
    $message =~ s/\s*http:\/\/\S*/ <a href=\"$&\" target=\"_blank\">$&<\/a>/gi;
    $message =~ s/\s*ftp:\/\/\S*/ <a href=\"$&\" target=\"_blank\">$&<\/a>/gi;
    for($c=0, $space=""; $c<length($id); $c++) { $space="$space&nbsp;&nbsp;";  }
    &html_submessage;
   }
   print "</table><br>";
  }
 }
 &html_end;
 exit;
}

# Начальная страница форума
 print "Content-type: text/html\n\n";
 &html_head;
 print "<p align=center><a href=\"/cgi-bin/forum.cgi?new=0\"><b>Новая тема</b></a></p>";
 open(DB,"$dirforum/base.txt");
 @base = <DB>;
 close(DB);
 foreach $str (@base) {
  ($date,$time,$file,$period,$name,$title,$message)=split(/\|/,$str);
  ($day,$mon,$year) = split(/\./,$date);
  $ttl = $year*365 + $mon*30 + $day;
  $ttl = $period - ($cur_year*365 + $cur_mon*30 + $cur_day - $ttl);
  if ($ttl > 0) {
   $newbase[$i]="$str";
   $i++;
   &html_message;
   open(DB,"$dirforum/$file.txt");
   @totals = <DB>;
   close(DB);
   foreach $tmp (@totals) {
    ($id,$name,$time,$date,$message)=split(/\|/,$tmp);
    for($c=0, $space=""; $c<length($id); $c++) {
     $space="$space&nbsp;&nbsp;";
    }
    if (length($message) > 60) {
     $message=substr("$message",0,60);
     $message="$message...";
    }
    &html_submessage;
   }
  }
  else {
   unlink("$dirforum/$file.txt");
  }
  open(DB,">$dirforum/base.txt");
  &filelock;
  truncate(DB,0);
  print DB @newbase;
  &fileunlock;
  close(DB);
  print "</table><br>";
 }
&html_end;
exit;
