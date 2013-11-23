#!/usr/bin/perl

# White Tiger WWW Board ver.2.1b
# система wwwboard. Разработка, реализация
# (C) 1998-1999, White Tiger (2:5049/81.38; 
# email:wtiger@mail.ru; http://wtiger.ncport.ru)
# wtbservice.cgi - модуль обеспечения сервисных функций

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
print "Content-type: TEXT/HTML \n\n";
$t1='<html><title>';
#$i1='<input type';
$cprt='&copy; 1998-1999, <a href=http://wtiger.ncport.ru>White Tiger</a>';
#$cr=chr(0x0D).chr(0x0A);
$crl=chr(0x0D);
#$lf=chr(0x0D);
$c=chr(0x0D);
@t=localtime;$t[4]=$t[4]+1;
use Env qw(REMOTE_ADDR);
$ipaddr=$REMOTE_ADDR;
$cookie=$ENV{'HTTP_COOKIE'};
chop $ipaddr;
$curdata=$t[0]+($t[1]+($t[2]+($t[3]+($t[4]+$t[5]*12)*31)*24)*60)*60;
use Env qw(REMOTE_ADDR);
@exts=('htm','html','shtml','stm');

# чтение данных
use Env qw(CONTENT_LENGTH);
read STDIN,$cs,$CONTENT_LENGTH;

if($CONTENT_LENGTH <= 0){use Env qw(QUERY_STRING);$cs=$QUERY_STRING;$cs=~s/\+/ /g;}

@a=split(/[&=]/,$cs);
undef $cs;

$fid=0;
# идентификатор форума
for $i(0..$#a)
{	if($a[$i] eq 'fid'){$fid=$a[$i+1]}
}

for $i(0..$#a-1)
{	$a[$i+1]=~s/\+/ /g;
	replacx($a[$i+1]);
}

# файлы данных
open DAT,"$data/$wtbini";@lng=<DAT>;close DAT;chomp @lng;
for $i(0..$#lng)
{	@b=split(/;/,$lng[$i]);
	if($fid==$b[0])
	{	$wtbaccess=$b[1];
#		$wtbadmin=$b[2];
		$wtblang=$b[3];
		$wtblast=$b[4];
		$wtbnames=$b[5];
		$wtbnews=$b[6];
		$wtboard=$b[7];
#		$wtbreplace=$b[8];
#		$wtbstruct=$b[9];
#		$wtwrong=$b[10];
		last;
	}
}
undef @lng;undef @b;


open DAT,"$data/$wtblang";@lng=<DAT>;close DAT;chomp @lng;

# ini-данные конференции
$private='noprivate';$quote='>';
$usecookie='on';$individual='on';
$ext='shtml';$paragraph='<dd>';
$userstat='on';
#$setsize='off';$includeform='off';$addip='off';$selectnew=360;$substip='on';
#$nulcolor='#ff0000';$selectnul='on';$notag=0;$quoting='on';$reply='Re';
$ipuserstat='off';$ignorstat='off';
#$selecttag=" <font color=#ff0000><b>New</b></font>";
$hr="<hr size=1 width=80% align=center>";


open DAT,"$data/$wtboard";@ini=<DAT>;close DAT;
chomp @ini;$arh=0;
for $i(0..$#ini)
{	if(index($ini[$i],'thekonf=')==0) {($a,$thekonf)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'tokonf=')==0) {($a,$tokonf)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'ofkonf=')==0) {($a,$ofkonf)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'onkonf=')==0) {($a,$onkonf)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'admin=')==0) {($a,$admin)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'private=')==0) {($a,$private)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'quote=')==0) {($a,$quote)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'individual=')==0){($a,$individual)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'ext=')==0){($a,$ext)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'paragraph=')==0){($a,$paragraph)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'hr=')==0){($a,$hr)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'indbgcolor=')==0) {($a,$indbgcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'indtcolor=')==0) {($a,$indtcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'indlcolor=')==0) {($a,$indlcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'indvlcolor=')==0) {($a,$indvlcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'indalcolor=')==0) {($a,$indalcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'indimg=')==0) {($a,$indimg)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'mesbgcolor=')==0) {($a,$mesbgcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'mestcolor=')==0) {($a,$mestcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'meslcolor=')==0) {($a,$meslcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'mesvlcolor=')==0) {($a,$mesvlcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'mesalcolor=')==0) {($a,$mesalcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'mesimg=')==0) {($a,$mesimg)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'errbgcolor=')==0) {($a,$errbgcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'errtcolor=')==0) {($a,$errtcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'errlcolor=')==0) {($a,$errlcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'errvlcolor=')==0) {($a,$errvlcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'erralcolor=')==0) {($a,$erralcolor)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'errimg=')==0) {($a,$errimg)=split(/=/,$ini[$i],2)}
#	if(index($ini[$i],'lenlogin=')==0) {($a,$lenlogin)=split(/=/,$ini[$i],2)}
#	if(index($ini[$i],'lenpass=')==0) {($a,$lenpass)=split(/=/,$ini[$i],2)}
#	if(index($ini[$i],'lenemailmes=')==0) {($a,$lenemailmes)=split(/=/,$ini[$i],2)}
#	if(index($ini[$i],'lenemailans=')==0) {($a,$lenemailans)=split(/=/,$ini[$i],2)}
#	if(index($ini[$i],'lensubj=')==0) {($a,$lensubj)=split(/=/,$ini[$i],2)}
#	if(index($ini[$i],'lenrows=')==0) {($a,$lenrows)=split(/=/,$ini[$i],2)}
#	if(index($ini[$i],'lencols=')==0) {($a,$lencols)=split(/=/,$ini[$i],2)}
#	if(index($ini[$i],'lenurl=')==0) {($a,$lenurl)=split(/=/,$ini[$i],2)}
#	if(index($ini[$i],'lentitleurl=')==0) {($a,$lentitleurl)=split(/=/,$ini[$i],2)}
#	if(index($ini[$i],'lenimg=')==0) {($a,$lenimg)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'dirkonf=')==0) {($a,$dirkonf)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'dirrealkonf=')==0) {($a,$dirrealkonf)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'dircgi=')==0) {($a,$dircgi)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'realpath=')==0) {($a,$realpath)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'info=')==0) {($a,$info)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'userstat=')==0) {($a,$userstat)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'ipuserstat=')==0) {($a,$ipuserstat)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'ignorstat=')==0) {($a,$ignorstat)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'archive=')==0) {($a,$archive[$arh])=split(/=/,$ini[$i],2);++$arh}
}
for $i(0..$#ini)
{	$ini[$i]=~s/\$thekonf/$thekonf/g;
	$ini[$i]=~s/\$tokonf/$tokonf/g;
	$ini[$i]=~s/\$ofkonf/$ofkonf/g;
	$ini[$i]=~s/\$onkonf/$onkonf/g;
	$ini[$i]=~s/\$dirkonf/$dirkonf/g;
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
	$ini[$i]=~s/\$separator/$hr/g;
	$ini[$i]=~s/\\n/$crl/g;
}

$ended="<p><center>[<a href=$dirkonf/>$thekonf</a>] [<a href=$dirkonf/service.shtml>$lng[190]</a>]<p></body></html>";

### индивидуализация
# распознавание
@cookie=split(/[= ;]/,$cookie);
for$i(0..@cookie)
{	if($cookie[$i] eq 'wtboard'){$cookie0=$cookie[$i];$cookie=$cookie[$i+1];}
}

open NAM,"$data/$wtbnames";
$i=0;while(<NAM>){chomp;($names[$i],$pwd[$i],$mails[$i],$realn[$i],$ipaddr[$i],$pars[$i],$utimes[$i],$s)=split(';;');++$i;}
close NAM;$s=0;

if($usecookie eq 'on' and $cookie0 eq 'wtboard')
{for $i(0..$#names){if($cookie eq $names[$i])
	{	$realn=$realn[$i];
		$xemail=$mails[$i];
		$pars=$pars[$i];
		$utimes=$utimes[$i];
		$s=1;last;
	}
}}
if($s!=1)
{for $i(0..$#names){if($REMOTE_ADDR eq $ipaddr[$i])
	{	$realn=$realn[$i];
		$xemail=$mails[$i];
		$pars=$pars[$i];
		$utimes=$utimes[$i];
		last;
	}
}}

# параметры индивидуальной настройки
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


if(not defined $a[0]){$a[0]='ins';$a[1]='news'}

for $i(0..$#a)
{	if($a[$i] eq 'search'){goto SEARCH}
	if($a[$i] eq 'ins'){goto INSERT}
	if($a[$i] eq 'lastest'){goto LASTEST}
	if($a[$i] eq 'about'){goto ABOUTX}
	if($a[$i] eq 'aboutsoft'){goto ABOUTSOFT}
	if($a[$i] eq 'statist'){goto STATIST}
	if($a[$i] eq 'help'){goto HELP}
	if($a[$i] eq 'forbidden'){goto FORBIDDEN}
}
goto ERROR;


INSERT:


for $i(0..$#a-1)
{	if($a[$i] eq 'ins') {$ins=$a[$i+1]}
}


if($ins eq 'begsearch')
{	open NAM,"$data/$wtblast";$last=<NAM>;close NAM;$last=$last-100;
	if($last<0){$last=0}
	print "<input type=text name=begsearch value=$last size=10>";
}
if($ins eq 'endsearch')
{	open NAM,"$data/$wtblast";$last=<NAM>;close NAM;
	print "<input type=text name=endsearch value=$last size=10>";
}
if($ins eq 'getsearch')
{	open NAM,"$data/$wtblast";$last=<NAM>-100;close NAM;
	print $last;
}
if($ins eq 'begdata')
{	@b=localtime time-604800;
	print "<input type=text name=begdata value=\"";
	printf ('%2.2d/%2.2d/19%2.2d',$b[3],$b[4]+1,$b[5]);
	print "\" size=15>";
}
if($ins eq 'enddata')
{	print "<input type=text name=enddata value=\"";
	printf ('%2.2d/%2.2d/19%2.2d',$t[3],$t[4],$t[5]);
	print "\" size=15>";
}
if($ins eq 'getdata')
{	@b=localtime time-259200;
	print "<input type=text name=getdata value=\"";
	printf ('%2.2d/%2.2d/19%2.2d',$b[3],$b[4]+1,$b[5]);
	print "\" size=15>";
}
if($ins eq 'news')
{	# проверка доступа с запрещенного ip-адреса
	open NAM,"$data/$wtbaccess";@b=<NAM>;close NAM;chomp @b;
	for $i(0..$#b)
	{	@c=split(/;;/,$b[$i]);
		$notip=$REMOTE_ADDR;
		$lng1=$lng[29];
		$lng2=$lng[0];
		if(length $c[1] > 0){$lng1=$c[1]}
		if(length $c[2] > 0){$lng2=$c[2]}
		if(length $c[0]>2)
		{	while(length '!'.$notip>length $c[0]){chop $notip}
			if('!'.$notip eq $c[0])
			{print "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=$dircgi/wtbservice.cgi?forbidden\"></body></html><h2>$lng[186]</h2><br><font face=\"Wingdings, Symbol\" color=$indbgcolor size=0>\n";exit}
		}
	}

# вставка общих новостей

	open NAM,"$data/$wtbnews";@a=<NAM>;close NAM;chomp @a;

	$writed=0;
	@t=localtime;$t[4]=$t[4]+1;
	$t=$t[5].$t[4].$t[3].$t[2].$t[1];
	$t=$t[1]+$t[2]*60+$t[3]*60*24+$t[4]*60*24*31+$t[5]*60*24*31*366;
	for($i=$#a;$i>=1;--$i)
	{	@b=split(/;;/,$a[$i]);
		$b1=$b[4]+$b[3]*60+$b[2]*60*24+$b[1]*60*24*31+$b[0]*60*24*31*366;
		$b2=$b[9]+$b[8]*60+$b[7]*60*24+$b[6]*60*24*31+$b[5]*60*24*31*366;
		if($t>=$b1 and $t<=$b2)
		{	$writed=1;
			print "$b[10]\n";
		}
		undef $a[$i];undef @b;
	}
	if($writed==1){print "$hr<p>"}
	$writed=0;

# вставка частной информации
	if($individual eq 'off'){exit;}
	if(length $realn<1){exit;}
	if($utimes<=0){goto WNAMES;}

# сканирование индекса на предмет новых сообщений
	open NAM,"$dirrealkonf/index.shtml";@a=<NAM>;chomp@a;
	$newmes=0;
	for$i(0..@a)
	{	if(index($a[$i],'--><li>')<1){next}
		$a[$i]=~m/<\/b> <i>(.{19}?)/;$t=$1;
		$t=~s/\/19/\//;
		counts($t);
		if($t>$utimes){++$newmes}
	}

# сканирование индекса на предмет новых сообщений - ответов данному участнику
	$newans=0;$i=0;
	while($i<$#a)
	{	$j=0;if(index($a[$i],"<b>$realn</b>")>0)
		{	++$i;
			if(index($a[$i],'--><li>')<1){next}
			$j=1;while($j>0)
			{	if(index($a[$i],'</ul>')==0){--$j}
				else
				{	$a[$i]=~m/<\/b> <i>(.{19}?)/;$t=$1;
					$t=~s/\/19/\//;
					counts($t);
					if($t>$utimes){++$newans;}
				}
				++$i;
			}
		}
		++$i;
	}

# сообщение-результат
	if($unewmes ne 'off' and $newmes>0)
	{	$writed=1;print "<center><b><i>$lng[280]$lng[282]: <a href=\"$dircgi/wtbservice.cgi?search=newmes&fid=$fid&begin=$utimes\"";
		if($unewwinmes ne 'off'){print " target=\"new\"";}
		print ">$newmes</a>";
	}

	if($unewmes ne 'off' and $unewans ne 'off' and $newmes>0 and $newans>0)
	{	print $lng[281];
	}
	elsif($unewmes ne 'off' and $unewans ne 'off' and $newmes>0 and $newans<=0)
	{	print '.</i></b></center><p>';
	}
	elsif($unewmes eq 'off' and $unewans ne 'off' and $newans>0)
	{	$writed=1;print "<center><b><i>$lng[280]";
	}
	elsif($unewmes ne 'off' and $unewans eq 'off' and $newmes>0)
	{	print '.</i></b></center><p>';
	}

	if($unewans ne 'off' and $newans>0)
	{	print "$lng[283]: <a href=\"$dircgi/wtbservice.cgi?search=newans&fid=$fid&begin=$utimes\"";
		if($unewwinans ne 'off'){print " target=\"new\"";}
		print ">$newans</a>.</i></b></center><p>";
	}

	if($writed==1){print "$hr<p>"}

# обновление wtbnames по факту просмотра
WNAMES:	for$i(0..$#names)
	{	if($cookie eq $names[$i])
		{	$utimes[$i]=$curdata;last;
		}
	}
	rename "$data/$wtbnames","$data/$wtbnames.old";
	open NAM,">$data/$wtbnames";for $j(0..$#names){print NAM "$names[$j];;$pwd[$j];;$mails[$j];;$realn[$j];;$ipaddr[$j];;$pars[$j];;$utimes[$j];;\n"};close NAM;
	if(-z "$data/$wtbnames"==1){rename "$data/$wtbnames.old","$data/$wtbnames";}

}






exit;


SEARCH:

for $i(0..$#a-1)
{	if($a[$i] eq 'keysearch') {$keysearch=$a[$i+1]}
	if($a[$i] eq 'begsearch') {$begsearch=$a[$i+1]}
	if($a[$i] eq 'endsearch') {$endsearch=$a[$i+1]}
	if($a[$i] eq 'typesearch') {$typesearch=$a[$i+1]}
	if($a[$i] eq 'begdata') {$begdata=$a[$i+1]}
	if($a[$i] eq 'enddata') {$enddata=$a[$i+1]}
	if($a[$i] eq 'sorttype') {$sorttype=$a[$i+1]}
	if($a[$i] eq 'reverse') {$reverse=$a[$i+1]}
	if($a[$i] eq 'bodyonly') {$bodyonly=$a[$i+1]}
	if($a[$i] eq 'archive') {$archive=$a[$i+1]}
	if($a[$i] eq 'newmes') {$typemes=1}
	if($a[$i] eq 'newans') {$typemes=2}
	if($a[$i] eq 'begin') {$begin=$a[$i+1]}
}

if(defined $begin){goto SEARCH2}

if(not defined $keysearch){print "$t1 $lng[191]</title><body bgcolor=$errbgcolor text=$errtcolor background=$errimg>$lng[192]<P>$ended";exit;}

if(length($endsearch)==0){open NAM,"$data/$wtblast";$endsearch=<NAM>;close NAM;}
if(length($begsearch)==0){$begsearch=$endsearch-100;}
if($begsearch<0){$begsearch=0;}

$begdata==0 ? $begdata=($t[3]-7)."/".$t[4]."/".$t[5] : $begdata=$begdata;
$enddata==0 ? $enddata=$t[3]."/".$t[4]."/".$t[5] : $enddata=$enddata ;
$begdatax=$begdata;$enddatax=$enddata;
$begdatax=~s/\/19/\//;$begdatax=~s/\/20/\//;
$enddatax=~s/\/19/\//;$enddatax=~s/\/20/\//;
counts($begdatax);counts($enddatax);

# составление массива номеров для поиска

@ks=split(/[+., ();:-]/,$keysearch);
smaller($keysearch);
correct($keysearch);
@keys=split(/[+., ();:-]/,$keysearch);

$is=0;
for$i($begsearch..$endsearch)
{	for$j(0..3)
	{	if(-e "$dirrealkonf/$i.$exts[$j]"!=1){next}
		else{$ia=$j;last}
	}
	if(-e "$dirrealkonf/$i.$exts[$ia]" !=1){goto NEXTS}
	open NAM,"$dirrealkonf/$i.$exts[$ia]";@b=<NAM>;close NAM;
	for$j(0..@b){if(index($b[$j],$lng[14])==0){@c=split('i>',$b[$j]);$k=$c[$#c-1];@c=split(/[ <]/,$k);$k=$c[1];last;}}
	$k=~s/\/19/\//;$k=~s/\/20/\//;
	counts($k);
	if($k<$begdatax or $k>$enddatax){next}

	if($bodyonly eq "on"){for$j(0..@b){if(index($b[$j-1],$paragraph)==0){$b=$b[$j];last}}}
	else{$b=join ' ',@b}

	smaller($b);correct($b);
	if($typesearch==1){for $k(0..$#keys){if(index($b,$keys[$k])<0){goto NEXTS;}}}
	elsif($typesearch==2)
	{	for $k(0..$#keys)
		{	if(index($b,$keys[$k])<0){goto NEXTS}
		}
	}
	elsif($typesearch==3){if(index($b,$keysearch)<0){goto NEXTS}}
	$searched[$is]=$dirrealkonf.'/'.$i.".$exts[$ia]";++$is;
NEXTS:
}

if($archive eq 'on')
{for $i($begsearch..$endsearch)
{	for $n(0..@archive)
	{if(-e "$realpath/$archive[$n]/$i.html" !=1){next}
	open NAM,"$realpath/$archive[$n]/$i.html";@b=<NAM>;close NAM;
	for$j(0..@b){if(index($b[$j],$lng[14])==0){@c=split('i>',$b[$j]);$k=$c[$#c-1];@c=split(/[ <]/,$k);$k=$c[1];last;}}
	$k=~s/\/19/\//;$k=~s/\/20/\//;
	counts($k);
	if($k<$begdatax or $k>$enddatax){next}

	if($bodyonly eq "on"){for$j(0..@b){if(index($b[$j-1],$paragraph)==0){$b=$b[$j];last}}}
	else{$b=join ' ',@b}

	smaller($b);correct($b);
	if($typesearch==1){for $k(0..$#keys){if(index($b,$keys[$k])>=0){$searched[$is]=$realpath.'/'.$archive[$n].'/'.$i.".html";++$is;goto NEXTSS;}}}
	elsif($typesearch==2)
	{	for $k(0..$#keys)
		{	if(index($b,$keys[$k])<0){goto NEXTSS}
		}
		$searched[$is]=$realpath.'/'.$archive[$n].'/'.$i.".html";++$is;
	}
	elsif($typesearch==3){if(index($b,$keysearch)>=0){$searched[$is]=$realpath.'/'.$archive[$n].'/'.$i.".html";++$is;goto NEXTSS}}
	goto NEXTSS;
NEXTSS:
	}
}
}

undef @si;undef @b;undef $b;
$s=$#searched+1;$ks=join '; ',@ks;
print "<html><title>$lng[207] $s</title><body bgcolor=$indbgcolor text=$indtcolor alink=$indalcolor background=$indimg>
<center><h1>$lng[193]</h1> <p><p>$hr<p> [<a href=$dirkonf/>$thekonf</a>] [<a href=$dirkonf/service.shtml>$lng[190]</a>] [<a href=$dirkonf/faq.htm>$lng[194]</a>]<p>$hr<p><div align=left>
<ul><li>$lng[195] $ks<br>
<li>$lng[196] [$begsearch.$ext]&#151;[$endsearch.$ext]<br>
<li>$lng[218] [$begdata]&#151;[$enddata]<br>";
($reverse eq 'on') ? print"<li>$lng[219]<br>" : print '' ;
($archive eq 'on') ? print"<li>$lng[229]<br>" : print '' ;
($bodyonly eq 'on') ? print"<li>$lng[224]<br>" : print"<li>$lng[225]<br>" ;
print"<li>$lng[220] ";
if($sorttype==1){print $lng[221]}elsif($sorttype==2){print $lng[222]}else{print $lng[223]}
print"<br>\n<li>$lng[197] $s.</ul><p>$hr<p><ul>\n";

for $i(0..$#searched)
{	open FILE,"$searched[$i]";@b=<FILE>;close FILE;
	$searched[$i]=~s/$dirrealkonf\//$dirkonf\//;
	for$j(0..@archive){$searched[$i]=~s/$realpath\/$archive[$j]\//\.\.\/$archive[$j]\//;}
	$sr[$i]="$searched[$i];;";
	$b[0]=~m/<title>(.*?)<\/title>/;$sr[$i]=$sr[$i]."$1;;";
	$b[2]=~m/\">(.*?)<\/a>/ig;$b[2]=~m/<b>(.*?)<\/b>/ig;$sr[$i]=$sr[$i]."$1;;";
	$b[2]=~m/<\/b> <i>(.*?)<\/i>/ig;$sr[$i]=$sr[$i]."$1;;";

	$cnt=-1;for $k(0..$#b){if(index($b[$k],'<ul>')==0){++$cnt}};
	undef @d;
	$sr[$i]=$sr[$i]."$cnt;;";
}

if($sorttype==1)
{for $i(0..$#sr){$sr[$i]=~s/(.*?);;(.*?);;(.*?);;(.*?);;(.*?);;/$2;;$3;;$4;;$1;;$5;;/ig;}}
elsif($sorttype==2)
{for $i(0..$#sr){$sr[$i]=~s/(.*?);;(.*?);;(.*?);;(.*?);;(.*?);;/$3;;$2;;$4;;$1;;$5;;/ig;}}

@sr=sort @sr;
if($reverse eq 'on'){@sr=reverse @sr}

if($sorttype==1)
{for $i(0..$#sr){$sr[$i]=~s/(.*?);;(.*?);;(.*?);;(.*?);;(.*?);;/<li><a href=$dirkonf\/$4>$1<\/a> &#151; <b>$2<\/b> <i>$3 <\/i>($lng[198] $5)\n/ig;}}
elsif($sorttype==2)
{for $i(0..$#sr){$sr[$i]=~s/(.*?);;(.*?);;(.*?);;(.*?);;(.*?);;/<li><b>$1<\/b> &#151; <a href=$dirkonf\/$4>$2<\/a> <i>$3 <\/i>($lng[198] $5)\n/ig;}}
else
{for $i(0..$#sr){$sr[$i]=~s/(.*?);;(.*?);;(.*?);;(.*?);;(.*?);;/<li><i>$4 <\/i><a href=$dirkonf\/$1>$2<\/a> &#151; <b>$3<\/b> ($lng[198] $5)\n/ig;}}

for $i(0..$#sr)
{	print "$sr[$i]\n<br>";
}
if(not defined @sr){print"<li>$lng[226]<br>\n"}


print "</ul><p>$hr<p>
<center>[<a href=$dirkonf/>$thekonf</a>] [<a href=$dirkonf/service.shtml>$lng[190]</a>] [<a href=$dirkonf/faq.htm>$lng[194]</a>]<p>$hr<p></center>
<div align=left><font size=-1><i>&#169; 1999, $thekonf<br>
$cprt</I><br>
</body></html>";

exit;

SEARCH2:

if($typemes==1)
{	open NAM,"$dirrealkonf/index.shtml";@a=<NAM>;close NAM;
	$newmes=0;$count=0;$i=0;
	while($i<$#a)
	{	if(index($a[$i],'--><li>')>0)
		{	$a[$i]=~m/<\/b> <i>(.{19}?)/;$t=$1;
			$t=~s/\/19/\//;counts($t);
			if($t>$begin)
			{	$sr[$count]=$a[$i];
				$sr[$count]=~s/<ul>//;
				++$count;++$newmes;++$i;
				$t=0;$u=0;while($t==0)
				{	if(index($a[$i],'<ul>')>=0)
					{	$sr[$count]=$a[$i];
						++$u;++$count;++$i;++$newmes;
					}
					elsif(index($a[$i],'</ul>')>=0)
					{	$sr[$count]="</ul>\n";
						--$u;++$count;++$i;
					}
					else{--$u;}
					if($u<0){$t=1}
				}
			}
			else{++$i;}
		}
		else{++$i;}
	}
	$s1=$lng[284];
	$s2=$lng[285];
}
elsif($typemes==2)
# сканирование индекса на предмет новых сообщений - ответов данному участнику
{	open NAM,"$dirrealkonf/index.shtml";@a=<NAM>;chomp@a;

	$newmes=0;$count=0;$i=0;
	while($i<$#a)
	{	if(index($a[$i],'--><li>')>0 and index($a[$i],"<b>$realn</b>")>0)
		{	++$i;
			$a[$i]=~m/<\/b> <i>(.{19}?)/;$t=$1;
			$t=~s/\/19/\//;counts($t);
			if($t>$begin)
			{	$sr[$count]=$a[$i];
				$sr[$count]=~s/<ul>//;
				++$count;++$newmes;++$i;
				$t=0;$u=0;while($t==0)
				{	if(index($a[$i],'<ul>')>=0)
					{	$sr[$count]=$a[$i];
						++$u;++$count;++$i;++$newmes;
					}
					elsif(index($a[$i],'</ul>')>=0)
					{	$sr[$count]="</ul>\n";
						--$u;++$count;++$i;
					}
					else{--$u;}
					if($u<0){$t=1}
				}
			}
			else{++$i;}
		}
		else{++$i;}
	}
	$s1=$lng[286];
	$s2=$lng[285];
}

for$i(0..@sr){$sr[$i]=~s/a href=/a href=$dirkonf\//;}

print "<html><title>$lng[207] $newmes</title><body bgcolor=$indbgcolor text=$indtcolor alink=$indalcolor background=$indimg>
<center><h1>$lng[193]</h1> <p><p>$hr<p> [<a href=$dirkonf/>$thekonf</a>] [<a href=$dirkonf/service.shtml>$lng[190]</a>] [<a href=$dirkonf/faq.htm>$lng[194]</a>]<p>$hr<p><div align=left>
<ul><li>$lng[195] $s1<br>
<li>$lng[218] [$s2]<br>";
print"<li>$lng[197] $newmes.</ul><p>$hr<p><ul>\n";


print "@sr";
if(not defined @sr){print "<li>$lng[226]"};

print "</ul><p>$hr<p><center>[<a href=$dirkonf/>$thekonf</a>] [<a href=$dirkonf/service.shtml>$lng[190]</a>] [<a href=$dirkonf/faq.htm>$lng[194]</a>]<p>$hr<p></center>
<div align=left><font size=-1><i>&#169; 1999, $thekonf<br>$cprt</I><br></body></html>";
exit;



LASTEST:

for $i(0..$#a-1)
{	if($a[$i] eq 'gettype') {$gettype=$a[$i+1]}
	if($a[$i] eq 'getdata') {$getdata=$a[$i+1]}
	if($a[$i] eq 'sorttype') {$sorttype=$a[$i+1]}
	if($a[$i] eq 'reverse') {$reverse=$a[$i+1]}
}

length($getdata)==0 ? $getdata=$t[3]."/".$t[4]."/".$t[5] : $s=0 ;
$getdatax=$getdata;counts($getdatax);

if($gettype==1)
{	$j=0;@si=<$dirrealkonf/*.$ext>;
	for $i(0..$#si)
	{	$si[$i]=~s/$dirrealkonf\///;
		$si[$i]=~s/\.$ext//;
		if(-e "$dirrealkonf/$si[$i].$ext" !=1){next}
		if($si[$i] eq 'index'){next}
		if($si[$i] eq 'wtbadmin'){next}
		if($si[$i] eq 'service'){next}
		if($si[$i] eq 'util'){next}
		if($si[$i] eq 'faq'){next}
		open NAM,"$dirrealkonf/$si[$i].$ext";@b=<NAM>;close NAM;
		$k=0;for$j(0..@b){if(index($b[$j],$lng[14])==0){@c=split('i>',$b[$j]);$k=$c[$#c-1];@c=split(/[ <]/,$k);$k=$c[1];last;}}
		if($k==0){next}
		$k=~s/\/19/\//;$k=~s/\/20/\//;
		counts($k);
		if($k<$getdatax){next}
		$searched[$j]=$si[$i];++$j
	}
	undef @si;
}
else
{	open NAM,"$data/$wtblast";$last=<NAM>;close NAM;
	$j=0;for $i($getdata..$last)
	{	if(-e "$dirrealkonf/$i.$ext" ==1){$searched[$j]=$i;++$j}
	}
	$getdata=$getdata.".$ext";
}

$s=$#searched+1;
print "<html><title>$lng[207] $s</title><body bgcolor=$indbgcolor text=$indtcolor alink=$indalcolor background=$indimg>
<center><h1>$lng[193]</h1> <p><p>$hr<p> [<a href=$dirkonf/>$thekonf</a>] [<a href=$dirkonf/service.shtml>$lng[190]</a>] [<a href=$dirkonf/faq.htm>$lng[194]</a>]<p>$hr<p><div align=left>
<ul><li>$lng[227]<br><li>$lng[230] [$getdata]<br>";
($reverse eq 'on') ? print"<li>$lng[219]<br>" : print '' ;
print"<li>$lng[220] ";
if($sorttype==1){print $lng[221]}elsif($sorttype==2){print $lng[222]}else{print $lng[223]}
print"<br>\n<li>$lng[197] $s.</ul><p>$hr<p><ul>\n";

for $i(0..$#searched)
{	if(-e "$dirrealkonf/$searched[$i].$ext" !=1){next}
	open NAM,"$dirrealkonf/$searched[$i].$ext";@b=<NAM>;close NAM;
	$sr[$i]="$searched[$i];;";
	$b[0]=~m/<title>(.*?)<\/title>/;$sr[$i]=$sr[$i]."$1;;";
	$b[2]=~m/\">(.*?)<\/a>/ig;$b[2]=~m/<b>(.*?)<\/b>/ig;$sr[$i]=$sr[$i]."$1;;";
	$b[2]=~m/<\/b> <i>(.*?)<\/i>/ig;$sr[$i]=$sr[$i]."$1;;";
	$cnt=-1;for $k(0..$#b){if(index($b[$k],'<ul>')==0){++$cnt}};
	undef @d;
	$sr[$i]=$sr[$i]."$cnt;;";
}

if($sorttype==1)
{for $i(0..$#sr){$sr[$i]=~s/(.*?);;(.*?);;(.*?);;(.*?);;(.*?);;/$2;;$3;;$4;;$1;;$5;;/ig;}}
elsif($sorttype==2)
{for $i(0..$#sr){$sr[$i]=~s/(.*?);;(.*?);;(.*?);;(.*?);;(.*?);;/$3;;$2;;$4;;$1;;$5;;/ig;}}

@sr=sort @sr;
if($reverse eq 'on'){@sr=reverse @sr}

if($sorttype==1)
{for $i(0..$#sr){$sr[$i]=~s/(.*?);;(.*?);;(.*?);;(.*?);;(.*?);;/<li><a href=$dirkonf\/$4\.$ext>$1<\/a> &#151; <b>$2<\/b> <i>$3 <\/i>($lng[198] $5)\n/ig;}}
elsif($sorttype==2)
{for $i(0..$#sr){$sr[$i]=~s/(.*?);;(.*?);;(.*?);;(.*?);;(.*?);;/<li><b>$1<\/b> &#151; <a href=$dirkonf\/$4\.$ext>$2<\/a> <i>$3 <\/i>($lng[198] $5)\n/ig;}}
else
{for $i(0..$#sr){$sr[$i]=~s/(.*?);;(.*?);;(.*?);;(.*?);;(.*?);;/<li><i>$4 <\/i><a href=$dirkonf\/$1\.$ext>$2<\/a> &#151; <b>$3<\/b> ($lng[198] $5)\n/ig;}}

for $i(0..$#sr)
{	print "$sr[$i]\n<br>";
}
if(not defined @sr){print"<li>$lng[226]<br>\n"}


print "</ul><p>$hr<p>
<center>[<a href=$dirkonf/>$thekonf</a>] [<a href=$dirkonf/service.shtml>$lng[190]</a>] [<a href=$dirkonf/faq.htm>$lng[194]</a>]<p>$hr<p></center>
<div align=left><font size=-1><i>&#169; 1999, $thekonf<br>
$cprt</I><br>
</body></html>";



exit;



ABOUTX:

print "<html><title>$lng[199]</title><body bgcolor=#aaaaaa text=#113355><h2><center>$lng[200]</h2>
<p>$hr<p> [<a href=$dirkonf/>$thekonf</a>] [<a href=$dirkonf/service.shtml>$lng[190]</a>]</center> <p>$hr<p>
<div align=left><div align=justify>
<p>$info<p>
<p><p>$hr<p><p>
<div align=left><font size=-1><i>&copy; 1999, <a href=$dirkonf>$thekonf</a><br>$cprt</body></html>";


exit;



ABOUTSOFT:

print "<html><title>$lng[199]</title><body bgcolor=#aaaaaa text=#113355><h2><center>$lng[202]</h2>
<p>$hr<p> [<a href=$dirkonf/>$thekonf</a>] [<a href=$dirkonf/service.shtml>$lng[190]</a>]</center> <p>$hr<p>
<div align=left><div align=justify>
<dd>$lng[203] &#171;$thekonf&#187; $lng[204].
<p><p>$hr<p><p>
<div align=left><font size=-1><i>&copy; 1999, <a href=$dirkonf>$thekonf</a><br>$cprt</body></html>";


exit;



STATIST:


open NAM,"$data/$wtbnames";@a=<NAM>;close NAM;$names=$#a+1;
open NAM,"$data/$wtblast";$last=<NAM>;close NAM;
#open NAM,"$data/$wtbaccess";@acc=<NAM>;close NAM;


print "<html><title>$lng[228]</title><body bgcolor=#aaaaaa text=#113355><h2><center>$lng[228]</h2>
<p>$hr<p> [<a href=$dirkonf/>$thekonf</a>] [<a href=$dirkonf/service.shtml>$lng[190]</a>]</center> <p>$hr<p>
<div align=left>
<font face=\"Arial, Times New Roman\">
$lng[231] $names $lng[232]<br><br>\n";

if($userstat eq 'on')
{	print "<font size=-1><ul>\n";
	open NAM,"$data/$wtbnames";@a=<NAM>;close NAM;chomp @a;
	for $i(0..@a){($s,$s,$mails[$i],$realn[$i],$ipadd[$i],$s)=split(/;;/,$a[$i]);}
	for $i(0..@a){$a[$i]=$realn[$i].';;'.$mails[$i].';;'.$ipadd[$i].';;'}
	@a=sort @a;
	for $i(0..@a){($realn[$i],$mails[$i],$ipadd[$i],$s)=split(/;;/,$a[$i]);}

	for$i(0..$#realn)
	{	if(length $realn[$i]>0)
		{	length $mails[$i]>0 ? print"<li><a href=\"mailto:$mails[$i]\">$realn[$i]</a>" : print"<li>$realn[$i]";
			$ipuserstat eq 'on' ? print ", <i>$lng[235]: $ipadd[$i]</i>" : print"";
			print "<br>\n";
		}
	}
	print "</font></ul>\n";
	undef @a;
}

print "<p>$hr<p><center>$lng[256]</center><p>";

# статистика активности форума
open NAM,"$dirrealkonf/index.shtml";@a=<NAM>;close NAM;chomp @a;
$curtime=$t[5]*366+$t[4]*31+$t[3];
$numdays=15;
for $i(3..$#a-2)
{	@b=split(/i>/,$a[$i]);
	if($#b==0){next}
	$b[2]=~s/\/19/\//;$b[2]=~s/\/20//;$b[2]=~s/<\///;
	@b=split(/\[/,$b[2]);
	@b=split(/\s/,$b[0]);
	@b=split(/\//,$b[1]);
	$mestime=$b[2]*366+$b[1]*31+$b[0];

	if($mestime<=$curtime-$numdays){next}
	++$stat[$numdays-1-$curtime+$mestime];
	$day[$numdays-1-$curtime+$mestime]=$b[0];
	$mon[$numdays-1-$curtime+$mestime]=$b[1];
}

for$i(0..@stat){if($max<$stat[$i]){$max=$stat[$i]}}
for$i(0..@stat){$height[$i]=$stat[$i]/($max/200);$stat=$stat+$stat[$i]}

print "<center><table border=0 cellspacing=2 cellpading=0 align=center><tr valign=bottom>";

for$j(0..$#stat){if(defined $stat[$j]){$max=$j;last}}
for$i($max..$#stat)
{	$max='<td bgcolor=#0000cc align=center><font size=-7 color=#ffff00>.</font></td>';
	if($day[$i]<10){$day[$i]=$day[$i]*1;$day[$i]='0'.$day[$i]}
	if($mon[$i]<10){$mon[$i]=$mon[$i]*1;$mon[$i]='0'.$mon[$i]}
	if(not defined $stat[$i]){$day[$i]='-';$mon[$i]='-';$max="<td bgcolor=#aaaaaa align=center><font size=-1 face=Arial>n/a</font></td>"}
	print "<td align=center><font size=-1 face=Arial>$stat[$i]<table border=0 width=30 height=$height[$i]><tr valign=bottom>$max</tr></table>$day[$i]/$mon[$i]</font></td>\n";
}
print "</tr></table></center>
<br>
$lng[233] $last.<br>$lng[255] $stat.";



if($ignorstat eq 'on')
{	open NAM,"$data/$wtbaccess";$i=0;while(<NAM>){chomp;($ignor[$i],$s)=split(';;');++$i;};close NAM;
	if(not defined $#ignor){goto NOTIGNOR}
	print "<p>$hr<p><center>$lng[257]</center><p>$lng[234]<br><font size=-1><ul>\n";
	for$i(0..$#ignor)
	{	$ignor[$i]=~s/!//;$ignor[$i]=~s/-//;
		print"<li>$ignor[$i]<br>\n";
	}
	print "</ul></font>";
}


NOTIGNOR:

print "<p><p>$hr<p><p>
<font face=\"Times New Roman\">
<center>[<a href=$dirkonf/>$thekonf</a>] [<a href=$dirkonf/service.shtml>$lng[190]</a>]</center> <p>$hr<p>
<div align=left><font size=-1><i>&copy; 1999, <a href=$dirkonf>$thekonf</a><br>$cprt</body></html>";


exit;


FORBIDDEN:

print "<html><title>$lng[29]</title><body><h2>$lng[29]</h2></body></html>";
exit;



HELP:

for $i(0..$#a-1)
{	if($a[$i] eq 'help') {$help=$a[$i+1]}
}

print "<html><title>$thekonf: контекстная подсказка</title><body bgcolor=$indbgcolor text=$indtcolor alink=$indalcolor background=$indimg>
<center><h3>$thekonf:<br>контекстная подсказка</h3> <p>$hr<p> <div align=left>
$lng[299+$help]
<p>$hr<p>\n
<center>[<a href=$dirkonf/>$thekonf</a>] [<a href=$dirkonf/service.shtml>$lng[190]</a>] [<a href=$dirkonf/faq.htm>$lng[194]</a>]</center>
</body></html>";

exit;




ERROR:
print "<html><title>$lng[188]</title><body>$lng[205] $ended";
exit;


# подпрограмма коррекции имени
sub correct($)
{$_[0]=~s/&#(\d*?);/chr($1)/eg;$_[0]=lc $_[0];
$_[0]=~s/[ \;\.\,\_\-]//g;
$_[0]=~tr/АВЕЗКМНОРСТУХаеиопрсух01ч/ABE3KMHOPCTYXaeuonpcyxOlr/;
$_[0]=lc $_[0];
}



# подпрограмма уменьшения регистра
sub smaller($)
{$_[0]=~tr/АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ/абвгдежзийклмнопрстуфхцчшщъыьэюя/;
$_[0]=lc $_[0]}




sub replacx($)
{$_[0] =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;}



# подпрограмма подсчета секунд
sub counts($)
{my(@cc)=split(/[\/.: ]/,$_[0]);
$_[0]=((((($cc[5]*12+$cc[4])*31+$cc[3])*24+$cc[0])*60)+$cc[1])*60+$cc[2];
}
