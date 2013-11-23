// MyWnd.cpp : implementation file
//
//--
#include "stdafx.h"
#include "wiz.h"
//#include "MyWnd.h"
//#include "wizDlg.h"
#include "Edit2.h"
#include <winuser.h>
#include "Face.h"
#include "Goto.h"
#include "EvalDlg.h"
//1
//2
//3
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//1
//2
#define ID_TIMER_1                      1006
#define ID_TIMER_2                      1007

/////////////////////////////////////////////////////////////////////////////
// CReadWnd

CReadWnd::CReadWnd()
{
        //par=(CWizDlg*) AfxGetApp()->GetMainWnd();
        //(CWizDlg*)par->
        Create(AfxRegisterWndClass(CS_HREDRAW |CS_VREDRAW , ::LoadCursor(NULL,IDC_ARROW), ::CreateSolidBrush(RGB(0,0,0) )), //(HBRUSH)DKGRAY_BRUSH       ),
        " ",WS_CHILD|WS_POPUP,CRect(10,10,530,500), par ,NULL);

        m_edit=new CEdit2;
        m_edit->Create(ES_MULTILINE|ES_NOHIDESEL  | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL |ES_READONLY    ,// |WS_DLGFRAME|WS_SIZEBOX           ,
     CRect(50, 50, GetSystemMetrics(SM_CXSCREEN)-50, GetSystemMetrics(SM_CYSCREEN)-50), this, 1);

   // m_edit->HideCaret();
        bc=CreateSolidBrush(clr_bc);
        //bc2=CreateSolidBrush(clr_bc);

    f.m_hFile=NULL;
        cnt=20;
        res=false;
        decod=0;
        track=false;
        pages=0;
    //speed_start = false;
    m_sizecur=::LoadCursor(AfxGetApp()->m_hInstance,(LPCTSTR)IDC_POINTER_COPY1);
    timer2=0;
}

CReadWnd::~CReadWnd()
{

}

BEGIN_MESSAGE_MAP(CReadWnd, CWnd)
        //{{AFX_MSG_MAP(CReadWnd)
        ON_WM_CTLCOLOR()
        ON_WM_DROPFILES()
        ON_WM_TIMER()
        ON_WM_CLOSE()
        ON_WM_HELPINFO()
    ON_WM_SETCURSOR()
        ON_WM_PAINT()
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CReadWnd message handlers

BOOL CReadWnd::PreCreateWindow(CREATESTRUCT& cs)
{
        cs.dwExStyle= WS_EX_TOOLWINDOW | WS_EX_ACCEPTFILES | WS_EX_TOPMOST;
    cs.style=WS_POPUP | WS_BORDER ;
        return CWnd::PreCreateWindow(cs);
}


bool CReadWnd::BringUP()
{
    ShowWindow(SW_SHOW);
        SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE,0);
        Invalidate(true);
return true;

}


HBRUSH CReadWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
        HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);
        switch ( nCtlColor)
        {
        case CTLCOLOR_STATIC   :
                pDC->SetTextColor(clr_fnt);
                pDC->SetBkColor(clr_bc);
                //DeleteObject(bc);
                //bc=CreateSolidBrush(clr_bc);
                return bc;
                break;
        }
        return hbr;
}

bool CReadWnd::change_font()
{
    fnt.DeleteObject();
        fnt.CreateFontIndirect(&maindlg3()->Info.fonts[3].fnt);
        m_edit->SetFont(&fnt,false);

    sizes(line_y,cnt);
    show_curr_page(1,0);
        Invalidate(true);
        return 1;
}

bool CReadWnd::change_color()
{
          clr_fnt=maindlg3()->Info.fonts[3].clr;
          clr_bc=maindlg3()->Info.fonts[3].clr_bk;

      DeleteObject(bc);
      bc=CreateSolidBrush(clr_bc);
          ::SetClassLong(m_hWnd,GCL_HBRBACKGROUND, (LONG)bc);

          m_edit->Invalidate(true);
          return 1;
}

BOOL CReadWnd::DestroyWindow()
{
    KillTimer(timer2);
    DeleteObject(m_sizecur);
        DeleteObject(bc);
        //DeleteObject(bc2);
        f.Close();
        f.m_hFile=NULL;
        return CWnd::DestroyWindow();
}

BOOL CReadWnd::PreTranslateMessage(MSG* pMsg)
{
        switch ( pMsg->message )
        {
    //case WM_CLOSE:
      //  return 1;
    case WM_LBUTTONDOWN:
        if (afterHLP)
        {
          afterHLP=false;
          this->Invalidate(true);
        }
        if ( track)
        {
            CPoint point(LOWORD(pMsg->lParam),HIWORD(pMsg->lParam) );
            if ( tr.HitTest(point) >= 0 )
            {
                if ( tr.Track(this, point, false) )
                {
                    r=tr.m_rect;
                    r.DeflateRect(6,6);
                    this->Invalidate(true);
                    m_edit->SetWindowPos(NULL,r.left,r.top,r.right-r.left,r.bottom-r.top,0);
                    sizes(line_y,cnt);
                    show_curr_page(1,0);
                    m_edit->RedrawWindow();
                    m_edit->SetWindowPos(NULL,0,0,0,0,SWP_NOREDRAW  );
                    CClientDC dcs(this);
                    tr.Draw(&dcs);
                }
            }
            return 1;
        }
        if ( pMsg->hwnd!=m_edit->m_hWnd) readnext(1);
            break;
    case WM_RBUTTONDOWN:
        if ( pMsg->hwnd!=m_edit->m_hWnd && !track) readnext(0); break;
        case WM_KEYDOWN:
                switch (pMsg->wParam)
                {
        case VK_ESCAPE:
            if (afterHLP) {afterHLP=false; Invalidate(true);}
            if (track)
            {
                r=tr.m_rect;
                r.DeflateRect(6,6);
                m_edit->SetWindowPos(NULL,r.left,r.top,r.right-r.left,r.bottom-r.top,0);
                track = false;
                maindlg3()->dlg_start=false;
                this->Invalidate(true);
                return 1;
            }
            break;
        case VK_SHIFT:
            if (!track)
            {
                maindlg3()->dlg_start=true;
                track = true;
                prepare_tracker();
            } else
            {
                r=tr.m_rect;
                r.DeflateRect(6,6);
                m_edit->SetWindowPos(NULL,r.left,r.top,r.right-r.left,r.bottom-r.top,0);
                track = false;
                maindlg3()->dlg_start=false;
                this->Invalidate(true);
                return 1;
            }

            return 1; break;
                case 90:
                         maindlg3()->from_readerwnd(4,0,0,NULL);  return 1;
             break;  // VK_Z
                case 65:
                         maindlg3()->from_readerwnd(3,0,0,NULL);  return 1;
             break; //VK_A
                case VK_CONTROL:
                        if ( !isOpened() || tip ) break;
                        {
                                tip=true;
                                draw_info();
                        }
                        break;
                case VK_TAB:
                         maindlg3()->from_readerwnd(7,0,0,NULL);  return 1; break; //VK_A
                        //MessageBeep(1);
                        break;
                };
                break;
                case WM_KEYUP:
                        switch (pMsg->wParam)
                        {
                        case VK_CONTROL:
                                tip=false;
                                InvalidateRect(info,true);
                                break;
                        }
                        break;
                case WM_SYSKEYDOWN:
                        {
                if (!track)
                                switch (pMsg->wParam)
                                {
                                case 65:
                                        maindlg3()->from_readerwnd(6,0,0,NULL);
                                        break; //alt+VK_A
                case 'F':
                    maindlg3()->from_readerwnd(9,5,0,NULL);
                                        break;
                case 'O':
                    maindlg3()->from_readerwnd(9,1,0,NULL);
                    break;
                case 'M':
                    maindlg3()->from_readerwnd(9,3,0,NULL);
                    break;
                case 'G':
                    {
                        maindlg3()->minim=maindlg3()->dlg_start=true;
                        CGoto Goto(this);
                        Goto.DoModal();
                        maindlg3()->minim=maindlg3()->dlg_start=false;
                    }
                }
                        }
                                break;

        }
        if ( !maindlg3()->showing) this->SetFocus();
        return CWnd::PreTranslateMessage(pMsg);
}


int CReadWnd::RedFile(LPTSTR name,UINT charset)
{
    //MessageBeep(1);
        strcpy(filename,name);
        metX=GetSystemMetrics(SM_CXSCREEN);
        metY=GetSystemMetrics(SM_CYSCREEN);

    RECT_arrow.SetRect(metX-250,metY-109,metX,metY);

    if ( f.m_hFile!=NULL ) { maindlg3()->from_readerwnd(27,0,0,NULL); f.Close();        }
        if ( f.Open(name,CFile::modeRead | CFile::typeText | CFile::shareDenyNone   ))
        {
                strncpy(buff,filename,1000);
                strcpy( strrchr(buff,'\\')+1 , "\0");
                ::SetCurrentDirectory(buff);
        if (!timer2)
           timer2=SetTimer(ID_TIMER_2,100,NULL); // = 1 sec/10

                eof=false;
                cash.RemoveAll();
                cash.Add(0);
                pages=1;
        pages_read = 0;
        page_sec = 0;
        aver_speed2 = aver_speed3 =0;
        ms2=0;
        line_back=1;
        milisec2 = 0;
        //speed_start = maindlg3()->Info.timer_st;

        read_page(1);
                maindlg3()->from_readerwnd(1,0,0,name);

                this->SetFocus();
                return 1;
        }
        else
        {
                f.Close();
                f.m_hFile=NULL;
        m_edit->SetWindowText("Error opening File ! \x0D\x0A");
        }
        return 0;
}

bool CReadWnd::readnext(short n)
{
        if ( !isOpened() ) return 0;

        if ( (n) )
        {
        strcpy(buff,maindlg3()->Info.key);
        if (eof) return false;

        ////////////////////
        if ( (pages+1)%10 == 0)
            if ( !strchr(decode_b64(buff),'+') || ( (hash( strchr(buff+2,'+')+1 )/ 1000)+11 != strlen(buff+2) )  )
            {
                CEvalDlg dlg(this);
                maindlg3()->dlg_start=true;
                if ( dlg.DoModal(maindlg3()->Info.days) == IDCANCEL)
                {
                    maindlg3()->SendMessage(WM_SYSCOMMAND,SC_CLOSE      ,0);
                }
                maindlg3()->dlg_start=false;
            }
            ///////////////////////////
            if ( read_page(1) )
            {
                pages_read++;
                ++pages;
            }

    }
        else
    {
        if (pages>1)
        {
            eof=false;
            if ( read_page(0) ) --pages;
        }
        }

    InvalidateRect(RECT_arrow,true);

    if ( page_sec)
    {
        double  l1 =  words_in_page/page_sec;
        aver_speed2 = 100 / l1;
        aver_speed3 = 10 * l1;
    }


       maindlg3()->from_readerwnd(2,pages,0,NULL);

    aver_page_sec+=page_sec;
    page_sec = 0;
    line_back =1;
    ms2=0;

        return true;
}

bool CReadWnd::read_page(bool show)
{
    //if ( !isOpened() ) return 0;

    char str[200];
        buff1[0]=0;
        buff[0]=0;
        page_kb=0;
    int buf_len = 8000;
    int l;
    int p1;
    char *s,*s3,*bf;
    int y=0;
    int read_len=5000;

    line[0]=0;

    if ( show)
    {
        f_pos=f.GetPosition();
        y=f.Read(buff1,read_len);
        if (y==0) { eof=true; return 0; };

        s=buff1;
        y=0;

        while ( y<cnt)
        {
           s3 = strpbrk(s,"\x0D\x0A\x0");
           s3 = ( (s3)? ( (s3-s<=line_y)? s3 : s+line_y ) : s+line_y );

           if (*s3==13 && *(s3+1)==10) *(s3+1)=0;
           *s3=0;

           if ( decod ) decode(s);
           strcat(buff,s);
           strcat(buff,"\x0D\x0A");

           s=s3+1;
           if (*s==0) s++;
           y++;
        }
        f.Seek(f_pos+(s-buff1),CFile::begin);
        bf=buff;

    }else
    {

        f.Seek( (f_pos>read_len) ? f_pos-read_len : 0 ,CFile::begin);
        read_len = ( f_pos>read_len ) ? read_len : f_pos;
        y=f.Read(buff1, read_len);

        if (y==0) { eof=true; return 0; };
        buff1[y]=0;
        s=buff1+y;
        char *s4=s;
        y=0;

        bf=buff+buf_len;
        MessageBeep(1);
        s3=s;
        if ( *s==10 ) *s=0;
        if ( *(s-1)==10 ) *(s-1)=0;
        //s=buff1;
        while ( y<cnt)
        {
            s=s3-line_y;
            s3 = strrchr(s,10);
            if (s3==NULL) {MessageBeep(1); s3=s;}

            strcpy(str,s3+1);
            strcat(str,"\x0D\x0A");
            if ( decod ) decode(str);

            bf-=strlen(str);
            memcpy(bf,str,strlen(str));
            AfxMessageBox(str);

            if ( *(s3-1) == 13 ) s3--;
            *(s3)=0;
            y++;
        }
        f_pos=f.GetPosition()-(s4-s3);
    }

    m_edit->SetWindowText(bf);
    words_in_page=GetWordsCnt(bf);
    return true;
}


bool CReadWnd::SetDimens(int pg)
{
        cnt=pg;
        if ( !isOpened() ) return 0;

        f.Seek(cash.GetAt(pages-1),CFile::begin );
        //sizes(line_y,cnt);
        read_page();

        return true;
}

void CReadWnd::OnDropFiles(HDROP hDropInfo)
{
        par->SendMessage(WM_DROPFILES,(UINT)hDropInfo,0);
        //par->i
}


BOOL CReadWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
        par=pParentWnd;
        return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
        //return true;
}

bool CReadWnd::isOpened()
{
        return (f.m_hFile==NULL) ? 0 : 1;
}


bool CReadWnd::decode(char *s)
{

        int a[]={      //KOI_2_WIN
                0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,
                        0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,
                        0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,
                        0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,

                        0x000 ,0x000 ,0x000 ,0x038 ,0x000 ,0x000 ,0x000 ,0x000 ,
                        0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,
                        0x000 ,0x000 ,0x000 ,0x028 ,0x000 ,0x000 ,0x000 ,0x000 ,
                        0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,0x000 ,

                        0x07E ,0x060 ,0x061 ,0x076 ,0x064 ,0x065 ,0x074 ,0x063 ,
                        0x075 ,0x068 ,0x069 ,0x06A ,0x06B ,0x06C ,0x06D ,0x06E ,
                        0x06F ,0x07F ,0x070 ,0x071 ,0x072 ,0x073 ,0x066 ,0x062 ,
                        0x07C ,0x07B ,0x067 ,0x078 ,0x07D ,0x079 ,0x077 ,0x07A ,

                        0x05E ,0x040 ,0x041 ,0x056 ,0x044 ,0x045 ,0x054 ,0x043 ,
                        0x055 ,0x048 ,0x049 ,0x04A ,0x04B ,0x04C ,0x04D ,0x04E ,
                        0x04F ,0x05F ,0x050 ,0x051 ,0x052 ,0x053 ,0x046 ,0x042 ,
                        0x05C ,0x05B ,0x047 ,0x058 ,0x05D ,0x059 ,0x057 ,0x05A };


        if (decod==1)
        {
                while ( *(s)!=0 )
                {
                        if ( unsigned char(*(s))>127 && unsigned char(*(s))<176) *(s)+=64;
                        else
                                if ( unsigned char(*(s))>223 && unsigned char(*(s))<240) *(s)+=16;
                        s++;
                }
                return true;
        }
        if (decod==2)
        {
                while ( *(s)!=0 )
                {
                        if ( unsigned char(*(s))>0x080 && unsigned char(*(s))<0x0ff)
                                *(s)=a[unsigned char(*(s))-0x080]+0x080;
                        s++;
                }
                return true;
        }
return true;
}

bool CReadWnd::update_viewPort(UINT x)
{
        decod=maindlg3()->Info.decod;
    m_edit->MoveWindow(maindlg3()->Info.pos,false);
    cnt=maindlg3()->Info.lines;
    //unsigned int i;
    sizes(line_y,cnt);
    //if (cnt>i) cnt=i;

    Invalidate();
        show_curr_page(0,0);
        return true;
}

short CReadWnd::get_decode()
{
        return decod;
}

void CReadWnd::sizes(int &x, UINT &y)  //
{
        CSize size;

        RECT rect;
        char *s = new char[500];
        memset(s,(int)'x',499);
        m_edit->GetClientRect(&rect);
        CDC *dc = m_edit->GetDC();
        dc->SelectObject(&fnt);

        size.cx=10000;
        int y2,x_l=499;

    memset(s,(int)'s',199);
        while ( size.cx>rect.right)
        {
                size=dc->GetTextExtent(s,----x_l);
                *(s+x_l)=0;
                dc->LPtoDP(&size);
        }
        (x_l<1500) ? x=x_l : x=1500 ;
        y=rect.bottom/(size.cy)-1;

        ReleaseDC(dc);
        delete s;

        maindlg3()->from_readerwnd(5,y,0,NULL);
        return ;

        //m_edit->LineLength(

}

DWORD CReadWnd::get_dim()
{
        return cash.GetAt(pages-1)+50;
}

void CReadWnd::prepare_tracker()
{
    maindlg3()->dlg_start=true;

    tr.m_sizeMin.cx=GetSystemMetrics(SM_CXSCREEN)/4;
        tr.m_sizeMin.cy=GetSystemMetrics(SM_CXSCREEN)/3;
        tr.m_nHandleSize=6;
    tr.m_nStyle |= CRectTracker::resizeOutside | CRectTracker::hatchedBorder ;

    CRect edit; m_edit->GetWindowRect(edit);
    edit.DeflateRect(-6,-6);
    tr.m_rect=edit;

    CClientDC dcs(this);
    tr.Draw(&dcs);

    OnPaint();
    m_edit->SetWindowPos(NULL,0,0,1,1,SWP_NOREDRAW  );


}

int CReadWnd::get_pagenum()
{
        return pages;
}
void CReadWnd::Seek_toPage(UINT page)
{
     AfxGetApp()->DoWaitCursor(1);

        if (page==pages || !isOpened() ) return;
        eof=false;
        cash.RemoveAll();
        f.SeekToBegin();
        pages=0;
        while ( pages<page )
        {
                if (eof) break;
                cash.Add(f.GetPosition());
                ++pages;
                for (int i=1; i<=cnt; ++i)
                {
                        //if ( !f.ReadString(buff,line_y))
                        {
                                eof=true; break;
                        }
                }
        }
        f.Seek(cash.GetAt(pages-1),CFile::begin );
        read_page();
    AfxGetApp()->EndWaitCursor();
}

void CReadWnd::Seek_to(UINT page)
{
    AfxGetApp()->DoWaitCursor(1);

        if (page==pages || !isOpened() ) return;
        eof=false;
        cash.RemoveAll();
        f.SeekToBegin();
        pages=0;
    int p_kb;

        //
    while ( f.GetPosition()<=page+50 )
        {
                if (eof) break;
                cash.Add(f.GetPosition());
                ++pages;
                for (int i=1; i<=cnt; ++i)
                {
//                      if ( !f.ReadString(buff,line_y))
                        {
                                eof=true; break;
            }
            p_kb+=strlen(buff);
            //f.Seek(cash.GetAt(pages-1),CFile::begin );
            //f.Seek(cash.GetAt(pages-1)+page_kb,CFile::begin );
        }
        }

    show_curr_page(0,0);
    AfxGetApp()->EndWaitCursor();
}

void CReadWnd::OnTimer(UINT nIDEvent)
{
    switch (nIDEvent)
        {
    case ID_TIMER_1:
        {
            KillTimer(timer);
            CRect r(15,5,26,110);
            InvalidateRect(r,true);
        }
        break;
    case ID_TIMER_2:
        {
            if ( !maindlg3()->is_runpointer_enable() || tip || milisec2==0 || track ) return;
            ms2++;
            int bytes= line[line_back]-line[line_back-1];

            if ( (milisec2*bytes)-1 <= ms2)
            {
                draw_runner_lead(m_edit->PosFromChar(line[line_back+1]-20));
                ms2=0;
                line_back++;
            }
        }
        break;
    }
        CWnd::OnTimer(nIDEvent);
}

void CReadWnd::OnClose()
{
        maindlg3()->SendMessage(WM_SYSCOMMAND,SC_CLOSE  ,0);
        CWnd::OnClose();
}

void CReadWnd::draw_bm_lable(UINT i)
{
        CDC * dcs = GetDC();

        pPen.CreatePen(PS_SOLID,10, RGB(180,220,150));
        pPenOld = dcs->SelectObject(&pPen);
        dcs->MoveTo(20,10);
        dcs->LineTo(20,100);
    dcs->SelectObject(pPenOld);
    pPen.DeleteObject();
    ReleaseDC(dcs);

        timer=SetTimer(ID_TIMER_1,400,NULL);
        return;
}


void CReadWnd::draw_arrow()
{
    CDC * dcs = GetDC();
    pPen.CreatePen(PS_SOLID,6, RGB(80,180,50));
    pPenOld = dcs->SelectObject(&pPen);

        dcs->MoveTo(metX-100,metY-100);
        dcs->LineTo(metX-50,metY-100);
        dcs->LineTo(metX-75,metY-50);
        dcs->LineTo(metX-100,metY-100);

    dcs->SelectObject(pPenOld);
    pPen.DeleteObject();
    ReleaseDC(dcs);
}

void CReadWnd::draw_runner_lead(CPoint pnt)
{
    InvalidateRect(lead ,true);

    CDC * dcs = GetDC();
    pPen.CreatePen(PS_SOLID,2, RGB(80,180,50));
    pPenOld =  dcs->SelectObject(&pPen);

    m_edit->ClientToScreen(&pnt);
    pnt.x=20;
    pnt.y+=8;

        dcs->MoveTo(pnt.x,pnt.y);
        dcs->LineTo(pnt.x+15,pnt.y+5);
        dcs->LineTo(pnt.x,pnt.y+10);
        dcs->LineTo(pnt.x,pnt.y);
    lead.SetRect(pnt.x-2,pnt.y-2,pnt.x+17,pnt.y+12);

    dcs->SelectObject(pPenOld);
    pPen.DeleteObject();
    ReleaseDC(dcs);
}


void CReadWnd::draw_info()
{
        CDC * dcs = GetDC();
    CBrush *pBrsO = NULL;
    CFont* pOldFont = NULL;

        pBrs.CreateSolidBrush( maindlg3()->Info.fonts[4].clr_bk );
        pBrsO =dcs->SelectObject(&pBrs);

        fnt2.CreateFontIndirect(&maindlg3()->Info.fonts[4].fnt);
        pOldFont = dcs->SelectObject(&fnt2);
        dcs->SetTextColor(maindlg3()->Info.fonts[4].clr);
        dcs->SetBkMode(TRANSPARENT   );

        CString s1;
        CString s2;
        par->GetDlgItemText(IDC_BUTTON1,s2);
        parse_templ(s1,maindlg3()->Info.fonts[4].templ,s2,0);

    for ( int x=1; x<=2; x++)
    {
        dcs->DrawText(s1,&info,DT_TOP | DT_LEFT | DT_CALCRECT);
    switch ( maindlg3()->Info.info_pos)
    {
    case 0:
        info.left=20;
        info.top=20;
        break;
    case 1:
        info.top=20;
        info.left=metX-info.Width()-10;
        break;
    case 2:
        info.left = metX / 2 - info.Width() / 2;
        info.top = metY / 2 - info.Height() / 2;
        break;
    case 3:
        info.top=metY-info.Height()-10;
        info.left=20;
        break;
    case 4:
        info.top=metY-info.Height()-10;
        info.left=metX-info.Width()-10;
        break;
    }
    }


        info.DeflateRect(-4,-2);
        dcs->Rectangle(info);
        info.DeflateRect(4,2);
        dcs->DrawText(s1,&info,DT_TOP | DT_LEFT);
        info.DeflateRect(-4,-2);

        dcs->SelectObject(pOldFont);
    fnt2.DeleteObject();
    dcs->SelectObject(pBrsO);
    pBrs.DeleteObject();

    ReleaseDC(dcs);

}


CString& CReadWnd::GetStatName(short ch)
{
        if ( !isOpened() ) { stat=""; return stat; };

        UINT DayOfWeek[] =
        {
                LOCALE_SDAYNAME7,  LOCALE_SDAYNAME1, LOCALE_SDAYNAME2,  LOCALE_SDAYNAME3,
                LOCALE_SDAYNAME4,  LOCALE_SDAYNAME5, LOCALE_SDAYNAME6
        };
        UINT months[] =
        {
                LOCALE_SMONTHNAME13,  LOCALE_SMONTHNAME1, LOCALE_SMONTHNAME2,   LOCALE_SMONTHNAME3,
                LOCALE_SMONTHNAME4,  LOCALE_SMONTHNAME5, LOCALE_SMONTHNAME6 , LOCALE_SMONTHNAME7,
                LOCALE_SMONTHNAME8,  LOCALE_SMONTHNAME9,LOCALE_SMONTHNAME10,LOCALE_SMONTHNAME11,
                LOCALE_SMONTHNAME12
        };

        ldiv_t p= ldiv(f.GetLength(),100 );
        ldiv_t l;
        if (p.quot!=0) l = ldiv(f.GetPosition(),p.quot);
        else l.quot=100;

        CTime time2(CTime::GetCurrentTime());
        bool h24 =  !maindlg3()->Info.AMpm;

        switch ( ch)
        {
        case 1:
                stat.Format(" %d (%d%%) ",pages,l.quot);
                break;
        case 2:
                stat.Format(" %d (%d%%) \n", pages,l.quot);
                (h24) ? stat+=time2.Format("%H:%M:%S ") : stat+=time2.Format("%I:%M:%S %p ");
                break;
        case 3:
                {
                        CString s2;
                        par->GetDlgItemText(IDC_BUTTON1,s2);
                        stat.Format(" %d (%d%%) \n %s",pages,l.quot,(h24) ? time2.Format("%H:%M:%S ") : time2.Format("%I:%M:%S %p "));
                        if (s2!="")
                                stat+=" \n "+s2;
                }
                break;
        case 4:
                stat.Format("%d (%d%%) | %s",pages,l.quot,filename);
                break;
                // ************
        case 5:
                stat.Format("%d",pages);
                break;
        case 6:
                stat.Format("%d%%",l.quot);
                break;
        case 7:
                TCHAR strM[256];
          ::GetLocaleInfo(LOCALE_USER_DEFAULT, months[time2.GetMonth()], strM, sizeof(strM));
                stat=strM;
                stat+=time2.Format(",%d %Y");

                break;
        case 8:
                (h24) ? stat=time2.Format("%H:%M") : stat=time2.Format("%I:%M %p");
                break;
        case 9:
                TCHAR strWeekday[256];
                  ::GetLocaleInfo(LOCALE_USER_DEFAULT, DayOfWeek[time2.GetDayOfWeek()-1], strWeekday, sizeof(strWeekday));
                  stat=strWeekday;
                break;
        case 10: // FILE
                stat.Format("%s",filename);
                stat=stat.Right(stat.GetLength()-stat.ReverseFind('\\')-1);
                break;
        case 11:
                stat.Format("%d",get_dim());
                break;
        case 12: //PATH
        stat.Format("%s",filename);
                stat=stat.Left(stat.ReverseFind('\\'));
                break;
        case 13:
                break;
        case 14:
        {
                unsigned long i2=100;
                GetUserName((char*)(LPCTSTR)stat,&i2);
                break;
        }
    case 15: // words
        stat.Format("%d",words_in_page);
        break;
    case 16: // speed
        stat.Format("%d",page_sec);
        break;
    case 17: // aver_speed
        if (pages_read) stat.Format("%d",aver_page_sec/pages_read); else
            stat="";
        break;
    case 18: // read_ages
        if (pages_read) stat.Format("%d",pages_read); else
            stat="";
        break;
    case 19: // aver_speed = 100 words per # sec
        if (pages_read) stat.Format("%d",aver_speed2); else
            stat="";
        break;
    case 20: // aver_speed  = # words per 10sec
        if (pages_read)
            stat.Format("%d",aver_speed3);
        else  stat="";
        break;
    }
    return stat;
}


void CReadWnd::from_edit2(WPARAM param)
{
        /*CString s2;
        s2.Format("%d",param);
        AfxMessageBox(s2);*/

        switch ( param)
        {
        case 100:  // copy
                m_edit->Copy();
                break;
        case 101: // memo
                {
                        int x1,x2;
                        CString s1;
                        m_edit->GetSel(x1,x2);
                        m_edit->GetWindowText(s1);
            add_memo(s1.Mid(x1,x2-x1));
                }
                break;
        case 104: //fins
                maindlg3()->from_readerwnd(9,5,0,NULL);
                break;
    case 105: //fins
        {
            maindlg3()->minim=maindlg3()->dlg_start=true;
            CGoto Goto(this);
            Goto.DoModal();
            maindlg3()->minim=maindlg3()->dlg_start=false;
        }

                break;
        case 107: //save
        {   int x1,x2;
            CString s1;
            m_edit->GetSel(x1,x2);
            m_edit->GetWindowText(s1);
            export_text(s1.Mid(x1,x2-x1),this);
        }
        break;
    case 108: // print
                {
                        CPrintDialog dlg(false,PD_SELECTION || PD_NOPAGENUMS,this);


                        dlg.m_pd.nMinPage =1;
                        dlg.m_pd.nMaxPage =cash.GetSize();
                        dlg.m_pd.nFromPage =pages;
                        dlg.m_pd.nToPage = pages;

                        if (dlg.DoModal() == IDOK)
                        {
                                CString PrintOut,s1,s2;
                                CDC pdc;

                                pdc.Attach(dlg.m_pd.hDC);
                                //if (dlg.PrintAll())     {     }       else if (dlg.PrintRange())  {           }
                                 if (dlg.PrintSelection())
                                {
                                        //MessageBeep(1);

                                        DOCINFO docinfo;
                                        memset(&docinfo, 0, sizeof(docinfo));
                                        docinfo.cbSize = sizeof(docinfo);
                                        docinfo.lpszDocName = _T("MadReader file");
                                        if ( pdc.StartDoc(&docinfo) >= 0)
                                        {
                                                if (pdc.StartPage() >= 0)
                                                {
                                                        CFont fnt3;
                                                        CRect r;
                            int h;
                            CGdiObject* pOldFont;

                            if ( strlen(maindlg3()->Info.fonts[0].templ) )
                            {
                                fnt3.CreateFontIndirect(&maindlg3()->Info.fonts[0].fnt);
                                pOldFont = pdc.SelectObject(&fnt3);

                                r.SetRectEmpty();
                                //r.SetRect(0, 0, pdc.GetDeviceCaps(HORZRES), pdc.GetDeviceCaps(VERTRES));
                                //pdc.DPtoLP(r);

                                parse_templ(PrintOut,maindlg3()->Info.fonts[0].templ);
                                pdc.DrawText(PrintOut,r,DT_TOP | DT_LEFT | DT_CALCRECT   );
                                pdc.DrawText(PrintOut,r,DT_TOP | DT_LEFT  );
                                h=r.Height();
                                r.top+=h+20;

                                pdc.SelectObject(pOldFont);
                                fnt3.DeleteObject();
                            }
                            //////////////////////////////////////////

                            fnt3.CreateFontIndirect(&maindlg3()->Info.fonts[1].fnt);
                                                        pOldFont = pdc.SelectObject(&fnt3);

                                                        int x1,x2;
                                                        m_edit->GetSel(x1,x2);
                                                        m_edit->GetWindowText(s1);
                                                        PrintOut=s1.Mid(x1,x2-x1);
                            PrintOut+="\x0D\x0A";

                            pdc.DrawText(PrintOut,r,DT_TOP | DT_LEFT | DT_CALCRECT   );
                            pdc.DrawText(PrintOut,r,DT_TOP | DT_LEFT  );
                            h=r.Height();
                            r.top+=h+20;

                            pdc.SelectObject(pOldFont);
                            fnt3.DeleteObject();
                            //////////////////////////////////////////
                            if ( strlen(maindlg3()->Info.fonts[2].templ) )
                            {
                                fnt3.CreateFontIndirect(&maindlg3()->Info.fonts[2].fnt);
                                pOldFont = pdc.SelectObject(&fnt3);

                                PrintOut.Empty();
                                parse_templ(PrintOut,maindlg3()->Info.fonts[2].templ);
                                pdc.DrawText(PrintOut,r,DT_TOP | DT_LEFT | DT_CALCRECT   );
                                pdc.DrawText(PrintOut,r,DT_TOP | DT_LEFT  );
                                h=r.Height();
                                r.top+=h+20;

                                pdc.SelectObject(pOldFont);
                                fnt3.DeleteObject();
                            }
                            /////////////////////////////////////////////////

                                                        pdc.EndPage();
                                                        pdc.EndDoc();
                                                        pdc.SelectObject(pOldFont);
                                                }

                                        }

                                }

                        }

                }
    case 110:
     /*   //MessageBeep(1);
        page_sec=0;
        pages_read = 0;
        speed_start=true;*/
        break;
        }
}

CReadWnd* mainwnd3()
{
        CWizDlg* dlg = (CWizDlg*)AfxGetApp()->GetMainWnd();
        return &dlg->wnd;
}

DWORD CReadWnd::read_hide(int i, CString& s1)
{
        ldiv_t p= ldiv(f.GetLength(),100 );
        ldiv_t l;
        if (p.quot!=0) l = ldiv(f.GetPosition(),p.quot);
        else l.quot=100;

        if (!isOpened() || eof || (i>1 && pages<2)) { s1.Empty(); return l.quot;        }


        if (i==0) { m_edit->GetWindowText(s1); return l.quot; }

        if ( i==1 ) //vpered 1 page
        {
                cash.Add(f.GetPosition());
                ++pages;
        }
        else //back 1 page
        {
                if ( cash.GetSize()<=1 || pages<2 ) {return l.quot ; }
                f.Seek(cash.GetAt(pages-2),CFile::begin );
                --pages;
        }

        s1="";
        for (int i2=1; i2<=cnt; ++i2)
        {
//              if ( !f.ReadString(buff,line_y)) {break;}
                if ( decod ) decode((char*)&buff);
                s1+=buff;
        }
         p= ldiv(f.GetLength(),100 );
        if (p.quot!=0) l = ldiv(f.GetPosition(),p.quot);
        else l.quot=100;
        return  l.quot;
}

void CReadWnd::show_curr_page(int i, int i2)
{
    if ( isOpened() )
    {
        f.Seek(cash.GetAt(pages-1),CFile::begin );
        read_page();
    }
    if ( i2 ) m_edit->SetSel(i,i2);
}



BOOL CReadWnd::OnHelpInfo(HELPINFO* pHelpInfo)
{
    SetWindowPos(&wndNoTopMost,0,0,0,0,SWP_NOACTIVATE   |SWP_NOMOVE   |SWP_NOREDRAW   |SWP_NOSIZE  );
    maindlg3()->context_h=true;
    afterHLP=true;
    WinHelp(1001,HELP_CONTEXTPOPUP);
    return true;
}

BOOL CReadWnd::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message )
{
    if (track)
    {
        GetCursorPos(&p);
        tr.GetTrueRect(&r);
        if (r.PtInRect(p) )
        {
            tr.SetCursor( pWnd, nHitTest);
            return 1;
        }
    }
    if ( pWnd == this && isOpened())
    {
        GetCursorPos(&p);
        if ( p.x >metX-20 ) { SetCursor(NULL); return true; }
        else { SetCursor(m_sizecur);  return true; }
    }
    return CWnd::OnSetCursor(pWnd, nHitTest, message );
}

int CReadWnd::GetWordsCnt(char *s)
{
    int cnt=0;
    bool w1 = false, w2 = false;
    //char * s1 =s;

    while ( *s )
    {
        s++;
        switch ( *s )
        {
        case 'é':
        case 'ö':
        case 'ó':
        case 'ê':
        case 'å':
        case 'í':
        case 'ã':
        case 'ø':
        case 'ù':
        case 'ç':
        case 'õ':
        case 'ú':
        case 'ô':
        case 'û':
        case 'â':
        case 'à':
        case 'ï':
        case 'ð':
        case 'î':
        case 'ë':
        case 'ä':
        case 'æ':
        case 'ý':
        case 'ÿ':
        case '÷':
        case 'ñ':
        case 'ì':
        case 'è':
        case 'ò':
        case 'ü':
        case 'á':
        case 'þ':
        case '¨':
        case '¸':


        case 'q':
        case 'w':
        case 'e':
        case 'r':
        case 't':
        case 'y':
        case 'u':
        case 'i':
        case 'o':
        case 'p':
        case 'a':
        case 's':
        case 'd':
        case 'f':
        case 'g':
        case 'h':
        case 'j':
        case 'k':
        case 'l':
        case 'z':
        case 'x':
        case 'c':
        case 'v':
        case 'b':
        case 'n':
        case 'm':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':

        case 'É':
        case 'Ö':
        case 'Ó':
        case 'Ê':
        case 'Å':
        case 'Í':
        case 'Ã':
        case 'Ø':
        case 'Ù':
        case 'Ç':
        case 'Õ':
        case 'Ú':
        case 'Ô':
        case 'Û':
        case 'Â':
        case 'À':
        case 'Ï':
        case 'Ð':
        case 'Î':
        case 'Ë':
        case 'Ä':
        case 'Æ':
        case 'Ý':
        case 'ß':
        case '×':
        case 'Ñ':
        case 'Ì':
        case 'È':
        case 'Ò':
        case 'Ü':
        case 'Á':
        case 'Þ':


        case 'Q':
        case 'W':
        case 'E':
        case 'R':
        case 'T':
        case 'Y':
        case 'U':
        case 'I':
        case 'O':
        case 'P':
        case 'A':
        case 'S':
        case 'D':
        case 'F':
        case 'G':
        case 'H':
        case 'J':
        case 'K':
        case 'L':
        case 'Z':
        case 'X':
        case 'C':
        case 'V':
        case 'B':
        case 'N':
        case 'M':
            w1 = true;
        }

        if (!w1 && w2 ) cnt++;
        w2=w1;
        w1 = false;
    }
    return cnt;
}

void CReadWnd::timer_1sec(int mode, int sum, bool run)
{
    if ( tip || track) return;
    page_sec++;

    if ( run )
    {

        int sec = maindlg3()->Info.runsec;
        double  l1 ;
        double  l2;
        double  l3;

        switch ( mode )
        {
        case 1:
            break;
        /*case 2: //kb
            l1 = maindlg3()->Info.run_kb ;
            l2 = (sec>0)? sec:1;
            l3 = page_kb;
            sec = l3 * ( l1 / l2);
            if ( sec==0 ) sec=2;
            break;*/
        case 0: //wrds
            l1 = maindlg3()->Info.run_wrd  ;
            l2 = (sec>0)? sec:1;
            l3 = words_in_page;
            sec = l3 / ( l1 / l2);
            if ( sec==0 ) sec=2;
            break;
        }
        l2=sec;
        l3= (page_kb>0)?page_kb:1;
        milisec2 = (l2 / l3)*10 ; // secnd/10 to read 1 byte

        if ( sec-1 == page_sec) { draw_arrow(); return;};
        if ( sec == page_sec) { readnext(1); return;};
    }
}

void CReadWnd::OnPaint()
{
        CPaintDC dc(this); // device context for painting

    if ( track)
        tr.Draw(&dc);

        // Do not call CWnd::OnPaint() for painting messages
}

