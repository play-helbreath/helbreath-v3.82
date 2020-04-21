// Client.cpp: implementation of the CClient class.
//
//////////////////////////////////////////////////////////////////////

#include "Client.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClient::CClient(HWND hWnd)
{
 register int i;

	m_pXSock = NULL;
	m_pXSock = new class XSocket(hWnd, DEF_CLIENTSOCKETBLOCKLIMIT);
	m_pXSock->bInitBufferSize(DEF_MSGBUFFERSIZE);

	ZeroMemory(m_cProfile, sizeof(m_cProfile));
	strcpy(m_cProfile, "__________");

	ZeroMemory(m_cCharName, sizeof(m_cCharName));
	ZeroMemory(m_cAccountName, sizeof(m_cAccountName));
	ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));

	ZeroMemory(m_cGuildName, sizeof(m_cGuildName));
	ZeroMemory(m_cLocation, sizeof(m_cLocation));
	strcpy(m_cLocation, "NONE");
	m_iGuildRank = -1;
	m_iGuildGUID = -1;

	m_bIsInitComplete = FALSE;

	//m_cLU_Str = m_cLU_Int = m_cLU_Vit = m_cLU_Dex = m_cLU_Mag = m_cLU_Char = 0;
	m_iLU_Pool = 0;
	m_iValidationNumber = 0;
	m_cAura = 0;

	// REINTRODUCED by SNOOPY
	m_iHitRatio_ItemEffect_SM = 0;
	m_iHitRatio_ItemEffect_L  = 0;
	m_iMagicHitRatio_ItemEffect = 0;

	m_cVar = 0;
	m_iEnemyKillCount = 0;
	m_iPKCount = 0;
	m_iRewardGold = 0;
	m_iCurWeightLoad = 0;
	m_dwLastDamageTime = 0;

	// Charges
	m_iAddTransMana = 0;
	m_iAddChargeCritical = 0;

	m_bIsSafeAttackMode  = FALSE;

	// ¾ÆÀÌÅÛ ÀåÂø »óÅÂ ÃÊ±âÈ­ÇÑ ÈÄ ¼³Á¤ÇÑ´Ù.
	for (i = 0; i < DEF_MAXITEMEQUIPPOS; i++) 
		m_sItemEquipmentStatus[i] = -1;
	
	// ¾ÆÀÌÅÛ ¸®½ºÆ® ÃÊ±âÈ­ 
	for (i = 0; i < DEF_MAXITEMS; i++) {
		m_pItemList[i]       = NULL;
		m_ItemPosList[i].x   = 40;
		m_ItemPosList[i].y   = 30;
		m_bIsItemEquipped[i] = FALSE;
	}
	m_cArrowIndex = -1;	// È­»ì ¾ÆÀÌÅÛ ÀÎµ¦½º´Â ÇÒ´çµÇÁö ¾ÊÀº »óÅÂ 

	// ¸Ã°Ü³í ¾ÆÀÌÅÛ ¸®½ºÆ® ÃÊ±âÈ­.
	for (i = 0; i < DEF_MAXBANKITEMS; i++) {
		m_pItemInBankList[i] = NULL;
	}

	// Magic - Skill ¼÷·Ãµµ ¸®½ºÆ® ÃÊ±âÈ­ 
	for (i = 0; i < DEF_MAXMAGICTYPE; i++)
		m_cMagicMastery[i] = NULL;
	
	for (i = 0; i < DEF_MAXSKILLTYPE; i++)
		m_cSkillMastery[i] = NULL;

	for (i = 0; i < DEF_MAXSKILLTYPE; i++) {
		m_bSkillUsingStatus[i] = FALSE;
		m_iSkillUsingTimeID[i] = NULL;
	}

	// testcode
	m_cMapIndex = -1;
	m_sX = -1;
	m_sY = -1;
	m_cDir = 5; 
	m_sType   = 0;
	m_sOriginalType = 0;
	m_sAppr1  = 0;
	m_sAppr2  = 0;
	m_sAppr3  = 0;
	m_sAppr4  = 0;
	m_iApprColor = 0; // v1.4
	m_iStatus = 0;

	m_cSex  = 0;
	m_cSkin = 0;
	m_cHairStyle  = 0;
	m_cHairColor  = 0;
	m_cUnderwear  = 0;

	m_cAttackDiceThrow_SM = 0;	// °ø°ÝÄ¡ ÁÖ»çÀ§ ´øÁö´Â È¸¼ö @@@@@@@@@@@@@
	m_cAttackDiceRange_SM = 0;
	m_cAttackDiceThrow_L = 0;	// °ø°ÝÄ¡ ÁÖ»çÀ§ ´øÁö´Â È¸¼ö @@@@@@@@@@@@@
	m_cAttackDiceRange_L = 0;
	m_cAttackBonus_SM    = 0;
	m_cAttackBonus_L     = 0;
	
	// ÇÃ·¹ÀÌ¾îÀÇ ¼Ò¼Ó ¸¶À»¿¡ µû¶ó¼­ »çÀÌµå°¡ °áÁ¤µÇ¸ç ÀÌ°ÍÀ» º¸°í NPC°¡ °ø°Ý¿©ºÎ¸¦ °áÁ¤ÇÒ °ÍÀÌ´Ù. 
	m_cSide = 0;

	m_iHitRatio = 0;
	m_iHitRatio3 = 0;
	m_iDefenseRatio = 0;
	//SNOOPY: Defratio2
	m_iDefenseRatio2 = 0;
	//SNOOPY: Defratio3, excluding any armor natural defence
	m_iDefenseRatio3 = 0;
	// SNOOPY: for simplier Priests/Druids.
	m_iPriestDruidID = 0;
	m_iSetEffect = 0;
	m_bSpecialFeatureAllowed = FALSE;
	m_iCrazyPlayerKiller = 0;
	m_bKilledByPlayerKiller = FALSE;
	
	for (i = 0; i < DEF_MAXITEMEQUIPPOS; i++) m_iDamageAbsorption_Armor[i]  = 0;
	m_iDamageAbsorption_Shield = 0;

	m_iHPstock = 0;
	m_bIsKilled = FALSE;

	for (i = 0; i < DEF_MAXMAGICEFFECTS; i++) 
		m_cMagicEffectStatus[i]	= 0;

	m_iWhisperPlayerIndex = -1;
	ZeroMemory(m_cWhisperPlayerName, sizeof(m_cWhisperPlayerName));

	m_iHungerStatus  = 100; 
	
	
	m_iAngelicStr = 0; // By Snoopy81
	m_iAngelicInt = 0; // By Snoopy81
	m_iAngelicDex = 0; // By Snoopy81
	m_iAngelicMag = 0; // By Snoopy81
	

	m_bIsPoisoned    = FALSE;
	m_iPoisonLevel   = NULL;

	m_iAdminUserLevel  = 0;
	m_iRating          = 0;
	m_iClientPrimaryDropRate = -1;
	m_iTimeLeft_ShutUp = 0;
	m_iTimeLeft_Rating = 0;
	m_iTimeLeft_FirmStaminar = 0;
	m_iTimeLeft_ForceRecall  = 0;
	m_bIsWarLocation = FALSE;
	
	m_bInhibition = FALSE;
	// Add by Snoopy
	m_bInvincibleSlate = FALSE;
	m_bManaSlate = FALSE;
	m_bXpSlate = FALSE;

	m_iExpStock = 0;

	m_iAllocatedFish = NULL;
	m_iFishChance    = 0;

	ZeroMemory(m_cIPaddress, sizeof(m_cIPaddress)); 
	m_bIsOnWaitingProcess = FALSE;		// Set TRUE Means wait deletion and connection to other server.

	m_iSuperAttackLeft  = 0;
	m_iSuperAttackCount = 0;

	m_sUsingWeaponSkill = 5; // ±âº»ÀûÀ¸·Î ¸Ç¼Õ°ÝÅõ 

	m_iManaSaveRatio   = 0;
	m_iAddResistMagic  = 0;
	m_iAddPhysicalDamage = 0;
	m_iAddMagicalDamage  = 0;
	m_bIsLuckyEffect     = 0;
	m_iSideEffect_MaxHPdown = 0;

	m_iAddAbsAir   = 0;	// ¼Ó¼ºº° ´ë¹ÌÁö Èí¼ö
	m_iAddAbsEarth = 0;
	m_iAddAbsFire  = 0;
	m_iAddAbsWater = 0;

	m_iAddDamageAir		= 0;	// Add by Snoopy
	m_iAddDamageEarth	= 0;
	m_iAddDamageFire	= 0;
	m_iAddDamageWater	= 0;

	m_iComboAttackCount = 0;
	m_iDownSkillIndex   = -1;
	bIsHeldenianHeroEnabled = FALSE;

	m_iMagicDamageSaveItemIndex = -1;

	m_sCharIDnum1 = m_sCharIDnum2 = m_sCharIDnum3 = 0;

	// New 06/05/2004
	m_iPartyID = 0;
	m_iPartyStatus = 0;
	m_IsPeaceMode = TRUE;
	m_iReqJoinPartyClientH = 0;
	ZeroMemory(m_cReqJoinPartyName,sizeof(m_cReqJoinPartyName));
	m_bIsReflexionVictim = FALSE;

	/*m_iPartyRank = -1; // v1.42
	m_iPartyMemberCount = 0;
	m_iPartyGUID        = 0;

	for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) {
		m_stPartyMemberName[i].iIndex = 0;
		ZeroMemory(m_stPartyMemberName[i].cName, sizeof(m_stPartyMemberName[i].cName));
	}*/

	m_iAbuseCount     = 0;
	m_bIsBWMonitor    = FALSE;
	m_bIsExchangeMode = FALSE;

	// v1.4311-3 Ãß°¡ º¯¼ö ÃÊ±âÈ­ »çÅõÀå ¿¹¾à °ü·Ã º¯¼ö 
    m_iFightZoneTicketNumber =	m_iFightzoneNumber = m_iReserveTime = 0 ;            

	m_iPenaltyBlockYear = m_iPenaltyBlockMonth = m_iPenaltyBlockDay = 0; // v1.4

	m_iExchangeH = NULL;											// ±³È¯ÇÒ ´ë»óÀÇ ÀÎµ¦½º 
	ZeroMemory(m_cExchangeName, sizeof(m_cExchangeName));			// ±³È¯ÇÒ ´ë»óÀÇ ÀÌ¸§ 
	ZeroMemory(m_cExchangeItemName, sizeof(m_cExchangeItemName));	// ±³È¯ÇÒ ¾ÆÀÌÅÛ ÀÌ¸§ 

	m_bIsExchangeConfirm = FALSE;
	for(i=0; i<4; i++){
		m_cExchangeItemIndex[i]  = -1; // ±³È¯ÇÒ ¾ÆÀÌÅÛ ÀÎµ¦½º 
		m_iExchangeItemAmount[i] = 0;  // ±³È¯ÇÒ ¾ÆÀÌÅÛ °¹¼ö 
	}


	m_iQuest		 = NULL; // ÇöÀç ÇÒ´çµÈ Quest 
	m_iQuestID       = NULL; // QuestID
	m_iAskedQuest	 = NULL; // ¹°¾îº» Äù½ºÆ® 
	m_iCurQuestCount = NULL; // ÇöÀç Äù½ºÆ® »óÅÂ 

	m_iQuestRewardType	 = NULL; // Äù½ºÆ® ÇØ°á½Ã »óÇ° Á¾·ù -> ¾ÆÀÌÅÛÀÇ ID°ªÀÌ´Ù.
	m_iQuestRewardAmount = NULL; // »óÇ° °¹¼ö 

	m_iContribution = NULL;			// °øÇåµµ 
	m_bQuestMatchFlag_Loc = FALSE;  // Äù½ºÆ® Àå¼Ò È®ÀÎ¿ë ÇÃ·¡±×.
	m_bIsQuestCompleted   = FALSE;

	m_cHeroArmourBonus = 0;

	m_bIsNeutral      = FALSE;
	m_bIsObserverMode = FALSE;
	m_cDiscount		  = 0;

	// 2000.8.1 ÀÌº¥Æ® »óÇ° ¼ö¿© È®ÀÎ¿ë 
	m_iSpecialEventID = 200081;

	m_iSpecialWeaponEffectType  = 0;	// 
	m_iSpecialWeaponEffectValue = 0;	// 
	m_iSpecialWeaponEffectSpell = -1;	// Stores a Spell nbe the weapon may cast
	

	m_iAddHP = m_iAddSP = m_iAddMP = 0; 
	m_iAddAR = m_iAddPR = m_iAddDR = 0;
	m_iAddAbsPD = m_iAddAbsMD = 0;
	m_iAddCD = m_iAddExp = m_iAddGold = 0;
		
	m_iSpecialAbilityTime = DEF_SPECABLTYTIMESEC;		// DEF_SPECABLTYTIMESEC
	m_iSpecialAbilityType = NULL;
	m_bIsSpecialAbilityEnabled = FALSE;
	m_iSpecialAbilityLastSec   = 0;

	m_iSpecialAbilityEquipPos  = 0;


	m_bIsAdminCommandEnabled = FALSE;
	m_bIsAdminStopStart = FALSE;
	m_iAlterItemDropIndex = -1;
	m_iEventItemDropIndex = -1;

	m_iAutoExpAmount = 0;
	m_iWarContribution = 0;

	// Snoopy: Anti-Hack based on connection check by client.
	m_iConnectionCheck = 0;
	dwTimeConnectionCheck = 0;
	dwEventTimeConnectionCheck = 0;	
	for (i = 0; i < 11; i++) m_cMsgCount[i] = 0;

	// SNOOPY: Client Connexion Check Messages gap monitoring
	m_iTheoricGap = 0;					// Calculated theoric Gap
	m_iLowerGap = 0;					// Lower observer gap
	m_iLowerGapValidation = 0;			// Counter before accepting a gap as the lower possible one.
	m_iTotalGap = 0;
	m_iServerSideTotalGap = 0;			// Used to compute client's average gap 
	m_iNumberGap = 0;
	m_iNumberBadGap = 0;
	m_iLowServerGapCount = 0;
	m_cPreviousKey = 0;
	m_iNbeSameKey = 0;
	m_iMaxPackets = 0;
	m_bMonitorThisChar = false;
	m_wSignature1 = 0;					// Used to check the signature sent by Client...
	m_wSignature2 = 0;					// Used to check the signature sent by Client...
	i_iSignatureCount = 0;
	
	// SNOOPY: Denial of service attack detection (using packet sniffer/sender)
	m_dwDSLAT = m_dwDSLATOld = m_dwDSLATS = 0;
	m_iDSCount = 0;

	// SNOOPY: Moving Hack checkers
	m_bIsMoveBlocked = FALSE;
	m_dwWalkLAT  = m_dwWalkLATS  = m_dwRunLAT  = m_dwRunLATS  = 0;
	m_iWalkTotal = m_iWalkTotalS = m_iRunTotal = m_iRunTotalS = 0;
	m_iWalkCount = m_iRunCount   = 0;

	// SNOOPY: DAMAGEMove tsearch hack detection...
	m_iLastDamage = 0;
	m_dwLastDamageMoveTime = 0;
	m_dwDamageMoveCounter = 0;

	// Attack (Swing) Hack checkers
	m_dwAttackLAT = m_dwAttackLATS = m_dwDashLAT = 0;
	m_iAttackTotal = m_iAttackTotalS = m_iDashTotal = 0;
	m_iAttackCount = m_iDashCount = 0;
	m_iAttackCountOK = m_iAttackCountBad = 0;

	// Potion Drink Delay hack
	m_dwPopoLATS = 0;
	m_iPopoTotalS = m_iPopoCount = 0;

	// Scroll delay hack, Instant LogOut (after damage)
	m_dwLastDamageTime = 0;

	// Precast Hack checkers 
	m_dwPreCastLAT = m_dwPreCastLATS = 0;
	m_sPreCastSpellID = 0;

	// Magic Hack Checkers
	m_bMagicConfirm		= FALSE;
	m_dwMagicFreqTime	= 0;
	m_iSpellCount		= 0;

	// prevents two spells/swings in a 300ms (onTimer)
	m_dwRecentAttackTime = 0;

	// Activity checkers
	m_dwLastActionTime	= NULL;	// To limit Party XP with AFK character
	m_dwAFKCheckTime	= NULL;	// AFK player checker
	m_dwXPHackCheckTime = NULL;	// Hourlly XP check 
	m_iXPHackCheckExp	= 0;	// Hourlly XP total
	m_bAntiTPLameEK		= TRUE;
	m_cDelayedDeco		= 0;	// 0: normal, 1:in progress, 2: deco now

	// Skill Hack (Manuf/Alchi Paquets / Tsearch hacks)
	m_iSkillMsgRecvCount	= 0;

	// Very Rich players log
	m_KnownPreviousGold = 0;

	// Limit user to lvl 100 for PL
	m_bIsLimitedUser	= FALSE;

	ZeroMemory(m_cLockedMapName, sizeof(m_cLockedMapName));
	strcpy(m_cLockedMapName, "NONE");
	m_iLockedMapTime = NULL;

	m_iCrusadeDuty    = NULL;
	m_dwCrusadeGUID   = NULL;
	m_dwHeldenianGUID = NULL; 
	m_dwAvatarGUID	  = NULL; 
	m_cdwDecoTime	  = NULL;	
	// Used to check if character was just deco a few seconds ago
	//         prevent a dead character to come back on a temporary map (death=> NULL)
	//         prevent a character loggedout long ago on previous event in this map, to loggin again

	for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++) 
	{	m_stCrusadeStructureInfo[i].cType = NULL;
		m_stCrusadeStructureInfo[i].cSide = NULL;
		m_stCrusadeStructureInfo[i].sX = NULL;
		m_stCrusadeStructureInfo[i].sY = NULL;
	}

	m_iCSIsendPoint = NULL;

	m_bIsSendingMapStatus = FALSE;
	ZeroMemory(m_cSendingMapName, sizeof(m_cSendingMapName));

	m_iConstructionPoint = NULL;

	ZeroMemory(m_cConstructMapName, sizeof(m_cConstructMapName));
	m_iConstructLocX = m_iConstructLocY = -1;

	m_bIsAdminOrderGoto = FALSE;
	m_bIsInsideWarehouse = FALSE;
	m_bIsInsideWizardTower = FALSE;
	m_bIsCheckingWhisperPlayer = FALSE;
	m_bIsOwnLocation = FALSE;
	m_pIsProcessingAllowed = FALSE;
	m_cHeroArmorBonus = 0;

	m_bIsBeingResurrected = FALSE;
	m_iBeholderPower = 0;
	m_cInitProgress = 0;
}

CClient::~CClient()
{
 int i;
	
	if (m_pXSock != NULL) delete m_pXSock;
	for (i = 0; i < DEF_MAXITEMS; i++)
		if (m_pItemList[i] != NULL) {
			delete m_pItemList[i];
			m_pItemList[i] = NULL;
		}
	for(i = 0; i < DEF_MAXBANKITEMS; i++)
		if (m_pItemInBankList[i] != NULL) {
			delete m_pItemInBankList[i];
			m_pItemInBankList[i]=NULL;
		}
}

BOOL CClient::bCreateNewParty()
{
 int i;

	if (m_iPartyRank != -1) return FALSE;

	m_iPartyRank = 0;
	m_iPartyMemberCount = 0;
	m_iPartyGUID = (rand() % 999999) + timeGetTime();

	for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) {
		m_stPartyMemberName[i].iIndex = 0;
		ZeroMemory(m_stPartyMemberName[i].cName, sizeof(m_stPartyMemberName[i].cName));
	}

	return TRUE;
}
