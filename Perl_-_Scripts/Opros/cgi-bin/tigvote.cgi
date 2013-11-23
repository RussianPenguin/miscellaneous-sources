#!/usr/bin/perl
#tigvote.cgi
#
#TigVote, ver. 1.0
#Tigra
#Home Page - http://www.lgg.ru/~tigra
#E-mail    - tigra@lgg.ru
#------------------------------------
#Copyright (C) 1999, Tigra
#=============================================================

$tagToTitle="<font face=arial size=3><b>"; # Теги для заголовка
$tagToRow="<font face=arial size=2><b>"; # Теги для пунктов
$graphLenght=150; # длина максимального поля графика (в пикселах)
$graphWidth=15; # ширина поля графика (в пикселах)
$submitText="Проголосовать"; # надпись на кнопке отправки формы

$closeIP="yes"; # чтобы один адрес не мог голосовать два раза, значение должно 
                # быть "yes". если "no" - то адрес может голосовать 
                # неограниченное количество раз

# ВНИМАНИЕ!!! Если вы запрещаете голосовать с одного адреса несколько раз,
# то не забывайте при новом голосовании очищать файл со списком адресов!

$showResult="yes"; # показывать ли результаты голосования?
$fileName="../vote.txt"; # файл с вопросами и результатами голосования (путь относительно скрипта)
$fileIP="ip.txt"; # файл со списком IP адресов (путь относительно скрипта)
$pathToImage="../img/"; # путь к картинкам для полей графика (путь относительно скрипта)
$cgiUrl="http://www.lgg.ru/~tigra/cgi-bin/"; # URL каталога cgi-bin
$body="<BODY bgcolor=#ff8000 VLINK=#501000 LINK=#903000 ALINK=#ffff00 background=../back.jpg TEXT=#000000 bgproperties=fixed><center>";

#=============================================================
# проверка на вызов подпрограммы

$in = $ENV{'QUERY_STRING'};
if($in eq 'result'){print "Content-Type: text/html\n\n";result();exit;}
if($in eq 'form'){print "Content-Type: text/html\n\n";form();exit;}


#получение данных из формы и проверка на выбор пункта

read(STDIN, $query, $ENV{'CONTENT_LENGTH'});
@vote=split /=/,$query;


if($query eq ''){print "Content-Type: text/html\n\n";
print "<HTML><HEAD><TITLE>Выберите пункт!</TITLE></HEAD>$body\n";
print "<br><center><h2>Ни один пункт не был выбран!</h2><h3><a href=$ENV{'HTTP_REFERER'}>Вернуться</a></h3></center>";
print "</BODY></HTML>";
exit;}


# проверка IP

if($closeIP eq 'yes'){IPcheck();}


#открытие файла с данными

open FILE,"$fileName";
@fil=<FILE>;
close FILE;


#обработка данных

$punkt=@vote[1];
@temp=split /=/,@fil[$punkt];
@temp[1]++;
@fil[$punkt]=join '=',@temp;
@fil[$punkt]=@fil[$punkt]."\n";


#запись полученного результата в файл

open FILE,">$fileName";

for $i(0..$#fil){
print FILE "@fil[$i]";
}

close FILE;


#ответ после голосования

print "Content-Type: text/html\n\n";
print "<HTML><HEAD><TITLE>Спасибо, Ваш голос засчитан.</TITLE></HEAD>$body\n";

print "<h3>Спасибо, Ваш голос был принят.</h3>\n";
if($showResult eq 'yes'){result();}
print "<h3><a href=$ENV{'HTTP_REFERER'}>Вернуться</a></h3>\n";

print "</BODY></HTML>";

exit;



#------------------------------------
#подпрограмма вывода графика
#------------------------------------

sub result()
{
open FILE,"$fileName";
@fil=<FILE>;
close FILE;


#обработка данных из файла

for $i(1..$#fil){
@temp=split /=/,@fil[$i];
@mess[$i]=@temp[0];@num[$i]=@temp[1];
}

#вычисление графика
#нахождение большего значения, вычисление коэффициента

$max=0;$sum=0;
for $i(1..$#fil){
$sum=$sum+@num[$i];
if(@num[$i]>$max){$max=@num[$i];}
}
if($max==0){$max=1;}
$koeff=$graphLenght/$max;


#построение графика

print "<table border=0>\n";
print "<tr><td colspan=4>$tagToTitle@fil[0]</td></tr>\n";

for $i(1..$#fil){
$width=int(@num[$i]*$koeff);
$percent=0;

if($sum!=0){$percent=@num[$i]/$sum*100;$percent=int($percent*100+0.5)/100;}

$image=$pathToImage.'strip'.$i.'.gif';
if($width==0){print "<tr><td>$tagToRow@mess[$i]</td><td>$tagToRow&nbsp;@num[$i]</td><td>$tagToRow($percent%)</td><td></td></tr>\n";}
else {print "<tr><td>$tagToRow@mess[$i]</td><td>$tagToRow&nbsp;@num[$i]</td><td>$tagToRow($percent%)</td><td><img src=$image height=$graphWidth width=$width></td></tr>\n";}
}
print "<tr><td colspan=4><font face=arial size=1>TigVote powered by <a href=http://www.lgg.ru/~tigra target=_new>Tigra</a></td></tr>";
print "</table>";
}


#------------------------------------
#подпрограмма построения формы
#------------------------------------
sub form()
{
open FILE,"$fileName";
@fil=<FILE>;
close FILE;


#построение формы

$tigvote=$cgiUrl.'tigvote.cgi';
print "<form action=$tigvote method=POST>\n";

print "<table border=0>\n";
print "<tr><td>$tagToTitle@fil[0]</td></tr>\n";

for $i(1..$#fil){
@temp=split /=/,@fil[$i];
print "<tr><td>$tagToRow<input type=radio name=tigvote value=$i>@temp[0]</td></tr>\n";
}

print "<tr><td>$tagToRow<input type=submit value=$submitText></td></tr>\n";
print "<tr><td><font face=arial size=1>TigVote powered by <a href=http://www.lgg.ru/~tigra target=_new>Tigra</a></td></tr>";
print "</table></form>\n";
}


#------------------------------------
#подпрограмма проверки IP
#------------------------------------
sub IPcheck()
{
open FILE,"$fileIP";
@filip=<FILE>;
close FILE;

chomp(@filip);

$ip=$ENV{'REMOTE_ADDR'};

# не пущать, если адрес есть в базе

for $i(0..$#filip){
if(@filip[$i] eq $ip){print "Content-Type: text/html\n\n";
print "<HTML><HEAD><TITLE>Ваш голос не принят!</TITLE></HEAD>$body\n";

print "<center><h2>Ваш голос не был принят, т.к.<br>Вы уже голосовали!</h2>";
if($showResult eq 'yes'){result();}
print "<h3><a href=$ENV{'HTTP_REFERER'}>Вернуться</a></h3>\n</center>";

print "</BODY></HTML>\n";exit;}
}

open FILE,">>$fileIP";
print FILE "$ip\n";
close FILE;
}