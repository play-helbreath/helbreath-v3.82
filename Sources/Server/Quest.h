// Quest.h: interface for the CQuest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUEST_H__3E61C780_FF48_11D3_9DC2_00A0CC5B45EE__INCLUDED_)
#define AFX_QUEST_H__3E61C780_FF48_11D3_9DC2_00A0CC5B45EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>


#define DEF_QUESTTYPE_MONSTERHUNT				1		// ÀÏ¹ÝÀûÀÎ ¸ó½ºÅÍ ÇåÆÃ 
#define DEF_QUESTTYPE_MONSTERHUNT_TIMELIMIT		2		// ½Ã°£ Á¦ÇÑÀÌ °É·ÁÀÖ´Â ¸ó½ºÅÍ ÇåÆÃ 
#define DEF_QUESTTYPE_ASSASSINATION 			3		// ¾Ï»ì 
#define DEF_QUESTTYPE_DELIVERY					4		// ¹è´Þ: Æ¯Á¤ Àå¼Ò·Î ¾ÆÀÌÅÛÀ» ¹è´ÞÇÑ´Ù.
#define DEF_QUESTTYPE_ESCORT					5		// º¸È£: Æ¯Á¤ Ä³¸¯ÅÍ¸¦ º¸È£ÇÑ´Ù.
#define DEF_QUESTTYPE_GUARD						6		// Æ¯Á¤ Áö¿ªÀ» ÀûÀÇ °ø°ÝÀ¸·ÎºÎÅÍ ¹æ¾îÇÑ´Ù. 
#define DEF_QUESTTYPE_GOPLACE					7		// Æ¯Á¤ Àå¼Ò·Î °£´Ù. Àû±¹ Ä§Åõ 
#define DEF_QUESTTYPE_BUILDSTRUCTURE			8		// ±¸Á¶¹° ¼³Ä¡ ÀÓ¹«
#define DEF_QUESTTYPE_SUPPLYBUILDSTRUCTURE		9		// ±¸Á¶¹° ¼³Ä¡ º¸±Þ ÀÓ¹«
#define DEF_QUESTTYPE_STRATEGICSTRIKE			10		// Àü¼úÀû Æø°ÝÀÓ¹« 
#define DEF_QUESTTYPE_SENDTOBATTLE				11		// °ð¹Ù·Î ±³ÀüÀå¼Ò Âü°¡ÇÏ´Â ÀÓ¹«
#define DEF_QUESTTYPE_SETOCCUPYFLAG				12		// ¿µÅä Á¡·É ±ê¹ßÀ» ¼³Ä¡ÇÏ´Â ÀÓ¹« 

class CQuest  
{
public:
	
	char m_cSide;				// 0: Neutral, 1:Ares, 2:Elvine, 4:Executor
	
	int m_iType;				// Quest Á¾·ù 
	int m_iTargetType;			// QuestÀÇ ¸ñÇ¥ Á¾·ù. °¢ Type¿¡ µû¶ó ´Ù¸¥ °ªÀÌ Á¤ÇØÁø´Ù. 
	int m_iMaxCount;			// ÃÖ´ë ¸¸Á· È½¼ö 

	int m_iFrom;				// Quest¸¦ ³»·ÁÁÖ´Â NPC Á¾·ù 
	
	int m_iMinLevel;			// Quest¸¦ ¹Þ±â À§ÇÑ ÃÖÀú ·¹º§. 
	int m_iMaxLevel;			// Quest¸¦ ¹Þ±â À§ÇÑ ÃÖ´ë ·¹º§ 

	int m_iRequiredSkillNum;	// Á¶°Ç ÆÇ´Ü¿¡ ÇÊ¿äÇÑ ½ºÅ³ ¹øÈ£ 
	int m_iRequiredSkillLevel;	// Á¶°Ç ÆÇ´Ü¿¡ ÇÊ¿äÇÑ ½ºÅ³ ·¹º§ 

	int m_iTimeLimit; 			// ½Ã°£ Á¦ÇÑ ÀÜÁ¸·® 
	int m_iAssignType;			// Äù½ºÆ® ÇÒ´ç Å¸ÀÔ. -1ÀÌ¸é ¾Æ¹«¶§³ª. 1ÀÌ¸é Crusade Àü¸éÀüÀÏ¶§¸¸.

								// »óÇ° Á¾·ù ¹× ¼ö·®. 3°³ Áß 1°³°¡ ·£´ýÇÏ°Ô Á¤ÇØÁü. 0¹ø ÀÎµ¦½º´Â »ç¿ë ¾ÈÇÔ.
	int m_iRewardType[4]; 
	int m_iRewardAmount[4];

	int m_iContribution;		// °øÇåµµ 
	int m_iContributionLimit;	// ÃÖ´ë °øÇåµµ Á¦ÇÑ 

	int m_iResponseMode;		// ÀÀ´ä ¸ðµå: 0(ok) 1(Accept/Decline) 2(Next)

	char m_cTargetName[21];		// Äù½ºÆ®°¡ ÁöÁ¤µÈ ÀÌ¸§. ¸Ê È¤Àº Ä³¸¯ÅÍ ÀÌ¸§  
	int  m_sX, m_sY, m_iRange;	// Äù½ºÆ®°¡ ÁöÁ¤µÈ ¸Ê Àå¼Ò 

	int  m_iQuestID;			// Äù½ºÆ® ID. ¸¸¾à Äù½ºÆ®ÀÇ ³»¿ëÀÌ º¯°æµÇ¾úÀ» °æ¿ì¸¦ ´ëºñÇÑ °ÍÀÓ.

	int  m_iReqContribution;	// Äù½ºÆ®¸¦ ¸Ã±â À§ÇÑ ÃÖÀú °øÇåµµ Á¦ÇÑ. 


	//CQuest();
	//virtual ~CQuest();

};

#endif // !defined(AFX_QUEST_H__3E61C780_FF48_11D3_9DC2_00A0CC5B45EE__INCLUDED_)
