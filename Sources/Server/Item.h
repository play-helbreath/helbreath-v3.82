// Item.h: interface for the CItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEM_H__211A1360_91B9_11D2_B143_00001C7030A6__INCLUDED_)
#define AFX_ITEM_H__211A1360_91B9_11D2_B143_00001C7030A6__INCLUDED_

#include <windows.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
										   
#define DEF_MAXITEMEQUIPPOS		15
#define DEF_EQUIPPOS_NONE		0	
#define DEF_EQUIPPOS_HEAD		1	//66Ah	m_pClientList[]->m_sItemEquipmentStatus[DEF_EQUIPPOS_HEAD]
#define DEF_EQUIPPOS_BODY		2	//66Ch	m_pClientList[]->m_sItemEquipmentStatus[DEF_EQUIPPOS_BODY]
#define DEF_EQUIPPOS_ARMS		3	//66Eh	m_pClientList[]->m_sItemEquipmentStatus[DEF_EQUIPPOS_ARMS]
#define DEF_EQUIPPOS_PANTS		4	//670h	m_pClientList[]->m_sItemEquipmentStatus[DEF_EQUIPPOS_PANTS]
#define DEF_EQUIPPOS_FOOT		5	//672h	m_pClientList[]->m_sItemEquipmentStatus[DEF_EQUIPPOS_FOOT]
#define DEF_EQUIPPOS_NECK		6   //674h	m_pClientList[]->m_sItemEquipmentStatus[DEF_EQUIPPOS_NECK]
#define DEF_EQUIPPOS_LHAND		7	//676h  m_pClientList[]->m_sItemEquipmentStatus[DEF_EQUIPPOS_LHAND]
#define DEF_EQUIPPOS_RHAND		8	//678h	m_pClientList[]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND]
#define DEF_EQUIPPOS_TWOHAND	9	//67Ah	m_pClientList[]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND]
#define DEF_EQUIPPOS_RFINGER	10	//67Ch
#define DEF_EQUIPPOS_LFINGER	11	//67Eh
#define DEF_EQUIPPOS_BACK		12  //680h
#define DEF_EQUIPPOS_RELEASEALL	13	//682h
 
#define DEF_ITEMTYPE_NOTUSED	-1	// v1.4 기존에 사용되었으나 현재로서는 사용되지 않는 아이템: 포상금으로 대체된다.
#define DEF_ITEMTYPE_NONE		 0
#define DEF_ITEMTYPE_EQUIP		 1
#define DEF_ITEMTYPE_APPLY		 2
#define DEF_ITEMTYPE_USE_DEPLETE 3  // Client will make it transparent, waiting for the server to delete it...     
#define DEF_ITEMTYPE_INSTALL	 4
#define DEF_ITEMTYPE_CONSUME	 5
#define DEF_ITEMTYPE_ARROW		 6
#define DEF_ITEMTYPE_EAT		 7
#define DEF_ITEMTYPE_USE_SKILL   8
#define DEF_ITEMTYPE_USE_PERM    9
#define DEF_ITEMTYPE_USE_SKILL_ENABLEDIALOGBOX	10
#define DEF_ITEMTYPE_USE_DEPLETE_DEST			11
#define DEF_ITEMTYPE_MATERIAL					12
#define DEF_ITEMTYPE_BOMB						66	// Add by Snoopy


#define DEF_ITEMEFFECTTYPE_NONE				0
#define DEF_ITEMEFFECTTYPE_ATTACK			1		// 공격치: value1 D value2 + value3
#define DEF_ITEMEFFECTTYPE_DEFENSE			2		// 방어능력 
#define DEF_ITEMEFFECTTYPE_ATTACK_ARROW		3		// 화살을 사용하는 공격무기. 무기 자체는 공격력이 없다.		
#define DEF_ITEMEFFECTTYPE_HP   		    4		// HP관련 효과 
#define DEF_ITEMEFFECTTYPE_MP   		    5		// MP관련 효과 
#define DEF_ITEMEFFECTTYPE_SP   		    6		// SP관련 효과 
#define DEF_ITEMEFFECTTYPE_HPSTOCK 		    7		// HP관련 효과. 즉각적으로 반응이 나타나지는 않는다. 
#define DEF_ITEMEFFECTTYPE_GET			    8		// 얻는다. 물고기나 광물등 
#define DEF_ITEMEFFECTTYPE_STUDYSKILL		9		// 기술을 배우는 아이템이다.
#define DEF_ITEMEFFECTTYPE_SHOWLOCATION		10		// 위치를 표시하는 아이템. 
#define DEF_ITEMEFFECTTYPE_MAGIC			11		// 사용하면 마법 효과를 얻는 아이템 
#define DEF_ITEMEFFECTTYPE_CHANGEATTR		12		// 플레이어의 속성을 변환시킨다. 성별, 머리모양, 피부색, 헤어스타일 
#define DEF_ITEMEFFECTTYPE_ATTACK_MANASAVE	13		// 공격효과와 더불어 마나의 절약 효과가 있다.(마법사용)
#define DEF_ITEMEFFECTTYPE_ADDEFFECT	    14		// 추가 효과
#define DEF_ITEMEFFECTTYPE_MAGICDAMAGESAVE	15		// 마법으로 인한 공격의 대미지를 절감한다. 반지나 목걸이류 
#define DEF_ITEMEFFECTTYPE_OCCUPYFLAG		16		// 점령 깃발 
#define DEF_ITEMEFFECTTYPE_DYE				17		// 염색약. 
#define DEF_ITEMEFFECTTYPE_STUDYMAGIC		18		// 마법을 배우는 아이템이다.
#define DEF_ITEMEFFECTTYPE_ATTACK_MAXHPDOWN	19		// 공격 효과와 함께 최대  HP 및 HP 회복량이 떨어지는 아이템 
#define DEF_ITEMEFFECTTYPE_ATTACK_DEFENSE	20		// 공격 효과와 함께 갑옷과 같이 물리 방어구 효과가 있는 아이템 
#define DEF_ITEMEFFECTTYPE_MATERIAL_ATTR	21		// 무기 제작 재료 속성 
#define DEF_ITEMEFFECTTYPE_FIRMSTAMINAR		22		// 스태미너 고정 아이템 
#define DEF_ITEMEFFECTTYPE_LOTTERY			23		// 복권 아이템
#define DEF_ITEMEFFECTTYPE_ATTACK_SPECABLTY		24	// 공격 아이템 특수 효과 
#define DEF_ITEMEFFECTTYPE_DEFENSE_SPECABLTY	25	// 방어구 아이템 특수 효과 
#define DEF_ITEMEFFECTTYPE_ALTERITEMDROP		26	// ZemStone of sacrifice
#define DEF_ITEMEFFECTTYPE_CONSTRUCTIONKIT		27	// 건축 키트
#define DEF_ITEMEFFECTTYPE_WARM				28		// Unfreeze pot ?
#define DEF_ITEMEFFECTTYPE_FARMING			30
#define DEF_ITEMEFFECTTYPE_SLATES			31
#define DEF_ITEMEFFECTTYPE_ARMORDYE			32
#define DEF_ITEMEFFECTTYPE_CRIT				33		// Adds single Crit
#define DEF_ITEMEFFECTTYPE_BOMB				66		// Add by Snoopy
#define DEF_ITEMEFFECTTYPE_EVENT_ITEMDROP	67		// Item that will drop even before any ZemStone of sacrifice, for events

#define DEF_ITET_UNIQUE_OWNER				1		// ItemTouchEffect: 주인을 갖는 아이템 
#define DEF_ITET_ID							2		// 그냥 아이템 아이디
#define DEF_ITET_DATE						3		// 사용가능한 날짜가 지정된 아이템 


class CItem  
{
public:
	CItem();
	virtual ~CItem();

	char  m_cName[21];
	
	short m_sIDnum;					// 아이템의 고유 번호
	char  m_cItemType;
	char  m_cEquipPos;
	short m_sItemEffectType;     
	short m_sItemEffectValue1, m_sItemEffectValue2, m_sItemEffectValue3; 
	short m_sItemEffectValue4, m_sItemEffectValue5, m_sItemEffectValue6; 
	WORD  m_wMaxLifeSpan;
	short m_sSpecialEffect;
	
	// re introduced by SNOOPY using m_sSpecialEffectValue1/2
	//short m_sSM_HitRatio, m_sL_HitRatio;
	short m_sSpecialEffectValue1, m_sSpecialEffectValue2; 

	short m_sSprite;
	short m_sSpriteFrame;

	char  m_cApprValue;
	char  m_cSpeed;

	DWORD m_wPrice; 
	WORD  m_wWeight;
	short m_sLevelLimit;	
	char  m_cGenderLimit;

	short m_sRelatedSkill;
	
	char  m_cCategory;		// Used for sell/repair dye categories....
	BOOL  m_bIsForSale;

	DWORD m_dwCount;
	short m_sTouchEffectType;
	short m_sTouchEffectValue1, m_sTouchEffectValue2, m_sTouchEffectValue3;
	char  m_cItemColor; // v1.4 에서 아이템 색으로 변경되었다. 
	short m_sItemSpecEffectValue1, m_sItemSpecEffectValue2, m_sItemSpecEffectValue3;
	WORD  m_wCurLifeSpan;
	DWORD m_dwAttribute;				// aaaa bbbb cccc dddd eeee ffff xxxx xxx1 
										// 1: Custom-Made Item flag 
										// a: Item Xelima upgraded
										// b: 
										// c: Stat Flag 
										// d: Stat value
										// e: 2nd stat Flag
										// f: 2nd stat value
										 

};

/*
아이템 정의파일에 필요한 내용 - 게임 서버용

char cItemType
 - 아이템의 종류. 장착되는 것인지 소모되는 것인지에 대한 정의

char cEquipPos
 - 장착되는 아이템이라면 그 위치 

short sItemEffectType     
  - 아이템의 효과 종류.  

short sItemEffectValue1, 2, 3 ... 
 - 아이템 효과의 수치 1, 2, 3...

WORD wMaxLifeSpan
 - 아이템의 최대 수명 

short sMaxFixCount
 - 최대 고칠수 있는 횟수

short sSprite
short sSpriteFrame
 - 아이템 스프라이트 번호 

WORD  wPrice 
 - 아이템 가격 
WORD  wWeight
 - 아이템 무게 
short sLevelLimit
 - 아이템 레벨 제한 
char  cGenderLimit
 - 아이템 성별 제한 

short m_SM_HitRatio, m_sL_HitRatio
 - 목표별 명중률 가감치 (무기일 경우)

short sRelatedSkill
 - 연결된 Skill

플레이어 데이터 파일에 저장되어야 할 정보 - 로그 서버용 

DWORD dwCount
 - 아이템의 갯수. (같은 종류의 화살이나 포션, Gold등만이 의미를 갖는다)

WORD wCurLifeSpan
 - 현재 남은 수명 

short sCurFixCount
 - 현재까지 수리한 횟수 

short sTouchEffectType
 - 아이템을 처음 건드렸을때 작동되는 효과 종류 

short sTouchEffectValue1, 2, 3...
 - 아이템 접촉 효과의 수치 

short sItemSpecEffectType
 - 아이템의 특수효과 종류 (ex:마법이 걸린 무기라면 공격력이나 방어력에 영향이 있을수도)

short sItemSpecEffectValue1, 2, 3...
 - 아이템 특수효과의 수치 1, 2, 3...


옷 아이템인 경우(Equip Position이 Body, Leggings, Arms인 경우)
sItemEffectValue4: 옷의 특정 특성치 제한 종류를 나타낸다. 

  10: Str
  11: Dex
  12: Vit
  13: Int
  14: Mag
  15: Chr

sItemEffectValue5: 옷의 특정 특성치 제한 수준



*/

#endif // !defined(AFX_ITEM_H__211A1360_91B9_11D2_B143_00001C7030A6__INCLUDED_)
