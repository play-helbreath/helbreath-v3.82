// GameMonitor.h: interface for the CGameMonitor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEMONITOR_H__FF3C1F40_F134_11D3_9DC2_00A0CC5B45EE__INCLUDED_)
#define AFX_GAMEMONITOR_H__FF3C1F40_F134_11D3_9DC2_00A0CC5B45EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "Msg.h"
#include "strtok.h"

#define DEF_MAXBADWORD		500

class CGameMonitor  
{
public:
	BOOL bCheckBadWord(char * pWord);
	int iReadBadWordFileList(char * pFn);
	CGameMonitor();
	virtual ~CGameMonitor();

	class CMsg * m_pWordList[DEF_MAXBADWORD];
	
};

#endif // !defined(AFX_GAMEMONITOR_H__FF3C1F40_F134_11D3_9DC2_00A0CC5B45EE__INCLUDED_)
