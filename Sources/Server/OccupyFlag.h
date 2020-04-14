// OccupyFlag.h: interface for the COccupyFlag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OCCUPYFLAG_H__77BDEA60_C909_11D3_9DC2_00001C7030A6__INCLUDED_)
#define AFX_OCCUPYFLAG_H__77BDEA60_C909_11D3_9DC2_00001C7030A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

class COccupyFlag  
{
public:
	COccupyFlag(int dX, int dY, char cSide, int iEKNum, int iDOI);
	virtual ~COccupyFlag();
	char m_cSide;
	int  m_iEKCount;
	int  m_sX, m_sY;
	int  m_iDynamicObjectIndex;
};

#endif // !defined(AFX_OCCUPYFLAG_H__77BDEA60_C909_11D3_9DC2_00001C7030A6__INCLUDED_)
