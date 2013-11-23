#!/usr/bin/perl

# White Tiger WWW Board ver.2.936b
# система wwwboard. Разработка, реализация
# (C) 1998-2000, White Tiger (2:5049/91.38; 
# email:wtiger@mail.ru; http://wtiger.ncport.ru)
# wtbservice.cgi - модуль обеспечения сервисных функций
# wtbservice.cgi - services module

# замена переменных производится в файле wtbext.cgi
# you must change values in the wtbext.cgi















# прочие величины
if(!-e"wtbext.cgi"){print "\nError: not found wtbext.cgi";exit}
require "wtbext.cgi";
params(3);


$ended="<p><center>[<a href=$inip{'dirkonf'}/>$inip{'thekonf'}</a>] [<a href=$inip{'dirkonf'}/$inip{'service'}>$lng[190]</a>]<p>$endbody";

### индивидуализация
# распознавание


if(not defined $a[0]){$a[0]='ins';$a[1]='news'}

for$i(0..$#a)
{	if($a[$i] eq 'search'){$tps=1;goto SEARCH}
	if($a[$i] eq 'ins'){goto INSERT}
	if($a[$i] eq 'lastest'){$tps=2;goto SEARCH}
	if($a[$i] eq 'about'){goto ABOUTX}
	if($a[$i] eq 'aboutsoft'){&about; exit;}
	if($a[$i] eq 'statist'){goto STATIST}
	if($a[$i] eq 'help'){goto HELP}
	if($a[$i] eq 'forbidden'){goto FORBIDDEN}
}
goto ERROR;


INSERT:

for$i(0..$#cks)
{	($a1,$a2)=split('=',$cks[$i],2);
	if($a1 eq 'ins'){$ins=$a2}
	if($a1 eq 'newstype'){$newstype=$a2}
}

if($ins eq 'begsearch')		# (последнее сообщение)-100
{	open NAM,"$data/$wtblast";$last=<NAM>-100;close NAM;
	if($last<0){$last=0}
	print $last;
}
if($ins eq 'endsearch')		# (последнее сообщение)
{	open NAM,"$data/$wtblast";$last=<NAM>;close NAM;
	print $last;
}
if($ins eq 'begdata')
{	@b=localtime(time+$timeshift*60-604800);$b[5]=$b[5]+1900;
	printf ('%2.2d/%2.2d/%2.2d',$b[3],$b[4]+1,$b[5]);
}
if($ins eq 'enddata')
{	printf ('%2.2d/%2.2d/%2.2d',$t[3],$t[4]+1,$t[5]);
}
if($ins eq 'getdata')
{	@b=localtime(time+$timeshift*60-259200);$b[5]=$b[5]+1900;
	printf ('%2.2d/%2.2d/%2.2d',$b[3],$b[4]+1,$b[5]);
}
if($ins eq 'news')
{

# проверка доступа с запрещенного ip-адреса
	$s=&verifyuser;
	if($s==-2){print "$lng[421] <p> $inip{'separator'}\n<script>\n<font size=1 color=\"$inip{'indbgcolor'}\">"}
	if($s==-1){print "$lng[495] <p> $inip{'separator'}\n<font size=1 color=\"$inip{'indbgcolor'}\">"}
	
	&shownews;
# обновление wtbnames по факту просмотра
	updateuser($names);
}

exit;


SEARCH:

$val=0;$tot=0;

for$i(0..$#cks)
{	($a1,$a2)=split('=',$cks[$i],2);
	if($a2 eq 'newmes'){$typemes=1}
	if($a2 eq 'newans'){$typemes=2}
	if($a1 eq 'begin'){$begin=$a2}
}

if(defined $begin){goto SEARCH2}


if($tps==1)
{

if(not defined $keysearch){print "$t1 $lng[191]</title>$begbody$lng[192]<P>$ended";exit;}

if(length($endsearch)==0){open NAM,"$data/$wtblast";$endsearch=<NAM>;close NAM;}
if(length($begsearch)==0){$begsearch=$endsearch-100;}
if($begsearch<0){$begsearch=0;}

$begdatax=counts($begdata);
$enddatax=counts($enddata);


$ks=$keysearch;
@keys=split(/[+\., \(\);:\-]/,$keysearch);
for(@keys,$keysearch){replacx($_);smaller($_);correct($_)}

### поиск в текущем форуме
# область поиска
for$i(0..$#cks)
{	($a1,$a2)=split('=',$cks[$i],2);
	if($a1 eq 'srhall'){if($a2 eq 'on'){$srhall=1;last}}
	if($a1 eq 'bodyonly'){if($a2 eq 'on'){$bodyonly=1}}
	if($a1 eq 'srhsubj'){if($a2 eq 'on'){$srhsubj=1}}
	if($a1 eq 'srhauthor'){if($a2 eq 'on'){$srhauthor=1}}
	if($a1 eq 'srhaddr'){if($a2 eq 'on'){$srhaddr=1}}
	if($a1 eq 'srhurl'){if($a2 eq 'on'){$srhurl=1}}
	if($a1 eq 'srhimg'){if($a2 eq 'on'){$srhimg=1}}
}

if($srhall+$bodyonly+$srhsubj+$srhauthor+$srhaddr+$srhurl+$srhimg==0){$bodyonly=1}
if($bodyonly+$srhsubj+$srhauthor+$srhaddr+$srhurl+$srhimg==6){$srhall=1}

SE:for$i($begsearch..$endsearch)
{	$s=0;$b='';
	for$j(0..4)
	{	if(-e"$inip{'dirrealkonf'}/$i.$exts[$j]"==1){$ia=$j;last}
	}
	if(!-e"$inip{'dirrealkonf'}/$i.$exts[$ia]"){next};
	if(filestp("$inip{'dirrealkonf'}/$i.$exts[$ia]")<0){next};

	++$tot;
	if($srhall){$b=join(' ',@stp[1,3,11,17,19,22,24,25,26,27,31])}
	else
	{	if($bodyonly){$b.=$stp[24]}
		if($srhsubj){$b.=$stp[1]}
		if($srhauthor){$b.=$stp[3]}
		if($srhaddr){$b.=$stp[31]}
		if($srhurl){$b.=$stp[25].$stp[26]}
		if($srhimg){$b.=$stp[27]}
	}
	replacx($b);smaller($b);correct($b);
	if($typesearch==1)
	{	for(@keys)
		{	if($b=~/$_/){$s=1;last}
		}
		if(!$s){next}
	}
	elsif($typesearch==2)
	{	for(@keys)
		{	if(!($b=~/$_/)){$s=1;last}
		}
		if($s){next}
	}
	elsif($typesearch==3){if(!($b=~/$keysearch/)){next}}
	for$j(0..$#stp){$prs[$val].=sprintf("|%%%2.2d|$stp[$j]",$j)};++$val;
}

if($searcharchive eq 'on')
{for$i($begsearch..$endsearch)
{	for$n(0..@archive)
	{if(-e "$inip{'realpath'}/$archive[$n]/$i.html" !=1){next}
	open NAM,"$inip{'realpath'}/$archive[$n]/$i.html";@b=<NAM>;close NAM;
	for$j(0..@b){if(index($b[$j],$lng[14])==0){@c=split('i>',$b[$j]);$k=$c[$#c-1];@c=split(/[ <]/,$k);$k=$c[1];last;}}
	$k=~s/(\/19)|(\/20)/\//;$k=counts($k);
	if($k<$begdatax or $k>$enddatax){next}

	if($bodyonly eq "on"){for$j(0..@b){if(index($b[$j-1],$inip{'paragraph'})==0){$b=$b[$j];last}}}
	else{$b=join ' ',@b}

	++$tot;
	smaller($b);correct($b);
	if($typesearch==1){for $k(0..$#keys){if(index($b,$keys[$k])<0){goto NEXTSS;}}}
	elsif($typesearch==2)
	{	for $k(0..$#keys)
		{	if(index($b,$keys[$k])<0){goto NEXTSS}
		}
	}
	elsif($typesearch==3){if(index($b,$keysearch)<0){goto NEXTSS}}
	$prs[$val]=$inip{'realpath'}.'/'.$archive[$n].'/'.$i.".html";++$val;
NEXTSS:
	}
}
}

undef @b;undef $b;

#	for$j(0..@archive){$stp[0]=~s/$inip{'realpath'}\/$archive[$j]\//\.\.\/$archive[$j]\//;}
}
if($tps==2)
{

$getdatax=$getdata;
if($gettype==1)
{	length($getdata)==0 ? $getdata="$t[2]:$t[1]:$t[0] $t[3]/".($t[4]+1)."/$t[5]" : $getdata="$t[2]:$t[1]:$t[0] $getdata" ;
	$getdata=counts($getdata);
}
else{open NAM,"$data/$wtblast";$last=<NAM>;close NAM;}

open NAM,"$inip{'dirrealkonf'}/$inip{'indname'}";@b=<NAM>;close NAM;
for$i(3..$#b-1)
{	if($b[$i]=~m/<li>/!=1){next}
	++$tot;
       	$hstring=$string;
	string($b[$i]);
	$stp[0]="$inip{'dirkonf'}/$stp[0]";

	if($gettype==1)
	{	if($stp[23]<$getdata){next}
	}
	else
	{	$b=$stp[38];
		if($b<$getdata or $b>$last){next}
	}

	for$j(0..$#stp){$prs[$val].=sprintf("|%%%2.2d|$stp[$j]",$j)}
	++$val;
}

}

# сортировка и вывод результата

if($tps>0)
{	if($sorttype==1){$s='01'}
	elsif($sorttype==2){$s='02'}
	elsif($sorttype==3){$s='23'}
	else{$s='00'}

	@prs=sort{substr($a,index($a,"|%$s|")) cmp substr($b,index($b,"|%$s|"))}@prs;
	if($reverse eq 'on'){@prs=reverse@prs}

	for(@prs)
	{	($s,@stp)=split(/\|\%\d\d\|/);
		$string=$hstring;$stp[14]=sprintf('%2.2d',++$stp[14]);$stp[15]=sprintf('%2.2d',++$stp[15]);
		for$j(0..$#tag)
		{	if(length$tag[$j]){$string=~s/$tag[$j]/$stp[$j]/g}
		}
		$_="<li>$string\n";
	}
}

if($val==0){$prs[0]="<li>$lng[226]<br>\n"}

@t=localtime(time+$inip{'timeshift'}*60);$t[5]+=1900;
$newdata=$t[0]+($t[1]+($t[2]+($t[3]+($t[4]+$t[5]*12)*31)*24)*60)*60;
$newdata=$newdata-$curtime;


if($tps==1)
{$pra="<ul><li>$lng[195] $ks<br><li>$lng[230] [$begsearch.$ext]&#151;[$endsearch.$ext]<br>\n<li>$lng[218] [$begdata]&#151;[$enddata]<br>";
}
elsif($tps==2)
{
$pra="<ul><li>$lng[227]<br><li>$lng[230] [$getdatax]<br>";
}

$reverse eq 'on' ? $pra.="<li>$lng[219]<br>" : $pra=$pra ;
#$searcharchive eq 'on' ? $pra.="<li>$lng[229]<br>" : $pra=$pra ;

if($tps==1)
{	$pra.="<li>$lng[597]";
	if($srhall){$pra.=" [$lng[225]]"}
	else
	{	if($bodyonly){$pra.=" [$lng[224]]"}
		if($srhsubj){$pra.=" [$lng[598]]"}
		if($srhauthor){$pra.=" [$lng[599]]"}
		if($srhaddr){$pra.=" [$lng[600]]"}
		if($srhurl){$pra.=" [$lng[601]]"}
		if($srhimg){$pra.=" [$lng[602]]"}
	}
}


$pra.="<li>$lng[220] ";
if($sorttype==1){$pra.=$lng[221]}elsif($sorttype==2){$pra.=$lng[222]}elsif($sorttype==3){$pra.=$lng[223]}else{$pra.=$lng[425]}
$pra.="<br>\n<li>$lng[197] $val
<li>$lng[424] $tot
<li>$lng[422] $newdata $lng[423].</ul><p>$inip{'separator'}<p><ul>\n";


delete $inip{'search'};
substit($lng[667],$patp{'searchmes'});$lng[667]=~s/[\$%]searched/\n$pra\n@prs\n<\/ul>/g;
print "\n$lng[667]";

exit;

SEARCH2:


open NAM,"$inip{'dirrealkonf'}/$inip{'indname'}";@a=<NAM>;close NAM;chomp@a;
$newmes=0;$count=0;$s1=0;$s=0;
for(@a)
{	if(/<!\-\-end\-\->/){last}
	undef@stp;if(/<!\-\-\d+\-\->/){string($_);correct($stp[2]);}

# newmes - typemes=1, newans - typemes=2

	if(!$s and $begin<$stp[23])
	{	s/<ul>(<!\-\-\d+\-\->)/$1/;
		$s=1;$s1=0;
		if($typemes==2){if($stp[2] ne $names){$s=0};$s2=0;next}
	}
	if($s)
	{	if($typemes==2)
		{	if(/^<!\-\-\d+\-\->/){$s=0;next}
			if(!$s2){s/^<ul>(<!\-\-\d+\-\->)/$1/;$s2=1}
		}
		if(/<!\-\-\d+\-\->/){$sr[$count]="$_\n";++$count;++$newmes;if(/<ul>/){++$s1}}
		else{if($s1>0){$sr[$count]="$_\n";++$count};--$s1;if($s1<1){$s=0}}
	}

}

if($typemes==1){$s1=$lng[284];$s2=$lng[285];}
elsif($typemes==2){$s1=$lng[286];$s2=$lng[285];}

for$i(0..@sr){$sr[$i]=~s/a href=/a href=$inip{'dirkonf'}\//;}

extrtime($begin);++$et[4];
$pra="<ul><li>$lng[195] $s1<br>\n<li>$lng[218] [$s2, <i>$et[2]:$et[1]:$et[0] $et[3]/$et[4]/$et[5]</i>]<br>\n<li>$lng[197] $newmes.</ul><p>$inip{'separator'}<p><ul>\n";
$pra.="@sr";
if(!length$sr[0]){$pra.="<li>$lng[226]"};
$pra.="</ul>";

delete $inip{'search'};@inin=keys%inip;
substit($lng[667],$patp{'searchmes'});$lng[667]=~s/[\$%]searched/\n$pra\n/g;
print $lng[667];

exit;


ABOUTX:


substit($lng[668],$patp{'about'});
$lng[668]=~s/\$info/$info/g;
print $lng[668];
exit;



STATIST:

@a=();$names=0;%a=%wtbuser;
while(($s1,$s2)=each%wtbuser){if($s1=~/^id_(.*)/){$a[$names]=$a{"n_$1"}.';;'.$a{"m_$1"}.';;'.$a{"h_$1"}.';;';++$names}}

open NAM,"$data/$wtblast";$last=<NAM>;close NAM;chomp$last;
#open NAM,"$data/$wtbaccess";@acc=<NAM>;close NAM;

$val=0;


if($inip{'userstat'} eq 'on')
{	$prs[$val]="<font size=-1><ul><multicol cols=2 gutter=40>\n";++$val;
	@a=sort @a;
	for$i(0..$#a){($realn[$i],$mails[$i],$ipadd[$i],$s)=split(';;',$a[$i]);}

	for$i(0..$#realn)
	{	if(length $realn[$i]>0)
		{	if(length$mails[$i]){$prs[$val]="<li><a href=\"mailto:$mails[$i]\">$realn[$i]</a>";++$val}else{$prs[$val]="<li>$realn[$i]";++$val}
			if($inip{'ipuserstat'} eq 'on'){$prs[$val]=", <i>$lng[235]: $ipadd[$i]</i>";++$val}else{$prs[$val]="";++$val}
			$prs[$val]="<br>\n";++$val;
		}
	}
	$prs[$val]="</multicol></ul></font>\n";++$val;
	undef @a;
}


$prs[$val]="<p>$inip{'separator'}<p><center>$lng[256]</center><p>";++$val;

# статистика активности форума
open NAM,"$inip{'dirrealkonf'}/$inip{'indname'}";@a=<NAM>;close NAM;chomp @a;
$curtims=$t[5]*372+$t[4]*31+$t[3];
for$i(3..$#a-2)
{	string($a[$i]);
	$mestime=$stp[19]*372+$stp[15]*31+$stp[13];

	if($mestime<=($curtims-$inip{'statdays'})){next}
	++$stat[$inip{'statdays'}-1-$curtims+$mestime];
	$day[$inip{'statdays'}-1-$curtims+$mestime]=$stp[13];
	$mon[$inip{'statdays'}-1-$curtims+$mestime]=$stp[15];
}


for$i(0..@stat){if($max<$stat[$i]){$max=$stat[$i]}}
for$i(0..@stat){$height[$i]=$stat[$i]/($max/200);$stat=$stat+$stat[$i]}

$prs[$val]="<center><table border=0 cellspacing=2 cellpading=0 align=center><tr valign=bottom>";++$val;

for$j(0..$#stat){if(defined $stat[$j]){$max=$j;last}}
for$i($max..$#stat)
{	$max='<td bgcolor=#0000cc align=center><font size=-7 color=#ffff00>.</font></td>';
	$day[$i]=sprintf('%2.2d',$day[$i]);
	$mon[$i]=sprintf('%2.2d',$mon[$i]+1);
	if(not defined $stat[$i]){$day[$i]='-';$mon[$i]='-';$max="<td bgcolor=#aaaaaa align=center><font size=-1 face=Arial>n/a</font></td>"}
	$prs[$val]="<td align=center><font size=-1 face=Arial>$stat[$i]<table border=0 width=30 height=$height[$i]><tr valign=bottom>$max</tr></table>$day[$i]/$mon[$i]</font></td>\n";++$val;
}
$prs[$val]="</tr></table></center><br>
<center><font size=-1>$lng[233] $last.<br>$lng[255] $stat.</font></center>";++$val;


if($inip{'ignorstat'} eq 'on')
{#	open NAM,"$data/$wtbaccess";$i=0;while(<NAM>){chomp;($ignor[$i],$s)=split(';;');++$i;};close NAM;
	$ignor=$wtbuser{'ignor_ip'}.$wtbuser{'stop_ip'};$ignor=~s/^;//;
	@ignor=split(';',$ignor);

	while(($s1,$s2)=each%wtbuser){if($s1=~/^i_(.*)/){$s1=$1;if($s2=~/[!\-]/){$ignor[$#ignor+1]=$a{"n_$s1"}}}}

	if(not defined $#ignor){goto NOTIGNOR}
	$prs[$val]="<p>$inip{'separator'}<p><center>$lng[257]</center><p>$lng[234]<br><font size=-1><ul>\n";++$val;
	for$i(0..$#ignor)
	{	if(!length$ignor[$i]){next}
		$ignor[$i]=~s/!//;$ignor[$i]=~s/-//;
		$prs[$val]="<li>$ignor[$i]<br>\n";++$val;
	}
	$prs[$val]="</ul></font>";++$val;
}


NOTIGNOR:

substit($lng[669],$patp{'statistics'});
$lng[669]=~s/\$statinfo/@prs/g;
print $lng[669];
exit;


FORBIDDEN:

print "<html><title>$lng[29]</title><body><h2>$lng[29]</h2>$endbody";
exit;


HELP:

for $i(0..$#a-1)
{	if($a[$i] eq 'help') {$help=$a[$i+1]}
}
substit($lng[670],$patp{'contexthelp'});
$lng[670]=~s/\$helpstring/$lng[299+$help]/g;
print $lng[670];

exit;




ERROR:
print "<html><title>$lng[188]</title><body>$lng[205] $ended";
exit;

