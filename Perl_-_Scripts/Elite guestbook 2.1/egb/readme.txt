This script is copyright (c) 1999-2000 www.MainCentral.com. All Rights Reserved.

You may modify and distribute this script as long as this header is above all.
Please visit http://www.MainCentral.com
Copyright Notice:
	This script may only be used if the copyright, and footers are intact.
	This script was created in hope that it may be useful to you, but is WITHOUT ANY WARRANTY; AS IS

Script name: Elite Guestbook
Version: 2.11
Description: A superior guestbook program which lets the administrator set up an easy-to-use, and control, guestbook.


-	$title
	Defines the title of your guest book ("David's guestbook" / "My site's guestbook" / ...)

-	$sitetitle
	Title of your website. Used as a "Get back to your site" link

-	$siteurl
	URL Adderss of your website. Used as a "Get back to your site" link

-	$tempdir
	This directory holds the template files
	Absolute path, NOT URL!
	No "/" at end!

-	$datadir
	This directory holds the data files
	Absolute path, NOT URL!
	No "/" at end!


-	$egburl
	This directory holds the egb.cgi
	URL, NOT absolute path!
	No "/" at end!

-	@bad = ('word1','word2','word2');
	A list of "bad" words.

-	$lock
	Allow file locking? - Some servers don't allow this, set to "no" if you have one of those servers.

-	$admincheck
	Setting this varuable to "yes" will put the guests' posts into a 
	temporary database until you accept their post, or reject it.

	Good part: You can control the guestbook very well this way.
	Bad part: If you get a lot of visitors, then it's a REAL pain in the butt
			to check the messages.

-	$adminpass
	This is the password to the administration section.

-	$notify
	Set to "yes" if you want to be notified when new posts are made.

	Good part: You know when you get new posts. Plus you can read the post and decide whether you need to take action. (Accept/Reject/Edit/Delete)
	Bad part: If you get a lot of visitors, your e-mail box may be flooded with these.


-	$mailprog
	Absolute path and program where sendmail is installed.
	Only needed if $notify is "yes"

-	$to
	Your e-mail.
	Your E-mail Address.
	Only needed if $notify is "yes"

	Note: Don't forget to escape the @ sign -> \@
	
-	$sub
	Subject of the notification letter.
	Useful so you know that this isn't spam.

-	$frm
	The From: field of a notification letter.
	Useful so you know that it isn't spam.

-	$days
	Enter a digit for how long (in worst cases) it will take you to review a message.
	Set to 0 if $admincheck is "no"

-------------------------------------- Index Options ----------------------------------

$ipwarn		Warn people when logging their IP?	(yes/no)

$sip		Show IP in the guestbook?		(yes/no)
$stop		Show time of posting?			(yes/no)

$rname		Require name? - User must enter a name	(yes/no)
$remail		"	email			email	"
$rhomepage	"	homepage		hompage	"
$rtitle		"	title			title	"
$rmsg		"	message			message	"


$sname		Show Name in guestbook?			(yes/no)
$semail		"Emaul				"	"
$surl		"Homepage url			"	"
$srefer		"Referred by			"	"
$smsg		"Message			"	"


$mname		Max characters the Name may be		(#)
$memail		"		Email		"	"
$murl		"		Homepage Url	"	"
$mtitle		"		Title		"	"
$mmsg		"		Message		"	"


Version updates:
-- If you are updating your EGB script, make sure you update your templates.
  The new version of EGB templates does NOT use the variable $egbname
  The old path of EGB was: $egburl/$egbname
  The new path to EGB is: $egburl

-- Contains $messagesperpage = 20;
-- Contains $newmessages = 'top';

Installation
	Define the configuration.
	Upload to server
	Point users to egb.cgi
	That's it, the script will take care of everything else... including creating database files.
		If the script can't make the database files, it will give an error explaining why
		Fix the error, and try again. (May be permission of $datadir directory, set to 777)

How to use
	To use the guestbook, point ordinary users to egb.cgi
	Everything else will be taken care of by the script.

How to use administration section
	To enter the administration section goto egb.cgi?action=admin
	You will be presented with a field to enter your password
		This is your $adminpass password
	Then it will ask whether you want to edit or delete existing messages
		or accept/reject new messages.
		(This function is if you want to check the messages before they are posted
		to turn this function on set $admincheck to "yes")

	Everything else is simple.

	The form will load, you make any changes you want, select Accept / Edit or Reject / Delete
		to edit or remove messages.

IMPORTANT NOTES:
	1> Do NOT create your own templates, it will just cause the script to malfunction 
		and give weird errors.  The templates are there to insert images
		change the backgrounds, and thing like that.

	2> Under NO CIRSUMSTANCES remove ANY of the headers, or footers!
		
	3> Some servers to not allow flock'ing, in that case delete, the $lock setting.

	4> Keep ALL copyrights intact.