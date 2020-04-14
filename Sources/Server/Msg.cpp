// Msg.cpp: implementation of the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "Msg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsg::CMsg()
{
	m_pData  = NULL;
	m_dwSize = NULL;
}

CMsg::~CMsg()						   
{
	if (m_pData != NULL) delete m_pData;
}

BOOL CMsg::bPut(char cFrom, char * pData, DWORD dwSize, int iIndex, char cKey, DWORD dwTime)
{
	m_pData = new char [dwSize + 1];
	if (m_pData == NULL) return FALSE;
	ZeroMemory(m_pData, dwSize + 1);
	memcpy(m_pData, pData, dwSize);

	m_dwSize = dwSize;
	m_cFrom  = cFrom;
	m_iIndex = iIndex;
	m_cKey   = cKey;
	m_dwMsgTime = dwTime; 

	return TRUE;
}

void CMsg::Get(char * pFrom, char * pData, DWORD * pSize, int * pIndex, char * pKey, DWORD * pTime)
{
	*pFrom  = m_cFrom;
	memcpy(pData, m_pData, m_dwSize);
	*pSize  = m_dwSize;
	*pIndex = m_iIndex;
	*pKey   = m_cKey;
	*pTime = m_dwMsgTime;
}
