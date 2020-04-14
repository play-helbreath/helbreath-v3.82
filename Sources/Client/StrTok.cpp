// StrTok.cpp: implementation of the CStrTok class.
//
//////////////////////////////////////////////////////////////////////

#include "StrTok.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStrTok::CStrTok(char * pData, char * pSeps)
{
	m_pData = pData;
	m_pSeps = pSeps;

	m_iDataLength = strlen(pData);
	m_iCurLoc     = 0;
}

CStrTok::~CStrTok()
{

}

char * CStrTok::pGet()
{
 register int i = 0;
 char cNextData;
 BOOL bFlag;

	ZeroMemory(m_cToken, sizeof(m_cToken));

	while (m_iCurLoc < m_iDataLength) {

		if (m_iCurLoc <= (m_iDataLength - 2))
			 cNextData = m_pData[m_iCurLoc+1];
		else cNextData = NULL;

		if (_bIsSeperator(m_pData[m_iCurLoc], cNextData))
		{	bFlag = FALSE;
			while (bFlag == FALSE) {
				if (m_iCurLoc <= (m_iDataLength - 2))
					 cNextData = m_pData[m_iCurLoc+1];
				else cNextData = NULL;
				if (_bIsSeperator(m_pData[m_iCurLoc], cNextData)) {
					m_iCurLoc++;	
				}
				else bFlag = TRUE;

				if (m_iCurLoc >= (m_iDataLength-1)) bFlag = TRUE;
			}
			
			return (char *)(&m_cToken);
		}
		else {
			// separator
			m_cToken[i] = m_pData[m_iCurLoc];
			i++;
			m_iCurLoc++;
		}
	}

	if (strlen(m_cToken) != 0) return (char *)(&m_cToken);
	return NULL;
}

bool CStrTok::_bIsSeperator(char cData, char cNextData)
{
 int i = 0;
	
	if (cData == NULL) return TRUE;
	if ((cData == 0x0D) && (cNextData == 0x0A)) return TRUE;
	
	while (m_pSeps[i] != NULL) {
		if (m_pSeps[i] == cData) return TRUE;
		i++;
	}
	return FALSE;
}

