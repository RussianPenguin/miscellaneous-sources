#!/usr/bin/perl
##############################################################################
# WWWCatalogizer          Version 1.7                                        #
# Copyright 1999 Chemodun chemodun@mail.ru                             	     #
# Created 04/07/99        Last Modified 04/08/99                             #
# Scripts Archive at:     http://www.geocities.com/SiliconValley/Bridge/5323/#
##############################################################################
# COPYRIGHT NOTICE                                                           #
# Copyright 1999 Chemodun           All Rights Reserved.                     #
#                                                                            #
# WWWCatalogizer may be used and modified free of charge by anyone so long as#
# this copyright notice and the comments above remain intact.  By using this #
# code you agree to indemnify Chemodun from any liability that might arise   #
# from it's use.                                                 	     #
#                                                                            #
# Selling the code for this program without prior written consent is         #
# expressly forbidden.  In other words, please ask first before you try and  #
# make money off of my program.                                              #
#                                                                            #
# Obtain permission before redistributing this software over the Internet or #
# in any other medium.  In all cases copyright and header must remain intact.#
##############################################################################
# Define Variables
$wwwhome="/usr/local/apache/home/local/"; #Home directory www server
$indexfile="index.htm";			  #Default index file name
$namedir="";				  #First directory for Catalog
$recurse=1;				  #Use recursive	
$backdir=1;				  #Enable back dir (eq ..)
$namescript='/cgi-bin/catalog.pl';	  #Script name and path 
$online=1;				  #Use online
$defaultcode="win";			  #Default charset(win,koi,dos,iso)	
$description="\.htaccess";		  #Description file name
$charsetdesc="CharsetSourceEnc";	  #Name parameter describes charset in
					  #Description file (CharsetSourceEnc=win)
$usedir=1;				  #Output 1 - dirname & title from index
					  # 0 - only title from index
#
##############################################################################
#
if ($online) {
 $addref=$namescript . "\?catalog\=";
}
else {
 $addref="";
}
if ($ENV{'REQUEST_METHOD'} eq 'GET') {
 @pairs = split(/&/, $ENV{'QUERY_STRING'});
}
elsif ($ENV{'REQUEST_METHOD'} eq 'POST') {
 read(STDIN, $buffer, $ENV{'CONTENT_LENGTH'});
 @pairs = split(/&/, $buffer);
}
else {
# &error('request_method');
}
foreach $pair (@pairs) {
 my($name, $value) = split(/=/, $pair);
 $name =~ tr/+/ /;
 $name =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;
 $value =~ tr/+/ /;
 $value =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;
 $value =~ s/<!--(.|\n)*-->//g;
 $FORM{$name} = $value;
 if ($name eq "catalog") {
   $namedir=$value;
 }
} 
if ($defaultcode eq "win") {
 $charset="windows-1251"; 
}
elsif ($defaultcode eq "koi") {
 $charset="koi8-r"; 
}
elsif ($defaultcode eq "dos") {
 $charset="dos-866"; 
}
elsif ($defaultcode eq "iso") {
 $charset="iso-8859-5"; 
}
print "Content-type: text/html\n\n";
print "<html>\n <head>\n";
print " <title>WWWCatalogizer. Current catalog's $namedir</title>\n";
print "<meta http-equiv=\"Content-Type\" ";
print " content=\"text/html; charset=$charset\">\n";
print "</head>\n <body>\n";
print "<H1>Current catalog's $namedir<\/H1>\n";
print "<ul>\n";
if (($recurse) && ($backdir) && !($namedir eq "")) {
 @tmpdir=split(/\//,$namedir);
 $tmpdir=@tmpdir;
 $ownerdir="";
 for ($i=1;$i < $tmpdir-1;$i++) {
  $ownerdir=$ownerdir . "\/" . @tmpdir[$i];
 }
 print "<li><a href='$addref$ownerdir'>. . Up Level<\/a>\n";   
}
&expand_dir($namedir,$recurse,$defaultcode);
print "<\/ul>\n";
print "<p>";
print "<br> WWWCatalogizer v. 1.7 . Copyright 1999 <a href='mailto:chemodun\@mail.ru'>Chemodun<\/a>. All Rights Reserved. ";
print "</body>\n";
print "</html>";

sub expand_dir {
 my($namedir,$level,$chset)= @_;
 my($workdir,$fn,@fn,$index,@dsc,$dsc,$pname,$pvalue);
 $workdir=$wwwhome . $namedir;
 if (opendir(DIR,"$workdir")) {
  @fn=readdir(DIR);
  closedir(DIR);
  $index="";
  foreach $fn (@fn) {
   if ( $fn =~ m/$description/i ) {
    open(DSC,"$workdir$description");
    @dsc=<DSC>;
    close(DSC);
    foreach $dsc (@dsc) {
     ($pname,$pvalue)=split(/\=/,$dsc);
     if ($pname =~ m/$charsetdesc/i) {
      $pvalue =~ s/\n//;
      $pvalue =~ s/\r//;
      $chset=$pvalue; 
     }
    }
   }
   if ( $fn =~ m/$indexfile/i ) {
    $index=$fn;
   }
  }
  if (($index) && ($level > 1)) {
   if ($usedir) {
    print "<li><a href='$addref$namedir'>$namedir<\/a>\n";   
    print "<ul>\n";
   }
   &expand_title("$namedir",$index,$chset);
   if ($usedir) {
    print "<\/ul>\n";
   }
  }
  else {
   if ($level > 1) {
    print "<li><a href='$addref$namedir'>$namedir<\/a>\n";   
    print "<ul>\n";
   } 
   @fn=sort {
    my($fa)=$a;
    my($fb)=$b;
    my($da,$db,$wa,$wb,$rz); 
    $da=$db=0;
    $wa=$workdir . $fa;
    $wb=$workdir . $fb; 
    if (opendir(TST,$wa)) {
     closedir(TST);
     $da=1;
    }
    if (opendir(TST,$wb)) {
     closedir(TST);
     $db=1;
    }
    if ($da == $db) {
     if ($fa eq $fd) {
      $rz=0;
     }
     elsif ($fa gt $fb){
      $rz=1;
     }
     else {
      $rz=-1;
     }
    }
    elsif ($da) {
     $rz=-1;
    }
    else {
     $rz=1;
    }
    return $rz;
   } @fn;
   foreach $fn (@fn) {
    if (length($fn) > 0) {
     if (!(($fn eq '.') || ($fn eq '..'))) { 
      if (opendir(TST,$workdir . "/" . $fn)) {
       closedir(TST);
       if ($level) {
        &expand_dir("$namedir$fn\/",$level+1,$chset);
       }
       else {
        print "<li><a href='$addref$namedir\/$fn'>Catalog : $fn<\/a>\n";
       }
      }
      else {
       &expand_title($namedir,$fn,$chset);
      }
     }     
    }
   }
   if ($level > 1) {
    print "<\/ul>\n";
   }
  }
 }
}


sub expand_title {
 my($wdir,$wfile,$chset) = @_;
 my($idir,$html,$endfind,$title,$from,$tmpset,$fname);
 $idir=$wwwhome . $wdir;
 $from=$chset;
 if ($wfile =~ /(\D+).htm/i) {
  $fname=$wfile;
  $title="";
  if (open(HTML,"<".$idir . $wfile)) {
   $html=<HTML>;
   $endfind=0;
   while (($html) && ($endfind < 3)) {
    $tmpset=$html;
    if ($tmpset =~ /charset\=/) {
     $tmpset=$';
     if ($tmpset =~ /\'/) {
      $tmpset=$`;
     }
     if ($tmpset =~ /\"/) {
      $tmpset=$`;
     }
     if ($tmpset =~ / /) {
      $tmpset=$`;
     }
     if ($tmpset =~ /\;/) {
      $tmpset=$`;
     }
     if ($tmpset =~ /windows-1251/i) {
      $from="win";
     }
     elsif  ($tmpset =~ /koi8-r/i) {
      $from="koi";
     }
     elsif  ($tmpset =~ /koi8/i) {
      $from="koi";
     }
     elsif  ($tmpset =~ /koi-8/i) {
      $from="koi";
     }
     elsif  ($tmpset =~ /dos-866/i) {
      $from="dos";
     }
     elsif  ($tmpset =~ /iso-8859-5/i) {
      $from="iso";
     }
    }
    if ($endfind == 0) {
     if ($html =~ /<TITLE>/i) {
      $html=$';
      if ($html =~ /<\/TITLE>/i) {
      $html=$`;
      $title=$title . $html;
       $endfind=3;
      }
      else {
       $title=$title . $html;
       $endfind=1;
      } 
     }
    }
    elsif ($endfind == 1) {
     if ($html =~ /<\/TITLE>/i) {
      $html=$`;
      $endfind=2;
     }
     $title=$title . $html;
    }
    if ($html =~ /<BODY>/i) {
     $endfind=3;
    }
    $html=<HTML>;
   }
  }
  $title=$title . " \( " . $fname . " \)";
  if ($from ne $defaultcode) {
   $title=&convert($title,$from,$defaultcode);
  }
  print "<li><a href='\/$wdir$wfile'>$title<\/a>\n";
 }
}

sub convert{
 my($isstr,$from,$to)=@_;
 if ($to eq "koi") {
  if ($from eq "win" ) {
   $isstr =~ tr/ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ¨¸ªº¯¿¡¢°•·v¹¤¦ /áâ÷çäåöúéêëìíîïğòóôõæèãşûıÿùøüàñÁÂ×ÇÄÅÖÚÉÊËÌÍÎÏĞÒÓÔÕÆÈÃŞÛİßÙØÜÀÑ³£™˜“›Ÿ—œ•–¿”š/;
  }
  elsif ($from eq "dos") {
   $isstr =~ tr/€‚ƒ„…†‡ˆ‰Š‹Œ‘’“”•–—˜™š›œŸ ¡¢£¤¥¦§¨©ª«¬­®¯àáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ/áâ÷çäåöúéêëìíîïğòóôõæèãşûıÿùøüàñÁÂ×ÇÄÅÖÚÉÊËÌÍÎÏĞÒÓÔÕÆÈÃŞÛİßÙØÜÀÑ³£™˜“›Ÿ—œ•–¿”š/;
  }
  elsif ($from eq "iso") {
   $isstr =~ tr/°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîï¡ñ£ó¤ô¦ö§÷úûğışÿ/áâ÷çäåöúéêëìíîïğòóôõæèãşûıÿùøüàñÁÂ×ÇÄÅÖÚÉÊËÌÍÎÏĞÒÓÔÕÆÈÃŞÛİßÙØÜÀÑ³£™˜“›Ÿ—œ•–¿”š/;
  }
 }
 elsif ($to eq "win") {
  if ($from eq "koi" ) {
   $isstr =~ tr/áâ÷çäåöúéêëìíîïğòóôõæèãşûıÿùøüàñÁÂ×ÇÄÅÖÚÉÊËÌÍÎÏĞÒÓÔÕÆÈÃŞÛİßÙØÜÀÑ³£™˜“›Ÿ—œ•–¿”š/ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ¨¸ªº¯¿¡¢°•·v¹¤¦ /;
  }
  elsif ($from eq "dos") {
   $isstr =~ tr/€‚ƒ„…†‡ˆ‰Š‹Œ‘’“”•–—˜™š›œŸ ¡¢£¤¥¦§¨©ª«¬­®¯àáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ/ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ¨¸ªº¯¿¡¢°•·v¹¤¦ /;
  }
  elsif ($from eq "iso") {
   $isstr =~ tr/°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîï¡ñ£ó¤ô¦ö§÷úûğışÿ/ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ¨¸ªº¯¿¡¢°•·v¹¤¦ /;
  }
 }
 elsif ($to eq "dos") {
  if ($from eq "koi" ) {
   $isstr =~ tr/áâ÷çäåöúéêëìíîïğòóôõæèãşûıÿùøüàñÁÂ×ÇÄÅÖÚÉÊËÌÍÎÏĞÒÓÔÕÆÈÃŞÛİßÙØÜÀÑ³£™˜“›Ÿ—œ•–¿”š/€‚ƒ„…†‡ˆ‰Š‹Œ‘’“”•–—˜™š›œŸ ¡¢£¤¥¦§¨©ª«¬­®¯àáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ/;
  }
  elsif ($from eq "win") {
   $isstr =~ tr/ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ¨¸ªº¯¿¡¢°•·v¹¤¦ /€‚ƒ„…†‡ˆ‰Š‹Œ‘’“”•–—˜™š›œŸ ¡¢£¤¥¦§¨©ª«¬­®¯àáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ/;
  }
  elsif ($from eq "iso") {
   $isstr =~ tr/°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîï¡ñ£ó¤ô¦ö§÷úûğışÿ/€‚ƒ„…†‡ˆ‰Š‹Œ‘’“”•–—˜™š›œŸ ¡¢£¤¥¦§¨©ª«¬­®¯àáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ/;
  }
 }
 elsif ($to eq "iso") {
  if ($from eq "koi" ) {
   $isstr =~ tr/áâ÷çäåöúéêëìíîïğòóôõæèãşûıÿùøüàñÁÂ×ÇÄÅÖÚÉÊËÌÍÎÏĞÒÓÔÕÆÈÃŞÛİßÙØÜÀÑ³£™˜“›Ÿ—œ•–¿”š/°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîï¡ñ£ó¤ô¦ö§÷úûğışÿ/;
  }
  elsif ($from eq "win") {
   $isstr =~ tr/ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ¨¸ªº¯¿¡¢°•·v¹¤¦ /°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîï¡ñ£ó¤ô¦ö§÷úûğışÿ/;
  }
  elsif ($from eq "dos") {
   $isstr =~ tr/€‚ƒ„…†‡ˆ‰Š‹Œ‘’“”•–—˜™š›œŸ ¡¢£¤¥¦§¨©ª«¬­®¯àáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ/°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîï¡ñ£ó¤ô¦ö§÷úûğışÿ/;
  }
 }
 return $isstr;
}