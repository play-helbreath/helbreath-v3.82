// CharInfo.h: interface for the CCharInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARINFO_H__DD443240_AD62_11D2_B143_00001C7030A6__INCLUDED_)
#define AFX_CHARINFO_H__DD443240_AD62_11D2_B143_00001C7030A6__INCLUDED_

#include <windows.h>
#include "Cint.h"	//20030220 mando..

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CCharInfo  
{
public:
	CCharInfo();
	virtual ~CCharInfo();
	char m_cName[12], m_cMapName[12];
	short m_sSkinCol, m_sSex, m_sAppr1, m_sAppr2, m_sAppr3, m_sAppr4;
	short	m_sStr, m_sVit, m_sDex, m_sInt, m_sMag, m_sChr;
	CInt	m_sLevel;
//	short m_sLevel;
	int   m_iExp;
	int   m_iApprColor;
	int   m_iYear, m_iMonth, m_iDay, m_iHour, m_iMinute;
};

#endif // !defined(AFX_CHARINFO_H__DD443240_AD62_11D2_B143_00001C7030A6__INCLUDED_)
