// Effect.h: interface for the CEffect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EFFECT_H__E57B4FA0_ABC0_11D2_B143_00001C7030A6__INCLUDED_)
#define AFX_EFFECT_H__E57B4FA0_ABC0_11D2_B143_00001C7030A6__INCLUDED_

#include <windows.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEffect  
{
public:
	CEffect();
	virtual ~CEffect();

	short m_sType;
	char  m_cFrame, m_cMaxFrame;
	char  m_cDir;
	DWORD m_dwTime, m_dwFrameTime;
	int   m_sX, m_sY, m_dX, m_dY; 
	int   m_mX, m_mY, m_mX2, m_mY2, m_mX3, m_mY3;
	int   m_iErr;
	int   m_rX, m_rY;
	int   m_iV1;	
};

#endif // !defined(AFX_EFFECT_H__E57B4FA0_ABC0_11D2_B143_00001C7030A6__INCLUDED_)
