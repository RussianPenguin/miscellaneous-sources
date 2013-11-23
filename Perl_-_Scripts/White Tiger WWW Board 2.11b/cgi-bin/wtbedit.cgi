#!/usr/bin/perl

# White Tiger WWW Board ver.2.1b
# система wwwboard. Разработка, реализация
# (C) 1998-1999, White Tiger (2:5049/81.38; 
# email:wtiger@mail.ru; http://wtiger.ncport.ru)
# wtbedit.cgi - модуль администрирования форума

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
$i1='<input type';
$cr=chr(0x0D).chr(0x0A);
$cl=chr(0x0D);
$cs2='<td colspan=2><div align=left>';
$cs3='<td colspan=3 align=center>';
$cs4="</td><td colspan=4>";
$cs6='<td colspan=6><div align=left>';
$dr='</td></tr>';
$rd='<tr><td>';

# получение post-данных
use Env qw(CONTENT_LENGTH);
read STDIN,$cs,$CONTENT_LENGTH;
@t=localtime;$t[4]=$t[4]+1;
@exts=('htm','html','shtml','stm');

$cs=~s/\+/ /g;

@a=split(/[&=]/,$cs);
undef $cs;

$fid=0;
# идентификатор форума
for $i(0..$#a)
{	if($a[$i] eq 'fid'){$fid=$a[$i+1]}
}

open DAT,"$data/$wtbini";@lng=<DAT>;close DAT;chomp @lng;
for $i(0..$#lng)
{	@b=split(/;/,$lng[$i]);
	if($fid==$b[0])
	{	$wtbaccess=$b[1];
		$wtbadmin=$b[2];
		$wtblang=$b[3];
#		$wtblast=$b[4];
		$wtbnames=$b[5];
		$wtbnews=$b[6];
		$wtboard=$b[7];
#		$wtbreplace=$b[8];
		$wtbstruct=$b[9];
		$wtwrong=$b[10];
		last;
	}
}
undef @lng;undef @b;

# язык
open DAT,"$data/$wtblang";@lng=<DAT>;close DAT;chomp @lng;

# ini-данные конференции
$private='noprivate';$quote='>';$substip='on';$setsize='off';$addip='off';
$notag=0;$usecookie='on';$quoting='on';$individual='on';
$includeform='off';$ext='shtml';$reply='Re';$paragraph='<dd>';
$selectnew=360;$nulcolor='#ff0000';$selectnul='on';$userstat='on';
$ipuserstat='off';$ignorstat='off';
$selecttag=" <font color=#ff0000><b>New</b></font>";
$hr="<hr size=1 width=80% align=center>";$quotebeg='<i>';$quoteend='</i>';
$seturl='on';

open NAM,"$data/$wtboard";@ini=<NAM>;close NAM;
chomp @ini;
for $i(0..$#ini)
{	if(index($ini[$i],'thekonf=')==0){($a,$thekonf)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'tokonf=')==0){($a,$tokonf)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'ofkonf=')==0){($a,$ofkonf)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'onkonf=')==0){($a,$onkonf)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'admin=')==0){($a,$admin)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'private=')==0){($a,$private)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'quote=')==0){($a,$quote)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'quotebeg=')==0){($a,$quotebeg)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'quoteend=')==0){($a,$quoteend)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'reply=')==0){($a,$reply)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'quoting=')==0){($a,$quoting)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'individual=')==0){($a,$individual)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'substip=')==0){($a,$substip)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'usecookie=')==0){($a,$usecookie)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'setsize=')==0){($a,$setsize)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'addip=')==0){($a,$addip)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'notag=')==0){($a,$notag)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'selectnew=')==0){($a,$selectnew)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'selecttag=')==0){($a,$selecttag)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'selectnul=')==0){($a,$selectnul)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'individual=')==0){($a,$individual)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'includeform=')==0){($a,$includeform)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'ext=')==0){($a,$ext)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'paragraph=')==0){($a,$paragraph)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'hr=')==0){($a,$hr)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'seturl=')==0){($a,$seturl)=split(/=/,$ini[$i],2);}
	if(index($ini[$i],'nulcolor=')==0){($a,$nulcolor)=split(/=/,$ini[$i],2);}
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
	if(index($ini[$i],'begmesform=')==0){($a,$begmesform)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'endmesform=')==0){($a,$endmesform)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'begansform=')==0){($a,$begansform)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'endansform=')==0){($a,$endansform)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'begarchive=')==0){($a,$begarchive)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'endarchive=')==0){($a,$endarchive)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'begmes=')==0){($a,$begmes)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'endmes=')==0){($a,$endmes)=split(/=/,$ini[$i],2)}
#	if(index($ini[$i],'begans=')==0){($a,$begans)=split(/=/,$ini[$i],2)}
#	if(index($ini[$i],'endans=')==0){($a,$endans)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'begindex=')==0){($a,$begindex)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'endindex=')==0){($a,$endindex)=split(/=/,$ini[$i],2)}
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
	if(index($ini[$i],'dirkonf=')==0){($a,$dirkonf)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'dirrealkonf=')==0){($a,$dirrealkonf)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'dircgi=')==0){($a,$dircgi)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'realpath=')==0){($a,$realpath)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'userstat=')==0) {($a,$userstat)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'ipuserstat=')==0) {($a,$ipuserstat)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'ignorstat=')==0) {($a,$ignorstat)=split(/=/,$ini[$i],2)}
	if(index($ini[$i],'info=')==0){($a,$info)=split(/=/,$ini[$i],2)}
}
undef @ini;


$begindex=~s/<!>/$cl/g;
$endindex=~s/<!>/$cl/g;
$begmesform=~s/<!>/$cl/g;
$endmesform=~s/<!>/$cl/g;
$begansform=~s/<!>/$cl/g;
$endansform=~s/<!>/$cl/g;
$begarchive=~s/<!>/$cl/g;
$endarchive=~s/<!>/$cl/g;
$begmes=~s/<!>/$cl/g;
$endmes=~s/<!>/$cl/g;
$info=~s/<!>/$cl/g;


$ended="<p><center>[<a href=$dirkonf/>$thekonf</a>] [<a href=$dirkonf/wtbadmin.htm>$lng[206] $thekonf</a>]<p></body></html>";

for $i(0..$#a-1)
{	replacx($a[$i+1]);
	if($a[$i] eq 'login'){$login=$a[$i+1]}
	if($a[$i] eq 'pass'){$pass=$a[$i+1]}
	if($a[$i] eq 'oper'){$oper=$a[$i+1]}
}

open NAM,"$data/$wtbadmin";$i=0;while(<NAM>){chomp;($nam[$i],$pwd[$i],$stat[$i])=split(';;');++$i;}close NAM;

for $i(0..$#nam)
{	if($login eq $nam[$i])
	{	if($pass eq $pwd[$i]){$stat=$stat[$i];goto ENTER}
		else
		{	print "<html><title>$lng[186]</title><body>$lng[48]</body></html>";
			use Env qw(REMOTE_ADDR);
			open NAM,">>$data/$wtwrong";
			print NAM "BDADM Log=$login; Pwd=$pass; Host=$REMOTE_ADDR; Time=";
			printf NAM ('%2.2d:%2.2d:%2.2d %2.2d/%2.2d/19%2.2d',$t[2],$t[1],$t[0],$t[3],$t[4],$t[5]);
			print NAM "\n";
			exit;
		}
	}
}

print "<html><title>$lng[186]</title><body>$lng[48]</body></html>";
use Env qw(REMOTE_ADDR);
open NAM,">>$data/$wtwrong";
print NAM "BDADM Log=$login; Pwd=$pass; Host=$REMOTE_ADDR; Time=";
printf NAM ('%2.2d:%2.2d:%2.2d %2.2d/%2.2d/19%2.2d',$t[2],$t[1],$t[0],$t[3],$t[4],$t[5]);
print NAM "\n";
exit;

ENTER:

if($oper eq 'admin'){goto ADMIN}
elsif($oper eq 'modif'){goto MODIF}
elsif($oper eq 'arhiv'){goto ARHIV}
elsif($oper eq 'ignor'){goto IGNOR}
elsif($oper eq 'news'){goto NEWS}
elsif($oper eq 'sedit'){goto SEDIT}
elsif($oper eq 'seditx'){goto SEDITX}
elsif($oper eq 'restore'){goto RESTORE}
elsif($oper eq 'wronglog'){goto WRONGLOG}
elsif($oper eq 'submit'){goto SUBMIT}
else{goto ERROR}

### администрация - элементы интерфейса, статус,  список администраторов, игнор-лист
ADMIN:
                               
print "<html><title>$lng[49] 1 &#151; $login</title><body bgcolor=#f0f0ff><font size=\"+2\"><center>$lng[50]<br><b>$login</b>,<font size=\"+1\"><br><i>$lng[51]<b>";
if(index($stat,'a')>=0){print ": $lng[52] "}
if(index($stat,'i')>=0){print ": $lng[53] "}
if(index($stat,'g')>=0){print ": $lng[54] "}
if(index($stat,'d')>=0){print ": $lng[55] "}
if(index($stat,'h')>=0){print ": $lng[56] "}
if(index($stat,'e')>=0){print ": $lng[57] "}
if(index($stat,'n')>=0){print ": $lng[58] "}
if(index($stat,'s')>=0){print ": $lng[59] "}

print "</b></i></font><p>$hr</center></font><p><form action=$dircgi/wtbedit.cgi method=post><table width=100%>";

if(index($stat,'a')>=0)
{
$nam=join(chr(0x0D),@nam);$pwd=join(chr(0x0D),@pwd);$stats=join(chr(0x0D),@stat);
$rows=$#nam+2;
print"<tr><td colspan=6><font size=\"+1\"><center>$lng[65]<br><br>$dr
<tr><td colspan=3>$lng[66]$i1=text name=thekonf size=18 value=\"$thekonf\"></td>
<td nowrap colspan=3>$lng[67]$i1=text name=tokonf size=15 value=\"$tokonf\">$dr
<tr><td colspan=3>$lng[208]$i1=text name=ofkonf size=18 value=\"$ofkonf\"></td>
<td nowrap colspan=3>$lng[68]$i1=text name=onkonf size=13 value=\"$onkonf\">$dr
$rd&nbsp;<p>$dr
<tr><td colspan=3>$lng[69]<br><textarea name=anam cols=35 rows=$rows>$nam</textarea></td>
<td colspan=2>$lng[70]<br><textarea name=apwd cols=20 rows=$rows>$pwd</textarea></td>
<td>$lng[71]<br><textarea name=astat cols=6 rows=$rows>$stats</textarea>$dr
<tr>$cs6$lng[72] &nbsp;<p>$dr
<tr><td colspan=2>$lng[73]</td>";

if($private eq 'private'){print "<td colspan=2>$i1=radio name=private value=private checked>$lng[74]</td><td colspan=2>$i1=radio name=private value=noprivate>$lng[75]</td>";}
else{print"<td colspan=2>$i1=radio name=private value=private>$lng[74]</td><td colspan=2>$i1=radio name=private value=noprivate checked>$lng[75]</td>";}

print "<tr>$cs6$lng[76] &nbsp;<p>$dr
<tr>$cs2$lng[77]$cs4$i1=text name=admin value=$admin size=30>$dr
<tr>$cs6$lng[78] &nbsp;<p>$dr
<tr>$cs2$lng[273]$cs4<textarea name=paragraph cols=35 rows=1>$paragraph</textarea>$dr
<tr>$cs6$lng[274] &nbsp;<p>$dr
<tr>$cs2$lng[289]$cs4<textarea name=hr cols=35 rows=1>$hr</textarea>$dr
<tr>$cs6$lng[290] &nbsp;<p>$dr
<tr>$cs2$lng[79]$cs4$i1=text name=quote value=\"$quote\" size=30>$dr
<tr>$cs6$lng[80] &nbsp;<p>$dr
<tr>$cs2$lng[293]<td>$i1=text name=quotebeg value=\"$quotebeg\" size=8></td>
$cs2$lng[294]<td>$i1=text name=quoteend value=\"$quoteend\" size=8>$dr
<tr>$cs6$lng[295] &nbsp;<p>$dr
<tr>$cs2$lng[271]$cs4$i1=text name=reply value=\"$reply\" size=30>$dr
<tr>$cs6$lng[272] &nbsp;<p>$dr";

if($quoting eq 'on'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<tr>$cs6$lng[265]&nbsp;&nbsp;$lng[213]$i1=radio name=quoting value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=quoting value=off $s2>$dr
<tr>$cs6$lng[266] &nbsp;<p>$dr";

if($notag==0){$s1='checked';$s2='';;$s3=''}
elsif($notag==1){$s1='';$s2='checked';$s3=''}
elsif($notag==2){$s1='';$s2='';$s3='checked';}
print "<tr>$cs6$lng[260]&nbsp;&nbsp;$lng[261]$i1=radio name=notag value=0 $s1>&nbsp;&nbsp;$lng[262]$i1=radio name=notag value=1 $s2>&nbsp;&nbsp;$lng[263]$i1=radio name=notag value=2 $s3>$dr
<tr>$cs6$lng[264] &nbsp;<p>$dr";

if($ext eq 'htm'){$s1='checked';$s2='';$s3='';$s4='';}
elsif($ext eq 'html'){$s1='';$s2='checked';$s3='';$s4='';}
elsif($ext eq 'stm'){$s1='';$s2='';$s3='';$s4='checked';}
else{$s1='';$s2='';$s3='checked';$s4='';}
print "<tr>$cs6$lng[269]&nbsp;&nbsp;htm$i1=radio name=ext value=htm $s1>&nbsp;&nbsp;html$i1=radio name=ext value=html $s2>&nbsp;&nbsp;shtml$i1=radio name=ext value=shtml $s3>&nbsp;&nbsp;stm$i1=radio name=ext value=stm $s4>$dr
<tr>$cs6$lng[270] &nbsp;<p>$dr";

if($usecookie eq 'on'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<tr>$cs6$lng[258]&nbsp;&nbsp;$lng[213]$i1=radio name=usecookie value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=usecookie value=off $s2>$dr
<tr>$cs6$lng[259] &nbsp;<p>$dr";

if($substip eq 'on'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<tr>$cs6$lng[81]&nbsp;&nbsp;$lng[213]$i1=radio name=substip value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=substip value=off $s2>$dr
<tr>$cs6$lng[82] &nbsp;<p>$dr";

if($individual eq 'on'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<tr>$cs6$lng[267]&nbsp;&nbsp;$lng[213]$i1=radio name=individual value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=individual value=off $s2>$dr
<tr>$cs6$lng[268] &nbsp;<p>$dr";

if($setsize eq 'on'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<tr>$cs6$lng[209]&nbsp;&nbsp;$lng[213]$i1=radio name=setsize value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=setsize value=off $s2>$dr
<tr>$cs6$lng[210] &nbsp;<p>$dr
<tr>$cs2$lng[275]$cs4$i1=text name=selectnew value=\"$selectnew\" size=10>$dr
<tr>$cs6$lng[276] &nbsp;<p>$dr
<tr>$cs2$lng[287]$cs4<textarea name=selecttag cols=35 rows=1>$selecttag</textarea>$dr
<tr>$cs6$lng[288] &nbsp;<p>$dr";

if($selectnul eq 'on'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<tr><td colspan=4><div align=left>$lng[277]&nbsp;&nbsp;$lng[213]$i1=radio name=selectnul value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=selectnul value=off $s2></td>
$cs2$lng[278] $i1=text name=nulcolor value=\"$nulcolor\" size=10>$dr
<tr>$cs6$lng[279] &nbsp;<p>$dr";

if($addip eq 'on'){$s1='checked';$s2=''}
else{$s1='';$s2='checked'}

print "<tr>$cs6$lng[211]&nbsp;&nbsp;$lng[213]$i1=radio name=addip value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=addip value=off $s2>$dr
<tr>$cs6$lng[212] &nbsp;<p>$dr
<tr>$cs2$lng[83]</td><td>$i1=text name=lenlogin value=$lenlogin size=9></td>
$cs2$lng[84]</td><td>$i1=text name=lenpass value=$lenpass size=9>$dr
<tr>$cs2$lng[85]</td><td>$i1=text name=lenemailmes value=$lenemailmes size=9></td>
$cs2$lng[86]</td><td>$i1=text name=lenemailans value=$lenemailans size=9>$dr
<tr>$cs2$lng[87]</td><td>$i1=text name=lensubj value=$lensubj size=9>$dr
<tr>$cs2$lng[88]</td><td>$i1=text name=lenrows value=$lenrows size=9></td>
$cs2$lng[89]</td><td>$i1=text name=lencols value=$lencols size=9>$dr
<tr>$cs2$lng[90]</td><td>$i1=text name=lenurl value=$lenurl size=9></td>
$cs2$lng[91]</td><td>$i1=text name=lentitleurl value=$lentitleurl size=9>$dr
<tr>$cs2$lng[92]</td><td>$i1=text name=lenimg value=$lenimg size=9>$dr
<tr>$cs6$lng[93] &nbsp;<p>$dr";
}

if($seturl eq 'on'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<tr>$cs6$lng[401]&nbsp;&nbsp;$lng[213]$i1=radio name=seturl value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=seturl value=off $s2>$dr
<tr>$cs6$lng[402]$dr
<tr>$cs6 &nbsp;<p>$hr&nbsp;<p>$dr";


if(index($stat,'a')>=0)
{
print "
<tr><td colspan=6><font size=\"+1\"><center><b>$lng[200]$dr<tr><td colspan=6 align=center><textarea name=info cols=70 rows=10>$info</textarea>$dr<tr>$cs6$lng[201] &nbsp;<p>$dr<tr><td colspan=6>$dr";

if($userstat eq 'on'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<tr>$cs6$lng[236]&nbsp;&nbsp;$lng[213]$i1=radio name=userstat value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=userstat value=off $s2>$dr
<tr>$cs6$lng[237] &nbsp;<p>$dr";

if($ipuserstat eq 'on'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<tr>$cs6$lng[240]&nbsp;&nbsp;$lng[213]$i1=radio name=ipuserstat value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=ipuserstat value=off $s2>$dr
<tr>$cs6$lng[241] &nbsp;<p>$dr";

if($ignorstat eq 'on'){$s1='checked';$s2='';}
else{$s1='';$s2='checked';}
print "<tr>$cs6$lng[238]&nbsp;&nbsp;$lng[213]$i1=radio name=ignorstat value=on $s1>&nbsp;&nbsp;$lng[214]$i1=radio name=ignorstat value=off $s2>$dr
<tr>$cs6$lng[239] &nbsp;<p>$hr&nbsp;<p>$dr";

}

if(index($stat,'a')>=0 or index($stat,'i')>=0)
{
print"<tr><td colspan=6><font size=\"+1\"><center><b>$lng[94]$dr
<tr><td colspan=6>$lng[95]$dr
<tr><td colspan=6><i><center><font size=\"+1\"><b>$lng[96]$dr
$rd<center>$lng[97]</td><td colspan=3><center>$lng[103]</td><td colspan=2><center>$lng[104]$dr
$rd$lng[98]</td>$cs3<textarea name=begindex cols=30 rows=2>$begindex</textarea></td>
<td colspan=2 align=center><textarea name=endindex cols=20 rows=2>$endindex</textarea>$dr
$rd$lng[99]</td>$cs3<textarea name=begarchive cols=30 rows=2>$begarchive</textarea></td>
<td colspan=2 align=center><textarea name=endarchive cols=20 rows=2>$endarchive</textarea>$dr
$rd$lng[100]</td>$cs3<textarea name=begmesform cols=30 rows=2>$begmesform</textarea></td>
<td colspan=2 align=center><textarea name=endmesform cols=20 rows=2>$endmesform</textarea>$dr
$rd$lng[101]</td>$cs3<textarea name=begansform cols=30 rows=2>$begansform</textarea></td>
<td colspan=2 align=center><textarea name=endansform cols=20 rows=2>$endansform</textarea>$dr
$rd$lng[102]</td>$cs3<textarea name=begmes cols=30 rows=2>$begmes</textarea></td>
<td colspan=2 align=center><textarea name=endmes cols=20 rows=2>$endmes</textarea>$dr
<tr>$cs6$lng[105] $lng[106] $lng[107]
<tr><td colspan=6><i><center><font size=\"+1\"><b>$lng[108]$dr
$rd<center>$lng[97]</td><td><center>$lng[98]</td><td><center>$lng[99]</td><td><center>$lng[100]</td><td><center>$lng[101]</td><td><center>$lng[102]$dr
$rd$lng[109]</td><td>$i1=text name=indbgcolor value=$indbgcolor size=9></td><td><center>&#151;</td><td>$i1=text name=errbgcolor value=$errbgcolor size=9></td><td><center>&#151;</td><td>$i1=text name=mesbgcolor value=$mesbgcolor size=9>$dr
$rd$lng[110]</td><td>$i1=text name=indtcolor value=$indtcolor size=9></td><td><center>&#151;</td><td>$i1=text name=errtcolor value=$errtcolor size=9></td><td><center>&#151;</td><td>$i1=text name=mestcolor value=$mestcolor size=9>$dr
$rd$lng[111]</td><td>$i1=text name=indlcolor value=$indlcolor size=9></td><td><center>&#151;</td><td>$i1=text name=errlcolor value=$errlcolor size=9></td><td><center>&#151;</td><td>$i1=text name=meslcolor value=$meslcolor size=9>$dr
$rd$lng[112]</td><td>$i1=text name=indvlcolor value=$indvlcolor size=9></td><td><center>&#151;</td><td>$i1=text name=errvlcolor value=$errvlcolor size=9></td><td><center>&#151;</td><td>$i1=text name=mesvlcolor value=$mesvlcolor size=9>$dr
$rd$lng[113]</td><td>$i1=text name=indalcolor value=$indalcolor size=9></td><td><center>&#151;</td><td>$i1=text name=erralcolor value=$erralcolor size=9></td><td><center>&#151;</td><td>$i1=text name=mesalcolor value=$mesalcolor size=9>$dr
$rd$lng[114]</td><td>$i1=text name=indimg value=\"$indimg\" size=9></td><td><center>&#151;</td><td>$i1=text name=errimg value=\"$errimg\" size=9></td><td><center>&#151;</td><td>$i1=text name=mesimg value=\"$mesimg\" size=9>$dr
<tr>$cs6$lng[115]$dr"
}

print "</table><p><center>$hr<p>$i1=hidden name=login value=$login>
$i1=hidden name=pass value=$pass>$i1=hidden name=oper value=submit>
$i1=hidden name=fid value=$fid>$i1=submit value=$lng[8]></form><p></body></html>";

exit;


IGNOR:

if(index($stat,'g')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body>$lng[116]</body></html>";exit;}

print "<html><title>$lng[49] 2 &#151; $login</title><body bgcolor=#f0f0ff><font size=\"+2\"><center>$lng[50]<br><b>$login</b>,<font size=\"+1\"><br><i>$lng[51]<b>";
if(index($stat,'a')>=0){print ": $lng[52] "}
if(index($stat,'i')>=0){print ": $lng[53] "}
if(index($stat,'g')>=0){print ": $lng[54] "}
if(index($stat,'d')>=0){print ": $lng[55] "}
if(index($stat,'h')>=0){print ": $lng[56] "}
if(index($stat,'e')>=0){print ": $lng[57] "}
if(index($stat,'n')>=0){print ": $lng[58] "}
if(index($stat,'s')>=0){print ": $lng[59] "}

print "</b></i></font><p>$hr</center></font><p><form action=$dircgi/wtbedit.cgi method=post><table width=100%>
$rd<font size=\"+1\"><center><b>$lng[117]$dr";

open NAM,"$data/$wtbnames";@nam=<NAM>;chomp @nam;close NAM;
for$i(0..@nam){$nam[$i]=~s/;;/|/g;}
$nam=join(chr(0x0D),@nam);

print "$rd<center>$lng[118]<br><textarea name=names cols=70 rows=10>$nam</textarea></center>$dr
$rd<div align=left>$lng[122]</div>$dr
$rd<p>&nbsp;<p><center>$hr<p><p>&nbsp;<p>$dr
$rd<font size=\"+1\"><center><b>$lng[123]$dr</table>";

open NAM,"$data/$wtbaccess";@ini=<NAM>;close NAM;chomp @ini;
for $i(0..$#ini){($inii[$i],$init[$i],$inim[$i])=split(/;;/,$ini[$i])}
$inii=join(chr(0x0D),@inii);
$init=join(chr(0x0D),@init);
$inim=join(chr(0x0D),@inim);
print "<table width=100%><tr><td colspan=2 align=center>$lng[215]</td><td align=center>$lng[216]</td><td colspan=2 align=center>$lng[217]$dr
<tr><td colspan=2 align=center><textarea name=ignor cols=22 rows=10>$inii</textarea></td>
<td align=center><textarea name=ignort cols=13 rows=10>$init</textarea></td>
<td colspan=2 align=center><textarea name=ignorm cols=25 rows=10>$inim</textarea>
$i1=hidden name=private value=$private>$dr
</table>
<div align=left>$lng[125]<center>$hr<p>$i1=hidden name=login value=$login>
$i1=hidden name=pass value=$pass>$i1=hidden name=oper value=submit>
$i1=hidden name=fid value=$fid>$i1=submit value=$lng[8]></form><p>$t<p>
<center><form action=$dircgi/wtbedit.cgi method=post>$i1=hidden name=login value=$login>
$i1=hidden name=pass value=$pass>$i1=hidden name=oper value=wronglog>
$i1=hidden name=fid value=$fid>$i1=submit value=\"$lng[124]\"></form><p></body></html>";

exit;


SEDIT:

if(index($stat,'e')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body><h2>$lng[126]</h2></body></html>";exit;}

print "<html><title>$lng[49] 3 &#151; $login</title><body bgcolor=#f0f0ff><font size=\"+2\"><center>$lng[50]<br><b>$login</b>,<font size=\"+1\"><br><i>$lng[51]<b>";
if(index($stat,'a')>=0){print ": $lng[52] "}
if(index($stat,'i')>=0){print ": $lng[53] "}
if(index($stat,'g')>=0){print ": $lng[54] "}
if(index($stat,'d')>=0){print ": $lng[55] "}
if(index($stat,'h')>=0){print ": $lng[56] "}
if(index($stat,'e')>=0){print ": $lng[57] "}
if(index($stat,'n')>=0){print ": $lng[58] "}
if(index($stat,'s')>=0){print ": $lng[59] "}

print "</b></i></font><p>$hr</center></font><p><form action=$dircgi/wtbedit.cgi method=post><table width=100%>";

print "$rd<font size=\"+1\"><center><b>$lng[127]$dr
$rd$lng[128] $i1=text name=nummes size=10>$dr
$rd<div align=left>$lng[129]$dr</table><p><center>$hr<p>
$i1=hidden name=login value=$login>$i1=hidden name=pass value=$pass>
$i1=hidden name=oper value=seditx>$i1=hidden name=fid value=$fid>$i1=submit value=$lng[8]></form><p></body></html>";
exit;


SEDITX:

for $i(0..$#a){if($a[$i] eq 'nummes'){$nummes=$a[$i+1];}}

if(defined $nummes)
{	open NAM,"$dirrealkonf/index.shtml";@ini=<NAM>;close NAM;
	chomp @ini;
	for $i(0..$#ini){if(index($ini[$i],"<!--$nummes-->")>=0){$text=$ini[$i]}}
	undef @ini;

	if(length $text <3){print "<html><title>$lng[187]</title>$lng[130] $ended</html>";exit;}

	print "<html><title>$lng[49] 3 &#151; $login</title><body bgcolor=#f0f0ff><font size=\"+2\"><center>$lng[50]<br><b>$login</b>,<font size=\"+1\"><br><i>$lng[51]<b>";
	if(index($stat,'a')>=0){print ": $lng[52] "}
	if(index($stat,'i')>=0){print ": $lng[53] "}
	if(index($stat,'g')>=0){print ": $lng[54] "}
	if(index($stat,'d')>=0){print ": $lng[55] "}
	if(index($stat,'h')>=0){print ": $lng[56] "}
	if(index($stat,'e')>=0){print ": $lng[57] "}
	if(index($stat,'n')>=0){print ": $lng[58] "}
	if(index($stat,'s')>=0){print ": $lng[59] "}

	print "<form action=$dircgi/wtbedit.cgi method=post><table width=100%>";
	print "<tr><td colspan=3><font size=\"+1\"><center><b>$lng[127]$dr";
	print "$rd$lng[131]<br><textarea name=editind cols=70 rows=1>$text</textarea>$dr<tr>$cs6$lng[132]$dr";
}
print "</table><p><center>$hr<p>$i1=hidden name=login value=$login>
$i1=hidden name=pass value=$pass>$i1=hidden name=oper value=submit>
$i1=hidden name=fid value=$fid>$i1=hidden name=nummes value=$nummes>$i1=submit value=$lng[8]></form><p></body></html>";

exit;


MODIF:

if(index($stat,'d')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body><h2>$lng[133]</h2></body></html>";exit;}

print "<html><title>$lng[49] 4 &#151; $login</title><body bgcolor=#f0f0ff><font size=\"+2\"><center>$lng[50]<br><b>$login</b>,<font size=\"+1\"><br><i>$lng[51]<b>";
if(index($stat,'a')>=0){print ": $lng[52] "}
if(index($stat,'i')>=0){print ": $lng[53] "}
if(index($stat,'g')>=0){print ": $lng[54] "}
if(index($stat,'d')>=0){print ": $lng[55] "}
if(index($stat,'h')>=0){print ": $lng[56] "}
if(index($stat,'e')>=0){print ": $lng[57] "}
if(index($stat,'n')>=0){print ": $lng[58] "}
if(index($stat,'s')>=0){print ": $lng[59] "}

print "</b></i></font><p>$hr</center></font><p><form action=$dircgi/wtbedit.cgi method=post><table width=100%>";
print "<tr><td colspan=3><font size=\"+1\"><center><b>$lng[134]<br>&nbsp;$dr
$rd$lng[135]</td><td>$i1=text name=delref size=10></td>
<td><div align=right>$lng[136] $i1=checkbox name=delfil unchecked></tr>
<tr><td colspan=3><div align=left>$lng[137]$dr</table><p><center>$hr<p>
$i1=hidden name=login value=$login>$i1=hidden name=pass value=$pass>
$i1=hidden name=fid value=$fid>$i1=hidden name=oper value=submit>$i1=submit value=$lng[8]></form><p></body></html>";

exit;


ARHIV:

if(index($stat,'h')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body>$lng[138]</body></html>";exit;}

print "<html><title>$lng[49] 5 &#151; $login</title><body bgcolor=#f0f0ff><font size=\"+2\"><center>$lng[50]<br><b>$login</b>,<font size=\"+1\"><br><i>$lng[51]<b>";
if(index($stat,'a')>=0){print ": $lng[52] "}
if(index($stat,'i')>=0){print ": $lng[53] "}
if(index($stat,'g')>=0){print ": $lng[54] "}
if(index($stat,'d')>=0){print ": $lng[55] "}
if(index($stat,'h')>=0){print ": $lng[56] "}
if(index($stat,'e')>=0){print ": $lng[57] "}
if(index($stat,'n')>=0){print ": $lng[58] "}
if(index($stat,'s')>=0){print ": $lng[59] "}

print "</b></i></font><p>$hr</center></font><p>$lng[139]<p><form action=$dircgi/wtbedit.cgi method=post><table width=100%>";
print "<tr><td colspan=3><font size=\"+1\"><center><b>$lng[140]<br>&nbsp;$dr
$rd$lng[141]</td><td>$i1=text name=dirarhiv size=10>$dr
$rd$lng[142]</td><td>$i1=text name=mesarhiv size=10>$dr
$rd$lng[143]</td><td>$i1=checkbox name=delarhiv>$dr
<tr><td colspan=3><div align=left>$lng[144]$dr</table><p><center>$hr<p>
$i1=hidden name=login value=$login>$i1=hidden name=pass value=$pass>
$i1=hidden name=fid value=$fid>$i1=hidden name=oper value=submit>$i1=submit value=$lng[8]></form><p></body></html>";

exit;


NEWS:

if(index($stat,'n')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body><h2>$lng[145]</h2></body></html>";exit;}
print "<html><title>$lng[49] 6 &#151; $login</title><body bgcolor=#f0f0ff><font size=\"+2\"><center>$lng[50]<br><b>$login</b>,<font size=\"+1\"><br><i>$lng[51]<b>";
if(index($stat,'a')>=0){print ": $lng[52] "}
if(index($stat,'i')>=0){print ": $lng[53] "}
if(index($stat,'g')>=0){print ": $lng[54] "}
if(index($stat,'d')>=0){print ": $lng[55] "}
if(index($stat,'h')>=0){print ": $lng[56] "}
if(index($stat,'e')>=0){print ": $lng[57] "}
if(index($stat,'n')>=0){print ": $lng[58] "}
if(index($stat,'s')>=0){print ": $lng[59] "}

print "</b></i></font><p>$hr</center></font><p>";
$daye=$t[3]+5;
print "<div align=justify><form action=$dircgi/wtbedit.cgi method=post><table width=100%>";
print "<tr><td colspan=8><font size=\"+1\"><center><b>$lng[146]<br>&nbsp;$dr
<tr><td colspan=3 width=30%>$lng[147]</td>
<td nowrap>$lng[148]<input type=text name=yearh size=2 maxlength=2 value=$t[5]></td>
<td nowrap>$lng[149] $i1=text name=monh size=2 maxlength=2 value=$t[4]></td>
<td nowrap>$lng[150] $i1=text name=dayh size=2 maxlength=2 value=$t[3]></td>
<td nowrap>$lng[151] $i1=text name=hourh size=2 maxlength=2 value=$t[2]></td>
<td nowrap>$lng[152] $i1=text name=minh size=2 maxlength=2 value=$t[1]>$dr
<tr><td colspan=3>$lng[153]</td>
<td nowrap>$lng[148]<input type=text name=yeare size=2 maxlength=2 value=$t[5]></td>
<td nowrap>$lng[149] $i1=text name=mone size=2 maxlength=2 value=$t[4]></td>
<td nowrap>$lng[150] $i1=text name=daye size=2 maxlength=2 value=$daye></td>
<td nowrap>$lng[151] $i1=text name=houre size=2 maxlength=2 value=$t[2]></td>
<td nowrap>$lng[152] $i1=text name=mine size=2 maxlength=2 value=$t[1]>$dr
<tr><td colspan=1>$lng[154]</td><td colspan=7>$i1=text name=newmessage size=55></td><tr>
<tr><td colspan=3 nowrap>$lng[155] $i1=checkbox name=setdate checked></td>
<td colspan=2 align=center nowrap>$lng[156] $i1=checkbox name=blinqued></td>
<td colspan=3 align=right nowrap>$lng[157] $i1=checkbox name=marqued checked>$dr
<tr><td colspan=2 nowrap align=left>$lng[158] $i1=checkbox name=italic></td>
<td colspan=2 nowrap align=center>$lng[159] $i1=checkbox name=bold checked></td>
<td colspan=2 nowrap align=center>$lng[160] $i1=checkbox name=underlined></td>
<td colspan=2 nowrap align=right>$lng[161] $i1=checkbox name=stronged>$dr
<tr><td colspan=4 nowrap align=left>$lng[162]<select name=fontsize><option>-4<option>-3<option>-2<option>-1<option value=+0>0<option selected>+1<option>+2<option>+3<option>+4</select></td>
<td colspan=4 nowrap align=left>$lng[163] $lng[164]$dr
<tr><td colspan=8>$lng[165] $i1=radio name=centered value=left checked>
$i1=radio name=centered value=center>
$i1=radio name=centered value=right>
$i1=radio name=centered value=justify>$dr
<tr><td colspan=10><div align=left>$lng[166]$dr</table><p><center>$hr<p>
$i1=hidden name=login value=$login>$i1=hidden name=pass value=$pass>
$i1=hidden name=fid value=$fid>$i1=hidden name=oper value=submit>$i1=submit value=$lng[8]></form><p></body></html>";

exit;


RESTORE:

if(index($stat,'s')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body>$lng[167]</body></html>";exit;}
print "<html><title>$lng[49] 7 &#151; $login</title><body bgcolor=#f0f0ff><font size=\"+2\"><center>$lng[50]<br><b>$login</b>,<font size=\"+1\"><br><i>$lng[51]<b>";
if(index($stat,'a')>=0){print ": $lng[52] "}
if(index($stat,'i')>=0){print ": $lng[53] "}
if(index($stat,'g')>=0){print ": $lng[54] "}
if(index($stat,'d')>=0){print ": $lng[55] "}
if(index($stat,'h')>=0){print ": $lng[56] "}
if(index($stat,'e')>=0){print ": $lng[57] "}
if(index($stat,'n')>=0){print ": $lng[58] "}
if(index($stat,'s')>=0){print ": $lng[59] "}

print "</b></i></font><p>$hr</center></font><p><table width=100%>
<tr><td colspan=3><font size=\"+1\"><center><b>$lng[168]<br>&nbsp;$dr
<tr><td align=center>$lng[169]</td><td align=center>$lng[170]$dr
<tr><td align=center><form action=$dircgi/wtbedit.cgi method=post>
$i1=hidden name=restoration value=genindex>$i1=hidden name=login value=$login>
$i1=hidden name=fid value=$fid>$i1=hidden name=pass value=$pass>$i1=hidden name=oper value=submit>
$i1=submit value=$lng[8]></form></td>
<td align=center><form action=$dircgi/wtbedit.cgi method=post>
$i1=hidden name=restoration value=genstr>$i1=hidden name=login value=$login>
$i1=hidden name=pass value=$pass>$i1=hidden name=oper value=submit>
$i1=hidden name=fid value=$fid>$i1=submit value=$lng[8]></form><p>$dr
<tr><td colspan=2>$hr$dr
<tr><td colspan=2><form action=$dircgi/wtbedit.cgi method=post>
<br><font size=\"+1\"><b><center>$lng[171]</center><br>$dr
$rd$lng[172] $i1=text name=begrest size=10><br></td>
<td>$lng[173] $i1=text name=endrest size=10>$dr
$rd$lng[174]</td><td>$i1=text name=namindex size=20>$dr
<tr><td align=center colspan=2><form action=$dircgi/wtbedit.cgi method=post>
$i1=hidden name=login value=$login>
$i1=hidden name=pass value=$pass>$i1=hidden name=oper value=submit>
$i1=hidden name=fid value=$fid>$i1=submit value=$lng[8]></form>$dr
<tr><td colspan=2>$lng[175]$dr</table></body></html>";

exit;



WRONGLOG:

if(index($stat,'i')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body>$lng[116]</body></html>";exit;}
print "<html><title>$lng[49] 2 &#151; $login</title><body bgcolor=#f0f0ff><font size=\"+2\"><center>$lng[50]<br><b>$login</b>,<font size=\"+1\"><br><i>$lng[51]<b>";
if(index($stat,'a')>=0){print ": $lng[52] "}
if(index($stat,'i')>=0){print ": $lng[53] "}
if(index($stat,'g')>=0){print ": $lng[54] "}
if(index($stat,'d')>=0){print ": $lng[55] "}
if(index($stat,'h')>=0){print ": $lng[56] "}
if(index($stat,'e')>=0){print ": $lng[57] "}
if(index($stat,'n')>=0){print ": $lng[58] "}
if(index($stat,'s')>=0){print ": $lng[59] "}

print "</b></i></font><p>$hr</center></font><p>
<font size=\"+1\"><center><b>$lng[242]</b><p><font size=\"-1\"> $hr</center><ol>";

open NAM,"$data/$wtwrong";@b=<NAM>;close NAM;chomp @b;@b=reverse @b;

for$i(0..@b-1)
{	@c=split(/[;=]/,$b[$i]);
	if(length $c[1]<1){$c[1]=$lng[243]}
	if(length $c[$#c]<1){$c[$#c]=$lng[244]}
	if(length $c[5]<1){$c[5]=$lng[245]}
	print "<li><i>$lng[246]</i> <b>$c[$#c]</b>; <i>$lng[247]</i> <b>$c[1]</b>; <i>$lng[248]</i> <b>$c[5]</b>; <i>$lng[249]</i> <b>";
	@c=split(/ /,$c[0]);
	if($c[0] eq 'BDADM'){print $lng[250]}
	elsif($c[0] eq 'WRONG'){print $lng[251]}
	elsif($c[0] eq 'REGST'){print $lng[252]}
	else{print $lng[253]}
	print "</b><br>\n"
}

print "</ul></font>$hr<p><dd>$lng[254]</body></html>";

exit;



### принятие изменений
SUBMIT:

undef $begindex;undef $endindex;

for $i(0..$#a)
{	if($a[$i] eq 'begindex'){$a[$i+1]=~s/$cr/<!>/g;}
	if($a[$i] eq 'endindex'){$a[$i+1]=~s/$cr/<!>/g;}
	if($a[$i] eq 'begmesform'){$a[$i+1]=~s/$cr/<!>/g;}
	if($a[$i] eq 'endmesform'){$a[$i+1]=~s/$cr/<!>/g;}
	if($a[$i] eq 'begansform'){$a[$i+1]=~s/$cr/<!>/g;}
	if($a[$i] eq 'endansform'){$a[$i+1]=~s/$cr/<!>/g;}
	if($a[$i] eq 'begarchive'){$a[$i+1]=~s/$cr/<!>/g;}
	if($a[$i] eq 'endarchive'){$a[$i+1]=~s/$cr/<!>/g;}
	if($a[$i] eq 'begmes'){$a[$i+1]=~s/$cr/<!>/g;}
	if($a[$i] eq 'endmes'){$a[$i+1]=~s/$cr/<!>/g;}
	if($a[$i] eq 'info'){$a[$i+1]=~s/$cr/<!>/g;}
}

# обновление wtboard.txt
open NAM,"$data/$wtboard";@b=<NAM>;close NAM;chomp @b;
rename "$data/$wtboard","$data/$wtboard.old";
open NAM,">$data/$wtboard";
for $i(0..$#b)
{	($b1,$b2)=split(/=/,$b[$i],2);
	if(length($b2)>0)
	{	$j=0;
		while($j<$#a)
		{	if($a[$j] eq $b1){if(defined $a[$j+1]){$b2=$a[$j+1];}}
			++$j;++$j;
		}
		print NAM "$b1=$b2\n";
	}
	else{print NAM "$b[$i]\n";}
}
close NAM;
undef @b;
if(-z "$data/$wtboard"==1){rename "$data/$wtboard.old","$data/$wtboard";}


# администрация
for $i(0..$#a)
{	if($a[$i] eq 'names'){@names=split(/$cr/,$a[$i+1]);}
}
if(defined @names)
{	rename "$data/$wtbnames","$data/$wtbnames.old";
	open NAM,">$data/$wtbnames";for $i(0..$#names){$names[$i]=~s/\|/;;/g;print NAM "$names[$i]\n";}close NAM;
	if(-z "$data/$wtbnames"==1){rename "$data/$wtbnames.old","$data/$wtbnames";}
	undef @names;
}

for $i(0..$#a)
{	if($a[$i] eq 'anam'){@anam=split(/$cr/,$a[$i+1]);}
	if($a[$i] eq 'apwd'){@apwd=split(/$cr/,$a[$i+1]);}
	if($a[$i] eq 'astat'){@astat=split(/$cr/,$a[$i+1]);}
}
if(defined @anam)
{	open NAM,">$data/$wtbadmin";
	for $i(0..$#anam){print NAM "$anam[$i];;$apwd[$i];;$astat[$i]\n";}
	close NAM;
	undef @anam;undef @apwd;undef @astat;
}



for $i(0..$#a)
{	$a[$i]=~s/\$thekonf/$thekonf/g;
	$a[$i]=~s/\$tokonf/$tokonf/g;
	$a[$i]=~s/\$ofkonf/$ofkonf/g;
	$a[$i]=~s/\$onkonf/$onkonf/g;
	$a[$i]=~s/\$dirkonf/$dirkonf/g;
	$a[$i]=~s/\$dircgi/$dircgi/g;
	$a[$i]=~s/\$admin/$admin/g;
	$a[$i]=~s/\$indbgcolor/$indbgcolor/g;
	$a[$i]=~s/\$indtcolor/$indtcolor/g;
	$a[$i]=~s/\$indlcolor/$indlcolor/g;
	$a[$i]=~s/\$indvlcolor/$indvlcolor/g;
	$a[$i]=~s/\$indalcolor/$indalcolor/g;
	$a[$i]=~s/\$indimg/$indimg/g;
	$a[$i]=~s/\$fid/$fid/g;
	$a[$i]=~s/\$separator/$hr/g;
}
for $i(0..$#a)
{	if($a[$i] eq 'begindex'){$begindex=$a[$i+1];}
	if($a[$i] eq 'endindex'){$endindex=$a[$i+1];}
}
if(defined $begindex)
{	open NAM,"$dirrealkonf/index.shtml";@ini=<NAM>;close NAM;
	open NAM,">$dirrealkonf/index.shtml";
	print NAM $begindex,"\n";print NAM @ini[1..$#ini-1];print NAM $endindex,"\n";
	close NAM;undef @ini;
	goto LAST;
}


open NAM,"$data/$wtboard";@b=<NAM>;close NAM;chomp @b;
for $i(0..$#b)
{	$b[$i]=~s/\$thekonf/$thekonf/g;
	$b[$i]=~s/\$tokonf/$tokonf/g;
	$b[$i]=~s/\$ofkonf/$ofkonf/g;
	$b[$i]=~s/\$onkonf/$onkonf/g;
	$b[$i]=~s/\$admin/$admin/g;
	$b[$i]=~s/\$dirkonf/$dirkonf/g;
	$b[$i]=~s/\$dircgi/$dircgi/g;
	$b[$i]=~s/\$indbgcolor/$indbgcolor/g;
	$b[$i]=~s/\$indtcolor/$indtcolor/g;
	$b[$i]=~s/\$indlcolor/$indlcolor/g;
	$b[$i]=~s/\$indvlcolor/$indvlcolor/g;
	$b[$i]=~s/\$indalcolor/$indalcolor/g;
	$b[$i]=~s/\$indimg/$indimg/g;
	$b[$i]=~s/\$fid/$fid/g;
	$b[$i]=~s/\$separator/$hr/g;
}
for $i(0..$#b)
{	if(index($b[$i],'begindex')==0){($a,$begindex)=split(/=/,$b[$i],2);}
	if(index($b[$i],'endindex')==0){($a,$endindex)=split(/=/,$b[$i],2);}
	if(index($b[$i],'begarchive')==0){($a,$begarchive)=split(/=/,$b[$i],2);}
	if(index($b[$i],'endarchive')==0){($a,$endarchive)=split(/=/,$b[$i],2);}
}
undef @b;


for $i(0..$#a)
{	if($a[$i] eq 'ignor'){@ignor=split(/$cr/,$a[$i+1]);}
	if($a[$i] eq 'ignort'){@ignort=split(/$cr/,$a[$i+1]);}
	if($a[$i] eq 'ignorm'){@ignorm=split(/$cr/,$a[$i+1]);}
	if($a[$i] eq 'private'){$private=$a[$i+1];}
}
if(defined @ignor)
{	open NAM,">$data/$wtbaccess";
	for $i(0..$#ignor){print NAM "$ignor[$i];;$ignort[$i];;$ignorm[$i]\n";}
	close NAM;
	undef @ignor;undef @ignort;undef @ignorm;
}


# редактирование индекса
for $i(0..$#a)
{	if($a[$i] eq 'nummes'){$nummes=$a[$i+1];}
	if($a[$i] eq 'editind'){$editind=$a[$i+1];}
}
if(defined $editind)
{	$s=chr(151);
	$editind=~s/$s/&#151;/g;
	open NAM,"$dirrealkonf/index.shtml";@ini=<NAM>;close NAM;
	open NAM,">$dirrealkonf/index.shtml";
	for $i(0..$#ini)
	{	if(index($ini[$i],"<!--$nummes-->")>=0){$ini[$i]=$editind."\n";}
		print NAM $ini[$i];
	}
	close NAM;
	goto LAST;
}

# новостная строка
for $i(0..$#a)
{	if($a[$i] eq 'newmessage'){$newmessage=$a[$i+1];}
}
if(defined $newmessage)
{	for $i(0..$#a)
	{	if($a[$i] eq 'yearh'){$yearh=$a[$i+1];}
		if($a[$i] eq 'monh'){$monh=$a[$i+1];}
		if($a[$i] eq 'dayh'){$dayh=$a[$i+1];}
		if($a[$i] eq 'hourh'){$hourh=$a[$i+1];}
		if($a[$i] eq 'minh'){$minh=$a[$i+1];}
		if($a[$i] eq 'yeare'){$yeare=$a[$i+1];}
		if($a[$i] eq 'mone'){$mone=$a[$i+1];}
		if($a[$i] eq 'daye'){$daye=$a[$i+1];}
		if($a[$i] eq 'houre'){$houre=$a[$i+1];}
		if($a[$i] eq 'mine'){$mine=$a[$i+1];}
		if($a[$i] eq 'setdate'){$setdate=$a[$i+1];}
		if($a[$i] eq 'marqued'){$marqued=$a[$i+1];}
		if($a[$i] eq 'blinqued'){$blinqued=$a[$i+1];}
		if($a[$i] eq 'centered'){$centered=$a[$i+1];}
		if($a[$i] eq 'colormes'){$colormes=$a[$i+1];}
		if($a[$i] eq 'italic'){$italic=$a[$i+1];}
		if($a[$i] eq 'bold'){$bold=$a[$i+1];}
		if($a[$i] eq 'underlined'){$underlined=$a[$i+1];}
		if($a[$i] eq 'stronged'){$stronged=$a[$i+1];}
		if($a[$i] eq 'fontsize'){$fontsize=$a[$i+1];}
	}

	$newmessage=~s/ - / &#151; /g;
	$newmessage=~s/--/&#151;/g;
	open NAM,"+>>$data/$wtbnews";
	print NAM "$yearh;;$monh;;$dayh;;$hourh;;$minh;;$yeare;;$mone;;$daye;;$houre;;$mine;;";

	print NAM "<font size=\"$fontsize\" color=#$colormes><div align=$centered>";
	if($setdate eq 'on'){printf NAM ('<b>%2.2d:%2.2d <i>%2.2d/%2.2d/%2.2d</i></b>',$hourh,$minh,$dayh,$monh,$yearh)}
	if($blinqued eq 'on'){print NAM "<blink>"}
	if($marqued eq 'on'){print NAM "<marquee>"}
	if($italic eq 'on'){print NAM "<i>"}
	if($bold eq 'on'){print NAM "<b>"}
	if($underlined eq 'on'){print NAM "<u>"}
	if($stronged eq 'on'){print NAM "<strike>"}

	print NAM " $newmessage";

	if($stronged eq 'on'){print NAM "</strike>"}
	if($underlined eq 'on'){print NAM "</u>"}
	if($bold eq 'on'){print NAM "</b>"}
	if($italic eq 'on'){print NAM "</i>"}
	if($marqued eq 'on'){print NAM "</marquee>"}
	if($blinqued eq 'on'){print NAM "</blink>"}
	print NAM "</div></font><p>\n";

	close NAM;
}

# структура
for $i(0..$#a)
{	if($a[$i] eq 'restoration'){$restor=$a[$i+1];}
}
if($restor eq 'genindex')	# восстановление индекса из структуры
{	open NAM,"$data/$wtbstruct";@a=<NAM>;close NAM;chomp @a;
	open NAM,">$dirrealkonf/index.shtml";
	print NAM "$begindex\n<ul>\n<!--home-->";
	for $i(1..$#a)
	{	while(index($a[$i],'()')>0){$a[$i]=~s/\(\)//g;}
		$a[$i]=~s/ //g;
		if(length $a[$i]<2){goto NEXTING}
		@b=split(/([(.,*)])/,$a[$i]);
		for $j(0..$#b)
		{	if($b[$j] eq '('){print NAM "\n<ul><!--".$b[$j+1]."--><li><a href=".$b[$j+1].".$ext>"}
			elsif($b[$j] eq ')'){print NAM "\n</ul>"}
			elsif($b[$j] eq '*'){print NAM "\n<!--".$b[$j+1]."--><li>* <a href=".$b[$j+1].".$ext>"}
			elsif($b[$j] eq ','){print NAM "\n<!--".$b[$j+1]."--><li>** <a href=".$b[$j+1].".$ext>"}
			elsif($b[$j] eq '.'){print NAM "\n<!--".$b[$j+1]."--><li><a href=".$b[$j+1].".$ext>"}
			elsif(length $b[$j] <1){next}
			else
			{	for$ja(0..3)
				{	if(-e "$dirrealkonf/$b[$j].$exts[$ja]"!=1){next}
					else{$ia=$ja;last}
				}
				if(-e "$dirrealkonf/$b[$j].$exts[$ia]" !=1)
				{	print NAM "$lng[176]</a>";
				}
				else
				{	open FILE,"$dirrealkonf/$b[$j].$exts[$ia]";@c=<FILE>;close FILE;
					$c[0]=~m/<title>(.*?)<\/title>/;
					print NAM "$1</a> &#151; <b>";
					@d=split(/[<>]/,$c[2]);
					$c[2]=~m/\">(.*?)<\/a>/ig;$b[2]=~m/<b>(.*?)<\/b>/ig;
					print NAM "$1</b> <i>";
					$c[2]=~m/<\/b> <i>(.*?)<\/i>/ig;
					print NAM "$1 </i>(";

					$cnt=-1;for $k(0..$#c){if(index($c[$k],'<ul>')==0){++$cnt}};
					undef @d;undef@c;
					print NAM "$cnt)";
				}
			}
		}
NEXTING:
	}
	print NAM "\n$endindex";
	close NAM;
	goto LAST;
}
elsif($restor eq 'genstr')		# генерация структуры из индекса
{	open NAM,"$dirrealkonf/index.shtml";@a=<NAM>;close NAM;
	open NAM,">$data/$wtbstruct";
	$i=3;
	while($i<$#a)
	{	@b=split('--',$a[$i]);
		if(index($a[$i],'<ul>')==0){print NAM "($b[1]";}
		elsif(index($a[$i],'</ul>')==0){print NAM ")";}
		elsif(index($a[$i],'<li>* ')>0){print NAM "\n*$b[1]";}
		elsif(index($a[$i],'<li>** ')>0){print NAM "\n,$b[1]";}
		else{print NAM "\n.$b[1]";}
		++$i;
	}
	print NAM "\n";
	close NAM;
	goto LAST;
}


# восстановление индекса только из сообщений
for $i(0..$#a)
{	if($a[$i] eq 'begrest'){$begrest=$a[$i+1];}
	if($a[$i] eq 'endrest'){$endrest=$a[$i+1];}
	if($a[$i] eq 'namindex'){$namindex=$a[$i+1];}
}
if(defined $namindex)
{	$j=0;
	for $i($begrest..$endrest)
	{	for$ja(0..3)
		{	if(-e "$dirrealkonf/$i.$exts[$ja]"!=1){next}
			else{$ia=$ja;last}
		}
		open FILE,"$dirrealkonf/$i.$exts[$ia]";@b=<FILE>;close FILE;
		@c=split('numans=',$b[0]);$b[0]=$c[1];
		@c=split('>',$b[0]);$b[0]=$c[0];
		@c=split(';',$b[0]);
		if($#c==0){$rest[$j]=$i;++$j;}
	}
	@rest=reverse(@rest);
	undef @b;undef @c;

	open NAM,">$dirrealkonf/$namindex";
	print NAM "$begarchive\n<ul>\n<!--home-->\n";

	$i=0;while($i<=$#rest)
	{	for$ja(0..3)
		{	if(-e "$dirrealkonf/$rest.$exts[$ja]"!=1){next}
			else{$ia=$ja;last}
		}
		open FILE,"$dirrealkonf/$rest[$i].$exts[$ia]";@b=<FILE>;close FILE;
		print NAM "<!--".$rest[$i]."--><li><a href=".$rest[$i].".$exts[$ia]>";

		$b[0]=~m/<title>(.*?)<\/title>/;
		print NAM "$1</a> &#151; <b>";
		$b[2]=~m/\">(.*?)<\/a>/ig;$b[2]=~m/<b>(.*?)<\/b>/ig;
		print NAM "$1</b> <i>";
		$b[2]=~m/<\/b> <i>(.*?)<\/i>/ig;
		print NAM "$1 </i>(";
		$cnt=-1;for $k(0..$#b){if(index($b[$k],'<ul>')==0){++$cnt}};
		undef @d;
		print NAM "$cnt)\n";
        	
		$k=0;while($k<=$#b)
		{	if(index($b[$k],"<!--$rest[$i]-->")==0)
			{	++$k;while(index($b[$k],'<!--end-->')!=0)
				{print NAM $b[$k];++$k;}
			}
			++$k;
		}
		++$i;
	}
	print NAM "$endarchive";
	close NAM;
	print "$lng[177]<p><pre>[&lt;a href=./$namindex&gt;$lng[178]&lt;/a&gt;]</pre><p>";
	goto LAST;
}


# удаление
for $i(0..$#a)
{	if($a[$i] eq 'delref'){@delref=split(/ /,$a[$i+1]);}
	if($a[$i] eq 'delfil'){$delfil=$a[$i+1];}
}
if(defined @delref)
{	for $m(0..$#delref)
{	$delref=$delref[$m];

	open NAM,"$data/$wtbstruct";@ini=<NAM>;close NAM;chomp @ini;
	open NAM,">$data/$wtbstruct";
	$i=0;
	while($i<=$#ini)
	{	@b=split(/([(.,*)])/,$ini[$i]);chomp @b;
		$j=0;while($j<=$#b)
		{	if($b[$j] eq $delref){undef $b[$j];}
			print NAM $b[$j];
			++$j;
		}
		print NAM "\n";
		++$i
	}
	close NAM;
	open NAM,"$dirrealkonf/index.shtml";@ini=<NAM>;close NAM;
	open NAM,">$dirrealkonf/index.shtml";
	$j=0;
	$i=0;while($i<=$#ini)
	{	if(index($ini[$i],"<!--$delref-->")==0)
		{	++$i;
			if(index($ini[$i],"<!--")!=0)
			{	$u=1;++$i;
				while($u>0)
				{	while(index($ini[$i],'</ul>')<0){++$u;++$i;}
					--$u;++$i;
				}
			}
		}
		elsif(index($ini[$i],"<!--$delref-->")>0)
		{	$u=1;++$i;
			while($u>0)
			{	while(index($ini[$i],'</ul>')<0){++$u;++$i;}
				--$u;++$i;
			}
		}
		print NAM $ini[$i];
		++$i;
	}
	close NAM;
}
}
if($delfil eq 'on')
{	for $m(0..$#delref)
{	$delref=$delref[$m];
	for$j(0..3)
	{	if(-e "$dirrealkonf/$delref.$exts[$j]"!=1){next}
		else{$ia=$j;last}
	}
	open NAM,"$dirrealkonf/$delref.$exts[$ia]";@ini=<NAM>;close NAM;
	$i=0;$j=0;
	while($i<$#ini)
	{	if(index($ini[$i],'<!--home-->')==0)
		{	++$i;$j=0;
			while(index($ini[$i],'<!--end-->')<0)
			{	if(index($ini[$i],'</ul>')==0){++$i;}
				else {($a,$numdel[$j],$a)=split(/--/,$ini[$i],3);++$i;++$j;}
			}
		}
		if(not defined @numclear and index($ini[$i],'&numans=')>0)
		{	@b=split(/[&,=]/,$ini[$i]);
			for $j(0..$#b)
			{	if($b[$j] eq 'numans')
				{@numclear=split(/;/,$b[$j+1]);}
			}
			undef @b;
			--$#numclear;
		}
		++$i;
	}
	undef @ini;

	for $k(0..$#numclear)
	{	for$j(0..3)
		{	if(-e "$dirrealkonf/$numclear[$k].$exts[$j]"!=1){next}
			else{$ia=$j;last}
		}
		open NAM,"$dirrealkonf/$numclear[$k].$exts[$ia]";@ini=<NAM>;close NAM;
		@datn=stat("$dirrealkonf/$numclear[$k].$exts[$ia]");
		open NAM,">$dirrealkonf/$numclear[$k].$exts[$ia]";
		$j=0;
		$i=0;while($i<=$#ini)
		{	if(index($ini[$i],"<!--$delref-->")==0)
			{	++$i;
				if(index($ini[$i],"<!--")!=0)
				{	$u=1;++$i;
					while($u>0)
					{	while(index($ini[$i],'</ul>')<0){++$u;++$i;}
						--$u;++$i;
					}
				}
			}
			elsif(index($ini[$i],"<!--$delref-->")>0)
			{	$u=1;++$i;
				while($u>0)
				{	while(index($ini[$i],'</ul>')<0){++$u;++$i;}
					--$u;++$i;
				}
			}
			print NAM $ini[$i];
			++$i;
		}
		close NAM;
		utime ($datn[9],$datn[9],"$dirrealkonf/$numclear[$k].$exts[$ia]");
		undef @ini;
	}
	undef @numclear;

	for $i(0..$#numdel)
	{rename "$dirrealkonf/$numdel[$i].$exts[$ia]","$dirrealkonf/util.htm";}
	undef @numdel;
}
}


# архивация
for $i(0..$#a)
{	if($a[$i] eq 'dirarhiv'){$dirarhiv=$a[$i+1];}
	if($a[$i] eq 'mesarhiv'){$mesarhiv=$a[$i+1];}
	if($a[$i] eq 'delarhiv'){$delarhiv=$a[$i+1];}
}

if(defined $mesarhiv)
{	if(defined "$realpath/$dirarhiv" and $delarhiv ne 'on')
	{$i=mkdir "$realpath/$dirarhiv",777;}

	if($delarhiv ne 'on' and -e "$realpath/$dirarhiv" !=1)
	{print "<html><title>lng[188]</title><body>$lng[179] $ended";exit;}

	open NAM,"$dirrealkonf/index.shtml";@ini=<NAM>;close NAM;
#	open NAM,">$dirrealkonf/index.shtml";
	$mmm=0;$m=0;for $i(0..$#ini)
	{	if(index($ini[$i],"<!--$mesarhiv-->")==0){$m=1;$j1=$i;$mmm=1;}
		if(index($ini[$i],"<!--end-->")==0){$m=0;$j2=$i-1;}
#		if($m==0){print NAM $ini[$i];}
	}
#	close NAM;

	if($mmm==0){print "<html><title>$lng[188]</title><body>$lng[180] $ended";exit;}

	$j=0;for $i($j1..$j2)
	{	if(index($ini[$i],'<li>')>=0){($a,$forarc[$j],$a)=split(/--/,$ini[$i],3);++$j;}
	}

	if(defined "$realpath/$dirarhiv" and $delarhiv ne 'on')
	{	open NAM,"+>$realpath/$dirarhiv/index.htm";
		print NAM "$begarchive\n<ul>\n<!--home-->\n";
		for $i($j1..$j2)
		{	print NAM $ini[$i];
		}
		print NAM $endarchive;
	}
	if(-e "$realpath/$dirarhiv/index.htm" !=1)
	{print "<html><title>$lng[188]</title><body>$lng[180] $ended";exit;}


	for $i(0..$#forarc)
	{	if($delarhiv ne 'on')
		{	for$j(0..3)
			{	if(-e "$dirrealkonf/$forarc.$exts[$j]"!=1){next}
				else{$ia=$j;last}
			}

			if(-e "$dirrealkonf/$forarc[$i].$exts[$ia]" ==1)
			{	open NAM,"$dirrealkonf/$forarc[$i].$exts[$ia]";@b=<NAM>;close NAM;

				for $j(0..$#b){$b[$j]=~s/root=off/root=on/;}
				for $j(0..$#b){$b[$j]=~s/\&numans=/&arc=..\/$dirarhiv\/$forarc[$i].html\&numans=/;}
				for $j(0..$#b){$b[$j]=~s/$dirkonf/$dirarhiv/g;}

				open NAM,"+>$realpath/$dirarhiv/$forarc[$i].html";
				print NAM @b;
				close NAM;
				undef @b;
			}
			if(-e "$realpath/$dirarhiv/$forarc[$i].html" ==1){if("$realpath/$dirarhiv/$forarc[$i].html" ne "$dirrealkonf/$forarc[$i].$exts[$ia]"){rename "$dirrealkonf/$forarc[$i].$exts[$ia]","$dirrealkonf/util.htm";}}
		}
		else
		{	for$j(0..3)
			{	if(-e "$dirrealkonf/$forarc.$exts[$j]"!=1){next}
				else{$ia=$j;last}
			}
			rename "$dirrealkonf/$forarc[$i].$exts[$ia]","$dirrealkonf/util.htm";
		}
	}

	open NAM,">$dirrealkonf/index.shtml";
	for $i(0..$j1-1){print NAM $ini[$i]};
	for $i($j2+1..$#ini){print NAM $ini[$i]};
	close NAM;


	open NAM,"$data/$wtbstruct";@b=<NAM>;close NAM;
	open NAM,">$data/$wtbstruct";
	for $i(0..$#b)
	{	@c=split(/[(.,*)]/,$b[$i]);
		if($c[1] eq $mesarhiv){last;}
		print NAM $b[$i]
	}
	close NAM;


	if($delarhiv ne 'on' and defined "$realpath/$dirarhiv")
	{	open NAM,">>$data/$wtboard";print NAM "archive=$dirarhiv\n";close NAM;
		print "$lng[182] <p><pre>[&lt;a href=../$dirarhiv/&gt;$lng[183]&lt;/a&gt;]</pre><p>";
	}
}

LAST:

print "<html><title>$lng[189]</title><body>$lng[184] $ended";

exit;


ERROR:
print "<html><title>$lng[188]</title><body>$lng[185] $ended";
exit;



# подпрограмма коррекции имени
sub correct($)
{$_[0]=~s/&#(\d*?);/chr($1)/eg;$_[0]=lc $_[0];
$_[0]=~s/[ \;\.\,\_\-]//g;
$_[0]=~tr/АВЕЗКМНОРСТУХаеиопрсух01ч/ABE3KMHOPCTYXaeuonpcyxOlr/;
$_[0]=lc $_[0];
}



sub replacx($)
{$_[0] =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;}

