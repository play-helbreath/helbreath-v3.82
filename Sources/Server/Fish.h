// Fish.h: interface for the CFish class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FISH_H__B43430CE_E9DE_45BF_9E17_EDF084B0BADD__INCLUDED_)
#define AFX_FISH_H__B43430CE_E9DE_45BF_9E17_EDF084B0BADD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>
#include "item.h"

class CFish  
{
public:
	CFish(char cMapIndex, short sX, short sY, short sType, class CItem * pItem, int iDifficulty);
	virtual ~CFish();

	char  m_cMapIndex;
	short m_sX, m_sY;			// 맵상의 위치 

	short m_sType;				// 물고기 종류  
	class CItem * m_pItem;		// 낚았을때 할당되는 아이템(물고기 류일 것임)

	short m_sDynamicObjectHandle;

	short m_sEngagingCount;		// 현재 이 물고기를 노리고 있는 플레이어 수 
	int   m_iDifficulty;		// 난이도. 최소 1은 되어야 한다.
};

#endif // !defined(AFX_FISH_H__B43430CE_E9DE_45BF_9E17_EDF084B0BADD__INCLUDED_)
