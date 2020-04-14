// TeleportLoc.h: interface for the CTeleportLoc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPCITEM_H__D4288400_F8C0_11D2_9B6C_00001C7030A6__INCLUDED_)
#define AFX_NPCITEM_H__D4288400_F8C0_11D2_9B6C_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>

class CNpcItem  
{
public:
	CNpcItem(); 
	virtual ~CNpcItem();

	char m_cName[21];
	short m_sItemID;
	short m_sFirstProbability;
	short m_sSecondProbability;
	char m_cFirstTargetValue;
	char m_cSecondTargetValue;

};

#endif
