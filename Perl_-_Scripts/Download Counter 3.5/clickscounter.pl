#!/usr/bin/perl
##############################################################################
# Clicks Counter: Download Counter           Version 3.5                     #
# Copyright 2000, MitriDAT                info@mitridat.com                  #
#                                        http://www.mitridat.com             #
# Created 03.04.2000                    Last Modified 02.03.2001             #
##############################################################################
# COPYRIGHT NOTICE                                                           #
# Copyright 2000, MitriDAT All Rights Reserved.                              #
#                                                                            #
# Please check the ReadMe folder for full details on installation            #
# and registration.                                                          #
##############################################################################

##############################################################################
#                             Variable Defention 
#
# $filename - the name of the log file. 
#
# $main_dir - the location of the log file.  You must
#             have the full path.  If you are unsure what it is
#	      contact your server admin.
#
# $autoadd - decides wether or not to automatically
#	     add links that are not in the database.
#	       1 = on      2 = off
#
# $view_log - The password you wish to use to view the
#	      log file online so clickscounter.cgi?view=whatever you 
#	      chose for this string.  In this script it is set-up
#             to use test so you would use clickscounter.cgi?view=password
#

##############################################################################
#                             Start Variables
$filename = 'clicks-counter.log';
$main_dir = '.';
$autoadd=1;  
$view_log='password';
#                               End Variable
##############################################################################


#*********************** DO NOT EDIT PAST THIS LINE *************************#

require 5;
use LWP::Simple;

&FormInput(*input);


################################
# Some Default Set Variables
################################

$addnew=0;
$totalclicks=0;

$lock = "$main_dir/clickcount_lock.lock";


####################
# Set Lock File
####################

if ($input{'view'} ne $view_log) 
  {
	&SetLock;
  }


####################
# Read in Data File
####################

open(DATA,"$main_dir/$filename");
   @lines = <DATA>;
close(DATA);


#####################
# View Log
#####################
if ($input{'view'} eq $view_log) 
  {
	$spacing = "&nbsp;&nbsp;&nbsp;&nbsp;";

	print "HTTP/1.0 200 OK\n" if $ENV{PERLXS} eq "PerlIS";
	print "Content-type: text/html\n\n";

	print "<html>\n";
	print "<title>Clicks Counter Log Viewer</title>\n";
	print "<body bgcolor=FFFFFF>\n";
	print "<center>\n";
	print "<h1>Clicks Counter Log Viewer</h1>\n";
	print "<table border=1>\n";
	print "<tr><td colspan=1 bgcolor=\"ADADAD\">$spacing<u><strong>URL/Link</strong></u>$spacing</td>\n";
	print "<td colspan=1 bgcolor=\"ADADAD\">$spacing<strong><u>Clicks/Hits</strong></u> $spacing</td></tr>\n";

	foreach $line (@lines)
  	  {
		($link_url1, $link_count1) = split(/\|/,$line);
  		print "<tr><td bgcolor=\"E6E6E6\" align=left>$link_url1 $spacing</td>\n";
		print "<td bgcolor=\"D4D4D4\" align=right>$spacing $link_count1</td></tr>\n";
		$totalclicks = $totalclicks + $link_count1;
  	  }

	print "</table>\n";
	print "<p>Total Clicks/Hits: $totalclicks</p>\n";
	print "<hr width=\"200\">\n";
	print "<p><b>UnRegistered Version!<br>Shareware limitation:</b> The unregistered version of this script <br>will pop up new window with certain site at the definite frequency. <br>Exampe: every 5-th click will be pop uped new window with MitriDAT web site.<br><b><a href=\"http://www.mitridat.com/products-ordering-information.html\">Click here to Order Now!</a><br>Read \"ReadMe\" for more information.</b></p>\n";
	print "<br><em>Clicks Counter Ver. 3.5</em>\n";                                                                                                                                        
	print "<br>&copy; 2000 <a href=\"http://www.mitridat.com/\">MitriDAT</a>";
	print "</center>\n";
	print "</body>\n";
	print "</html>\n";
  }  

	

#####################
# Count Incrementing
#####################

else
  {

	open(DATA,">$main_dir/$filename");
	  foreach $line (@lines)
	  {
	  	($link_url1, $link_count1) = split(/\|/,$line);
	  	if ($input{'url'} eq $link_url1) 
		  {
			$link_count1++;
		 	print DATA ("$link_url1|$link_count1\n");
		 	$addnew=1;
	  	  }
	      else 
	  	  {
			print DATA $line;
	  	  }
		 $totalclicks = $totalclicks + $link_count1;
	  }


	#####################
	# Auto Add entry
	#####################

	if ($addnew == 0 && $autoadd == 1)
	  {
		print DATA ("$input{'url'}|1\n");
	  }
	 &EndLock;


	#####################
	# Close Log File
	#####################

	close(DATA);



	#####################
	# Go to URL
	#####################

	if ($input{'url'} !~ m?://?)
	{
		$input{'url'} = "http://" . $input{'url'};
	}
	print "HTTP/1.0 302 Temporary Redirection\r\n" if $ENV{PERLXS} eq "PerlIS";
	print "Content-type: text/html\n\n";

	if ($totalclicks > 20)
	{
		$AdvURL = 'http://www.mitridat.com/adv/cc.txt';
		my $fullpage = get $AdvURL;
	  	($probability, $page) = split(/\|/,$fullpage);

		if ((int($totalclicks / $probability) * $probability) == $totalclicks)
		{
			print "<script language=\"JavaScript\">";
			print "window.open(\"$page\", \"AdvWin\");";
			print "</script>";
		}
	}

	print "<meta http-equiv=\"refresh\" content=\"0; URL=$input{'url'}\">";
		
  } # Closes Else for View Log

	exit;


#*************************************************************
# function: FormInput
#*************************************************************

sub FormInput
{
local (*qs) = @_ if @_;

if ($ENV{'REQUEST_METHOD'} eq "GET")
        {
        $qs = $ENV{'QUERY_STRING'};
        }
elsif ($ENV{'REQUEST_METHOD'} eq "POST")
        {
        read(STDIN,$qs,$ENV{'CONTENT_LENGTH'});
        }

@qs = split(/&/,$qs);

foreach $i (0 .. $#qs)
        {
        $qs[$i] =~ s/\+/ /g;
        $qs[$i] =~ s/%(..)/pack("c",hex($1))/ge;

        ($name,$value) = split(/=/,$qs[$i],2);

        if($qs{$name} ne "")
                {
                $qs{$name} = "$qs{$name}:$value";
                }
        else
                {
                $qs{$name} = $value;
                }
        }

return 1;
}

#*************************************************************
# SetLock: Subroutine
#*************************************************************

sub SetLock {

        $timecheck = 0;
	while(-e $lock)
	    {
            sleep(5);
	    $timecheck = $timecheck + 1;
	    if ($timecheck >= 5)
		{
		unlink("$lock");
		}
	    }
        open(LOCKFILE,">$lock");
        close(LOCKFILE);
        return;
}

#*************************************************************
# EndLock: Subroutine
#*************************************************************
sub EndLock {

	unlink("$lock");
        return;
}
