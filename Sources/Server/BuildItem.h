// BuildItem.h: interface for the CBuildItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUILDITEM_H__D8858F0E_7737_4E39_9BF9_960C73B0727A__INCLUDED_)
#define AFX_BUILDITEM_H__D8858F0E_7737_4E39_9BF9_960C73B0727A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

class CBuildItem  
{
public:
	CBuildItem();
	virtual ~CBuildItem();

	char  m_cName[21];
	short m_sItemID;

	int  m_iSkillLimit;
	
	int  m_iMaterialItemID[6];
	int  m_iMaterialItemCount[6];
	int  m_iMaterialItemValue[6];		// 재료 아이템 가중치 
	int  m_iIndex[6];

	int	 m_iMaxValue;
	int  m_iAverageValue;	
	int   m_iMaxSkill;					// 이 아이템을 제작해서 올릴 수 있는 최대 스킬
	WORD  m_wAttribute;					// 아이템의 속성을 부여할 수 있다.
};

#endif // !defined(AFX_BUILDITEM_H__D8858F0E_7737_4E39_9BF9_960C73B0727A__INCLUDED_)
