//CWaveViewCtrl.CPP
#include "stdafx.h"
#include "CWaveFile.h"

static const IID IID_DirectSound= {0x279AFA83, 0x4981, 0x11CE, 0xA5, 0x21, 0x00, 0x20, 0xAF, 0x0B, 0xE5, 0x60};

UINT TimerID;

IMPLEMENT_SERIAL(CWaveViewCtrl,CObject,VERSIONABLE_SCHEMA|2)

UINT DrawThread(LPVOID pParam);

//Message Map	
BEGIN_MESSAGE_MAP( CWaveViewCtrl, CWnd)
//{{AFX_MSG_MAP(CWaveEditorView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()	
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//<<<<<<<Constructors>>>>>>>>>
CWaveViewCtrl::CWaveViewCtrl()
{
	m_selpoint=-1;
	m_shiftcaret=false;
	DSound=NULL;
	DSoundBuff=NULL;
	isComm=false;
	m_MouseSel=false;
	m_PBP.x=m_PBP.y=NULL;
}
//******************************
//<<<<<<<<<<<Overrides>>>>>>>>>>>>
BOOL CWaveViewCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
		pContext = NULL;

	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);

	return CWnd::CreateEx(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE,
		className, NULL, dwStyle, 
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		pParentWnd->GetSafeHwnd(), (HMENU) nID);
}

int CWaveViewCtrl::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_selpoint=-1;
//	hWnd=GetSafeHwnd();
	GetClientRect(&rect);
//	CreateCaret(true);
	return 0;
}
void CWaveViewCtrl::Serialize( CArchive& ar )
{
	CObject::Serialize(ar);
	if(ar.IsLoading ())
	{
		CFile *file;
		char* groupID;
		file=ar.GetFile();
		HANDLE m_hMap=::CreateFileMapping((HANDLE)file->m_hFile,NULL,PAGE_READONLY,0,0,NULL);
		LPVOID lpvFile=::MapViewOfFile(m_hMap,FILE_MAP_READ,0,0,0);
		
		int p=0;
		
		m_pRiff=(RIFF*)lpvFile;
		p+=sizeof(*m_pRiff);
		if(memcmp(m_pRiff->ID ,"RIFF",sizeof(m_pRiff->ID))==0)  //for reading file heder difinetion
		{
			groupID=(char*)lpvFile+p;p+=4;
			if(memcmp(groupID ,"WAVE",sizeof(groupID))!=0)
			{
				AfxThrowArchiveException(CArchiveException::badIndex);
			}
		}
		else 
			AfxThrowArchiveException(CArchiveException::badIndex);
		
		m_pRiff=(RIFF*)((BYTE*)lpvFile+p);
		p+=sizeof(*m_pRiff);
		while(memcmp(m_pRiff->ID ,"fmt ",sizeof(m_pRiff->ID))) 	//for reading format chunk 
		{
			p+=m_pRiff->Size;
			m_pRiff=(RIFF*)((BYTE*)lpvFile+p);
			p+=sizeof(*m_pRiff);
			
		}
		
		m_pfch=(fchunk*)((BYTE*)lpvFile+p);
		
		if(m_pfch->wFormatTag ==1)
		{
			do{
				p+=m_pRiff->Size;
				m_pRiff=(RIFF*)((BYTE*)lpvFile+p);
				p+=sizeof(*m_pRiff);
				
			}while(memcmp(m_pRiff->ID ,"data",sizeof(m_pRiff->ID)));

			m_data=(BYTE*)lpvFile+p;
			isComm=true;
			m_MouseSel=true;
		}	
	}
		

}


void CWaveViewCtrl::OnLButtonDown( UINT nFlags, CPoint point )
{
	CWnd::OnLButtonDown(nFlags,point );
	if(!m_MouseSel)return;
	if(m_selpoint!=-1)
	{
		m_selpoint=-1;
		OnPaint();	
	}
	m_selpoint=point.x ;
	::SetCaretPos(point.x,26);
}

void CWaveViewCtrl::OnMouseMove( UINT nFlags, CPoint point )
{
	CWnd::OnMouseMove(nFlags,point );
	if(!m_MouseSel)return;
	int i=-1;
	if(nFlags==MK_LBUTTON &&m_selpoint!=-1)
	{
		CDC *dc=GetDC();
		
		CPoint old=GetCaretPos();
		CPen pe(PS_NULL,0,COLORREF(0));
		CPen* oldp =dc->SelectObject (&pe);
		dc->SetROP2(R2_NOT);
		
		if(point.x <old.x )
			if(!m_shiftcaret)
			{
				i=0;
				m_shiftcaret=true;
			}
			else
				i=1;
		
		if(point.x >old.x )
			if(m_shiftcaret)
			{
				i=0;
				m_shiftcaret=false;
			}
			else
				i=-1;
		
		if(point.x!=m_selpoint)
		{
			HideCaret();
			dc->Rectangle (old.x+i,26,point.x,rect.Width ()-26);
			::SetCaretPos(point.x,26);
			ShowCaret();
		}
		else
			dc->Rectangle (m_selpoint+i,26,old.x,rect.Width ()-26);
		
		dc->SelectObject (oldp);
		ReleaseDC (dc);	
	}
}

void CWaveViewCtrl::OnLButtonUp( UINT nFlags, CPoint point )
{
	m_shiftcaret=false;

}

void CWaveViewCtrl::OnSize( UINT nType, int cx, int cy )
{
	CRect rec;
	CPoint caret;
	caret=GetCaretPos();
		
	GetClientRect(&rec);
	
	if(m_selpoint!=-1)
	{
		TRACE("%d",m_selpoint);
		int pre1=(int)(((float)m_selpoint/rect.Width ())*100);
		m_selpoint=(int)((((float)rec.Width()*pre1)/100)+1);
	}	
	int pre=(int)(((float)caret.x/rect.Width ())*100);
	int pos=(int)((float)(rec.Width()*pre)/100);
		
	rect=rec;
	if(isComm)
	{
		CreateCaret(true);
		::SetCaretPos(pos+1,26);
		ShowCaret();
	}	
	CWnd::OnSize (nType,rect.Width (),rect.Height());
}
//*******************************
//<<<<<<<<<<<Implimentations>>>>>>>>>>>>>>>>
CWaveViewCtrl::~CWaveViewCtrl()
{
	/*if(isComm)			//for free memory
		VirtualFree(m_data,m_pRiff->Size,MEM_DECOMMIT);
	VirtualFree(m_data,m_pRiff->Size,MEM_RELEASE);	*/
	UnmapViewOfFile(lpvFile);
	isComm=!isComm;
	
	DestroyCaret();
	SelectObject(m_MDC.GetSafeHdc (),m_pOldBitmap);

	if(DSound!=NULL)
	{
		if(DSoundBuff)
			DSoundBuff->Release ();
		DSound->Release() ;
		//	DSound=NULL;DSoundBuff=NULL;
	}
}

void CWaveViewCtrl::OnPaint()
{
	CPaintDC DC(this);
	if(isComm==false) return;
	/*::fch=fch;
	::Riff=Riff;
	::m_data =m_data;
	::pDC=&m_MDC;
	::hBitmap=&m_bitmap;
	::hOldBitmap=m_pBitmap;
	::memrect=&memrec;*/
	
	DrawTimeRuler(&DC);	
	if (m_MDC.m_hDC ==NULL)
	{
		AfxBeginThread(DrawThread,(LPVOID)this);
	}
	else
		DrawThread((LPVOID)this);
	
	if(m_selpoint!=-1)
		OnMouseMove( MK_LBUTTON, CPoint(m_selpoint,0) );
}

void CWaveViewCtrl::DrawTimeRuler(CPaintDC* PaintDC)
{
	CFont font,*oldf;
	int sp=rect.Width ()/10;
	int w=sp-sp/2;
	font.CreateFont((int)(w*0.33),w/8,0,0,FW_BOLD,1,0,0,0,1,OUT_DEFAULT_PRECIS,PROOF_QUALITY,FF_ROMAN,NULL );
	oldf=PaintDC->SelectObject(&font);
	
	int ss=(m_pRiff->Size/m_pfch->awAvgBytesPerSec)/10;
	ss=ss==0?ss=1:ss;
	
	int sc=0;	
	for(int i=0 ;i<=10;i++)
	{
		int r=sp*i;
		PaintDC->Rectangle(r,25,r+1,12);
		int t[3];	
		t[1]=sc/60;
		t[2]=t[1]/60;
		t[1]=t[1]-(t[2]*60);
		t[0]=sc-(t[2]*60+t[1])*60;
		char str[]="        \0";
		for(int j=0;j<=2;j++)
		{
			char a[2];
			itoa(t[j],a,10);
			if(t[j]<=9)
			{
				a[1]=a[0];
				a[0]='0';
			}
			memcpy(&str[6-(j*3)],a,sizeof(char)*2);
		}
		str[2]=str[5]=':';
		PaintDC->TextOut(r,0,str,8);
		sc+=ss;	
	}
	PaintDC->SelectObject(oldf);
}

void CWaveViewCtrl::Command(bool state)
{
	if(!isComm)
		return;

	HRESULT hr;
	CLSID clsid;
	
	IUnknown *pUnk;
	IClassFactory *pclsf;
	
	DSBUFFERDESC Buffer;
	WAVEFORMATEX WavFmt;
	if(DSound==NULL)
	{
		if((hr=::CLSIDFromProgID(L"DirectSound",&clsid))!=NOERROR)
		{
			MessageBeep(MB_OK);
			return;
		}
		if((hr=::CoGetClassObject(clsid,CLSCTX_INPROC_SERVER,NULL,IID_IClassFactory,(void**)&pclsf))!=
			NOERROR)
		{
			MessageBeep(MB_OK);
			return;
		}
	
		if(pclsf->CreateInstance(NULL,IID_IUnknown,(void**)&pUnk)!=S_OK)
		{
			MessageBeep(MB_OK);
			return;
		}
		if(pUnk->QueryInterface(IID_DirectSound,(void **)&DSound)!=S_OK)
		{
			MessageBeep(MB_OK);
			return;
		}
		
		pclsf->Release();
		pUnk->Release ();
	}
	
	if(DSoundBuff==NULL)
	{
		DSound->Initialize(NULL);
		DSound->SetCooperativeLevel (GetSafeHwnd(),DSSCL_NORMAL );
		memset(&Buffer,0,sizeof(Buffer));
		Buffer.dwSize =sizeof(Buffer);
		Buffer.dwFlags =DSBCAPS_CTRLDEFAULT;
		Buffer.dwBufferBytes= m_pRiff->Size ;
		memcpy((void*)&WavFmt,(void*)m_pfch,sizeof(*m_pfch));
		WavFmt.cbSize =0;
	
		Buffer.lpwfxFormat=&WavFmt;
		if((hr=DSound->CreateSoundBuffer (&Buffer,&DSoundBuff,NULL))!=DS_OK)
			return;
		
		LPVOID buff1,buff2;
		DWORD size1,size2;
		DSoundBuff->Lock (0,Buffer.dwBufferBytes,&((LPVOID)buff1),&size1,&((LPVOID)buff2),&size2,0);
		memcpy((void*)buff1,m_data,Buffer.dwBufferBytes );
		DSoundBuff->Unlock (buff1,size1,buff2,size2);
	}
	if(DSoundBuff)
	{
		DWORD stat;
		DSoundBuff->GetStatus (&stat);
		if(stat!=DSBSTATUS_PLAYING&&state)
		{
			CPoint caret=GetCaretPos();
			
			m_PBP.x=caret.x;
			m_PBP.y=m_selpoint;
			
			if(m_selpoint<caret.x)
				caret.x=m_selpoint;
			
			OnLButtonDown( 1, CPoint(0,0) );
			m_MouseSel=false;
			
			int pre=(int)(((float)caret.x/rect.Width ())*100);
			int pos=(int)((float)(m_pRiff->Size*pre)/100);
			DSoundBuff->SetCurrentPosition(pos);
			
			
			DSoundBuff->Play (0,0,0);
			TimerID=SetTimer(1,1,NULL);
		
		}else
			if(!state)
				DSoundBuff->Stop();
	}
}

void CWaveViewCtrl::CreateCaret(bool Flag)
{
	if(Flag==true)
	{
		::CreateCaret(GetSafeHwnd(),NULL,0,rect.Height ());
		ShowCaret();
	}
	else
		DestroyCaret();
}

void CWaveViewCtrl::OnSetFocus( CWnd* pOldWnd )
{
	if(isComm)
		CreateCaret(true);
}

void CWaveViewCtrl::OnKillFocus( CWnd* pNewWnd )
{
	if(isComm)
		CreateCaret(false);
}
//*************************************************
//<<<<<<<<<<<<<<<<<Thread>>>>>>>>>>>>>>>>>>>>>
UINT DrawThread(LPVOID pParam){
	CWaveViewCtrl* pWnd=(CWaveViewCtrl*)pParam;
	HWND hWnd =pWnd->GetSafeHwnd();

	if(pWnd->m_MDC.m_hDC ==NULL)  // we will draw wave for frist time 
	{
		CPen pen,*oldpen;
		
		//hBitmap=m_bitmap;//new CBitmap(); // create new bitmap
		pWnd->m_MDC.CreateCompatibleDC (NULL); // create memory DC compatible with system display
	
		pWnd->GetClientRect(&(pWnd->memrec)); // get the borders of the window that will display the wave
	
		pWnd->m_bitmap.CreateCompatibleBitmap(CDC::FromHandle (GetDC(hWnd)),pWnd->memrec.Width (),pWnd->memrec.Height ());
		pWnd->m_pOldBitmap =(CBitmap*)SelectObject(pWnd->m_MDC.GetSafeHdc (),pWnd->m_bitmap);
		pWnd->m_MDC.Rectangle (0,0,pWnd->memrec.Width (),pWnd->memrec.Height ());
		
		pen.CreatePen (PS_SOLID,0,RGB(0,90,180));
		oldpen=pWnd->m_MDC.SelectObject (&pen);
		
		DWORD size;
		size=pWnd->m_pfch->wBitsPerSample ==16?pWnd->m_pRiff->Size/2:pWnd->m_pRiff->Size;
		
		int b=0;
		
		int time=pWnd->m_pRiff->Size/pWnd->m_pfch->awAvgBytesPerSec ; // calcualte the time of the wave
		
		b=time<10 ? pWnd->memrec.Width()-((pWnd->memrec.Width()/10)*time):0;// if the time<10 calculate the wave width
		
		int pps=(pWnd->memrec.Width ()*15)/time; // calculate how many pixles per scond
		int n= pWnd->m_pfch->dwSamplesPerSec /pps;     // calculate the number of escapes
		
		int yy=pWnd->memrec.Height ()/4;	// calculate the y of the first channel 
		pWnd->m_MDC.MoveTo (0,yy);			// move to the orgin
		int h=yy;					// calculate the hight of the first channel 
	
		short sample;
		for(int register x=0;x<(long)size;x=x+n)	//to draw first channel
		{
			sample=pWnd->m_pfch->wBitsPerSample ==8?( (*((BYTE*)pWnd->m_data+x)-128)*h)/128:((*((short*)pWnd->m_data+x))*h)/(65535/2);
			pWnd->m_MDC.LineTo (int(((float)x/size)*(pWnd->memrec.Width()-b)),yy-sample);
		}

		yy= yy+h+h/2;
		pWnd->m_MDC.MoveTo (0,yy);
		if(pWnd->m_pfch->wChannels>1) // go here if the wave is stereo
			for( x=1;x<=(long)size;x=x+n) // to draw the scond channel
			{

				sample=pWnd->m_pfch->wBitsPerSample ==8?( (*((BYTE*)pWnd->m_data+x)-128)*h)/128:((*((short*)pWnd->m_data+x))*h)/(65535/2);
				pWnd->m_MDC.LineTo (int(((float)x/size)*(pWnd->memrec.Width()-b)),yy-sample);
			}	
		pWnd->m_MDC.SelectObject (oldpen);
	}
	CRect rc;
	GetClientRect(hWnd,&rc);
	StretchBlt(GetDC(hWnd),0,25,rc.Width (),rc.Height (),pWnd->m_MDC .GetSafeHdc(),0,0,pWnd->memrec.Width ()
		,pWnd->memrec.Height(),SRCCOPY);	
	return 0;
}

void CWaveViewCtrl::OnTimer( UINT nIDEvent )
{
	DWORD stat;
	DSoundBuff->GetStatus (&stat);
	if(stat==DSBSTATUS_PLAYING)
	{
		DWORD ReadPos,WritePos;
		DSoundBuff->GetCurrentPosition (&ReadPos,&WritePos);
		int time=m_pRiff->Size /m_pfch->dwSamplesPerSec ; // calcualte the time of the wave
		int timepos=ReadPos/m_pfch->dwSamplesPerSec ;
		float pre=((float)timepos/time)*100+1;
		int pos=int((rect.Width()*pre)/100);
	
		if(m_PBP.x>m_PBP.y)
		{
			if(pos>=m_PBP.x&&m_PBP.x!=m_PBP.y)
				DSoundBuff->Stop();
		}
		else
			if(pos>=m_PBP.y&&m_PBP.x!=m_PBP.y)
				DSoundBuff->Stop();
		::SetCaretPos(pos,26);
	}else
	{
		::SetCaretPos(m_PBP.x,26);
		m_selpoint=m_PBP.y;
		m_MouseSel=true;
		OnMouseMove( MK_LBUTTON, CPoint(m_selpoint,0) );
		KillTimer(TimerID);
		m_MouseSel=true;
	}
	
}
//**************************************