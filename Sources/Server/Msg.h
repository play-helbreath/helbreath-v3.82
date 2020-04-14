// Msg.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSG_H__57BA71C0_B929_11D2_B143_00001C7030A6__INCLUDED_)
#define AFX_MSG_H__57BA71C0_B929_11D2_B143_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>

#define DEF_MSGFROM_CLIENT		1
#define DEF_MSGFROM_LOGSERVER	2
#define DEF_MSGFROM_GATESERVER	3
#define DEF_MSGFROM_BOT			4

class CMsg  								 
{
public:
	void Get(char * pFrom, char * pData, DWORD * pSize, int * pIndex, char * pKey, DWORD * pTime);
	BOOL bPut(char cFrom, char * pData, DWORD dwSize, int iIndex, char cKey, DWORD dwTime);
	CMsg();
	virtual ~CMsg();

	char   m_cFrom;

	char * m_pData;
	DWORD  m_dwSize;

	int    m_iIndex;
	char   m_cKey;   // v1.4
	DWORD  m_dwMsgTime;
};

#endif // !defined(AFX_MSG_H__57BA71C0_B929_11D2_B143_00001C7030A6__INCLUDED_)
