<?php

/*
    Paul Gareau - paul@xhawk.net
    Copyright (C) 2001 - Paul Gareau
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*****************************************************************************/

// disable for now
// include ('ubb2html.inc.php');

class discussion
{
    var $board_id;
    var $mail_reply;
    var $display;
    var $font1;
    var $font2;
    var $th_color;
    var $form_color;

    function discussion()
    {
        $this->board_id = 1;
        $this->mail_reply = 0;
        $this->display = 'full';
        $this->font1 = "<font face='tahoma, arial, helvetica' size=2>";
        $this->font2 = "<font face='tahoma, arial, helvetica' size=2>";
        $this->th_color = "#DDDDDD";
        $this->form_color = "#EEEEEE";
    }

    /*****************************************************************************/

    function get_topics($num_topics)
    {
        global $link_id, $PHP_SELF;

        $sql = "SELECT id, date, name, email, subject, body
               FROM board
               WHERE board_id='$this->board_id'
               AND thread_id=0
               ORDER BY date DESC
               LIMIT 0, $num_topics";

        $result = mysql_query($sql, $link_id);
        $num_topics = mysql_num_rows($result);

        if($this->display!='full')
        {
            $html.= "<ul>\n";
        }

        for($topic=0; $topic<$num_topics; $topic++)
        {
            $record = mysql_fetch_object($result);

            $id = $record->id;
            $subject = $record->subject;
            $name = $record->name;
            // $email = $record->email;
            $date = $record->date;
            $body = $record->body;

            if($this->display=='basic' || $this->display=='nokids')
            {
                $html.= $this->show_link($id, $subject, $name, $email, $date);

                if($this->display != 'nokids')
                {
                    $html.= $this->get_kids($id);
                }

            }
            elseif($this->display=='full')
            {
                $html.= $this->show_post($id, $subject, $name, $email, $date, $body);
            }
        }

        if($this->display!='full')
        {
            $html.= "</ul>\n";
        }

        return $html;
    }

    /*****************************************************************************/

    function get_kids($parent_id)
    {
        global $link_id, $PHP_SELF;

        $sql = "SELECT id, name, email, date, subject
               FROM board
               WHERE parent_id='$parent_id'
               ORDER BY date ASC";
        $result = mysql_query($sql, $link_id);
        $num_kids = mysql_num_rows($result);

        if($num_kids>0)
        {
            $html.= "<ul>\n";

            for($child=0; $child<$num_kids; $child++)
            {
                $record = mysql_fetch_object($result);

                $id = $record->id;
                $subject = $record->subject;
                $name = $record->name;
                // $email = $record->email;
                $date = $record->date;

                $html.= $this->show_link($id, $subject, $name, $email, $date);
                $html.= $this->get_kids($id);
            }
            $html.= "</ul>\n";
        }

        if($html)
        {
            return $html;
        }
        else
        {
            return false;
        }
    }

    /*****************************************************************************/

    function get_post($id)
    {
        global $link_id, $PHP_SELF;

        $sql = "SELECT id, parent_id, thread_id, date, name, email, subject, body
               FROM board
               WHERE id='$id'";
        $result = mysql_query($sql, $link_id);
        $num_posts = mysql_num_rows($result);

        if($num_posts)
        {
            $record = mysql_fetch_object($result);
            $id = $record->id;
            $parent_id = $record->parent_id;
            $thread_id = $record->thread_id;
            $subject = $record->subject;
            $name = $record->name;
            $email = $record->email;
            $date = $record->date;
            $body = $record->body;

            $html.= $this->show_nav($thread_id, $parent_id);
            $html.= $this->show_post($id, $subject, $name, $email, $date, $body);
            $html.= $this->show_nav($thread_id, $parent_id);

            $subject = (! strstr($subject, 'Re:')) ? 'Re: '.$subject : $subject;

            if($thread_id==0)
            {
                $thread_id = $id;
            }

            $html.= $this->show_form($id, $thread_id, $subject);

            return $html;
        }
    }

    /*****************************************************************************/

    function add_post($parent_id, $thread_id, $name, $email, $subject, $body)
    {
        global $link_id, $HTTP_HOST;

        if(! $name)
        {
            $name = '[anonymous]';
        }

        if(! $body)
        {
            $body = '[no text]';
        }

        if(! $subject)
        {
            return false;
        }

        $name = strip_tags($name);
        $email = strip_tags($email);
        $subject = strip_tags($subject);
        $body = nl2br(strip_tags($body));

        // disable for now
        // $body = ubb2html($body);

        $sql = "INSERT INTO board(board_id, parent_id, thread_id, date, name, email, subject, body)
               VALUES('$this->board_id', '$parent_id', '$thread_id', NOW(), '$name', '$email', '$subject', '$body')";
        $result = mysql_query($sql, $link_id);

        if($result)
        {
            if($this->mail_reply)
            {
                $sql = "SELECT DISTINCT email FROM board 
                       WHERE (thread_id='$thread_id' OR id='$thread_id')
                       AND email!='$email'";
                $result = mysql_query($sql, $link_id);
                $num_emails = mysql_num_rows($result);

                while($record = mysql_fetch_object($result))
                {
                    $to = $record->email;

                    // make sure its a valid email address 
                    if(ereg(".+@.+\\..+", $to)) 
                    {
                        mail($to, $subject, $body, "From: $HTTP_HOST");
                    }
                }
            }

            return true;
        }
        else
        {
            return false;
        }
    }

    /*****************************************************************************/

    function show_nav($thread_id, $parent_id)
    {
        global $PHP_SELF;

        $html.= $this->font2;
        $html.= "<a href='$PHP_SELF'><b>Home</b></a> : \n";
        $html.= "<a href='$PHP_SELF?p=$thread_id'><b>Top</b></a> : \n";
        $html.= "<a href='$PHP_SELF?p=$parent_id'><b>Parent</b></a> : \n";
        $html.= "<a href='#reply'><b>Reply</b></a><br><br>\n";
        $html.= "</font>";

        return $html;
    }

    /*****************************************************************************/

    function show_link($id, $subject, $name, $email, $date)
    {
        global $PHP_SELF;

        if($email)
        {
            $name = "<a href='mailto:$email'>$name</a>";
        }

        $time_stamp = strtotime($date);
        $date = date("M j, Y, g:i A", $time_stamp);

        $html.= "$this->font2<li><a href='$PHP_SELF?p=$id'><b>$subject</b></a>";
        $html.= " by $name - <font size='-1'>$date</font></font>\n";

        return $html;
    }

    /*****************************************************************************/

    function show_post($id, $subject, $name, $email, $date, $body)
    {
        global $PHP_SELF;

        if($email)
        {
            $name = "<a href='mailto:$email'>$name</a>";
        }

        $time_stamp = strtotime($date);
        $date = date("M j, Y, g:i A", $time_stamp);

        $html.= "<table border=0 cellpadding=2 cellspacing=0 width=500>\n";
        $html.= "<tr><td colspan=2 bgcolor='$this->th_color'>";
        $html.= "$this->font1<a href='$PHP_SELF?p=$id'><b>$subject</b></a>";
        $html.= " by $name - <font size='-1'>$date</font></font>";
        $html.= "</td></tr><tr>\n";
        $html.= "<td>&nbsp;</td>\n";
        $html.= "<td width='100%'>$this->font2 $body</font></td>\n";
        $html.= "</tr></table>\n";

        $kids = $this->get_kids($id);

        if($kids)
        {
            $html.= $this->get_kids($id);
        }
        else
        {
            $html.= '<br>';
        }

        return $html;
    }


    /*****************************************************************************/

    function show_form($parent_id=0, $thread_id=0, $subject='')
    {
        global $PHP_SELF;

        if($parent_id)
        {
            $msg = 'Reply to this post';
        }
        else
        {
            $msg = 'Post a new message';
        }

        $html.= "<a name='reply'>\n";
        $html.= "<script>\n";
        $html.= "function check_form(){\n";
        $html.= " if(document.dform.subject.value.length < 1){\n";
        $html.= "  alert ('You must enter a subject!')\n";
        $html.= "  return false\n";
        $html.= " }\n";
        $html.= "}\n";
        $html.= "</script>\n";
        $html.= "<form name='dform' action='$PHP_SELF' method='post' onSubmit='return check_form()'>\n";
        $html.= "<input type='hidden' name='post' value='post'>\n";
        $html.= "<input type='hidden' name='parent_id' value='$parent_id'>\n";
        $html.= "<input type='hidden' name='thread_id' value='$thread_id'>\n";
        $html.= "<table border=0 cellpadding=3 cellspacing=0 bgcolor='$this->form_color'>\n";
        $html.= "<tr><td colspan=2 bgcolor='$this->th_color'>$this->font1<b>$msg:</b></font></td></tr>\n";
        $html.= "<tr><td>$this->font2 Name:</td><td><input type='text' size=35 name='name'></td></tr>\n";
        $html.= "<tr><td>$this->font2 Email:</td><td><input type='text' size=35 name='email'></td></tr>\n";
        $html.= "<tr><td>$this->font2 Subject:</td><td><input type='text' size=35 name='subject' value=\"$subject\"></td></tr>\n";
        $html.= "<tr><td colspan=2>$this->font2 Message:</td></tr>\n";
        $html.= "<tr><td colspan=2><textarea rows=10 cols=40 name=body wrap='virtual'></textarea></td></tr>\n";
        $html.= "<tr><td colspan=2 align='right'><input type='submit' value=' Post '></td></tr>\n";
        $html.= "</table>\n";
        $html.= "</form>\n";

        return $html;
    }
}

?>
