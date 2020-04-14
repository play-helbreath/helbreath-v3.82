// Game.h: interface for the CGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAME_H__C3D29FC5_755B_11D2_A8E6_00001C7030A6__INCLUDED_)
#define AFX_GAME_H__C3D29FC5_755B_11D2_A8E6_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#pragma warning( disable: 4049 )  /* more than 64k source lines */
#endif

#include "GlobalDef.h"
#include <windows.h>
#include <winbase.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <memory.h>
#include <direct.h>
#include <vector>

#include "winmain.h"
#include "StrTok.h"
#include "Xsocket.h"
#include "Client.h"
#include "Npc.h"
#include "Map.h"
#include "ActionID.h"
#include "UserMessages.h"
#include "NetMessages.h"
#include "MessageIndex.h"
#include "Misc.h"
#include "Msg.h"
#include "Magic.h"
#include "Skill.h"
#include "DynamicObject.h"
#include "DelayEvent.h"
#include "Fish.h"
#include "DynamicObject.h"
#include "DynamicObjectID.h"
#include "Portion.h"
#include "Mineral.h"
#include "Quest.h"
#include "BuildItem.h"
#include "TeleportLoc.h"
#include "Teleport.h"
#include "TempNpcItem.h"

#define DEF_MAXADMINS				50
#define DEF_MAXMAPS					100
#define DEF_MAXAGRICULTURE			200
#define DEF_MAXNPCTYPES				200
#define DEF_MAXBUILDITEMS			300
#define DEF_SERVERSOCKETBLOCKLIMIT	300
#define DEF_MAXBANNED				500
#define DEF_MAXNPCITEMS				1000
#define DEF_MAXCLIENTS				2000
#define DEF_MAXNPCS					5000
#define DEF_MAXITEMTYPES			5000
#define DEF_CLIENTTIMEOUT			10000
#define DEF_SPUPTIME				10000
#define DEF_POISONTIME				12000
#define DEF_HPUPTIME				15000
#define DEF_MPUPTIME				20000
#define DEF_HUNGERTIME				60000
#define DEF_NOTICETIME				80000
#define DEF_SUMMONTIME				300000
#define DEF_AUTOSAVETIME			600000
#define DEF_AFKTIME					300000 // 5 minutes
#define MAX_HELDENIANTOWER			200

#define DEF_EXPSTOCKTIME		1000*10		// ExpStock을 계산하는 시간 간격 
#define DEF_MSGQUENESIZE		100000		// 메시지 큐 사이즈 10만개 
#define DEF_AUTOEXPTIME			1000*60*6	// 자동으로 경험치가 올라가는 시간간격 
#define DEF_TOTALLEVELUPPOINT	3			// 레벨업시 할당하는 총 포인트 수 


#define DEF_MAXDYNAMICOBJECTS	60000
#define DEF_MAXDELAYEVENTS		60000
#define DEF_GUILDSTARTRANK		12

#define DEF_SSN_LIMIT_MULTIPLY_VALUE	2	// SSN-limit 곱하는 수 

#define DEF_MAXNOTIFYMSGS		300			// 최대 공지사항 메시지 
#define DEF_MAXSKILLPOINTS		700			// 스킬 포인트의 총합 
#define DEF_NIGHTTIME			40

#define DEF_CHARPOINTLIMIT		1000		// 각각의 특성치의 최대값 
#define DEF_RAGPROTECTIONTIME	7000		// Snoopy: was 7000, increased and stopped the protection if moving/casting
#define DEF_LOGPROTECTIONTIME	20000		// Snoopy: protection on connect
#define DEF_MAXREWARDGOLD		99999999	// 포상금 최대치 

#define DEF_ATTACKAI_EXCHANGEATTACK		1	// switch target: runner
#define DEF_ATTACKAI_TWOBYONEATTACK		2	//				  1/2 runner
#define DEF_ATTACKAI_FOURBYONEATTACK	3	//				  1/4 runner
#define DEF_ATTACKAI_NORMAL				4	// Normal, this is the default setting as well

#define DEF_ATTACKAI_CHANGING			7	// Starts Normal then change to random AI when seriouslly wounded
#define DEF_ATTACKAI_CLOSEATTACK1		8	// Strike as well at 90� or 45�
#define DEF_ATTACKAI_CLOSEATTACK2		9	// Strike as well at 90� or 45�
#define DEF_ATTACKAI_ANGLEATTACK		10	// Prefers strike at 45�
#define DEF_ATTACKAI_FARATTACK			11	// Prefers strike a far attacker
#define DEF_ATTACKAI_MAGEKILLER			12	// Search for another target, in range, but as far as possible.

#define DEF_MAXFISHS					200
#define DEF_MAXMINERALS					200
#define	DEF_MAXCROPS					200
#define DEF_MAXENGAGINGFISH				30  // 한 물고기에 낚시를 시도할 수 있는 최대 인원 
#define DEF_MAXPORTIONTYPES				500 // Also used for Crating
#define DEF_MAXTELEPORTLIST				20

#define DEF_SPECIALEVENTTIME			300000 //600000 // 300sec = 5 minutes
// Snoopy: Added for npc destruction
#define DEF_SPECIALEVENTTIME99			288000 //600000 // 288sec = 4 minutes 48s

#define DEF_MAXQUESTTYPE				200

#define DEF_MAXSUBLOGSOCK				10

#define DEF_ITEMLOG_GIVE				1
#define DEF_ITEMLOG_DROP				2
#define DEF_ITEMLOG_GET					3
#define DEF_ITEMLOG_DEPLETE				4
#define DEF_ITEMLOG_NEWGENDROP			5
#define DEF_ITEMLOG_DUPITEMID			6

// Macros for logging item operations
#define DEF_ITEMLOG_BUY					7
#define DEF_ITEMLOG_SELL				8
#define DEF_ITEMLOG_RETRIEVE			9
#define DEF_ITEMLOG_DEPOSIT				10
#define DEF_ITEMLOG_EXCHANGE			11
#define DEF_ITEMLOG_SKILLLEARN			12
#define DEF_ITEMLOG_MAKE				13
#define DEF_ITEMLOG_SUMMONMONSTER		14
#define DEF_ITEMLOG_POISONED			15
#define DEF_ITEMLOG_MAGICLEARN			16
#define DEF_ITEMLOG_REPAIR				17
#define DEF_ITEMLOG_UPGRADEFAIL			29
#define DEF_ITEMLOG_UPGRADESUCCESS		30
#define DEF_ITEMLOG_USE					32
#define DEF_ITEMLOG_ITEMEVENT			33 // bt snoopy for log of itemEvents
#define DEF_ITEMLOG_LOST				34 // by Snoopy Drop item when killed
#define DEF_ITEMLOG_CRAFT				35 // By Snoopy for Crafting

// Macros for logging pvp event and events
#define DEF_CRUSADELOG_ENDCRUSADE		1
#define DEF_CRUSADELOG_STARTCRUSADE		2
#define DEF_CRUSADELOG_SELECTDUTY		3
#define DEF_CRUSADELOG_GETEXP			4
#define DEF_CRUSADELOG_ENDHELDENIAN		11
#define DEF_CRUSADELOG_STARTHELDENIAN	12
#define DEF_CRUSADELOG_GETHELDENIANEXP	14
#define DEF_CRUSADELOG_HELDENIANVICTORY	15
#define DEF_CRUSADELOG_HELDENIANWARNOW	16
#define DEF_CRUSADELOG_APOCALYPSE		21
#define DEF_CRUSADELOG_BEGINAVATAR		22 //Avatars
#define DEF_CRUSADELOG_ENDAVATAR		23
#define DEF_CRUSADELOG_EK_LOG			66
#define DEF_CRUSADELOG_TEST				69

//Macros for logging EK & PK & resurections
#define  DEF_PKLOG_REDUCECRIMINAL					1
#define  DEF_PKLOG_BYPLAYER							2
#define  DEF_PKLOG_BYPK								3
#define  DEF_PKLOG_BYENEMY							4
#define  DEF_PKLOG_BYNPC							5
#define  DEF_PKLOG_BYOTHER							6
#define  DEF_PKLOG_PLRAIDER							95
#define  DEF_PKLOG_SAFEMAP							96
#define  DEF_PKLOG_BYENEMY_SAME_IP					97
#define  DEF_PKLOG_BYSELF							98
#define  DEF_PKLOG_RESURRECTION						99 // Snoopy: Added log for RESURECTION here


// Macros for Party Code
#define DEF_PARTYSTATUS_PROCESSING	1
#define DEF_PARTYSTATUS_NULL		0
#define DEF_PARTYSTATUS_CONFIRM		2

// NPC drops
#define DEF_ITEMSPREAD_RANDOM	1
#define DEF_ITEMSPREAD_FIXED	2
#define MAX_NPCITEMDROP			25

// Slates for client
#define DEF_STR							0x01
#define DEF_DEX							0x02
#define DEF_INT							0x03
#define DEF_VIT							0x04
#define DEF_MAG							0x05
#define DEF_CHR							0x06

#define DEF_NOTIFY_SLATECLEAR			99 // For internal use only

#define DEF_MAXDUPITEMID				100

#define DEF_MAXGUILDS					1000 
#define DEF_MAXONESERVERUSERS			800	// 800 

#define DEF_MAXGATESERVERSTOCKMSGSIZE	10000

#define DEF_MAXCONSTRUCTNUM				10
#define DEF_MAXSCHEDULE					10
#define DEF_MAXAPOCALYPSE				7
#define DEF_MAXHELDENIAN				10
#define DEF_MAXSIDES					12  // Snoopy: Anti Sublogsock9 bug (EK by Executor)
#define DEF_MAXFIGHTZONE 10 

//============================
#define DEF_PLRAIDER_LEVELLIMIT		90				// Limit for PromizeLand raiders, those chars will not rize above that level.			
//============================

//============================
#define DEF_MINIMUMHITRATIO 15				// 
//============================		

//============================
#define DEF_MAXIMUMHITRATIO	99				// 
//============================

//============================
#define DEF_PLAYERMAXLEVEL	180				// 
//============================

//============================
// New Changed 12/05/2004
#define DEF_GMGMANACONSUMEUNIT	15			// Grand Magic Generator 
//============================

#define DEF_MAXCONSTRUCTIONPOINT 30000		// 
#define DEF_MAXHELDENIANSUMMONPOINT 20000	// Snoopy: increased from 12000 ans chaged formula due to priests/druids/paladins
#define DEF_MAXSUMMONPOINTS		 30000
#define DEF_MAXWARCONTRIBUTION	 200000		// SNOOPY: Changed because of 2bytes msg to Gate serveur for WarContribution



#define DEF_TEST 0xFFFF0000
//#define DEF_TESTSERVER

#define NO_MSGSPEEDCHECK

class CGame  
{
public:


	void HeldenianWarEnder();
	void HeldenianWarStarter();

	// Snoopy: tweaked Heldenian functions...
	void _CreateHeldenianGUID(DWORD dwHeldenianGUID, int iWinnerSide);
	BOOL bReadHeldenianGUIDFile(char * cFn);
	void ManualStartHeldenianMode(int iClientH, char *pData, DWORD dwMsgSize);
	void GlobalStartHeldenianMode();
	void LocalStartHeldenianMode(short sV1, short sV2, DWORD dwHeldenianGUID);
	void HeldenianStartWarNow();
	void HeldenianVictoryNow(int iSide);
	void HeldenianEndWarNow();
	void ManualEndHeldenianMode(int iClientH, char *pData, DWORD dwMsgSize);
	void GlobalEndHeldenianMode();
	void LocalEndHeldenianMode(DWORD dwHeldenianGUID, int iWinner);
	void CheckHeldenianResultCalculation(int iClientH);
	BOOL UpdateHeldenianStatus(int iClientH);
	BOOL bCheckHeldenianMap(int sAttackerH, char cType);
	void RequestHeldenianTeleportList(int iClientH, char * pData, DWORD dwMsgSize);
	void RequestHeldenianTeleportNow(int iClientH, char * pData, DWORD dwMsgSize);
	void RequestHeldenianScroll(int iClientH, char * pData, DWORD dwMsgSize);
	BOOL __bSetOccupyFlag(char cMapIndex, int dX, int dY, int iSide, int iEKNum, int iClientH, BOOL bAutoFlag);
	void RemoveOccupyFlags(int iMapIndex);
	void GetOccupyFlagHandler(int iClientH);	

	DWORD m_dwHeldenianWarTime;
	DWORD m_dwHeldenianEndTime;
	char  m_cHeldenianSummonMode;

	void AdminOrder_GetFightzoneTicket(int iClientH);
	BOOL _bCheckCharacterData(int iClientH);
	//BOOL _bDecodeNpcItemConfigFileContents(char * pData, DWORD dwMsgSize);
	void GlobalUpdateConfigs(char cConfigType);
	void LocalUpdateConfigs(char cConfigType);


	void SetHeroFlag(short sOwnerH, char cOwnerType, BOOL bStatus);
	void SetInhibitionCastingFlag(short sOwnerH, char cOwnerType, BOOL bStatus);
	void CalculateEnduranceDecrement(short sTargetH, short sAttackerH, char cTargetType, char cAttackerType, int iArmorType);
	char _cCheckHeroItemEquipped(int iClientH);
	BOOL bPlantSeedBag(int iMapIndex, int dX, int dY, int iItemEffectValue1, int iItemEffectValue2, int iClientH);
	void _CheckFarmingAction(short sAttackerH, short sTargetH, BOOL bType);

	void GreenBall_Weather(int iClientH, char * pData, DWORD dwMsgSize);
	void ApocalypseEnder();
	//void ApocalypseStarter();
	BOOL bReadScheduleConfigFile(char *pFn);
	BOOL bReadApocalypseGUIDFile(char * cFn);

	void _CreateApocalypseGUID(DWORD dwApocalypseGUID);
	void LocalEndApocalypse();
	void LocalStartApocalypse(DWORD dwApocalypseGUID);
	void GlobalEndApocalypseMode(int iClientH);
	void GlobalStartApocalypseMode(int iClientH, int iMode); // Changed by SNOOPY
//	void OpenApocalypseGate(int iClientH);


	// SNOOPY: Added Apocalypse functions
	void GenerateApocalypseBoss(int MapIndex);
	void OpenCloseApocalypseGate();
	void Notify_ApocalypseGateState(int iClientH);
	void Use_ApocalypseGate(int iClientH);
	void ForceOpen_ApocalypseGate();
	void ForceClose_ApocalypseGate();
	void Open_EmptyMap_Gate(int MapIndex);
	void GenerateSlime(int MapIndex);

	// KLKS clean tiles
	void AdminOrder_CleanMap(int iClientH, char * pData, DWORD dwMsgSize);
	// Snoopy: regain empty owners (cause for bumps?)
	void AdminOrder_CleanBumps(int iClientH, char * pData, DWORD dwMsgSize);

	// Lists
	BOOL bReadBannedListConfigFile(char *pFn);
	BOOL bReadAdminListConfigFile(char *pFn);

	void AdminOrder_CheckStatus(int iClientH, char *pData,DWORD dwMsgSize);
	void Command_RedBall(int iClientH, char *pData,DWORD dwMsgSize);
	void Command_BlueBall(int iClientH, char *pData,DWORD dwMsgSize);
	void Command_YellowBall(int iClientH, char* pData, DWORD dwMsgSize);

	// Crusade
	void ManualEndCrusadeMode(int iWinnerSide); // 2.17 (x) 2.14 ( )
	void CrusadeWarStarter();
	BOOL bReadCrusadeGUIDFile(char * cFn);
	void _CreateCrusadeGUID(DWORD dwCrusadeGUID, int iWinnerSide);
	void GlobalStartCrusadeMode();
	void GSM_SetGuildTeleportLoc(int iGuildGUID, int dX, int dY, char * pMapName);
	void SyncMiddlelandMapInfo();
	void RemoveCrusadeStructures();
	void _SendMapStatus(int iClientH);
	void MapStatusHandler(int iClientH, int iMode, char * pMapName);
	void SelectCrusadeDutyHandler(int iClientH, int iDuty);
	void RequestSummonWarUnitHandler(int iClientH, int dX, int dY, char cType, char cNum, char cMode);
	void RequestGuildTeleportHandler(int iClientH);
	void RequestSetGuildTeleportLocHandler(int iClientH, int dX, int dY, int iGuildGUID, char * pMapName);
	void MeteorStrikeHandler(int iMapIndex);
	void _LinkStrikePointMapIndex();
	void MeteorStrikeMsgHandler(char cAttackerSide);
	void _NpcBehavior_GrandMagicGenerator(int iNpcH);
	void CollectedManaHandler(WORD wAresdenMana, WORD wElvineMana);
	void SendCollectedMana();
	void CreateCrusadeStructures();
	void _GrandMagicLaunchMsgSend(int iType, char cAttackerSide);
	void GrandMagicResultHandler(char *cMapName, int iCrashedStructureNum, int iStructureDamageAmount, int iCasualities, int iActiveStructure, int iTotalStrikePoints, char * cData);
	void CalcMeteorStrikeEffectHandler(int iMapIndex);
	void DoMeteorStrikeDamageHandler(int iMapIndex);
	void RequestSetGuildConstructLocHandler(int iClientH, int dX, int dY, int iGuildGUID, char * pMapName);
	void GSM_SetGuildConstructLoc(int iGuildGUID, int dX, int dY, char * pMapName);
	void GSM_ConstructionPoint(int iGuildGUID, int iPoint);
	void CheckCommanderConstructionPoint(int iClientH);
	BOOL bReadCrusadeStructureConfigFile(char * cFn);
	void LocalEndCrusadeMode(int iWinnerSide);
	void LocalStartCrusadeMode(DWORD dwGuildGUID);
	void CheckCrusadeResultCalculation(int iClientH);
	BOOL _bNpcBehavior_Detector(int iNpcH);
	BOOL _bNpcBehavior_ManaCollector(int iNpcH);
	BOOL __bSetConstructionKit(int iMapIndex, int dX, int dY, int iType, int iTimeCost, int iClientH);

	// SNOOPY Re Activated this
	void AdminOrder_SummonGuild(int iClientH, char * pData, DWORD dwMsgSize);

	// Acidx commands
	void AdminOrder_Time(int iClientH, char * pData, DWORD dwMsgSize);
	//SNOOPY: not twice! 
	// void AdminOrder_CheckRep(int iClientH, char *pData);
	void AdminOrder_Pushplayer(int iClientH, char * pData, DWORD dwMsgSize);

	void AdminOrder_CheckRep(int iClientH, char *pData,DWORD dwMsgSize);
	void AdminOrder_CheckStats(int iClientH, int iTargetH);

	void SetForceRecallTime(int iClientH);
	void ApplyCombatKilledPenalty(int iClientH, int cPenaltyLevel, BOOL bIsSAattacked);

	//	void AdminOrder_ClearTiles(int iClientH);
	void AdminOrder_ClearNpc(int iClientH);

	// Settings.cfg
	BOOL bReadSettingsConfigFile(char * cFn);

	//  BOOL bReadTeleportConfigFile(char * cFn);
	//	void RequestTeleportD2Handler(int iClientH, char * pData);
	
	// Daryl - AdminSettings.cfg
	BOOL bReadAdminSetConfigFile(char * cFn);


	// Hack Checks
	BOOL bCheckClientMoveFrequency(int iClientH, DWORD dwClientTime, DWORD dwMsgTime, int iMoveType);
	BOOL bCheckClientAttackFrequency(int iClientH, DWORD dwClientTime, DWORD dwMsgTime);
	BOOL bCheckClientDashFrequency(int iClientH, DWORD dwClientTime, DWORD dwMsgTime);
	void CheckDenialServiceAttack(int iClientH, DWORD dwClientTime, DWORD dwMsgTime, char cKey);

	// BOOL bCheckClientInvisibility(short iClientH);

	//Hypnotoad functions
	void SetDefenseShieldFlag(short sOwnerH, char cOwnerType, BOOL bStatus);
	void SetMagicProtectionFlag(short sOwnerH, char cOwnerType, BOOL bStatus);
	void SetProtectionFromArrowFlag(short sOwnerH, char cOwnerType, BOOL bStatus);
	void SetIllusionMovementFlag(short sOwnerH, char cOwnerType, BOOL bStatus);
	void SetIllusionFlag(short sOwnerH, char cOwnerType, BOOL bStatus);
	// Added by SNOOPY
	void SetConfusionFlag(short iClientH, char cOwnerType, BOOL bStatus);
	void SetMetamorphosisFlag(short sOwnerH, char cOwnerType, BOOL bStatus);
	void SetReflexionFlag(short sOwnerH, char cOwnerType, BOOL bStatus);

	void RequestChangePlayMode(int iClientH);
	void GetHeroMantleHandler(int iClientH,int iItemID,char * pString);
	void AdminOrder_Weather(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_Thunder(int iClientH, char * pData, DWORD dwMsgSize); // snoopy
	void AdminOrder_SendMSG(int iClientH, char *pData, DWORD dwMsgSize);
	void SendMsg(short sOwnerH, char cOwnerType, BOOL bStatus, long lPass);
	BOOL bCheckMagicInt(int iClientH);
	BOOL bChangeState(char cStateChange, char* cStr, char *cVit,char *cDex,char *cInt,char *cMag,char *cChar);
	void StateChangeHandler(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_SetStatus(int iClientH, char *pData, DWORD dwMsgSize);
	void SetStatusFlag(short sOwnerH, char cOwnerType, BOOL bStatus, int iPass);
	void SetPoisonFlag(short sOwnerH, char cOwnerType, BOOL bStatus);
	void AdminOrder_SummonStorm(int iClientH, char* pData, DWORD dwMsgSize);
	void AdminOrder_CallMagic(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_SummonDeath(int iClientH);

	// SNOOPY: Added Setpk-mode admin command
	void AdminOrder_SetPkMode(int iClientH, char * pData, DWORD dwMsgSize);
	// SNOOPY: Added Setmaptype admin command
	void AdminOrder_SetMapType(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_DropType(int iClientH, char * pData, DWORD dwMsgSize);
	// SNOOPY: Added serverinfo admin command
	void AdminOrder_GetMapInfo(int iClientH, char * pData, DWORD dwMsgSize);
	// SNOOPY Added Character order to get a Gizon Level
	void AdminOrder_GetGizonLevel(int iClientH, char * pData, DWORD dwMsgSize);
	// SNOOPY Addeg Character order to read Gizon Points
	void AdminOrder_GetGizonInfo(int iClientH, char * pData, DWORD dwMsgSize);
	// SNOOPY: Added Admin order to change Map Mob number
	void AdminOrder_MapMobNum(int iClientH, char * pData, DWORD dwMsgSize);
	//SNOOPY: Enable amin to prevent potions (HP MP SP) use
	void AdminOrder_PopoEnabled(int iClientH, char * pData, DWORD dwMsgSize);
	// SNOOPY: Added Admin order
	void AdminOrder_Test(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_StartServer(int iClientH, char * pData, DWORD dwMsgSize);	
	void AdminOrder_SetXPRate(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_SetExtraDrop(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_SetBossAdjust(int iClientH, char * pData, DWORD dwMsgSize);
	// SNOOPY: to perform heavyer log onsomeone.
	void AdminOrder_MonitorPlayer(int iClientH, char * pData, DWORD dwMsgSize);
	//SNOOPY: Adjust Primary drop rate only when rating change to remove from drop routine
	void AdjustClientDropRate(int iClientH);
	// SNOOPY: Send ZzZz to AFKs....
	void AFKChecker();
	void GetAngelHandler(int iClientH, char * pData, DWORD dwMsgSize);

	void AdminOrder_SetZerk(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_SetFreeze(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_Kill(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_Revive(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_SetObserverMode(int iClientH);
	void AdminOrder_EnableAdminCommand(int iClientH, char *pData, DWORD dwMsgSize);
	void AdminOrder_CreateItem(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_CreateToken(int iClientH, char *pData, DWORD dwMsgSize);
	void AdminOrder_ItemEventNow(int iClientH, char *pData, DWORD dwMsgSize);
	void AdminOrder_Summon(int iClientH, char * pData, DWORD dwMsgSize, char cSpecialAbility);
	void AdminOrder_SummonAll(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_SummonPlayer(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_UnsummonDemon(int iClientH);
	void AdminOrder_UnsummonAll(int iClientH);
	void AdminOrder_Safe(int iClientH, bool bIsSafe); // Add by Snoopy
	void AdminOrder_SummonDemon(int iClientH);
	void AdminOrder_SetInvi(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_Polymorph(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_GetNpcStatus(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_CheckIP(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_CreateFish(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_Teleport(int iClientH, char * pData, DWORD dwMsgSize, BOOL bForceTP = FALSE);
	void AdminOrder_Gate(int iClientH, char * pData, DWORD dwMsgSize, BOOL bForceTP = FALSE);
	void AdminOrder_ReserveFightzone(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_CloseConn(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_CallGuard(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_DisconnectAll(int iClientH, char * pData, DWORD dwMsgSize);

	BOOL bCopyItemContents(class CItem * pOriginal, class CItem * pCopy);
	int  iGetMapLocationForbiddenSide(char * pMapName);
	void ChatMsgHandlerGSM(int iMsgType, int iV1, char * pName, char * pData, DWORD dwMsgSize);
	void RemoveClientShortCut(int iClientH);
	BOOL bAddClientShortCut(int iClientH);

	void GSM_RequestFindCharacter(WORD wReqServerID, WORD wReqClientH, char *pName, char * pFinder); // New 16/05/2001 Changed
	void ServerStockMsgHandler(char * pData);
	void SendStockMsgToGateServer();
	BOOL bStockMsgToGateServer(char * pData, DWORD dwSize);
	void RequestHelpHandler(int iClientH);
	
	void CheckConnectionHandler(int iClientH, char *pData, char cKey, DWORD dwMsgTime);
	BOOL bActionOnWrongCRC(int iClientH, int iReason, int iValue = 0);

	void AgingMapSectorInfo();
	void UpdateMapSectorInfo();
	//BOOL bGetItemNameWhenDeleteNpc(char * pItemName, short sNpcType);
	BOOL bGetItemNameWhenDeleteNpc(int & iItemID, short sNpcType);
	int iGetItemWeight(class CItem * pItem, int iCount);
	void CancelQuestHandler(int iClientH);
	void ActivateSpecialAbilityHandler(int iClientH);
	void EnergySphereProcessor(BOOL bIsAdminCreate = FALSE, int iClientH = NULL);
	BOOL bCheckEnergySphereDestination(int iNpcH, short sAttackerH, char cAttackerType);
	void CGame::JoinPartyHandler(int iClientH, int iV1, char *pMemberName);
	void CreateNewPartyHandler(int iClientH);
	void RequestSellItemListHandler(int iClientH, char * pData);
	void RequestRestartHandler(int iClientH);
	int iRequestPanningMapDataRequest(int iClientH, char * pData);
	void GetMagicAbilityHandler(int iClientH);
		void _TamingHandler(int iClientH, int iSkillNum, char cMapIndex, int dX, int dY);
	void RequestCheckAccountPasswordHandler(char * pData, DWORD dwMsgSize);
	int _iTalkToNpcResult_Guard(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	void SetIceFlag(short sOwnerH, char cOwnerType, BOOL bStatus);
	void _bDecodeNoticementFileContents(char * pData, DWORD dwMsgSize);
	void RequestNoticementHandler(int iClientH, char * pData);
	void _AdjustRareItemValue(class CItem * pItem);
	BOOL _bCheckDupItemID(class CItem * pItem);
	BOOL _bDecodeDupItemIDFileContents(char * pData, DWORD dwMsgSize);
	void NpcDeadItemGenerator(int iNpcH, short sAttackerH, char cAttackerType);
	BOOL NpcDeadItemGeneratorWithItemEvent(int iNpcH, short sAttackerH, char cAttackerType);
	int  iGetPlayerABSStatus(int iWhatH, int iRecvH, BOOL & bTransparentInvi);
	void CheckSpecialEvent(int iClientH);
	char _cGetSpecialAbility(int iKindSA);
	void BuildItemHandler(int iClientH, char * pData);
	BOOL _bDecodeBuildItemConfigFileContents(char * pData, DWORD dwMsgSize);
	BOOL _bCheckSubLogSocketIndex();
	void _CheckGateSockConnection();
	void OnSubLogRead(int iIndex);
	void OnSubLogSocketEvent(UINT message, WPARAM wParam, LPARAM lParam);
	void _CheckStrategicPointOccupyStatus(char cMapIndex);
	void GetMapInitialPoint(int iMapIndex, short * pX, short * pY, char cSide = -1);
	int  iGetMaxHP(int iClientH, BOOL bBloodEffect = TRUE);
	int  iGetMaxMP(int iClientH);
	int  iGetMaxSP(int iClientH);
	void _ClearQuestStatus(int iClientH);
	BOOL _bCheckItemReceiveCondition(int iClientH, class CItem * pItem);
	void SendItemNotifyMsg(int iClientH, WORD wMsgType, class CItem * pItem, int iV1);
	
	int _iTalkToNpcResult_WTower(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	int _iTalkToNpcResult_WHouse(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	int _iTalkToNpcResult_BSmith(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	int _iTalkToNpcResult_GShop(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	int _iTalkToNpcResult_GuildHall(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	BOOL _bCheckIsQuestCompleted(int iClientH);
	void _CheckQuestEnvironment(int iClientH);
	void _SendQuestContents(int iClientH);
	void QuestAcceptedHandler(int iClientH);
	BOOL _bDecodeQuestConfigFileContents(char * pData, DWORD dwMsgSize);
	
	void CancelExchangeItem(int iClientH);
	BOOL bAddItem(int iClientH, class CItem * pItem, char cMode);
	void ConfirmExchangeItem(int iClientH);
	void SetExchangeItem(int iClientH, int iItemIndex, int iAmount);
	void ExchangeItemHandler(int iClientH, short sItemIndex, int iAmount, short dX, short dY, WORD wObjectID, char * pItemName);

	void _BWM_Command_Shutup(char * pData);
	void _BWM_Init(int iClientH, char * pData);
	void CheckUniqueItemEquipment(int iClientH);
	void _SetItemPos(int iClientH, char * pData);
	//void GetHeroMantleHandler(int iClientH);
	
	int  _iComposeFlagStatusContents(char * pData);
	void SetSummonMobAction(int iClientH, int iMode, DWORD dwMsgSize, char * pData = NULL);
	BOOL _bDepleteDestTypeItemUseEffect(int iClientH, int dX, int dY, short sItemIndex, short sDestItemID);
	void SetDownSkillIndexHandler(int iClientH, int iSkillIndex);
	int iGetComboAttackBonus(int iSkill, int iComboCount);
	int  _iGetWeaponSkillType(int iClientH);
	void CheckFireBluring(char cMapIndex, int sX, int sY);
	void NpcTalkHandler(int iClientH, int iWho);
	BOOL bDeleteMineral(int iIndex);
	void _CheckMiningAction(int iClientH, int dX, int dY);
	int iCreateMineral(char cMapIndex, int tX, int tY, char cLevel);
	void MineralGenerator();
	void LocalSavePlayerData(int iClientH);
	BOOL _bDecodePortionConfigFileContents(char * pData, DWORD dwMsgSize);
	void ReqCreatePortionHandler(int iClientH, char * pData);

// Crafting
	void ReqCreateCraftingHandler(int iClientH, char *pData);


	void _CheckAttackType(int iClientH, short * spType);
	BOOL bOnClose();
	void ForceDisconnectAccount(char * pAccountName, WORD wCount);
	void NpcRequestAssistance(int iNpcH);
	void ToggleSafeAttackModeHandler(int iClientH);
	void SetBerserkFlag(short sOwnerH, char cOwnerType, BOOL bStatus);
	void SpecialEventHandler();
	int _iForcePlayerDisconect(int iNum);
	int iGetMapIndex(char * pMapName);

	int iGetNpcRelationship(int iWhatH, int iRecvH, BOOL & bTransparentInvi);
	int iGetPlayerRelationship(int iClientH, int iOpponentH);					// Mimits ot not damage in safe mode

	int iGetWhetherMagicBonusEffect(short sType, char cWheatherStatus);
	void WhetherProcessor();
	int _iCalcPlayerNum(char cMapIndex, short dX, short dY, char cRadius);
	void FishGenerator();
	void ReqGetFishThisTimeHandler(int iClientH);
	void FishProcessor();
	int iCheckFish(int iClientH, char cMapIndex, short dX, short dY);
	BOOL bDeleteFish(int iHandle, int iDelMode);
	int  iCreateFish(char cMapIndex, short sX, short sY, short sDifficulty, class CItem * pItem, int iDifficulty, DWORD dwLastTime);
	void UserCommand_DissmissGuild(int iClientH, char * pData, DWORD dwMsgSize);
	// v1.4311-3 변경 함수 선언  Expire -> Ban 으로 
	void UserCommand_BanGuildsman(int iClientH, char * pData, DWORD dwMsgSize);
	// v1.4311-3 추가 함수 선언 이벤트를 대비하여 운영자가 사투장을 예약해놓는다.
	int iGetExpLevel(int iExp);
	void ___RestorePlayerRating(int iClientH);
	void CalcExpStock(int iClientH);
	void ResponseSavePlayerDataReplyHandler(char * pData, DWORD dwMsgSize);
	void NoticeHandler();
	BOOL bReadNotifyMsgListFile(char * cFn);
	void SetPlayerReputation(int iClientH, char * pMsg, char cValue, DWORD dwMsgSize);
	void ShutUpPlayer(int iClientH, char * pMsg, DWORD dwMsgSize);
	void CheckDayOrNightMode();
	BOOL bCheckBadWord(char * pString);
	BOOL bCheckResistingPoisonSuccess(short sOwnerH, char cOwnerType);
	void PoisonEffect(int iClientH, int iV1);
	void bSetNpcAttackMode(char * cName, int iTargetH, char cTargetType, BOOL bIsPermAttack);
	BOOL _bGetIsPlayerHostile(int iClientH, int sOwnerH);
	BOOL bAnalyzeCriminalAction(int iClientH, short dX, short dY, BOOL bIsCheck = FALSE);
	void RequestAdminUserMode(int iClientH, char * pData);
	int _iGetPlayerNumberOnSpot(short dX, short dY, char cMapIndex, char cRange);
	void CalcTotalItemEffect(int iClientH, int iEquipItemID, BOOL bNotify = TRUE);
	//void ___RestorePlayerCharacteristics(int iClientH);
	void GetPlayerProfile(int iClientH, char * pMsg, DWORD dwMsgSize);
	void SetPlayerProfile(int iClientH, char * pMsg, DWORD dwMsgSize);
	void ToggleWhisperPlayer(int iClientH, char * pMsg, DWORD dwMsgSize);
	void CheckAndNotifyPlayerConnection(int iClientH, char * pMsg, DWORD dwSize);
	void CheckAndNotifyGServersConnection(int iClientH); // by Snoopy
	int iCalcTotalWeight(int iClientH);
	void ReqRepairItemCofirmHandler(int iClientH, char cItemID, char * pString);
	void ReqRepairItemHandler(int iClientH, char cItemID, char cRepairWhom, char * pString);
	void ReqSellItemConfirmHandler(int iClientH, char cItemID, int iNum, char * pString);
	void ReqSellItemHandler(int iClientH, char cItemID, char cSellToWhom, int iNum, char * pItemName);
	void UseSkillHandler(int iClientH, int iV1, int iV2, int iV3);
	int  iCalculateUseSkillItemEffect(int iOwnerH, char cOwnerType, char cOwnerSkill, int iSkillNum, char cMapIndex, int dX, int dY);
	void ClearSkillUsingStatus(int iClientH);
	void DynamicObjectEffectProcessor();
	int _iGetTotalClients();
	void SendObjectMotionRejectMsg(int iClientH);
	void SetInvisibilityFlag(short sOwnerH, char cOwnerType, BOOL bStatus);
	BOOL bRemoveFromDelayEventList(int iH, char cType, int iEffectType);
	void DelayEventProcessor();
	BOOL bRegisterDelayEvent(int iDelayType, int iEffectType, DWORD dwLastTime, int iTargetH, char cTargetType, char cMapIndex, int dX, int dY, int iV1, int iV2, int iV3);
	int iGetFollowerNumber(short sOwnerH, char cOwnerType);
	int  _iCalcSkillSSNpoint(int iLevel);
	void OnKeyUp(WPARAM wParam, LPARAM lParam);
	void OnKeyDown(WPARAM wParam, LPARAM lParam);
	BOOL bCheckTotalSkillMasteryPoints(int iClientH, int iSkill);
	BOOL bSetItemToBankItem(int iClientH, class CItem * pItem);
	void NpcMagicHandler(int iNpcH, short dX, short dY, short sType);
	BOOL bCheckResistingTremorSuccess(short sTargetH, char cTargetType);
	BOOL bCheckResistingIceSuccess(char cAttackerDir, short sTargetH, char cTargetType, int iHitRatio);
	BOOL bCheckResistingMagicSuccess(char cAttackerDir, short sTargetH, char cTargetType, int iHitRatio);
	void Effect_SpUp_Spot(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sV1, short sV2, short sV3);
	void Effect_SpDown_Spot(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sV1, short sV2, short sV3);
	void Effect_HpUp_Spot(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sV1, short sV2, short sV3);
// SNOOPY Added circle info
	void Effect_Damage_Spot_DamageMove(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sAtkX, short sAtkY, short sV1, short sV2, short sV3, BOOL bExp, int iAttr, int iSpellSpecial = 0);
	      void Effect_Damage_Explosion(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sAtkX, short sAtkY, short sV1, short sV2, short sV3, BOOL bExp, int iAttr);
               void Effect_Damage_Spot(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sV1, short sV2, short sV3, BOOL bExp, int iAttr = NULL, int iSpellSpecial = 0);
	      
	
	// Added by Snoopy
	void Effect_ManaDown_Spot(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sV1, short sV2, short sV3, BOOL bExp, int iAttr = NULL);
	
	void UseItemHandler(int iClientH, short sItemIndex, short dX, short dY, short sDestItemID, DWORD dwMsgTime);
	void NpcBehavior_Stop(int iNpcH);
	void ItemDepleteHandler(int iClientH, short sItemIndex, BOOL bIsUseItemResult, BOOL bDontLog = FALSE);
	int _iGetArrowItemIndex(int iClientH);
	void RequestFullObjectData(int iClientH, char * pData);
	void DeleteNpc(int iNpcH);
	void CalcNextWayPointDestination(int iNpcH);
	void MobGenerator();
	void MagicSMG(); // Snoopy SpotMobGen moving with random mobs...
	void CalculateSSN_SkillIndex(int iClientH, short sSkillIndex, int iValue);
	void CalculateSSN_ItemIndex(int iClientH, short sWeaponIndex, int iValue);

	//SNOOPY: Added check for skill in cas of caract reduction
	void Check_Skill_Is_Valid(int iClientH);
	void CheckDynamicObjectList();
	int  iAddDynamicObjectList(short sOwner, char cOwnerType, short sType, char cMapIndex, short sX, short sY, DWORD dwLastTime, int iV1 = NULL);
	int _iCalcMaxLoad(int iClientH);
	void GetRewardMoneyHandler(int iClientH);
	void _PenaltyItemDrop(int iClientH, int iTotal, BOOL bIsSAattacked = FALSE);
	//void ApplyCombatKilledPenalty(int iClientH, char cPenaltyLevel, BOOL bIsSAattacked = FALSE);
	void EnemyKillRewardHandler(int iAttackerH, int iClientH);
	void PK_KillRewardHandler(short sAttackerH, short sVictumH);
	void ApplyPKpenalty(short sAttackerH, short sVictumH);
	BOOL bSetItemToBankItem(int iClientH, short sItemIndex);
	void RequestRetrieveItemHandler(int iClientH, char * pData);
	void RequestCivilRightHandler(int iClientH, char * pData);
	BOOL bCheckLimitedUser(int iClientH);
	BOOL bCheckPLRaider(int iClientH);
	void LevelUpSettingsHandler(int iClientH, char * pData, DWORD dwMsgSize);
	// v1.4311-3 선언 함수  사투장 예약 함수 선언 FightzoneReserveHandler
	void FightzoneReserveHandler(int iClientH, char * pData, DWORD dwMsgSize);
	BOOL bCheckLevelUp(int iClientH);
	int iGetLevelExp(int iLevel);
	void TimeManaPointsUp(int iClientH);
	void TimeStaminarPointsUp(int iClientH);
	void Quit();
	BOOL __bReadMapCrusadeInfo(int iMapIndex, BOOL bCrusadeBegin); // by Snoopy, to read again some data on crusade beginning
	BOOL __bReadMapInfo(int iMapIndex);
	BOOL bBankItemToPlayer(int iClientH, short sItemIndex);
	BOOL bPlayerItemToBank(int iClientH, short sItemIndex);
	int  _iGetSkillNumber(char * pSkillName);
	void TrainSkillResponse(BOOL bSuccess, int iClientH, int iSkillNum, int iSkillLevel);
	int _iGetMagicNumber(char * pMagicName, int * pReqInt, int * pCost);
	//SNOOPY: Added a item depletion confirmation
	void RequestStudyMagicHandler(int iClientH, char * pName, BOOL & bSucces, BOOL bIsPurchase = TRUE);
	BOOL _bDecodeSkillConfigFileContents(char * pData, DWORD dwMsgSize);
	BOOL _bDecodeMagicConfigFileContents(char * pData, DWORD dwMsgSize);

	// SNOOPY Added type "3   " to prevent scrolls use from recall-impossible maps
	void RequestTeleportHandler(int iClientH, char * pData, char * cMapName = NULL, int dX = -1, int dY = -1);

	
	// Precst hack detection routine
	int  iClientMotion_Magic_Handler(int iClientH, short sX, short sY, char cDir, DWORD dwClientTime, DWORD dwMsgTime, short sSpellID);
	// Cast hack detection routine 
	int  iClientCommon_Spell_Handler(int iClientH, short sX, short sY, DWORD dwClientTime, DWORD dwMsgTime, short sSpellID);
	void PlayerMagicHandler(int iClientH, int dX, int dY, short sType, BOOL bItemEffect = FALSE, int iV1 = NULL, DWORD dwClientTime = NULL, DWORD dwMsgTime = NULL);
	
	void SendMsgToGateServer(DWORD dwMsg, int iClientH, char * pData = NULL);
	void OnGateRead();
	void OnGateSocketEvent(UINT message, WPARAM wParam, LPARAM lParam);
	void ToggleCombatModeHandler(int iClientH);
	void GuildNotifyHandler(char * pData, DWORD dwMsgSize);
	void SendGuildMsg(int iClientH, WORD wNotifyMsgType, short sV1, short sV2, char * pString);
	void DelayEventProcess();
	void TimeHitPointsUp(int iClientH);
	void CalculateGuildEffect(int iVictimH, char cVictimType, short sAttackerH);
	void OnStartGameSignal();
	int iDice(int iThrow, int iRange);
	BOOL _bInitNpcAttr(class CNpc * pNpc, char * pNpcName, short sClass, char cSA);
	BOOL _bDecodeNpcConfigFileContents(char * pData, DWORD dwMsgSize);
	void ReleaseItemHandler(int iClientH, short sItemIndex, BOOL bNotice);
	void ClientKilledHandler(int iClientH, int iAttackerH, char cAttackerType, short sDamage);
	int  SetItemCount(int iClientH, char * pItemName, DWORD dwCount);
	int  SetItemCount(int iClientH, int iItemIndex, DWORD dwCount);
	DWORD dwGetItemCount(int iClientH, char * pName);
	void DismissGuildRejectHandler(int iClientH, char * pName);
	void DismissGuildApproveHandler(int iClientH, char * pName);
	void JoinGuildRejectHandler(int iClientH, char * pName);			    
	void JoinGuildApproveHandler(int iClientH, char * pName);
	void SendNotifyMsg(int iFromH, int iToH, WORD wMsgType, DWORD sV1, DWORD sV2, DWORD sV3, char * pString, DWORD sV4 = NULL, DWORD sV5 = NULL, DWORD sV6 = NULL, DWORD sV7 = NULL, DWORD sV8 = NULL, DWORD sV9 = NULL, char * pString2 = NULL);
	void GiveItemHandler(int iClientH, short sItemIndex, int iAmount, short dX, short dY, WORD wObjectID, char * pItemName);
	void RequestPurchaseItemHandler(int iClientH, char * pItemName, int iNum);
	void ResponseDisbandGuildHandler(char * pData, DWORD dwMsgSize);
	void RequestDisbandGuildHandler(int iClientH, char * pData, DWORD dwMsgSize);
	void RequestCreateNewGuildHandler(int iClientH, char * pData, DWORD dwMsgSize);
	void ResponseCreateNewGuildHandler(char * pData, DWORD dwMsgSize);
	int  iClientMotion_Stop_Handler(int iClientH, short sX, short sY, char cDir);
	
	BOOL bEquipItemHandler(int iClientH, short sItemIndex, BOOL bNotify = TRUE);
	BOOL _bAddClientItemList(int iClientH, class CItem * pItem, int * pDelReq);
	int  iClientMotion_GetItem_Handler(int iClientH, short sX, short sY, char cDir);
	void DropItemHandler(int iClientH, short sItemIndex, int iAmount, char * pItemName, BOOL bByPlayer = TRUE);
	void ClientCommonHandler(int iClientH, char * pData, DWORD dwMsgTime);

	// Snoopy: Added time to messages: Server time of related Socket event
	BOOL __fastcall bGetMsgQuene(char * pFrom, char * pData, DWORD * pMsgSize, int * pIndex, char * pKey, DWORD * pTime);
	BOOL __fastcall bPutMsgQuene(char cFrom, char * pData, DWORD dwMsgSize, int iIndex, char cKey, DWORD dwTime);
	void MsgProcess();

	void NpcBehavior_Flee(int iNpcH);
	int iGetDangerValue(int iNpcH, short dX, short dY);
	void NpcBehavior_Dead(int iNpcH);
	void NpcKilledHandler(short sAttackerH, char cAttackerType, int iNpcH, short sDamage);
	//int  iCalculateAttackEffect(short sTargetH, char cTargetType, short sAttackerH, char cAttackerType, int tdX, int tdY, int iAttackMode, BOOL bNearAttack = FALSE);
	int iCalculateAttackEffect(short sTargetH, char cTargetType, short sAttackerH, char cAttackerType, int tdX, int tdY, int iAttackMode, BOOL bNearAttack = FALSE, BOOL bIsDash = FALSE, BOOL bDontDepleteArrow = FALSE, BOOL bMainGaucheAttack = FALSE);

	
// Follower modes	
	BOOL bSetNpcFollowMode(char * pName, char * pFollowName, char cFollowOwnerType); // Sets the follower modes
	// Checks changes to modes
	void RemoveFromTarget(short sTargetH, char cTargetType, int iCode = NULL, int iAttackerH = NULL, char cAttackerType = 0);       
	void ReleaseFollowMode(short sOwnerH);	 // release from dead npc master
	// Reconnecting clients will recover summons 
	void iRecoverFollowers(int  iClientH, BOOL bControlAll = FALSE); 


	
	
	void NpcBehavior_Attack(int iNpcH);
	void TargetSearch(int iNpcH, short * pTarget, char * pTargetType);
	void FarTargetSearch(int iNpcH, short * pTarget, char * pTargetType); // Enables a Mob to find a far target, but still in striking range
	void NpcBehavior_Move(int iNpcH);
	BOOL bGetEmptyPosition(short * pX, short * pY, char cMapIndex);
	char cGetNextMoveDir(short sX, short sY, short dstX, short dstY, char cMapIndex, char cTurn, int * pError);

	int  iClientMotion_Attack_Handler(int iClientH, short sX, short sY, short dX, short dY, short wType, char cDir, WORD wTargetObjectID, DWORD dwClientTime, DWORD dwMsgTime, BOOL bResponse = TRUE, BOOL bIsDash = FALSE, BOOL bIsServerInitiated = FALSE);
	void ChatMsgHandler(int iClientH, char * pData, DWORD dwMsgSize);
	void NpcProcess();
	int bCreateNewNpc(char * pNpcName, char * pName, char * pMapName, short sClass, char cSA, char cMoveType, int * poX, int * poY, char * pWaypointList, RECT * pArea, int iSpotMobIndex, char cChangeSide, BOOL bHideGenMode, BOOL bIsSummoned = FALSE, BOOL bFirmBerserk = FALSE, BOOL bIsMaster = FALSE, int iGuildGUID = NULL);
	//BOOL bCreateNewNpc(char * pNpcName, char * pName, char * pMapName, short sX, short sY);
	BOOL _bReadMapInfoFiles(int iMapIndex);
	
	BOOL _bGetIsStringIsNumber(char * pStr);
	BOOL _bInitItemAttr(class CItem * pItem, char * pItemName);
	BOOL bReadProgramConfigFile(char * cFn);
	void GameProcess();
	void InitPlayerData(int iClientH, char * pData, DWORD dwSize);
	void ResponsePlayerDataHandler(char * pData, DWORD dwSize);
	BOOL bSendMsgToLS(DWORD dwMsg, int iClientH, BOOL bFlag = TRUE, char *pData = NULL);
	void OnMainLogRead();
	void OnMainLogSocketEvent(UINT message, WPARAM wParam, LPARAM lParam);
	void CheckClientResponseTime();
	void OnTimer(char cType);
	int iComposeMoveMapData(short sX, short sY, int iClientH, char cDir, char * pData);
	void SendEventToNearClient_TypeB(DWORD dwMsgID, WORD wMsgType, char cMapIndex, short sX, short sY, short sV1, short sV2, short sV3, short sV4 = NULL);
	void SendEventToNearClient_TypeA(short sOwnerH, char cOwnerType, DWORD dwMsgID, WORD wMsgType, short sV1, short sV2, short sV3);
	//SNOOPY: Version to show self attacks (Stormbringer)
	void SendEventToNearClient_TypeASelf(short sOwnerH, char cOwnerType, DWORD dwMsgID, WORD wMsgType, short sV1, short sV2, short sV3);
	void SendNearClientToChar(short sOwnerH, short sClient);
	void SendNearMobToChar(short sOwnerH, short sClient);
	void SendNewInitMapData(int iClientH); // To initialise again when using/not using Beholder power
	
	void DeleteClient(int iClientH, BOOL bSave, BOOL bNotify, BOOL bCountLogout = TRUE, BOOL bForceCloseConn = FALSE);
	// Snoopy: to prevent hacker to use hack only for emergency deco
	void DelayedDeleteClient(int iClientH, BOOL bSave, BOOL bNotify, BOOL bCountLogout = TRUE, BOOL bForceCloseConn = FALSE);

	



	// Snoopy: Avatar functions........
	BOOL bReadAvatarStructureConfigFile(char * cFn);
	void _CreateAvatarGUID(DWORD dwAvatarGUID, int iWinnerSide);
	BOOL bReadAvatarGUIDFile(char * cFn);

	void GlobalStartAvatarMode();
	void LocalStartAvatarMode(DWORD dwAvatarGUID);
	void GlobalEndAvatarMode(int iWinnerSide);
	void ManualEndAvatarMode(int iWinnerSide);
	void LocalEndAvatarMode(int iWinnerSide, char * cAvatarMessenger);

	void RelicGet(int iClientH, class CItem * pItem);
	void RelicDrop(int iClientH, class CItem * pItem);
	void CheckIfRelicDrop(int iClientH);
	void CheckRelicGoal();
	void GetGlobalAvatarInfo(int sV1, int sV2, int sV3, char * pString,  int sV4);
	void SendGlobalAvatarInfo(int sV1, int sV2, int sV3, char * pString,  int sV4);

	void CreateAvatarStructures();
	void RemoveAvatarStructures ();







		
	int  iComposeInitMapData(short sX, short sY, int iClientH, char * pData);
	void RequestInitDataHandler(int iClientH, char * pData, char cKey);
	void RequestInitPlayerHandler(int iClientH, char * pData, char cKey);
	int iClientMotion_Move_Handler(int iClientH, short sX, short sY, char cDir, char cMoveType, BOOL bIsBlocked = FALSE);
	void ClientMotionHandler(int iClientH, char * pData, DWORD dwMsgTime);
	void DisplayInfo(HDC hdc,HWND G_hWnd); // Snoopy added window pointer
	void OnClientRead(int iClientH, DWORD dwTime);
	BOOL bInit();
	void OnClientSocketEvent(UINT message, WPARAM wParam, LPARAM lParam);
	BOOL bAccept(class XSocket * pXSock);
	BOOL bAcceptPing(class XSocket * pXSock);
	// v1.4311-3 함수 선언 입장권 받는 함수 .. void GetFightzoneTicketHandler(int iClientH);
	void GetFightzoneTicketHandler(int iClientH);
	// v1.4311-3 2 시간마다 사투장 예약을 초기화 시킨다.
	void FightzoneReserveProcessor() ;

	// New 06/05/2004
	// Upgrades
	BOOL bCheckIsItemUpgradeSuccess(int iClientH, int iItemIndex, int iSomH, BOOL bBonus = FALSE);
	void RequestItemUpgradeHandler(int iClientH, int iItemIndex);
	void SetAngelFlag(short sOwnerH, char cOwnerType, int iStatus, int iTemp);

	void StormBlade(int iClientH, int iMapIndex, short dX, short dY);
	
	//Party Codes
	void RequestCreatePartyHandler(int iClientH);
	void PartyOperationResultHandler(char *pData);
	void PartyOperationResult_Create(int iClientH, char *pName, int iResult, int iPartyID);
	void PartyOperationResult_Join(int iClientH, char *pName, int iResult, int iPartyID);
	void PartyOperationResult_Dismiss(int iClientH, char *pName, int iResult, int iPartyID);
	void PartyOperationResult_Delete(int iPartyID);
	void RequestJoinPartyHandler(int iClientH, char *pData, DWORD dwMsgSize);
	void RequestDismissPartyHandler(int iClientH);
	void GetPartyInfoHandler(int iClientH);
	void PartyOperationResult_Info(int iClientH, char * pName, int iTotal, char *pNameList);
	void RequestDeletePartyHandler(int iClientH);
	void RequestAcceptJoinPartyHandler(int iClientH, int iResult);
	void GetExp(int iClientH, int iExp, BOOL bIsAttackerOwn = FALSE);

	// New 07/05/2004
	// Guild Codes
	void RequestGuildNameHandler(int iClientH, int iObjectID, int iIndex);

	// Item Logs
	BOOL _bItemLog(int iAction,int iClientH , char * cName, class CItem * pItem);
	BOOL _bItemLog(int iAction,int iGiveH, int iRecvH, class CItem * pItem,BOOL bForceItemLog = FALSE);
	BOOL _bCheckGoodItem( class CItem * pItem );

	BOOL bCheckAndConvertPlusWeaponItem(int iClientH, int iItemIndex);
	void ArmorLifeDecrement(int iAttackerH, int iTargetH, char cOwnerType, int iValue);

	// MultiDrops
	BOOL bGetMultipleItemNamesWhenDeleteNpc(short sNpcType, int iProbability, int iMin, int iMax, short sBaseX, short sBaseY,
											   int iItemSpreadType, int iSpreadRange,
											   int *iItemIDs, POINT *BasePos, int *iNumItem);

	// Player shutup
	void GSM_RequestShutupPlayer(char * pGMName,WORD wReqServerID, WORD wReqClientH, WORD wTime,char * pPlayer );
	// Abbaddon's Thunder...
	void DoAbaddonThunderDamageHandler(char cMapIndex);
	void SendThunder(int iClient, short sX, short sY, short sV3, short sV4);
	// PK Logs
	BOOL _bPKLog(int iAction,int iAttackerH , int iVictumH, char * pNPC);

	CGame(HWND hWnd);
	virtual ~CGame();

	char m_cServerName[11];
	char m_cGameServerAddr[16];
	char m_cGameServerAddrInternal[16];
	char m_cGameServerAddrExternal[16];
	int  m_iGameServerMode;
	char m_cLogServerAddr[16];
	char m_cGateServerAddr[16];
	int  m_iGameServerPort;
	int  m_iLogServerPort;
	int  m_iGateServerPort;

	int  m_iLimitedUserExp, m_iLevelExp20;

//private:
	BOOL _bDecodeItemConfigFileContents(char * pData, DWORD dwMsgSize);
	int _iComposePlayerDataFileContents(int iClientH, char * pData);
	BOOL _bDecodePlayerDatafileContents(int iClientH, char * pData, DWORD dwSize);
	BOOL _bRegisterMap(char * pName);

	class CClient * m_pClientList[DEF_MAXCLIENTS];
	class CNpc    * m_pNpcList[DEF_MAXNPCS];
	class CMap    * m_pMapList[DEF_MAXMAPS];
	class CNpcItem * m_pTempNpcItem[DEF_MAXNPCITEMS];
	class CDynamicObject * m_pDynamicObjectList[DEF_MAXDYNAMICOBJECTS];
	class CDelayEvent    * m_pDelayEventList[DEF_MAXDELAYEVENTS];

	class CMsg    * m_pMsgQuene[DEF_MSGQUENESIZE];
	int             m_iQueneHead, m_iQueneTail;
	int             m_iTotalMaps;
	class XSocket * m_pMainLogSock, * m_pGateSock;
	int				m_iGateSockConnRetryTimes;
	class CMisc     m_Misc;
	BOOL			m_bIsGameStarted;
	BOOL            m_bIsLogSockAvailable, m_bIsGateSockAvailable;
	BOOL			m_bIsItemAvailable, m_bIsBuildItemAvailable, m_bIsNpcAvailable, m_bIsMagicAvailable;
	BOOL			m_bIsSkillAvailable, m_bIsPortionAvailable, m_bIsQuestAvailable, m_bIsTeleportAvailable;
	class CItem   * m_pItemConfigList[DEF_MAXITEMTYPES];
	class CNpc    * m_pNpcConfigList[DEF_MAXNPCTYPES];
	class CMagic  * m_pMagicConfigList[DEF_MAXMAGICTYPE];
	class CSkill  * m_pSkillConfigList[DEF_MAXSKILLTYPE];
	class CQuest  * m_pQuestConfigList[DEF_MAXQUESTTYPE];

	class CTeleport * m_pTeleportConfigList[DEF_MAXTELEPORTLIST];

	char            m_pMsgBuffer[DEF_MSGBUFFERSIZE+1];

	HWND  m_hWnd;
	int   m_iTotalClients, m_iMaxClients, m_iTotalGameServerClients, m_iTotalGameServerMaxClients;
	int   m_iTotalBots, m_iMaxBots, m_iTotalGameServerBots, m_iTotalGameServerMaxBots;
	SYSTEMTIME m_MaxUserSysTime;

	BOOL  m_bF1pressed, m_bF4pressed, m_bF12pressed, m_bF5pressed;
	BOOL  m_bOnExitProcess;
	DWORD m_dwExitProcessTime;

	DWORD m_dwWhetherTime, m_dwGameTime1, m_dwGameTime2, m_dwGameTime3, m_dwGameTime4, m_dwGameTime5, m_dwGameTime6, m_dwFishTime;
	
	// Crusade Schedule
	BOOL m_bIsCrusadeWarStarter;
	BOOL m_bIsApocalypseStarter;
	int m_iLatestCrusadeDayOfWeek;
	int m_iCrusadeGMG, m_iCrusadeGMGMax;
	BOOL m_bEverybodyAdvised;		// True when everybody has been advised of Manasotes positions....

	// SNOOPY: Here the reason for DayNight not functionning !
	// BOOL  m_cDayOrNight;	
	char  m_cDayOrNight;		// Needed int !

 	int   m_iSkillSSNpoint[102];

	class CMsg * m_pNoticeMsgList[DEF_MAXNOTIFYMSGS];
	int   m_iTotalNoticeMsg, m_iPrevSendNoticeMsg;
	DWORD m_dwNoticeTime, m_dwSpecialEventTime;
	BOOL  m_bIsSpecialEventTime;
	char  m_cSpecialEventType;

	int m_iLevelExpTable[3500];	//New 22/10/04

 	class CFish * m_pFish[DEF_MAXFISHS];
	class CPortion * m_pPortionConfigList[DEF_MAXPORTIONTYPES];
//crafting:
	class CPortion * m_pCraftingConfigList[DEF_MAXPORTIONTYPES];

	BOOL  m_bIsServerShutdowned;
	char  m_cShutDownCode;
	class CMineral * m_pMineral[DEF_MAXMINERALS];

	int   m_iMiddlelandMapIndex;	// 
	int   m_iAresdenMapIndex;		//  
	int	  m_iElvineMapIndex;		// 
	int   m_iBTFieldMapIndex;
	int   m_iRampartMapIndex;
	int   m_iGodHMapIndex;
	int   m_iAresdenOccupyTiles;
	int   m_iElvineOccupyTiles;
	int   m_iCurMsgs, m_iMaxMsgs;

	// v1.4311-3 변수 선언  예약된 시간을 가지는 변수 DWORD m_dwCanFightzoneReserveTime 
	DWORD m_dwCanFightzoneReserveTime ;

	// v1.4311-3 변수 선언 각 사투장의 예약 여부를 저장 int  m_iFightZoneReserve[DEF_MAXFIGHTZONE];
	int  m_iFightZoneReserve[DEF_MAXFIGHTZONE] ;
	// v1.4311-3 변수 선언 사투장에 들어갔을때 운영자 명령어로 강콜 않되게 함.
	int  m_iFightzoneNoForceRecall  ;

	struct {
		__int64 iFunds;
		__int64 iCrimes;
		__int64 iWins;

	} m_stCityStatus[DEF_MAXSIDES]; // bigger here to enable 10 "sides"
	
	int	  m_iStrategicStatus;
	
	class XSocket * m_pSubLogSock[DEF_MAXSUBLOGSOCK];
	int   m_iSubLogSockInitIndex;
	BOOL  m_bIsSubLogSockAvailable[DEF_MAXSUBLOGSOCK];
	int   m_bIsSubLogSockInitialPointer[DEF_MAXSUBLOGSOCK]; // by Snoopy
	int	  m_iCurSubLogSockIndex;
	int   m_iSubLogSockFailCount;
	int   m_iSubLogSockActiveCount;	// v1.5 현재 연결 상태가 유지되고 있는 sub-log-socket 갯수
	int   m_iAutoRebootingCount;	// v1.5 자동 재부팅 된 횟수 

	class CBuildItem * m_pBuildItemList[DEF_MAXBUILDITEMS];
	class CItem * m_pDupItemIDList[DEF_MAXDUPITEMID];

	char * m_pNoticementData;
	DWORD  m_dwNoticementDataSize;

	DWORD  m_dwMapSectorInfoTime;
	int    m_iMapSectorInfoUpdateCount;

	// Crusade 처리용
	int	   m_iCrusadeCount;			// 0이면 전면전 대기상태. 1이면 카운트 다운 시작. 
	BOOL   m_bIsCrusadeMode;		// 크루세이드 모드

	BOOL   m_bIsApocalypseMode;	
	BOOL   m_bIsApocalypseGateOpen; // SNOOPY edd
	// Daryl - Chat logging option
	BOOL m_bLogChatOption;

	struct {
		char cMapName[11];			// 
		char cType;					// 
		int  dX, dY;				// 
		bool bManaStoneValid;		// SNOOPY: Added this to enable 3 random stones in ML

	} m_stCrusadeStructures[DEF_MAXCRUSADESTRUCTURES];
	// SNOOPY: Added to store the ManaStones number in ML, for crusades.
	int m_iManaStoneNumber;
	int m_iCollectedMana[3];
	int m_iAresdenMana, m_iElvineMana;
	int m_iLastSentAresdenMana, m_iLastSentElvineMana;

	struct {
		char cMapName[11];		// Name in avatar.cfg
		char cMapIndex;			// MapIndex or -1 if not on server
		char cType;				// DynamicObject type (15..21)
		int  dX, dY;			// Position
		char cStatueRank;		// -1 if absent, else 1..6
	} m_stAvatarStatues[DEF_MAX_STATUE_LOCATIONS];	
	struct {
		char cMapName[11];		// Name in avatar.cfg
		char cMapIndex;			// MapIndex or -1 if not on server
		char cType;				// Structure type
		int  dX, dY;			// Position
		char cMobSide;			// -1 mean Avatar absent
	} m_stAvatarStructures[DEF_MAX_STATUE_LOCATIONS];
	
	DWORD m_dwAvatarGUID;		// Unique event identifier
	DWORD m_dwAvatarStartTime;	// beginning time
	int   m_iAvatarWinnerSide;	// Side winning previous event or -1 during event
	BOOL  m_bIsAvatarMode;		// TRUE during event
	int   m_iPLmapIndex;		// 
	char  m_cAvatarMessenger[11]; // Name or character with the relic	
	int	  m_iAvatarMessenger;	// char id, if PL on this server.
	int	  m_iStatueCount;		// Rank of next Statue
	int	  m_iStatueIndex;		// Index of next Statue








	class CTeleportLoc m_pGuildTeleportLoc[DEF_MAXGUILDS];

	WORD  m_wServerID_GSS;
	char  m_cGateServerStockMsg[DEF_MAXGATESERVERSTOCKMSGSIZE];
	int   m_iIndexGSS;

	int m_iLastCrusadeWinner; 	// New 13/05/2004
	int m_iCrusadeAdvantage;	// Added by SNOOPY
	struct {
		int iCrashedStructureNum;
		int iStructureDamageAmount;
		int iCasualties;
	} m_stMeteorStrikeResult;

	struct {
		char cType;			// 
		char cSide;			// 
		short sX, sY;		// 
	} m_stMiddleCrusadeStructureInfo[DEF_MAXCRUSADESTRUCTURES];

	struct {
		char m_cBannedIPaddress[21];		 // IP address
	} m_stBannedList[DEF_MAXBANNED];

	struct {
		char m_cGMName[11];
	} m_stAdminList[DEF_MAXADMINS];

	// Remember erazed clients
	struct {
		int iClientH;
		char m_cCharName[11];
		char m_cAccountName[11];
		char m_cAccountPassword[11];
		DWORD m_dwDeleteTime;
	} m_stOldClientList[DEF_MAXCLIENTS];

	// Crusade Scheduler
	struct {
		int iDay;
		int iHour;
		int iMinute;
	} m_stCrusadeWarSchedule[DEF_MAXSCHEDULE];

	struct {
		int iDay;
		int iHour;
		int iMinute;
	} m_stApocalypseScheduleStart[DEF_MAXAPOCALYPSE];

	struct {
		int iDay;
		int iHour;
		int iMinute;
	} m_stApocalypseScheduleEnd[DEF_MAXAPOCALYPSE];

	struct {
		int iDay;
		int StartiHour;
		int StartiMinute;
		int EndiHour;
		int EndiMinute;
	} m_stHeldenianSchedule[DEF_MAXHELDENIAN];

	int m_iTotalMiddleCrusadeStructures;
 

	int m_iClientShortCut[DEF_MAXCLIENTS+1];

	int m_iNpcConstructionPoint[DEF_MAXNPCTYPES];
	DWORD m_dwCrusadeGUID;
	DWORD m_dwCrusadeStartTime;
	int   m_iCrusadeWinnerSide;
	int   m_iPlayerMaxLevel;


	struct  {
		int iTotalMembers;
		int iIndex[9];
	}m_stPartyInfo[DEF_MAXCLIENTS];

	// Daryl - Admin level adjustments
	int m_iAdminLevelWho;
	int m_iAdminLevelGMKill;
	int m_iAdminLevelGMRevive;
	int m_iAdminLevelGMCloseconn;
	int m_iAdminLevelGMCheckRep;
	int m_iAdminLevelEnergySphere;
	int m_iAdminLevelShutdown;
	int m_iAdminLevelObserver;
	int m_iAdminLevelShutup;
	int m_iAdminLevelCallGaurd;
	int m_iAdminLevelSummonDemon;
	int m_iAdminLevelSummonDeath;
	int m_iAdminLevelReserveFightzone;
	int m_iAdminLevelCreateFish;
	int m_iAdminLevelTeleport;
	int m_iAdminLevelCheckIP;
	int m_iAdminLevelPolymorph;
	int m_iAdminLevelSetInvis;
	int m_iAdminLevelSetZerk;
	int m_iAdminLevelSetIce;
	int m_iAdminLevelGetNpcStatus;
	int m_iAdminLevelSetAttackMode;
	int m_iAdminLevelUnsummonAll;
	int m_iAdminLevelUnsummonDemon;
	int m_iAdminLevelSummon;
	int m_iAdminLevelSummonAll;
	int m_iAdminLevelSummonPlayer;
	int m_iAdminLevelDisconnectAll;
	int m_iAdminLevelEnableCreateItem;
	int m_iAdminLevelCreateItem;
	int m_iAdminLevelStorm;
	int m_iAdminLevelWeather;
	int m_iAdminLevelSetStatus;
	int m_iAdminLevelGoto;
	int m_iAdminLevelMonsterCount;
	int m_iAdminLevelSetRecallTime;
	int m_iAdminLevelUnsummonBoss;
	int m_iAdminLevelClearNpc;
	int m_iAdminLevelTime;
	int m_iAdminLevelPushPlayer;
	int m_iAdminLevelSummonGuild;
	int m_iAdminLevelCheckStatus;
	int m_iAdminLevelCleanMap;

	// Snoopy: Allow Admin to change pk-mode setting for a map
	int m_iAdminLevelSetPkMode;
	// Snoopy: Allow Admin to change map type (drops rewards penalty xp....)
	int m_iAdminLevelSetMapType;
	// SNOOPY: Added Admin command getserverinfo
	int m_iAdminLevelGetServerInfo;
	// Snoopy: Added Admin command setmapmobnum
	int m_iAdminLevelMapMobNum;
	int m_iAdminLevelPopoEnabled;
	// Snoopy: AddedAdminlevel settings for starting Events (Apoc/Crusade/Heldenian)
	int m_iAdminLevelSpecialEvents;


	// SNOOPY: Added Alchimy and gizon item upgrades
	bool m_iAlchimyItemUpgradeEnabled;
	bool m_iGizonItemUpgradeEnabled;
	// SNOOPY: validation number for the server.
	int  m_iServerValidationNumber;
	// SNOOPY: 
	int  m_iClientConnectionCheckTime;
	int  m_iClientConnectionCheckMaxNumber;
	int  m_iClientConnectionCheckTimeRound;
	int  m_iCCCNeededForValidation;
	WORD m_wServerValidationCRC1;
	WORD m_wServerValidationCRC2;
	DWORD m_dwMSGID_REQUEST_REGISTERGAMESERVER;
	int  m_iLowServerGapCount;
	int  m_iVariableTimeOut; // DEF_CLIENTTIMEOUT (=10000)
	// SNOOPY: to allow a warning message to stay showned on buggy serveur
	int m_iBugWarning;
	char m_cBugText[127];

	//SNOOPY: added variable Hourlly XP check due to variable XPrate.
	int m_iHourllyXP250;
	int m_iHourllyXP300;
	int m_iHourllyXP400;
	//m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_iXPRate

	// SNOOPY81: for equilibrium map configuration.
	BOOL m_bMapModeEquilibrium;
	BOOL m_bMapModeEquilibriumChanged;

	// SNOOPY: Added pvp-hp-mode = HIGH or LOW
// in HIGH mode PvP, Player attacking player has a far better chance to hit.
// Defence formula is changed from Dext x 1 to Dext x1
// Critical attacks give a -100 malus to defender instead of +100 to hit 
	BOOL m_bPVPHPMode; 
// SNOOPY: Added this to choose the XP mode for the server
// Classic is standard HB (bonus up to level 80, reduced in farms above lvl 80
// USA is huge bonusses up to lvl 120.
// EQUILIBRIUM is my standard:
//             bonus up to lvl 120 instead of 80, no malus in farms at high levels
//			   malus for 10 max levels of the server (140 -> 150 (2% per level)
//			   XP20% weapons are counted AFTER the party XP sharing.
	int m_iXPBonusType;
// Either log all party info or just short log (default)
	bool m_iPartyLog;
// SNOOPY: Added function to limit chances of high % items with low skill alchemists
	int SkillCap (int Value, int SkillAl);
// SNOOPY: Admin order to save characters
	void AdminOrder_SaveChar(int iClientH, char * pData, DWORD dwMsgSize);
// SNOOPY: Added functions for special weapons
	bool SpecialWeapon_DS(int iClientH);
	bool SpecialWeapon_Orc(int iClientH);
	bool SpecialWeapon_StormBringer(int iClientH, int sItemIndex);
	void SpecialWeapon_StormBringer_KillsNow(int iClientH, int sItemIndex);	

//SNOOPY: Added PriestDruid functions
	void Become_PriestDruid(int iClientH);
	void Set_PriestDruid(int iClientH);
//SNOOPY: compute relative strengths on a server.
	int CalcCityStr(int iSide, char cMapIndex, bool bWantNumber, bool bIncludeAFK);
	// Reintroduced Teleport List functions...
	BOOL bDecodeTeleportList(char *pFn);
	void RequestChargedTeleportHandler(int iClientH, char *pData, DWORD dwMsgSize);
	void RequestTeleportListHandler(int iClientH, char * pData, DWORD dwMsgSize);


	bool bShowActivity; // Standard is true, to show activity on server , false will show relative strenths
	char m_cKillerIndicator; //0: never(default), 1: unless crusade, 2: even in crusade.
	short m_sSlateSuccessRate;
	short m_sForceRecallTime;
	int	 m_iPrimaryDropRate, m_iSecondaryDropRate;
	//SNOOPY:
	int	 m_iGoldDropRate;

	// 25/05/2004
	int m_iFinalShutdownCount;

	// New 06/07/2004
	BOOL m_bEnemyKillMode;
	int m_iEnemyKillAdjust;
	BOOL m_bAdminSecurity;

	// Configurable Raid Time 
	short m_sRaidTimeMonday; 
	short m_sRaidTimeTuesday; 
	short m_sRaidTimeWednesday; 
	short m_sRaidTimeThursday; 
	short m_sRaidTimeFriday; 
	short m_sRaidTimeSaturday; 
	short m_sRaidTimeSunday; 

	BOOL m_bManualTime;
	int m_iSummonGuildCost;
	
	// 	Heldenian
	BOOL	m_bIsHeldenianMode;			// Event has started	-> can TP on maps
	BOOL	m_bHeldenianWarInitiated;	// War has begun		-> can Fight 
	char	m_cHeldenianType;			// Type 1: (BtField) 
										// Type 2: (Casttle siege) Previous winner will defend.
	char    m_sLastHeldenianWinner;		// Last war result, allows to TP on BtField out off war time
										// Tells defender for next Type 2 Heldenian
	char	m_cHeldenianWinner;			// If victory before Event timeOut, tell who wins
	DWORD	m_dwHeldenianGUID;			// identify this event
	DWORD	m_dwHeldenianWarStartTime;	// 15min delay to start the real war
	DWORD	m_dwHeldenianFinishTime;	// 1h30 after, finish the event and compute result...	
	char	m_cHeldenianFirstDestroyedTowerWinner;
	int m_iHeldenianAresdenDead, m_iHeldenianElvineDead;
	int m_iHeldenianAresdenFlags, m_iHeldenianElvineFlags;
	int m_iHeldenianAresdenLeftTower, m_iHeldenianElvineLeftTower;

	DWORD m_dwApocalypseGUID;
	DWORD m_dwApocalypseGateOpenTime;
	DWORD m_dwApocalypseGateCloseTime;
	BOOL var_89C, var_8A0;

	BOOL m_bReceivedItemList;

	// Slate exploit
	int m_sCharPointLimit;

	// Limit Checks
	short m_sCharStatLimit;
	//BOOL  m_bAllow100AllSkill;
	short m_sCharSkillLimit;
	char  m_cRepDropModifier;
	char  m_cSecurityNumber[11];
	short m_sAbsoluteMaxPlayerLevel;
	short m_sEvilMaxPlayerLevel; // Max level for Evil side 
	DWORD m_dwBuildDate;	


private:
	int __iSearchForQuest(int iClientH, int iWho, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	int _iTalkToNpcResult_Cityhall(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	void _ClearExchangeStatus(int iToH);
	int _iGetItemSpaceLeft(int iClientH);

public:
	void AdminOrder_GoTo(int iClientH, char* pData, DWORD dwMsgSize);
	void AdminOrder_MonsterCount(int iClientH, char* pData, DWORD dwMsgSize);
	void AdminOrder_SetForceRecallTime(int iClientH, char* pData, DWORD dwMsgSize);
	void AdminOrder_UnsummonBoss(int iClientH);
	void RemoveCrusadeNpcs(void);
	void RemoveCrusadeRecallTime(void);
	BOOL _bCrusadeLog(int iAction,int iClientH,int iData, char * cName);
	int iGetPlayerABSStatus(int iClientH);
	BOOL _bInitItemAttr(class CItem * pItem, int iItemID);
	void ReqCreateSlateHandler(int iClientH, char* pData);
	void SetSlateFlag(int iClientH, short sType, bool bFlag);
	void CheckForceRecallTime(int iClientH);
	void SetPlayingStatus(int iClientH);
	void ForceChangePlayMode(int iClientH, bool bNotify);
	void ShowVersion(int iClientH);
	void ShowClientMsg(int iClientH, char* pFrom, char* pMsg); // Snoopy added pFrom
	void RequestResurrectPlayer(int iClientH, bool bResurrect);


};

#endif // !defined(AFX_GAME_H__C3D29FC5_755B_11D2_A8E6_00001C7030A6__INCLUDED_)
