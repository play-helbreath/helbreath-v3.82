// Fish.cpp: implementation of the CFish class.
//
//////////////////////////////////////////////////////////////////////

#include "Fish.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFish::CFish(char cMapIndex, short sX, short sY, short sType, class CItem * pItem, int iDifficulty)
{
	m_cMapIndex		= cMapIndex;
	m_sX			= sX;
	m_sY			= sY;
	m_sType			= sType;
	m_pItem			= pItem;

	m_sEngagingCount = 0;
	m_iDifficulty    = iDifficulty;
	
	if (m_iDifficulty <= 0) 
		m_iDifficulty = 1;
}

CFish::~CFish()
{
	if (m_pItem != NULL) delete m_pItem;
}
