#!/usr/local/bin/perl
# ^^^^^^^^^^^^^^^^^^^ This is the path to your Perl, in most cases, this will work,
#                     sometimes the admin changes it to something else.
#                     First try using this path, if fails, ask your admin.

#########################################################################
##           Elite Guestbook  v2.19  (c) 2000 Main Central.            ##
##  URL: http://www.MainCentral.com/redir.cgi?goto=egb                 ##
##                                                                     ##
##   Developed on [June 18, 2000]   Updated on [Sep  02, 2000]         ##
##                                                                     ##
#########################################################################
##                                                                     ##
## Description:                                                        ##
##  A superior guestbook program which lets the administrator set up   ##
##  an easy-to-use, and control, guestbook.                            ##
##                                                                     ##
## # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # ##
##                                                                     ##
## Copyright Notice:                                                   ##
##  Copyright (c) 2000 Main Central. All Rights Reserved.              ##
##                                                                     ##
##  This script may be used and/or modified as long as you do not      ##
##  change this header, and leave it remaining above all other         ##
##  headers.                                                           ##
##                                                                     ##
##  Selling, renting, leasing, etc of the script and/or "snippets" of  ##
##  this script without prior written consent from Main Central is     ##
##  strictly prohibited.                                               ##
##                                                                     ##
##                                                                     ##
## This script was created in hope that it may be useful to you,       ##
## but is WITHOUT ANY WARRANTY; AS IS                                  ##
##                                                                     ##
## ## END OF HEADER ## ## END OF HEADER ## ## END OF HEADER ## ## END ###
#########################################################################

use CGI qw(:standard);

print "Content-Type: text/html\n\n";
#****************  Configuration  ***************************************************************#

#Title of your guestbook
$title = "My guestbook";

#Title of your site
$sitetitle = "My really cool site";

#URL of your web site
$siteurl = "http://www.domainname.com/";

#-- Template directory - absolute path, NOT URL! - No "/" at end!
$tempdir = "/usr/blah/http/something";

#-- Message Data directory - absolute path, NOT URL! - No "/" at end!
$datadir = "/usr/blah/http/something";

#-- Where the egb.cgi resides - URL, NOT absolute path! - Including egb.cgi
$egburl = "http://www.YOURDOMAIN.com/cgi-bin/egb.cgi";

#-- Bad words - Will replace the bad words with <CENSORED>'s
@badwords = ('bitch','butt','dick');

#-- Use flock'ing? - Some servers do NOT allow this, set to "no" if you server doesn't allow this.
$lock = "yes";

#-- Check by admin first? - read readme.txt for more information
$admincheck = "no";

#-- Administration password - to check/change guest book
$adminpass = "fifi";

#-- Notify when posted - If your site is popular, it may cause your e-mail account to flood - read readme.txt for more information.
$notify = "yes";

#-- Place where Sendmail is installed - Not needed if $notify is "no"
$mailprog = "/usr/sbin/sendmail";

#-- Notify To:
$to = "webmaster\@YOURDOMAIN.com"; # Don't forget to escape the @ sign!

#-- Subject of notification letter
$sub = "Someone posted a message in the guestbook.";

#-- Notify From:
$frm = "webmaster\@YOURDOMAIN.com";

#How long it will take you to review the messages
$days = "3"; # "... x days ..."

#How many message you wish to display per page. (admin and public)
$messagesperpage = 20;

#New messages to on [top] / [bottom] (admin and public)
$newmessages = 'top';

#-- Index Options - -------- "yes" / "no"

#Warn about logging IP's?
$ipwarn = "yes";

$sip = "yes";		#Show IP
$stop = "yes";		#Show time and date of posting

$rname = "yes";		#Require name
$sname = "yes";		#Show name
$mname = "24";		#Max characters a name may be

$remail = "yes";	#Require email
$semail = "yes";	#Show E-mail
$memail = "52";		#Max characters an e-mail may be

$srefer = "yes";	#Show how they got to your site

$rhomepage = "yes";	#Require home page
$surl = "yes";		#Show home page info
$murl = "100";		#Max characters a URL may be

$rtitle = "yes";	#Require homepage title
$mtitle = "70";		#Max characters a title may have

$rmsg = "yes";		#Require a message
$smsg = "yes";		#Show message - I don't know why, but why not?
$mmsg = "300";		#Max characters a message may be

#**************** That's It! - END to configuration! - Do not modify anything below.*************#
#
#                  If you want this script to work, DO NOT EDIT BELOW THIS LINE.
#-------------------------------------------------------------------------------------------------

$action = param("action");
$pass = param('pass');
$mode = param('mode');
$ac = param('ac');


if ($action eq "") { &ShowGuestbook; exit; }
if ($action eq "post") { &ShowPost; exit; }
if ($action eq "Post It") { &DoPost; exit; }
if (($action eq "admin") && (($pass ne $adminpass) || !$pass)) { &AdminLogin; exit; }
if ((($action eq "admin") && ($pass eq "$adminpass")) && ($mode eq "")) { &Correct; exit; }
if ((($action eq "admin") && ($pass eq "$adminpass")) && ($mode eq "check") && ($ac eq "")) { &ShowCheckList; exit; }
if ((($action eq "admin") && ($pass eq "$adminpass")) && ($mode eq "check") && ($ac eq "accept")) { &Accept; exit; }
if ((($action eq "admin") && ($pass eq "$adminpass")) && ($mode eq "check") && ($ac eq "reject")) { &Reject; exit; }


if ((($action eq "admin") && ($pass eq "$adminpass")) && ($mode eq "ed") && ($ac eq "")) { &EdShowList; exit; }
if ((($action eq "admin") && ($pass eq "$adminpass")) && ($mode eq "ed") && ($ac eq "accept")) { &EdAccept; exit; }
if ((($action eq "admin") && ($pass eq "$adminpass")) && ($mode eq "ed") && ($ac eq "reject")) { &EdReject; exit; }
&ShowGuestbook;
exit;

sub Reject {
	$mid = param('mid');
	$msg = "Message has been rejected.";
	&DelMsg;
	&ShowCheckList;
}
sub Accept {
	$mid = param('mid');
	&DelMsg;
	$admincheck="admin";
	$ip = param('ip');
	$ptime = param('top');
	&DoPost;
	$msg = "Message has been added.";
	&ShowCheckList;
}
sub EdAccept {
	$mid = param('mid');
	&EdDelMsg;
	$admincheck="admin";
	$ip = param('ip');
	$ptime = param('top');
	$msg = "Message has been edited.";
	&EdShowList;
}
sub EdReject {
	$mid = param('mid');
	$msg = "Message has been deleted.";
	&EdDelMsg;
	&EdShowList;
}
sub DelMsg {
	$total = 0;
	open (DATA, "$datadir/egb-check.txt") || do { &Error("Could not open $datadir/egb-check.txt check file. Error: $!"); };
	&lockf;
	while (<DATA>) {
		$total++;
		$ln = $_;
		if ($total != $mid) { push(@repr, $ln); }
	}
	close(DATA);
	open (DATA, ">$datadir/egb-check.txt") || do { &Error("Could not open $datadir/egb-check.txt to rewrite file. Error: $!"); };
	&lockf;
	print DATA @repr;
	close(DATA);
	$repr = "";
}
sub EdDelMsg {
	$total = 0;
	open (DATA, "$datadir/egb-data.txt") || do { &Error("Could not open $datadir/egb-data.txt message file. Error: $!"); };
	&lockf;
	while (<DATA>) {
		$total++;
		$ln = $_;
		if ($total != $mid) { push(@repr, $ln); }
		if ($total == $mid) {
			if ($ac eq "accept") {
				$ip = param('ip');
				$ptime = param('top');
				$pname = param("name");
				$pemail = param("email");
				$prefer = param("refer");
				$ptitle = param("title");
				$purl = param("url");
				$pmsg = param("message");
				$pmsg =~ s/\>/\&gt\;/ig;	$pmsg =~ s/\</\&lt\;/ig;
				$pmsg =~ s/\n/>E/ig; 		$pmsg =~ s/\>\>/\>G/ig;		$pmsg =~ s/[^\w\d\W]//ig;
				$pname =~ s/\>/\&gt\;/ig;	$pname =~ s/\</\&lt\;/ig;
				$pname =~ s/\n/>E/ig;		$pname =~ s/\>\>/\>G/ig;	$pname =~ s/[^\w\d\W]//ig;
				$pemail =~ s/\>/\&gt\;/ig;	$pemail =~ s/\</\&lt\;/ig;
				$pemail =~ s/\n/>E/ig;		$pemail =~ s/\>\>/\>G/ig;	$pemail =~ s/[^\w\d\W]//ig;
				$prefer =~ s/\>/\&gt\;/ig;	$prefer =~ s/\</\&lt\;/ig;
				$prefer =~ s/\n/>E/ig;		$prefer =~ s/\>\>/\>G/ig;	$prefer =~ s/[^\w\d\W]//ig;
				$ptitle =~ s/\>/\&gt\;/ig;	$ptitle =~ s/\</\&lt\;/ig;
				$ptitle =~ s/\n/>E/ig;		$ptitle =~ s/\>\>/\>G/ig;	$ptitle =~ s/[^\w\d\W]//ig;
				$purl =~ s/\>/\&gt\;/ig;	$purl =~ s/\</\&lt\;/ig;
				$purl =~ s/\n/>E/ig;		$purl =~ s/\>\>/\>G/ig;		$purl =~ s/[^\w\d\W]//ig;

				push(@repr, "$pname>>$pemail>>$prefer>>$ip>>$ptitle>>$purl>>$pmsg>>$ptime\n");
			}
		}
	}
	close(DATA);
	open (DATA, ">$datadir/egb-data.txt") || do { &Error("Could not open $datadir/egb-data.txt to rewrite file. Error: $!"); };
	&lockf;
	print DATA @repr;
	close(DATA);
	$repr = "";
}
sub ShowCheckList {
	$output = &load("$tempdir/egb-admincheck.html");
	$output =~ s/\$title/$title/ig;
	$output =~ s/\$egburl/$egburl/ig;
	$output =~ s/\$pass/$pass/ig;
	&LoadCheck;
	$output =~ s/\$guestbook/$wt/ig;
	$output =~ s/\$total/$total/ig;
	$output =~ s/\$msg/$msg/ig;
	print $output;
}
sub EdShowList {
	$output = &load("$tempdir/egb-admined.html");
	$output =~ s/\$title/$title/ig;
	$output =~ s/\$egburl/$egburl/ig;
	$output =~ s/\$pass/$pass/ig;
	&LoadEd;
	$output =~ s/\$guestbook/$wt/ig;
	$output =~ s/\$total/$total/ig;
	$output =~ s/\$msg/$msg/ig;
	print $output;
}
sub Correct {
	$output = &load("$tempdir/egb-admin.html");
	$output =~ s/\$egburl/$egburl/ig;
	$output =~ s/\$title/$title/ig;
	$output =~ s/\$pass/$pass/ig;
	print $output;
}
sub AdminLogin {
	$output = &load("$tempdir/egb-adminlogin.html");
	$output =~ s/\$egburl/$egburl/ig;
	$output =~ s/\$title/$title/ig;
	print $output;
}
sub DoPost {
	$ip = $ENV{'REMOTE_ADDR'} unless ($ip);
	$pname = param("name") unless ($pname);
	$pemail = param("email") unless ($pemail);
	$prefer = param("refer") unless ($prefer);
	$ptitle = param("title") unless ($ptitle);
	$purl = param("url") unless ($purl);
	$pmsg = param("message") unless ($pmsg);
	$ptime = localtime(time) unless ($ptime);
	foreach (@bad) {
		$pmsg =~ s/$_/\&lt\;CENSORED&gt\;/ig;
	}
	if ($admincheck ne "admin") {
		if (($rname eq "yes") && ((length($pname) > $mname) || (!$pname))) { &PError("<STRONG>Name:</STRONG> Required - Max length: $mname"); }
		if (($remail eq "yes") && ((length($pemail) > $memail) || (!$pemail))) { &PError("<STRONG>E-mail:</STRONG> Required - Max length: $memail"); }
		if (($rhomepage eq "yes") && ((length($ptitle) > $mtitle) || (!$ptitle))) { &PError("<STRONG>Homepage Title:</STRONG> Required - Max length: $mtitle"); }
		if (($rhomepage eq "yes") && ((length($purl) > $murl) || (!$purl))) { &PError("<STRONG>Homepage:</STRONG> Required - Max length: $murl"); }
		if (($rmsg eq "yes") && ((length($pmsg) > $mmsg) || (!$pmsg))) { &PError("<STRONG>Message:</STRONG> Required - Max length: $mmsg"); }
	}
	if ($error) { &ShowPost; exit; }
	if ($admincheck ne "admin") { &Notify; }

	$pmsg =~ s/\>/\&gt\;/ig;	$pmsg =~ s/\</\&lt\;/ig;
	$pmsg =~ s/\n/>E/ig; 		$pmsg =~ s/\>\>/\>G/ig;		$pmsg =~ s/[^\w\d\W]//ig;
	$pname =~ s/\>/\&gt\;/ig;	$pname =~ s/\</\&lt\;/ig;
	$pname =~ s/\n/>E/ig;		$pname =~ s/\>\>/\>G/ig;	$pname =~ s/[^\w\d\W]//ig;
	$pemail =~ s/\>/\&gt\;/ig;	$pemail =~ s/\</\&lt\;/ig;
	$pemail =~ s/\n/>E/ig;		$pemail =~ s/\>\>/\>G/ig;	$pemail =~ s/[^\w\d\W]//ig;
	$prefer =~ s/\>/\&gt\;/ig;	$prefer =~ s/\</\&lt\;/ig;
	$prefer =~ s/\n/>E/ig;		$prefer =~ s/\>\>/\>G/ig;	$prefer =~ s/[^\w\d\W]//ig;
	$ptitle =~ s/\>/\&gt\;/ig;	$ptitle =~ s/\</\&lt\;/ig;
	$ptitle =~ s/\n/>E/ig;		$ptitle =~ s/\>\>/\>G/ig;	$ptitle =~ s/[^\w\d\W]//ig;
	$purl =~ s/\>/\&gt\;/ig;	$purl =~ s/\</\&lt\;/ig;
	$purl =~ s/\n/>E/ig;		$purl =~ s/\>\>/\>G/ig;		$purl =~ s/[^\w\d\W]//ig;
	

	if ($admincheck eq "yes") {
		if ($newmessages eq 'top') {
			if (!-e "$datadir/egb-check.txt") { 
				open (DATA, ">>$datadir/egb-check.txt") || do { &Error("Unable to create $datadir/egb-check.txt.  Please either create it manually, or make sure directory permission is correctly set."); };
				close(DATA);
			}
			open (DATA, "<$datadir/egb-check.txt") || do { &Error("Unable to read $datadir/egb-check.txt to add message [1]. Error: $!"); };
			&lockf;
			@file = <DATA>;
			close(DATA);
		}
		else { $append = ">"; }
		open (DATA, ">$datadir/egb-check.txt") || do { &Error("Unable to open $datadir/egb-check.txt to add message. Error: $!"); };
		&lockf;
		print DATA "$pname>>$pemail>>$prefer>>$ip>>$ptitle>>$purl>>$pmsg>>$ptime\n";
		if ($newmessages eq 'top') {
			foreach (@file) {
				print DATA $_;
			}
		}
		close(DATA);
	}
	else {
		if ($newmessages eq 'top') {
			open (DATA, "<$datadir/egb-data.txt") || do { &Error("Unable to read $datadir/egb-data.txt to add message [1]. Error: $!"); };
			&lockf;
			@file = <DATA>;
			close(DATA);
			
		}
		else { $append = ">"; }
		open (DATA, ">$append$datadir/egb-data.txt") || do { &Error("Unable to open $datadir/egb-data.txt to add message. Error: $!"); };
		&lockf;
		print DATA "$pname>>$pemail>>$prefer>>$ip>>$ptitle>>$purl>>$pmsg>>$ptime\n";
		if ($newmessages eq 'top') {
			foreach (@file) {
				print DATA $_;
			}
		}
		close(DATA);
	}
	if ($admincheck ne "admin") { &ShowThanks; }
}
sub ShowThanks {
	$output = &load("$tempdir/egb-thx.html");
	$output =~ s/\$sitetitle/$sitetitle/ig;
	$output =~ s/\$siteurl/$siteurl/ig;
	$output =~ s/\$egburl/$egburl/ig;
	$output =~ s/\$title/$title/ig;
	$output =~ s/\$days/$days/ig;
	print $output;
}
sub Notify {
	if ($notify eq "yes") {
		open(MAIL,"|$mailprog -t");
		print MAIL "From: $frm\n";
		print MAIL "To: $to\n";
		print MAIL "Subject: $sub\nContent-Type: text/plain\n\n";
		print MAIL "Hi, I am the notification robot for your guestbook located at $egburl\n";
		print MAIL "I am e-mailing you to notify of a new message.\n";
		if ($admincheck eq "yes") { $nmsg = "This message has not been posted in the guestbook.  It is waiting for your verification.\nTo verify this, or any waiting messages, goto <a href=\"$egburl?action=admin\">$egburl?action=admin</a>"; }
		else { $nmsg = "This message has been posted in the guestbook and can be viewed by all people.  To edit/delete this message, goto <a href=\"$egburl?action=admin\">$egburl?action=admin</a>"; }

print MAIL <<"EOM";
$nmsg

The person posted the following:
Posted at:		$ptime
Name:			$pname
E-mail:			$pemail
Referred by:	$prefer
IP:				$ip

Title of site:	<A href="$purl">$ptitle</a>
URL of site:	<A href="$purl">$purl</a>
Message:
$pmsg

EOM
		close(MAIL);
	}
}
sub ShowPost {
	$ip = $ENV{'REMOTE_ADDR'};
	$output = &load("$tempdir/egb-post.html");
	$output =~ s/\$title/$title/ig;
	$output =~ s/\$egburl/$egburl/ig;
	$logip = "";
	$logip = "IP addresses logged! ($ip)" if ($ipwarn eq "yes");
	$output =~ s/\$logip/$logip/ig;
	$output =~ s/\$error/$error/ig;
	print $output;
}
sub ShowGuestbook {
	$output = &load("$tempdir/egb.html");
	$output =~ s/\$title/$title/ig;
	$output =~ s/\$egburl/$egburl/ig;
	&LoadGuestbook;
	$output =~ s/\$guestbook/$wt/ig;
	$output =~ s/\$total/$total/ig;
	print $output;
}
sub LoadGuestbook {
	$total = 0;
	if (!-e "$datadir/egb-data.txt") {
		open (DATA, ">>$datadir/egb-data.txt") || do { &Error("Could not create $datadir/egb-data.txt message data file. Error: $!"); };
		&lockf;
		print DATA "";
		close(DATA);
	}
	open (DATA, "$datadir/egb-data.txt") || do { &Error("An error occurred when opening the message data file."); exit; };
	&lockf;
	while (<DATA>) {
		@s = split /\>\>/;
		$total++;
		if (int($total / 14) == ($total/14)) { print <<"EOM";	
		<font face="Arial"><small><small>This guestbook is powered by <strong><a href="http://www.MainCentral.com/redir.cgi?goto=egb">Elite GuestBook</a></strong></small></small><small><small>provided free by <strong><a href="http://www.MainCentral.com/">www.MainCentral.com</a></strong></small></small></font> # DO NOT REMOVE THIS HEADER!
EOM
		}
		#Do NOT alter, or remove the lines above, if you do, you will be prosecuted to the maximum extent of the law
		&ATT;
	}
	close(DATA);
}

sub ATT {
	$s[0] =~ s/\>E/\<BR\>\n/ig;	$s[0] =~ s/>G/\&gt\;&gt\;/ig;
	$s[1] =~ s/\>E/\<BR\>\n/ig;	$s[1] =~ s/>G/\&gt\;&gt\;/ig;
	$s[2] =~ s/\>E/\<BR\>\n/ig;	$s[2] =~ s/>G/\&gt\;&gt\;/ig;
	$s[3] =~ s/\>E/\<BR\>\n/ig;	$s[3] =~ s/>G/\&gt\;&gt\;/ig;
	$s[4] =~ s/\>E/\<BR\>\n/ig;	$s[4] =~ s/>G/\&gt\;&gt\;/ig;
	$s[5] =~ s/\>E/\<BR\>\n/ig;	$s[5] =~ s/>G/\&gt\;&gt\;/ig;
	$s[6] =~ s/\>E/\<BR\>\n/ig;	$s[6] =~ s/>G/\&gt\;&gt\;/ig;

	$name = @s[0];	$email = @s[1];		$refer = @s[2];
	$ip = @s[3];	$homepage = @s[4];	$homepageurl = @s[5];
	$message = @s[6];	$top = @s[7];
	$name = "&lt;Disabled&gt;" if ($sname ne "yes");
	$email = "&lt;Disabled&gt;" if ($semail ne "yes");
	$refer = "&lt;Disabled&gt;" if ($srefer ne "yes");
	$ip = "&lt;Disabled&gt;" if ($sip ne "yes");
	$homepage = "&lt;Disabled&gt;" if ($shomepage ne "yes");
	$homepageurl = "http://www.MainCentral.com/" if ($shomepage ne "yes");
	$message = "&lt;Disabled&gt;" if ($smsg ne "yes");
	$top = "&lt;Disabled&gt;" if ($stop ne "yes");

$wt .= <<"EOM";
  <tr>
    <td width="100%"><table border="1" cellpadding="0" cellspacing="0" width="100%">
      <tr>
        <td width="50%">
            <table border="0" cellpadding="0" cellspacing="0" width="100%"
        bgcolor="#FFFF80">
              <tr> 
                <td width="25%"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><small>Name:</small></font></td>
                <td width="75%"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><small>$name</small></font></td>
              </tr>
            </table>
        </td>
        <td width="50%">
            <table border="0" cellpadding="0" cellspacing="0" width="100%"
        bgcolor="#FFDFEF">
              <tr> 
                <td width="25%"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><small>Email:</small></font></td>
                <td width="75%"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><small><a href="mailto:$email">$email</a></small></font></td>
              </tr>
            </table>
        </td>
      </tr>
      <tr>
        <td width="50%">
            <table border="0" cellpadding="0" cellspacing="0" width="100%"
        bgcolor="#B9FFDC">
              <tr> 
                <td width="25%"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><small>Refer:</small></font></td>
                <td width="75%"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><small>$refer</small></font></td>
              </tr>
            </table>
        </td>
        <td width="50%">
            <table border="0" cellpadding="0" cellspacing="0" width="100%"
        bgcolor="#D5EAFF">
              <tr> 
                <td width="25%"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><small>IP 
                  Address:</small></font></td>
                <td width="75%"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><small>$ip</small></font></td>
              </tr>
            </table>
        </td>
      </tr>
      <tr>
        <td width="50%">
            <table border="0" cellpadding="0" cellspacing="0" width="100%"
        bgcolor="#FFDFDF">
              <tr> 
                <td width="25%"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><small>Homepage:</small></font></td>
                <td width="75%"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><small><a href="$homepageurl" target="_blank">$homepage</a></small></font></td>
              </tr>
            </table>
        </td>
        <td width="50%">
            <table border="0" cellpadding="0" cellspacing="0" width="100%"
        bgcolor="#DEEFEF">
              <tr> 
                <td width="25%"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><small>Posted:</small></font></td>
                <td width="75%"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><small>$top</small></font></td>
              </tr>
            </table>
        </td>
      </tr>
    </table>
    </td>
  </tr>
  <tr>
    <td width="100%"><table border="0" cellpadding="0" cellspacing="0" width="100%">
      <tr>
          <td width="100%"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><small>Message:<br>
            $message</small></font></td>
      </tr>
    </table>
    </td>
  </tr>
EOM
}
sub load {
	my $file = shift;
	my $fl;
	open(INPUT, "<$file") || do { &Error("An error occured when trying to open template file. Please try again in 10 minutes. $file Error: $!"); };
	undef $/;
	$fl = (<INPUT>);
	$/ = "\n";
	close(INPUT);
	return $fl;
}
sub lockf {
	if ($lock eq "yes") {
		local($TrysLeft) = 1500;
		while ($TrysLeft--) {
			select(undef,undef,undef,0.01);
			if ($switch != 1) {	(flock(DATA,6)) || next; }
			last;
		}
		unless ($TrysLeft >= 0) {
			&Error("Could not hold file open, please try again in 10 minutes.");
		}
	}
}
sub Error {
	$msg = $_[0];
	print "$msg";
	exit;
}
sub PError { $error .= "<BR>$_[0]"; }
sub LoadCheck {
	my $mpg = $messagesperpage;
	$start = param('start');
	$start = 0 if (!$start);
	$total = 0;
	if (!-e "$datadir/egb-check.txt") {
		open (DATA, ">>$datadir/egb-check.txt") || do { &Error("Could not create $datadir/egb-check.txt message data file. Error: $!"); };
		&lockf;
		print DATA "";
		close(DATA);
	}
	open (DATA, "$datadir/egb-check.txt") || do { &Error("An error occurred when opening the message check file. ($datadir/egb-check.txt) Error: $!"); exit; };
	&lockf;
	while (<DATA>) {
		if (($start == 0) && ($mpg != 0)) {
			@s = split /\>\>/;
			$total++;
			$mpg--;
			&AATT;
		}
		elsif ($start > 0) { $start-- }
		elsif ($mpg == 0) { last }
	}
	close(DATA);
}
sub LoadEd {
	$total = 0;
	my $mpg = $messagesperpage;
	$start = param('start');
	$start = 0 if (!$start);
	if (!-e "$datadir/egb-data.txt") {
		open (DATA, ">>$datadir/egb-data.txt") || do { &Error("Could not create $datadir/egb-data.txt message data file. Error: $!"); };
		&lockf;
		print DATA "";
		close(DATA);
	}
	open (DATA, "$datadir/egb-data.txt") || do { &Error("An error occurred when opening the message data file. ($datadir/egb-data.txt) Error: $!"); exit; };
	&lockf;
	while (<DATA>) {
		if (($start == 0) && ($mpg != 0)) {
			@s = split /\>\>/;
			$total++;
			$mpg--;
			&AATT;
		}
		elsif ($start > 0) { $start-- }
		elsif ($mpg == 0) { last }
	}
	close(DATA);
}
sub AATT {
	$s[0] =~ s/>E/\n/ig;	$s[0] =~ s/>G/>>/ig;
	$s[1] =~ s/>E/\n/ig;	$s[1] =~ s/>G/>>/ig;
	$s[2] =~ s/>E/\n/ig;	$s[2] =~ s/>G/>>/ig;
	$s[3] =~ s/>E/\n/ig;	$s[3] =~ s/>G/>>/ig;
	$s[4] =~ s/>E/\n/ig;	$s[4] =~ s/>G/>>/ig;
	$s[5] =~ s/>E/\n/ig;	$s[5] =~ s/>G/>>/ig;
	$s[6] =~ s/>E/\n/ig;	$s[6] =~ s/>G/>>/ig;

	$name = @s[0];	$email = @s[1];		$refer = @s[2];
	$ip = @s[3];	$homepage = @s[4];	$homepageurl = @s[5];
	$message = @s[6];	$top = @s[7];


$wt .= <<"EOM";
<form method="POST" action="$egburl">
  <input type="hidden" name="action" value="admin"><input type="hidden" name="mid"
  value="$total"><input type="hidden" name="mode" value="$mode"><input type="hidden"
  name="pass" value="$pass"><table border="0" cellpadding="0" cellspacing="0" width="100%">
    <tr>
      <td width="100%"><table border="1" cellpadding="0" cellspacing="0" width="100%">
        <tr>
          <td width="50%"><table border="0" cellpadding="0" cellspacing="0" width="100%"
          bgcolor="#FFFF80">
            <tr>
              <td width="25%"><font face="Arial"><small>Name:</small></font></td>
              <td width="75%"><font face="Arial"><input type="text" name="name" size="20" value="$name"></font></td>
            </tr>
          </table>
          </td>
          <td width="50%"><table border="0" cellpadding="0" cellspacing="0" width="100%"
          bgcolor="#FFDFEF">
            <tr>
              <td width="25%"><font face="Arial"><small>E-mail:</small></font></td>
              <td width="75%"><font face="Arial"><input type="text" name="email" size="20"
              value="$email"></font></td>
            </tr>
          </table>
          </td>
        </tr>
        <tr>
          <td width="50%"><table border="0" cellpadding="0" cellspacing="0" width="100%"
          bgcolor="#B9FFDC">
            <tr>
              <td width="25%"><font face="Arial"><small>Got here by:</small></font></td>
              <td width="75%"><font face="Arial"><input type="text" name="refer" size="20"
              value="$refer"></font></td>
            </tr>
          </table>
          </td>
          <td width="50%"><table border="0" cellpadding="0" cellspacing="0" width="100%"
          bgcolor="#D5EAFF">
            <tr>
              <td width="25%"><font face="Arial"><small>IP Address:</small></font></td>
              <td width="75%"><font face="Arial"><input type="text" name="ip" size="20" value="$ip"></font></td>
            </tr>
          </table>
          </td>
        </tr>
        <tr>
          <td width="50%"><table border="0" cellpadding="0" cellspacing="0" width="100%"
          bgcolor="#FFDFDF">
            <tr>
              <td width="25%"><font face="Arial"><small>Homepage URL:</small></font></td>
              <td width="75%"><font face="Arial"><input type="text" name="url" size="20"
              value="$homepageurl"></font></td>
            </tr>
            <tr>
              <td width="25%"><font face="Arial"><small>Title:</small></font></td>
              <td width="75%"><font face="Arial"><input type="text" name="title" size="20"
              value="$homepage"></font></td>
            </tr>
          </table>
          </td>
          <td width="50%"><table border="0" cellpadding="0" cellspacing="0" width="100%"
          bgcolor="#DEEFEF">
            <tr>
              <td width="25%"><font face="Arial"><small>Posted:</small></font></td>
              <td width="75%"><font face="Arial"><input type="text" name="top" size="20" value="$top"></font></td>
            </tr>
          </table>
          </td>
        </tr>
      </table>
      </td>
    </tr>
    <tr>
      <td width="100%"><table border="0" cellpadding="0" cellspacing="0" width="100%">
        <tr>
          <td width="80%"><font face="Arial"><small>Message:<br>
          </small></font><textarea rows="4" name="message" cols="52">$message</textarea></td>
          <td width="20%"><small><font face="Arial"><input type="radio" value="accept" checked
          name="ac">Accept / Edit<input type="radio" name="ac" value="reject">Reject / Delete<br>
          <input type="submit" value="Submit"><input type="reset" value="Reset" name="B2"></font></small></td>
        </tr>
      </table>
      </td>
    </tr>
  </table>
</form>
EOM
}