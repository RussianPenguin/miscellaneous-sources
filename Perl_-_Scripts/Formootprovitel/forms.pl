#!/usr/local/bin/perl

#########################################
#     Copyright    WM   1998            #
#     Все права зашищены(1998).         #
#     Почтмейстер                       #
#     По всем вопросам - Миша           #
#     email: scorp@i-connect.ru         #
#     url: http://wmcgi.hypermart.net   #
#########################################



###############################################
#Программа SENDMAIL
$mailprog = '/var/qmail/bin/qmail-inject';    
###############################################

read(STDIN, $buffer, $ENV{'CONTENT_LENGTH'});

@pairs = split(/&/, $buffer);

foreach $pair (@pairs) {
   ($name, $value) = split(/=/, $pair);
   $name =~ tr/+/ /;
   $name =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;
   $name =~ s/<!--(.|\n)*-->//g;
   $name =~ s/<([^>]|\n)*>//g;
   $value =~ tr/+/ /;
   $value =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;
   $value =~ s/<!--(.|\n)*-->//g;
   $value =~ s/<([^>]|\n)*>//g;
   $FORM{$name} = $value;
}


$subject = $FORM{subject};
$to = $FORM{to};
$from = $FORM{from};
$followupurl = $FORM{followupurl};

# Open the mail program
open(MAIL,"|$mailprog -t");

print MAIL "To: $to\n";
print MAIL "From: $from\n";
print MAIL "Subject: $subject\n";
print MAIL "\n";
print MAIL "---------------------------------------------------------------------\n";

foreach $key (keys(%FORM)) {
   if ($key ne "subject" && $key ne "to" && $key ne "from" && $key ne "followupurl") {
      print MAIL "$key: $FORM{$key}\n";
   }
}

print MAIL "---------------------------------------------------------------------\n";

close(MAIL);

print "Location: $followupurl\n\n";
