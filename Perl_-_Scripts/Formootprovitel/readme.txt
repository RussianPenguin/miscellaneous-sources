#########################################
#     Copyright    WM   1998            #
#     ��� ����� ��������(1998).         #
#     �����������                       #
#     �� ���� �������� - ����           #
#     email: scorp@i-connect.ru         #
#     url: http://wmcgi.hypermart.net   #
#########################################
��������� ��������� �� ������� �������������� Perl � CGI:
1.�������� ������ ������ � redirect.cgi �� "#!path/to/perl" - ���������� Perl �� �����
2.�������� forms.cgi � cgi-bin ������ �����
3.�� ��������� , ��� ������ ������������ ���� ������� ��������� HTML ���:
-----------
<form method=POST action="/cgi-bin/forms.pl">
<!-- ����� ���� ������������ ����, ������� TYPE ����� �������� � HIDDEN �� TEXT -->
<input type=hidden name="subject"     value="SUBJECT">
<input type=hidden name="to"          value="you@yoursite.ru">
<input type=hidden name="from"        value="somebody@somebody.ru">
<input type=hidden name="followupurl" value="http://www.yoursite.ru/thanks.htm">

<!-- ����� ����� ��������� ����� ����.(������� NAME ����������) -->

<input type=submit><input type=reset>
</form>
------------
THE END