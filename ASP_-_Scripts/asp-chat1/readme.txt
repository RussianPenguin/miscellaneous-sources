*************************************************************
*                 Adrenalin's ASP Chat                      *
*                         v1.0                              *
*************************************************************


   
Bare Minimum Instructions:

Extract the zip contents into its own directory, for instance
create a directory named chat under your web root directory 
and extract the contents there, but be sure to keep the directory
structure intact. The directory structure should look like so:

<install-dir>/chat
		  /files
		  /images

ASP Chat has 2 basic requirements. 1) It must use a global.asa,
which means it must be in a virtual directory. 2) It writes all
chat sessions to a file, so the virtual directory must have
-Write- permission (on win95/98 setting the directory to
Execute permissions should do).


NT Install
-----------
On NT you should use the Internet Service Manager to create
the virtual directory. To do so, go to Start-Programs-
Windows NT4.0 Option Pack-WebServer-Internet Service Manager.
Right click on the Web Site in the left pane where you want to 
install ASP Chat (e.g. Default Web Site). Select 
New->Virtual Directory. In the Alias text field enter chat
and click Next. Then click on the Browse button and browse to
the directory where you extracted this zip file. Select that
directory then click Next, Select the Read, Script and Write
Access checkboxes.


If you dont have Internet Service Manager but you have
an NTFS filesystem then you could do the following:
On NT right click on the directory you created and 
select properties, then select the web sharing tab. Click
the Share this folder option, you will be prompted to give the 
virtual directory a name, name it chat. 
* The virtual directory must have write permissions *


Win95/98 Install
----------------
On Win95/98 I think you can right click the web server
globe in the system tray and create the virtual
directory there. I'm not much help with 95/98, sorry.

That should do it. Now just go to http://<your-server>/chat/
where your server is your servers name (or do 127.0.0.1 if local) and 
virtualDir is the virtual directory you created in the last step above.

Other Details:

There are 2 ways to create chat rooms. 1) Use the web based 'Ad-Hoc' chat
room creation. This is good for short-lived rooms. When the server is
restarted, the rooms will disappear. 2) Open global.asa in a text editor
and view the lines in the '### comments. There is a subroutine called CreateRoom
that you must call to create room. It is very simple and should be added
below the comments. Its use is like so:
    CreateRoom "RoomName" "RoomDescription"



Questions/Suggestion should be sent to: dstoflet@calweb.com