// Magic.h: interface for the CMagic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAGIC_H__15121CC0_F3E3_11D2_9B6C_00001C7030A6__INCLUDED_)
#define AFX_MAGIC_H__15121CC0_F3E3_11D2_9B6C_00001C7030A6__INCLUDED_

#include <windows.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define DEF_MAGICTYPE_DAMAGE_SPOT		1
#define DEF_MAGICTYPE_HPUP_SPOT			2
#define DEF_MAGICTYPE_DAMAGE_AREA		3
#define DEF_MAGICTYPE_SPDOWN_SPOT		4
#define DEF_MAGICTYPE_SPDOWN_AREA		5
#define DEF_MAGICTYPE_SPUP_SPOT			6
#define DEF_MAGICTYPE_SPUP_AREA			7
#define DEF_MAGICTYPE_TELEPORT			8
#define DEF_MAGICTYPE_SUMMON			9 
#define DEF_MAGICTYPE_CREATE			10
#define DEF_MAGICTYPE_PROTECT			11
#define DEF_MAGICTYPE_HOLDOBJECT		12
#define DEF_MAGICTYPE_INVISIBILITY		13
#define DEF_MAGICTYPE_CREATE_DYNAMIC	14
#define DEF_MAGICTYPE_POSSESSION		15 
#define DEF_MAGICTYPE_CONFUSE			16 
#define DEF_MAGICTYPE_POISON			17 
#define DEF_MAGICTYPE_BERSERK			18
#define DEF_MAGICTYPE_POLYMORPH			20
#define DEF_MAGICTYPE_DAMAGE_AREA_NOSPOT	21
#define DEF_MAGICTYPE_TREMOR				22 
#define DEF_MAGICTYPE_ICE					23 

class CMagic  
{
public:
	CMagic();
	virtual ~CMagic();
	char m_cName[31];
	int  m_sValue1, m_sValue2, m_sValue3;
	// CLEROTH
	int m_sValue4;
	bool m_bIsVisible;
};

#endif // !defined(AFX_MAGIC_H__15121CC0_F3E3_11D2_9B6C_00001C7030A6__INCLUDED_)
