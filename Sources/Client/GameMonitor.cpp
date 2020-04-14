// GameMonitor.cpp: implementation of the CGameMonitor class.
//
//////////////////////////////////////////////////////////////////////

#include "GameMonitor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGameMonitor::CGameMonitor()
{
 int i;

	for (i = 0 ; i < DEF_MAXBADWORD; i++)
		m_pWordList[i] = NULL;
}

CGameMonitor::~CGameMonitor()
{
 int i;

	for (i = 0 ; i < DEF_MAXBADWORD; i++)
	if (m_pWordList[i] != NULL) delete m_pWordList[i];
}

int CGameMonitor::iReadBadWordFileList(char *pFn)
{char * pContents, * token;
 char seps[] = "/,\t\n";
 char cReadMode = 0;
 int  iIndex = 0;
 class CStrTok * pStrTok;
 HANDLE hFile;
 FILE * pFile;
 DWORD  dwFileSize;

	hFile = CreateFile(pFn, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

	pFile = fopen(pFn, "rt");
	if (pFile == NULL) return 0;
	else 
	{	pContents = new char[dwFileSize+1];
		ZeroMemory(pContents, dwFileSize+1);
		fread(pContents, dwFileSize, 1, pFile);
		fclose(pFile);
	}	
	pStrTok = new class CStrTok(pContents, seps);
	token = pStrTok->pGet();
	while( token != NULL ) 
	{	m_pWordList[iIndex] = new class CMsg(NULL, token, NULL);
		iIndex++;
		if (iIndex >= DEF_MAXBADWORD) break;
		token = pStrTok->pGet();
	}	
	delete pStrTok;
	delete[] pContents;
	return iIndex;
}

BOOL CGameMonitor::bCheckBadWord(char *pWord)
{int i;
 char cBuffer[500];
	ZeroMemory(cBuffer, sizeof(cBuffer));
	strcpy(cBuffer, pWord);
	i = 0;
	while ((m_pWordList[i] != NULL) && (strlen(m_pWordList[i]->m_pMsg) != 0)) 
	{	if (memcmp(cBuffer, m_pWordList[i]->m_pMsg, strlen(m_pWordList[i]->m_pMsg)) == 0) 
		{	return TRUE;
		}
		i++;
	}
	return FALSE;
}
