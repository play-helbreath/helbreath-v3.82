// Magic.h: interface for the CMagic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAGIC_H__CD611900_EF3A_11D2_9B6C_00001C7030A6__INCLUDED_)
#define AFX_MAGIC_H__CD611900_EF3A_11D2_9B6C_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>

#define DEF_MAGICTYPE_DAMAGE_SPOT				1
#define DEF_MAGICTYPE_HPUP_SPOT					2
#define DEF_MAGICTYPE_DAMAGE_AREA				3 // effect456->Damage on spot + -effect789->Damage on area
#define DEF_MAGICTYPE_SPDOWN_SPOT				4
#define DEF_MAGICTYPE_SPDOWN_AREA				5
#define DEF_MAGICTYPE_SPUP_SPOT					6 // Not used
#define DEF_MAGICTYPE_SPUP_AREA					7
#define DEF_MAGICTYPE_TELEPORT					8
#define DEF_MAGICTYPE_SUMMON					9 
#define DEF_MAGICTYPE_CREATE					10
#define DEF_MAGICTYPE_PROTECT					11	
#define DEF_MAGICTYPE_HOLDOBJECT				12
#define DEF_MAGICTYPE_INVISIBILITY				13
#define DEF_MAGICTYPE_CREATE_DYNAMIC			14 // Eff12=distance caster/wall, or= Size of square
#define DEF_MAGICTYPE_POSSESSION				15
#define DEF_MAGICTYPE_CONFUSE					16 // Mass-Illusion, Illusion, Illusion-Movement, Mass-Illusion-Movement
#define DEF_MAGICTYPE_POISON					17
#define DEF_MAGICTYPE_BERSERK					18
#define DEF_MAGICTYPE_DAMAGE_LINEAR				19 // LightningBolt
#define DEF_MAGICTYPE_POLYMORPH					20
#define DEF_MAGICTYPE_DAMAGE_AREA_NOSPOT		21 // Mass-Magic-Missile
#define DEF_MAGICTYPE_TREMOR					22
#define DEF_MAGICTYPE_ICE						23
// 24 SNOOPY: Used this unused for Lightning spell: This will often miss the target.
#define DEF_MAGICTYPE_DAMAGE_SPOT_RANDOM        24 // Lightning by SNOOPY
#define DEF_MAGICTYPE_DAMAGE_AREA_NOSPOT_SPDOWN	25 // EWS effect456->Damage, 789->SPdown
#define DEF_MAGICTYPE_ICE_LINEAR				26 // Blizzard
// 27 SNOOPY: Used this for HPup area
#define DEF_MAGICTYPE_HPUP_AREA					27 // Gives HP Twice on target
#define DEF_MAGICTYPE_DAMAGE_AREA_ARMOR_BREAK   28 // Armor Break m_sValue10 is used for armor decrement
#define DEF_MAGICTYPE_CANCELLATION				29
#define DEF_MAGICTYPE_DAMAGE_LINEAR_SPDOWN		30 // Earth-Shock-Wave
#define DEF_MAGICTYPE_INHIBITION				31 // Inhibition-Casting	
#define DEF_MAGICTYPE_RESURRECTION				32 // Resurrection
#define DEF_MAGICTYPE_SCAN						33 // Scan

#define DEF_MAGICTYPE_MANA_DOWN_SPOT			50 // Manadrain
#define DEF_MAGICTYPE_REFLEXION     			51 // Sends back effect to attacker
#define DEF_MAGICTYPE_EXPLOSION     			52 // Sends back pc or mobs away from caster with some damage.

#define DEF_MAGICTYPE_REFLEXION_COUNT     		56 // Store Physical relexion nb
#define DEF_MAGICTYPE_DEFENCESHIELD_VALUE	 	57 // Stores Defence shield value...
#define DEF_MAGICTYPE_METAMORPHOSIS_WEAPONTYPE 	58 // Changes Mage to War
#define DEF_MAGICTYPE_METAMORPHOSIS_TEMP_DEXT	59 // Changes Mage to War
#define DEF_MAGICTYPE_METAMORPHOSIS 			60 // Changes Mage to War

#define DEF_MAXMAGICEFFECTS			100

class CMagic  
{									 
public:
	CMagic();
	virtual ~CMagic();

	char m_cName[31];

	short m_sType;
	DWORD m_dwDelayTime, m_dwLastTime;
	short m_sValue1, m_sValue2, m_sValue3, m_sValue4, m_sValue5, m_sValue6;
	short m_sValue7, m_sValue8, m_sValue9, m_sValue10, m_sValue11, m_sValue12;
	short m_sIntLimit;
	int   m_iGoldCost;
	
	char  m_cCategory; // ¸¶aý Ál·u: RDaÝ ¸¶aý 0, °r°Ý¸¶aý 1, aclî ¸¶aý 2 
	int   m_iAttribute; // ¸¶aý LÓLs:  ¶A 1 ÇD´A 2 sN 3 a° 4  
};

#endif // !defined(AFX_MAGIC_H__CD611900_EF3A_11D2_9B6C_00001C7030A6__INCLUDED_)

