#!/usr/bin/perl

# White Tiger WWW Board ver.2.1b
# система wwwboard. Разработка, реализация
# (C) 1998-1999, White Tiger (2:5049/81.38; 
# email:wtiger@mail.ru; http://wtiger.ncport.ru)
# wtboard.cgi - модуль обеспечения работы форума

# =================================================
# Здесь произвести необходимую коррекцию пути к каталогу данных
# и название общего файла данных. Путь к каталогу должен быть либо
# относительным, либо абсолютным физическим на жестком диске.
# Correct the path to directory with datafiles and name of common ini-file.
# The directory path have been relative or absolute physical on the HDD.
$data='../data';	# ПРЯМОЙ ПУТЬ К КАТАЛОГУ, СОДЕРЖАЩЕМУ ФАЙЛЫ ДАННЫХ
			# DIRECT PATH TO THE DIRECTORY WITH DATAFILES
$wtbini='wtbini.txt';	# НАЗВАНИЕ ОБЩЕГО ФАЙЛА ДАННЫХ
			# NAME OF COMMON INI-FILE
# =================================================
# далее ничего менять не нужно
# do not change after this



# прочие величины
print "Content-type: TEXT/HTML \n";
$t1='<html><title>';
$i1='<input type';
$cr=chr(0x0D).chr(0x0A);
$crl=chr(0x0D);
#$lf=chr(0x0D);
$c=chr(0x0D);
@t=localtime;$t[4]=$t[4]+1;
use Env qw(REMOTE_ADDR);
$ipaddr=$REMOTE_ADDR;
$cookie=$ENV{'HTTP_COOKIE'};
chop $ipaddr;
$pars='';
$utimes=$t[0]+($t[1]+($t[2]+($t[3]+($t[4]+$t[5]*12)*31)*24)*60)*60;
@exts=('htm','html','shtml','stm');

# чтение данных
use Env qw(CONTENT_LENGTH);
read STDIN,$cs,$CONTENT_LENGTH;

if($CONTENT_LENGTH <= 0){use Env qw(QUERY_STRING);$cs=$QUERY_STRING;}

@a=split(/[&=]/,$cs);


# идентификатор форума
$fid=0;
for $i(0..$#a){if($a[$i] eq 'fid'){$fid=$a[$i+1];last}}

open DAT,"$data/$wtbini";@lng=<DAT>;close DAT;chomp @lng;
for $i(0..$#lng)
{	@b=split(/;/,$lng[$i]);
	if($fid==$b[0])
	{	$wtbaccess=$b[1];
#		$wtbadmin=$b[2];
		$wtblang=$b[3];
		$wtblast=$b[4];
		$wtbnames=$b[5];
#		$wtbnews=$b[6];
		$wtboard=$b[7];
		$wtbreplace=$b[8];
		$wtbstruct=$b[9];
		$wtwrong=$b[10];
		last;
	}
}
undef @lng;undef @b;

open DAT,"$data/$wtblang";@lng=<DAT>;close DAT;chomp @lng;


# ini-данные конференции
$private='noprivate';$quote='>';$substip='on';$setsize='off';$addip='off';
$notag=0;$usecookie='on';$quoting='on';$individual='on';
$includeform='off';$ext='shtml';$reply='Re';$paragraph='<dd>';
$selectnew=360;$nulcolor='#0000ff';$selectnul='on';
#$userstat='on';$ipuserstat='off';$ignorstat='off';
$selecttag=" <font color=#ff0000><b>New</b></font>";
$hr="<hr size=1 width=80% align=center>";$quotebeg='<i>';$quoteend='</i>';
$seturl='on';

open DAT,"$data/$wtboard";@ini=<DAT>;close DAT;
chomp @ini;
for $i(0..$#ini)
{	if(index($ini[$i],'thekonf=')==0){($a,$thekonf)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'tokonf=')==0){($a,$tokonf)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'ofkonf=')==0){($a,$ofkonf)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'onkonf=')==0){($a,$onkonf)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'admin=')==0){($a,$admin)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'private=')==0){($a,$private)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'quote=')==0){($a,$quote)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'quotebeg=')==0){($a,$quotebeg)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'quoteend=')==0){($a,$quoteend)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'reply=')==0){($a,$reply)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'quoting=')==0){($a,$quoting)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'substip=')==0){($a,$substip)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'usecookie=')==0){($a,$usecookie)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'setsize=')==0){($a,$setsize)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'addip=')==0){($a,$addip)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'notag=')==0){($a,$notag)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'selectnew=')==0){($a,$selectnew)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'selectnul=')==0){($a,$selectnul)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'individual=')==0){($a,$individual)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'includeform=')==0){($a,$includeform)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'ext=')==0){($a,$ext)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'paragraph=')==0){($a,$paragraph)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'hr=')==0){($a,$hr)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'seturl=')==0){($a,$seturl)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'nulcolor=')==0){($a,$nulcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'indbgcolor=')==0){($a,$indbgcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'indtcolor=')==0){($a,$indtcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'indlcolor=')==0){($a,$indlcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'indvlcolor=')==0){($a,$indvlcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'indalcolor=')==0){($a,$indalcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'indimg=')==0){($a,$indimg)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'mesbgcolor=')==0){($a,$mesbgcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'mestcolor=')==0){($a,$mestcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'meslcolor=')==0){($a,$meslcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'mesvlcolor=')==0){($a,$mesvlcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'mesalcolor=')==0){($a,$mesalcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'mesimg=')==0){($a,$mesimg)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'errbgcolor=')==0){($a,$errbgcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'errtcolor=')==0){($a,$errtcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'errlcolor=')==0){($a,$errlcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'errvlcolor=')==0){($a,$errvlcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'erralcolor=')==0){($a,$erralcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'errimg=')==0){($a,$errimg)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'lenlogin=')==0){($a,$lenlogin)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'lenpass=')==0){($a,$lenpass)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'lenemailmes=')==0){($a,$lenemailmes)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'lenemailans=')==0){($a,$lenemailans)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'lensubj=')==0){($a,$lensubj)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'lenrows=')==0){($a,$lenrows)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'lencols=')==0){($a,$lencols)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'lenurl=')==0){($a,$lenurl)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'lentitleurl=')==0){($a,$lentitleurl)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'lenimg=')==0){($a,$lenimg)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'dirkonf=')==0){($a,$dirkonf)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'dirrealkonf=')==0){($a,$dirrealkonf)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'dircgi=')==0){($a,$dircgi)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'selecttag=')==0){($a,$selecttag)=split(/=/,$ini[$i],2);}
}
for $i(0..$#ini)
{	$ini[$i]=~s/\$thekonf/$thekonf/g;
	$ini[$i]=~s/\$tokonf/$tokonf/g;
	$ini[$i]=~s/\$onkonf/$onkonf/g;
	$ini[$i]=~s/\$ofkonf/$ofkonf/g;
	$ini[$i]=~s/\$dirkonf/$dirkonf/g;
	$ini[$i]=~s/\$dirrealkonf/$dirrealkonf/g;
	$ini[$i]=~s/\$dircgi/$dircgi/g;
	$ini[$i]=~s/\$admin/$admin/g;
	$ini[$i]=~s/\$indbgcolor/$indbgcolor/g;
	$ini[$i]=~s/\$indtcolor/$indtcolor/g;
	$ini[$i]=~s/\$indlcolor/$indlcolor/g;
	$ini[$i]=~s/\$indvlcolor/$indvlcolor/g;
	$ini[$i]=~s/\$indalcolor/$indalcolor/g;
	$ini[$i]=~s/\$indimg/$indimg/g;
	$ini[$i]=~s/\$mesbgcolor/$mesbgcolor/g;
	$ini[$i]=~s/\$mestcolor/$mestcolor/g;
	$ini[$i]=~s/\$meslcolor/$meslcolor/g;
	$ini[$i]=~s/\$mesvlcolor/$mesvlcolor/g;
	$ini[$i]=~s/\$mesalcolor/$mesalcolor/g;
	$ini[$i]=~s/\$mesimg/$mesimg/g;
	$ini[$i]=~s/\$errbgcolor/$errbgcolor/g;
	$ini[$i]=~s/\$errtcolor/$errtcolor/g;
	$ini[$i]=~s/\$errlcolor/$errlcolor/g;
	$ini[$i]=~s/\$errvlcolor/$errvlcolor/g;
	$ini[$i]=~s/\$erralcolor/$erralcolor/g;
	$ini[$i]=~s/\$errimg/$errimg/g;
	$ini[$i]=~s/\$fid/$fid/g;
	$ini[$i]=~s/\$separator/$hr/g;
	$ini[$i]=~s/\\n/$crl/g;
}
for $i(0..$#ini)
{	if(index($ini[$i],'begmesform=')==0){($a,$begmesform)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'endmesform=')==0){($a,$endmesform)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'begansform=')==0){($a,$begansform)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'endansform=')==0){($a,$endansform)=split(/=/,$ini[$i],2)}
#	if(index($ini[$i],'begindex=')==0){($a,$begindex)=split(/=/,$ini[$i],2)}
#	if(index($ini[$i],'endindex=')==0){($a,$endindex)=split(/=/,$ini[$i],2)}
#	if(index($ini[$i],'begarchive=')==0){($a,$begarchive)=split(/=/,$ini[$i],2)}
#	if(index($ini[$i],'endarchive=')==0){($a,$endarchive)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'begmes=')==0){($a,$begmes)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'endmes=')==0){($a,$endmes)=split(/=/,$ini[$i],2)}
}
undef @ini;


# обработка cookie
$hello='';$goodbye='';
@cookie=split(/[= ;]/,$cookie);
for$i(0..@cookie)
{	if($cookie[$i] eq 'wtboard'){$cookie0=$cookie[$i];$cookie=$cookie[$i+1];}
	if($cookie[$i] eq 'greetings'){($hello,$goodbye)=split('\/\/',$cookie[$i+1]);}
}
$hello=~s/\+/ /g;$goodbye=~s/\+/ /g;
replacx($hello);replacx($goodbye);


# проверка доступа с запрещенного ip-адреса или запрещенного по cookie
open NAM,"$data/$wtbaccess";@b=<NAM>;close NAM;chomp @b;
for $i(0..$#b)
{	@c=split(/;;/,$b[$i]);

	if('-'.$cookie eq $c[0] or '!'.$cookie eq $c[0])
	{print "\n",$t1,"$lng1</title><body bgcolor=$errbgcolor text=$errtcolor background=$errimg><h3>$lng2</h3></body></html>";exit}

	$notip=$REMOTE_ADDR;
	$lng1=$lng[29];
	$lng2=$lng[0];
	if(length $c[1] > 0){$lng1=$c[1]}
	if(length $c[2] > 0){$lng2=$c[2]}
	if(length $c[0]>2)
	{	while(length '-'.$notip>length $c[0]){chop $notip}
		if('-'.$notip eq $c[0] or '!'.$notip eq $c[0])
		{print "\n",$t1,"$lng1</title><body bgcolor=$errbgcolor text=$errtcolor background=$errimg><h3>$lng2</h3></body></html>";exit}
	}
}



# подстановка имени и e-mail
$xlogin='';
$xemail='';

if($substip eq 'on')
{	open NAM,"$data/$wtbnames";
	$i=0;while(<NAM>){chomp;($names[$i],$pwd[$i],$mails[$i],$realn[$i],$ipaddr[$i],$pars[$i],$utimes[$i],$s)=split(';;');++$i;}
	close NAM;$s=0;

	if($usecookie eq 'on' and $cookie0 eq 'wtboard')
	{	for $i(0..$#names)
		{	if($cookie eq $names[$i])
			{	$xlogin=$realn[$i];
				$xemail=$mails[$i];
				$pars=$pars[$i];
				$xpwd=$pwd[$i];
				$s=1;last;
			}
		}
	}

	if($s!=1)
	{	for $i(0..$#names)
		{	if($REMOTE_ADDR eq $ipaddr[$i])
			{	$xlogin=$realn[$i];
				$xemail=$mails[$i];
				$pars=$pars[$i];
				$xpwd=$pwd[$i];
				$s=1;last;
			}
		}
	}
	if($s!=1)
	{	for $i(0..$#names)
		{	if($ipaddr eq $ipaddr[$i])
			{	$xlogin=$realn[$i];
				$xemail=$mails[$i];
				$pars=$pars[$i];
				$s=1;last;
			}
		}
	}
	if($s!=1)
	{	for $i(0..$#names)
		{	chop $ipaddr[$i];
			if($ipaddr eq $ipaddr[$i])
			{	$xlogin=$realn[$i];
				$xemail=$mails[$i];
				$pars=$pars[$i];
				last;
			}
		}
	}
	undef @names;undef @pwd;undef @mails;undef @ipaddr;undef @pars;
	$xlogin=~s/\"/&quot;/g;
	$xemail=~s/\"/&quot;/g;
}

## параметры индивидуальной настройки
# цитирование
if(index($pars,'c')>=0){$citating='off'}
if($individual ne 'on'){$citating='on'}
# использование cookie
if(index($pars,'k')>=0){$ucookie='off'}
if($individual ne 'on'){$ucookie='on'}
# вывод информации о новых сообщениях
if(index($pars,'m')>=0){$unewmes='off'}
if($individual ne 'on'){$unewmes='on'}
# новое окно для этого
if(index($pars,'M')>=0){$unewwinmes='off'}
if($individual ne 'on'){$unewwinmes='on'}
# вывод информации об ответах на сообщения этого участника
if(index($pars,'a')>=0){$unewans='off'}
if($individual ne 'on'){$unewans='on'}
# новое окно для этого
if(index($pars,'A')>=0){$unewwinans='off'}
if($individual ne 'on'){$unewwinans='on'}
# подстановка пароля
if(index($pars,'p')>=0){$setpass='on'}
if($individual ne 'on'){$setpass='off'}
if($setpass ne 'on'){undef $xpwd}
# перенаправление на сообщение
if(index($pars,'r')>=0){$redirect='r'}
# перенаправление на основную страницу
if(index($pars,'R')>=0){$redirect='R'}
if($individual ne 'on'){undef $redirect}
# отказ от показа полей для ссылок
if(index($pars,'h')>=0){$showurl='off'}
if($individual ne 'on'){$showurl='on'}

# если содержатся post-данные: то переходим к приему сообщения, иначе - форма.
# при USER - форма параметров пользователя, при UPDATE - принятие изменений
for $i(0..$#a)
{	if($a[$i] eq 'user'){goto USER;}
	if($a[$i] eq 'update'){goto UPDATE;}
}
if($CONTENT_LENGTH>0){goto SUBMIT}



### генерация формы

for $i(0..$#a)
{	if($a[$i] eq 'root'){$root=$a[$i+1];}
	if($a[$i] eq 'numans'){$numans=$a[$i+1];}
	if($a[$i] eq 'arc'){$arc=$a[$i+1];}
	if($a[$i] eq 'fid'){$fid=$a[$i+1]}
	if($a[$i] eq 'notitle'){$notitle='on'}
}

replacx($root);replacx($numans);replacx($arc);
$arc=~s/\+/ /g;



# распаковка предыдущих номеров
@prev=split(/;/,$numans);
$prev=$prev[$#prev];


if($root eq 'on')
{
$a='';
if($individual eq 'on')
{	if(length $hello>0){$a=$hello.$crl.$crl};
	if(length $goodbye>0){$a=$a.$crl.$crl.$goodbye};
}
if($notitle ne 'on'){print "\n$begmesform"}
if($private eq 'private'){print "\n$lng[45]<p>$hr"}

print"\n<form action=$dircgi/wtboard.cgi method=post><p>
<table align=center width=100% border=0><tr><td>$lng[1]</td> <td>$i1=text name=login size=$lenlogin value=\"$xlogin\"></td>
<td>$lng[2]</td> <td>$i1=password name=pass size=$lenpass value=\"$xpwd\"></td></tr>
<tr><td>E-Mail:</td> <td colspan=3>$i1=text name=email size=$lenemailmes value=\"$xemail\"></td></tr>
$i1=hidden name=root value=on>
<tr><td>$lng[3]</td> <td colspan=3>$i1=text name=subj size=$lensubj></td></tr>
$i1=hidden name=prev value=$numans>
$i1=hidden name=date value=\"";
printf ('%2.2d:%2.2d:%2.2d %2.2d/%2.2d/19%2.2d">',$t[2],$t[1],$t[0],$t[3],$t[4],$t[5]);
if(defined $arc){print "$i1=hidden name=arc value=$arc>";}
print "<tr><td colspan=4 align=center>$lng[4]<br><textarea name=body cols=$lencols rows=$lenrows wrap=virtual>$a</textarea></tr></td>\n";

if($showurl ne 'off' and $seturl eq 'on')
{	print "<tr><td>$lng[5]</td> <td colspan=3>$i1=text name=url value=http:// size=$lenurl></td></tr>
<tr><td>$lng[6]</td> <td colspan=3>$i1=text name=urltitle size=$lentitleurl></td></tr>
<tr><td>$lng[7]</td> <td colspan=3>$i1=text name=img value=http:// size=$lenimg></td></tr>\n";
}

print "</center><tr><td colspan=4>&nbsp;<br><center>$i1=hidden name=fid value=$fid>$i1=submit value=$lng[8]></tr></td>
</table><p>";
if($notitle ne 'on'){print "<center><font size=-1><i><a href=$dircgi/wtboard.cgi?user&fid=$fid>$lng[32]</a></i></font>",$endmesform;}
}

elsif($root eq 'off')
{
for$i(0..3)
{	if(-e "$dirrealkonf/$prev.$exts[$i]"!=1){next}
	open NAM,"$dirrealkonf/$prev.$exts[$i]";@a=<NAM>;close NAM;chomp @a;
	$a[0]=~m/<title>(.*?)<\/title>/i;$them=$1;
}

$them=~s/\"/&quot;/g;
$begansform=~s/\$subj/$them/g;
$endansform=~s/\$subj/$them/g;

$a='';
if($quoting eq 'on' and $citating ne 'off')
{	for $i(0..@a)
	{	if(index($a[$i],$paragraph)==0)
		{	$a=$quote.' '.$a[$i+1];
			chomp $a;
			$a=~s/&nbsp;$paragraph$quotebeg$quote(.*?)$quoteend/&nbsp;$paragraph$quote$1/g;
#			$a=~s/<i>$quote(.*)<\/i>/$quote$1/;
#			$a=~s/<\/i>&nbsp;$paragraph/&nbsp;$paragraph/g;
			$a=~s/&nbsp;$paragraph//;
			$a=~s/&nbsp;$paragraph/$c$quote /g;
			$a=~s/$quote $quote/$quote$quote/g;
			if(length $a<3){$a=''}
		}
	}
}

# замена контекстных вхождений
open NAM,"$data/$wtbreplace";
$i=0;while(<NAM>){chomp;($rd[$i],$rs[$i])=split(';;');$rd[$i]=~s/\\//g;++$i;}
close NAM;
for $i(0..$#rs)
{	$a=~s/$rs[$i]/$rd[$i]/g;
	$subj=~s/$rs[$i]/$rd[$i]/g;
	$login=~s/$rs[$i]/$rd[$i]/g;
#	++$i;
}

if(index($them,"$reply:")!=0 and index($them,"$reply (")!=0){$them="$reply: ".$them}
elsif(index($them,"$reply:")==0){$them=~s/$reply:/$reply (2):/;}
else{$them=~s/$reply \((\d+)\)/join('',"$reply \(",$1+1,')')/eg;}

if($notitle eq 'on' and $includeform eq 'on'){$a=''}
if($individual eq 'on')
{	if(length $hello>0){$a=$hello.$crl.$crl.$a};
	if(length $goodbye>0){$a=$a.$crl.$crl.$goodbye};
}
if($notitle ne 'on'){print "\n$begansform";}
if($private eq 'private'){print "\n$lng[45]<p>$hr"}
print "\n<form action=$dircgi/wtboard.cgi method=post><p>
<table width=100% align=center border=0>
<tr><td>$lng[1]</td> <td>$i1=text name=login size=$lenlogin value=\"$xlogin\"></td>
<td>$lng[2]</td> <td>$i1=password name=pass size=$lenpass value=\"$xpwd\"></td></tr>
<tr><td>E-Mail:</td> <td>$i1=text name=email size=$lenemailans value=\"$xemail\"></td>
<td>$lng[9]</td> <td>$i1=checkbox name=nroot unchecked></td></tr>
<tr><td>$lng[3]</td> <td colspan=3>$i1=text name=subj size=$lensubj value=\"$them\"></td></tr>
$i1=hidden name=prev value=$numans>
$i1=hidden name=root value=off>
$i1=hidden name=date value=\"";
printf ('%2.2d:%2.2d:%2.2d %2.2d/%2.2d/19%2.2d">',$t[2],$t[1],$t[0],$t[3],$t[4],$t[5]);
print "<tr><td colspan=4 align=center>$lng[4]<br><textarea name=body cols=$lencols rows=$lenrows wrap=virtual>$a</textarea></tr></td>\n";

if($showurl ne 'off' and $seturl eq 'on')
{	print "<tr><td>$lng[5]</td> <td colspan=3>$i1=text name=url value=http:// size=$lenurl></td></tr>
<tr><td>$lng[6]</td> <td colspan=3>$i1=text name=urltitle size=$lentitleurl></td></tr>
<tr><td>$lng[7]</td> <td colspan=3>$i1=text name=img value=http:// size=$lenimg></td></tr>\n";
}

print "</center><tr><td colspan=4>&nbsp;<br><center>$i1=hidden name=fid value=$fid>$i1=submit value=$lng[8]></tr></td>
</table><p>";
if($notitle ne 'on')
{	if($individual eq 'on'){print "<center><font size=-1><i><a href=$dircgi/wtboard.cgi?user&fid=$fid>$lng[32]</a></i></font>"};
	print $endansform;
}

undef $a;
}
else
{print "\n$t1$lng[46]</title><body bgcolor=$errbgcolor text=$errtcolor background=$errimg>$lng[47]<P></body></html>";}


exit;

### прием сообщения, проверка пароля, внесение в базу
SUBMIT:

for $i(0..$#a)
{	$a[$i]=~s/\+/ /g;
	replacx($a[$i]);
}

$body='';
for $i(0..$#a)
{	if($a[$i] eq 'login'){$login=$a[$i+1]}
	if($a[$i] eq 'pass'){$pass=$a[$i+1]}
	if($a[$i] eq 'email'){$email=$a[$i+1]}
	if($a[$i] eq 'subj'){$subj=$a[$i+1]}
	if($a[$i] eq 'root'){$root=$a[$i+1]}
	if($a[$i] eq 'body'){$body=$a[$i+1]}
	if($a[$i] eq 'url'){$url=$a[$i+1]}
	if($a[$i] eq 'urltitle'){$urltitle=$a[$i+1]}
	if($a[$i] eq 'img'){$img=$a[$i+1]}
	if($a[$i] eq 'date'){$date=$a[$i+1]}
	if($a[$i] eq 'prev'){$numans=$a[$i+1]}
	if($a[$i] eq 'nroot'){$them=$a[$i+1]}
	if($a[$i] eq 'arc'){$arc=$a[$i+1]}
}
undef @a;

if(length $urltitle<1){$urltitle=$url}
if($them eq 'on'){$root='on'}
@prev=split(/;/,$numans);
$prev=$prev[$#prev];

# замена <<text>> на "text"
$body=~s/<<(.*?)>>/&#171;$1&#187;/g;
# обработка тегов в body
# 0 - не трогать теги, 1 - преобразовывать в текст, 2 - удалять нафиг
if($notag==0){$body=$body;}
elsif($notag==1){$body=~s/<(.*?)>/&lt;$1&gt;/g;}
elsif($notag==2){$body=~s/<(.*?)>//g;}

# замена контекстных вхождений
open NAM,"$data/$wtbreplace";
$i=0;while(<NAM>){chomp;($rs[$i],$rd[$i])=split(';;');++$i;}
close NAM;
for $i(0..$#rs)
{	$body=~s/$rs[$i]/$rd[$i]/g;
	$subj=~s/$rs[$i]/$rd[$i]/g;
	$urltitle=~s/$rs[$i]/$rd[$i]/g;
	$url=~s/$rs[$i]/$rd[$i]/g;
	$img=~s/$rs[$i]/$rd[$i]/g;
	$login=~s/$rs[$i]/$rd[$i]/g;
	++$i;
}
$lenbody=length $body;

$subj=~s/<(.*?)>/&lt;$1&gt;/g;
$login=~s/<(.*?)>/&lt;$1&gt;/g;
$email=~s/<(.*?)>/&lt;$1&gt;/g;

# наличие полей
if(length $login<=0 or length $pass<=0 or length $subj<=0)
{print "\n$t1 $lng[30]</title><body bgcolor=$errbgcolor text=$errtcolor background=$errimg>$lng[10]</body></html>";exit;}


### проверка имени, пароля, если надо - внесение в базу
# коррекция имени
$logs=$login;
correct($logs);
open NAM,"$data/$wtbnames";
$i=0;while(<NAM>){chomp;($names[$i],$pwd[$i],$mails[$i],$realn[$i],$ipaddr[$i],$pars[$i],$utimes[$i],$s)=split(';;');++$i;}
close NAM;

for $i(0..$#names)
{	if($logs eq $names[$i])
	{	$cur=$i;
		if($pass ne $pwd[$i])
		{	open NAM,">>$data/$wtwrong";
			print NAM "WRONG Log=$login; Pwd=$pass; Host=$REMOTE_ADDR; Time=";
			printf NAM ('%2.2d:%2.2d:%2.2d %2.2d/%2.2d/19%2.2d',$t[2],$t[1],$t[0],$t[3],$t[4],$t[5]);
			print NAM "\n";
			print "\n",$t1,"$lng[33]</title><body bgcolor=$errbgcolor text=$errtcolor background=$errimg>$lng[11]</body></html>";
			exit;
		}
		$member=1;

		$mails[$cur]=$email;
		$ipaddr[$cur]=$REMOTE_ADDR;
		$realn[$cur]=$login;
#		$utimes[$cur]=$utimes;
		rename "$data/$wtbnames","$data/$wtbnames.old";
		open NAM,">$data/$wtbnames";for $j(0..$#names){print NAM "$names[$j];;$pwd[$j];;$mails[$j];;$realn[$j];;$ipaddr[$j];;$pars[$j];;$utimes[$j];;\n"};close NAM;
		if(-z "$data/$wtbnames"==1){rename "$data/$wtbnames.old","$data/$wtbnames";}

		if($usecookie eq 'on' and $cookie ne $logs)
		{	print "Set-Cookie: wtboard=$logs; path=/; expires=Wednesday, 08-Dec-19 23:59:59 GMT\n";
		}
	}
}
undef @nam;undef @pwd;undef @mails;

if($member!=1)
{	if($private eq 'private'){print "\n$t1 $lng[29]</title><body bgcolor=$errbgcolor text=$errtcolor link=$errlcolor vlink=$errvlcolor alink=$erralcolor background=$errimg>$lng[12] <a href=\"mailto:$admin\">$lng[13]</body></title>";exit;}
	open NAM,"$data/$wtbnames";@a=<NAM>;close NAM;
	rename "$data/$wtbnames","$data/$wtbnames.old";
	open NAM,">>$data/$wtbnames";print NAM @a,"$logs;;$pass;;$email;;$login;;$REMOTE_ADDR;;;;$utimes;;\n";close NAM;
	if(-z "$data/$wtbnames"==1){rename "$data/$wtbnames.old","$data/$wtbnames";}
	open NAM,">>$data/$wtwrong";
	print NAM "REGST Log=$login; Pwd=$pass; Host=$REMOTE_ADDR; Email=$email; Time=";
	printf NAM ('%2.2d:%2.2d:%2.2d %2.2d/%2.2d/19%2.2d',$t[2],$t[1],$t[0],$t[3],$t[4],$t[5]);
	print NAM "\n";
	close NAM;
}


### обработка сообщения

$body=$cr.$body;
#$body=~s/$crl/$cr/g;
$body=~s/$cr/\n/g;
$body=~s/\n$quote(.*)/\n$quotebeg$quote$1$quoteend/g;
$body=~s/\n/&nbsp;$paragraph/g;


#$body=$body.'</i>';
#$body=~s/&nbsp;$paragraph$quote/&nbsp;$paragraph$quotebeg$quote/g;
#if(index($body,$quote)<=1){$body=~s/$quote/$quotebeg$quote/}


# проверка наличия подобного сообщения
$s="$subj</a> &#151; <b>$login</b> <i>$date";
open NAM,"$dirrealkonf/index.shtml";@a=<NAM>;close NAM;
for $i(0..$#a)
{$a[$i]=~s/<font color=\"$nulcolor\">//;$a[$i]=~s/<\/font>//;if(index($a[$i],$s)>0){$a[$i]=~s/<a href=/<a href=$dirkonf\//;$a[$i]=~s/$selecttag//;print "\n<html><title>Message already present!</title><body bgcolor=$errbgcolor text=$errtcolor link=$errlcolor vlink=$errvlcolor alink=$erralcolor background=$errimg>$lng[28]<p>$a[$i]</body></html>";exit;}}
undef @a;


# выяснение и запись номера последнего сообщения
open NAM,"$data/$wtblast";$lastmes=<NAM>;close NAM;
$file=($lastmes+1).".$ext";++$lastmes;
$i=-e "$dirrealkonf/$file";while($i==1){++$lastmes;$file=$lastmes.".$ext";$i=-e "$dirrealkonf/$file";}
open NAM,">$data/$wtblast";print NAM $lastmes;close NAM;


if($root eq 'on' and not defined $them)
{
### генерация корневого сообщения

$command="root=off&fid=$fid&numans=$lastmes";
$begmes=~s/\$subj/$subj/g;
$begmes=~s/\$command/$command/g;
$endmes=~s/\$subj/$subj/g;
$endmes=~s/\$command/$command/g;
open FILE,"+>$dirrealkonf/$file";
print FILE "$begmes\n<!--endhome-->
$lng[14]";

length $email > 0 ? print FILE "<a href=\"mailto:$email\">$login</a>" : print FILE $login;

print FILE "</b> <i>$date</i>:\n<p><div align=justify>\n";

if(defined $arc){print FILE "$lng[15]<a href=$arc>$lng[16]</a>.<p>\n";}

if(length $img>=8){@c=split(/[\/\\]/,$img);print FILE "<center><img src=\"$img\" border=1 alt=\"$c[$#c]\"></center><p>\n";}

print FILE "$paragraph\n$body\n<p>";

if(length $url>=8){print FILE "<ul><li><a href=\"$url\">$urltitle<\/a></ul><p>\n";}
if($addip eq 'on'){print FILE "<div align=right><font size=-1><i>Отправлено с IP-адреса $REMOTE_ADDR</i></font></div><p>"}
print FILE "<center>$hr</center>
<p><a name=ans>$lng[17]</a><p>
</div><div align=left>
<ul>
<!--home-->
<!--$lastmes-->
<!--end-->
</ul>
<!--homeend-->\n";

if($includeform eq 'on' and $ext ne 'htm' and $ext ne 'html')
{print FILE "<p>$hr<p><center><!--#include virtual=\"$dircgi/wtboard.cgi?$command&notitle\"--></center><p>";}

print FILE $endmes;
close FILE;


# обновление файла структуры
open NAM,"$data/$wtbstruct";@c=<NAM>;close NAM;
open NAM,">$data/$wtbstruct";
$i=0;
if(defined $arc){print NAM "\n,";}
print NAM "\n.$lastmes";
print NAM @c;
close NAM;undef @c;undef @b;


### регистрация корневого сообщения на основной странице
open FILE,"$dirrealkonf/index.shtml";@a=<FILE>;close FILE;
open FILE,"+>$dirrealkonf/index.shtml";
for $i(0..$#a)
{	if($selectnew>0 and index($a[$i],$selecttag)>0)
	{	$a[$i]=~m/<\/b> <i>(.{19}?)/;$t=$1;$t=~s/\/19/\//;counts($t);
		if($t<$utimes-$selectnew*60){$a[$i]=~s/$selecttag//;}
	}
	print FILE $a[$i];
	$j=index $a[$i],"<!--home-->";
	if($j>=0)
	{	if(defined $arc){print FILE "<!--$lastmes--><li>** ";}
		else{print FILE "<!--$lastmes--><li>";}

		print FILE "<a href=$file>";
		if($lenbody<1 and $selectnul eq 'on'){print FILE "<font color=\"$nulcolor\">"};
		print FILE $subj;
		if($lenbody<1 and $selectnul eq 'on'){print FILE "</font>"};
		print FILE "</a> &#151; <b>$login</b> <i>$date ";
		if($setsize eq 'on'){print FILE "[$lenbody $lng[31]] ";}
		print FILE "</i>(0)";
		if($selectnew>0){print FILE $selecttag}
		print FILE "\n";
	}
}
close FILE;
}
else
{
### генерация ответного сообщения

$prev[$#prev+1]=$lastmes;
$numans=join ';',@prev;


$command="root=off&fid=$fid&numans=$numans";
$begmes=~s/\$subj/$subj/g;
$begmes=~s/\$command/$command/g;
$endmes=~s/\$subj/$subj/g;
$endmes=~s/\$command/$command/g;
open FILE,"+>$dirrealkonf/$file";
print FILE $begmes,"\n<!--endhome-->
$lng[14]";
length $email > 0 ? print FILE "<a href=\"mailto:$email\">$login</a>" : print FILE $login;
print FILE "</b> <i>$date</i>\n<br>";

$k=$prev[$#prev-1];$c=chop $lng[4];
for$i(0..3)
{	if(-e "$dirrealkonf/$prev.$exts[$i]"!=1){next}
	open NAM,"$dirrealkonf/$k.$exts[$i]";@a=<NAM>;close NAM;$is=$i;
}
for $i(0..$#a){if(index($a[$i],$lng[14])==0){$s=$i;last}}
$a[0]=~m/<title>(.*?)<\/title>/;$c=$1;
chomp $a[$s];
$a[$s]=~s/$lng[14]/$lng[18]/;
$a4="<div align=left>$lng[19]<a href=$k.$exts[$is]>$c</a>, $a[$s]<p>";
print FILE "$a4 <div align=justify>\n";
undef @a;
if(length $img>=8){@c=split(/[\/\\]/,$img);print FILE "<center><img src=\"$img\" border=1 alt=\"$c[$#c]\"></center><p>\n";}

print FILE "$paragraph\n$body\n<p>";

if(length $url>=8){print FILE "<ul><li><a href=\"$url\">$urltitle<\/a></ul><p>\n";}
if($addip eq 'on'){print FILE "<div align=right><font size=-1><i>Отправлено с IP-адреса $REMOTE_ADDR</i></font></div><p>"}
print FILE "<center>$hr</center>
<p><a name=ans>$lng[17]</a><p>
</div><div align=left>
<ul>
<!--home-->
<!--$lastmes-->
<!--end-->
</ul>
<!--homeend-->\n";

if($includeform eq 'on' and $ext ne 'htm' and $ext ne 'html')
{print FILE "<p>$hr<p><center><!--#include virtual=\"$dircgi/wtboard.cgi?$command&notitle\"--></center><p>";}

print FILE $endmes;
close FILE;


# обновление файла структуры
open NAM,"$data/$wtbstruct";@c=<NAM>;close NAM;
open NAM,">$data/$wtbstruct";
$i=0;
if($root eq 'on')
{	print NAM "\n*$lastmes";
	print NAM @c;
}
else
{	chomp @c;
	while($i<=$#c)
	{	@b=split(/([(.,*)])/,$c[$i]);
		for $j(0..$#b)
		{	print NAM $b[$j];
			if($b[$j] eq $k){print NAM "($lastmes)"}
		}
		print NAM "\n";
		++$i;
	}
}
close NAM;undef @c;undef @b;


### регистрация сообщения на основной странице
open FILE,"$dirrealkonf/index.shtml";@a=<FILE>;close FILE;
open FILE,"+>$dirrealkonf/index.shtml";
for $i(0..$#a)
{	if($selectnew>0 and index($a[$i],'<img src')>0)
	{	$a[$i]=~m/<\/b> <i>(.{19}?)/;$t=$1;$t=~s/\/19/\//;counts($t);
		if($t<$utimes-$selectnew*60){$a[$i]=~s/$selecttag//;}
	}
	for $j(0..$#prev)
	{	$l=$prev[$j];
		$k=index $a[$i],"<!--$l-->";
		if($k>=0){$a[$i]=~s/<\/i>\((\d+)\)/join('',"<\/i>\(",$1+1,')')/eg;}
	}
	print FILE $a[$i];
	$k=$prev[$#prev-1];

	if($root eq 'on')
	{	$j=index $a[$i],"<!--home-->";
		if($j>=0)
		{	print FILE "<!--$lastmes--><li>* <a href=$file>";
			if($lenbody<1 and $selectnul eq 'on'){print FILE "<font color=\"$nulcolor\">"};
			print FILE $subj;
			if($lenbody<1 and $selectnul eq 'on'){print FILE "</font>"};
			print FILE "</a> &#151; <b>$login</b> <i>$date ";
			if($setsize eq 'on'){print FILE "[$lenbody $lng[31]] ";}
			print FILE "</i>(0)";
			if($selectnew>0){print FILE $selecttag}
			print FILE "\n";
		}
	}
	else
	{	$j=index $a[$i],"<!--$k-->";
		if($j>=0)
		{	print FILE "<ul><!--$lastmes--><li><a href=$file>";
			if($lenbody<1 and $selectnul eq 'on'){print FILE "<font color=\"$nulcolor\">"};
			print FILE $subj;
			if($lenbody<1 and $selectnul eq 'on'){print FILE "</font>"};
			print FILE "</a> &#151; <b>$login</b> <i>$date ";
			if($setsize eq 'on'){print FILE "[$lenbody $lng[31]] ";}
			print FILE "</i>(0)";
			if($selectnew>0){print FILE $selecttag}
			print FILE "\n</ul>\n";
		}
	}

}
close FILE;
undef @a;

### регистрация сообщения в предыдущих сообщениях
for $n(0..$#prev-1)
{	$dn=$prev[$n];
	for$i(0..3)
	{	if(-e "$dirrealkonf/$prev.$exts[$i]"!=1){next}
		{	@datn=stat("$dirrealkonf/$dn.$exts[$i]");
			open FILE,"$dirrealkonf/$dn.$exts[$i]";@a=<FILE>;close FILE;
			open FILE,"+>$dirrealkonf/$dn.$exts[$i]";
			for $i(0..$#a)
			{	for $j(0..$#prev)
				{	$l=$prev[$j];
					$k=index $a[$i],"<!--$l-->";
					if($k>0){$a[$i]=~s/<\/i>\((\d+)\)/join('',"<\/i>\(",$1+1,')')/eg;}
				}
				print FILE $a[$i];
				$ga=$prev[$#prev-1];
				$j=index $a[$i],"<!--$ga-->";
				if($j>=0){print FILE "<ul><!--$lastmes--><li><a href=$file>$subj</a> &#151; <b>$login</b> <i>$date </i>(0)\n</ul>\n"}
			}
			close FILE;
			utime ($datn[9],$datn[9],"$dirrealkonf/$dn.$exts[$i]");
		}
	}
}

}

if($usecookie eq 'on' and length $member!=1){print "Set-Cookie: wtboard=$logs; path=/; expires=Wednesday, 08-Dec-19 23:59:59 GMT\n";}


print "\n<html>";

# перенаправления
if($redirect eq 'r'){print "<head><meta http-equiv=\"Refresh\" content=\"0; URL=$dirkonf/$file\"></head>"}
elsif($redirect eq 'R'){print "<head><meta http-equiv=\"Refresh\" content=\"0; URL=$dirkonf/\"></head>"}

print "<title> $lng[20] $tokonf</title><body bgcolor=$errbgcolor text=$errtcolor link=$errlcolor vlink=$errvlcolor alink=$erralcolor background=$mesimg><center><h3>$lng[20] $tokonf</h3><p>
$hr<p><div align=left><p><center><h2>$subj</h3><p>$hr</center><p>";

if($member!=1)
{	print " <h3>$lng[21] $onkonf $lng[22] <font color=#bb0021>$login</font>$lng[23] <font color=#bb0021>$pass</font>$lng[24] <a href=$dirkonf/faq.htm>$lng[25]";
	if($individual eq 'on'){print $lng[291]}
	print "</h3> <center>$hr</center>";
}

print "<p>$lng[26]<p><center>[<a href=$dirkonf/$file>$lng[27]</a>] [<a href=$dirkonf/>$thekonf</a>]<p>$hr</center> <p><div align=\"left\">$lng[14]";
$a4=~s/<a href=/<a href=$dirkonf\//;
length $email>0 ? print "<a href=\"mailto:$email\">$login</a>" : print $login;
print "</b> <i>$date</i>\n<br>$a4<p>";

if(length $img>=8){@c=split(/[\/\\]/,$img);print FILE "<center><img src=\"$img\" border=1 alt=\"$c[$#c]\"></center><p>\n";}

print "<div align=\"justify\">$paragraph\n$body\n<p>";

if(length $url>=8){print "<ul><li><a href=\"$url\">$urltitle<\/a></ul><p>\n";}
if($addip eq 'on'){print "<div align=right><font size=-1><i>Отправлено с IP-адреса $REMOTE_ADDR</i></font></div><p>"}

print "<center>$hr<p>[<a href=$dirkonf/$file>$lng[27]</a>] [<a href=$dirkonf/>$thekonf</a>]<p>
</body></html>";


exit;


# ФОРМА НАСТРОЙКИ ПАРАМЕТРОВ ПОЛЬЗОВАТЕЛЯ
USER:

if($individual ne 'on'){print "\n<html><title>$lng[34]</title><h2>$lng[34]</h3></html>";exit;}


print "\n$t1 $lng[35] $xlogin</title>
<body bgcolor=$errbgcolor text=$errtcolor background=$errimg>
<center><h2>$lng[35] <i>$xlogin</i></h2></center><p> $hr <p>
<center>[<a href=$dirkonf/>$thekonf</a>] [<a href=$dirkonf/faq.htm>$lng[194]</a>]</center><p> $hr <p>
<form action=$dircgi/wtboard.cgi method=post>
<table width=100% border=0>
<tr><td>$lng[1]</td><td colspan=2>$xlogin</td></tr>
<tr><td>$lng[2]</td><td colspan=2><input type=password name=pass size=30></td></tr>
<tr><td>E-mail</td><td colspan=2><input type=text name=email size=50 value=\"$xemail\"></td></tr>
<tr><td><a href=$dircgi/wtbservice.cgi?help=1&fid=$fid>$lng[36]</a></td><td colspan=2><input type=text size=50 name=hello value=\"$hello\"></td></tr>
<tr><td><a href=$dircgi/wtbservice.cgi?help=1&fid=$fid>$lng[37]</a></td><td colspan=2><input type=text size=50 name=goodbye value=\"$goodbye\">
$i1=hidden name=fid value=$fid>$i1=hidden name=update></td></tr>";

if($citating ne 'off'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<tr><td><a href=$dircgi/wtbservice.cgi?help=3&fid=$fid>$lng[38]</a></td><td colspan=2>$lng[213]$i1=radio name=uquoting value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=uquoting value=off $s2></td></tr>\n";

if($ucookie ne 'off'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<tr><td><a href=$dircgi/wtbservice.cgi?help=4&fid=$fid>$lng[41]</a></td><td colspan=2>$lng[213]$i1=radio name=ucookie value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=ucookie value=off $s2></td></tr>\n";

if($setpass eq 'on'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<tr><td><a href=$dircgi/wtbservice.cgi?help=5&fid=$fid>$lng[292]</a></td><td colspan=2>$lng[213]$i1=radio name=setpass value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=setpass value=off $s2></td></tr>\n";

if($seturl eq 'on')
{	if($showurl ne 'off'){$s1='checked';$s2='';}
	else{$s1='';$s2='checked';}
	print "<tr><td><a href=$dircgi/wtbservice.cgi?help=9&fid=$fid>$lng[400]</a></td><td colspan=2>$lng[213]$i1=radio name=showurl value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=showurl value=off $s2></td></tr>\n";
}

if($unewmes ne 'off'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<tr><td><a href=$dircgi/wtbservice.cgi?help=6&fid=$fid>$lng[42]</a></td><td>$lng[213]$i1=radio name=unewmes value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=unewmes value=off $s2></td>\n";

if($unewwinmes ne 'off'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<td>$lng[44]&nbsp;&nbsp;$lng[213]$i1=radio name=unewwinmes value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=unewwinmes value=off $s2></td></tr>\n";

if($unewans ne 'off'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<tr><td><a href=$dircgi/wtbservice.cgi?help=6&fid=$fid>$lng[43]</a></td><td>$lng[213]$i1=radio name=unewans value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=unewans value=off $s2></td>";

if($unewwinans ne 'off'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<td>$lng[44]&nbsp;&nbsp;$lng[213]$i1=radio name=unewwinans value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=unewwinans value=off $s2></td></tr>\n";

$s1='checked';$s2='';$s3='';
if($redirect eq 'r'){$s1='';$s2='checked';$s3='';}
elsif($redirect eq 'R'){$s1='';$s2='';$s3='checked';}

print "<tr><td><a href=$dircgi/wtbservice.cgi?help=8&fid=$fid>$lng[296]</a></td><td colspan=2>$lng[297]$i1=radio name=redirect value=\"\" $s1>&nbsp;&nbsp;$lng[298]$i1=radio name=redirect value=r $s2>&nbsp;&nbsp;$lng[299]$i1=radio name=redirect value=R $s3></td></tr>\n


</table><center><p><input type=submit value=\"$lng[39]\"></center>
</form>
<p> $hr <p><center>[<a href=$dirkonf/>$thekonf</a>] [<a href=$dirkonf/faq.htm>$lng[194]</a>]</center>

</body></html>";

exit;

# сохранение индивидуальной настройки
UPDATE:

if($individual ne 'on'){print "\n<html><title>$lng[34]</title><h2>$lng[34]</h3></html>";exit;}

for $i(0..$#a)
{	if($a[$i] eq 'hello'){$hello=$a[$i+1];}
	if($a[$i] eq 'goodbye'){$goodbye=$a[$i+1];}
}
for $i(0..@a)
{	$a[$i]=~s/\+/ /g;
	replacx($a[$i]);
}
for $i(0..$#a)
{	if($a[$i] eq 'email'){$email=$a[$i+1];}
	if($a[$i] eq 'uquoting'){$uquoting=$a[$i+1];}
	if($a[$i] eq 'ucookie'){$ucookie=$a[$i+1];}
	if($a[$i] eq 'unewmes'){$unewmes=$a[$i+1];}
	if($a[$i] eq 'unewwinmes'){$unewwinmes=$a[$i+1];}
	if($a[$i] eq 'unewans'){$unewans=$a[$i+1];}
	if($a[$i] eq 'unewwinans'){$unewwinans=$a[$i+1];}
	if($a[$i] eq 'setpass'){$setpass=$a[$i+1];}
	if($a[$i] eq 'redirect'){$redirect=$a[$i+1];}
	if($a[$i] eq 'showurl'){$showurl=$a[$i+1];}
	if($a[$i] eq 'pass'){$pass=$a[$i+1];}
}

$login=$xlogin;
$pars='';
if($uquoting eq 'off'){$pars=$pars.'c'}
if($ucookie eq 'off'){$pars=$pars.'k'}
if($unewmes eq 'off'){$pars=$pars.'m'}
if($unewwinmes eq 'off'){$pars=$pars.'M'}
if($unewans eq 'off'){$pars=$pars.'a'}
if($unewwinans eq 'off'){$pars=$pars.'A'}
if($setpass eq 'on'){$pars=$pars.'p'}
if($showurl eq 'off'){$pars=$pars.'h'}
$pars=$pars.$redirect;

# коррекция имени
$logs=$login;
correct($logs);


open NAM,"$data/$wtbnames";
$i=0;while(<NAM>){chomp;($names[$i],$pwd[$i],$mails[$i],$realn[$i],$ipaddr[$i],$pars[$i],$utimes[$i],$s)=split(';;');++$i;}close NAM;
for $i(0..$#names)
{	if($logs eq $names[$i])
	{	$cur=$i;
		if($pass ne $pwd[$i])
		{	open NAM,">>$data/$wtwrong";
			print NAM "WRNCP Log=$login; Pwd=$pass; Host=$REMOTE_ADDR; Time=";
			printf NAM ('%2.2d:%2.2d:%2.2d %2.2d/%2.2d/19%2.2d',$t[2],$t[1],$t[0],$t[3],$t[4],$t[5]);
			print NAM "\n";
			print "\n",$t1,"$lng[33]</title><body bgcolor=$errbgcolor text=$errtcolor background=$errimg>$lng[11]</body></html>";
			exit;
		}
		else
		{	$mails[$cur]=$email;
			$ipaddr[$cur]=$REMOTE_ADDR;
			$realn[$cur]=$login;
			$pars[$cur]=$pars;
			$utimes[$cur]=$utimes;
			rename "$data/$wtbnames","$data/$wtbnames.old";
			open NAM,">$data/$wtbnames";for $j(0..$#names){print NAM "$names[$j];;$pwd[$j];;$mails[$j];;$realn[$j];;$ipaddr[$j];;$pars[$j];;$utimes[$j];;\n"};close NAM;
			if(-z "$data/$wtbnames"==1){rename "$data/$wtbnames.old","$data/$wtbnames";}
			last;
		}
	}
}
undef @nam;undef @pwd;undef @mails;undef @pars;undef @utimes;

if($usecookie eq 'on'){print "Set-Cookie: greetings=$hello//$goodbye; path=/; expires=Wednesday, 08-Dec-19 23:59:59 GMT\n";}


print "\n<html><title>$lng[40]</title>
<body bgcolor=$errbgcolor text=$errtcolor background=$errimg>
<h2>$lng[40]</h2>
<p><center>[<a href=$dirkonf/>$thekonf</a>] [<a href=$dirkonf/faq.htm>$lng[194]</a>]</center>
</body></html>";

exit;





# подпрограмма коррекции имени
sub correct($)
{$_[0]=~s/&#(\d*?);/chr($1)/eg;$_[0]=lc $_[0];
$_[0]=~s/[ \;\.\,\_\-]//g;
$_[0]=~tr/АВЕЗКМНОРСТУХаеиопрсух01ч/ABE3KMHOPCTYXaeuonpcyxOlr/;
$_[0]=lc $_[0];
}


sub replacx($)
{$_[0]=~s/%([a-fA-F0-9][a-fA-F0-9])/pack("C",hex($1))/eg;}



# подпрограмма подсчета секунд
sub counts($)
{my(@cc)=split(/[\/.: ]/,$_[0]);
$_[0]=((((($cc[5]*12+$cc[4])*31+$cc[3])*24+$cc[0])*60)+$cc[1])*60+$cc[2];
}

