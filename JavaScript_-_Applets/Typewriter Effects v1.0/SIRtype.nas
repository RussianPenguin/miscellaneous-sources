// Decompiled by Jad v1.5.7d. Copyright 2000 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/SiliconValley/Bridge/8617/jad.html
// Decompiler options: packimports(3) nocode 
// Source File Name:   SIRtype.java

import java.applet.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.PrintStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.StringTokenizer;

public class SIRtype extends Applet
    implements MouseListener, Runnable
{

    Thread thread;
    AudioClip type[];
    URL newURL;
    Graphics pad;
    Graphics textPAD;
    Image buffer;
    Image textDISPLAY;
    Color textCOLOR[];
    Color fadeCOLOR;
    Color backgroundCOLOR;
    Font font;
    FontMetrics fontMETRICS;
    int fontTYPE;
    int fontSIZE[];
    int textEFFECT[];
    int textLENGTH;
    int textNUMBER;
    int textCOUNT;
    int textALIGNMENT[];
    int textHOLD[];
    int typeWAIT[];
    int textX;
    int textY;
    int bufferX;
    int bufferY;
    int bufferWIDTH;
    int bufferHEIGHT;
    int typeSPEED[];
    int fRed;
    int fGreen;
    int fBlue;
    int bRed;
    int bGreen;
    int bBlue;
    int tokenNUMBER;
    int aeSPEED[];
    boolean flag;
    boolean soundFLAG[];
    boolean fadeout;
    boolean rollup;
    boolean shrinkout;
    boolean textBUFFER;
    boolean noURL;
    boolean repeatRoutine;
    boolean linkatend;
    String text[];
    String subText;
    String parmsoundNAME;
    String soundNAME[];
    String parmfontSIZE;
    String parmfontNAME;
    String fontNAME[];
    String parmfontITALIC;
    String fontITALIC[];
    String parmfontBOLD;
    String fontBOLD[];
    String message;
    String parmAfterEffect;
    String AfterEffect[];
    static AppletContext APPLETCONTEXT;


    public void init() {}

    public void start() {}

    public void stop() {}

    public void run() {}

    public void paint(Graphics g) {}

    public void update(Graphics g) {}

    public synchronized void mouseEntered(MouseEvent mouseevent) {}

    public synchronized void mouseExited(MouseEvent mouseevent) {}

    public void mouseClicked(MouseEvent mouseevent) {}

    public void mousePressed(MouseEvent mouseevent) {}

    public void mouseReleased(MouseEvent mouseevent) {}

    public int parmgetint(String s, int i, int j, int k) {}

    public String parmgetstr(String s, String s1) {}

    public SIRtype() {}

}
