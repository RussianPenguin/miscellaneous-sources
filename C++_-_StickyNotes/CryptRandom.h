// CryptRandom.h: interface for the CCryptRandom class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPTRANDOM_H__FEC59A52_3A5D_4368_81D5_EEF18FBE881C__INCLUDED_)
#define AFX_CRYPTRANDOM_H__FEC59A52_3A5D_4368_81D5_EEF18FBE881C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include <wincrypt.h>

// CCryptRandom is used to generate random numbers
// Written by M. Howard "Writing secure code"
class CCryptRandom 
{
public:
    CCryptRandom();
    ~CCryptRandom();
    BOOL GenRand(void * lpGoop, DWORD dwGoop);

private:
    HCRYPTPROV m_hProv;
};

CCryptRandom::CCryptRandom() 
{
	ATLTRACE(_T("CCryptRandom::CCryptRandom\n"));

    m_hProv = NULL;
    CryptAcquireContext(&m_hProv, NULL, NULL,
						PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
}

CCryptRandom::~CCryptRandom() 
{
	ATLTRACE(_T("CCryptRandom::~CCryptRandom\n"));

    if (m_hProv) 
		CryptReleaseContext(m_hProv, 0);
}

BOOL CCryptRandom::GenRand(void * lpGoop, DWORD dwGoop)
{
    if (!m_hProv) 
		return FALSE;

    return CryptGenRandom(m_hProv, dwGoop, reinterpret_cast<LPBYTE>(lpGoop));
}

#endif // !defined(AFX_CRYPTRANDOM_H__FEC59A52_3A5D_4368_81D5_EEF18FBE881C__INCLUDED_)
