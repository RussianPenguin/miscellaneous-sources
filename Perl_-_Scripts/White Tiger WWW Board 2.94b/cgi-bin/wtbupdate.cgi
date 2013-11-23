#!/usr/bin/perl

# White Tiger WWW Board ver.2.936b
# система wwwboard. Разработка, реализация
# (C) 1998-2000, White Tiger (2:5049/91.38; 
# email:wtiger@mail.ru; http://wtiger.ncport.ru)
# wtbupdate.cgi - модуль обновления конфигурационного файла
# wtbupdate.cgi - module of update of configuration file

# замена переменных производится в файле wtbext.cgi
# you must change values in the wtbext.cgi
















# прочие величины
if(!-e"wtbext.cgi"){print "\nError: not found wtbext.cgi";exit}
require "wtbext.cgi";
params(4);

open DAT,"$data/$wtbini";@lng=<DAT>;close DAT;chomp @lng;

print "\n\n<html><title>Обновление форумов</title><b>Обновление:</b><p><hr size=1>\n";

### обработка
for$i(0..$#lng)
{
($id,$wtbaccess,$wtbadmin,$wtblang,$wtblast,$wtbnames,$wtbnews,$wtboard,$wtbreplace,$wtbstruct,$wtwrong)=split(/;/,$lng[$i]);

$registration='Russian user of White Tiger WWW Board//WTH7LyGpAUp0M';
$thekonf="Форум";
$tokonf="на форум";
$ofkonf="форума";
$onkonf="на форуме";
$admin="admin\@host.com";
$private="noprivate";
$dirkonf="../wtboard";
$dirrealkonf="../wtboard";
$dircgi="../cgi-bin";
$realpath="..";
$quote=">";
$quotebeg="<i>";
$quoteend="</i>";
$substip="on";
$addip="off";
$notag=0;
$usecookie="on";
$quoting="on";
$individual="on";
$includeform="on";
$ext="shtml";
$reply="Re";
$paragraph="<dd>";
$endparagraph="</dd>";
$separator="<hr size=1 width=80% align=center>";
$hr="<hr size=1 width=80% align=center>";
$selectnew=360;
$selecttag="<font color=#ff0000><b>New</b></font>";
$nulcolor="#0000ff";
$selectnul=2;
$string="<a href=\$href>\$subj</a> &#151; <b>\$name</b> <i>\$fhour:\$fmin:\$fsec \$fday/\$fmonth/\$fullyear</i> (\$answers) \$new";
$months="января/февраля/марта/апреля/мая/июня/июля/августа/сентября/октября/ноября/декабря";
$days="Понедельник,/Вторник,/Среда,/Четверг,/Пятница,/Суббота,/Воскресенье,";
$allowedtags="a/b/i/u/font/sub/sup/br/p/center/dd/dl/dt/em/hr/ol/ul/li/pre/s/table/td/th/tr";
$timeshift=0;
$smiles="on";
$allrestrict=0;
$codepage="cp-1251";
$answerlabel="* ";
$arclabel="** ";
$filter="off";
$filterwords="";
$indname="index.shtml";
$verifydbl=1;
$maxshowsubj=500;
$wrnpassbeg='<font size=-1 color=#888888>?</font> ';
$wrnpassend='';
$passstyle=1;
$externalcalls='off';
$overdefine='off';
$preview='on';
$resetbutton='off';
$quotesize=0;
$imgexts='jpg/jpeg/gif/png';
$begbody='<body bgcolor="$errbgcolor" text="$errtcolor" link="$errlcolor" vlink="$errvlcolor" alink="$erralcolor" background="$errimg">';
$endbody="</body></html>";
$showsuccess=0;
$selftimeout=1;
$contextreplace=1;
$copyright='';
$allowroot='on';
$setnroot=15;
$faq='faq.htm';
$expirescookie='Wednesday, 08-Dec-19 23:59:59';
$replacedeleted='on';
$treestyle=1;
$movenewtop='on';
$mestimeout=2400;

$timelimit=30;
$meslimit=1000;
$method=2;
$dirarc="archive";
$indexarc="index";
$intervaltype=2;
$setnewsarc="on";
$archive='archive.htm';
$sethtaccess='on';
$service='service.shtml';
$arctimeout=3;

$info="Информация о форуме";
$userstat="on";
$ipuserstat="off";
$ignorstat="off";
$advisenew='on';
$adviseans='on';
$statdays=15;

$lenlogin=30;
$lenpass=10;
$lenemailmes=50;
$lenemailans=30;
$lensubj=50;
$lenrows=12;
$lencols=70;
$lenurl=50;
$lentitleurl=50;
$lenimg=50;
$seturl="on";
$maxsubj=500;
$maxurl=200;
$setimg='on';

$indbgcolor="#c6e8d9";
$indtcolor="#800000";
$indlcolor="#000000";
$indvlcolor="#800000";
$indalcolor="#ffffff";
$indimg="";
$mesbgcolor="#f0f0ff";
$mestcolor="#000000";
$meslcolor="#000000";
$mesvlcolor="#800000";
$mesalcolor="#ffffff";
$mesimg="";
$errbgcolor="#a8bfb4";
$errtcolor="#000000";
$errlcolor="#000000";
$errvlcolor="#800000";
$erralcolor="#ffffff";
$errimg="";

$begmesform="<html><title>Отправление сообщения \$tokonf</title><body bgcolor=\"\$errbgcolor\" text=\"\$errtcolor\" link=\"\$errlcolor\" vlink=\"\$errvlcolor\" alink=\"\$erralcolor\" background=\"\$errimg\"><center>[<a href=\$dirkonf/>\$thekonf</a>] [<a href=\$dirkonf/\$faq>Правила</a>] <p>\$separator <P><h2>Отправление сообщения \$tokonf</h2><P> \$separator<P><div align=left>";
$endmesform="</body></html>";
$begansform="<html><title>Отправление ответа \$tokonf на сообщение &#171;\$subj&#187;</title><body bgcolor=\"\$errbgcolor\" text=\"\$errtcolor\" link=\"\$errlcolor\" vlink=\"\$errvlcolor\" alink=\"\$erralcolor\" background=\"\$errimg\"><center>[<a href=\$dirkonf/>\$thekonf</a>] [<a href=\$dirkonf/\$faq>Правила</a>] <p>\$separator<P><h3>Отправление ответа \$tokonf на сообщение <br>&#171;\$subj&#187;</h3> <P>\$separator<P><div align=left>";
$endansform="</body></html>";
$begindex="<html><meta http-equiv=\"pragma\" content=\"no-cache\"><title>\$thekonf</title><body bgcolor=\"\$indbgcolor\" text=\"\$indtcolor\" link=\"\$indlcolor\" vlink=\"\$indvlcolor\" alink=\"\$indalcolor\" background=\"\$indimg\"><center><h2>\$thekonf</h2> <p>\$separator<p><!--#include virtual=\"\$dircgi/wtbservice.cgi?fid=\$fid&ins=news\"-->[<a href=\"\$dircgi/wtboard.cgi?root=on&fid=\$fid\">Написать сообщение</a>] [<a href=\$dirkonf/\$servname>Сервис</a>] [<a href=\$dirkonf/\$archive>Архивы</a>] [<a href=\$dirkonf/\$faq>Правила</a>]<P>\$separator<p></center><div align=left>";
$endindex="<!--end--></ul></ul></ul></ul></ul></ul></ul><P><center>\$separator<p>[<a href=\"\$dircgi/wtboard.cgi?root=on&fid=\$fid\">Написать сообщение</a>] [<a href=\$dirkonf/\$servname>Сервис</a>] [<a href=\$dirkonf/\$archive>Архивы</a>] [<a href=\$dirkonf/\$faq>Правила</a>]<P></center>\$separator<p><div align=left><font size=\"-1\"><i>&copy; 2000, \$thekonf<br>&copy; 1998-2000, <a href=http://wtiger.ncport.ru>White Tiger</a></I></body></html>";
$begarchive="<html><title>Архив \$ofkonf</title><body bgcolor=\"\$indbgcolor\" text=\"\$indtcolor\" link=\"\$indlcolor\" vlink=\"\$indvlcolor\" alink=\"\$indalcolor\" background=\"\$indimg\"><center><h1>Архив \$ofkonf</h1> <P>\$separator<p>[<a href=\$dirkonf/>\$thekonf</a>] [<a href=\$dirkonf/\$servname>Сервис</a>] [<a href=\$dirkonf/\$archive>Архивы</a>] [<a href=\$dirkonf/\$faq>Правила</a>]<P>\$separator<p></center><div align=left>";
$endarchive="<P><center>\$separator<p>[<a href=\$dirkonf/>\$thekonf</a>] [<a href=\$dirkonf/\$servname>Сервис</a>] [<a href=\$dirkonf/\$archive>Архивы</a>] [<a href=\$dirkonf/\$faq>Правила</a>]<P></center>\$separator<p><div align=left><font size=\"-1\"><i>&copy; 2000, \$thekonf<br>&copy; 1998-2000, <a href=http://wtiger.ncport.ru>White Tiger</a></i></body></html>";
$begmes="<html><meta http-equiv=\"pragma\" content=\"no-cache\"><title>\$subj</title><body bgcolor=\"\$mesbgcolor\" text=\"\$mestcolor\" link=\"\$meslcolor\" vlink=\"\$mesvlcolor\" alink=\"\$mesalcolor\" background=\"\$mesimg\"><center><h2><a name=top>\$subj</a></h2> <p>\$separator<p>[<a href=\$dirkonf/>\$thekonf</a>] [<a href=#ans>Ответы и комментарии</a>] [<a href=\"\$dircgi/wtboard.cgi?\$command\">Написать ответ</a>]</center><p>\$separator<p><div align=left>";
$endmes="<center>\$separator<p>[<a href=\$dirkonf/>\$thekonf</a>] [<a href=#top>Начало</a>] [<a href=\"\$dircgi/wtboard.cgi?\$command\">Написать ответ</a>]<p></body></html>";
$searchmes='';
$about='';
$statistics='';
$contexthelp='';
$setnewsstring='';
$regstring='';
$regtext='';
$warntext='';
$begsettings='';
$endsettings='';
$savedsettings='';
$newmesanstext='';
$newmestext='';
$newanstext='';
$privatebegin='';
$addedbegin='';
$existbegin='';
$wrnpasstext='';
$nopasstext='';
$nonametext='';
$nosubjtext='';
$prevmodetext='';
$prevbuttontext='';
$resetbuttontext='';
$readonlybegin='';
$noaccessbegin='';
$delmesbegin='';

$externalcall0='';
$externalcall1='';
$externalcall2='';
$externalcall3='';
$externalcall4='';
$externalcall5='';
$externalcall6='';
$externalcall7='';
$externalcall8='';
$externalcall9='';

open DAT,"$data/$wtboard";@ini=<DAT>;close DAT;
chomp @ini;
for$i(0..$#ini)
{	($a,$b)=split(/=/,$ini[$i],2);

	if($a eq 'thekonf'){$thekonf=$b;}
	elsif($a eq 'registration'){$registration=$b;}
	elsif($a eq 'tokonf'){$tokonf=$b;}
	elsif($a eq 'ofkonf'){$ofkonf=$b;}
	elsif($a eq 'onkonf'){$onkonf=$b;}
	elsif($a eq 'admin'){$admin=$b;}
	elsif($a eq 'private'){$private=$b;}
	elsif($a eq 'dirkonf'){$dirkonf=$b;}
	elsif($a eq 'dirrealkonf'){$dirrealkonf=$b;}
	elsif($a eq 'dircgi'){$dircgi=$b;}
	elsif($a eq 'realpath'){$realpath=$b;}
	elsif($a eq 'quote'){$quote=$b;}
	elsif($a eq 'quotebeg'){$quotebeg=$b;}
	elsif($a eq 'quoteend'){$quoteend=$b;}
	elsif($a eq 'substip'){$substip=$b;}
	elsif($a eq 'addip'){$addip=$b;}
	elsif($a eq 'notag'){$notag=$b;}
	elsif($a eq 'usecookie'){$usecookie=$b;}
	elsif($a eq 'quoting'){$quoting=$b;}
	elsif($a eq 'individual'){$individual=$b;}
	elsif($a eq 'includeform'){$includeform=$b;}
	elsif($a eq 'ext'){$ext=$b;}
	elsif($a eq 'reply'){$reply=$b;}
	elsif($a eq 'paragraph'){$paragraph=$b;}
	elsif($a eq 'endparagraph'){$endparagraph=$b;}
	elsif($a eq 'hr'){$separator=$b;}
	elsif($a eq 'separator'){$separator=$b;}
	elsif($a eq 'selectnew'){$selectnew=$b;}
	elsif($a eq 'selecttag'){$selecttag=$b;}
	elsif($a eq 'nulcolor'){$nulcolor=$b;}
	elsif($a eq 'selectnul'){$selectnul=$b;if($selectnul eq 'on'){$selectnul=2}elsif($selectnul eq 'off'){$selectnul=1}}
	elsif($a eq 'months'){$months=$b;}
	elsif($a eq 'days'){$days=$b;}
	elsif($a eq 'allowedtags'){$allowedtags=$b;}
	elsif($a eq 'timeshift'){$timeshift=$b;}
	elsif($a eq 'smiles'){$smiles=$b;}
	elsif($a eq 'allrestrict'){$allrestrict=$b;}
	elsif($a eq 'codepage'){$codepage=$b;}
	elsif($a eq 'info'){$info=$b;}
	elsif($a eq 'userstat'){$userstat=$b;}
	elsif($a eq 'ipuserstat'){$ipuserstat=$b;}
	elsif($a eq 'ignorstat'){$ignorstat=$b;}
	elsif($a eq 'dirarc'){$dirarc=$b;}
	elsif($a eq 'method'){$method=$b;}
	elsif($a eq 'timelimit'){$timelimit=$b;}
	elsif($a eq 'meslimit'){$meslimit=$b;}
	elsif($a eq 'indexarc'){$indexarc=$b;}
	elsif($a eq 'interval'){$intervaltype=$b;}
	elsif($a eq 'intervaltype'){$intervaltype=$b;}
	elsif($a eq 'setnewsarc'){$setnewsarc=$b;}
	elsif($a eq 'answerlabel'){$answerlabel=$b;}
	elsif($a eq 'arclabel'){$arclabel=$b;}
	elsif($a eq 'filter'){$filter=$b;}
	elsif($a eq 'filterwords'){$filterwords=$b;}
	elsif($a eq 'indname'){$indname=$b;}
	elsif($a eq 'verifydbl'){$verifydbl=$b;}
	elsif($a eq 'servname'){$service=$b;}
	elsif($a eq 'service'){$service=$b;}
	elsif($a eq 'maxshowsubj'){$maxshowsubj=$b;}
	elsif($a eq 'wrnpassbeg'){$wrnpassbeg=$b;}
	elsif($a eq 'wrnpassend'){$wrnpassend=$b;}
	elsif($a eq 'passstyle'){$passstyle=$b;}
	elsif($a eq 'imgexts'){$imgexts=$b;}
	elsif($a eq 'begbody'){$begbody=$b;}
	elsif($a eq 'endbody'){$endbody=$b;}
	elsif($a eq 'showsuccess'){$showsuccess=$b;}
	elsif($a eq 'replacedeleted'){$replacedeleted=$b;}
	elsif($a eq 'treestyle'){$treestyle=$b;}
	elsif($a eq 'movenewtop'){$movenewtop=$b;}
	elsif($a eq 'mestimeout'){$mestimeout=$b;}
	elsif($a eq 'externalcalls'){$externalcalls=$b;}
	elsif($a eq 'externalcall0'){$externalcall0=$b;}
	elsif($a eq 'externalcall1'){$externalcall1=$b;}
	elsif($a eq 'externalcall2'){$externalcall2=$b;}
	elsif($a eq 'externalcall3'){$externalcall3=$b;}
	elsif($a eq 'externalcall4'){$externalcall4=$b;}
	elsif($a eq 'externalcall5'){$externalcall5=$b;}
	elsif($a eq 'externalcall6'){$externalcall6=$b;}
	elsif($a eq 'externalcall7'){$externalcall7=$b;}
	elsif($a eq 'externalcall8'){$externalcall8=$b;}
	elsif($a eq 'externalcall9'){$externalcall9=$b;}
	elsif($a eq 'overdefine'){$overdefine=$b;}
	elsif($a eq 'preview'){$preview=$b;}
	elsif($a eq 'resetbutton'){$resetbutton=$b;}
	elsif($a eq 'quotesize'){$quotesize=$b;}
	elsif($a eq 'filearc'){$archive=$b;}
	elsif($a eq 'archive'){$archive=$b;}
	elsif($a eq 'sethtaccess'){$sethtaccess=$b;}
	elsif($a eq 'selftimeout'){$selftimeout=$b;}
	elsif($a eq 'contextreplace'){$contextreplace=$b;}
	elsif($a eq 'copyright'){$copyright=$b;}
	elsif($a eq 'arctimeout'){$arctimeout=$b;}
	elsif($a eq 'statdays'){$statdays=$b;}
	elsif($a eq 'setnroot'){$setnroot=$b;}
	elsif($a eq 'faq'){$faq=$b;}
	elsif($a eq 'expirescookie'){$expirescookie=$b;}
	elsif($a eq 'allowroot'){$allowroot=$b;}
	elsif($a eq 'advisenew'){$advisenew=$b;}
	elsif($a eq 'adviseans'){$adviseans=$b;}
	elsif($a eq 'lenlogin'){$lenlogin=$b;}
	elsif($a eq 'lenpass'){$lenpass=$b;}
	elsif($a eq 'lenemailmes'){$lenemailmes=$b;}
	elsif($a eq 'lenemailans'){$lenemailans=$b;}
	elsif($a eq 'lensubj'){$lensubj=$b;}
	elsif($a eq 'lenrows'){$lenrows=$b;}
	elsif($a eq 'lencols'){$lencols=$b;}
	elsif($a eq 'lenurl'){$lenurl=$b;}
	elsif($a eq 'lentitleurl'){$lentitleurl=$b;}
	elsif($a eq 'lenimg'){$lenimg=$b;}
	elsif($a eq 'seturl'){$seturl=$b;}
	elsif($a eq 'setimg'){$setimg=$b;}
	elsif($a eq 'maxsubj'){$maxsubj=$b;}
	elsif($a eq 'maxurl'){$maxurl=$b;}
	elsif($a eq 'indbgcolor'){$indbgcolor=$b;}
	elsif($a eq 'indtcolor'){$indtcolor=$b;}
	elsif($a eq 'indlcolor'){$indlcolor=$b;}
	elsif($a eq 'indvlcolor'){$indvlcolor=$b;}
	elsif($a eq 'indalcolor'){$indalcolor=$b;}
	elsif($a eq 'indimg'){$indimg=$b;}
	elsif($a eq 'mesbgcolor'){$mesbgcolor=$b;}
	elsif($a eq 'mestcolor'){$mestcolor=$b;}
	elsif($a eq 'meslcolor'){$meslcolor=$b;}
	elsif($a eq 'mesvlcolor'){$mesvlcolor=$b;}
	elsif($a eq 'mesalcolor'){$mesalcolor=$b;}
	elsif($a eq 'mesimg'){$mesimg=$b;}
	elsif($a eq 'errbgcolor'){$errbgcolor=$b;}
	elsif($a eq 'errtcolor'){$errtcolor=$b;}
	elsif($a eq 'errlcolor'){$errlcolor=$b;}
	elsif($a eq 'errvlcolor'){$errvlcolor=$b;}
	elsif($a eq 'erralcolor'){$erralcolor=$b;}
	elsif($a eq 'errimg'){$errimg=$b;}
	elsif($a eq 'string'){$string=$b;}
	elsif($a eq 'begmesform'){$begmesform=$b;}
	elsif($a eq 'endmesform'){$endmesform=$b;}
	elsif($a eq 'begansform'){$begansform=$b;}
	elsif($a eq 'endansform'){$endansform=$b;}
	elsif($a eq 'begarchive'){$begarchive=$b;}
	elsif($a eq 'endarchive'){$endarchive=$b;}
	elsif($a eq 'begmes'){$begmes=$b;}
	elsif($a eq 'endmes'){$endmes=$b;}
	elsif($a eq 'begindex'){$begindex=$b;}
	elsif($a eq 'endindex'){$endindex=$b;}
	elsif($a eq 'regstring'){$regstring=$b;}
	elsif($a eq 'setnewsstring'){$setnewsstring=$b;}
	elsif($a eq 'string'){$string=$b;}
	elsif($a eq 'searchmes'){$searchmes=$b;}
	elsif($a eq 'about'){$about=$b;}
	elsif($a eq 'statistics'){$statistics=$b;}
	elsif($a eq 'contexthelp'){$contexthelp=$b;}
	elsif($a eq 'regtext'){$regtext=$b;}
	elsif($a eq 'warntext'){$warntext=$b;}
	elsif($a eq 'begsettings'){$begsettings=$b;}
	elsif($a eq 'endsettings'){$endsettings=$b;}
	elsif($a eq 'savedsettings'){$savedsettings=$b;}
	elsif($a eq 'newmesanstext'){$newmesanstext=$b;}
	elsif($a eq 'newmestext'){$newmestext=$b;}
	elsif($a eq 'newanstext'){$newanstext=$b;}
	elsif($a eq 'privatebegin'){$privatebegin=$b;}
	elsif($a eq 'addedbegin'){$addedbegin=$b;}
	elsif($a eq 'existbegin'){$existbegin=$b;}
	elsif($a eq 'wrnpasstext'){$wrnpasstext=$b;}
	elsif($a eq 'nopasstext'){$nopasstext=$b;}
	elsif($a eq 'nonametext'){$nonametext=$b;}
	elsif($a eq 'nosubjtext'){$nosubjtext=$b;}
	elsif($a eq 'prevmodetext'){$prevmodetext=$b;}
	elsif($a eq 'prevbuttontext'){$prevbuttontext=$b;}
	elsif($a eq 'resetbuttontext'){$resetbuttontext=$b;}
	elsif($a eq 'readonlybegin'){$readonlybegin=$b;}
	elsif($a eq 'noaccessbegin'){$noaccessbegin=$b;}
	elsif($a eq 'delmesbegin'){$delmesbegin=$b;}
	elsif(index($a,'[')==0){$b=$b;}
	elsif(index($a,';')==0){$b=$b;}
	elsif(index($a,'; White Tiger WWW Board ini-file')>=0){$b=$b;}
# исключаемые параметры
	elsif($a eq 'setsize'){$s=0}
	elsif($a eq 'aboutsoft'){$s=0}
	elsif($a eq '; пример 1	string'){$s=0;}
	elsif($a eq '; пример 2	string'){$s=0;}
	elsif($a eq 'converturl'){$s=0;}
	elsif($a eq 'convertmail'){$s=0;}
	elsif($a eq 'convertselect'){$s=0;}
	elsif($a eq 'timescan'){$s=0;}
	else{next}
	undef$ini[$i];
}

print "<b>fid</b>=$id<br>\n<b>thekonf</b>=$thekonf<br>\n";

rename "$data/$wtboard","$data/$wtboard.old";
open DAT,"+>$data/$wtboard";

print DAT "; White Tiger WWW Board ini-file ($version)\n\n[Board Options]
registration=$registration
thekonf=$thekonf
tokonf=$tokonf
ofkonf=$ofkonf
onkonf=$onkonf
admin=$admin
private=$private
dirkonf=$dirkonf
dirrealkonf=$dirrealkonf
dircgi=$dircgi
realpath=$realpath
quote=$quote
quotebeg=$quotebeg
quoteend=$quoteend
substip=$substip
addip=$addip
notag=$notag
usecookie=$usecookie
quoting=$quoting
individual=$individual
includeform=$includeform
ext=$ext
reply=$reply
paragraph=$paragraph
endparagraph=$endparagraph
separator=$separator
selectnew=$selectnew
selecttag=$selecttag
nulcolor=$nulcolor
selectnul=$selectnul
string=$string
months=$months
days=$days
allowedtags=$allowedtags
timeshift=$timeshift
smiles=$smiles
allrestrict=$allrestrict
codepage=$codepage
answerlabel=$answerlabel
arclabel=$arclabel
filter=$filter
filterwords=$filterwords
indname=$indname
verifydbl=$verifydbl
service=$service
maxshowsubj=$maxshowsubj
wrnpassbeg=$wrnpassbeg
wrnpassend=$wrnpassend
passstyle=$passstyle
externalcalls=$externalcalls
overdefine=$overdefine
preview=$preview
resetbutton=$resetbutton
quotesize=$quotesize
imgexts=$imgexts
begbody=$begbody
endbody=$endbody
showsuccess=$showsuccess
selftimeout=$selftimeout
contextreplace=$contextreplace
copyright=$copyright
allowroot=$allowroot
setnroot=$setnroot
faq=$faq
expirescookie=$expirescookie
replacedeleted=$replacedeleted
treestyle=$treestyle
movenewtop=$movenewtop
mestimeout=$mestimeout

[Archive Options]
timelimit=$timelimit
meslimit=$meslimit
method=$method
dirarc=$dirarc
indexarc=$indexarc
intervaltype=$intervaltype
setnewsarc=$setnewsarc
archive=$archive
sethtaccess=$sethtaccess
arctimeout=$arctimeout

[Service Options]
info=$info
userstat=$userstat
ipuserstat=$ipuserstat
ignorstat=$ignorstat
advisenew=$advisenew
adviseans=$adviseans
statdays=$statdays

[Form Options]
lenlogin=$lenlogin
lenpass=$lenpass
lenemailmes=$lenemailmes
lenemailans=$lenemailans
lensubj=$lensubj
lenrows=$lenrows
lencols=$lencols
lenurl=$lenurl
lentitleurl=$lentitleurl
lenimg=$lenimg
seturl=$seturl
maxsubj=$maxsubj
maxurl=$maxurl
setimg=$setimg

[Board Colors]
indbgcolor=$indbgcolor
indtcolor=$indtcolor
indlcolor=$indlcolor
indvlcolor=$indvlcolor
indalcolor=$indalcolor
indimg=$indimg
mesbgcolor=$mesbgcolor
mestcolor=$mestcolor
meslcolor=$meslcolor
mesvlcolor=$mesvlcolor
mesalcolor=$mesalcolor
mesimg=$mesimg
errbgcolor=$errbgcolor
errtcolor=$errtcolor
errlcolor=$errlcolor
errvlcolor=$errvlcolor
erralcolor=$erralcolor
errimg=$errimg

[Board Strings]
begmesform=$begmesform
endmesform=$endmesform
begansform=$begansform
endansform=$endansform
begindex=$begindex
endindex=$endindex
begarchive=$begarchive
endarchive=$endarchive
begmes=$begmes
endmes=$endmes
searchmes=$searchmes
about=$about
statistics=$statistics
contexthelp=$contexthelp
setnewsstring=$setnewsstring
regstring=$regstring
regtext=$regtext
warntext=$warntext
begsettings=$begsettings
endsettings=$endsettings
savedsettings=$savedsettings
newmesanstext=$newmesanstext
newmestext=$newmestext
newanstext=$newanstext
privatebegin=$privatebegin
addedbegin=$addedbegin
existbegin=$existbegin
wrnpasstext=$wrnpasstext
nopasstext=$nopasstext
nonametext=$nonametext
nosubjtext=$nosubjtext
prevmodetext=$prevmodetext
prevbuttontext=$prevbuttontext
resetbuttontext=$resetbuttontext
readonlybegin=$readonlybegin
noaccessbegin=$noaccessbegin
delmesbegin=$delmesbegin

[External Calls]
externalcall0=$externalcall0
externalcall1=$externalcall1
externalcall2=$externalcall2
externalcall3=$externalcall3
externalcall4=$externalcall4
externalcall5=$externalcall5
externalcall6=$externalcall6
externalcall7=$externalcall7
externalcall8=$externalcall8
externalcall9=$externalcall9

[Plugin Options]\n";

for$i(0..@ini)
{	if(length $ini[$i]>0){print DAT "$ini[$i]\n"}
}
$s=0;$i=(close DAT);if(!$i){print "&gt;&gt; update of ini-file failed<br>\n";$s=1;}

if(-z "$data/$wtboard"==1){print "&gt;&gt; ini-file has zero data, restored from $wtboard.old<br>\n";rename "$data/$wtboard\.old","$data/$wtboard";$s=1;}

if(!$s){print "&gt;&gt; ini-file succesfully updated<br>\n"}


# обновление wtbadmin.htm
@a=<$dirrealkonf/*.htm>;

for(@a)
{	if(/wtbadmin/i)
	{

	open DAT,"+>$dirrealkonf/$_";
	print DAT "<html><title>Администрирование</title><body bgcolor=\"#c6e8d9\" text=\"#800000\" link=\"#000000\" vlink=\"#800000\" alink=\"#ffffff\" background=\"\"><br><center><h2>Администрирование форума</h2> <P><hr size=1 width=80%><p>

<form action=$dircgi/wtbedit.cgi method=post><p><table width=100%><tr><td colspan=4><center><b><i><font size=+1>Выберите тип изменений:</font>
</i></b></center><br>
<ul>
<li><b>Идентификатор форума</b> <input type=text name=fid value=\"$id\" size=10>
<li><b>Основные параметры</b>
<ul><input type=radio name=oper value=adminstatus>статус форума, администраторы, внешние вызовы и т. д. <sup><i>(a)</i>*</sup>
<br><input type=radio name=oper value=admininterface checked>шаблоны интерфейса форума <sup><i>(i)</i></sup>
<br><input type=radio name=oper value=adminform>форма сообщения <sup><i>(i)</i></sup>
<br><input type=radio name=oper value=adminmessage>обработка сообщения <sup><i>(i)</i></sup>
<br><input type=radio name=oper value=adminindex>основная страница <sup><i>(i)</i></sup>
<br><input type=radio name=oper value=adminuser>участники <sup><i>(i)</i></sup>
<br><input type=radio name=oper value=adminstat>статистика <sup><i>(i)</i></sup>
</ul>
<li><b>Редактирование</b>
<ul><input type=radio name=oper value=sedit>редактирование основной страницы и сообщений <sup><i>(e)</i></sup>
<br><input type=radio name=oper value=adminreplace>шаблоны контекстной замены <sup><i>(a)</i></sup>
</ul>
<li><b>Модерирование</b>
<ul>
<input type=radio name=oper value=modif>удаление сообщений по номерам <sup>** <i>(d)</i></sup>
<br><input type=radio name=oper value=modifsubj>удаление сообщений по темам <sup>** <i>(d)</i></sup>
<br><input type=radio name=oper value=modifuser>удаление сообщений по участникам <sup>** <i>(d)</i></sup>
<br><input type=radio name=oper value=ignor>изменение списка участников, игнор-лист <sup><i>(g)</i></sup>
<br><input type=radio name=oper value=wronglog>log-файл событий <sup><i>(i)</i></sup>
</ul>
<li><b>Параметры самообслуживания</b>
<ul>
<input type=radio name=oper value=selfservice>сервис самообслуживания форума <sup><i>(degs)</i></sup>
<br><input type=radio name=oper value=arhiv>архивация форума и установки автоархивации <sup>** <i>(h)</i></sup>
<br><input type=radio name=oper value=selfmoder>параметры автомодерирования <sup><i>(dg)</i></sup>
<br><input type=radio name=oper value=restore>сервис восстановления Index <sup>** <i>(s)</i></sup>
</ul>
<li><b>Прочие операции</b>
<ul><input type=radio name=oper value=news>операции с новостными строками <sup><i>(n)</i></sup>
<br><input type=radio name=oper value=specarc>произвольная архивация <sup><i>(a)</i></sup>
<br><input type=radio name=oper value=plugin>конфигурация модулей <sup><i>(a)</i></sup>
</ul>
</ul>
</td></tr><tr><td><p>&nbsp;</p></td></tr><tr><td width=10%><div align=right>Имя:</td><td width=30%><input type=text name=login size=20></td>
<td width=20%><div align=right>Пароль:</td><td width=30%><input type=password name=pass size=20></td></tr><tr><td><p>&nbsp;</p></td></tr><tr><td colspan=4><center><input type=submit value=Послать><input type=reset value=Сброс></td></tr></table></form>
<div align=left><font size=-1>
<sup>*</sup> <i>&#151; в скобках указаны минимально необходимые права администратора для доступа к разделу.</i><br>
<sup>**</sup> <i>&#151; операции данного раздела производятся с индексной страницей форума.</i><br>
<i>Для очищения значения текстового поля укажите величину &#171;<b>n/a</b>&#187;.</i></font></div>
<P><hr size=1 width=80%><p><div align=left><font size=-1><i>&#169; 1998-2000,
<a href=http://wtiger.ncport.ru>White Tiger</a></I><br></body></html>";

	if(!(close DAT)){print "&gt;&gt; update of wtbadmin.htm failed<br>\n"}
	else{print "&gt;&gt; wtbadmin.htm updated<br>\n"}
	last;
	}
}

use SDBM_File;	# задание типа базы данных

# конвертация wtbnames.txt
if(-e "$data/$wtbnames.pag"){print "<hr size=1><p>\n";next}
if(!(dbmopen(%wtbuser,"$data/$wtbnames",0644))){print "&gt;&gt; cannot create user base<br>\n";next}
open NAM,"$data/$wtbnames";
$ss=0;while(<NAM>)
{	chomp;
	($names,$pwd,$mails,$realn,$ipaddr,$pars,$utimes,$s)=split(';;');
	$wtbuser{"id_$names"}=$names;
	$wtbuser{"w_$names"}=$pwd;
	$wtbuser{"m_$names"}=$mails;
	$wtbuser{"n_$names"}=$realn;
	$wtbuser{"h_$names"}=$ipaddr;
	$wtbuser{"u_${id}_$names"}=$pars;
	$wtbuser{"t_${id}_$names"}=$utimes;
	++$ss;
}
close NAM;

open NAM,"$data/$wtbaccess";
delete$wtbuser{'ignor_ip'};delete$wtbuser{'stop_ip'};
$st=0;while(<NAM>)
{	chomp;
	($names,$lng1,$lng2,$s)=split(';;');
	$names=~s/^([\-!])//;$s=$1;
	if($names=~/\./)	# это ip-адрес
	{	if($s eq '-'){$wtbuser{'ignor_ip'}.=";$names"}
         	if($s eq '!'){$wtbuser{'stop_ip'}.=";$names"}
	}
	else			# это cookie
	{	$wtbuser{"i_$names"}=$s;
		$wtbuser{"it_$names"}=$lng1;
		$wtbuser{"ib_$names"}=$lng2;
	}
	++$st;
}
close NAM;


dbmclose%wtbuser;
if((-s "$data/$wtbnames.pag")>0){print "&gt;&gt; user base converted, $ss user(s), $st ignor(s)<br>\n<hr size=1><p>\n"}
else{print "&gt;&gt; user base convertation failed<br>\n<hr size=1><p>\n"}


}

print "Обновление форумов завершено. На всякий случай проверьте их содержимое. Не забудьте также произвести изменения других файлов, связанных с форумами, которые необходимы для нормального перехода на новую версию скриптов.</body></html>";

exit;

