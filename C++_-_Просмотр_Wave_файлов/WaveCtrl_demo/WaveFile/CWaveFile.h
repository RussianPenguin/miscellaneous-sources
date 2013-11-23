//CWaveViewCtrl.h
#include <windows.h>
#include <mmsystem.h>
#include <DSOUND.h>
typedef struct FormatChunk{
	//long chunkSize;
	short wFormatTag;
	unsigned short wChannels;
	unsigned long dwSamplesPerSec;
	unsigned long awAvgBytesPerSec;
	unsigned short wBlockAlign;
	unsigned short wBitsPerSample;
}fchunk;

typedef struct RIFF{
	char ID[4];
	DWORD Size;
}riff;

class CWaveViewCtrl:public CWnd
{
DECLARE_SERIAL(CWaveViewCtrl);          // to make this class siralizeable
// Construction
public:
	CWaveViewCtrl();						//default constructor	
	// Attributes
public:
	void *m_data;		
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaveEditCtrl)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
	void Serialize( CArchive& ar );      //to do siralization
	
	void Command(bool state=true);			 //to play sound

	virtual ~CWaveViewCtrl();//distructor

protected:
	//{{AFX_MSG(CWaveEditCtrl)
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg int  OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnKillFocus( CWnd* pNewWnd );
	afx_msg void OnSetFocus( CWnd* pOldWnd );
	afx_msg void OnTimer( UINT nIDEvent );
	afx_msg void OnPaint();
	//}}AFX_MSG
public:
	CDC m_MDC;
	CBitmap m_bitmap,*m_pOldBitmap;
	CRect memrec;
	fchunk* m_pfch;
	RIFF* m_pRiff;
private:
	CRect rect;
	int m_selpoint;
	bool isComm,m_shiftcaret,m_MouseSel;
	POINT m_PBP;
	LPVOID lpvFile;

	IDirectSound* DSound;
	IDirectSoundBuffer* DSoundBuff;

	
	
	void CreateCaret(bool Flag);
	void DrawTimeRuler(CPaintDC* PaintDC);	
	
	DECLARE_MESSAGE_MAP()
};