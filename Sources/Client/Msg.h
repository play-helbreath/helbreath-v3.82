// Msg.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSG_H__4A385380_AADF_11D2_B143_00001C7030A6__INCLUDED_)
#define AFX_MSG_H__4A385380_AADF_11D2_B143_00001C7030A6__INCLUDED_

#include <windows.h>
#include <string.h>
#include <winbase.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMsg  
{
public:

	void * operator new (size_t size) 
	{
		return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);	
	};
	
	void operator delete(void * mem)
	{
		HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, mem); 		
	};

	CMsg(char cType, char * pMsg, DWORD dwTime);
	virtual ~CMsg();

	char   m_cType;
	char * m_pMsg;
	short  m_sX, m_sY;
	DWORD  m_dwTime;

	int    m_iObjectID;

};

#endif // !defined(AFX_MSG_H__4A385380_AADF_11D2_B143_00001C7030A6__INCLUDED_)
