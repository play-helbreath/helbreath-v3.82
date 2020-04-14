// Skill.h: interface for the CSkill class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKILL_H__ABF6BC21_0C4F_11D3_8F1D_00001C7030A6__INCLUDED_)
#define AFX_SKILL_H__ABF6BC21_0C4F_11D3_8F1D_00001C7030A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

class CSkill  
{
public:
	CSkill();
	virtual ~CSkill();

	char m_cName[21];

	int  m_iLevel;
	BOOL m_bIsUseable;
	char m_cUseMethod;
};

#endif // !defined(AFX_SKILL_H__ABF6BC21_0C4F_11D3_8F1D_00001C7030A6__INCLUDED_)
