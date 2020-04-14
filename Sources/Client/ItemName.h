// ItemName.h: interface for the CItemName class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMNAME_H__CBBF2DF7_525C_47E0_91B0_466BD3BC1013__INCLUDED_)
#define AFX_ITEMNAME_H__CBBF2DF7_525C_47E0_91B0_466BD3BC1013__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

class CItemName  
{
public:
	CItemName();
	virtual ~CItemName();

	char m_cOriginName[21];
	char m_cName[34];
};

#endif // !defined(AFX_ITEMNAME_H__CBBF2DF7_525C_47E0_91B0_466BD3BC1013__INCLUDED_)
