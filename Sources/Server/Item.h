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
 
#define DEF_ITEMTYPE_NOTUSED	-1	// v1.4 ±âÁ¸¿¡ »ç¿ëµÇ¾úÀ¸³ª ÇöÀç·Î¼­´Â »ç¿ëµÇÁö ¾Ê´Â ¾ÆÀÌÅÛ: Æ÷»ó±ÝÀ¸·Î ´ëÃ¼µÈ´Ù.
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
#define DEF_ITEMEFFECTTYPE_ATTACK			1		// °ø°ÝÄ¡: value1 D value2 + value3
#define DEF_ITEMEFFECTTYPE_DEFENSE			2		// ¹æ¾î´É·Â 
#define DEF_ITEMEFFECTTYPE_ATTACK_ARROW		3		// È­»ìÀ» »ç¿ëÇÏ´Â °ø°Ý¹«±â. ¹«±â ÀÚÃ¼´Â °ø°Ý·ÂÀÌ ¾ø´Ù.		
#define DEF_ITEMEFFECTTYPE_HP   		    4		// HP°ü·Ã È¿°ú 
#define DEF_ITEMEFFECTTYPE_MP   		    5		// MP°ü·Ã È¿°ú 
#define DEF_ITEMEFFECTTYPE_SP   		    6		// SP°ü·Ã È¿°ú 
#define DEF_ITEMEFFECTTYPE_HPSTOCK 		    7		// HP°ü·Ã È¿°ú. Áï°¢ÀûÀ¸·Î ¹ÝÀÀÀÌ ³ªÅ¸³ªÁö´Â ¾Ê´Â´Ù. 
#define DEF_ITEMEFFECTTYPE_GET			    8		// ¾ò´Â´Ù. ¹°°í±â³ª ±¤¹°µî 
#define DEF_ITEMEFFECTTYPE_STUDYSKILL		9		// ±â¼úÀ» ¹è¿ì´Â ¾ÆÀÌÅÛÀÌ´Ù.
#define DEF_ITEMEFFECTTYPE_SHOWLOCATION		10		// À§Ä¡¸¦ Ç¥½ÃÇÏ´Â ¾ÆÀÌÅÛ. 
#define DEF_ITEMEFFECTTYPE_MAGIC			11		// »ç¿ëÇÏ¸é ¸¶¹ý È¿°ú¸¦ ¾ò´Â ¾ÆÀÌÅÛ 
#define DEF_ITEMEFFECTTYPE_CHANGEATTR		12		// ÇÃ·¹ÀÌ¾îÀÇ ¼Ó¼ºÀ» º¯È¯½ÃÅ²´Ù. ¼ºº°, ¸Ó¸®¸ð¾ç, ÇÇºÎ»ö, Çì¾î½ºÅ¸ÀÏ 
#define DEF_ITEMEFFECTTYPE_ATTACK_MANASAVE	13		// °ø°ÝÈ¿°ú¿Í ´õºÒ¾î ¸¶³ªÀÇ Àý¾à È¿°ú°¡ ÀÖ´Ù.(¸¶¹ý»ç¿ë)
#define DEF_ITEMEFFECTTYPE_ADDEFFECT	    14		// Ãß°¡ È¿°ú
#define DEF_ITEMEFFECTTYPE_MAGICDAMAGESAVE	15		// ¸¶¹ýÀ¸·Î ÀÎÇÑ °ø°ÝÀÇ ´ë¹ÌÁö¸¦ Àý°¨ÇÑ´Ù. ¹ÝÁö³ª ¸ñ°ÉÀÌ·ù 
#define DEF_ITEMEFFECTTYPE_OCCUPYFLAG		16		// Á¡·É ±ê¹ß 
#define DEF_ITEMEFFECTTYPE_DYE				17		// ¿°»ö¾à. 
#define DEF_ITEMEFFECTTYPE_STUDYMAGIC		18		// ¸¶¹ýÀ» ¹è¿ì´Â ¾ÆÀÌÅÛÀÌ´Ù.
#define DEF_ITEMEFFECTTYPE_ATTACK_MAXHPDOWN	19		// °ø°Ý È¿°ú¿Í ÇÔ²² ÃÖ´ë  HP ¹× HP È¸º¹·®ÀÌ ¶³¾îÁö´Â ¾ÆÀÌÅÛ 
#define DEF_ITEMEFFECTTYPE_ATTACK_DEFENSE	20		// °ø°Ý È¿°ú¿Í ÇÔ²² °©¿Ê°ú °°ÀÌ ¹°¸® ¹æ¾î±¸ È¿°ú°¡ ÀÖ´Â ¾ÆÀÌÅÛ 
#define DEF_ITEMEFFECTTYPE_MATERIAL_ATTR	21		// ¹«±â Á¦ÀÛ Àç·á ¼Ó¼º 
#define DEF_ITEMEFFECTTYPE_FIRMSTAMINAR		22		// ½ºÅÂ¹Ì³Ê °íÁ¤ ¾ÆÀÌÅÛ 
#define DEF_ITEMEFFECTTYPE_LOTTERY			23		// º¹±Ç ¾ÆÀÌÅÛ
#define DEF_ITEMEFFECTTYPE_ATTACK_SPECABLTY		24	// °ø°Ý ¾ÆÀÌÅÛ Æ¯¼ö È¿°ú 
#define DEF_ITEMEFFECTTYPE_DEFENSE_SPECABLTY	25	// ¹æ¾î±¸ ¾ÆÀÌÅÛ Æ¯¼ö È¿°ú 
#define DEF_ITEMEFFECTTYPE_ALTERITEMDROP		26	// ZemStone of sacrifice
#define DEF_ITEMEFFECTTYPE_CONSTRUCTIONKIT		27	// °ÇÃà Å°Æ®
#define DEF_ITEMEFFECTTYPE_WARM				28		// Unfreeze pot ?
#define DEF_ITEMEFFECTTYPE_FARMING			30
#define DEF_ITEMEFFECTTYPE_SLATES			31
#define DEF_ITEMEFFECTTYPE_ARMORDYE			32
#define DEF_ITEMEFFECTTYPE_CRIT				33		// Adds single Crit
#define DEF_ITEMEFFECTTYPE_BOMB				66		// Add by Snoopy
#define DEF_ITEMEFFECTTYPE_EVENT_ITEMDROP	67		// Item that will drop even before any ZemStone of sacrifice, for events

#define DEF_ITET_UNIQUE_OWNER				1		// ItemTouchEffect: ÁÖÀÎÀ» °®´Â ¾ÆÀÌÅÛ 
#define DEF_ITET_ID							2		// ±×³É ¾ÆÀÌÅÛ ¾ÆÀÌµð
#define DEF_ITET_DATE						3		// »ç¿ë°¡´ÉÇÑ ³¯Â¥°¡ ÁöÁ¤µÈ ¾ÆÀÌÅÛ 


class CItem  
{
public:
	CItem();
	virtual ~CItem();

	char  m_cName[21];
	
	short m_sIDnum;					// ¾ÆÀÌÅÛÀÇ °íÀ¯ ¹øÈ£
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
	char  m_cItemColor; // v1.4 ¿¡¼­ ¾ÆÀÌÅÛ »öÀ¸·Î º¯°æµÇ¾ú´Ù. 
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
¾ÆÀÌÅÛ Á¤ÀÇÆÄÀÏ¿¡ ÇÊ¿äÇÑ ³»¿ë - °ÔÀÓ ¼­¹ö¿ë

char cItemType
 - ¾ÆÀÌÅÛÀÇ Á¾·ù. ÀåÂøµÇ´Â °ÍÀÎÁö ¼Ò¸ðµÇ´Â °ÍÀÎÁö¿¡ ´ëÇÑ Á¤ÀÇ

char cEquipPos
 - ÀåÂøµÇ´Â ¾ÆÀÌÅÛÀÌ¶ó¸é ±× À§Ä¡ 

short sItemEffectType     
  - ¾ÆÀÌÅÛÀÇ È¿°ú Á¾·ù.  

short sItemEffectValue1, 2, 3 ... 
 - ¾ÆÀÌÅÛ È¿°úÀÇ ¼öÄ¡ 1, 2, 3...

WORD wMaxLifeSpan
 - ¾ÆÀÌÅÛÀÇ ÃÖ´ë ¼ö¸í 

short sMaxFixCount
 - ÃÖ´ë °íÄ¥¼ö ÀÖ´Â È½¼ö

short sSprite
short sSpriteFrame
 - ¾ÆÀÌÅÛ ½ºÇÁ¶óÀÌÆ® ¹øÈ£ 

WORD  wPrice 
 - ¾ÆÀÌÅÛ °¡°Ý 
WORD  wWeight
 - ¾ÆÀÌÅÛ ¹«°Ô 
short sLevelLimit
 - ¾ÆÀÌÅÛ ·¹º§ Á¦ÇÑ 
char  cGenderLimit
 - ¾ÆÀÌÅÛ ¼ºº° Á¦ÇÑ 

short m_SM_HitRatio, m_sL_HitRatio
 - ¸ñÇ¥º° ¸íÁß·ü °¡°¨Ä¡ (¹«±âÀÏ °æ¿ì)

short sRelatedSkill
 - ¿¬°áµÈ Skill

ÇÃ·¹ÀÌ¾î µ¥ÀÌÅÍ ÆÄÀÏ¿¡ ÀúÀåµÇ¾î¾ß ÇÒ Á¤º¸ - ·Î±× ¼­¹ö¿ë 

DWORD dwCount
 - ¾ÆÀÌÅÛÀÇ °¹¼ö. (°°Àº Á¾·ùÀÇ È­»ìÀÌ³ª Æ÷¼Ç, Goldµî¸¸ÀÌ ÀÇ¹Ì¸¦ °®´Â´Ù)

WORD wCurLifeSpan
 - ÇöÀç ³²Àº ¼ö¸í 

short sCurFixCount
 - ÇöÀç±îÁö ¼ö¸®ÇÑ È½¼ö 

short sTouchEffectType
 - ¾ÆÀÌÅÛÀ» Ã³À½ °Çµå·ÈÀ»¶§ ÀÛµ¿µÇ´Â È¿°ú Á¾·ù 

short sTouchEffectValue1, 2, 3...
 - ¾ÆÀÌÅÛ Á¢ÃË È¿°úÀÇ ¼öÄ¡ 

short sItemSpecEffectType
 - ¾ÆÀÌÅÛÀÇ Æ¯¼öÈ¿°ú Á¾·ù (ex:¸¶¹ýÀÌ °É¸° ¹«±â¶ó¸é °ø°Ý·ÂÀÌ³ª ¹æ¾î·Â¿¡ ¿µÇâÀÌ ÀÖÀ»¼öµµ)

short sItemSpecEffectValue1, 2, 3...
 - ¾ÆÀÌÅÛ Æ¯¼öÈ¿°úÀÇ ¼öÄ¡ 1, 2, 3...


¿Ê ¾ÆÀÌÅÛÀÎ °æ¿ì(Equip PositionÀÌ Body, Leggings, ArmsÀÎ °æ¿ì)
sItemEffectValue4: ¿ÊÀÇ Æ¯Á¤ Æ¯¼ºÄ¡ Á¦ÇÑ Á¾·ù¸¦ ³ªÅ¸³½´Ù. 

  10: Str
  11: Dex
  12: Vit
  13: Int
  14: Mag
  15: Chr

sItemEffectValue5: ¿ÊÀÇ Æ¯Á¤ Æ¯¼ºÄ¡ Á¦ÇÑ ¼öÁØ



*/

#endif // !defined(AFX_ITEM_H__211A1360_91B9_11D2_B143_00001C7030A6__INCLUDED_)
