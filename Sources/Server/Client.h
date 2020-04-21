// Client.h: interface for the CClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENT_H__39CC7700_789F_11D2_A8E6_00001C7030A6__INCLUDED_)
#define AFX_CLIENT_H__39CC7700_789F_11D2_A8E6_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GlobalDef.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "XSocket.h"
#include "Item.h"
#include "GuildsMan.h"
#include "Magic.h"

#define DEF_CLIENTSOCKETBLOCKLIMIT	15

//#define DEF_MSGBUFFERSIZE	30000
#define DEF_MSGBUFFERSIZE	50000
#define DEF_MAXITEMS		50
#define DEF_MAXBANKITEMS	120
#define DEF_MAXGUILDSMAN	128 // ÃÖ´ë ±æµå¿ø ¼ö 

#define	DEF_MAXMAGICTYPE	100	// º¯°æÇÏ·Á¸é ·Î±×¼­¹ö³»¿ëµµ ¹Ù²Ù¾î¾ß ÇÑ´Ù.
#define DEF_MAXSKILLTYPE	60

#define DEF_MAXPARTYMEMBERS	8

#define DEF_SPECABLTYTIMESEC	1200

class CClient  
{
public:
		
	char m_cVar;
	char m_cHeroArmourBonus;
	BOOL bCreateNewParty();

	//int m_iUninteruptibleCheck; BOOL m_bMagicItem

//*********************************************************************************	
// ANTI HACK
//*********************************************************************************	
	// Snoopy: Anti-Hack based on connection check by client.
	int m_iConnectionCheck;				// count packets beetween 2 connection checks
	DWORD dwTimeConnectionCheck;		// stores client time when sending connection check
	DWORD dwEventTimeConnectionCheck;	// stores server time when receiving connection check
	unsigned char  m_cMsgCount[11]; 

	// SNOOPY: Client Connexion Check Messages gap monitoring
	int  m_iTheoricGap;					// Calculated theoric Gap, (for comparation to expected one)
	int  m_iLowerGap;					// Lower observed gap      (if lower than allowed => wrong client)
	int  m_iLowerGapValidation;			// Counter before accepting a gap as the lower possible one.
	int  m_iTotalGap;					// Used to compute average gap client side
	int  m_iServerSideTotalGap;			// Used to compute average gap server side
	int  m_iNumberGap;					// Counter to compute average
	int  m_iNumberBadGap;				// Counter for wrong gaps.
	int  m_iLowServerGapCount;			// Conuter for too short server side gaps.
	char m_cPreviousKey;				// To check the Char key randomlly sent by client in Connexion Check Messages
	int  m_iNbeSameKey;					// Counter for successive similar Keys
	int  m_iMaxPackets;					// Store the max nbe of client packets received between 2 successive Connexion Check Messages
	bool m_bMonitorThisChar;			// Some more logging on this char, on GM command.

	WORD  m_wSignature1;				// Store Signature sent by Client..
	WORD  m_wSignature2;				// Store Signature sent by Client..
	int   i_iSignatureCount;			// Number of consecutive sigatures.

	// SNOOPY: Denial of service attack detection (using packet sniffer/sender)
	DWORD m_dwDSLAT, m_dwDSLATOld, m_dwDSLATS;
	int	  m_iDSCount;

	// SNOOPY: Moving Hack checkers
	BOOL  m_bIsMoveBlocked;
	DWORD m_dwWalkLAT,  m_dwWalkLATS,  m_dwRunLAT,  m_dwRunLATS;
	int	  m_iWalkTotal, m_iWalkTotalS, m_iRunTotal, m_iRunTotalS;
	int	  m_iWalkCount, m_iRunCount;

	// SNOOPY: DAMAGEMove tsearch hack detection...
	int   m_iLastDamage;
	int   m_dwLastDamageMoveTime;
	int   m_dwDamageMoveCounter;

	// Attack/Swing Hack checkers
	DWORD m_dwAttackLAT,  m_dwAttackLATS,  m_dwDashLAT;
	int	  m_iAttackTotal, m_iAttackTotalS, m_iDashTotal;
	int	  m_iAttackCount, m_iDashCount;
	int   m_iAttackCountOK, m_iAttackCountBad;

	// Potion Drink Delay hack
	DWORD m_dwPopoLATS;
	int   m_iPopoTotalS, m_iPopoCount;

	// Scroll delay hack, Instant LogOut (after damage)
	DWORD m_dwLastDamageTime;	

	// Precast Hack checkers
	DWORD m_dwPreCastLAT, m_dwPreCastLATS;
//	int	  m_iMagicTotal, m_iMagicTotalS;
//	int	  m_iMagicCount;

	short m_sPreCastSpellID;
	
	// Magic Hack Checkers
	BOOL  m_bMagicConfirm;		// Used to confirm that a spell was really casted when mesuring precast gaps.
	DWORD m_dwMagicFreqTime;	// Used to mesure gap betxeen 2 precast
	int   m_iSpellCount;		// Used to confirm that player precast before unbounding the spell

	// prevents two spells/swings in a 300ms (onTimer)
	DWORD m_dwRecentAttackTime;	// Basic action latence mesure, 

	// Activity checkers
	DWORD m_dwLastActionTime;	// To limit Party XP with AFK character, reset every Move/action
	DWORD m_dwAFKCheckTime;		// AFK player checker, reset every Chat/Move/action (shows on serveur screen)
	DWORD m_dwXPHackCheckTime;	// Hourlly XP check, also used as a reference time to stop AntiLameEK after a while 
	int   m_iXPHackCheckExp;	// Hourlly XP total
	BOOL  m_bAntiTPLameEK;	
	char  m_cDelayedDeco;

	// Skill Hack (Manuf/Alchi Paquets / Tsearch hacks)
	int  m_iSkillMsgRecvCount;	// Counts Skill messages (manuf & Alchim)
	
	// Very Rich players log
	int  m_KnownPreviousGold;


//*********************************************************************************	

	char m_cKlonessMiscDamageBonus;	// By Snoopy, for zerk wands kloness etc....
	char m_cKlonessNeckDamageBonus;	// By Snoopy
	CClient(HWND hWnd);
	virtual ~CClient();

	char m_cCharName[11];
	char m_cAccountName[11];
	char m_cAccountPassword[11];

	BOOL  m_bIsInitComplete;
	BOOL  m_bIsMsgSendAvailable;

	char  m_cMapName[11];
	char  m_cMapIndex;
	short m_sX, m_sY;
	
	char  m_cGuildName[21];		// ±æµåÀÇ ÀÌ¸§ 
	char  m_cLocation[11];      //  <- ¸ÊÀÌ¸§ÀÌ ±×´ë·Î ÀúÀåµÈ´Ù. ¼Ò¼Ó ¸¶À» 
	int   m_iGuildRank;			// -1ÀÌ¸é ¹«ÀÇ¹Ì. 0ÀÌ¸é ±æµå ¸¶½ºÅÍ. ¾ç¼ö´Â ±æµå³»¿¡¼­ÀÇ ¼­¿­ 
	int   m_iGuildGUID;
	
	char  m_cDir;
	short m_sType;				// ÇöÀç Å¸ÀÔ <- Æú¸®¸ðÇÁ ½Ã¿¡ º¯ÇÑ´Ù. 
	short m_sOriginalType;		// ¿À¸®Áö³¯ Å¸ÀÔ
	short m_sAppr1;
	short m_sAppr2;
	short m_sAppr3;
	short m_sAppr4;
	int   m_iApprColor;			// v1.4 ¿ÜÇü ÄÃ·¯Å×ÀÌºí
	int   m_iStatus;

	DWORD m_dwTime, m_dwHPTime, m_dwMPTime, m_dwSPTime, m_dwAutoSaveTime, m_dwHungerTime, m_dwWarmEffectTime;
	// Player m_dwTime is reset at each succesfully received client's message.

	char m_cSex, m_cSkin, m_cHairStyle, m_cHairColor, m_cUnderwear;

	int  m_iHP;						// Hit Point
	int  m_iHPstock;
	int  m_iMP;
	int  m_iSP;
	int  m_iExp;
	int  m_iNextLevelExp;
	BOOL m_bIsKilled;

	int  m_iDefenseRatio;		// Defense Ratio
	int  m_iDefenseRatio2;		// Snoopy: Defense Ratio2 for HIGH PvP ToHit  mode
	int  m_iDefenseRatio3;		// Snoopy: Defense Ratio3 excludind any armor natural defence
	int  m_iHitRatio;			// Hit Ratio
	int  m_iHitRatio3;			// Hit Ratio3 doesn't take into account any weapon skill % (for Metamorphosis)
	int  m_bSpecialFeatureAllowed; // Flag to allow special features depending on equipment or other conditions (ie: Monks, Barbarians, Druids...)

	// SNOOPY: for simplier Priests/Druids.
	int  m_iPriestDruidID;
	// Snoopy: for special sets effects.
	int m_iSetEffect;

	// re introduced by SNOOPY
	int  m_iHitRatio_ItemEffect_SM; // SNOOPY Added this again
	int  m_iHitRatio_ItemEffect_L;
	int  m_iMagicHitRatio_ItemEffect; // By Snoopy (for special wands)

	int  m_iDamageAbsorption_Armor[DEF_MAXITEMEQUIPPOS];
	int  m_iDamageAbsorption_Shield;	// Parrying 

	int  m_iLevel;
	int  m_iStr, m_iInt, m_iVit, m_iDex, m_iMag, m_iCharisma;
	int  m_iAngelicStr; // By Snoopy81
	int  m_iAngelicInt; // By Snoopy81
	int  m_iAngelicDex; // By Snoopy81
	int  m_iAngelicMag; // By Snoopy81
	//char m_cLU_Str, m_cLU_Int, m_cLU_Vit, m_cLU_Dex, m_cLU_Mag, m_cLU_Char;
	int  m_iLuck; 
	int  m_iLU_Pool;
	char m_cAura;
	//MOG var - 3.51
	int m_iGizonItemUpgradeLeft;

	int  m_iValidationNumber; // Safety check by SNOOPY
	int	 m_iCrazyPlayerKiller; // Snoopy: check for Players loving PvP, maybe too much!
	bool m_bKilledByPlayerKiller; // Snoopy: Check to see who performed the Kill, PK, EK...

	int m_iAddTransMana, m_iAddChargeCritical;

	int  m_iEnemyKillCount, m_iPKCount, m_iRewardGold;
	int  m_iCurWeightLoad;		// 

	char m_cSide;				// ÇÃ·¹ÀÌ¾îÀÇ Æí 
	
	BOOL m_bInhibition;
	//Add by Snoopy
	BOOL m_bInvincibleSlate;
	BOOL m_bManaSlate;
	BOOL m_bXpSlate;

	char m_cAttackDiceThrow_SM;	// °ø°ÝÄ¡ ÁÖ»çÀ§ ´øÁö´Â È¸¼ö 
	char m_cAttackDiceRange_SM;	// °ø°ÝÄ¡ ÁÖ»çÀ§ ¹üÀ§ 
	char m_cAttackDiceThrow_L;	// °ø°ÝÄ¡ ÁÖ»çÀ§ ´øÁö´Â È¸¼ö 
	char m_cAttackDiceRange_L;	// °ø°ÝÄ¡ ÁÖ»çÀ§ ¹üÀ§ 
	char m_cAttackBonus_SM;		// °ø°Ý º¸³Ê½º
	char m_cAttackBonus_L;		// °ø°Ý º¸³Ê½º

	class CItem * m_pItemList[DEF_MAXITEMS];
	POINT m_ItemPosList[DEF_MAXITEMS];
	class CItem * m_pItemInBankList[DEF_MAXBANKITEMS];
	
	BOOL  m_bIsItemEquipped[DEF_MAXITEMS];
	short m_sItemEquipmentStatus[DEF_MAXITEMEQUIPPOS];
	char  m_cArrowIndex;		// ÇÃ·¹ÀÌ¾î°¡ È°À» »ç¿ëÇÒ¶§ È­»ì ¾ÆÀÌÅÛ ÀÎµ¦½º. ÃÊ±â°ªÀº -1(ÇÒ´ç ¾ÈµÊ)

	char           m_cMagicMastery[DEF_MAXMAGICTYPE];
	unsigned char  m_cSkillMastery[DEF_MAXSKILLTYPE]; // v1.4

	int   m_iSkillSSN[DEF_MAXSKILLTYPE];
	BOOL  m_bSkillUsingStatus[DEF_MAXSKILLTYPE];
	int   m_iSkillUsingTimeID[DEF_MAXSKILLTYPE]; //v1.12

	char  m_cMagicEffectStatus[DEF_MAXMAGICEFFECTS];

	int   m_iWhisperPlayerIndex;
	char  m_cProfile[256];

	int   m_iHungerStatus;		// 


	BOOL  m_bIsPoisoned;		// Áßµ¶µÇ¾ú´ÂÁöÀÇ ¿©ºÎ 
	int   m_iPoisonLevel;       // µ¶ÀÇ °­µµ 
	DWORD m_dwPoisonTime;		// Áßµ¶ ½Ã°£.
	
	int   m_iPenaltyBlockYear, m_iPenaltyBlockMonth, m_iPenaltyBlockDay; // v1.4

	//v1.4311-3 Ãß°¡ º¯¼ö ¼±¾ð »çÅõÀå ¹øÈ£¿Í »çÅõÀå ¿¹¾àÇÑ ½Ã°£
	int   m_iFightzoneNumber , m_iReserveTime, m_iFightZoneTicketNumber ; 

	class XSocket * m_pXSock;

	int   m_iAdminUserLevel;     // °ü¸®ÀÚ ·¹º§. 0ÀÌ¸é ¹«È¿. ¹øÈ£°¡ ¿Ã¶ó°¥ ¼ö·Ï ±ÇÇÑÀÌ Ä¿Áø´Ù.
	int   m_iRating;
	int   m_iClientPrimaryDropRate;

	int   m_iTimeLeft_ShutUp;	 // ÀÌ °ªÀÌ 0ÀÌ ¾Æ´Ï¸é Ã¤ÆÃ¸Þ½ÃÁö°¡ Àü´ÞµÇÁö ¾Ê´Â´Ù.
	int   m_iTimeLeft_Rating;	 // ´Ù¸¥ ÇÃ·¹ÀÌ¾îÀÇ ÆòÆÇÀ» ¸Å±â±â À§ÇØ ³²Àº ½Ã°£. 0ÀÌ¸é »ç¿ë °¡´É 
	int   m_iTimeLeft_FirmStaminar; // ½ºÅÂ¹Ì³Ê°¡ ´Þ¾Æ ¾ø¾îÁöÁö ¾Ê´Â ½Ã°£ ÅÒ  
	int   m_iTimeLeft_ForceRecall;	// Time counter for force recall (counts by 3 seconds)
	BOOL  m_bIsWarLocation;			// True if m_iTimeLeft_ForceRecall needs to recall client


	int   m_iExpStock;			 // ½×¿©ÀÖ´Â °æÇèÄ¡ 
	DWORD m_dwExpStockTime;		 // ExpStock °è»ê ½Ã°£.

	int   m_iAutoExpAmount;		 // Auto-Exp ½Ã°£ µ¿¾È ¾òÀº °æÇèÄ¡ 
	DWORD m_dwAutoExpTime;		 // Auto-Exp °è»ê ½Ã°£.


	int   m_iAllocatedFish;		 // ÀÌ °ªÀÌ 0ÀÌ ¾Æ´Ï¸é ÀÌº¥Æ® ³¬½Ã¸ðµå¶ó´Â ÀÌ¾ß±â´Ù. 
	int   m_iFishChance;		 // ÇöÀç ³¬À» »óÅÂ 
	
	char  m_cIPaddress[21];		 // Å¬¶óÀÌ¾ðÆ®ÀÇ IP address
	BOOL  m_bIsSafeAttackMode;

	BOOL  m_bIsOnWaitingProcess;	// TRUE Means wait deletion and connection to other server.
									// Prevents another TP tentative, and LogoutHack Check
	
	int   m_iSuperAttackLeft;	 // v1.2 ÇÊ»ì±â »ç¿ë °¡´É È½¼ö 
	int   m_iSuperAttackCount;   // v1.2 ÇÊ»ì±â »ç¿ë °¡´É Ä«¿îÆ®. ÀÌ Ä«¿îÆ®°¡ ´Ù Â÷¸é ÇÊ»ì±â »ç¿ë È½¼ö°¡ ´Ã¾î³­´Ù. 

	short m_sUsingWeaponSkill;	 // v1.2 ÇöÀç »ç¿ëÇÏ´Â ¹«±âÀÇ ½ºÅ³ ÀÎµ¦½º 

	int   m_iManaSaveRatio;		 // v1.2 ¸¶³ª Àý¾à Æ÷ÀÎÆ® 
	
	int   m_bIsLuckyEffect;		 // v1.2 Çà¿î È¿°ú 
	int   m_iSideEffect_MaxHPdown; // v1.4 ÃÖ´ë HP Àý°¨ È¿°ú 

	int   m_iComboAttackCount;   // v1.3 ¿¬Å¸ °ø°Ý Ä«¿îÆ® 
	int   m_iDownSkillIndex;	 // v1.3 ´Ù¸¥ ½ºÅ³ÀÌ ¿Ã¶ó°¥¶§ ³»¸± ½ºÅ³ ÀÎµ¦½º 

	int   m_iMagicDamageSaveItemIndex; // v1.3 ¸¶¹ý °ø°Ý ´ë¹ÌÁö Àý°¨ ¾ÆÀÌÅÛ ÀÎµ¦½º (º¸ÅëÀº -1)

	short m_sCharIDnum1, m_sCharIDnum2, m_sCharIDnum3; // v1.3 ±× Ä³¸¯ÅÍ°¡ °®´Â °íÀ¯°ª!

	int   m_iAbuseCount;		// ÇØÅ· ¿ëÀÇÀÚ ÆÄ¾Ç¿ë 
	
	BOOL  m_bIsBWMonitor;		// BadWord ¸ð´ÏÅÍÀÎ°¡?

	//BOOL  m_bIsExchangeMode;		// ÇöÀç ¾ÆÀÌÅÛ ±³È¯ ¸ðµåÀÎ°¡? 
	//int   m_iExchangeH;				// ±³È¯ÇÒ ´ë»óÀÇ ÀÎµ¦½º 
	//char  m_cExchangeName[11];		// ±³È¯ÇÒ ´ë»óÀÇ ÀÌ¸§ 
	//char  m_cExchangeItemName[21];	// ±³È¯ÇÏ°íÀÚ ÇÏ´Â ¾ÆÀÌÅÛ ÀÌ¸§ 
	//char  m_cExchangeItemIndex;  // ±³È¯ÇÒ ¾ÆÀÌÅÛ ÀÎµ¦½º 
	//int   m_iExchangeItemAmount; // ±³È¯ÇÒ ¾ÆÀÌÅÛ °¹¼ö 
	//BOOL  m_bIsExchangeConfirm;  // ±³È¯ È®ÀÎ 


	BOOL  m_bIsExchangeConfirm;			// Has the user hit confirm? 	
	BOOL  m_bIsExchangeMode;			// Is In Exchange Mode? 
	int   m_iExchangeH;					// Client ID to Exchanging with 
	char  m_cExchangeName[11];			// Name of Client to Exchanging with 
	char  m_cExchangeItemName[4][21];	// Name of Item to exchange 
	char  m_cExchangeItemIndex[4];		// ItemID to Exchange
	int   m_iExchangeItemAmount[4];		// Ammount to exchange with
	int	  iExchangeCount;				// Keeps track of items which are on list

	int   m_iQuest;				// ÇöÀç ÇÒ´çµÈ Quest 
	int   m_iQuestID;			// ÇÒ´ç¹ÞÀº QuestÀÇ ID°ª 
	int   m_iAskedQuest;		// ¹°¾îº» Äù½ºÆ® 
	int   m_iCurQuestCount;		// ÇöÀç Äù½ºÆ® »óÅÂ 
	
	int   m_iQuestRewardType;	 // Äù½ºÆ® ÇØ°á½Ã »óÇ° Á¾·ù -> ¾ÆÀÌÅÛÀÇ ID°ªÀÌ´Ù.
	int   m_iQuestRewardAmount;	 // »óÇ° °¹¼ö 

	int   m_iContribution;		 // µµ½Ã¿¡ ´ëÇÑ °øÇåµµ. 

	BOOL  m_bQuestMatchFlag_Loc; // Äù½ºÆ® ¼öÇà Á¶°ÇÀ» ÆÇ´ÜÇÏ±â À§ÇÔ.
	BOOL  m_bIsQuestCompleted;   // Äù½ºÆ®°¡ ¿Ï·áµÇ¾ú´Â°¡? 

	int   m_iCustomItemValue_Attack;
	int   m_iCustomItemValue_Defense;

	int   m_iMinAP_SM;			// Custom-ItemÀÇ È¿°ú·Î ÀÎÇÑ ÃÖ¼Ò AP
	int   m_iMinAP_L;

	int   m_iMaxAP_SM;			// Custom-ItemÀÇ È¿°ú·Î ÀÎÇÑ ÃÖ´ë AP
	int   m_iMaxAP_L;

	BOOL  m_bIsNeutral;			// v1.5 Áß¸³¿©ºÎ¸¦ ÆÇº°ÇÏ±â À§ÇÑ ÇÃ·¡±×. Ã³¸® ¼Óµµ¸¦ ³ôÀÌ±â À§ÇÔÀÌ´Ù.
	BOOL  m_bIsObserverMode;	// v1.5 °ü¶÷ÀÚ ¸ðµåÀÎÁö ÆÇº° 

	int   m_iSpecialEventID;	// Æ¯¼ö Çà»ç Âü°¡È®ÀÎ¿ë ÇÃ·¡±× 

	int   m_iSpecialWeaponEffectType;	// Èñ±Í ¾ÆÀÌÅÛ È¿°ú Á¾·ù
	int   m_iSpecialWeaponEffectValue;	// Èñ±Í ¾ÆÀÌÅÛ È¿°ú °ª
	int   m_iSpecialWeaponEffectSpell;


	// v1.42
	int   m_iAddHP, m_iAddSP, m_iAddMP; 
	int   m_iAddAR, m_iAddPR, m_iAddDR;
	int   m_iAddMR, m_iAddAbsPD, m_iAddAbsMD; 
	int   m_iAddCD, m_iAddExp, m_iAddGold;		// °íÁ¤ ¸¶¹ý ´ë¹ÌÁö Èí¼öÀ². ¹ÝÁö·ù¿Í´Â µ¶¸³ÀûÀ¸·Î °è»êµÈ´Ù.

	int   m_iAddResistMagic;					// v1.2 Ãß°¡ ¸¶¹ý ÀúÇ× 
	int   m_iAddPhysicalDamage;					// v1.2 °íÁ¤ ´ë¹ÌÁö Ãß°¡ Æ÷ÀÎÆ® 
	int   m_iAddMagicalDamage;	

	int   m_iAddAbsAir;							// ¼Ó¼ºº° ´ë¹ÌÁö Èí¼ö
	int   m_iAddAbsEarth;
	int   m_iAddAbsFire;
	int   m_iAddAbsWater;

	int   m_iAddDamageAir;						// Add by Snoopy
	int   m_iAddDamageEarth;
	int   m_iAddDamageFire;
	int   m_iAddDamageWater;	


	int   m_iSpecialAbilityTime;				// Æ¯¼ö ´É·ÂÀ» »ç¿ëÇÏ±â À§ÇØ¼­´Â ÀÌ °ªÀÌ 0ÀÌ µÇ¾î¾ß ÇÑ´Ù. 
	BOOL  m_bIsSpecialAbilityEnabled;			// Æ¯¼ö ´É·ÂÀÌ È°¼ºÈ­ µÈ »óÅÂÀÎ°¡?
	DWORD m_dwSpecialAbilityStartTime;			// Æ¯¼ö ´É·ÂÀ» »ç¿ëÇÏ±â ½ÃÀÛÇÑ ½Ã°£
	int   m_iSpecialAbilityLastSec;				// Æ¯¼ö ´É·Â Áö¼Ó ½Ã°£.

	int   m_iSpecialAbilityType;				// ÇÒ´çµÈ Æ¯¼ö ´É·Â Á¾·ù
												// °ø°ÝÇü
												// 0:´É·Â ¾øÀ½  1:°ø°Ý½Ã Àû HP 50% °¨¼Ò  2:³Ãµ¿ È¿°ú  3: ¸¶ºñ È¿°ú  4: ¿ø¼¦ ¿øÅ³  5:ÀÔÈù ´ë¹ÌÁö ¸¸Å­ÀÇ HP¸¦ ¾ò´Â´Ù.
												// ¹æ¾îÇü
												// 50: ¹«±â ¼ö¸í 0·Î ¸¸µë. 51:ÇØ´ç ºÎÀ§ ´ë¹ÌÁö ¹«È¿È­  52: ¸ð5µç ºÎÀ§ ´ë¹ÌÁö ¹«È¿È­
	int   m_iSpecialAbilityEquipPos;			// ¹æ¾î±¸ÀÎ °æ¿ì Æ¯¼öÈ¿°ú°¡ Àû¿ëµÇ´Â ºÎÀ§¸¦ ÀÇ¹ÌÇÔ.
	bool  m_bIsAdminCommandEnabled;
	bool  m_bIsAdminStopStart;					// Snoopy: to prevent wrong GMs to restart or close a server.
	int   m_iAlterItemDropIndex;				// Index of ZemStone
	int   m_iEventItemDropIndex;				// Index of Item for events

	int   m_iWarContribution;					// ÀüÀï °øÇåµµ 


	char  m_cLockedMapName[11];					// °®Èù ¸Ê ÀÌ¸§
	int   m_iLockedMapTime;						// ÀÌ °ªÀÌ 0 ÀÌ»óÀÌ¸é ¾îµð·Î ÅÚ·¹Æ÷Æ® ÇØµµ À§ÀÇ ¸ÊÀ¸·Î °£´Ù.

	int   m_iCrusadeDuty;						// Å©·ç¼¼ÀÌµå¿¡¼­ ¸ÃÀº ¿ªÇÒ: 1-¿ëº´. 2-°Ç¼³ÀÚ. 3-ÁöÈÖ°ü
	DWORD m_dwCrusadeGUID;						// Å©·ç¼¼ÀÌµå GUID
	DWORD m_dwHeldenianGUID;
	DWORD m_dwAvatarGUID;
	BOOL bIsHeldenianHeroEnabled;

	DWORD m_cdwDecoTime;						// Used to see if character left an event or if just accidental deco

	
	struct {
		char cType;
		char cSide;
		short sX, sY;
	} m_stCrusadeStructureInfo[DEF_MAXCRUSADESTRUCTURES];
	int m_iCSIsendPoint;

	char m_cSendingMapName[11];
	BOOL m_bIsSendingMapStatus;

	// ÁöÈÖ°üÀÌ °Ç¼³ÇÒ ¼ö ÀÖ´Â Æ÷ÀÎÆ®. ÀÏ¹Ý ÇÃ·¹ÀÌ¾î¶ó¸é ÀÚ½ÅÀÇ Çàµ¿¿¡ ´ëÇÑ ´©Àû°ªÀÌ´Ù.
	int  m_iConstructionPoint;

	char m_cConstructMapName[11];
	int  m_iConstructLocX, m_iConstructLocY;


	// 2.06
	BOOL m_bIsPlayerCivil;
	BOOL m_bIsAttackModeChange;
	BOOL m_IsPeaceMode;

	// New 06/05/2004
	// Party Stuff
	int m_iPartyID;
	int m_iPartyStatus;
	int m_iReqJoinPartyClientH;
	char m_cReqJoinPartyName[12];
	bool m_bIsReflexionVictim; // By Snoopy

	int   m_iPartyRank;										// Party³»¿¡¼­ÀÇ À§Ä¡. -1ÀÌ¸é ¹«ÀÇ¹Ì. 1ÀÌ¸é ÆÄÆ¼ »ý¼ºÀÚ. 12¸é ¸â¹ö 
	int   m_iPartyMemberCount;								// ÆÄÆ¼ ÀÎ¿ø Á¦ÇÑ¿ë 
	int   m_iPartyGUID;										// v1.42 Party GUID
	struct {
	int  iIndex;
	char cName[11];
	} m_stPartyMemberName[DEF_MAXPARTYMEMBERS];

	int m_iDeadPenaltyTime;

	// New 16/05/2004
	char m_cWhisperPlayerName[11];
	BOOL m_bIsAdminOrderGoto;
	BOOL m_bIsInsideWarehouse;
	BOOL m_bIsInsideWizardTower;
	BOOL m_bIsCheckingWhisperPlayer;
	BOOL m_bIsOwnLocation;
	BOOL m_pIsProcessingAllowed;

	// Updated 10/11/2004 - 24/05/2004
	char m_cHeroArmorBonus;

	// New 25/05/2004
	BOOL m_bIsBeingResurrected;
	int m_iBeholderPower;		//0: no effect, 1: GM, or neck active, 2: Potion effect 
								//-1: Neck inactive (bearer inv)
	char m_cDiscount;			// 0: Normal prices,  20: prices +20%,  -15: Prices -15%

	DWORD m_dwFightzoneDeadTime;
	char m_cSaveCount;	
	BOOL m_bIsLimitedUser;		// True means limit level to 100...
	char m_cInitProgress;		// to prevent use of MSGID_REQUEST_INITDATA before MSGID_REQUEST_INITPLAYER

};

#endif // !defined(AFX_CLIENT_H__39CC7700_789F_11D2_A8E6_00001C7030A6__INCLUDED_)

