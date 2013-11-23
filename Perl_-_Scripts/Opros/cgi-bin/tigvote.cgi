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

$tagToTitle="<font face=arial size=3><b>"; # ���� ��� ���������
$tagToRow="<font face=arial size=2><b>"; # ���� ��� �������
$graphLenght=150; # ����� ������������� ���� ������� (� ��������)
$graphWidth=15; # ������ ���� ������� (� ��������)
$submitText="�������������"; # ������� �� ������ �������� �����

$closeIP="yes"; # ����� ���� ����� �� ��� ���������� ��� ����, �������� ������ 
                # ���� "yes". ���� "no" - �� ����� ����� ���������� 
                # �������������� ���������� ���

# ��������!!! ���� �� ���������� ���������� � ������ ������ ��������� ���,
# �� �� ��������� ��� ����� ����������� ������� ���� �� ������� �������!

$showResult="yes"; # ���������� �� ���������� �����������?
$fileName="../vote.txt"; # ���� � ��������� � ������������ ����������� (���� ������������ �������)
$fileIP="ip.txt"; # ���� �� ������� IP ������� (���� ������������ �������)
$pathToImage="../img/"; # ���� � ��������� ��� ����� ������� (���� ������������ �������)
$cgiUrl="http://www.lgg.ru/~tigra/cgi-bin/"; # URL �������� cgi-bin
$body="<BODY bgcolor=#ff8000 VLINK=#501000 LINK=#903000 ALINK=#ffff00 background=../back.jpg TEXT=#000000 bgproperties=fixed><center>";

#=============================================================
# �������� �� ����� ������������

$in = $ENV{'QUERY_STRING'};
if($in eq 'result'){print "Content-Type: text/html\n\n";result();exit;}
if($in eq 'form'){print "Content-Type: text/html\n\n";form();exit;}


#��������� ������ �� ����� � �������� �� ����� ������

read(STDIN, $query, $ENV{'CONTENT_LENGTH'});
@vote=split /=/,$query;


if($query eq ''){print "Content-Type: text/html\n\n";
print "<HTML><HEAD><TITLE>�������� �����!</TITLE></HEAD>$body\n";
print "<br><center><h2>�� ���� ����� �� ��� ������!</h2><h3><a href=$ENV{'HTTP_REFERER'}>���������</a></h3></center>";
print "</BODY></HTML>";
exit;}


# �������� IP

if($closeIP eq 'yes'){IPcheck();}


#�������� ����� � �������

open FILE,"$fileName";
@fil=<FILE>;
close FILE;


#��������� ������

$punkt=@vote[1];
@temp=split /=/,@fil[$punkt];
@temp[1]++;
@fil[$punkt]=join '=',@temp;
@fil[$punkt]=@fil[$punkt]."\n";


#������ ����������� ���������� � ����

open FILE,">$fileName";

for $i(0..$#fil){
print FILE "@fil[$i]";
}

close FILE;


#����� ����� �����������

print "Content-Type: text/html\n\n";
print "<HTML><HEAD><TITLE>�������, ��� ����� ��������.</TITLE></HEAD>$body\n";

print "<h3>�������, ��� ����� ��� ������.</h3>\n";
if($showResult eq 'yes'){result();}
print "<h3><a href=$ENV{'HTTP_REFERER'}>���������</a></h3>\n";

print "</BODY></HTML>";

exit;



#------------------------------------
#������������ ������ �������
#------------------------------------

sub result()
{
open FILE,"$fileName";
@fil=<FILE>;
close FILE;


#��������� ������ �� �����

for $i(1..$#fil){
@temp=split /=/,@fil[$i];
@mess[$i]=@temp[0];@num[$i]=@temp[1];
}

#���������� �������
#���������� �������� ��������, ���������� ������������

$max=0;$sum=0;
for $i(1..$#fil){
$sum=$sum+@num[$i];
if(@num[$i]>$max){$max=@num[$i];}
}
if($max==0){$max=1;}
$koeff=$graphLenght/$max;


#���������� �������

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
#������������ ���������� �����
#------------------------------------
sub form()
{
open FILE,"$fileName";
@fil=<FILE>;
close FILE;


#���������� �����

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
#������������ �������� IP
#------------------------------------
sub IPcheck()
{
open FILE,"$fileIP";
@filip=<FILE>;
close FILE;

chomp(@filip);

$ip=$ENV{'REMOTE_ADDR'};

# �� ������, ���� ����� ���� � ����

for $i(0..$#filip){
if(@filip[$i] eq $ip){print "Content-Type: text/html\n\n";
print "<HTML><HEAD><TITLE>��� ����� �� ������!</TITLE></HEAD>$body\n";

print "<center><h2>��� ����� �� ��� ������, �.�.<br>�� ��� ����������!</h2>";
if($showResult eq 'yes'){result();}
print "<h3><a href=$ENV{'HTTP_REFERER'}>���������</a></h3>\n</center>";

print "</BODY></HTML>\n";exit;}
}

open FILE,">>$fileIP";
print FILE "$ip\n";
close FILE;
}