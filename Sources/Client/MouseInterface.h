// MouseInterface.h: interface for the CMouseInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOUSEINTERFACE_H__8EB34B20_7FC7_11D2_A8E6_00001C7030A6__INCLUDED_)
#define AFX_MOUSEINTERFACE_H__8EB34B20_7FC7_11D2_A8E6_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>
#include <time.h>

#define DEF_MAXRECTS	30
#define DEF_MIRESULT_NONE		0
#define DEF_MIRESULT_PRESS		1
#define DEF_MIRESULT_CLICK		2


class CMouseInterface  
{
public:
	int iGetStatus(int msX, int msY, char cLB, char * pResult);
	void AddRect(long sx, long sy, long dx, long dy);
	CMouseInterface();
	virtual ~CMouseInterface();
	RECT * m_pRect[DEF_MAXRECTS];
	char   m_cPrevPress;
	DWORD  m_dwTime;
};

#endif // !defined(AFX_MOUSEINTERFACE_H__8EB34B20_7FC7_11D2_A8E6_00001C7030A6__INCLUDED_)
