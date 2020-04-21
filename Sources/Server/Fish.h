// Fish.h: interface for the CFish class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FISH_H__B43430CE_E9DE_45BF_9E17_EDF084B0BADD__INCLUDED_)
#define AFX_FISH_H__B43430CE_E9DE_45BF_9E17_EDF084B0BADD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>
#include "Item.h"

class CFish  
{
public:
	CFish(char cMapIndex, short sX, short sY, short sType, class CItem * pItem, int iDifficulty);
	virtual ~CFish();

	char  m_cMapIndex;
	short m_sX, m_sY;			// ¸Ê»óÀÇ À§Ä¡ 

	short m_sType;				// ¹°°í±â Á¾·ù  
	class CItem * m_pItem;		// ³¬¾ÒÀ»¶§ ÇÒ´çµÇ´Â ¾ÆÀÌÅÛ(¹°°í±â ·ùÀÏ °ÍÀÓ)

	short m_sDynamicObjectHandle;

	short m_sEngagingCount;		// ÇöÀç ÀÌ ¹°°í±â¸¦ ³ë¸®°í ÀÖ´Â ÇÃ·¹ÀÌ¾î ¼ö 
	int   m_iDifficulty;		// ³­ÀÌµµ. ÃÖ¼Ò 1Àº µÇ¾î¾ß ÇÑ´Ù.
};

#endif // !defined(AFX_FISH_H__B43430CE_E9DE_45BF_9E17_EDF084B0BADD__INCLUDED_)
