#########################################
#     Copyright    WM   1998            #
#     Все права зашищены(1998).         #
#     Почтмейстер                       #
#     По всем вопросам - Миша           #
#     email: scorp@i-connect.ru         #
#     url: http://wmcgi.hypermart.net   #
#########################################
Установка программы на сервере поддерживающем Perl и CGI:
1.Измените первую строку в redirect.cgi на "#!path/to/perl" - нахождение Perl на диске
2.Положите forms.cgi в cgi-bin вашего сайта
3.На страничке , где хотите использовать меню впишите следуюший HTML код:
-----------
<form method=POST action="/cgi-bin/forms.pl">
<!-- Здесь идут обязательные поля, атрибут TYPE можно изменить с HIDDEN на TEXT -->
<input type=hidden name="subject"     value="SUBJECT">
<input type=hidden name="to"          value="you@yoursite.ru">
<input type=hidden name="from"        value="somebody@somebody.ru">
<input type=hidden name="followupurl" value="http://www.yoursite.ru/thanks.htm">

<!-- Здесь можно вставлять любые поля.(Атрибут NAME обязателен) -->

<input type=submit><input type=reset>
</form>
------------
THE END