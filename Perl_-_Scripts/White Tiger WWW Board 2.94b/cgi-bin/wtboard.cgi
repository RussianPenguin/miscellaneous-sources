#!/usr/bin/perl

# White Tiger WWW Board ver.2.936b
# система wwwboard. Разработка, реализация
# (C) 1998-2000, White Tiger (2:5049/91.38; 
# email:wtiger@mail.ru; http://wtiger.ncport.ru)
# wtboard.cgi - модуль обеспечения работы форума
# wtboard.cgi - general wtboard script

# замена переменных производится в файле wtbext.cgi
# you must change values in the wtbext.cgi
















# прочие величины
if(!-e"wtbext.cgi"){print "Content-type: TEXT/HTML\n\nError: not found wtbext.cgi";exit}
require "wtbext.cgi";
params(1);
$nopass=0;

if($inip{'treestyle'}!=1){$allowroot='off'}

if($inip{'externalcalls'} eq 'on'){eval $inip{'externalcall0'}}	# внешний вызов 0

# обработка cookie

# проверка доступа с запрещенного ip-адреса или запрещенного по cookie
$s=&verifyuser($lng1,$lng2);
if($s==-1){print "\n",$t1,"$lng1</title>$begbody<h3>$lng2</h3>$endbody";exit;}
if($s==-2){print "\n",$t1,"$lng1</title>$begbody<h3>$lng2</h3>$endbody";exit;}


# подстановка имени и e-mail
$xlogin=$realn;
$xemail=$mails;$inip{'xemail'}=$xemail;
$xpwd=$pwd;
if($inip{'setpass'} ne 'on'){undef $xpwd}

if($inip{'substip'} eq 'on')
{	if(!$su){while(($s1,$s2)=each%wtbuser){if($s1=~/^h_(.*?)\Z/){if($s2 eq $ipaddr){$xlogin=$wtbuser{"n_$1"};$xemail=$wtbuser{"m_$1"};$su=1;last;}}}}
	if(!$su){while(($s1,$s2)=each%wtbuser){if($s1=~/^h_(.*?)\Z/){chop$s2;if($s2 eq $ipaddr){$xlogin=$wtbuser{"n_$1"};$xemail=$wtbuser{"m_$1"};$su=1;last;}}}}
	$xlogin=~s/\"/&quot;/g;
}

if(length($xlogin)<=0){$xemail='';}

# установка пользовательских шаблонов
if($inip{'allowgreetings'} eq 'on')
{	$hello=$wtbuser{"gh_$names"};
	$goodbye=$wtbuser{"gg_$names"};
	$ahello=$wtbuser{"gah_$names"};
	$agoodbye=$wtbuser{"gag_$names"};

	srand(time^$$);
	@hello=split(/\|/,$hello);@ahello=split(/\|/,$ahello);@goodbye=split(/\|/,$goodbye);@agoodbye=split(/\|/,$agoodbye);
	for($hello,$ahello,$goodbye,$agoodbye)
	{	chomp;
		replacx($_);
		@s=split(/\|/);
		$_=$s[rand(@s)];
		s/&/&amp;/g;s/</&lt;/g;s/>/&gt;/g;
	}
	if(length$ahello<=0){$ahello=$hello}
	if(length$agoodbye<=0){$agoodbye=$goodbye}
}

# если содержатся post-данные: то переходим к приему сообщения, иначе - форма.
# при USER - форма параметров пользователя, при UPDATE - принятие изменений
for$i(0..$#a)
{	if($a[$i] eq 'user'){goto USER;}
	if($a[$i] eq 'update'){goto UPDATE;}
	if($a[$i] eq 'mpreview'){goto SUBMIT;}
	if($a[$i] eq 'about'){&about; exit;}
}
if($CONTENT_LENGTH>0){goto SUBMIT}




NOPASS:
### генерация формы

for$i(0..$#a)
{	if($a[$i] eq 'notitle'){$notitle='on'}
}

if($notitle eq 'on' and $inip{'includeform'} eq 'off'){print "\n ";exit}

replacx($root);replacx($numans);replacx($arc);
$arc=~s/\+/ /g;
$arc=~s/\\/\//g;


#if(!length$root){($a,$b)=&verifyreg;$a=~s/<p><dd>//;print "\n$t1$lng[46]</title>$begbody$lng[47]<P>$a $endbody";exit;}
if(!length$root){$a=~s/<p><dd>//;print "\n$t1$lng[46]</title>$begbody$lng[47]<P>$endbody";exit;}


# распаковка предыдущих номеров
@prev=split(';',$numans);
$prev=$prev[$#prev];


if($nopass>0)
{	for($a){s/&/&amp;/gi;s/</&lt;/gi;s/>/&gt;/gi;s/$cr/$cl/g}
	$them=$subj;
	$them=~s/\"/&quot;/g;
	$patp{'begansform'}=~s/\$subj/$them/g;
	$patp{'endansform'}=~s/\$subj/$them/g;
	$xpwd=$pass;

	if($urltitle eq 'http://'){undef$urltitle}
	if($nopass==2){undef $xpwd}
}
else
{$url="http://";$urltitle='';$img="http://";$a='';
}

if($nopass==0 and $root eq 'off')
{	for$i(0..4)
	{	if(-e "$inip{'dirrealkonf'}/$prev\.$exts[$i]"!=1){next;}
		filestp("$inip{'dirrealkonf'}/$prev\.$exts[$i]");last;
	}
	$them=$stp[1];
	$them=~s/\"/&quot;/g;
	$patp{'begansform'}=~s/\$subj/$them/g;
	$patp{'endansform'}=~s/\$subj/$them/g;

	if($inip{'quoting'} eq 'on' and $inip{'uquoting'} ne 'off')
	{	$a=$inip{'quote'}.' '.$stp[24];
		chomp $a;
		$a=~s/&nbsp;$inip{'paragraph'}$inip{'quotebeg'}$inip{'quote'}(.*?)$inip{'quoteend'}$inip{'endparagraph'}/&nbsp;$inip{'paragraph'}$inip{'quote'}$1$inip{'endparagraph'}/g;
		$a=~s/$inip{'endparagraph'}&nbsp;$inip{'paragraph'}//;
		$a=~s/$inip{'endparagraph'}&nbsp;$inip{'paragraph'}/$c$inip{'quote'} /g;
		$a=~s/$inip{'quote'} $inip{'quote'}/$inip{'quote'}$inip{'quote'}/g;
		$a=~s/$inip{'endparagraph'}//g;
		if($inip{'smiles'} eq 'on')
		{	$a=~s/<font face=\"Wingdings\">J<\/font>/\:-\)/g;
			$a=~s/<font face=\"Wingdings\">K<\/font>/\:-\|/g;
			$a=~s/<font face=\"Wingdings\">L<\/font>/\:-\(/g;
		}
		if(length$a<3){$a=''}
	
	}
	# замена контекстных вхождений
	if($inip{'contextreplace'})
	{	open NAM,"$data/$wtbreplace";
		$i=0;while(<NAM>){chomp;($rd[$i],$rs[$i])=split(';;');($rs[$i],$s)=split(/\\\;\//,$rs[$i]);++$i;}
		close NAM;$s=$#rs;
		for($i=$#rs;$i>=0;--$i)
		{	$repside=0;$regexp=0;
			if(index($rd[$i],';')==0){next}
			if(index($rd[$i],'*')==0){$rd[$i]=~s/\*//;$repside=0}
			elsif(index($rd[$i],'#')==0){$rd[$i]=~s/#//;$repside=1}
			elsif(index($rd[$i],'@')==0){$rd[$i]=~s/\@//;$repside=2}
			if(index($rd[$i],'%')==0){$rd[$i]=~s/%//;$regexp=1}
			if(index($rd[$i],'!')==0){$rd[$i]=~s/!//;if($inip{'setreplace'} eq 'off'){next}}
			if(index($rd[$i],'>')==0){$regexp=0;next}
			if(index($rd[$i],'<')==0){$rd[$i]=~s/<//}
			if(index($rd[$i],"\\")==0){$rd[$i]=~s/\\//}
			if($regexp==1)
			{	if($repside==0 or $repside==1){$them=~s/$rs[$i]/$rd[$i]/eegi}
				if($repside==0 or $repside==2){$a=~s/$rs[$i]/$rd[$i]/eegi}
			}
			else
			{	if($repside==0 or $repside==1){$them=~s/\Q$rs[$i]/$rd[$i]/gi}
				if($repside==0 or $repside==2){$a=~s/\Q$rs[$i]/$rd[$i]/gi}
			}
		}
	}

	if($inip{'quotesize'})
	{	$i=0;
		while($a=~s/(.{$'inip{'quotesize'},}?[\!\.\?\"\'] )//)
		{$s[$i]="$inip{'quote'} $1";++$i;}
		$s[$i]="$inip{'quote'} $a";
		$a=join("$c",@s);
		$a=~s/$inip{'quote'} $inip{'quote'}/$inip{'quote'}$inip{'quote'}/g;
	}

	$a=~s/&/&amp;/g;$a=~s/</&lt;/g;$a=~s/>/&gt;/g;


	if(index($them,"$inip{'reply'}:")!=0 && index($them,"$inip{'reply'} (")!=0 && length$inip{'reply'}){$them="$inip{'reply'}: ".$them}
	elsif(index($them,"$inip{'reply'}:")==0){$them=~s/$inip{'reply'}:/$inip{'reply'} (2):/;}
	else{$them=~s/$inip{'reply'} \((\d+)\)/join('',"$inip{'reply'} \(",$1+1,')')/eg;}

	if($notitle eq 'on' and $inip{'includeform'} eq 'on'){$a=''}
}


if(!$nopass and $inip{'individual'} eq 'on' and $inip{'usecookie'} eq 'on')
{	if($root ne 'on'){$hello=$ahello;$goodbye=$agoodbye}
	for($hello,$goodbye)
	{	s/(%|\$)toname/$stp[2]/gi;
		$stp[2]=~/(\S+?)(\s|\Z|\.|\,)/;$s=$1;s/(%|\$)tofname/$s/gi;
		s/(%|\$)fromname/$stp[30]/gi;
		$stp[30]=~/(\S+?)(\s|\Z|\.|\,)/;$s=$1;s/(%|\$)fromfname/$s/gi;
		s/(%|\$)name/$realn/gi;
		$realn=~/(\S+?)(\s|\Z|\.|\,)/;$s=$1;s/(%|\$)fname/$s/gi;
		s/(%|\$)subject/$stp[1]/gi;
		s/(%|\$)number/$stp[38]/gi;
		s/(%|\$)shortmtime/$stp[5]:$stp[7]/gi;
		s/(%|\$)fullmtime/$stp[5]:$stp[7]:$stp[9]/gi;
		s/(%|\$)shortmdate/$stp[13]\/$stp[15]\/$stp[18]/gi;
		s/(%|\$)fullmdate/$stp[13]\/$stp[15]\/$stp[19]/gi;
		s/(%|\$)shortwmdate/$stp[13] $stp[17] $stp[18]/gi;
		s/(%|\$)fullwmdate/$stp[13] $stp[17] $stp[19]/gi;
	}

	if(length$hello){$a=$hello.$cl.$cl.$a};
	if(length$goodbye){$a=$a.$cl.$cl.$goodbye};

}

$stp[40]=~s/.*\.//;@s=split(';',$stp[40]);if(($#s+2)>$setnroot and $setnroot!=0){$nroot='on'}

if($root eq 'on' and $nroot ne 'on'){$begform=$patp{'begmesform'};$endform=$patp{'endmesform'};$lenemail=$inip{'lenemailmes'}}
else{$begform=$patp{'begansform'};$endform=$patp{'endansform'};$lenemail=$inip{'lenemailans'}}
if($inip{'allowroot'} ne 'on'){$lenemail=$inip{'lenemailmes'}}

if($notitle ne 'on'){substit($begform);print "\n$begform";}
else{print "\n<p>$inip{'separator'}<p>";}

if($inip{'private'} ne 'noprivate'){print "\n$lng[45]<p>$inip{'separator'}"}

if($nopass>0)
{	substit($lng[498],$patp{'nopasstext'});
	substit($lng[499],$patp{'wrnpasstext'});
	substit($lng[500],$patp{'nonametext'});
	substit($lng[501],$patp{'nosubjtext'});
	substit($lng[502],$patp{'prevmodetext'});
	print "<center><b><i><font color=#ff0000><blink>$lng[497+$nopass]</blink></font></i></b></center><p>$inip{'separator'}<p>"
}

print "\n<form$formencodetype action=$inip{'dircgi'}/wtboard.cgi method=post><p>$i1=hidden name=fid value=$fid>\n<table width=100% align=center border=0>";

if(!$inip{'passstyle'})
{	print "<tr><td>$lng[1]</td><td colspan=3>$i1=text name=login size=$inip{'lensubj'} value=\"$xlogin\"></td></tr>\n";
}
else
{	print "<tr><td>$lng[1]</td><td>$i1=text name=login size=$inip{'lenlogin'} value=\"$xlogin\"></td>
	<td>$lng[2]</td> <td>$i1=password name=pass size=$inip{'lenpass'} value=\"$xpwd\"></td></tr>\n";
}
print "<tr><td>E-Mail:</td>";
(($root eq 'off' or $nroot eq 'on') and $inip{'allowroot'} eq 'on') ? print "<td>" : print "<td colspan=3>";
print "$i1=text name=email size=$lenemail value=\"$xemail\"></td>";
if($nroot eq 'on'){$s=' checked'}else{$s=' unchecked'}
if($root ne 'on' and $inip{'allowroot'} eq 'on'){print "<td>$lng[9]</td><td>$i1=checkbox name=nroot$s></td>"}
print "</tr>\n<tr><td>$lng[3]</td>\n<td colspan=3>$i1=text name=subj size=$inip{'lensubj'} maxlength=\"$inip{'maxsubj'}\" value=\"$them\"></td></tr>\n$i1=hidden name=numans value=$numans>$i1=hidden name=root value=$root>$i1=hidden name=date value=$curtime/$t[6]>";
if(defined $arc){print "$i1=hidden name=arc value=\"$arc\">";}
print "\n<tr><td colspan=4 align=center>$lng[4]<br><textarea name=xbody cols=$inip{'lencols'} rows=$inip{'lenrows'} wrap=virtual>$a</textarea></td></tr>\n";

if($inip{'showurl'} ne 'off' and $inip{'seturl'} eq 'on'){print "<tr><td>$lng[5]</td><td colspan=3>$i1=text name=url value=\"$url\" size=$inip{'lenurl'} maxlength=\"$inip{'maxurl'}\"></td></tr>\n<tr><td>$lng[6]</td><td colspan=3>$i1=text name=urltitle size=$inip{'lentitleurl'} value=\"$urltitle\" maxlength=\"$inip{'maxurl'}\"></td></tr>\n";}
if($inip{'showimg'} ne 'off' and $inip{'setimg'} eq 'on'){print "<tr><td>$lng[7]</td><td colspan=3>$i1=text name=img value=\"$img\" size=$inip{'lenimg'} maxlength=\"$inip{'maxurl'}\"></td></tr>\n";}

if($inip{'externalcalls'} eq 'on'){eval $inip{'externalcall1'}}	# внешний вызов 1

print "<tr><td colspan=4>&nbsp;<br><center>$i1=submit value=$lng[8]>";

if($inip{'preview'} eq 'on' and $inip{'upreview'} ne 'off'){substit($lng[538],$patp{'prevbuttontext'});print "$i1=submit name=mpreview value=\"$lng[538]\">"}
if($inip{'resetbutton'} eq 'on' and $inip{'uresetbutton'} eq 'on'){substit($lng[539],$patp{'resetbuttontext'});print "$i1=submit name=reset value=\"$lng[539]\">"}

print "</td></tr>\n</table><p>";
if($notitle ne 'on')
{	if($inip{'individual'} eq 'on' && length$xlogin && $inip{'passstyle'}){print "<center><font size=-1><i><a href=$inip{'dircgi'}/wtboard.cgi?user&fid=$fid>$lng[32]</a></i></font>"};
	substit($endform);print $endform;
}
undef $a;

exit;


### прием сообщения, проверка пароля, внесение в базу
SUBMIT:


for(@cks)
{	($a1,$a2)=split('=',$_,2);
	if($a1 eq 'login'){$login=$a2}
	if($a1 eq 'pass'){$pass=$a2}
	if($a1 eq 'email'){$email=$a2}
	if($a1 eq 'root'){$root=$a2}
	if($a1 eq 'nroot'){$nroot=$a2}
	if($a1 eq 'subj'){$subj=$a2}
	if($a1 eq 'numans'){$numans=$a2}
	if($a1 eq 'date'){$date=$a2}
	if($a1 eq 'arc'){$arc=$a2}
	if($a1 eq 'xbody'){$xbody=$a2}
	if($a1 eq 'url'){$url=$a2}
	if($a1 eq 'urltitle'){$urltitle=$a2}
	if($a1 eq 'img'){$img=$a2}
}


$prev=$numans;$prev=~s/.*;(\d+?)\Z/$1/;@prev=$prev;

# наличие полей
$logs=$login;
correct($logs);
if(length $logs<=0){$a=$xbody;$nopass=3;$xlogin=$login;$xemail=$email;goto NOPASS}
if(length $subj<=0){$a=$xbody;$nopass=4;$xlogin=$login;$xemail=$email;goto NOPASS}

if($mpreview){$a=$xbody;$nopass=5;$xlogin=$login;$xemail=$email;goto PUBLICATION}
if($inip{'passstyle'} and !length$pass){$a=$xbody;$nopass=1;$xlogin=$login;$xemail=$email;goto NOPASS}

if($nroot eq 'on' and !$nopass){$root='on'}

# запрет публикации по игнор-листу
open NAM,"$data/$wtbaccess";@b=<NAM>;close NAM;chomp @b;
for $i(0..$#b)
{	$s=&verifyuser($lng1,$lng2);
	@c=split(';;',$b[$i]);

	if('-'.$logs eq $c[0] or '!'.$logs eq $c[0])
	{print "\n$t1$lng1</title>$begbody<h3>$lng2</h3>$endbody";exit}

	$notip=$REMOTE_ADDR;
	substit($lng[29],$patp{'noaccessbegin'});
	substit($lng[578],$patp{'readonlybegin'});
	$lng1=$lng[29];
	$lng2=$lng[578];
	if(length$c[1]>0){$lng1=$c[1]}
	if(length$c[2]>0){$lng2=$c[2]}
	if(length$c[0]>2)
	{	while(length '-'.$notip>length $c[0]){chop $notip}
		if('-'.$notip eq $c[0] or '!'.$notip eq $c[0])
		{print "\n",$t1,"$lng1</title>$begbody<h3>$lng2</h3>$endbody";exit}
	}
}

### проверка имени, пароля, если надо - внесение в базу

if(length$wtbuser{"id_$logs"} and length$logs)
{	if($inip{'passstyle'} and $pass ne $wtbuser{"w_$logs"})
	{	savewrong('WRONG',$login,$pass);
		if($inip{'passstyle'}==2){$member=2;goto PUBLICATION}
		else{$a=$xbody;$nopass=2;$xlogin=$login;$xemail=$email;goto NOPASS;}
	}
	$member=1;

	if(length$email){$wtbuser{"m_$logs"}=$email;}
	$wtbuser{"h_$logs"}=$REMOTE_ADDR;
	$wtbuser{"n_$logs"}=$login;

	if($inip{'usecookie'} eq 'on' and $cookie ne $logs)
	{	print "Set-Cookie: wtboard$fid=$logs; path=/; expires=$inip{'expirescookie'}\n";
	}
}
else
{	if($inip{'private'} eq 'private'){substit($lng[12],$patp{'privatebegin'});print $lng[12];exit}

	$wtbuser{"id_$logs"}=$logs;
	$wtbuser{"w_$logs"}=$pass;
	$wtbuser{"m_$logs"}=$email;
	$wtbuser{"n_$logs"}=$login;
	$wtbuser{"h_$logs"}=$REMOTE_ADDR;
	$wtbuser{"u_${fid}_$logs"}='';
	$wtbuser{"t_${fid}_$logs"}=$curtime;
	savewrong('REGST',$login,$pass,$email);

}

PUBLICATION:

if($inip{'externalcalls'} eq 'on' and !$mpreview){eval $inip{'externalcall2'}}	# внешний вызов 2

if(!length$urltitle){$urltitle=$url}

# мониторинг запрещенных слов
if($inip{'filter'} eq 'on' and $#filter>=0)
{	for$i(0..$#filter)
	{	if(length$filter[$i])
		{	if($xbody=~/$filter[$i]/ or $subj=~/$filter[$i]/)
			{	savewrong('FILTR',$login,$pass,'',$filter[$i]);
				print "\n$t1$lng[450]</title>$begbody$lng[451]$endbody";
				exit;
			}
		}
	}
}

# замена <<text>> на "text"
#for($subj,$login,$email,$xbody){s/\\([\'\"\\])/$1/g}
$xbody=~s/<<(.*?)>>/&#171;$1&#187;/g;
# обработка тегов в body
# 0 - не трогать теги, 1 - преобразовывать в текст, 2 - удалять нафиг,
# 3 - частично разрешить
if($inip{'notag'}==1){$xbody=~s/</&lt;/g;$xbody=~s/>/&gt;/g;}
elsif($inip{'notag'}==2){$xbody=~s/<(.*?)>//g;}
elsif($inip{'notag'}==3)
{	if($inip{'allrestrict'}==1 and $restricted eq 'on'){$xbody=clean_html_tags($xbody,@allowedtags);}
	if($inip{'allrestrict'}==2 and $restricted ne 'on'){$xbody=clean_html_tags($xbody,@allowedtags);}
}

# замена смайликов
if($inip{'smiles'} eq 'on' and $inip{'setsmiles'} ne 'off')
{	$xbody=~s/([:;8])([-*]*)\)+/<font face=\"Wingdings\">J<\/font>/g;
	$xbody=~s/([:;8])([-*]*)\(+/<font face=\"Wingdings\">L<\/font>/g;
	$xbody=~s/([:;8])([-*]*)\|+/<font face=\"Wingdings\">K<\/font>/g;
}

for($subj,$login,$email){s/&/&amp;/g}
for($subj,$login,$email){s/</&lt;/g}
for($subj,$login,$email){s/>/&gt;/g}
# замена контекстных вхождений
if($inip{'contextreplace'})
{	open NAM,"$data/$wtbreplace";
	$i=0;while(<NAM>){chomp;($rs[$i],$rd[$i])=split(';;');($rd[$i],$s)=split(/\\\;\//,$rd[$i]);++$i;}
	close NAM;
	for$i(0..$#rs)
	{	$repside=0;$regexp=0;
		if(index($rs[$i],';')==0){next}
		if(index($rs[$i],'*')==0){$rs[$i]=~s/\*//;$repside=0}
		elsif(index($rs[$i],'#')==0){$rs[$i]=~s/#//;$repside=1}
		elsif(index($rs[$i],'@')==0){$rs[$i]=~s/\@//;$repside=2}
		if(index($rs[$i],'%')==0){$rs[$i]=~s/%//;$regexp=1}
		if(index($rs[$i],'!')==0){$rs[$i]=~s/!//;if($inip{'setreplace'} eq 'off'){next}}
		if(index($rs[$i],'<')==0){$regexp=0;next}
		if(index($rs[$i],'>')==0){$rs[$i]=~s/>//}
		if(index($rs[$i],"\\")==0){$rs[$i]=~s/\\//;}
		if($regexp==1)
		{	if($repside==0 or $repside==1){for($subj){s/$rs[$i]/$rd[$i]/eegi}}
			if($repside==0 or $repside==2){for($xbody){s/$rs[$i]/$rd[$i]/eegi}}
		}
		else
		{	if($repside==0 or $repside==1){for($subj,$urltitle){s/\Q$rs[$i]/$rd[$i]/gi}}
			if($repside==0 or $repside==2){for($xbody){s/\Q$rs[$i]/$rd[$i]/gi;}}
		}
	}
}


$subj=~s/\$/&#36;/g;$stp[1]=$subj;$stp[2]=$login;$stp[3]=$login;
if(length$stp[1]>$inip{'maxshowsubj'}){$stp[1]=substr($stp[1],0,$inip{'maxshowsubj'}-3).'...'}

if(length($email)){$stp[3]="<a href=\"mailto:$email\">$login</a>"}

if($mpreview){goto PREV2}

if($member==2){$subj="(?) $subj";$stp[1]="$inip{'wrnpassbeg'}$stp[1]$inip{'wrnpassend'}"};

# проверка наличия подобного сообщения
if($inip{'verifydbl'})
{	open NAM,"$inip{'dirrealkonf'}/$inip{'indname'}";@a=<NAM>;close NAM;

	if($inip{'verifydbl'} && $inip{'verifydbl'}<3)
	{	for$i(0..$#a)
		{	if($inip{'verifydbl'}==1)
			{	if(index($a[$i],$stp[1])>0 and index($a[$i],$login)>0){$dbl=1;$s=$a[$i]}
			}
			elsif($inip{'verifydbl'}==2)
			{	string($a[$i]);
				if($stp[1] eq $subj and $stp[2] eq $login){$dbl=1;$s=$a[$i]}
			}
		}
	}
	elsif($inip{'verifydbl'}>2 and $inip{'verifydbl'}<=4)
	{	for$j(0..4)
		{	if(-e "$inip{'dirrealkonf'}/$numans\.$exts[$j]"!=1){next;}
			if(!filestp("$inip{'dirrealkonf'}/$numans\.$exts[$j]")){last}
		}

		$stp[39]=~tr/\.\*\,\(\)/ /s;
		@s=split(' ',$stp[39]);
		for(@s)
		{	for$k(0..4)
			{	if(-e "$inip{'dirrealkonf'}/$_\.$exts[$k]"!=1){next;}
				if(!filestp("$inip{'dirrealkonf'}/$_\.$exts[$k]")){last}
			}
			if($stp[1] eq $subj and $stp[2] eq $login){$dbl=1;$stp[0]="$inip{'dirkonf'}/$stp[0]";$s=$hstring;for$i(0..$#tag){if(!length$tag[$i]){next}$s=~s/$tag[$i]/$stp[$i]/g};last}
		}

		if(!$dbl and $inip{'verifydbl'}==3)
		{	for(@a)
			{	if(index($_,'<!--')!=0){next}
				string($_);
				if($stp[1] eq $subj and $stp[2] eq $login and $curtime-$stp[23]<60){$dbl=1;$s=$_;last}
			}
		}

	}
	if($dbl==1){$href=$s;$href=~s/(\d*?)\.$ext/$inip{'dirkonf'}\/$1\.$ext/;substit($lng[28],$patp{'existbegin'});print $lng[28];exit;}
}

$stp[1]=$subj;$stp[1]=~s/\$/&#36;/g;$stp[2]=$login;$stp[3]=$login;
if(length$stp[1]>$inip{'maxshowsubj'}){$s=$inip{'maxshowsubj'}-3;$stp[1]=~s/\A(.{$inip{'maxshowsubj'}}).*\Z/$1\.\.\./}
if(length($email)){$stp[3]="<a href=\"mailto:$email\">$login</a>"}

if($member==2){$subj="(?) $subj";$stp[1]="$inip{'wrnpassbeg'}$stp[1]$inip{'wrnpassend'}"};

# выяснение и запись номера последнего сообщения
open NAM,"$data/$wtblast";$lastmes=<NAM>;chomp $lastmes;@xlast=<NAM>;chomp@xlast;close NAM;
$prevfile=$lastmes;$file=($lastmes+1).".$ext";++$lastmes;$nextfile=$lastmes+1;
$i=-e "$inip{'dirrealkonf'}/$file";while($i==1){++$lastmes;$file=$lastmes.".$ext";$i=-e "$inip{'dirrealkonf'}/$file";}
open NAM,">$data/$wtblast";print NAM "$lastmes\n";for$i(0..@xlast){print NAM "$xlast[$i]\n"};close NAM;


PREV2:

# генерация данных для строки
if(length$date<=0){@et=@t}
else{($date,$stp[11])=split(/\//,$date);extrtime($date);}

$stp[0]=$file;
$stp[4]=$et[2];$stp[5]=$t[2];$stp[6]=$et[1];$stp[7]=$t[1];
$stp[8]=$et[0];$stp[9]=$t[0];$stp[10]=$days[$et[6]-1];$stp[11]=$days[$t[6]-1];
$stp[12]=$et[3];$stp[13]=$t[3];
$stp[14]=$et[4]+1;$stp[15]=$t[4]+1;$stp[16]=$months[$stp[14]-1];
$stp[17]=$months[$stp[15]-1];$stp[18]=$t[5];$stp[19]=$t[5];
$stp[18]=~s/^20//;
$stp[20]='0';$stp[21]=$inip{'selecttag'};

for(@stp[4..9,12..15]){$_=sprintf('%2.2d',$_)}

$s=sprintf('%2.2d',$stp[15]);
$date="$stp[5]:$stp[7]:$stp[9] $stp[13]/$s/$stp[19]";

### обработка сообщения

$xbodyx=$xbody;
$xbody=$cr.$xbody;

$xbody=~s/$cr/\n/g;
$xbody=~s/\n$inip{'quote'}(.*)/\n$inip{'quotebeg'}$inip{'quote'}$1$inip{'quoteend'}/g;
$xbody=~s/\n/$inip{'endparagraph'}&nbsp;$inip{'paragraph'}/g;
$xbodyx=~s/&nbsp;/ /g;
$xbodyx=~s/$cr/\n/g;

for(@hello,@goodbye,@ahello,@agoodbye){s/([\[\]\(\)\-\*\?\+])/\\$1/g;s/((%|\$)toname)|((%|\$)tofname)|((%|\$)fromname)|((%|\$)fromfname)|((%|\$)subject)|((%|\$)number)|((%|\$)shortmtime)|((%|\$)fullmtime)|((%|\$)shortmdate)|((%|\$)fullmdate)|((%|\$)shortwmdate)|((%|\$)fullwmdate)|((%|\$)name)|((%|\$)fname)/\.\*/gi}
for(@hello,@ahello){$xbodyx=~s/\A$_//g;}
for(@goodbye,@agoodbye){$xbodyx=~s/$_\Z//g;}

$xbodyx=~s/\n$inip{'quote'}(.*)//g;
$xbodyx=~s/\n//g;

$lenbody=length$xbodyx;
$stp[22]=$lenbody;


if($inip{'selectnul'}==2)
{	if(length$img>=8){$stp[22]+=5}
	if(length$url>=8){$stp[22]+=length$urltitle}
	if($stp[22]<=0){$stp[1]="<font color=$nulcolor>$stp[1]</font>"}
}
if(!$stp[22] and !$inip{'selectnul'}){print "\n$t1$lng[551]</title>$begbody<h3>$lng[552]</h3>$endbody";exit}


# строка индекса
$string=$hstring;
for$i(0..$#tag)
{	if(!length$tag[$i]){next}
	$string=~s/$tag[$i]/$stp[$i]/g;
}


### генерация сообщения

$command="root=off&fid=$fid&numans=$lastmes";
$prevfile="$prevfile.$ext";
$nextfile="$nextfile.$ext";
$patp{'begmes'}=~s/\$next/$nextfile/g;
$patp{'begmes'}=~s/\$prev/$prevfile/g;
$patp{'begmes'}=~s/$cl/<!>/g;
$patp{'endmes'}=~s/\$next/$nextfile/g;
$patp{'endmes'}=~s/\$prev/$prevfile/g;
$patp{'endmes'}=~s/$cl/<!>/g;
substit($patp{'begmes'});substit($patp{'endmes'});


# preview
if($mpreview){substit($lng[502],$patp{'prevmodetext'});substit($lng[538],$patp{'prevbuttontext'}); $ffile='>-';print "\n<title>$lng[538]</title><center><table width=100% border=0 bgcolor=\"$inip{'errbgcolor'}\"><tr><td><center><h1>$lng[538]</h1><b><i><font color=#aa0000><blink>$lng[502]</blink></font></i></b></center></td></tr></table><p>";}
else{$ffile="+>$inip{'dirrealkonf'}/$file"}


open FILE,$ffile;

print FILE "$patp{'begmes'}\n<!--endhome-->
$lng[14]";
length $email > 0 ? print FILE "<a href=\"mailto:$email\">$login</a>" : print FILE $login;
print FILE "</b> <i>$date</i>";

if($root eq 'on' and $nroot ne 'on')
{	$numans=$lastmes;print FILE ":<p><div align=justify>";}
else
{	print FILE "\n";
	$c=chop $lng[4];
	for$i(0..4)
	{	if(-e "$inip{'dirrealkonf'}/$prev.$exts[$i]"!=1){next}
		open NAM,"$inip{'dirrealkonf'}/$prev.$exts[$i]";@a=<NAM>;close NAM;$is=$i;
	}
	for$i(0..$#a){if(index($a[$i],$lng[14])==0){$s=$i;last}}
	$a[0]=~m/<title>(.*?)<\/title>/i;$c=$1;
	chomp$a[$s];
	$a[$s]=~s/$lng[14]/$lng[18]/;
	$a4="<div align=left>$lng[19]<a href=$prev.$exts[$is]>$c</a>, $a[$s]";
	print FILE "$a4";
	for(@a){if(/\A<p><!\-\-(.*?)\-\-><a name=ans>/){$opts=$1;last}}
	$setnroot='';if($nroot eq 'on'){$setnroot='.'}
	if(!$mpreview){($s1,$s,$s,$s)=split(/\//,$opts);if(length$s1>0){$s2=$s1;$s2=~s/\.//g;@prev=split(';',$s2);$numans="$s1;$setnroot$lastmes";}else{$numans="$numans;$setnroot$lastmes";}}
	undef @a;
}
print FILE "\n";

if(defined$arc){print FILE "$lng[15]<a href=$arc>$lng[16]</a>.<p>\n";}
if(length$img>=8){@c=split(/[\/\\]/,$img);for(@imgexts){if($c[$#c]=~/$_\Z/i){print FILE "<p><center><img src=\"$img\" border=1 alt=\"$c[$#c]\"></center><p>\n"}}}

print FILE "$inip{'paragraph'}\n$xbody$inip{'endparagraph'}\n<p>";

if(length $url>=8){print FILE "<ul><li><a href=\"$url\">$urltitle<\/a></ul><p>\n";$stp[22]+=length$urltitle}
if($inip{'addip'} eq 'on'){print FILE "<div align=right><font size=-1><i>$lng[671] $REMOTE_ADDR</i></font></div><p>"}
print FILE "$inip{'separator'}\n<p><!--$numans/$curtime/$t[6]/$stp[22]--><a name=ans>$lng[17]</a><p>\n</div><div align=left>\n<ul>\n<!--home-->\n<!--$lastmes-->\n<!--end-->\n</ul>\n<!--homeend-->\n";

if($inip{'includeform'} eq 'on' && $ext ne 'htm' && $ext ne 'html'){print FILE "<p><center><!--#include virtual=\"$inip{'dircgi'}/wtboard.cgi?$command&notitle\"--></center><p>"}

if($inip{'externalcalls'} eq 'on' and !$mpreview){eval $inip{'externalcall3'}}	# внешний вызов 3

print FILE $patp{'endmes'};


close FILE;
if($mpreview){print "<p><table width=100% border=0 bgcolor=\"$inip{'errbgcolor'}\"><tr><td>&nbsp;</td></tr></table><p>\n";goto NOPASS}

if(!-e"$inip{'dirrealkonf'}/$file"){print "\n<html><title>Error</title>$begbody Error in creating file <b>$file</b> (possible cause: invalid access rights or can't find the main directory), please fix this problem or contact with <a href=mailto:$inip{'admin'}>administrator</a>. <p><center>[<a href=$inip{'dirkonf'}/>$inip{'thekonf'}</a>] [<a href=$inip{'dirkonf'}/$inip{'faq'}>$lng[194]</a>]</center>$endbody";exit;}



if($inip{'externalcalls'} eq 'on'){eval $inip{'externalcall4'}}	# внешний вызов 4

# обновление файла структуры
open NAM,"$data/$wtbstruct";@c=<NAM>;close NAM;chomp@c;
open NAM,">$data/$wtbstruct";
$i=0;
if(length$arc){print NAM "\n,$lastmes";for$i(0..@c){print NAM "$c[$i]\n";}}
elsif($root eq 'on' and $nroot eq 'on' and $inip{'treestyle'}==1){print NAM "\n*$lastmes";for$i(0..@c){print NAM "$c[$i]\n";}}
elsif($root eq 'on'){print NAM "\n.$lastmes";for$i(0..@c){print NAM "$c[$i]\n";}}
elsif($root eq 'off')
{	chomp @c;
	while($i<=$#c)
	{	@b=split(/([(.,*)])/,$c[$i]);
		for $j(0..$#b)
		{	print NAM $b[$j];
			if($b[$j] eq $prev){print NAM "($lastmes)"}
		}
		print NAM "\n";
		++$i;
	}
}
close NAM;undef @c;undef @b;


### регистрация корневого сообщения на основной странице
open FILE,"$inip{'dirrealkonf'}/$inip{'indname'}";@a=<FILE>;close FILE;
for$i(0..$#a)
{	if($inip{'selectnew'} and index($a[$i],$inip{'selecttag'}))
	{	string($a[$i]);
		$t=$stp[9]+($stp[7]+($stp[5]+($stp[13]+($stp[15]+$stp[19]*12)*31)*24)*60)*60;
		if($t<$curtime-$inip{'selectnew'}*60){$a[$i]=~s/$inip{'selecttag'}//;}
	}
	if($root eq 'on')
	{	if($nroot eq 'on' && $inip{'treestyle'}!=1){next}
		if(index($a[$i-1],"<!--home-->")>=0)
		{	if(length$arc){$strs="<!--$lastmes--><li>$inip{'arclabel'}"}
			elsif($nroot eq 'on'){$strs="<!--$lastmes--><li>$inip{'answerlabel'}"}
			else{$strs="<!--$lastmes--><li>";}

			$strs="$strs$string\n";
			$here=$i-1;
		}

		if($nroot eq 'on')
		{	for$j(0..$#prev)
			{	if(index($a[$i],"<!--$prev[$j]-->")>=0)
				{	if(index($a[$i],"<ul>")>=0){$ul=1}
                                 	if(index($a[$i],$inip{'arclabel'})>=0){$ul2=2}
                                 	elsif(index($a[$i],$inip{'answerlabel'})>=0){$ul2=1}

					string($a[$i]);++$stp[20];$stp[14]=sprintf('%2.2d',++$stp[14]);$stp[15]=sprintf('%2.2d',++$stp[15]);
					if($inip{'treestyle'}==2)
					{	$stp[4]=$et[2];$stp[5]=$t[2];$stp[6]=$et[1];$stp[7]=$t[1];
						$stp[8]=$et[0];$stp[9]=$t[0];$stp[10]=$days[$et[6]-1];$stp[11]=$days[$t[6]-1];
						$stp[12]=$et[3];$stp[13]=$t[3];
						$stp[14]=$et[4]+1;$stp[15]=$t[4]+1;$stp[16]=$months[$stp[14]-1];
						$stp[17]=$months[$stp[15]-1];$stp[18]=$t[5];$stp[19]=$t[5];
						$stp[18]=~s/^20//;
					}
					
					if(length($stp[0])>3 and length($stp[1])>0 and length($stp[2])>0)
					{	$a[$i]=$hstring;
						for$k(0..$#tag)
						{	if(!length$tag[$k]){next}
							$a[$i]=~s/$tag[$k]/$stp[$k]/g;
						}
						if($ul2==1){$a[$i]="$inip{'answerlabel'}$a[$i]";$ul2=0}
						elsif($ul2==2){$a[$i]="$inip{'arclabel'}$a[$i]";$ul2=0}
						$a[$i]="<!--$prev[$j]--><li>$a[$i]\n";
						if($ul==1){$a[$i]="<ul>$a[$i]";$ul=0}
					}
				}
			}
		}
	}
	elsif($root eq 'off')
	{	for$j(0..$#prev)
		{	if(index($a[$i],"<!--$prev[$j]-->")>=0)
			{	if(index($a[$i],"<ul>")>=0){$ul=1}
                               	if(index($a[$i],$inip{'arclabel'})>=0){$ul2=2}
                               	elsif(index($a[$i],$inip{'answerlabel'})>=0){$ul2=1}

				undef@stp;string($a[$i]);++$stp[20];
				if($inip{'treestyle'}==2){$stp[4]=$et[2];$stp[5]=$t[2];$stp[6]=$et[1];$stp[7]=$t[1];$stp[8]=$et[0];$stp[9]=$t[0];$stp[10]=$days[$et[6]-1];$stp[11]=$days[$t[6]-1];$stp[12]=$et[3];$stp[13]=$t[3];$stp[14]=$et[4]+1;$stp[15]=$t[4]+1;$stp[16]=$months[$stp[14]-1];$stp[17]=$months[$stp[15]-1];$stp[18]=$t[5];$stp[19]=$t[5];$stp[18]=~s/^20//;}
				$stp[14]=sprintf('%2.2d',++$stp[14]);$stp[15]=sprintf('%2.2d',++$stp[15]);

				if(length($stp[0])>3 and length($stp[1]) and length($stp[2]))
				{	$a[$i]=$hstring;
					for$k(0..$#tag)
					{	if(!length$tag[$k]){next}
						$a[$i]=~s/$tag[$k]/$stp[$k]/g;
					}
					if($ul2==1){$a[$i]="$inip{'answerlabel'}$a[$i]";$ul2=0}
					elsif($ul2==2){$a[$i]="$inip{'arclabel'}$a[$i]";$ul2=0}
					$a[$i]="<!--$prev[$j]--><li>$a[$i]\n";
					if($ul==1){$a[$i]="<ul>$a[$i]";$ul=0}

					if($inip{'treestyle'}==2 and $inip{'movenewtop'} eq 'on'){@a[3,4..$i]=@a[$i,3..($i-1)];last}
				}

			}
		}

		if(index($a[$i],"<!--$prev-->")>=0 and $inip{'treestyle'}==1)
		{	$strs="<ul><!--$lastmes--><li>";
			$strs="$strs$string\n</ul>\n";
			$here=$i;
		}
	}
}
open FILE,"+>$inip{'dirrealkonf'}/$inip{'indname'}";chomp@a;
substit($patp{'begindex'});print FILE "$patp{'begindex'}\n";
for$i(1..$here){if(length$a[$i]>0){print FILE "$a[$i]\n"}}
print FILE "$strs";
for$i($here+1..($#a-1)){if($a[$i]=~/<!\-\-end\-\->/){last};if(length$a[$i]){print FILE "$a[$i]\n"}}
substit($patp{'endindex'});print FILE "$patp{'endindex'}\n";
close FILE;



$string=~s/$inip{'selecttag'}//g;
### регистрация сообщения в предыдущих сообщениях
if($root eq 'off' or $nroot eq 'on')
{	for$n(0..$#prev)
	{	$dn=$prev[$n];
		for$i(0..4)
		{	if(-e "$inip{'dirrealkonf'}/$dn.$exts[$i]"!=1){next}
			else
			{	@datn=stat("$inip{'dirrealkonf'}/$dn.$exts[$i]");
				open FILE,"$inip{'dirrealkonf'}/$dn.$exts[$i]";@a=<FILE>;close FILE;
				open FILE,"+>$inip{'dirrealkonf'}/$dn.$exts[$i]";


				for$l(0..$#a)
				{	for$j(0..$#prev)
					{	if(index($a[$l],"<!--$prev[$j]-->")>=0 and $dn ne $prev[$j])
						{	string($a[$l]);++$stp[20];$stp[14]=sprintf('%2.2d',++$stp[14]);$stp[15]=sprintf('%2.2d',++$stp[15]);
							if(length($stp[0])>3 and length($stp[1]) and length($stp[2]))
							{	$a[$l]=$hstring;
								for$k(0..$#tag)
								{	if(!length$tag[$k]){next}
									$a[$l]=~s/$tag[$k]/$stp[$k]/g;
								}
								$a[$l]="<ul><!--$prev[$j]--><li>$a[$l]\n";
							}
						}
					}

					print FILE $a[$l];

					if(index($a[$l],"<!--$prev-->")>=0)
					{	print FILE "<ul><!--$lastmes--><li>$string\n</ul>\n";
					}
				}
				close FILE;
			}
		}
	}
}

if($inip{'usecookie'} eq 'on' and length $member<1){print "Set-Cookie: wtboard$fid=$logs; path=/; expires=$inip{'expirescookie'}\n";}

print "\n<html>";


# перенаправления
if($inip{'showmiddlescreen'} eq 'off' and !length$inip{'redirect'}){$inip{'redirect'}='r'}
if($member==1)
{	if($inip{'redirect'} eq 'r'){print "<head><meta http-equiv=\"Refresh\" content=\"0; URL=$inip{'dirkonf'}/$file\"></head>"}
	elsif($inip{'redirect'} eq 'R'){print "<head><meta http-equiv=\"Refresh\" content=\"0; URL=$inip{'dirkonf'}/\"></head>"}
	if($inip{'showmiddlescreen'} eq 'off'){print "<center>[<a href=$inip{'dirkonf'}/$file>$lng[27]</a>] [<a href=$inip{'dirkonf'}/>$inip{'thekonf'}</a>]</center></html>";goto ENDAPPLY}
}

$password=$pass;$name=$login;
substit($lng[20],$patp{'addedbegin'});print $lng[20];

if($member<1 and $inip{'passstyle'})
{	substit($lng[21],$patp{'regtext'});
	print " <h3>$lng[21]</h3> <center>$inip{'separator'}</center>";
}

substit($lng[26],$patp{'warntext'});

print "<p>$lng[26]<p><center>[<a href=$inip{'dirkonf'}/$file>$lng[27]</a>] [<a href=$inip{'dirkonf'}/>$inip{'thekonf'}</a>]<p>$inip{'separator'}</center> <p><div align=\"left\">$lng[14]";
$a4=~s/<a href=/<a href=$inip{'dirkonf'}\//;
length $email>0 ? print "<a href=\"mailto:$email\">$login</a>" : print $login;
print "</b> <i>$date</i>\n<br>$a4<p>";

if(length $img>=8){@c=split(/[\/\\]/,$img);print FILE "<center><img src=\"$img\" border=1 alt=\"$c[$#c]\"></center><p>\n";}

print "<div align=\"justify\">$inip{'paragraph'}\n$xbody\n<p>";

if(length $url>=8){print "<ul><li><a href=\"$url\">$urltitle<\/a></ul><p>\n";}
if($inip{'addip'} eq 'on'){print "<div align=right><font size=-1><i>$lng[671] $REMOTE_ADDR</i></font></div><p>"}

print "<center>$inip{'separator'}<p>[<a href=$inip{'dirkonf'}/$file>$lng[27]</a>] [<a href=$inip{'dirkonf'}/>$inip{'thekonf'}</a>]<p>\n";

if($inip{'externalcalls'} eq 'on'){eval $inip{'externalcall5'}}	# внешний вызов 5

print $endbody;


# восстановление greetings из cookie
if($inip{'usecookie'} eq 'on')
{	for$i(0..@cookie)
	{	if($cookie[$i]=~/\Agreetings/)
		{	$cookie[$i]=~/greetings(?:\d*)=(.*?)\/\/(.*?)(?:\/\/(.*?))?(?:\/\/(.*?))?\Z/;
			if(!length$hello and (length$1+length"gh_$names")<1000){$wtbuser{"gh_$names"}=$1}
			if(!length$goodbye and (length$2+length"gg_$names")<1000){$wtbuser{"gg_$names"}=$2}
			if(!length$ahello and (length$3+length"gah_$names")<1000){$wtbuser{"gah_$names"}=$3}
			if(!length$agoodbye and (length$4+length"gag_$names")<1000){$wtbuser{"gag_$names"}=$4}
		}
	}
}


ENDAPPLY:

## автоматическая архивация

if(!$inip{'method'}){exit};

$inip{'selftimeout'}*=86400;
$inip{'arctimeout'}*=86400;
$inip{'timelimit'}*=86400;

for$i(0..@xlast)
{	($s1,$s2)=split('=',$xlast[$i]);
	if($s1 eq 'arc'){$arc=$s2}
}

if(length $arc<=0)
{	open NAM,"$data/$wtblast";@xlast=<NAM>;chomp@xlast;close NAM;
	$xlast[1]="arc=$curtime";
	open NAM,">$data/$wtblast";for$i(0..@xlast){if(length($xlast[$i])>0){print NAM "$xlast[$i]\n"}};close NAM;
	exit;
}

if($arc<$curtime-$inip{'selftimeout'})
{
	open NAM,"$data/$wtblast";@xlast=<NAM>;chomp@xlast;close NAM;
	$xlast[1]="arc=$curtime";
	open NAM,">$data/$wtblast";for$i(0..@xlast){print NAM "$xlast[$i]\n"};close NAM;

	open NAM,"$inip{'dirrealkonf'}/$inip{'indname'}";@ini=<NAM>;close NAM;

	$i=$#ini-1;while($i>2)
	{	if(index($ini[$i],"<!--")==0){$s2=$ini[$i];$i=1}
		--$i;
	}
	string($s2);$s2=$stp[23];string($ini[3]);$s1=$stp[23];$s1=$s1-$s2;
	$s2=0;for$i(3..@ini)
	{	if(index($ini[$i],'<!--')>=0){++$s2}
	}

	if($s1<$inip{'timelimit'} and $s2<$inip{'meslimit'}){exit}

	for$i(3..@ini)
	{	if(index($ini[$i],'<!--')<0){next}
		if(index($ini[$i],'<!--')>0){next}
		if(index($ini[$i],'</ul>')==0){next}
		string($ini[$i]);

		if($stp[23]<$curtime-$inip{'arctimeout'})
		{	$ini[$i]=~m/<!--(.*?)-->/;$mesarhiv=$1;
			last;
		}
	}

	if(length$mesarhiv){$login='AUTOARC';&archivate;}

}

if($inip{'externalcalls'} eq 'on'){eval $inip{'externalcall6'}}	# внешний вызов 6

exit;


# ФОРМА НАСТРОЙКИ ПАРАМЕТРОВ ПОЛЬЗОВАТЕЛЯ
USER:

if($inip{'individual'} ne 'on'){print "\n<html><title>$lng[34]</title><h2>$lng[34]</h3></html>";exit;}

$name=$xlogin;
substit($lng[35],$patp{'begsettings'});
substit($lng[654],$patp{'endsettings'});

print "\n$lng[35]\n<form action=$inip{'dircgi'}/wtboard.cgi method=post>
<table width=100% border=0>
<tr><td colspan=2>$i1=hidden name=fid value=$fid>$i1=hidden name=update>$lng[1]</td><td colspan=4>$xlogin</td></tr>
<tr><td colspan=2>$lng[2]</td><td colspan=4><input type=password name=pass size=30></td></tr>\n";

%inis=%inip;

optfield('xemail','E-mail:');

if($inip{'allowgreetings'} eq 'on')
{	if(length$wtbuser{"gh_$names"}){$inis{'hellox'}=$wtbuser{"gh_$names"}}
	if(length$wtbuser{"gg_$names"}){$inis{'goodbyex'}=$wtbuser{"gg_$names"}}
	if(length$wtbuser{"gah_$names"}){$inis{'ahellox'}=$wtbuser{"gah_$names"}}
	if(length$wtbuser{"gag_$names"}){$inis{'agoodbyex'}=$wtbuser{"gag_$names"}}
	for($inis{'hellox'},$inis{'ahellox'},$inis{'goodbyex'},$inis{'agoodbyex'})
	{	chomp;
		s/&/&amp;/g;s/</&lt;/g;s/>/&gt;/g;
	}
	optfield('hellox',"<a href=$inip{'dircgi'}/wtbservice.cgi?help=2&fid=$fid>$lng[36]</a>");
	optfield('goodbyex',"<a href=$inip{'dircgi'}/wtbservice.cgi?help=2&fid=$fid>$lng[37]</a>");
	optfield('ahellox',"<a href=$inip{'dircgi'}/wtbservice.cgi?help=2&fid=$fid>$lng[576]</a>");
	optfield('agoodbyex',"<a href=$inip{'dircgi'}/wtbservice.cgi?help=2&fid=$fid>$lng[577]</a>");
	print "\n<tr><td colspan=2 align=left><a href=$inip{'dircgi'}/wtbservice.cgi?help=14&fid=$fid>$lng[701]</a></td><td colspan=4><input type=checkbox name=greetingsall unchecked></td></tr>";
}

if($inip{'quoting'} eq 'on'){optonoff('uquoting',"<a href=$inip{'dircgi'}/wtbservice.cgi?help=3&fid=$fid>$lng[38]</a>")}
if($inip{'smiles'} eq 'on'){optonoff('setsmiles',"<a href=$inip{'dircgi'}/wtbservice.cgi?help=10&fid=$fid>$lng[473]</a>")}
if($inip{'contextreplace'}==1){optonoff('setreplace',"<a href=$inip{'dircgi'}/wtbservice.cgi?help=7&fid=$fid>$lng[595]</a>")}
if($inip{'usecookie'} eq 'on'){optonoff('ucookie',"<a href=$inip{'dircgi'}/wtbservice.cgi?help=4&fid=$fid>$lng[41]</a>")}
if($inip{'passstyle'}){optonoff('setpass',"<a href=$inip{'dircgi'}/wtbservice.cgi?help=5&fid=$fid>$lng[292]</a>")}
if($inip{'seturl'} eq 'on'){optonoff('showurl',"<a href=$inip{'dircgi'}/wtbservice.cgi?help=9&fid=$fid>$lng[400]</a>")}
if($inip{'setimg'} eq 'on'){optonoff('showimg',"<a href=$inip{'dircgi'}/wtbservice.cgi?help=9&fid=$fid>$lng[562]</a>")}
if($inip{'preview'} eq 'on'){optonoff('upreview',"<a href=$inip{'dircgi'}/wtbservice.cgi?help=11&fid=$fid>$lng[540]</a>")}
if($inip{'resetbutton'} eq 'on'){optonoff('uresetbutton',"<a href=$inip{'dircgi'}/wtbservice.cgi?help=12&fid=$fid>$lng[541]</a>")}

if($inip{'advisenew'} eq 'on')
{	if($inip{'unewmes'} ne 'off')
	{	if($inip{'unewwinmes'} ne 'off'){$s1='';$s2=' selected';$s3='';}
	 	else{$s1='';$s2='';$s3=' selected';}
	}
	else
	{	$s1=' selected';$s2='';$s3='';
	}
	print "<tr><td colspan=2><a href=$inip{'dircgi'}/wtbservice.cgi?help=6&fid=$fid>$lng[42]</a></td><td colspan=4><select name=unewwinmes><option value=1$s1>$lng[426]<option value=2$s2>$lng[44]<option value=3$s3>$lng[449]</select></td></tr>\n";
}

if($inip{'adviseans'} eq 'on')
{	if($inip{'unewans'} ne 'off')
	{	if($inip{'unewwinans'} ne 'off'){$s1='';$s2=' selected';$s3='';}
	 	else{$s1='';$s2='';$s3=' selected';}
	}
	else
	{	$s1=' selected';$s2='';$s3='';
	}
	print "<tr><td colspan=2><a href=$inip{'dircgi'}/wtbservice.cgi?help=6&fid=$fid>$lng[43]</a></td><td colspan=4><select name=unewwinans><option value=1$s1>$lng[426]<option value=2$s2>$lng[44]<option value=3$s3>$lng[449]</select></td></tr>\n";
}

if($inip{'showsuccess'}==0){optonoff('showmiddlescreen',"<a href=$inip{'dircgi'}/wtbservice.cgi?help=13&fid=$fid>$lng[561]</a>")}
optselect('redirect',"<a href=$inip{'dircgi'}/wtbservice.cgi?help=8&fid=$fid>$lng[296]</a>",'',3,'','r','R',@lng[297..299]);


if($inip{'externalcalls'} eq 'on'){eval $inip{'externalcall7'}}	# внешний вызов 7


print "</table><center><p><input type=submit value=\"$lng[39]\"></center>
</form>\n$lng[654]";

exit;

# сохранение индивидуальной настройки
UPDATE:

if($inip{'individual'} ne 'on'){print "\n<html><title>$lng[34]</title><h2>$lng[34]</h3></html>";exit;}

for$i(0..$#cks)
{	($a1,$a2)=split('=',$cks[$i],2);
	if($a1 eq 'unewwinans'){$unewwinans=$a2}
	if($a1 eq 'unewans'){$unewans=$a2}
	if($a1 eq 'unewwinmes'){$unewwinmes=$a2}
	if($a1 eq 'unewmes'){$unewmes=$a2}
	if($a1 eq 'uquoting'){$uquoting=$a2}
	if($a1 eq 'ucookie'){$ucookie=$a2}
	if($a1 eq 'setpass'){$setpass=$a2}
	if($a1 eq 'showurl'){$showurl=$a2}
	if($a1 eq 'showimg'){$showimg=$a2}
	if($a1 eq 'redirect'){$redirect=$a2}
	if($a1 eq 'setsmiles'){$setsmiles=$a2}
	if($a1 eq 'setreplace'){$setreplace=$a2}
	if($a1 eq 'upreview'){$upreview=$a2}
	if($a1 eq 'uresetbutton'){$uresetbutton=$a2}
	if($a1 eq 'showmiddlescreen'){$showmiddlescreen=$a2}
	if($a1 eq 'hellox'){$hello=$a2}
	if($a1 eq 'goodbyex'){$goodbye=$a2}
	if($a1 eq 'ahellox'){$ahello=$a2}
	if($a1 eq 'agoodbyex'){$agoodbye=$a2}
	if($a1 eq 'xemail'){$email=$a2}
	if($a1 eq 'greetingsall'){$greetingsall=$a2}
}


if($unewwinans==1){$unewans='off';}
elsif($unewwinans==2){$unewans='on';$unewwinans='on'}
else{$unewans='on';$unewwinans='off'}

if($unewwinmes==1){$unewmes='off';}
elsif($unewwinmes==2){$unewmes='on';$unewwinmes='on'}
else{$unewmes='on';$unewwinmes='off'}


$login=$xlogin;
$pars=~s/Z(.*)//;$plugpars=$1;
$pars=~s/[ckmMaAphHsSrRbvw]//g;
if($uquoting eq 'off'){$pars='c'.$pars}
if($ucookie eq 'off'){$pars='k'.$pars}
if($unewmes eq 'off'){$pars='m'.$pars}
if($unewwinmes eq 'off'){$pars='M'.$pars}
if($unewans eq 'off'){$pars='a'.$pars}
if($unewwinans eq 'off'){$pars='A'.$pars}
if($setpass eq 'on'){$pars='p'.$pars}
if($showurl eq 'off'){$pars='h'.$pars}
if($showimg eq 'off'){$pars='H'.$pars}
if($setsmiles eq 'off'){$pars='s'.$pars}
if($setreplace eq 'off'){$pars='S'.$pars}
if($upreview eq 'off'){$pars='v'.$pars}
if($uresetbutton eq 'on'){$pars='b'.$pars}
if($showmiddlescreen eq 'off'){$pars='w'.$pars}
$pars=$redirect.$pars.'Z'.$plugpars;

# коррекция имени
$logs=$login;
correct($logs);

if($inip{'externalcalls'} eq 'on'){eval $inip{'externalcall8'}}	# внешний вызов 8


if($wtbuser{"w_$logs"} ne $pass)
{	savewrong('WRNCP',$login,$pass);
	print "\n",$t1,"$lng[33]</title>$begbody$lng[11]$endbody";
	exit;
}
else
{	$wtbuser{"m_$logs"}=$email;
	$wtbuser{"h_$logs"}=$REMOTE_ADDR;
	$wtbuser{"n_$logs"}=$login;
	$wtbuser{"u_${fid}_$logs"}=$pars;
	$wtbuser{"t_${fid}_$logs"}=$curtime;
	if(length$hellox<(1000-length"gh_$logs")){$wtbuser{"gh_$logs"}=$hellox}
	if(length$goodbyex<(1000-length"gg_$logs")){$wtbuser{"gg_$logs"}=$goodbyex}
	if(length$ahellox<(1000-length"gah_$logs")){$wtbuser{"gah_$logs"}=$ahellox}
	if(length$agoodbyex<(1000-length"gag_$logs")){$wtbuser{"gag_$logs"}=$agoodbyex}
}


if($inip{'usecookie'} eq 'on' and $greetingsall eq 'on')
{	for($hellox,$goodbyex,$ahellox,$agoodbyex){s/"/&quot;/g;s/;/:,/g;}
	print "Set-Cookie: greetings=$hello//$goodbye//$ahello//$agoodbye; path=/; expires=$expirescookie GMT\n";
}

substit($lng[658],$patp{'savedsettings'});print $lng[658];

if($inip{'externalcalls'} eq 'on'){eval $inip{'externalcall9'}}	# внешний вызов 9

print $endbody;

exit;

