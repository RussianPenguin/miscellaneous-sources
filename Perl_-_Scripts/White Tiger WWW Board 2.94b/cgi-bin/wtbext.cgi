# =================================================

# White Tiger WWW Board ver.2.936b
# система wwwboard. Разработка, реализация
# (C) 1998-2000, White Tiger (2:5049/91.38; 
# email:wtiger@mail.ru; http://wtiger.ncport.ru)
# wtbext.cgi - модуль внутренних подпрограмм
# wtbext.cgi - internal subroutines module

# =================================================
sub params{
# =================================================
# Здесь произвести необходимую коррекцию пути к каталогу данных
# и названия общего файла данных. Путь к каталогу должен быть либо
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



#############################################################
###подпрограмма задания переменных и считывания параметров###
#############################################################

if($cksdefined){return}

if($ENV{'WTBP_QUERY_STRING'}){$ENV{'QUERY_STRING'}=$ENV{'WTBP_QUERY_STRING'};}
else
{	if(!$contenttype){print "Content-type: TEXT/HTML\n";if($_[0]!=1){print "\n";}}
}
if(!-e"$data/$wtbini"){print "\nError: not found $data/$wtbini";exit}

$contenttype=1;
use SDBM_File;	# задание типа базы данных

# сокращение часто используемых фрагментов
$i1='<input type';
$cr=chr(0x0D).chr(0x0A);
$cl=chr(0x0A);
$c=chr(0x0A);
$crd=chr(0x0D);
$cs2='<td colspan=2 align=left>';
$cs3='<td colspan=3 align=center>';
$cs4="</td><td colspan=4>";
$cs6='<td colspan=6><div align=left>';
$dr='</td></tr>';
$rd='<tr><td>';
$t1='<html><title>';
$version='2.936b';
$internalversion=2936;
$newstype=3;	# 1 - news only, 2 - advise only, 3 - both
$formdata=1;	# 1 - x-www-url-encoded, 2 - multipart/form-data
$cs=0;

if($_[0]==4){return;}

# получение post-данных
$CONTENT_LENGTH=$ENV{'CONTENT_LENGTH'};
#use Env qw(CONTENT_LENGTH);
if($CONTENT_LENGTH){read STDIN,$cs,$CONTENT_LENGTH}
else{$cs=$ENV{'QUERY_STRING'}}

if($ENV{'CONTENT_TYPE'} eq 'application/x-www-form-urlencoded'){$formdata=1}
if($ENV{'CONTENT_TYPE'}=~/multipart\/form\-data; boundary=(.*?)\Z/i){$formdata=2;$formdataseparator=$1}

if($formdata==1){$cs=~s/\+/ /g}

#use Env qw(REMOTE_ADDR);
$REMOTE_ADDR=$ENV{'REMOTE_ADDR'};$ipaddr=$REMOTE_ADDR;chop$ipaddr;
$cookie=$ENV{'HTTP_COOKIE'};
$pars='';
@exts=('htm','html','shtml','stm','asp');
$hr='<hr size=1 width=80% align=center>';

@tag=(	'\$href',	'\$subj',	'\$name',	'\$nemail',
#	0		1		2		3
	'\$fhour',	'\$shour',	'\$fmin',	'\$smin',
#	4		5		6		7
	'\$fsec',	'\$ssec',	'\$fweek',	'\$sweek',
#	8		9		10		11
	'\$fday',	'\$sday',	'\$fmonth',	'\$smonth',
#	12		13		14		15
	'\$fwmonth',	'\$swmonth',	'\$year',	'\$fullyear',
#	16		17		18		19
	'\$answers',	'\$new',	'\$length',	'\$fxdata',
#	20		21		22		23
	'\$fxbody',	'\$fxurl',	'\$fxturl',	'\$fximg'
#	24		25		26		27
);
$tag[38]='\$number';
$tag[41]='\$fxfile';



# ini-данные конференции
%inip=(	addip=>'off',		adviseans=>'on',
	advisenew=>'on',	allowroot=>'on',
	allowgreetings=>'on',
	allrestrict=>0,		answerlabel=>'* ',
	archive=>'archive.htm',	arclabel=>'** ',
	arctimeout=>3,		codepage=>'cp-1251',
	contextreplace=>1,	dirarc=>'archive',
	cprt=>'&copy; 1998-2000, <a href=http://wtiger.ncport.ru>White Tiger</a>',
	begbody=>'<body bgcolor="$errbgcolor" text="$errtcolor" link="$errlcolor" vlink="$errvlcolor" alink="$erralcolor" background="$errimg">',
	dircookie=>1,		endbody=>"</body></html>",
	endparagraph=>'</dd>',	expirescookie=>'Wednesday, 08-Dec-19 23:59:59',
	ext=>'shtml',		externalcalls=>'off',
	faq=>'faq.htm',		filter=>'off',
	separator=>'<hr size=1 width=80% align=center>',
	ignorstat=>'off',	imgexts=>'jpg/jpeg/gif/png',
	includeform=>'on',	indexarc=>'index',
	individual=>'on',	indname=>'index.shtml',
	intervaltype=>2,	ipuserstat=>'off',
	maxshowsubj=>500,	maxsubj=>500,
	maxurl=>200,		meslimit=>1000,
	mestimeout=>2400,	method=>0,
	movenewtop=>'on',	notag=>0,
	nulcolor=>'#0000ff',	overdefine=>'off',
	paragraph=>'<dd>',	passstyle=>1,
	preview=>'on',		private=>'noprivate',
	quote=>'>',		quotebeg=>'<i>',
	quoteend=>'</i>',	quotesize=>0,
	quoting=>'on',		replacedeleted=>'on',
	reply=>'Re',
	resetbutton=>'off',	selectnew=>360,
	selectnul=>2,		selecttag=>"<font color=#ff0000><b>New</b></font>",
	selftimeout=>1,		service=>'service.shtml',
	sethtaccess=>'on',	setimg=>'on',
	setnewsarc=>'on',	setnroot=>15,
	seturl=>'on',		showmiddlescreen=>'on',
	showsuccess=>0,		smiles=>'on',
	statdays=>15,		substip=>'on',
	string=>'<a href=$href>$subj</a> &#151; <b>$name</b> <i>$fhour:$fmin:$fsec $fday/$fmonth/$year</i> ($answers) $new',
	treestyle=>1,
	timelimit=>30,		timeshift=>0,
	usecookie=>'on',	userstat=>'on',
	verifydbl=>1,		wrnpassbeg=>'<font size=-1 color=#888888>?</font> ',
	wrnpassend=>''
);


# идентификатор форума
$fid=0;
# получение переменных из потока данных

if($formdata==1){@cks=split('&',$cs);for(@cks){replacx($_)}}
elsif($formdata==2)
{	@cks=split("$cr--$formdataseparator",$cs);undef$cs;
	for(@cks)
	{	($s,$s1,$s,$s2)=split($cr,$_,4);
		if(!($s1=~s/Content-Disposition: form\-data; name=\"(.*?)\"(?:; filename=\"(.*?)\")?\Z//i)){undef$_;next}
		if(length$2){$filename=$2}
		$s1=$1;$_="$s1=$s2";
		$s2=~s/([.]|[^ a-zA-Z0-9])/'%'.unpack("H2",$1)/ge;$s2=~s/ /+/g;$cs.="$s1=$s2&";
	}
}
$cksdefined=1;

for(@cks)
{	if(!length){next}
	($a1,$a2)=split('=',$_,2);
	$a1=~s/[\$\@\&\'\s\"\;]//g;
#	$a2=~s/([\\\'\"])/\\$1/g;
#	$a2=~s/\\/\\\\/g;$a2=~s/\'/\\\'/g;
	$inip{$a1}=$a2;
	if($a1 eq 'fid'){$fid=$a2}
}

for(@cks){@a=(@a,split('=',$_,2))}


open DAT,"$data/$wtbini";@lng=<DAT>;close DAT;chomp @lng;
for$i(0..$#lng)
{	@b=split(';',$lng[$i]);
	if($fid==$b[0])
	{	$wtbaccess=$b[1];
		$wtbadmin=$b[2];
		$wtblang=$b[3];
		$wtblast=$b[4];
		$wtbnames=$b[5];
		$wtbnews=$b[6];
		$wtboard=$b[7];
		$wtbreplace=$b[8];
		$wtbstruct=$b[9];
		$wtwrong=$b[10];
		$s=1;last;
	}
}

if(!$s){print "\n\nError: not found forum with <b>$fid</b> identificator.";exit}

undef @lng;undef @b;

#if(!-e"$data/$wtbaccess"){print "\n\nError: not found $data/$wtbaccess";exit}
if(!-e"$data/$wtbadmin"){print "\n\nError: not found $data/$wtbadmin";exit}
if(!-e"$data/$wtblang"){print "\n\nError: not found $data/$wtblang";exit}
if(!-e"$data/$wtblast"){print "\n\nError: not found $data/$wtblast";exit}
if(!-e"$data/$wtboard"){print "\n\nError: not found $data/$wtboard";exit}
if(!-e"$data/$wtbreplace"){print "\n\nError: not found $data/$wtbreplace";exit}
if(!-e"$data/$wtbstruct"){print "\n\n<font color=#ff0000 size=+1><b>Error: not found $data/$wtbstruct. Run the &#171;Restore structure&#187; service from administration.</b></font><p>";}

if(!(dbmopen(%wtbuser,"$data/$wtbnames",0644))){print "\n\nError: cannot open user base $data/$wtbnames.*";exit}

open DAT,"$data/$wtboard";@ini=<DAT>;close DAT;chomp@ini;

$s=0;$j=0;for(@ini)
{	if($s==1 && !length){$s=0;next}
	if($s==1 || /^;/){next}
	if($_[0]!=2 and /\[board strings\]/i){$s=1;next}
	if(/^\[/ || !length){next}
	($a,$b)=split('=',$_,2);if(defined$b){$inip{$a}=$b}
}

$hstring=$inip{'string'};
$hstring=~s/&lt;/</g;$hstring=~s/&gt;/>/g;$hstring=~s/&quot;/\"/g;$hstring=~s/&amp;/&/g;
$fstring=$hstring;
$fstring=~s/([\/\\\(\)\.\?\*\+\^\|\[\]])/\\$1/g;
$fstring=~s/\$/\$\#\#/g;$sval=1;
for$i(0..$#tag)
{	if(!length$tag[$i]){next}
	$q=$fstring=~s/\$\#\#/\$/;if($q!=1){last}
	for$j(0..$#tag)
	{	if(!length$tag[$j]){next}
		$q=$fstring=~s/$tag[$j]/\(\.\*\?\)/;
		if($q==1){$astring=$astring."\$stp[$j]=\$$sval;";++$sval}
	}
}
$fstring="\$_[0]=~m/$fstring\\Z/;$astring";

if($_[0]!=2)
{	$s=0;for(@ini)
	{	if(!length){$s=0;next}
		if(/^;/){next}
		if(/^\[board strings\]/i){$s=1;next}
		if(/^\[/){$s=0;next}
		if(!$s){next}

		($a,$b)=split('=',$_,2);
		$patp{$a}=$b;
	}
}

delete $inip{'help'};
@patn=keys%patp;

# перезапись переменных при overdefine=on
for(@cks)
{	($s1,$s2)=split('=',$_,2);
	$s1=~s/[\$\@\&\'\s\"\;]//g;
	$s2=~s/([\\\'])/\\$1/g;
#	$s2=~s/\\/\\\\/g;$s2=~s/\'/\\\'/g;
	if($inip{'overdefine'} eq 'on' or $_[0]==2){$inip{$s1}=$s2}
}

# интерполяция
if($_[0]!=2){substit($inip{'begbody'});substit($inip{'endbody'})}

&initiate;


if(!length$fid){$fid=0}
##############


@days=split(/\//,$inip{'days'});
@months=split(/\//,$inip{'months'});
@allowedtags=split(/\//,$inip{'allowedtags'});
@filter=split(/\//,$inip{'filterwords'});
@imgexts=split(/\//,$inip{'imgexts'});

@t=localtime(time+$inip{'timeshift'}*60);$t[5]=$t[5]+1900;
$curtime=$t[0]+($t[1]+($t[2]+($t[3]+($t[4]+$t[5]*12)*31)*24)*60)*60;

open DAT,"$data/$wtblang";@lng=<DAT>;close DAT;chomp @lng;
for$i(0..@lng)
{	$lng[$i]=~s/\"/\\\"/g;
	$a="\$lng[\$i]=\"$lng[$i]\"";eval $a;
	$lng[$i]=~s/<!>/\n/g;
}

## индивидуализация участника

@cookie=split('; ',$cookie);
for$i(0..@cookie)
{	if($cookie[$i]=~/wtboard$fid/){$cookie=$cookie[$i];last}
}

$realn='';$mails='';
if($inip{'usecookie'} eq 'on' and index($cookie,'wtboard')==0)
{	$cookie=~/wtboard$fid=(.*?)\Z/i;$cookie=$1;
	if(length$wtbuser{"id_$cookie"}){$names=$cookie;$realn=$wtbuser{"n_$cookie"};$mails=$wtbuser{"m_$cookie"};$pars=$wtbuser{"u_${fid}_$cookie"};$pwd=$wtbuser{"w_$cookie"};$utimes=$wtbuser{"t_${fid}_$cookie"};$su=1;}
}
if(!$su and $inip{'substip'} ne 'off')
{	while(($s1,$s2)=each%wtbuser){if($s2 eq "$REMOTE_ADDR"){($s,$s1)=split('_',$s1,2);$names=$s1;$realn=$wtbuser{"n_$s1"};$mails=$wtbuser{"m_$s1"};$pars=$wtbuser{"u_${fid}_$s1"};$pwd=$wtbuser{"w_$s1"};$utimes=$wtbuser{"t_${fid}_$s1"};$su=1;last;}}
}

# параметры индивидуальной настройки
# цитирование
$inip{'uquoting'}='on';
if($pars=~/c.*?Z/){$uquoting='off'}
if($inip{'individual'} ne 'on'){$inip{'uquoting'}='on'}
# использование cookie
$inip{'ucookie'}='on';
if($pars=~/k.*?Z/){$inip{'ucookie'}='off'}
if($inip{'individual'} ne 'on'){$inip{'ucookie'}='on'}
# вывод информации о новых сообщениях
$inip{'unewmes'}='on';
if($pars=~/m.*?Z/){$inip{'unewmes'}='off'}
if($inip{'individual'} ne 'on'){$inip{'unewmes'}='on'}
if($inip{'advisenew'} ne 'on'){$inip{'unewmes'}='off'}
# новое окно для этого
$inip{'unewwinmes'}='on';
if($pars=~/M.*?Z/){$inip{'unewwinmes'}='off'}
if($inip{'individual'} ne 'on'){$inip{'unewwinmes'}='on'}
# вывод информации об ответах на сообщения этого участника
$inip{'unewans'}='on';
if($pars=~/a.*?Z/){$inip{'unewans'}='off'}
if($inip{'individual'} ne 'on'){$inip{'unewans'}='on'}
if($inip{'adviseans'} ne 'on'){$inip{'unewans'}='off'}
# новое окно для этого
$inip{'unewwinans'}='on';
if($pars=~/A.*?Z/){$inip{'unewwinans'}='off'}
if($inip{'individual'} ne 'on'){$inip{'unewwinans'}='on'}
# подстановка пароля
$inip{'setpass'}='off';
if($pars=~/p.*?Z/){$inip{'setpass'}='on'}
if($inip{'individual'} ne 'on'){$inip{'setpass'}='off'}
# перенаправление на сообщение
if($pars=~/r.*?Z/){$inip{'redirect'}='r'}
# перенаправление на основную страницу
if($pars=~/R.*?Z/){$inip{'redirect'}='R'}
if($inip{'individual'} ne 'on'){undef $inip{'redirect'}}
# показ промежуточного экрана приема сообщения
$inip{'showmiddlescreen'}='on';
if($pars=~/w.*?Z/){$inip{'showmiddlescreen'}='off'}
if($inip{'individual'} ne 'on'){$inip{'showmiddlescreen'}='on'}
if($inip{'showsuccess'}==1){$inip{'showmiddlescreen'}='off';if(!$inip{'redirect'}){$inip{'redirect'}='r'}}
elsif($inip{'showsuccess'}==2){$inip{'showmiddlescreen'}='off';if(!$inip{'redirect'}){$inip{'redirect'}='R'}}
# отказ от показа полей для ссылок
$inip{'showurl'}='on';
if($pars=~/h.*?Z/){$inip{'showurl'}='off'}
if($inip{'individual'} ne 'on'){$inip{'showurl'}='on'}
# отказ от показа поля для ссылки на изображение
$inip{'showimg'}='on';
if($pars=~/H.*?Z/){$inip{'showimg'}='off'}
if($inip{'individual'} ne 'on'){$inip{'showimg'}='on'}
# преобразование смайликов
$inip{'setsmiles'}='on';
if($pars=~/s.*?Z/){$inip{'setsmiles'}='off'}
if($inip{'individual'} ne 'on'){$inip{'setsmiles'}='on'}
# настройка контекстной замены
$inip{'setreplace'}='on';
if($pars=~/S.*?Z/){$inip{'setreplace'}='off'}
if($inip{'individual'} ne 'on'){$inip{'setreplace'}='on'}
if($inip{'contextreplace'}!=1){$inip{'setreplace'}='on'}
# наличие кнопки "просмотр"
$inip{'upreview'}='on';
if($pars=~/v.*?Z/){$inip{'upreview'}='off'}
if($inip{'individual'} ne 'on'){$inip{'upreview'}='on'}
# наличие кнопки "сброс"
$inip{'uresetbutton'}='off';
if($pars=~/b.*?Z/){$inip{'uresetbutton'}='on'}
if($inip{'individual'} ne 'on'){$inip{'uresetbutton'}='off'}

# статус пользователя, устанавливаемый администратором
$restricted='off';
if($pars=~/t.*?Z/){$restricted='on'}


}

##################################
###подпрограмма коррекции имени###
##################################
sub correct
{$_[0]=~s/&#(\d*?);/chr($1)/eg;$_[0]=lc $_[0];
$_[0]=~s/&(.*?);//g;
$_[0]=~s/[ \;\.\,\_\-\|]//g;
$_[0]=~tr/АВЕЗКМНОРСТУХаеиопрсух01ч/ABE3KMHOPCTYXaeuonpcyxOlr/;
$_[0]=lc $_[0];
}

############################################
###подпрограмма преобразования cgi-потока###
############################################
sub replacx
{$_[0]=~s/%([a-fA-F0-9][a-fA-F0-9])/pack("C",hex($1))/eg;}

######################################
###подпрограмма уменьшения регистра###
######################################
sub smaller
{$_[0]=~tr/АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ/абвгдежзийклмнопрстуфхцчшщъыьэюя/;
$_[0]=lc $_[0]}

##################################
###подпрограмма подсчета секунд###
##################################
sub counts
{
$_[0]=~/\A((\d{1,2})?:(\d{2})?:?(\d{2})?)?(.*?)((\d{1,2})?[\/\.]?(\d{1,2})?[\/\.]?(\d{2,4})?)?\Z/;
my(@c)=($2,$3,$4,$7,$8,$9);
my(@t)=localtime(time+$timeshift*60);
if(!length$c[0]){$c[0]=$t[2]}
if(!length$c[1]){$c[1]=$t[1]}
if(!length$c[2]){$c[2]=$t[0]}
if(!length$c[3]){$c[3]=$t[3]}
if(!length$c[4]){$c[4]=$t[4]+1}
if(!length$c[5]){$c[5]=$t[5]}
if($c[5]<1900){$c[5]+=1900}
$_[0]=sprintf('%2.2d:%2.2d:%2.2d %2.2d/%2.2d/%4d',$c[0],$c[1],$c[2],$c[3],$c[4],$c[5]);
return ((((($c[5]*12+$c[4]-1)*31+$c[3])*24+$c[0])*60)+$c[1])*60+$c[2];
}

#########################################
###подпрограмма анализа строки индекса###
#########################################
sub string
{undef@stp;

eval $fstring;

if(!length$stp[5]){$stp[5]=$stp[4]}
if(!length$stp[7]){$stp[7]=$stp[6]}
if(!length$stp[9]){$stp[9]=$stp[8]}
if(!length$stp[11]){$stp[11]=$stp[10]}
if(!length$stp[13]){$stp[13]=$stp[12]}
if(!length$stp[15]){$stp[15]=$stp[14]}
if(length$stp[15]){--$stp[14];--$stp[15];}
if(length$stp[15]){$stp[17]=$months[$stp[15]];$stp[16]=$stp[17]}

if(length$stp[17]){for$j(0..@months){if($stp[17] eq $months[$j]){$stp[15]=$j;last}}}
$stp[14]=$stp[15];

if(length$stp[18]>0){$stp[19]=$stp[18];$stp[19]=~s/\A0/200/;$stp[19]=~s/\A9/199/;}
else{$stp[18]=$stp[19];$stp[18]=~s/(19)|(20)//;}

for(@stp[4..9,12..15]){$_=sprintf('%2.2d',$_)};

$stp[23]=$stp[9]+($stp[7]+($stp[5]+($stp[13]+($stp[15]+$stp[19]*12)*31)*24)*60)*60;
$stp[23]=sprintf('%15.0f',$stp[23]);
$stp[38]=$stp[0];$stp[38]=~s/(\d+?)\..*\Z/$1/;
$stp[41]=$stp[0];$stp[41]=~s/$inip{'dirkonf'}//;
$stp[42]=$inip{'dirrealkonf'}."/$stp[41]";
}





###############################################
###подпрограмма анализа параметров сообщения###
###############################################
sub filestp
{	undef@stp;if(!-e$_[0]){return-1}
	my($i,$opts);
	open FILESTP,$_[0];my(@b)=<FILESTP>;close FILESTP;chomp@b;

	my($f)=$_[0];$f=~s/.*?(\d*?)\.(.{3,5})\Z/$1\.$2/;
	$stp[0]="$inip{'dirkonf'}/$f";

	$b[0]=~m/<title>(.*?)<\/title>/;$stp[1]=$1;

	if($b[2]=~m/<a href=\"mailto:(.*?)\">(.*?)<\/a>/){$stp[3]="<a href=\"mailto:$1\">$2</a>";$stp[2]=$2;}
	else{$b[2]=~m/<b>(.*?)<\/b>/;$stp[3]=$1;$stp[2]=$1;}

	$b[2]=~m/<\/b> <i>(\d+?):(\d+?):(\d+?) (\d+?)\/(\d+?)\/(\d+?)<\/i>/;
	$stp[4]=$1;$stp[5]=$1;$stp[6]=$2;$stp[7]=$2;$stp[8]=$3;$stp[9]=$3;
	$stp[12]=$4;$stp[13]=$4;$stp[14]=$5;$stp[15]=$5;$stp[19]=$6;
	$stp[18]=$stp[19];$stp[18]=~s/(19)|(20)//;

	$stp[16]=$months[$stp[14]-1];
	$stp[17]=$stp[16];

	$stp[20]=-1;for(@b){if(index($_,'<ul>')==0){++$stp[20]}};

	for(@stp[4..9,12..15]){$_=sprintf('%2.2d',$_)}
	$stp[23]=$stp[8]+($stp[6]+($stp[4]+($stp[12]+($stp[14]+$stp[19]*12)*31)*24)*60)*60;
	$stp[23]=sprintf('%15.0f',$stp[23]);

	for(@b){if(/\A<p><!\-\-(.*?)\-\-><a name=ans>/){$opts=$1;last}}
	if(length$opts>0){($stp[40],$stp[23],$wday,$stp[22])=split(/\//,$opts);}

	for$i(0..@b)
	{	if(index($b[$i],"$inip{'endparagraph'}&nbsp;$inip{'paragraph'}")==0){$stp[24]=$b[$i];if(length$stp[22]<=0){$b[$i]=~s/($inip{'endparagraph'}&nbsp;$inip{'paragraph'})|$inip{'endparagraph'}//g;$stp[22]=length($b[$i]);}}
		if(index($b[$i],'<p><ul><li>')==0){$b[$i]=~/<p><ul><li><a href=\"(.*?)\">(.*?)<\/a><\/ul><p>/;$stp[25]=$1;$stp[26]=$2;}
		if($b[$i]=~/<center><img src/){$b[$i]=~/<center><img src=\"(.*?)\" border/;$stp[27]=$1;}
		if($b[$i]=~/<\!\-\-home\-\->/){$s1=$i-2}
		if($b[$i]=~/<\!\-\-end\-\->/){$s2=$i}
	}
	if(index($b[3],'<div align=left>')==0)
	{	$b[3]=~/<div align=left>$lng[19]<a href=(.*?)>(.*?)<\/a>, $lng[18](.*?)<\/b> <i>(\d\d):(\d\d):(\d\d) (\d\d)\/(\d\d)\/(\d*?)<\/i>/;
		$stp[28]=$1;$stp[29]=$2;$stp[30]=$3;$stp[31]=$3;$stp[32]=$4;$stp[33]=$5;$stp[34]=$6;$stp[35]=$7;$stp[36]=$8;$stp[37]=$9;
		if($stp[31]=~/<a href=\"mailto:/){$stp[31]=~/<a href=\"mailto:.*?\">(.*?)<\/a>/;$stp[30]=$1}
	}
	$f=~/(\d*?)\./;$stp[38]=$1;
	$stp[39]=branch($stp[38],@b[$s1..$s2]);
	$stp[41]=$f;$stp[42]="$inip{'dirrealkonf'}/$f";
	return 1;
}

###################################################
###подпрограмма преобразования разрешенных тегов###
###########created by Konstantin Boyandin##########
###################################################
sub clean_html_tags {
	my ($src, @allowed_list) = @_;
	my $pv = "";
	# Remove 'plused' tags
	$src =~ s/<\/?\+[a-zA-Z]{1}([^>]|\n)*>//g;
	# Turn all allowable <XXX ...> tags into <+XXX ...>
	foreach $pv (@allowed_list) {
	$src =~ s/<$pv([^a-zA-Z]{1})/<\+$pv$1/ig;
	$src =~ s/<\/$pv([^a-zA-Z]{1})/<\/\+$pv$1/ig;
	}
	# Remove 'unplused' tags
	$src =~ s/<\/?[a-zA-Z]{1}([^>]|\n)*>//g;
	# Remove HTML comments (possible security breach!)
	$src =~ s/<\!--.*?-->//g;
	# 'Unplus' all protected tags
	foreach $pv (@allowed_list) {
	$src =~ s/<\+$pv([^a-zA-Z]{1})/<$pv$1/ig;
	$src =~ s/<\/\+$pv([^a-zA-Z]{1})/<\/$pv$1/ig;
	}
	return $src;
}

###############################################
###подпрограмма преобразования времени в код###
###############################################
sub extrtime
{	my$s=1;
	for(reverse map $s *= $_,1,60,60,24,31,12)
	{	unshift@et,int($_[0]/$_);
		$_[0]-=$et[0]*$_;
	}
	$#et=5;
	for(@et[0..4]){$_=sprintf('%2.2d',$_)};
}

############################
###подпрограмма архивации###
############################
sub archivate
{
# массив архивируемых номеров
open NAM,"$inip{'dirrealkonf'}/$inip{'indname'}";@ini=<NAM>;close NAM;
$mmm=0;$m=0;for$i(0..$#ini)
{	if(index($ini[$i],"<!--$inip{'mesarhiv'}-->")==0){$j1=$i;$mmm=1;}
	if(index($ini[$i],"<!--end-->")==0){$j2=$i-1;}
}
if($mmm==0){$error=2;return;}
$j=0;for$i($j1..$j2)
{	if(index($ini[$i],'<li>')>=0){($a,$forarc[$j],$a)=split('--',$ini[$i],3);++$j;}
}

# название индекса архива
$s1=$t[3];$s2=$t[4]+1;
if(length $s1==1){$s1='0'.$s1}
if(length $s2==1){$s2='0'.$s2}
$inip{'indexarc'}.="$s1$s2$t[5]";
if($inip{'method'}==4){$arcext='rar'}else{$arcext='zip'}
$i='';while($i<100){if(-e "$inip{'realpath'}/$inip{'dirarc'}/$inip{'indexarc'}$i.htm"==1 or -e "$inip{'realpath'}/$inip{'dirarc'}/$inip{'indexarc'}$i.$arcext"==1){++$i}else{$inip{'indexarc'}.="$i";last;}}

$stp[4]=$t[2];$stp[5]=$t[2];
$stp[6]=$t[1];$stp[7]=$t[1];
$stp[8]=$t[0];$stp[9]=$t[0];
$stp[10]=$days[$t[6]-1];$stp[11]=$days[$t[6]-1];
$stp[12]=$t[3];$stp[13]=$t[3];
$stp[14]=$t[4]+1;$stp[15]=$t[4]+1;
$stp[16]=$months[$stp[15]-1];$stp[17]=$stp[16];
$stp[18]=$t[5];$stp[19]=$t[5];
$stp[18]=~s/(19)|(20)//;

for(@stp[4..9,12..15]){$_=sprintf('%2.2d',$_)}

# $mesarhiv как сообщение, с которого начинается архив;
# определяется либо пользователем, либо в wtboard.cgi, раздел archivating

if($inip{'method'}==3)		# удаление
{	for$i(0..$#forarc)
	{	for$j(0..4){if(-e "$inip{'dirrealkonf'}/$forarc[$i].$exts[$j]"==1){$ia=$j;last}}
		unlink "$inip{'dirrealkonf'}/$forarc[$i].$exts[$ia]";
	}

	open NAM,"$data/$wtbstruct";@b=<NAM>;close NAM;
	open NAM,">$data/$wtbstruct";
	for $i(0..$#b)
	{	@c=split(/[(\n\.,\*)]/,$b[$i]);
		if($c[1] eq $inip{'mesarhiv'}){last;}
		print NAM $b[$i]
	}
	close NAM;
	savewrong('ARCDL',$login);
}
elsif($inip{'method'}==1 or $inip{'method'}==2 or $inip{'method'}==4)
{	$allsize=0;
	if(-e "$inip{'realpath'}/$inip{'dirarc'}" !=1){$error=1;return;}

	if($inip{'sethtaccess'} eq 'on'){open NAM,"+>$inip{'realpath'}/$inip{'dirarc'}/.htaccess";print NAM "CharsetByExtension $inip{'codepage'} \.html \.htm \.shtml \.stm \.txt \.cgi";close NAM;}

	open NAM,"+>$inip{'realpath'}/$inip{'dirarc'}/$inip{'indexarc'}.htm";
	substit($patp{'begarchive'});print NAM "$patp{'begarchive'}\n<ul>\n<!--home-->\n";
	for$i($j1..$j2)
	{	$ini[$i]=~s/(\.htm>)|(\.html>)|(\.shtml>)|(\.stm>)/\.html>/;
		print NAM $ini[$i]
	}
	substit($patp{'endarchive'});print NAM $patp{'endarchive'};
	close NAM;

	if(-e "$inip{'realpath'}/$inip{'dirarc'}/$inip{'indexarc'}.htm"!=1){$error=2;return;}
	$s=-s "$inip{'realpath'}/$inip{'dirarc'}/$inip{'indexarc'}.htm";$allsize+=$s;

	for $i(0..$#forarc)
	{	for$j(0..4){if(-e "$inip{'dirrealkonf'}/$forarc[$i].$exts[$j]"==1){$ia=$j;last}}
		if(-e "$inip{'dirrealkonf'}/$forarc[$i].$exts[$ia]"!=1){next}
		$s=-s "$inip{'dirrealkonf'}/$forarc[$i].$exts[$ia]";$allsize+=$s;
		open NAM,"$inip{'dirrealkonf'}/$forarc[$i].$exts[$ia]";@b=<NAM>;close NAM;
		for(@b){s/root=off/root=on/};
		for(@b){s/\&numans=/&arc=%2E%2E\/$inip{'dirarc'}\/$forarc[$i].html\&numans=/};
		for(@b){s/$inip{'dirkonf'}\//$inip{'dirarc'}\//g};
		for(@b){s/(\d*?)(\.html)|(\.htm)|(\.shtml)|(\.stm)/$1\.html/g;};
		open NAM,"+>$inip{'realpath'}/$inip{'dirarc'}/$forarc[$i].html";
		print NAM @b;
		close NAM;
		undef @b;

		if(-e "$inip{'realpath'}/$inip{'dirarc'}/$forarc[$i].html"==1){if("$inip{'realpath'}/$inip{'dirarc'}/$forarc[$i].html" ne "$inip{'dirrealkonf'}/$forarc[$i].$exts[$ia]"){unlink "$inip{'dirrealkonf'}/$forarc[$i].$exts[$ia]";}}
	}

	for$i(4..19)
	{	$patp{'regstring'}=~s/$tag[$i]/$stp[$i]/g;
		$patp{'setnewsstring'}=~s/$tag[$i]/$stp[$i]/g;
	}

	$s1=$ini[$j1];
	$i=$#ini-1;while($i>2)
	{	if(index($ini[$i],"<!--")==0){$s2=$ini[$i];$i=1}
		--$i;
	}
	if($inip{'intervaltype'}==1)	# от сооб. до сооб.
	{	($s,$s1,$s)=split('--',$s1);
		($s,$s2,$s)=split('--',$s2);
		$interval="$s2&#151;$s1";
	}
	elsif($inip{'intervaltype'}==2)
	{	string($s2);$interval="$stp[13] $stp[17] $stp[19]";
		string($s1);$interval.="&#151;$stp[13] $stp[17] $stp[19]";
	}


	open NAM,"$data/$wtbstruct";@b=<NAM>;close NAM;
	open NAM,">$data/$wtbstruct";
	for $i(0..$#b)
	{	@c=split(/[(\n\.,*)]/,$b[$i]);
		if($c[1] eq $inip{'mesarhiv'}){last;}
		print NAM $b[$i]
	}
	close NAM;
}


open NAM,">$inip{'dirrealkonf'}/$inip{'indname'}";
print NAM @ini[0..($j1-1),($j2+1)..$#ini];
close NAM;

if($inip{'method'}==3){savewrong('ARCDL',$login);return;}

if($inip{'method'}==1)
{	$inip{'indexarc'}="\.\./$inip{'dirarc'}/$inip{'indexarc'}.htm";
	savewrong('ARCST',$login);
	$errlevel="<b>Statistics:</b> <br>Succesfully archived <b>".($#forarc+1)."</b> file(s) archived into <b>$inip{'realpath'}/$inip{'dirarc'}</b>. <br>Size of source files: <b>$allsize</b>. <br>";
}
if($inip{'method'}==2 or $inip{'method'}==4)
{	for$i(0..@forarc)
	{	$forarc[$i]="$inip{'realpath'}/$inip{'dirarc'}/$forarc[$i].html ";
	}
	$#forarc=$#forarc-1;
	if($inip{'method'}==2){system('zip','-j -m -q',"\"$inip{'realpath'}/$inip{'dirarc'}/$inip{'indexarc'}.$arcext\" @forarc \"$inip{'realpath'}/$inip{'dirarc'}/$inip{'indexarc'}.htm\" ");$arczp='ARCZP';}
	elsif($inip{'method'}==4){system("rar mf -inul -m5 -ep -s $inip{'realpath'}/$inip{'dirarc'}/$inip{'indexarc'}.$arcext @forarc $inip{'realpath'}/$inip{'dirarc'}/$inip{'indexarc'}.htm ");$arczp='ARCRR';}
	if(!$!)
	{	($s,$s,$s,$s,$s,$s,$s,$size)=stat"$inip{'realpath'}/$inip{'dirarc'}/$inip{'indexarc'}.$arcext";$ksize=int($size/1024);
		savewrong($arczp,$login,'','',$s1);
		$errlevel="<b>Statistics:</b> <br>Succesfully archived <b>".($#forarc+1)."</b> file(s) into <b>$inip{'realpath'}/$inip{'dirarc'}/$inip{'indexarc'}.$arcext</b>. <br>Size of source files: <b>$allsize</b>. <br>Size of archive: <b>$size</b>. <br>";
		$inip{'indexarc'}="\.\./$inip{'dirarc'}/$inip{'indexarc'}.$arcext";
	}
	else
	{	$inip{'indexarc'}="\.\./$inip{'dirarc'}/$inip{'indexarc'}.htm";
		savewrong('ARCST',$login,'','','err'.$s1);
		$errlevel="<b>Statistics:</b> <br>Compression <b>$arcext</b> failed, possible cause: unable to execute the compression program. <br>Standart archivation applied: <b>".($#forarc+1)."</b> file(s) archived into <b>$inip{'realpath'}/$inip{'dirarc'}</b>. <br>Size of source files: <b>$allsize</b>. <br>";
	}
}

open NAM,"+>$inip{'realpath'}/$inip{'dirarc'}/index.htm";
print NAM "<HTML><HEAD><TITLE>$lng[472]</TITLE><META HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=$inip{'dirkonf'}/$inip{'archive'}\"></HEAD>
<BODY><a href=\"$inip{'dirkonf'}/$inip{'archive'}\">$lng[472]</a></BODY></HTML>";
close NAM;


for($patp{'regstring'},$patp{'setnewsstring'}){s/\$interval/$interval/g;s/\$href/$inip{'indexarc'}/g;s/\$ofkonf/$inip{'ofkonf'}/g;s/\$nummes/$#forarc/g;s/\$ksize/$ksize/g;s/\$size/$size/g;}

substit($patp{'regstring'});substit($patp{'setnewsstring'});
# новостная строка
if($inip{'setnewsarc'} eq 'on')
{	$yearh=$t[5];$yeare=$t[5];$monh=$t[4];$mone=$t[4];
	$dayh=$t[3];$daye=$t[3]+2;$hourh=$t[2];$houre=$t[2];
	$minh=$t[1];$mine=$t[1];

	open NAM,"+>>$data/$wtbnews";
	print NAM "$yearh;;$monh;;$dayh;;$hourh;;$minh;;$yeare;;$mone;;$daye;;$houre;;$mine;;$patp{'setnewsstring'}<p>\n";
	close NAM;
}

open NAM,"$inip{'dirrealkonf'}/$inip{'archive'}";@a=<NAM>;close NAM;
for$i(0..@a){if(index($a[$i],'<!--archive-->')>=0){$a[$i]=~s/<\!--archive-->/<\!--archive-->$patp{'regstring'}/g}}
open NAM,"+>$inip{'dirrealkonf'}/$inip{'archive'}";
print NAM @a;close NAM;

}

###########
###about###
###########
sub about
{	($a,$b)=&verifyreg;
	$lng[204]=~s/%registration/$a/i;
	print "\n$lng[204]";
}

################################################
###подпрограмма сохранения сторонних настроек###
################################################
###savecopyright($begin,$end,$string)
sub savecopyright
{	$s=$inip{'copyright'}=~s/$_[0].*?$_[1]/$_[0]$_[2]$_[1]/gi;
	if($s<=0){$inip{'copyright'}.=$_[0].$_[2].$_[1]}
	savevalue('Board Options','copyright',$inip{'copyright'});
}

################################################
###подпрограмма сохранения сторонних настроек###
################################################
sub savevalue
{	open NAM,"$data/$wtboard";@b=<NAM>;close NAM;chomp @b;
	rename "$data/$wtboard","$data/$wtboard.old";
	open NAM,">$data/$wtboard";

	$s=0;for$i(0..@b)
	{	if($b[$i]=~/\A[\[;]/){next}
		if(!length$b[$i]){next}
		($b1,$b2)=split('=',$b[$i],2);
		if(length($b1)>0)
		{	$j=0;
			while($j<$#a)
			{	if($_[1] eq $b1){$b2=$_[2];$s=1;}
				++$j;++$j;
			}
			$b[$i]="$b1=$b2";
		}
	}
	if($s==0)
	{	for$i(0..@b)
		{	if($b[$i] eq "[$_[0]]")
			{	$b[$i]="$b[$i]\n$_[1]=$_[2]";$s=1;
			}
		}
	}
	if($s==0){$b[$#b+1]="\n\n[$_[0]]\n$_[1]=$_[2]";}
	for(@b){print NAM "$_\n";}
	close NAM;
	undef @b;
	if(-z "$data/$wtboard"==1){rename "$data/$wtboard.old","$data/$wtboard";}
}

##############################################
###подпрограмма записи критических действий###
##############################################
###savewrong($action,$user,$password,$email,$misc)
sub savewrong
{	open WRN,">>$data/$wtwrong";
	print WRN "$_[0] Time=";
	printf WRN ('%2.2d:%2.2d:%2.2d %2.2d/%2.2d/%4.4d',$t[2],$t[1],$t[0],$t[3],$t[4]+1,$t[5]);
	print WRN "; Log=$_[1]; Pwd=$_[2]; Host=$REMOTE_ADDR; Email=$_[3]; Misc=$_[4]\n";
	close WRN;
}

#############################################
###подпрограмма верификации администратора###
#############################################
sub verifyadmin
{	open NAM,"$data/$wtbadmin";$i=0;while(<NAM>){chomp;($nam[$i],$pwd[$i],$stat[$i],$s)=split(';;');++$i;}close NAM;

for $i(0..$#nam)
{	if($_[0] eq $nam[$i])
	{	if($_[1] eq $pwd[$i]){$stat=$stat[$i];return $stat;}
		else
		{	return -1;
		}
	}
}
return -1;
}


#################################################
###подпрограмма вывода шапки администрирования###
#################################################
###titleadmin($mode,$login,$stat)
sub titleadmin
{	print "\n<html><title>$lng[49] $_[0] &#151; $_[1]</title><body bgcolor=#f0f0ff><font size=\"+2\"><center>$lng[50] <b>$_[1]</b>,<font size=\"+1\"><br><i>$lng[51]<b>";
	if($_[2]=~/a/){print ": $lng[52] "}
	if($_[2]=~/i/){print ": $lng[53] "}
	if($_[2]=~/g/){print ": $lng[54] "}
	if($_[2]=~/d/){print ": $lng[55] "}
	if($_[2]=~/h/){print ": $lng[56] "}
	if($_[2]=~/e/){print ": $lng[57] "}
	if($_[2]=~/n/){print ": $lng[58] "}
	if($_[2]=~/s/){print ": $lng[59] "}
	print "</b></i><p>$lng[487]<i><b>$_[0]</b></i></font><p>$hr</center></font><p>";
}


####################
###форма вкл/выкл###
####################
###sub optonoff('parameter',$title,$desc)
sub optonoff
{	if($inis{$_[0]} eq 'on'){$s1=' checked';$s2='';}
	else{$s1='';$s2=' checked';}
	print "\n<tr><td colspan=2 align=left>$_[1]</td><td colspan=4>$lng[213]<input type=radio name=$_[0] value=on$s1>&nbsp;&nbsp;$lng[214]<input type=radio name=$_[0] value=off$s2></td></tr>";
	if(length$_[2]>0){print "\n<tr><td colspan=6 align=left>$_[2] &nbsp;<p></td></tr>";}
}

###########################
###форма текстового поля###
###########################
###optfield('parameter',$title,$desc)
sub optfield
{	print "\n<tr><td colspan=2 align=left>$_[1]</td><td colspan=4><input type=text name=$_[0] value=\"$inis{$_[0]}\" size=40></td></tr>";
	if(length$_[2]>0){print "\n<tr><td colspan=6 align=left>$_[2] &nbsp;<p></td></tr>";}
}

###########################
###форма текстового поля, два рядом###
###########################
###opt2field('parameter1',$title1,'parameter2',$title2,$desc,$length1,$length2)
sub opt2field
{	my($l1)=10;if($_[5]>0){$l1=$_[5]}
	my($l2)=$l1;if($_[6]>0){$l2=$_[6]}
	print "\n<tr><td colspan=2 align=left>$_[1]</td><td><input type=text name=$_[0] value=\"",$inis{$_[0]},"\" size=$l1></td><td colspan=2 align=left>$_[3]</td><td><input type=text name=$_[2] value=\"",$inis{$_[2]},"\" size=$l2></td></tr>";
	if(length$_[4]>0){print "\n<tr><td colspan=6 align=left>$_[4] &nbsp;<p></td></tr>";}
}

######################################
###форма текстового поля, ширина 10###
######################################
###optfield('parameter',$title,$desc)
sub optfield10
{	print "\n<tr><td colspan=2 align=left>$_[1]</td><td colspan=4><input type=text name=$_[0] value=\"",$inis{$_[0]},"\" size=10></td></tr>";
	if(length$_[2]>0){print "\n<tr><td colspan=6 align=left>$_[2] &nbsp;<p></td></tr>";}
}

######################################
###форма текстового поля, ширина 20###
######################################
###optfield('parameter',$title,$desc)
sub optfield20
{	print "\n<tr><td colspan=2 align=left>$_[1]</td><td colspan=4><input type=text name=$_[0] value=\"",$inis{$_[0]},"\" size=20></td></tr>";
	if(length$_[2]>0){print "\n<tr><td colspan=6 align=left>$_[2] &nbsp;<p></td></tr>";}
}

############################
###форма выбора из списка###
############################
###optselect('parameter',$title,$desc,$nvalues,$values,$descs)
sub optselect
{	for$i(4..4+$_[3]-1)
	{	if($inis{$_[0]} eq $_[$i]){$s[$i-3]=' selected';}
		else{$s[$i-3]='';}
	}
	print "\n<tr><td colspan=2 align=left>$_[1]</td><td colspan=4><select name=$_[0]>";
	for$i(4..4+$_[3]-1)
	{	print "<option value=\"$_[$i]\"$s[$i-3]>$_[$i+$_[3]]";
	}
	print "</select></td></tr>";
	if(length$_[2]>0){print "\n<tr><td colspan=6 align=left>$_[2] &nbsp;<p></td></tr>";}
}

#####################################
###форма кнопки принятия изменений###
#####################################
###optsubmit($login,$pass,$oper,$fid,$stringsubmit)
sub optsubmit
{	print "\n<center><input type=hidden name=fid value=\"$_[3]\"><input type=hidden name=login value=\"$_[0]\"><input type=hidden name=pass value=\"$_[1]\"><input type=hidden name=oper value=\"$_[2]\"><input type=submit value=\"$_[4]\"></center>";
}

###################################################
###вывод новостей и извещений о новых сообщениях###
###################################################
###&shownews
sub shownews
{
# вставка общих новостей
if($newstype==1 or $newstype==3)
{	open NAM,"$data/$wtbnews";@a=<NAM>;close NAM;chomp @a;

	$writed=0;
	$t=$t[1]+$t[2]*60+$t[3]*60*24+$t[4]*60*24*31+$t[5]*60*24*31*12;

	for($i=$#a;$i>=1;--$i)
	{	@b=split(';;',$a[$i]);
		$b1=$b[4]+$b[3]*60+$b[2]*60*24+$b[1]*60*24*31+$b[0]*60*24*31*12;
		$b2=$b[9]+$b[8]*60+$b[7]*60*24+$b[6]*60*24*31+$b[5]*60*24*31*12;
		if($t>=$b1 and $t<=$b2)
		{	$writed=1;
			print "$b[10]\n";
		}
		undef $a[$i];undef @b;
	}
	if($writed==1){print "$inip{'separator'}<p>"}
	$writed=0;
}
# вставка частной информации
	if($inip{'individual'} eq 'off'){return;}
	if(!length$realn){return;}
	if($utimes<=0){return;}
	if($newstype==1){return}

# сканирование индекса на предмет новых сообщений
	if($unewmes ne 'off' or $unewans ne 'off')
	{	open NAM,"$inip{'dirrealkonf'}/$inip{'indname'}";@a=<NAM>;chomp@a;
		$newmes=0;$newans=0;$i=0;
	}

	if($unewmes ne 'off')
	{	for$i(0..@a)
		{	if(index($a[$i],'--><li>')<1){next}
			string($a[$i]);
			if($stp[23]>=$utimes){++$newmes}
		}
	}

# сканирование индекса на предмет новых сообщений - ответов данному участнику
	if($unewans ne 'off')
	{	$i=0;while($i<$#a)
		{	$j=0;if(index($a[$i],"$realn")>0)
			{	++$i;
				if(index($a[$i],'--><li>')<1){next}
				$j=1;while($j>0)
				{	if(index($a[$i],'</ul>')>=0){--$j}
					else
					{	string($a[$i]);
						correct($stp[2]);
						if($stp[23]>$utimes and $stp[2] ne $names){++$newans}
					}
					++$i;
				}
			}
			++$i;
		}
	}

# сообщение-результат

	if($newmes>0 or $newans>0)
	{	substit($lng[280],$patp{'newmesanstext'});
		substit($lng[281],$patp{'newmestext'});
		substit($lng[282],$patp{'newanstext'});

		$s='';if($unewwinmes ne 'off'){$s=" target=\"new\"";}
		$s1="<a href=\"$inip{'dircgi'}/wtbservice.cgi?search=newmes&fid=$fid&begin=$utimes\"$s>$newmes</a>";
		$s='';if($unewwinans ne 'off'){$s=" target=\"new\"";}
		$s2="<a href=\"$inip{'dircgi'}/wtbservice.cgi?search=newans&fid=$fid&begin=$utimes\"$s>$newans</a>";

		for(@lng[280..282]){s/[%\$]newmes/$s1/gi;s/[%\$]newans/$s2/gi;s/[%\$]snewmes/$newmes/gi;s/[%\$]snewans/$newans/gi}

		if(!$newmes){$unewmes='off'}
		if(!$newans){$unewans='off'}

		if($unewmes ne 'off' && $unewans ne 'off'){print $lng[280]}
		elsif($unewmes ne 'off'){print $lng[281]}
		elsif($unewans ne 'off'){print $lng[282]}
	}
}


###################################
###обновление базы пользователей###
###################################
###&updateuser
sub updateuser
{	if(!length$names){return}
	$wtbuser{"m_$names"}=$mails;
	$wtbuser{"h_$names"}=$REMOTE_ADDR;
	$wtbuser{"u_${fid}_$names"}=$pars;
	$wtbuser{"t_${fid}_$names"}=$curtime;
}


########################################################
###проверка доступа пользователя с запрещенных хостов###
########################################################
###verifyuser($title,$notaccess)
sub verifyuser
{	my$ret=0; 
# проверка доступа с запрещенного по cookie
	if($wtbuser{"i_$cookie"} eq '-'){$ret=-1}
	elsif($wtbuser{"i_$cookie"} eq '!'){$ret=-2}
	if($ret<0){$_[0]=$wtbuser{"it_$cookie"};$_[1]=$wtbuser{"ib_$cookie"};return$ret}
# проверка доступа с запрещенного ip-адреса
	substit($lng[29],$patp{'noaccessbegin'});
	substit($lng[578],$patp{'readonlybegin'});
	@c=split(';',$wtbuser{'ignor_ip'});
	for(@c)
	{	if(!length){next}
		if($REMOTE_ADDR=~/\Q$_/)
		{$ret=-1;$_[0]=$lng[578];$_[1]=$lng[578]}
	}
	@c=split(';',$wtbuser{'stop_ip'});
	for(@c)
	{	if(!length){next}
		if($REMOTE_ADDR=~/\Q$_/)
		{$ret=-2;$_[0]=$lng[29];$_[1]=$lng[29]}
	}
	return $ret;
}


###################################################
###получение ветви сообщений в формате структуры###
###################################################
###$branch=branch($nummes,@a), при этом @a - массив с $indname
sub branch
{	my($i,$s);
	my($nummes,@a)=@_;my($branch)='';
	$s=0;$i=2;while($i<$#a)
	{	$a[$i]=~/<!\-\-(\d*?)\-\->/;
		if($1==$nummes)
		{	$branch=$1;++$i;
			while($i<$#a)
			{	if($a[$i]=~/<ul>/)
				{	$branch=$branch.'(';++$s;
					$a[$i]=~/<!\-\-(\d*?)\-\->/;$branch=$branch.$1;
				}
				elsif($s>0 and $a[$i]=~/<\/ul>/){$branch=$branch.')';--$s;}
				++$i;if($s<0){return $branch}
				if(index($a[$i],'<!--')==0){return $branch};
			}
		}
		++$i;
	}
	return $branch;
}


##########################
###проверка регистрации###
##########################
sub verifyreg
{	use IO::Socket;
#	my$host='localhost';my$port='http(80)';my$wbcgi='/cgi-bin/wtboardreg.cgi';
	my$host='wtiger.ncport.ru';my$port='8101';my$wbcgi='/cgi/wtboardreg.cgi';
	my$remote=IO::Socket::INET->new(Proto=>"tcp",PeerAddr=>$host,PeerPort=>$port);
	unless($remote){return}$remote->autoflush(1);
	$inip{'registration'}=~s/\s/\+/g;$inip{'registration'}=~s/\//\|/g;
	print $remote "GET $wbcgi?fid=$fid&registration=$inip{'registration'} HTTP/1.1\015\012Host: $host\015\012Accept: */*\015\012User-Agent: Mozilla/4.05 [en] (White Tiger WWW Board registration verification)\015\012Referer: $ENV{'HOST'}\015\012\015\012";
	my($a)=join('',<$remote>);close $remote;
	my($b)=$a=~/<reg>(.*?)<\/reg>/;
	($a)=$a=~/<registration>(.*?)<\/registration>/;
	$a=~s/\$errvlcolor/$inip{'errvlcolor'}/gi;
	return $a,$b;
}


########################
###удаление сообщения###
########################
###deletemes($delref,$delfil), при этом $delfil - 'on' или 'off'
sub deletemes
{	my($err)=0;my(@s,$s,$j,$ia,$exist,@b,@c);
	for$j(0..3){if(-e "$inip{'dirrealkonf'}/$_[0].$exts[$j]"){$ia=$j;last}}
	$b[0]=$_[0];$stp[0]=$_[0];
	$exist=filestp("$inip{'dirrealkonf'}/$_[0].$exts[$ia]");
# список ответов вместе с текущим
	if($exist==1)
	{	$s=$stp[39];$s=~tr/\(\)/s/d;@b=split('s',$s);
# список вышестоящих
		$s=$stp[40];$s=~s/\.//g;@c=split(';',$s);
	}
# обновление файла структуры
	open NAM,"$data/$wtbstruct";my(@ini)=<NAM>;close NAM;chomp @ini;
	my($i)=0;
	for(@ini)
	{	@s=split(/([\(.,*\)])/);
		for$i(@s)
		{	for$j(@b){if($i==$j){undef$i}}
		}
		$_=join '',@s;
		while($_=~s/\(\)//g){}
	}
	open NAM,"+>$data/$wtbstruct";print NAM "\n";for(@ini){if(length$_>1){print NAM "$_\n"}};close NAM;

# обновление индекса
	open NAM,"$inip{'dirrealkonf'}/$inip{'indname'}";@ini=<NAM>;close NAM;chomp@ini;

	for$i(@b)
	{	$s=0;for(@ini)
		{	if(/<!\-\-$i\-\->/){$err=1;if(/<ul>/){++$s;};undef$_;next;}
			elsif(/<ul>/ and $s>0){++$s;undef$_;}
			elsif(/<\/ul>/ and $s>0){--$s;undef$_;next;}
			if($s==0){next}
			if($s<=1){last}
		}
	}

	open NAM,"+>$inip{'dirrealkonf'}/$inip{'indname'}";for(@ini){if(length$_){print NAM "$_\n"}};close NAM;

# обновление сообщений, если файл удаляется
	if($_[1] eq 'on')
	{	$err=2;
		for$i(@c)
		{	for$j(0..3){if(-e "$inip{'dirrealkonf'}/$i.$exts[$j]"){$ia=$j;last}}

			open NAM,"$inip{'dirrealkonf'}/$i.$exts[$ia]";@ini=<NAM>;close NAM;chomp@ini;
			for$j(@b)
			{	$s=0;for(@ini)
				{	if(/<!\-\-$j\-\->/){if(/<ul>/){++$s;};undef$_;next;}
					elsif(/<ul>/ and $s>0){++$s;undef$_;}
					elsif(/<\/ul>/ and $s>0){--$s;undef$_;next;}
					if($s==0){next}
					if($s<=1){last}
				}
			}
			open NAM,"+>$inip{'dirrealkonf'}/$i.$exts[$ia]";for(@ini){if(length$_){print NAM "$_\n"}};close NAM;
		}
		for$i(@b)
		{	for$j(0..3){if(-e "$inip{'dirrealkonf'}/$i.$exts[$j]"){$ia=$j;last}}
			unlink "$inip{'dirrealkonf'}/$i.$exts[$ia]";
			if($inip{'replacedeleted'} eq 'on'){open NAM,">$inip{'dirrealkonf'}/$i.$exts[$ia]";print NAM $lng[672];close NAM}
		}
	}
	return $err;
}


###########################
###интерполяция шаблонов###
###########################
sub substit
{	local($i);if(length$_[1]){$_[0]=$_[1]}
	my(@a)=('href','name','password','subj','fid','command','cprt');
	my(@b)=($href,$name,$password,$subj,$fid,$command,$cprt);
	for$i(0..$#a){$_[0]=~s/[\$%]$a[$i]/$b[$i]/gi}
	while(my($a,$b)=each%inip){$_[0]=~s/[\$%]$a/$b/gi}
	$_[0]=~s/<!!>/\n/g;
}


#############################
###интерполяция параметров###
#############################
sub initiate
{	my($s1,$s2);
	while(($s1,$s2)=each%inip)
	{	$s2=~s/([\'\\])/\\$1/g;
		eval "\$$s1='$s2';";
	}
	while(($s1,$s2)=each%patp)
	{	$s2=~s/([\'\\])/\\$1/g;
		eval "\$$s1='$s2';";
	}
}

1;
