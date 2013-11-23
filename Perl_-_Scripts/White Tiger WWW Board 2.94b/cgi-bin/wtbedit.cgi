#!/usr/bin/perl

# White Tiger WWW Board ver.2.936b
# система wwwboard. Разработка, реализация
# (C) 1998-2000, White Tiger (2:5049/91.38; 
# email:wtiger@mail.ru; http://wtiger.ncport.ru)
# wtbedit.cgi - модуль администрирования форума
# wtbedit.cgi - administration module

# замена переменных производится в файле wtbext.cgi
# you must change values in the wtbext.cgi















# прочие величины
if(!-e"wtbext.cgi"){print "\nError: not found wtbext.cgi";exit}
require "wtbext.cgi";
params(2);


$ended="<p><center>[<a href=$inip{'dirkonf'}/>$thekonf</a>] [<a href=$inip{'dirkonf'}/wtbadmin.htm>$lng[206] $thekonf</a>]<p></body></html>";

if(verifyadmin($inip{'login'},$inip{'pass'})<0)
{	print "<html><title>$lng[186]</title><body>$lng[48]</body></html>";
	savewrong('BDADM',$login,$pass);
	exit;
}


open DAT,"$data/$wtboard";@ini=<DAT>;close DAT;chomp@ini;
$s=0;$j=0;for(@ini)
{	if(/^\[/ or !length or /^;/){next}
	s/&/&amp;/g;
	s/\"/&quot;/g;
	s/<!>/$cl/g;
	s/</&lt;/g;
	s/>/&gt;/g;
	($a,$b)=split('=',$_,2);if(length$b){$inis{$a}=$b}
}
@inis=keys%inis;
for(@inis)
{	$a=$inis{$_};
	$a=~s/\'/\\\'/g;
	$a="\$$_='$inis{$_}';";
	eval$a;
}


if($oper eq 'admin'){print "\n\nPlease update your wtbadmin.htm file.";exit}
elsif($oper eq 'adminstatus'){goto ADMINSTATUS}
elsif($oper eq 'admininterface'){goto ADMININTERFACE}
elsif($oper eq 'adminform'){goto ADMINFORM}
elsif($oper eq 'adminmessage'){goto ADMINMESSAGE}
elsif($oper eq 'adminindex'){goto ADMININDEX}
elsif($oper eq 'adminuser'){goto ADMINUSER}
elsif($oper eq 'adminstat'){goto ADMINSTAT}
elsif($oper eq 'adminreplace'){goto ADMINREPLACE}
elsif($oper eq 'modif'){goto MODIF}
elsif($oper eq 'modifuser'){goto MODIFUSER}
elsif($oper eq 'modifsubj'){goto MODIFSUBJ}
elsif($oper eq 'selfservice'){goto SELFSERVICE}
elsif($oper eq 'arhiv'){goto ARHIV}
elsif($oper eq 'ignor'){goto IGNOR}
elsif($oper eq 'news'){goto NEWS}
elsif($oper eq 'sedit'){goto SEDIT}
elsif($oper eq 'seditx'){goto SEDITX}
elsif($oper eq 'seditf'){goto SEDITF}
elsif($oper eq 'restore'){goto RESTORE}
elsif($oper eq 'wronglog'){goto WRONGLOG}
elsif($oper eq 'specarc'){goto SPECARC}
elsif($oper eq 'plugin'){goto PLUGIN}
elsif($oper eq 'submit'){goto SUBMIT}
else{goto ERROR}

#optonoff('parameter',$title,$desc)
#optfield('parameter',$title,$desc)
#optselect('parameter',$title,$desc,$nvalues,$values,$descs)


### статус форума, администраторы, внешние вызовы и т.д.
ADMINSTATUS:

if(index($stat,'a')<0){print "<html><title>$lng[186]</title><body>$lng[48]</body></html>";exit;}
titleadmin($lng[488],$login,$stat);
print "<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100% border=0>
<tr><td colspan=6><font size=\"+1\"><center>$lng[65]<br><br>$dr";

optfield('registration',@lng[665,666]);
opt2field('thekonf',$lng[66],'tokonf',$lng[67],'',18,15);
opt2field('ofkonf',$lng[208],'onkonf',$lng[68],'',18,15);

open NAM,"$data/$wtbadmin";$i=0;while(<NAM>){($anam[$i],$apwd[$i],$astat[$i],$s)=split(';;');++$i;}close NAM;
$anam=join(chr(0x0D),@anam);$apwd=join(chr(0x0D),@apwd);$astat=join(chr(0x0D),@astat);
$rows=$#anam+2;

print"<tr>$cs6&nbsp;<p>$dr
<tr><td colspan=3>$lng[69]<br><textarea name=anam cols=35 rows=$rows>$anam</textarea></td>
<td colspan=2>$lng[70]<br><textarea name=apwd cols=20 rows=$rows>$apwd</textarea></td>
<td>$lng[71]<br><textarea name=astat cols=10 rows=$rows>$astat</textarea>$dr
<tr>$cs6$lng[72] &nbsp;<p>$dr";

optfield('admin',$lng[77],$lng[78]);
optselect('private',$lng[73],$lng[76],2,'private','noprivate',@lng[74..75]);
optselect('passstyle',$lng[553],$lng[554],3,0,1,2,@lng[555..557]);
opt2field('wrnpassbeg',$lng[558],'wrnpassend',$lng[559],$lng[560],15,15);
optonoff('overdefine',$lng[511],$lng[512]);
optonoff('externalcalls',$lng[513],$lng[514]);
optfield('externalcall0',$lng[515],$lng[516]);
optfield('externalcall1',$lng[517],$lng[518]);
optfield('externalcall2',$lng[519],$lng[520]);
optfield('externalcall3',$lng[521],$lng[522]);
optfield('externalcall4',$lng[523],$lng[524]);
optfield('externalcall5',$lng[525],$lng[526]);
optfield('externalcall6',$lng[527],$lng[528]);
optfield('externalcall7',$lng[529],$lng[530]);
optfield('externalcall8',$lng[531],$lng[532]);
optfield('externalcall9',$lng[533],$lng[534]);
print "\n<tr>$cs6$lng[535] &nbsp;<p>$dr\n";
optfield('indname',$lng[459],$lng[460]);
optfield('service',$lng[485],$lng[486]);
optfield('faq',$lng[635],$lng[636]);
optselect('ext',$lng[269],$lng[270],5,@exts,'.htm','.html','.shtml','.stm','.asp');
optselect('codepage',$lng[419],$lng[420],4,'cp-1251','koi8-r','iso-8859-5','cp-866','Windows CP-1251','KOI-8','ISO 8859-5','DOS');
optfield10('timeshift',$lng[536],$lng[537]);
print "</table><p><center>$hr<p>";
optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form><p></body></html>";

exit;


### шаблоны интерфейса форума
ADMININTERFACE:

if(index($stat,'i')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body>$lng[116]</body></html>";exit;}
titleadmin($lng[579],$login,$stat);                               
print "<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100%>";

optfield('begbody',$lng[571],$lng[572]);
optfield('endbody',$lng[573],$lng[574]);
optfield('separator',$lng[289],$lng[290]);

print"<tr><td colspan=6><font size=\"+1\"><center><b><i>$lng[94]</i></b>$dr
<tr><td colspan=6>$lng[95]$dr
<tr><td colspan=6><i><center><font size=\"+1\"><b>$lng[96]$dr
$rd<center>$lng[97]</td><td colspan=3><center>$lng[103]</td><td colspan=2><center>$lng[104]$dr
$rd$lng[98]</td>$cs3<textarea name=begindex cols=30 rows=3>$inis{'begindex'}</textarea></td>
<td colspan=2 align=center><textarea name=endindex cols=20 rows=3>$inis{'endindex'}</textarea>$dr
$rd$lng[99]</td>$cs3<textarea name=begarchive cols=30 rows=3>$inis{'begarchive'}</textarea></td>
<td colspan=2 align=center><textarea name=endarchive cols=20 rows=3>$inis{'endarchive'}</textarea>$dr
$rd$lng[100]</td>$cs3<textarea name=begmesform cols=30 rows=3>$inis{'begmesform'}</textarea></td>
<td colspan=2 align=center><textarea name=endmesform cols=20 rows=3>$inis{'endmesform'}</textarea>$dr
$rd$lng[101]</td>$cs3<textarea name=begansform cols=30 rows=3>$inis{'begansform'}</textarea></td>
<td colspan=2 align=center><textarea name=endansform cols=20 rows=3>$inis{'endansform'}</textarea>$dr
$rd$lng[102]</td>$cs3<textarea name=begmes cols=30 rows=3>$inis{'begmes'}</textarea></td>
<td colspan=2 align=center><textarea name=endmes cols=20 rows=3>$inis{'endmes'}</textarea>$dr

<tr><td colspan=6>&nbsp;<p><i><center><font size=\"+1\"><b><i>$lng[585]</i></b>$dr
$rd$lng[567]</td><td colspan=5 align=center><textarea name=searchmes cols=55 rows=3>$inis{'searchmes'}</textarea>$dr
$rd$lng[568]</td><td colspan=5 align=center><textarea name=about cols=55 rows=3>$inis{'about'}</textarea>$dr
$rd$lng[569]</td><td colspan=5 align=center><textarea name=statistics cols=55 rows=3>$inis{'statistics'}</textarea>$dr
$rd$lng[570]</td><td colspan=5 align=center><textarea name=contexthelp cols=55 rows=3>$inis{'contexthelp'}</textarea>$dr
$rd$lng[686]</td><td colspan=5 align=center><textarea name=privatebegin cols=55 rows=3>$inis{'privatebegin'}</textarea>$dr
$rd$lng[687]</td><td colspan=5 align=center><textarea name=addedbegin cols=55 rows=3>$inis{'addedbegin'}</textarea>$dr
$rd$lng[688]</td><td colspan=5 align=center><textarea name=existbegin cols=55 rows=3>$inis{'existbegin'}</textarea>$dr
$rd$lng[689]</td><td colspan=5 align=center><textarea name=readonlybegin cols=55 rows=3>$inis{'readonlybegin'}</textarea>$dr
$rd$lng[690]</td><td colspan=5 align=center><textarea name=noaccessbegin cols=55 rows=3>$inis{'noaccessbegin'}</textarea>$dr
<tr>$cs6$lng[105] $lng[106] $lng[107]\n";

optfield('begsettings',$lng[655]);
optfield('endsettings',$lng[656],$lng[657]);
optfield('savedsettings',$lng[659],$lng[660]);

print"<tr><td colspan=6><font size=\"+1\"><center><b><i>$lng[647]</i></b>$dr\n";
optfield('regtext',$lng[648],$lng[649]);
optfield('warntext',$lng[650],$lng[651]);
optfield('newmesanstext',$lng[661]);
optfield('newmestext',$lng[662]);
optfield('newanstext',@lng[663,664]);
optfield('wrnpasstext',$lng[677]);
optfield('nopasstext',$lng[678]);
optfield('nonametext',$lng[679]);
optfield('nosubjtext',@lng[680,681]);
optfield('prevmodetext',$lng[682]);
optfield('prevbuttontext',$lng[683]);
optfield('resetbuttontext',@lng[684,685]);

print "<tr><td colspan=6><center><font size=\"+1\"><b><i>$lng[108]</i></b>$dr
$rd<center>$lng[97]</td><td><center>$lng[98]</td><td><center>$lng[99]</td><td><center>$lng[100]</td><td><center>$lng[101]</td><td><center>$lng[102]$dr
$rd$lng[109]</td><td>$i1=text name=indbgcolor value=\"$inis{'indbgcolor'}\" size=9></td><td><center>&#151;</td><td>$i1=text name=errbgcolor value=\"$inis{'errbgcolor'}\" size=9></td><td><center>&#151;</td><td>$i1=text name=mesbgcolor value=\"$inis{'mesbgcolor'}\" size=9>$dr
$rd$lng[110]</td><td>$i1=text name=indtcolor value=\"$inis{'indtcolor'}\" size=9></td><td><center>&#151;</td><td>$i1=text name=errtcolor value=\"$inis{'errtcolor'}\" size=9></td><td><center>&#151;</td><td>$i1=text name=mestcolor value=\"$inis{'mestcolor'}\" size=9>$dr
$rd$lng[111]</td><td>$i1=text name=indlcolor value=\"$inis{'indlcolor'}\" size=9></td><td><center>&#151;</td><td>$i1=text name=errlcolor value=\"$inis{'errlcolor'}\" size=9></td><td><center>&#151;</td><td>$i1=text name=meslcolor value=\"$inis{'meslcolor'}\" size=9>$dr
$rd$lng[112]</td><td>$i1=text name=indvlcolor value=\"$inis{'indvlcolor'}\" size=9></td><td><center>&#151;</td><td>$i1=text name=errvlcolor value=\"$inis{'errvlcolor'}\" size=9></td><td><center>&#151;</td><td>$i1=text name=mesvlcolor value=\"$inis{'mesvlcolor'}\" size=9>$dr
$rd$lng[113]</td><td>$i1=text name=indalcolor value=\"$inis{'indalcolor'}\" size=9></td><td><center>&#151;</td><td>$i1=text name=erralcolor value=\"$inis{'erralcolor'}\" size=9></td><td><center>&#151;</td><td>$i1=text name=mesalcolor value=\"$inis{'mesalcolor'}\" size=9>$dr
$rd$lng[114]</td><td>$i1=text name=indimg value=\"$inis{'indimg'}\" size=9></td><td><center>&#151;</td><td>$i1=text name=errimg value=\"$inis{'errimg'}\" size=9></td><td><center>&#151;</td><td>$i1=text name=mesimg value=\"$inis{'mesimg'}\" size=9>$dr
<tr>$cs6$lng[115]$dr";

print "</table><p><center>$hr<p>";
optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form><p></body></html>";

exit;


### форма сообщения
ADMINFORM:

if(index($stat,'i')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body>$lng[116]</body></html>";exit;}
titleadmin($lng[580],$login,$stat);
print "<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100%>";

opt2field('lenlogin',$lng[83],'lenpass',$lng[84]);
opt2field('lenemailmes',$lng[85],'lenemailans',$lng[86]);
opt2field('lensubj',$lng[87],'maxsubj',$lng[468]);
opt2field('lenrows',$lng[88],'lencols',$lng[89]);
opt2field('lenurl',$lng[90],'lentitleurl',$lng[91]);
opt2field('lenimg',$lng[92],'maxurl',$lng[469],$lng[93]);
optonoff('seturl',$lng[401],$lng[402]);
optonoff('setimg',$lng[563],$lng[564]);
optfield('imgexts',$lng[565],$lng[566]);
optonoff('preview',$lng[542],$lng[543]);
optonoff('resetbutton',$lng[544],$lng[545]);
optfield10('reply',$lng[271],$lng[272]);
optonoff('allowroot',$lng[632],$lng[633]);
optfield10('setnroot',$lng[618],$lng[619]);
optonoff('quoting',$lng[265],$lng[266]);
optfield('quote',$lng[79],$lng[80]);
optfield10('quotesize',$lng[546],$lng[547]);

print "</table><p><center>$hr<p>";
optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form><p></body></html>";

exit;


### обработка сообщения
ADMINMESSAGE:

if(index($stat,'i')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body>$lng[116]</body></html>";exit;}
titleadmin($lng[581],$login,$stat);
print "<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100%>";

opt2field('paragraph',$lng[273],'endparagraph',$lng[406],$lng[274]);
opt2field('quotebeg',$lng[293],'quoteend',$lng[294],$lng[295]);
optselect('notag',$lng[260],$lng[264],4,0,3,1,2,$lng[261],$lng[403],@lng[262..263]);
optfield('allowedtags',$lng[404],$lng[405]);
optselect('allrestrict',$lng[414],$lng[418],3,0,1,2,@lng[415..417]);
optonoff('includeform',$lng[478],$lng[479]);
optonoff('filter',$lng[452],$lng[453]);
optfield('filterwords',$lng[454],$lng[455]);
optselect('contextreplace',$lng[620],$lng[624],3,0,1,2,@lng[621..623]);
optonoff('smiles',$lng[411],$lng[412]);
optonoff('addip',$lng[211],$lng[212]);

print "</table><p><center>$hr<p>";
optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form><p></body></html>";

exit;


### основная страница
ADMININDEX:

if(index($stat,'i')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body>$lng[116]</body></html>";exit;}
titleadmin($lng[582],$login,$stat);
print "<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100% border=0>";

optfield('string',$lng[209],$lng[210]);
optfield('days',$lng[407],$lng[408]);
optfield('months',$lng[409],$lng[410]);
optfield10('answerlabel',$lng[445],$lng[446]);
optfield10('arclabel',$lng[447],$lng[448]);
optfield10('selectnew',$lng[275],$lng[276]);
optfield('selecttag',$lng[287],$lng[288]);

if($inis{'selectnul'}==0){$s1=' selected';$s2='';$s3=''}elsif($inis{'selectnul'}==1){$s1='';$s2=' selected';$s3=''}else{$s1='';$s2='';$s3=' selected'}
print "<tr>$cs2$lng[277]</td><td colspan=2><select name=selectnul><option value=0$s1>$lng[548]<option value=1$s2>$lng[549]<option value=2$s3>$lng[550]</select></td>\n$cs2$lng[278] $i1=text name=nulcolor value=\"$inis{'nulcolor'}\" size=10>$dr\n<tr>$cs6$lng[279] &nbsp;<p>$dr";

optselect('verifydbl',$lng[463],$lng[467],5,0,1,2,3,4,@lng[464..466],$lng[510],$lng[575]);
optfield10('maxshowsubj',$lng[496],$lng[497]);
optselect('treestyle',@lng[691,692],2,1,2,@lng[693..694]);
optonoff('movenewtop',@lng[695..696]);
optfield10('mestimeout',@lng[697..698]);

print "</table><p><center>$hr<p>";
optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form><p></body></html>";

exit;


### участники
ADMINUSER:

if(index($stat,'i')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body>$lng[116]</body></html>";exit;}
titleadmin($lng[583],$login,$stat);
print "<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100%>";

optonoff('usecookie',@lng[258,259]);
optfield('expirescookie',@lng[652,653]);
optonoff('substip',@lng[81,82]);
optonoff('individual',@lng[267,268]);
optselect('allrestrict',@lng[414,418],3,0,1,2,@lng[415..417]);
optselect('showsuccess',@lng[588,589],3,0,1,2,@lng[590..592]);
optonoff('advisenew',@lng[474,476]);
optonoff('adviseans',@lng[475,477]);

print "</table><p><center>$hr<p>";
optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form><p></body></html>";

exit;


### статистика
ADMINSTAT:

if(index($stat,'i')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body>$lng[116]</body></html>";exit;}
titleadmin($lng[584],$login,$stat);
print "<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100% border=0>";

optonoff('userstat',$lng[236],$lng[237]);
optonoff('ipuserstat',$lng[240],$lng[241]);
optonoff('ignorstat',$lng[238],$lng[239]);
optfield10('statdays',$lng[596]);
print "\n<tr><td colspan=6>&nbsp;<br><font size=\"+1\"><center><b>$lng[200]$dr
<tr><td colspan=6 align=center><textarea name=info cols=70 rows=10 wrap=virtual>$inis{'info'}</textarea>$dr
<tr>$cs6$lng[201] &nbsp;<p>$dr";

print "</table><p><center>$hr<p>";
optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form><p></body></html>";

exit;


### произвольная компрессия
SPECARC:

if(!$stat=~/a/){print "<html><title>$lng[186]</title><body>$lng[116]</body></html>";exit;}
titleadmin($lng[637],$login,$stat);
print "$lng[638]<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100% border=0>";

@saarcext=('','zip','rar');$inis{'specarcext'}='*.*htm*';$inis{'specarcmethod'}=1;$inis{'specarcdelfil'}='on';
$inis{'specarcsrcdir'}="$inis{'realpath'}/$inis{'dirarc'}";$inis{'specarcdestdir'}="$inis{'realpath'}/$inis{'dirarc'}";
map{$_=sprintf('%2.2d',$_)}@t[3,4];$inis{'specarcfile'}="index$t[3]$t[4]$t[5].$saarcext[$inis{'specarcmethod'}]";
optfield('specarcsrcdir',$lng[639]);
optfield('specarcext',$lng[644]);
optfield('specarcfile',$lng[640]);
optfield('specarcdestdir',$lng[641]);
optselect('specarcmethod',$lng[642],'',2,1,2,$lng[436],$lng[593]);
optonoff('specarcdelfil',$lng[643]);

print "</table><p><center>$hr<p>";
optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form><p></body></html>";

exit;

### конфигурация плагинов
PLUGIN:

if(!$stat=~/a/){print "<html><title>$lng[186]</title><body>$lng[48]</body></html>";exit;}
titleadmin($lng[699],$login,$stat);
print "<table width=100% border=0>
<tr><td colspan=6><font size=\"+1\"><center>$lng[65]<br><br>$dr";

@a=(<./*.cgi>,<./*.pl>);$counter=0;

NEXTET:for$n(@a)
{
	open NAM,$n;$n=~s/\.\///;
	$s=0;while(<NAM>)
	{	if($s){if(/admin\.operation/){$s=0};next}
		if(/admin\.requireversion=\{(.*?)\}/){if($1>$internalversion){$s=1;next}}
         	if(/admin\.skip=\{(.*?)\}/){if(defined$inip{$1}){$s=1;next}}
		if(/admin\.name=\{(.*?)\}/){print "<tr valign=middle><td colspan=5> <form action=\"$n\" method=post><input type=hidden name=fid value=\"$fid\">$1 ";++$counter}
		if(/admin\.version=\{(.*?)\}/){print "ver.$1 "}
		if(/admin\.description=\{(.*?)\}/){print "&#151; $1</td><td>"}
		if(/admin\.administrator=\{(.*?)\}/){print "<input type=hidden name=\"$1\" value=\"$login\">"}
		if(/admin\.password=\{(.*?)\}/){print "<input type=hidden name=\"$1\" value=\"$pass\">"}
		if(/admin\.operation=\{(.*?)\}/){print "<input type=hidden name=\"oper\" value=\"$1\"><input type=submit value=Go></form> </td></tr>\n"}
		if(/admin\.section end/){next NEXTET}
	}
}
if(!$counter){print "<tr><td colspan=6>$lng[700]</td></tr>"}

print "</table><p><center>$hr<p>";
#optsubmit($login,$pass,'pluginselect',$fid,$lng[8]);
print "<p></body></html>";


exit;




### игнор-лист
IGNOR:

if(index($stat,'g')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body>$lng[116]</body></html>";exit;}
titleadmin($lng[489],$login,$stat);
print "<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100%>
$rd<font size=\"+1\"><center><b>$lng[117]$dr";

$s=0;%a=%wtbuser;
while(($s1,$s2)=each%wtbuser){if($s1=~/^id_(.*)/){
$nam[$s]=$a{"id_$1"}.'|'.$a{"w_$1"}.'|'.$a{"m_$1"}.'|'.$a{"n_$1"}.'|'.$a{"h_$1"}.'|'.$a{"u_${fid}_$1"}.'|'.$a{"t_${fid}_$1"}.'|';++$s}}

@nam=sort@nam;
$nam=join(chr(0x0D),@nam);

print "$rd<center>$lng[118]<br><textarea name=names cols=70 rows=10>$nam</textarea></center>$dr
$rd<div align=left>$lng[122]</div>$dr
$rd<p>&nbsp;<p><center>$hr<p><p>&nbsp;<p>$dr
$rd<font size=\"+1\"><center><b>$lng[123]$dr</table>";

@s=keys%wtbuser;for(@s){if(/^i_(.*)/){if(!length$1){next}$inii.=$wtbuser{"i_$1"}."$1$crd";$init.=$wtbuser{"it_$1"}.$crd;$inim.=$wtbuser{"ib_$1"}.$crd}}
@s=split(';',$a{'ignor_ip'});for(@s){if(!length){next}$inii.='-'.$_.$crd;$init.='n/d'.$crd;$inim.='n/d'.$crd}
@s=split(';',$a{'stop_ip'});for(@s){if(!length){next}$inii.='!'.$_.$crd;$init.='n/d'.$crd;$inim.='n/d'.$crd}
for($inii,$init,$inim){s/$crd$//};

print "<table width=100%><tr><td colspan=2 align=center>$lng[215]</td><td align=center>$lng[216]</td><td colspan=2 align=center>$lng[217]$dr
<tr><td colspan=2 align=center><textarea name=ignor cols=22 rows=10>$inii</textarea></td>
<td align=center><textarea name=ignort cols=13 rows=10>$init</textarea></td>
<td colspan=2 align=center><textarea name=ignorm cols=25 rows=10>$inim</textarea>
$i1=hidden name=private value=$private>$dr
</table>
<div align=left>$lng[125]<center>$hr<p>";

optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form><p>$t<p><center><form action=$inip{'dircgi'}/wtbedit.cgi method=post>";
optsubmit($login,$pass,'wronglog',$fid,$lng[124]);
print "</form><p></body></html>";

exit;


ADMINREPLACE:

if(index($stat,'a')<0){print "<html><title>$lng[186]</title><body><h2>$lng[126]</h2></body></html>";exit;}
titleadmin("&#171;$lng[625]&#187;",$login,$stat);
print "<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100% border=0>";

optselect('contextreplace',$lng[620],$lng[624],3,0,1,2,@lng[621..623]);

print "<tr><td colspan=6><center><b>$lng[625]</b><br>&nbsp;</td></tr>
<tr><td>F</td><td>R U</td><td>D</td><td><center>$lng[627]</td><td><center><center>$lng[628]</td><td><center>$lng[629]$dr\n";

open NAM,"$data/$wtbreplace";
$i=0;while(<NAM>)
{	chomp;($s1,$s2)=split(';;');($s2,$s)=split(/\\\;\//,$s2);

	if(index($s1,';')==0){next}

	$s111=' selected';$s112='';$s113='';
	if(index($s1,'*')==0){$s1=~s/\*//;$s111=' selected'}
	elsif(index($s1,'@')==0){$s1=~s/\@//;$s111='';$s112=' selected'}
	elsif(index($s1,'#')==0){$s1=~s/#//;$s111='';$s113=' selected'}

	$s12='';if(index($s1,'%')==0){$s1=~s/%//;$s12=' checked'}

	$s13='';if(index($s1,'!')==0){$s1=~s/!//;$s13=' checked'}

	$s141=' selected';$s142='';$s143='';
	if(index($s1,'<')==0){$s1=~s/<//;$s141='';$s142=' selected'}
	elsif(index($s1,'>')==0){$s1=~s/>//;$s141='';$s143=' selected'}

	if(index($s1,"\\")==0){$s1=~s/\\//;}

	for($s1,$s2,$s){s/&/&amp;/g}for($s1,$s2,$s){s/</&lt;/g}
	for($s1,$s2,$s){s/&gt;/&gt;/g}for($s1,$s2,$s){s/"/&quot;/g}

	print"$rd<select name=replfield><option value=\"*\"\"$s111\">*<option value=\"\@\"$s112>@<option value=\"#\"$s113>#<option value=\";\">;</select></td>
<td>$i1=checkbox name=replregexp$s12>$i1=checkbox name=replrestuser$s13></td>
<td><select name=repldirection><option value=\"\"\"$s141\">=<option value=\"&gt;\"$s143>&gt;<option value=\"&lt;\"$s142>&lt;</select></td>
<td>$i1=text name=replpattern value=\"$s1\" size=20></td>
<td>$i1=text name=replcontent value=\"$s2\" size=20></td>
<td>$i1=text name=replcomment value=\"$s\" size=20>$dr\n";

++$i;}

print "<tr><td colspan=6>$lng[626]</td></tr></table><p><center>$hr<p>";
optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form></body></html>";

exit;


### параметры самообслуживания
SELFSERVICE:

if(!$stat=~/[adegs]/){print "<html><title>$lng[186]</title><body>$lng[116]</body></html>";exit;}
titleadmin("&#171;$lng[630]&#187;",$login,$stat);
print "<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100% border=0>";

optfield20('selftimeout',$lng[431],"<dd>$lng[631] <p>");

print "</table><center>$hr<p>";
optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form><p></body></html>";

exit;



SEDIT:

if(index($stat,'e')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body><h2>$lng[126]</h2></body></html>";exit;}
titleadmin($lng[490],$login,$stat);
print "<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100%>$cs6<font size=\"+1\"><center><b>$lng[127]<br>&nbsp;$dr";

optfield20('nummes',$lng[128],$lng[129]);
print "</table><p><center>$hr<p>";
optsubmit($login,$pass,'seditx',$fid,$lng[8]);
print "</form><p>$hr<p>";

print "<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100%>$cs6<font size=\"+1\"><center><b>$lng[127] $lng[586]<br>&nbsp;$dr";
optfield20('xfile',$lng[482],$lng[483]);
print "</table><p><center>$hr<p>";
optsubmit($login,$pass,'seditf',$fid,$lng[8]);
print "</form><p></body></html>";

exit;


SEDITX:

if(index($stat,'e')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body><h2>$lng[126]</h2></body></html>";exit;}
for $i(0..$#a){if($a[$i] eq 'nummes'){$nummes=$a[$i+1];}}

if(defined $nummes)
{	open NAM,"$inip{'dirrealkonf'}/$indname";@ini=<NAM>;close NAM;
	chomp @ini;
	for $i(0..$#ini){if(index($ini[$i],"<!--$nummes-->")>=0){$text=$ini[$i]}}
	undef @ini;

	if(length $text <3){print "<html><title>$lng[187]</title>$lng[130]$ended</html>";exit;}

	titleadmin($lng[490],$login,$stat);

	$text=~s/&/&amp;/g;$text=~s/</&lt;/g;$text=~s/>/&gt;/g;$text=~s/\"/&quot;/g;

	print "<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100%>";
	print "<tr><td colspan=3><font size=\"+1\"><center><b>$lng[127]$dr";
	print "$rd$lng[131]<br>$i1=text name=editind size=70 value=\"$text\">$dr<tr>$cs6$lng[132]$dr";
}
print "</table><p><center>$hr<p>$i1=hidden name=nummes value=$nummes>";
optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form><p></body></html>";

exit;


SEDITF:

if(index($stat,'e')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body><h2>$lng[126]</h2></body></html>";exit;}
if(length $xfile>0)
{	if(-e "$inip{'dirrealkonf'}/$xfile"!=1){print "<html><title>$lng[188]</title><body>File not found: $inip{'dirkonf'}/$xfile. $ended";exit;}
	if($xfile=~/\//){print "<html><title>$lng[188]</title><body>File not found: $inip{'dirkonf'}/$xfile. $ended";exit;}

	open NAM,"$inip{'dirrealkonf'}/$xfile";@ini=<NAM>;close NAM;chomp@ini;
	$a=join($cl,@ini);
	$a=~s/&/&amp;/g;$a=~s/</&lt;/g;$a=~s/>/&gt;/g;$a=~s/\"/&quot;/g;
	undef @ini;

	titleadmin($lng[490],$login,$stat);

	print "<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100%><tr><td colspan=3><font size=\"+1\"><center><b>$lng[127]$dr$rd<center>&nbsp;<br>$lng[484] $xfile:<br><textarea cols=70 rows=12 name=xtextx>$a</textarea>$dr<tr>$cs6 $dr</table><p><center>$hr<p>$i1=hidden name=xfilex value=\"$xfile\">$i1=hidden name=nummes value=$nummes>";
	optsubmit($login,$pass,'submit',$fid,$lng[8]);
	print "</form><p></body></html>";
}
else{goto ERROR}

exit;


MODIF:

if(index($stat,'d')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body><h2>$lng[133]</h2></body></html>";exit;}
titleadmin($lng[134],$login,$stat);
print "<center><b><i>$lng[611]</i></b>
</center><p>
<hr size=1 width=100% align=center><p>
<a name=mes></a><form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100%>$rd$lng[135]</td><td>$i1=text name=delref size=10></td><td><div align=right>$lng[136] $i1=checkbox name=delfil unchecked></tr><tr><td colspan=3><div align=left>$lng[137]$dr";
optonoff('replacedeleted',@lng[673,674]);
optfield('delmesbegin',@lng[675,676]);
print "</table><p><center>$hr<p>";
optsubmit($login,$pass,'submit',$fid,$lng[8]);

print "</form><p></body></html>";

exit;



MODIFUSER:

if(index($stat,'d')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body><h2>$lng[133]</h2></body></html>";exit;}
titleadmin("&#171;$lng[603]&#187;",$login,$stat);
print "<center><b><i>$lng[611]</i></b>
</a></center><p>";

# подсчет участников
open TMP,"$inip{'dirrealkonf'}/$indname";
$all=0;$s=0;while(<TMP>)
{	if(!/\-\-><li>/){next}
	string($_);if(length$stp[2]<=0){next}
	$s1=0;for$i(0..$#sra){if($sra[$i] eq $stp[2]){++$srs[$i];$s1=1;last}}
	if(!$s1){$sra[$s]=$stp[2];$srs[$s]=1;++$s}
}
close TMP;
print "<hr size=1 width=100% align=center><p>
<a name=user></a>
<br><div align=left>$lng[612] ",$#sra+1,"
<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100% border=1 cellpadding=0 cellspacing=0>
<tr><td><center><b>#</b></td><td width=80%><center><b>$lng[604]</b></td><td><center><b>$lng[605]</b></td><td><center><b>$lng[458]</b></td><td><center><b>$lng[609]</b></td><td><center><b>$lng[617]</b>$dr\n";

for$i(0..$#sra)
{	$sra[$i]=~s/"/&quot;/g;print $rd,$i+1," </td><td>$sra[$i]</td><td>$srs[$i]</td><td><input type=checkbox name=deluser value=\"$sra[$i]\" unchecked></td><td>$i1=checkbox name=delfil unchecked></td><td>$i1=checkbox name=setignor unchecked>$dr\n";
}

print "<tr><td>&nbsp;<p></td></tr>";
optonoff('replacedeleted',@lng[673,674]);
optfield('delmesbegin',@lng[675,676]);
print "</table><div align=left>$lng[606]</div><p><center>$hr<p>";
optsubmit($login,$pass,'submit',$fid,$lng[8]);

print "</form><p></body></html>";

exit;



MODIFSUBJ:

if(index($stat,'d')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body><h2>$lng[133]</h2></body></html>";exit;}
titleadmin("&#171;$lng[607]&#187;",$login,$stat);
print "<center><b><i>$lng[611]</i></b>
</center><p>";

# подсчет тем
undef@sra;undef@srs;open TMP,"$inip{'dirrealkonf'}/$inip{'indname'}";
$rep=0;$nul=0;$all=0;$s=0;while(<TMP>)
{	if(!/\-\-><li>/){next}
	string($_);if(length$stp[1]<=0){next}
	if($stp[1]=~s/$reply(\s\((\d+?)\))?:\s//i>0){++$rep}
	if($stp[1]=~s/<font color=.*?>(.*?)<\/font>/$1/i>0){++$nul}
	++$all;$s1=0;for$i(0..$#sra){if($sra[$i] eq $stp[1]){++$srs[$i];$s1=1;last}}
	if(!$s1){$sra[$s]=$stp[1];$srs[$s]=1;++$s}
}
close TMP;
print "<hr size=1 width=100% align=center><p>
<a name=subj></a>
<br><div align=left>$lng[613] ",$#sra+1,", $lng[614] $all, $lng[615] $nul, $lng[616] $rep.
<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100% border=1 cellpadding=0 cellspacing=0>
<tr><td><center><b>#</b></td><td width=80%><center><b>$lng[608]</b></td><td><center><b>$lng[605]</b></td><td><center><b>$lng[458]</b></td><td><center><b>$lng[609]</b>$dr\n";

for$i(0..$#sra)
{	$sra[$i]=~s/"/&quot;/g;print "$rd",$i+1," </td><td>$sra[$i]</td><td>$srs[$i]</td><td><input type=checkbox name=delsubj value=\"$sra[$i]\" unchecked></td><td>$i1=checkbox name=delfil unchecked>$dr\n";
}

print "<tr><td>&nbsp;<p></td></tr>";

optonoff('replacedeleted',@lng[673,674]);
optfield('delmesbegin',@lng[675,676]);
print "</table><div align=left>$lng[610]</div><p><center>$hr<p>";
optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form><p></body></html>";

exit;


ARHIV:

if(index($stat,'h')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body>$lng[138]</body></html>";exit;}
titleadmin($lng[492],$login,$stat);
print "$lng[443]<p>$hr<p><form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100% border=0>";
print "<tr><td colspan=6><font size=\"+1\"><center><b><a name=now></a>$lng[140]<br>&nbsp;$dr\n";

optselect('method',$lng[440],'',4,1,2,4,3,$lng[442],$lng[436],$lng[593],$lng[441]);
optfield20('dirarc',$lng[141]);
optonoff('sethtaccess',$lng[481]);
optfield20('indexarc',$lng[430]);
optfield20('archive',$lng[470]);
optfield20('mesarhiv',$lng[142]);
optselect('intervaltype',$lng[432],'',2,1,2,@lng[433,434]);
optfield20('regstring',"$lng[439] ($inip{'archive'})");
optonoff('setnewsarc',$lng[437]);
optfield20('setnewsstring',$lng[439],$lng[144]);

print "</table><p><center>$hr<p>";
optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form><p> <p><hr size=2 width=100% align=center></center></font><p><form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100% border=0><tr><td colspan=6><font size=\"+1\"><center><b><a name=auto></a>$lng[139]<br>&nbsp;$dr\n";

optselect('method',$lng[440],'',5,0,1,2,4,3,$lng[426],$lng[442],$lng[436],$lng[593],$lng[441]);
optfield20('dirarc',$lng[587]);
optonoff('sethtaccess',$lng[480]);
optfield20('indexarc',$lng[430]);
optfield20('archive',$lng[471]);
optfield20('timelimit',$lng[428]);
optfield20('meslimit',$lng[429]);
optfield20('selftimeout',$lng[431]);
optfield20('arctimeout',$lng[594]);
optselect('intervaltype',$lng[432],'',2,1,2,@lng[433,434]);
optfield20('regstring',"$lng[439] ($inip{'archive'})");
optonoff('setnewsarc',$lng[437]);
optfield20('setnewsstring',$lng[439],$lng[435]);
print "</table><p><center>$hr<p>";
optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form><p></body></html>";

exit;


NEWS:

if(index($stat,'n')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body><h2>$lng[145]</h2></body></html>";exit;}
titleadmin($lng[493],$login,$stat);

$daye=$t[3]+5;$monh=$t[4]+1;$mone=$t[4]+1;
print "<form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100%>
<tr><td colspan=8><font size=\"+1\"><center><b>$lng[146]<br>&nbsp;$dr
<tr><td colspan=3 width=30%>$lng[147]</td>
<td>$lng[151] $i1=text name=hourh size=2 maxlength=2 value=$t[2]></td>
<td>$lng[152] $i1=text name=minh size=2 maxlength=2 value=$t[1]></td>
<td>$lng[150] $i1=text name=dayh size=2 maxlength=2 value=$t[3]></td>
<td>$lng[149] $i1=text name=monh size=2 maxlength=2 value=$monh></td>
<td>$lng[148] $i1=text name=yearh size=4 maxlength=4 value=$t[5]>$dr
<tr><td colspan=3>$lng[153]</td>
<td>$lng[151] $i1=text name=houre size=2 maxlength=2 value=$t[2]></td>
<td>$lng[152] $i1=text name=mine size=2 maxlength=2 value=$t[1]></td>
<td>$lng[150] $i1=text name=daye size=2 maxlength=2 value=$daye></td>
<td>$lng[149] $i1=text name=mone size=2 maxlength=2 value=$mone></td>
<td>$lng[148] $i1=text name=yeare size=4 maxlength=4 value=$t[5]>$dr
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
<tr><td colspan=10><div align=left>$lng[166]$dr</table><p><center>$hr<p>";

optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form><p>$hr<p><div align=justify><form action=$inip{'dircgi'}/wtbedit.cgi method=post><table width=100%><tr><td colspan=8><font size=\"+1\"><center><b>$lng[456]<br>&nbsp;$dr\n";

open NAM,"$data/$wtbnews";@a=<NAM>;close NAM;chomp @a;

print "<tr><td colspan=10><center><select name=delnews multiple size=\"$#a\">";

for$i(1..(@a-1))
{	@b=split(';;',$a[$i]);
	$b[10]=~s/<(.*?)>//g;
	$b[10]=substr $b[10],0,50;
	print "<option value=$i>$b[3]:$b[4] $b[2]/$b[1]/$b[0]&#151;$b[8]:$b[9] $b[7]/$b[6]/$b[5]. $b[10]...</option>\n";
}


print "</select></center></td></tr><tr><td colspan=10><div align=left>$lng[457]$dr</table><p><center>$hr<p>";
optsubmit($login,$pass,'submit',$fid,$lng[458]);
print "</form></body></html>";

exit;


RESTORE:

if(index($stat,'s')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body>$lng[167]</body></html>";exit;}
titleadmin($lng[494],$login,$stat);

print "<table width=100% border=0>
<tr><td colspan=3><font size=\"+1\"><center><b>$lng[168]<br>&nbsp;$dr
<tr><td align=center>$lng[169]</td><td align=center>$lng[170]$dr
<tr><td align=center><form action=$inip{'dircgi'}/wtbedit.cgi method=post>
$i1=hidden name=restoration value=genindex>$i1=hidden name=login value=$login>
$i1=hidden name=fid value=$fid>$i1=hidden name=pass value=$pass>$i1=hidden name=oper value=submit>
$i1=submit value=$lng[8]></form></td>
<td align=center><form action=$inip{'dircgi'}/wtbedit.cgi method=post>
$i1=hidden name=restoration value=genstr>";

optsubmit($login,$pass,'submit',$fid,$lng[8]);

print "</form><p>$dr<tr><td colspan=2>$hr$dr
<tr><td colspan=2><form action=$inip{'dircgi'}/wtbedit.cgi method=post>
<br><font size=\"+1\"><b><center>$lng[171]</center><br>$dr
$rd$lng[172] $i1=text name=begrest size=10><br></td>
<td>$lng[173] $i1=text name=endrest size=10>$dr
$rd$lng[174]</td><td>$i1=text name=namindex size=20 value=\"$indname\">$dr
<tr><td align=center colspan=2><br>";

optsubmit($login,$pass,'submit',$fid,$lng[8]);
print "</form>$dr<tr><td colspan=2>$lng[175]$dr</table></body></html>";

exit;



WRONGLOG:

if(index($stat,'i')<0 and index($stat,'a')<0){print "<html><title>$lng[186]</title><body>$lng[116]</body></html>";exit;}
titleadmin($lng[489],$login,$stat);
print "\n<font size=\"+1\"><center><b>$lng[242]</b><p><font size=\"-1\"> $hr</center><ol>";

open NAM,"$data/$wtwrong";@b=<NAM>;close NAM;chomp @b;@b=reverse @b;
for(@b)
{	m/\A(.*?) /;$met=$1;
	m/Time=(.*?)(;|\Z)/;$time=$1;
	m/Log=(.*?); /;$log=$1;
	m/Pwd=(.*?); /;$pwd=$1;
	m/Host=(.*?); /;$host=$1;
	m/Email=(.*?); /;$email=$1;
	m/Misc=(.*?)/;$misc=$1;

	@c=split(/[;=]/);
	if(length $c[1]<1){$c[1]=$lng[243]}
	if(length $c[$#c]<1){$c[$#c]=$lng[244]}
	if(length $c[5]<1){$c[5]=$lng[245]}
	print "<li><i>$lng[246]</i> <b>$time</b>; <i>$lng[247]</i> <b>$log</b>; <i>$lng[248]</i> <b>$host</b>; <i>$lng[249]</i> <b>";

	if($met eq 'BDADM'){print $lng[250]}
	elsif($met eq 'WRONG'){print $lng[251]}
	elsif($met eq 'WRNCP'){print $lng[462]}
	elsif($met eq 'REGST'){print $lng[252]}
	elsif($met eq 'FILTR'){print $lng[461]}
	elsif($met eq 'ARCDL'){print $lng[62]}
	elsif($met eq 'ARCST'){print $lng[63]}
	elsif($met eq 'ARCZP'){print $lng[64]}
	elsif($met eq 'ARCRR'){print $lng[634]}
	elsif($met eq 'CMPZP'){print $lng[645]}
	elsif($met eq 'CMPRR'){print $lng[646]}
	else{print "$lng[253]: $met"}
	print "</b><br>\n"
}

print "</ul></font>$hr<p><dd>$lng[254]</body></html>";
exit;



### принятие изменений
SUBMIT:


# произвольная компрессия
if(length$specarcsrcdir)
{
	if(!-d $specarcsrcdir){$errlevel="Error: <b>$specarcsrcdir</b> &#151; not directory";goto LAST}
	if(!-d $specarcdestdir){$errlevel="Error: <b>$specarcdestdir</b> &#151; not directory";goto LAST}
	if(-e "$specarcdestdir/$specarcfile"){$errlevel="Error: file <b>$specarcdestdir/$specarcfile</b> already exist.";goto LAST}
	if(!-e $specarcsrcdir){$errlevel="Error: directory <b>$specarcsrcdir</b> not found.";goto LAST}
	if(!-e $specarcdestdir){if(!mkdir $specarcdestdir,0777){$errlevel="Error: can't create directory <b>$specarcdestdir</b>. Create it yourself and try again.";goto LAST}}


	if($specarcmethod==1)
	{	$s="zip -j -q";
		if($specarcdelfil eq 'on'){$s.=" -m"}
		$s.=" $specarcdestdir/$specarcfile $specarcsrcdir/$specarcext ";
		$arczp='CMPZP';
	}
	elsif($specarcmethod==2)
	{	$s="rar.exe";
		if($specarcdelfil eq 'on'){$s.=" mf"}else{$s.=" a"}
		$s.=" -inul -m5 -ep -s $specarcdestdir/$specarcfile $specarcsrcdir/$specarcext ";
		$arczp='CMPRR';
	}

	$s1=system$s;
	savewrong($arczp,$login,$pass,'',$s1);

	if(!$!)
	{	$size=-s "$specarcdestdir/$specarcfile";
		$errlevel="<b>Statistics:</b> <br>Succesfully archived into <b>$specarcdestdir/$specarcfile</b>. <br>Size of archive: <b>$size</b>. <br>";
	}
	else
	{	$errlevel="<b>Error:</b> <br>Compression failed, possible cause: unable to execute the compression program (errorlevel=$s1). <br>Standart archivation applied: <b>".($#forarc+1)."</b> file(s) archived into <b>$inip{'realpath'}/$inip{'dirarc'}</b>. <br>Size of source files: <b>$allsize</b>. <br>";
	}

	goto LAST;
}


# принудительная архивация
if(length$mesarhiv)
{	params(5);
	for(@cks)
	{	($a1,$a2)=split('=',$_,2);
		if($a1 eq 'method'){$inip{'method'}=$a2;}
		if($a1 eq 'dirarc'){$inip{'dirarc'}=$a2;}
		if($a1 eq 'sethtaccess'){$inip{'sethtaccess'}=$a2;}
		if($a1 eq 'archive'){$inip{'archive'}=$a2;}
		if($a1 eq 'mesarhiv'){$inip{'mesarhiv'}=$a2;}
		if($a1 eq 'intervaltype'){$inip{'intervaltype'}=$a2;}
		if($a1 eq 'regstring'){$patp{'regstring'}=$a2;}
		if($a1 eq 'setnewsarc'){$inip{'setnewsarc'}=$a2;}
		if($a1 eq 'setnewsstring'){$patp{'setnewsstring'}=$a2;}
		if($a1 eq 'arctimeout'){$inip{'arctimeout'}=$a2;}
	}
	$patp{'begarchive'}=$inip{'begarchive'};
	$patp{'endarchive'}=$inip{'endarchive'};
	substit($patp{'begarchive'});
	substit($patp{'endarchive'});
	&archivate;
	if($error==1){print "<html><title>$lng[188]</title><body>$lng[179] $ended";exit;}
	if($error==2){print "<html><title>$lng[188]</title><body>$lng[180] $ended";exit;}
	goto LAST;
}

#undef$begindex;undef$endindex;

#for($begindex,$endindex,$begmesform,$endmesform,$begansform,$endansform,$begarchive,$endarchive,$begmes,$endmes,$info,$xtextx,$searchmes,$about,$statistics,$contexthelp){s/$cr/<!>/g}
for(@inip){$inip{'$_'}=~s/$cr/<!>/g}


# обновление wtboard.txt
open NAM,"$data/$wtboard";@b=<NAM>;close NAM;chomp @b;
rename "$data/$wtboard","$data/$wtboard.old";
open NAM,">$data/$wtboard";
for(@b)
{	s/&amp;/&/g;s/&quot;/\"/g;
	s/&lt;/</g;s/&gt;/>/g;
	($b1,$s,$b2)=split(/(=)/,$_,2);


#	$inip{$b1}=~s/\\\'/\'/g;
	if($s eq '=')
	{	if(length$inip{$b1}){$b2=$inip{$b1}}
		$b2=~s/$cr|$cl/<!>/g;
		$b2=~s/\\([\$\@\&\'\s\"\;])/$1/g;
		if($b2 eq 'n/a'){$b2=''}
		print NAM "$b1=$b2\n";
	}
	else{print NAM "$_\n"}
}
close NAM;
undef @b;
if(-z "$data/$wtboard"==1){rename "$data/$wtboard\.old","$data/$wtboard";}

### прочие администрации

# администрация
for$i(0..$#cks)
{	($a1,$a2)=split('=',$cks[$i],2);
	if($a1 eq 'names'){@gnames=split($cr,$a2);}
}
if(defined @gnames)
{	for(@gnames)
	{	@s=split(/\|/);
		$wtbuser{"id_$s[0]"}=$s[0];
		$wtbuser{"w_$s[0]"}=$s[1];
		$wtbuser{"m_$s[0]"}=$s[2];
		$wtbuser{"n_$s[0]"}=$s[3];
		$wtbuser{"h_$s[0]"}=$s[4];
		$wtbuser{"u_${fid}_$s[0]"}=$s[5];
		$wtbuser{"t_${fid}_$s[0]"}=$s[6];
	}
	undef@gnames;
}

for(@cks)
{	($a1,$a2)=split('=',$_,2);
	if($a1 eq 'anam'){@anam=split($cr,$a2);}
	if($a1 eq 'apwd'){@apwd=split($cr,$a2);}
	if($a1 eq 'astat'){@astat=split($cr,$a2);}
}
if(defined@anam)
{	open NAM,">$data/$wtbadmin";
	for$i(0..$#anam){print NAM "$anam[$i];;$apwd[$i];;$astat[$i];;\n";}
	close NAM;
	undef@anam;undef@apwd;undef@astat;
}


substit($inip{'begbody'});substit($inip{'endbody'});
#$begbody=$inip{'begbody'};$endbody=$inip{'endbody'};
substit($inip{'begindex'});substit($inip{'endindex'});
substit($inip{'begarchive'});substit($inip{'endarchive'});

open NAM,"$inip{'dirrealkonf'}/$inip{'indname'}";@ini=<NAM>;close NAM;

if($ini[0] ne $inip{'begindex'})
{	open NAM,">$inip{'dirrealkonf'}/$inip{'indname'}";
	print NAM $inip{'begindex'},"\n";print NAM @ini[1..$#ini-1];print NAM $inip{'endindex'},"\n";
	close NAM;undef @ini;
#	goto LAST;
}




# игнор-лист
for$i(0..$#cks)
{	($a1,$a2)=split('=',$cks[$i],2);
	if($a1 eq 'ignor'){@ignor=split($cr,$a2);}
	if($a1 eq 'ignort'){@ignort=split($cr,$a2);}
	if($a1 eq 'ignorm'){@ignorm=split($cr,$a2);}
}
if(defined @ignor)
{#	delete$wtbuser{'ignor_ip'};delete$wtbuser{'stop_ip'};
	$s1='';$s2='';for$i(0..$#ignor)
	{	if(!length$ignor[$i]){next}
		if($ignor[$i]=~/\./)	# ip-адрес
		{	$ignor[$i]=~s/([\-!])//;
			if($1 eq '-'){$s1.=";$ignor[$i]"}
			elsif($1 eq '!'){$s2.=";$ignor[$i]"}
			next;
		}
		else		# маска
		{	$ignor[$i]=~s/([\-!])//;my$s=$1;correct($ignor[$i]);
			$wtbuser{"i_$ignor[$i]"}=$s;
			$wtbuser{"it_$ignor[$i]"}=$ignort[$i];
			$wtbuser{"ib_$ignor[$i]"}=$ignorm[$i];
		}
	}
	$wtbuser{'ignor_ip'}=$s1;
	$wtbuser{'stop_ip'}=$s2;
	undef @ignor;undef @ignort;undef @ignorm;
}


# редактирование индекса
if(length$editind>0)
{	$s=chr(151);
	$text=~s/&lt;/</g;$text=~s/&gt;/>/g;$text=~s/&quot;/\"/g;$text=~s/&amp;/&/g;

	$editind=~s/$s/&#151;/g;
	open NAM,"$inip{'dirrealkonf'}/$inip{'indname'}";@ini=<NAM>;close NAM;
	open NAM,">$inip{'dirrealkonf'}/$inip{'indname'}";
	for $i(0..$#ini)
	{	if(index($ini[$i],"<!--$nummes-->")>=0){$ini[$i]=$editind."\n";}
		print NAM $ini[$i];
	}
	close NAM;
	goto LAST;
}

# новостная строка
if(length$newmessage>0)
{	$newmessage=~s/ - / &#151; /g;
	$newmessage=~s/--/&#151;/g;
	open NAM,"+>>$data/$wtbnews";
	print NAM "$yearh;;",$monh-1,";;$dayh;;$hourh;;$minh;;$yeare;;",$mone-1,";;$daye;;$houre;;$mine;;";

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
	goto LAST;
}

# удаление новостной строки
$j=1;for$i(0..$#a)
{	if($a[$i] eq 'delnews'){$dn[$j]=$a[$i+1];++$j}
}
if($#dn>0)
{	open NAM,"$data/$wtbnews";@b=<NAM>;close NAM;chomp@b;open NAM,"+>$data/$wtbnews";

	for$i(1..$#dn)
	{	undef $b[$dn[$i]];
	}
	for$i(0..@b)
	{	if(length $b[$i]>0){print NAM "$b[$i]\n"}
	}
	close NAM;
	goto LAST;
}


# сохранение отредактированного файла
for$i(0..$#cks)
{	($a1,$a2)=split('=',$cks[$i],2);
	if($a1 eq 'xtextx'){$xtextx=$a2;}
}
if(length $xfilex>0)
{	$xtextx=~s/$cr/\n/g;
	open NAM,"+>$inip{'dirrealkonf'}/$xfilex";
	print NAM $xtextx;close NAM;
	goto LAST;
}


# сохранение элементов контекстной замены

$j=0;for$i(0..$#cks)
{	($a1,$a2)=split('=',$cks[$i],2);
	if($a1 eq 'replfield'){$replfield[$j]=$a2;}
	if($a1 eq 'replregexp'){$replregexp[$j]=$a2;}
	if($a1 eq 'replrestuser'){$replrestuser[$j]=$a2;}
	if($a1 eq 'repldirection'){$repldirection[$j]=$a2;}
	if($a1 eq 'replpattern'){$replpattern[$j]=$a2;}
	if($a1 eq 'replcontent'){$replcontent[$j]=$a2;}
	if($a1 eq 'replcomment'){$replcomment[$j]=$a2;++$j;}
	
}

if(defined@replfield)
{	open NAM,"+>$data/$wtbreplace";
	print NAM "; White Tiger WWW Board. File of patterns\n; and definitions of contextual replacement\n;\n;    Note: at \"Submit\" the replacement is carried out according to the direct \n;    order of an arrangement of definitions, at quoting of the text -\n;    according to the return order of an arrangement of definitions\n;\n;    Keychars:\n;      # - replace only in subject                          \\\n;      \@ - replace only in body                             і I, only first\n;      * - replace both                                     і position\n;      ; - commentary                                       /\n;      % - enable regexp                                    - II, after I\n;      ! - allow to stop replace by user                    - III, after I and II\n;      > - replace text-to-message at submit the message    \\ IV, after I, II\n;      < - replace message-to-form at get the form          / and III\n;      \\ - begin of pattern                                 - only after all\n;\n;";
	for$i(0..$#replfield)
	{	print NAM "\n$replfield[$i]";
		if($replregexp[$i] eq 'on'){print NAM '%'}
		if($replrestuser[$i] eq 'on'){print NAM '!'}
		print NAM "$repldirection[$i]\\$replpattern[$i];;$replcontent[$i]";
		if(length$replcomment[$i]>0){print NAM "\\;\/$replcomment[$i]"}
	}

	$errlevel="<b>Statistics:</b> <br>".($#replfield+1)." patterns saved. <br>";

}

# структура
for$i(0..$#cks)
{	($a1,$a2)=split('=',$cks[$i],2);
	if($a1 eq 'restoration'){$restor=$a2;}
}
if($restor eq 'genindex')	# восстановление индекса из структуры
{	$all=0;
	open NAM,"$data/$wtbstruct";@a=<NAM>;close NAM;chomp @a;
	open NAM,">$inip{'dirrealkonf'}/$inip{'indname'}";
	print NAM "$inip{'begindex'}\n<ul>\n<!--home-->";
	for $i(1..$#a)
	{	while(index($a[$i],'()')>0){$a[$i]=~s/\(\)//g;}
		$a[$i]=~s/ //g;
		if(length $a[$i]<2){goto NEXTING}
		@b=split(/([(.,*)])/,$a[$i]);
		$s=0;for$j(0..$#b)
		{	if($b[$j] eq '(' and $inip{'treestyle'}==1){print NAM "\n<ul><!--".$b[$j+1]."--><li>"}
			elsif($b[$j] eq ')' and $inip{'treestyle'}==1){print NAM "\n</ul>"}
			elsif($b[$j] eq '*' and $inip{'treestyle'}==1){print NAM "\n<!--".$b[$j+1]."--><li>$inip{'answerlabel'}"}
			elsif($b[$j] eq ',' and $inip{'treestyle'}==1){print NAM "\n<!--".$b[$j+1]."--><li>$inip{'arclabel'}"}
			elsif($b[$j] eq '.'){$s=1;print NAM "\n<!--".$b[$j+1]."--><li>"}
			elsif(!length$b[$j]){next}
			else
			{	if($inip{'treestyle'}==2 and !$s){next}
				for$ja(0..4)
				{	if(!-e "$inip{'dirrealkonf'}/$b[$j].$exts[$ja]"){next}
					else{$ia=$ja;last}
				}
				if(!-e "$inip{'dirrealkonf'}/$b[$j].$exts[$ia]")
				{	print NAM "<i>$b[$j] &#151; $lng[176]</i>";next;
				}
				else
				{	undef @stp;
					filestp("$inip{'dirrealkonf'}/$b[$j].$exts[$ia]");
					$stp[0]="$b[$j].$exts[$ia]";

					if(length$stp[1]>$inip{'maxshowsubj'}){$stp[1]=substr($stp[1],0,$inip{'maxshowsubj'}-3).'...'}
					if(!length$stp[1]){$stp[1]=$lng[176]}
					elsif(length$stp[22]>0 and $stp[22]<=0 and $inip{'selectnul'}==2){$stp[1]="<font color=\"$inip{'nulcolor'}\">$stp[1]</font>"}

					$string=$hstring;
					for$i(0..$#tag)
					{	if(!length$tag[$i]){next}
						$string=~s/$tag[$i]/$stp[$i]/g;
					}
					print NAM "$string";
					++$all;
				}
				if($inip{'treestyle'}==2){last}
			}
		}
NEXTING:
	}
	print NAM "\n$inip{'endindex'}";
	close NAM;
	$errlevel.="<b>Statistics:</b> <br>$all messages restored. <br>";
	goto LAST;
}
elsif($restor eq 'genstr')		# генерация структуры из индекса
{	open NAM,"$inip{'dirrealkonf'}/$inip{'indname'}";@a=<NAM>;close NAM;chomp@a;
	open NAM,">$data/$wtbstruct";
	$i=3;
	while($i<$#a)
	{	@b=split('--',$a[$i]);
		if(index($a[$i],'<ul>')==0)
		{	print NAM "(";
			if($a[$i]=~/<li>\Z/i){}
			elsif(index($a[$i],$lng[176])<0){print NAM $b[1]}
		}
		elsif(index($a[$i],'</ul>')==0){print NAM ")";}
		elsif(index($a[$i],"<li>$inip{'answerlabel'}")>0 and index($a[$i],$lng[176])<0){print NAM "\n*$b[1]";}
		elsif(index($a[$i],"<li>$inip{'arclabel'}")>0 and index($a[$i],$lng[176])<0){print NAM "\n,$b[1]";}
		else{if(index($a[$i],$lng[176])<0){print NAM "\n.$b[1]";}}

		++$i;
	}
	print NAM "\n";
	close NAM;

	open NAM,"$data/$wtbstruct";@ini=<NAM>;close NAM;chomp @ini;
	open NAM,">$data/$wtbstruct";
	for$i(0..@ini)
	{	$ini[$i]=~s/\(\)//g;
		if(length($ini[$i])>1 or $i==0){print NAM "$ini[$i]\n"}
	}
	close NAM;

	if(-z "$data/$wtbstruct"){print "\n<html><title>Error</title>Error in creating file <b>$data/$wtbstruct</b>, <b><i>do not run</i></b> restoration of index-file! Check access rights of $wtbstruct and turn again. $ended";exit;}

	goto LAST;
}


# восстановление индекса только из сообщений
if(length$namindex>0)
{	$j=0;
	for$i($begrest..$endrest)
	{	$ia=-1;for$ja(0..4)
		{	if(-e "$inip{'dirrealkonf'}/$i.$exts[$ja]"==1){$ia=$ja;last}
		}
		next if $ia<0;
		filestp("$inip{'dirrealkonf'}/$i.$exts[$ia]");
		@c=split(';',$stp[40]);
		if($#c<=0)
		{	$rest[$j]=sprintf('%12.12d',$i);
			++$j;
		}
	}

	@rest=reverse(@rest);
	for$i(0..@rest){$rest[$i]=~s/^(0*)//;}
	undef@b;undef@c;

	open NAM,">$inip{'dirrealkonf'}/$inip{'namindex'}";
	substit($inip{'begindex'});print NAM "$inip{'begindex'}\n<ul>\n<!--home-->\n";

	$all=0;$i=0;while($i<=$#rest)
	{	for$ja(0..4){if(-e "$inip{'dirrealkonf'}/$rest[$i].$exts[$ja]"==1){$ia=$ja;last}}
		if(-e "$inip{'dirrealkonf'}/$rest[$i].$exts[$ia]"!=1){++$i;next}
		undef @stp;filestp("$inip{'dirrealkonf'}/$rest[$i].$exts[$ia]");

		print NAM "<!--".$rest[$i]."--><li>";

		$s=$stp[39];@b=split(/([\(\)])/,$s);
		$stp[0]="$rest[$i].$exts[$ia]";
		$string=$hstring;#$string=~s/&amp;/&/g;

		if(length$stp[1]>$inip{'maxshowsubj'}){$stp[1]=substr($stp[1],0,$inip{'maxshowsubj'}-3).'...'}
		$stp[1]=~s/\$/&#36;/g;
		for$i(0..$#tag)
		{	if(!length$tag[$i]){next}
			$string=~s/$tag[$i]/$stp[$i]/g;
		}
		print NAM "$string\n";++$all;

		if($inip{'treestyle'}==1)
		{	for$j(1..$#b)
			{	if($b[$j] eq '('){print NAM "<ul><!--".$b[$j+1]."--><li>"}
				elsif($b[$j] eq ')'){print NAM "</ul>\n"}
				elsif(length$b[$j]<1){next}
				else
				{	for$ja(0..4){if(-e "$inip{'dirrealkonf'}/$b[$j].$exts[$ja]"){$ia=$ja;last}}
					if(!-e "$inip{'dirrealkonf'}/$b[$j].$exts[$ia]")
					{	print NAM "<i>$b[$j]</i> &#151; $lng[176]";next;
					}
					else
					{	undef @stp;
						filestp("$inip{'dirrealkonf'}/$b[$j].$exts[$ia]");
						$stp[0]="$b[$j].$exts[$ia]";
						if(length$stp[22]>0 and $stp[22]<=0 and $selectnul==2){$stp[1]="<font color=$nulcolor>$stp[1]</font>"}
						$string=$hstring;
						$stp[1]=~s/\$/&#36;/g;
						for$i(0..$#tag)
						{	if(!length$tag[$i]){next}
							$string=~s/$tag[$i]/$stp[$i]/g;
						}
						print NAM "$string\n";++$all;
					}
				}
			}
			++$i;
		}
	}
	substit($inip{'endindex'});print NAM $inip{'endindex'};
	close NAM;$errlevel.="<b>Statistics:</b> <br>$all messages restored. <br>";
	print "$lng[177]<p><pre>[&lt;a href=./$inip{'namindex'}&gt;$lng[178]&lt;/a&gt;]</pre><p>";
	goto LAST;
}


## удаление по номерам
substit($lng[672],$patp{'delmesbegin'});
for$i(0..$#cks)
{	($a1,$a2)=split('=',$cks[$i],2);
	if($a1 eq 'delref'){@delref=split(' ',$a2);}
	if($a1 eq 'delfil'){$delfil=$a2;}
}

if(defined@delref){$errlevel='<b>Statistics:</b><br> ';$s=0;for(@delref){$s=deletemes($_,$delfil);if($s){$delfil eq 'on'?$errlevel=$errlevel."$stp[42] &#151; deleted<br> ":$errlevel=$errlevel."$stp[0] &#151; cleared<br> "}elsif($s==-1){$errlevel=$errlevel."$stp[42] &#151; not found<br> "}elsif(!$s){$errlevel.="$stp[42] &#151; not found<br> "}}}


# удаление по участникам
undef@deluser;undef@delfil;$s=0;
for$i(0..$#cks)
{	($a1,$a2)=split('=',$cks[$i],2);
	if($a1 eq 'deluser')
	{	++$s;
		$deluser[$s]=$a2;
		$s1=1;
	}
	if($a1 eq 'delfil'){$delfil[$s]=$a2}
	if($a1 eq 'setignor'){$setignor[$s]=$a2}
}
if(defined@deluser)
{	$ss=0;$errlevel='<b>Statistics:</b><br> ';
	open TMP,"$inip{'dirrealkonf'}/$inip{'indname'}";@b=<TMP>;close TMP;chomp@b;
	for(@b)
	{	if(!/\-\-><li>/){next}
		string($_);if(length$stp[2]<=0){next}
		for$i(0..$#deluser)
		{	if($stp[2] eq $deluser[$i])
			{	$s1=deletemes($stp[38],$delfil[$i]);
				if($s1==1){if($delfil[$i] eq 'on'){$errlevel=$errlevel."$stp[42] ($deluser[$i]) &#151; deleted<br> "}else{$errlevel=$errlevel."$stp[0] ($deluser[$i]) &#151; cleared<br> "}}elsif($s1==-1){$errlevel=$errlevel."$stp[42] ($deluser[$i]) &#151; not found (may be already deleted by preview process)<br> "}elsif($s1==0){$errlevel=$errlevel."$stp[42] ($deluser[$i]) &#151; not deleted<br> "}
				$s2='';$ss=1;
			}
		}
	}
	if(!$ss){$errlevel=$errlevel."Users not found.<p>"}
	for$i(0..$#deluser){if($setignor[$i] eq 'on'){$errlevel=$errlevel."$deluser[$i] &#151; added into ignor-list<br> ";correct($deluser[$i]);$wtbuser{"i_$deluser[$i]"}='-';$wtbuser{"it_$deluser[$i]"}=$lng[29];$wtbuser{"it_$deluser[$i]"}=$lng[578]}}
}

# удаление по темам
undef@delsubj;undef@delfil;$s=0;
for$i(0..$#cks)
{	($a1,$a2)=split('=',$cks[$i],2);
	if($a1 eq 'delsubj')
	{	++$s;
		$delsubj[$s]=$a2;
	}
	if($a1 eq 'delfil'){$delfil[$s]=$a2}
}
if(defined@delsubj)
{	$ss=0;$errlevel='<b>Statistics:</b><br> ';
	open TMP,"$inip{'dirrealkonf'}/$inip{'indname'}";@b=<TMP>;close TMP;chomp@b;
	for(@b)
	{	if(!/\-\-><li>/){next}
		string($_);if(length$stp[1]<=0){next}
		$stp[1]=~s/$inip{'reply'}(\s\((\d+?)\))?:\s//i;
		$stp[1]=~s/<font color=.*?>(.*?)<\/font>/$1/i;
		for$i(0..$#delsubj)
		{	if($stp[1] eq $delsubj[$i])
			{	$s1=deletemes($stp[38],$delfil[$i]);
				if($s1==1){if($delfil[$i] eq 'on'){$errlevel.="$stp[42] ($delsubj[$i]) &#151; deleted<br> "}else{$errlevel.="$stp[0] ($delsubj[$i]) &#151; cleared<br> "}}elsif($s1==-1){$errlevel.="$stp[42] ($delsubj[$i]) &#151; not found (may be already deleted)<br> "}elsif($s1==0){$errlevel.="$stp[42] ($delsubj[$i]) &#151; not deleted<br> "}
				$s2='';$ss=1;
			}
		}
	}
	if(!$ss){$errlevel.="Subjects not found.<p>"}
}

goto LAST;




LAST:

print "<html><title>$lng[189]</title><body bgcolor=#bbbbbb>$errlevel$lng[184] $ended";

exit;


ERROR:
print "<html><title>$lng[188]</title><body>$lng[185] $ended";
exit;


