// DynamicObject.h: interface for the CDynamicObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DYNAMICOBJECT_H__D8E4A581_0C95_11D3_8F1D_00001C7030A6__INCLUDED_)
#define AFX_DYNAMICOBJECT_H__D8E4A581_0C95_11D3_8F1D_00001C7030A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

class CDynamicObject  
{
public:
	CDynamicObject(short sOwner, char cOwnerType, short sType, char cMapIndex, short sX, short sY, DWORD dwRegisterTime, DWORD dwLastTime, int iV1);
	virtual ~CDynamicObject();

	short m_sOwner;
	char  cOwnerName[11];
	char  m_cOwnerType;

	short m_sType;
	char  m_cMapIndex;
	short m_sX, m_sY; 
	DWORD m_dwRegisterTime;
	DWORD m_dwLastTime;

	int   m_iCount;			// 
	int   m_iV1;			// 
};

#endif // !defined(AFX_DYNAMICOBJECT_H__D8E4A581_0C95_11D3_8F1D_00001C7030A6__INCLUDED_)
