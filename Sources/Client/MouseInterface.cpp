// MouseInterface.cpp: implementation of the CMouseInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "MouseInterface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMouseInterface::CMouseInterface()
{
	m_cPrevPress = 0;
	for (int i = 1; i < DEF_MAXRECTS; i++) 
		m_pRect[i] = NULL;
	m_dwTime = timeGetTime();
}

CMouseInterface::~CMouseInterface()
{
	for (int i = 1; i < DEF_MAXRECTS; i++)
	if (m_pRect[i] != NULL) delete m_pRect[i];
}

void CMouseInterface::AddRect(long sx, long sy, long dx, long dy)
{
	for (int i = 1; i < DEF_MAXRECTS; i++)
	if (m_pRect[i] == NULL) {
		m_pRect[i] = (RECT *) new RECT;
		SetRect(m_pRect[i], sx, sy, dx, dy);
		return ;
	}
}

int CMouseInterface::iGetStatus(int msX, int msY, char cLB, char * pResult)
{
 int i, iRet;
	if (cLB != 0) {
		for (i = 1; i < DEF_MAXRECTS; i++) 
		if (m_pRect[i] != NULL) {
			if ((m_pRect[i]->left < msX) && (m_pRect[i]->right > msX) &&
				(m_pRect[i]->top < msY)  && (m_pRect[i]->bottom > msY)) {
				m_cPrevPress = i;
				*pResult = DEF_MIRESULT_PRESS;
				return i;
			}
		}								  
	}
	
	if ((m_cPrevPress != 0) && (cLB == 0)) {
		//if (m_cPrevPress <= 0 ) return 0 ;
		if ((m_pRect[m_cPrevPress]->left < msX) && (m_pRect[m_cPrevPress]->right > msX) &&
			(m_pRect[m_cPrevPress]->top < msY)  && (m_pRect[m_cPrevPress]->bottom > msY)) {
			iRet = m_cPrevPress;
			m_cPrevPress = 0;
			*pResult = DEF_MIRESULT_CLICK;
			return iRet;
		}
	}

	*pResult = DEF_MIRESULT_NONE;
	return 0;
}

