// YWSound.h: interface for the YWSound class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YWSOUND_H__AB055FE0_F550_11D1_8255_00002145AAC4__INCLUDED_)
#define AFX_YWSOUND_H__AB055FE0_F550_11D1_8255_00002145AAC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "dsound.h"

class YWSound
{
public:
	YWSound();
	virtual ~YWSound();
	bool Create(HWND hWnd);
	LPDIRECTSOUND m_lpDS;
	DSCAPS m_DSCaps;
};

#endif // !defined(AFX_YWSOUND_H__AB055FE0_F550_11D1_8255_00002145AAC4__INCLUDED_)