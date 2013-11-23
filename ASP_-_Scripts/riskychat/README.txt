RISKYCHAT 1.2.3 README FILE
19.03.00

So that you'd know:

Riskychat is FREEWARE, because I believe in sharing thoughts. Use it well.
Use Riskychat as you wish, but please do not sell it, or edit it and the sell it :-)
I am not to be held responsible for anything which eventually goes wrong with
your server (I hate to say this, but you never know)
I WOULD APPRECIATE IT IF YOU USE RISKYCHAT AND THEN TELL ME 
WHERE IT'S BEING USED ;-)


Update from 1.2.2:
Now users can just press the enter key to sned their messages. This was a simple JScript bug due to the OnClick event not well handled by the interpreter. The OnSubmit event is now used and seems to work fine...


Now the real README file:

1. Copy all the files in a directory called "chatchat"of your web-root directory
   This is done because the Javascript calls to reload the pages point to that
   directory. I know it is not elegant but did not have enough time to parametrize
   everything. Next version will be fully customizable.
   
2. To start the chat call 'default.asp' in 'YOUR_ROOT/chatchat' directory. A page
	appears saying that the chat needs to be 'started'. Click the 'start chat' link.
	A new window appears saying that you should close it. Do it. Reload (F5) the 
	original 'default.asp' page. The chat is now ready. Riskychat needs this to
	initialise the different arrays ('users', 'text' and 'event').
	You only need to do this everytime you start (or re-start) your web server.
   
3. I would suggest to link the Riskychat from an external page with the following 
	link:
		<a HREF="javascript:open_chat()">Riskychat</a>
	having previously declared this javascript function:
		function open_chat(){
			chat = window.open("","8",'width=630,height=480,toolbar=0,location=0,directories=0,status=0,menubar=0,resizable=0,scrollbars=1');
			chat.location = "http://<%=$Request->ServerVariables("SERVER_NAME")%>/chatchat/";
  		}
	This is done because Riskychat has been optimized graphically to run in
	a 630*480 window, both with IE and Netscape.

4. As far as browser independency goes, Riskychat has been tested with IE
	(4 and 5) and Netscape (3 and 4.x) on different platforms (Win, Mac, Linux).
	Opera has a few problems when reloading pages in different frames. 

5. Users are not, at the moment, logged with IPs or any other way. I am working 
	(god knows when) on a db for user profiles.

6. If you need to see (dinamycally from a different html page) how many users are
	logged in, check out the 'conta_utenti.txt' file in the 'chatchat' directory. Do not manually edit the file.

7. Please forgive eventual not translated code 'remarks :-)



KNOWN BUGS:

a. Sometimes, not at all often really, users remain, for some to-me-unknown-reason,
	logged in. To overcome this call the 'stoppa.asp' file. Then restart the chat (see 2.).
b. As said in 4., Opera has problems with in-frame reloads.
c. This is a first public edition, so many things might have still problems.
	Do consider that Riskychat has been running almost fault-free for over 6
	months on the riskypoint.com server, though!



CONTACTS:

Feel free to contact me for ANY problems you might encounter with chat administration,
or any ideas or whatever:
filippo de vita
wave@flashnet.it
filippo@riskypoint.com



SPECIAL THANKS TO:
dada, for ASP baptism
giorgio, for the pizzas