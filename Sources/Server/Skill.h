// Skill.h: interface for the CSkill class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKILL_H__CD611901_EF3A_11D2_9B6C_00001C7030A6__INCLUDED_)
#define AFX_SKILL_H__CD611901_EF3A_11D2_9B6C_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>



#define DEF_SKILLEFFECTTYPE_GET			    1		// 얻는다. 물고기나 광물등 
#define DEF_SKILLEFFECTTYPE_PRETEND			2		// ...한 체 하다 
#define DEF_SKILLEFFECTTYPE_TAMING			3		//  길들이기 계열	


class CSkill  
{
public:
	CSkill();
	virtual ~CSkill();

	char m_cName[21];

	short m_sType;
	short m_sValue1, m_sValue2, m_sValue3, m_sValue4, m_sValue5, m_sValue6;
						 
};

#endif // !defined(AFX_SKILL_H__CD611901_EF3A_11D2_9B6C_00001C7030A6__INCLUDED_)
