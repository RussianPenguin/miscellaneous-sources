#!/usr/bin/perl

# White Tiger WWW Board ver.2.933b (or higher)
# система wwwboard. Разработка, реализация
# (C) 1998-2000, White Tiger (2:5049/91.38; 
# email:wtiger@mail.ru; http://wtiger.ncport.ru)
# wtbdev.cgi - модуль отображения параметров инициализации
# и внутренних переменных
# wtbdev.cgi - script for indicating of initialisation parameters
# and internal values

# замена переменных производится в файле wtbext.cgi
# you must change values in the wtbext.cgi













print "Content-type: TEXT/HTML\n\n";
# прочие величины
if(!-e"wtbext.cgi"){print "\nError: not found wtbext.cgi";exit}
require "wtbext.cgi";
params(5);

if($internalversion<2501){print "\n<html><title>Old version</title>Old version of WTBoard</html>";exit;}


print "\n<html><title>Параметры WTBoard</title>
<body bgcolor=$errbgcolor text=$errtcolor background=$errimg>
<h2>Параметры WTBoard</h2>
<p>

<table width=100% border=0>";



print "<tr><td colspan=2><b>Параметры командной строки</b></td></tr>\n";
#@a=split(/&/,$cs);
#for(@a){s/&/&amp;/g};for(@a){s/</&lt;/g};for(@a){s/>/&gt;/g};for(@a){s/ /&nbsp;/g};

for$i(0..@a)
{	if(length$a[$i]<=0){next}
	($s1,$s2)=split(/=/,$a[$i],2);
	replacx($s1);replacx($s2);
	$s2=~s/\\/\\\\/g;
	$s2=~s/\'/\\\'/g;
	if(defined eval "if(not defined \$$s1){\$$s1=\'$s2\';};"){print "<tr><td>\$$s1=</td><td>$s2</td></tr>\n";}
}


for(@ini){s/&/&amp;/g};for(@ini){s/</&lt;/g};for(@ini){s/>/&gt;/g};for(@ini){s/ /&nbsp;/g};

print "<tr><td colspan=2>&nbsp;<br><b>Параметры конфигурационного файла</b></td></tr>\n";

for$i(0..@ini)
{	if(index($ini[$i],';')==0){next}
	if(index($ini[$i],'[')==0){next}
	if(length$ini[$i]<=0){next}

	$ini[$i]=~s/\'/\\\'/g;

	($a,$b)=split('=',$ini[$i],2);
	print "<tr><td>\$$a=</td><td>$b</td></tr>\n";

}

$,=' |';
$hstring=~s/&/&amp;/g;$hstring=~s/</&lt;/g;$hstring=~s/>/&gt;/g;$hstring=~s/ /&nbsp;/g;
$fstring=~s/&/&amp;/g;$fstring=~s/</&lt;/g;$fstring=~s/>/&gt;/g;$fstring=~s/ /&nbsp;/g;


print "<tr><td colspan=2>&nbsp;<br><b>Содержимое хеша %inip (ключ, значение)</b></td></tr>\n";
@inip=sort(keys%inip);
for(@inip){$inip{$_}=~s/&/&amp;/g;$inip{$_}=~s/>/&gt;/g;$inip{$_}=~s/</&lt;/g;print "<tr><td>\$inip{'$_'}=</td><td>$inip{$_}</td></tr>\n"}

print "<tr><td colspan=2>&nbsp;<br><b>Содержимое хеша %patp (ключ, значение)</b></td></tr>\n";
@inip=sort(keys%patp);
for(@inip){$patp{$_}=~s/&/&amp;/g;$patp{$_}=~s/>/&gt;/g;$patp{$_}=~s/</&lt;/g;print "<tr><td>\$patp{'$_'}=</td><td>$patp{$_}</td></tr>\n"}

print "<tr><td colspan=2>&nbsp;<br><b>Прочие внутренние рабочие переменные и массивы</b></td></tr>\n";

print "
<tr><td>\$wtbaccess=</td><td>$wtbaccess</td></tr>\n
<tr><td>\$wtbadmin=</td><td>$wtbadmin</td></tr>\n
<tr><td>\$wtblang=</td><td>$wtblang</td></tr>\n
<tr><td>\$wtblast=</td><td>$wtblast</td></tr>\n
<tr><td>\$wtbnames=</td><td>$wtbnames</td></tr>\n
<tr><td>\$wtbnews=</td><td>$wtbnews</td></tr>\n
<tr><td>\$wtboard=</td><td>$wtboard</td></tr>\n
<tr><td>\$wtbreplace=</td><td>$wtbreplace</td></tr>\n
<tr><td>\$wtbstruct=</td><td>$wtbstruct</td></tr>\n
<tr><td>\$wtwrong=</td><td>$wtwrong</td></tr>\n
<tr><td>\$hstring=</td><td>$hstring</td></tr>\n
<tr><td>\$fstring=</td><td>$fstring</td></tr>\n
<tr><td>\@tag=</td><td>",@tag,"</td></tr>\n
<tr><td>\@t=</td><td>",@t,"</td></tr>\n
<tr><td>\@exts=</td><td>",@exts,"</td></tr>\n
<tr><td>\@days=</td><td>",@days,"</td></tr>\n
<tr><td>\@months=</td><td>",@months,"</td></tr>\n
<tr><td>\@allowedtags=</td><td>",@allowedtags,"</td></tr>\n
<tr><td>\@filter=</td><td>",@filter,"</td></tr>\n
<tr><td>\@cookie=</td><td>",@cookie,"</td></tr>\n
<tr><td>\$cookie0=</td><td>$cookie0</td></tr>\n
<tr><td>\$cookie=</td><td>$cookie</td></tr>\n
<tr><td>\$names=</td><td>$names</td></tr>\n
<tr><td>\$pwd=</td><td>$pwd</td></tr>\n
<tr><td>\$mails=</td><td>$mails</td></tr>\n
<tr><td>\$realn=</td><td>$realn</td></tr>\n
<tr><td>\$REMOTE_ADDR=</td><td>$REMOTE_ADDR</td></tr>\n
<tr><td>\$ipaddr=</td><td>$ipaddr</td></tr>\n
<tr><td>\$pars=</td><td>$pars</td></tr>\n
<tr><td>\$utimes=</td><td>$utimes</td></tr>\n
<tr><td>\$restricted=</td><td>$restricted</td></tr>\n
<tr><td>\$curtime=</td><td>$curtime</td></tr>\n
<tr><td>\$newstype=</td><td>$newstype</td></tr>\n
<tr><td>\$version=</td><td>$version</td></tr>\n
<tr><td>\$internalversion=</td><td>$internalversion</td></tr>\n
";



print "</table>
</body></html>";

exit;

