// Game.h: interface for the CGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAME_H__0089D9E3_74E6_11D2_A8E6_00001C7030A6__INCLUDED_)
#define AFX_GAME_H__0089D9E3_74E6_11D2_A8E6_00001C7030A6__INCLUDED_

// for client only : MJ Stats Change - Diuuude
 #define DEF_STR							0x01
 #define DEF_DEX							0x02
 #define DEF_INT							0x03
 #define DEF_VIT							0x04
 #define DEF_MAG							0x05
 #define DEF_CHR							0x06


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mmsystem.h>
#include <winbase.h>
#include <memory.h>
#include <string.h>
#include <process.h>
#include <direct.h>
#include <tlhelp32.h>  // pour MP3

#include "GlobalDef.h"
#include "DXC_ddraw.h"
#include "DXC_dinput.h"
#include "YWSound.h"
#include "SoundBuffer.h"
#include "XSocket.h"
#include "Sprite.h"
#include "SpriteID.h"
#include "Misc.h"
#include "StrTok.h"
#include "Msg.h"
#include "Effect.h"
#include "MapData.h"
#include "ActionID.h"
#include "NetMessages.h"
#include "MouseInterface.h"
#include "CharInfo.h"
#include "Item.h"
#include "Magic.h"
#include "Skill.h"
#include "DynamicObjectID.h"
#include "GameMonitor.h"
#include "BuildItem.h"
#include "ItemName.h"
#include "Curse.h"
#include "Cint.h"

// Snoopy: MP3 support
#include "mp3.h"
#include "CRCdemo.h"


#ifdef DEF_USING_WIN_IME
	#include <RICHEDIT.H>
#endif

//Snoopy: Implementation JPG sreenshots
#include "cximage/ximage.h" // Snoopy
#include "cximage/ximajpg.h" // Snoopy

//v2.18
#define DEF_BTNSZX				74
#define DEF_BTNSZY				20
#define DEF_LBTNPOSX			30
#define DEF_RBTNPOSX			154
#define DEF_BTNPOSY				292

#define DEF_INDEX4_MSGID		0
#define DEF_INDEX2_MSGTYPE		4

#define DEF_SOCKETBLOCKLIMIT	300

#define DEF_MAXSPRITES			25000	// 20000 // Snoopy: Adjusted!
#define DEF_MAXTILES			1000	// 800 // Snoopy: Adjusted!
#define DEF_MAXEFFECTSPR		300
#define DEF_MAXSOUNDEFFECTS		200		// 110   //Snoopy: Adjusted!
#define DEF_MAXCHATMSGS			500
#define DEF_MAXWHISPERMSG		5
#define DEF_MAXCHATSCROLLMSGS	80
#define DEF_MAXEFFECTS			300	//600 <- original
#define DEF_CHATTIMEOUT_A		4000
#define DEF_CHATTIMEOUT_B		500
#define DEF_CHATTIMEOUT_C		2000
#define DEF_MAXITEMS			50
#define DEF_MAXBANKITEMS		121 // v1.2 120+1
#define DEF_MAXGUILDSMAN		32
#define DEF_MAXMENUITEMS		150  //v2.15  120 ->140, Snoopy: 140 ->150
#define DEF_TEXTDLGMAXLINES		300 //v2.18 3000->300

#define DEF_MAXMAGICTYPE		100
#define DEF_MAXSKILLTYPE		60
#define DEF_MAXWHETHEROBJECTS	600
#define DEF_MAXBUILDITEMS		100
#define DEF_MAXGAMEMSGS			300
#define DEF_MAXITEMNAMES		1000
#define DEF_MAXGUILDNAMES		100
#define DEF_MAXSELLLIST			12

#define WM_USER_GAMESOCKETEVENT	WM_USER + 2000
#define WM_USER_LOGSOCKETEVENT	WM_USER + 2001
#define WM_USER_MP3_EVENT		WM_USER + 2002

#define DEF_GAMEMODE_NULL					-2
#define DEF_GAMEMODE_ONQUIT					-1
#define DEF_GAMEMODE_ONMAINMENU				0
#define DEF_GAMEMODE_ONCONNECTING			1
#define DEF_GAMEMODE_ONLOADING				2
#define DEF_GAMEMODE_ONWAITINGINITDATA		3
#define DEF_GAMEMODE_ONMAINGAME				4
#define DEF_GAMEMODE_ONCONNECTIONLOST		5
#define DEF_GAMEMODE_ONMSG					6
#define DEF_GAMEMODE_ONCREATENEWACCOUNT		7
#define DEF_GAMEMODE_ONLOGIN				8
#define DEF_GAMEMODE_ONQUERYFORCELOGIN		9
#define DEF_GAMEMODE_ONSELECTCHARACTER		10
#define DEF_GAMEMODE_ONCREATENEWCHARACTER	11
#define DEF_GAMEMODE_ONWAITINGRESPONSE		12
#define DEF_GAMEMODE_ONQUERYDELETECHARACTER 13
#define DEF_GAMEMODE_ONLOGRESMSG			14
#define DEF_GAMEMODE_ONCHANGEPASSWORD		15
#define DEF_GAMEMODE_ONVERSIONNOTMATCH		17
#define DEF_GAMEMODE_ONINTRODUCTION			18
#define DEF_GAMEMODE_ONAGREEMENT			19
#define DEF_GAMEMODE_ONSELECTSERVER			20
#define DEF_GAMEMODE_ONINPUTKEYCODE			21

#define DEF_SERVERTYPE_GAME			1
#define DEF_SERVERTYPE_LOG			2

#define DEF_CURSORSTATUS_NULL		0
#define DEF_CURSORSTATUS_PRESSED	1
#define DEF_CURSORSTATUS_SELECTED	2
#define DEF_CURSORSTATUS_DRAGGING	3

#define DEF_SELECTEDOBJTYPE_DLGBOX	1
#define DEF_SELECTEDOBJTYPE_ITEM	2

#define DEF_DOUBLECLICKTIME			300
#define DEF_MAXPARTYMEMBERS			8
#define DEF_MAXCRUSADESTRUCTURES	300


class CGame
{
public:
	// CLEROTH - AURAS
	void CheckActiveAura(short sX, short sY, DWORD dwTime, short sOwnerType);
	void CheckActiveAura2(short sX, short sY, DWORD dwTime, short sOwnerType);

	// MJ Stats Change Related functions - Alastor
	void DrawDialogBox_ChangeStatsMajestic(short msX, short msY);		// Change stats using majestic - Alastor
	void DlgBoxClick_ChangeStatsMajestic(short msX, short msY);			// Change stats using majestic - Alastor

	// MJ Stats Change Related vars - Alastor
	char cStateChange1;
	char cStateChange2;
	char cStateChange3;

	int m_iTeleportMapCount;
	void ResponseTeleportList(char * pData);
	void ResponseChargedTeleport(char * pData);
	void * operator new (size_t size)
	{
		return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
	};

	void operator delete(void * mem)
	{
		HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, mem);
	};

	void ItemEquipHandler(char cItemID);
	void ReleaseEquipHandler(char cEquipPos);

	void ReadSettings();
	void WriteSettings();

	int  iGetManaCost(int iMagicNo);
	void UseMagic(int iMagicNo);
	BOOL _bCheckMoveable( short sx, short sy );
	BOOL FindGuildName(char* pName, int* ipIndex);
	void bItemDrop_SkillDialog();
	void bItemDrop_IconPannel(short msX, short msY);
	void bItemDrop_Character();
	void bItemDrop_Inventory(short msX, short msY);
	void bItemDrop_ItemUpgrade();
	void bItemDrop_SellList(short msX, short msY);
	void bItemDrop_ExchangeDialog(short msX, short msY);
	void bItemDrop_Bank(short msX, short msY);
	void bItemDrop_ExternalScreen(char cItemID, short msX, short msY);
	void CreateScreenShot();
	void CrusadeWarResult(int iWinnerSide);
	void CrusadeContributionResult(int iWarContribution);
	void CannotConstruct(int iCode);
	void DrawTopMsg();
	void SetTopMsg(char * pString, unsigned char iLastSec);
	void DrawObjectFOE(int ix, int iy, int iFrame);
	void GrandMagicResult(char * pMapName, int iV1, int iV2, int iV3, int iV4, int iHP1, int iHP2, int iHP3, int iHP4) ;
	void MeteorStrikeComing(int iCode);
	void _Draw_OnLogin(char * pAccount, char * pPassword, int msX, int msY, int iFrame = 60000);
	void DrawNewDialogBox(char cType, int sX, int sY, int iFrame, BOOL bIsNoColorKey = FALSE, BOOL bIsTrans = FALSE);
	void AddMapStatusInfo(char * pData, BOOL bIsLastData);
	void _RequestMapStatus(char * pMapName, int iMode);
	int  GetCharKind(char *str, int index);
	void ReceiveString(char * pString);
	void EndInputString();
	void ClearInputString();
	void ShowReceivedString(BOOL bIsHide = FALSE);
	bool GetText(HWND hWnd,UINT msg,WPARAM wparam, LPARAM lparam);
	BOOL bReadItemNameConfigFile();
	void DrawDialogBoxs(short msX, short msY, short msZ, char cLB);
	void DrawDialogBox_Character(short msX, short msY);//1
	void DrawDialogBox_Inventory(int msX, int msY);//2
	void DrawDialogBox_Magic(short msX, short msY, short msZ);//3
	void DrawDialogBox_GuildMenu(short msX, short msY);//7
	void DrawDialogBox_GuildOperation(short msX, short msY);//8
	void DrawDialogBox_GuideMap(short msX, short msY, char cLB);//9
	void DrawDialogBox_Chat(short msX, short msY, short msZ, char cLB);//10
	void DrawDialogBox_Shop(short msX, short msY, short msZ, char cLB);//11
	void DrawDialogBox_LevelUpSetting(short msX, short msY);//12
	void DrawDialogBox_CityHallMenu(short msX, short msY);//13
	void DrawDialogBox_Bank(short msX, short msY, short msZ, char cLB);//14
	void DrawDialogBox_Skill(short msX, short msY, short msZ, char cLB);//15
	void DrawDialogBox_MagicShop(short msX, short msY, short msZ);//16
	void DrawDialogBox_QueryDropItemAmount();//17
	void DrawDialogBox_Text(short msX, short msY, short msZ, char cLB);//18
	void DrawDialogBox_SysMenu(short msX, short msY, char cLB);//19
	void DrawDialogBox_NpcActionQuery(short msX, short msY);//20
	void DrawDialogBox_NpcTalk(short msX, short msY, char cLB);//21
	void DrawDialogBox_Map();//22
	void DrawDialogBox_SellorRepairItem(short msX, short msY);//23
	void DrawDialogBox_Fishing(short msX, short msY);//24
	void DrawDialogBox_ShutDownMsg(short msX, short msY);//25
	void DrawDialogBox_SkillDlg(short msX, short msY, short msZ, char cLB);//26
	void DrawDialogBox_Exchange(short msX, short msY);//27
	void DrawDialogBox_Quest(int msX, int msY);//28
	void DrawDialogBox_GaugePannel();//29
	void DrawDialogBox_IconPannel(short msX, short msY);//30
	void DrawDialogBox_SellList(short msX, short msY);//31
	void DrawDialogBox_Party(short msX, short msY);//32
	void DrawDialogBox_CrusadeJob(short msX, short msY);//33
	void DrawDialogBox_ItemUpgrade(int msX, int msY);//34
	void DrawDialogBox_Help(int msX, int msY);//35
	void DrawDialogBox_Commander(int msX, int msY);//36
	void DrawDialogBox_Constructor(int msX, int msY);//37
	void DrawDialogBox_Soldier(int msX, int msY);//38
    void DrawDialogBox_ItemDrop(short msX, short msY);//4
	void DrawDialogBox_WarningMsg(short msX, short msY);//6
	void DrawDialogBox_15AgeMsg(short msX, short msY);//5
	void DrawDialogBox_FeedBackCard(short msX, short msY);//40
	void DisplayCommaNumber_G_cTxt(int iGold);// Name changed by Snoopy (easyer to understand...)

	void DrawDialogBox_ConfirmExchange(short msX, short msY); //41

	// Slates - Alastor
	void bItemDrop_Slates();
	void DlgBoxClick_Slates(short msX, short msY);
	void DrawDialogBox_Slates(short msX, short msY, short msZ, char cLB);//40

	BOOL _bCheckDlgBoxClick(short msX, short msY);
	void DlgBoxClick_WarningMsg(short msX, short msY);
	void DlgBoxClick_15AgeMsg(short msX, short msY);
	void DlgBoxClick_ItemDrop(short msX, short msY);
	void DlgBoxClick_Character(short msX, short msY);
	void DlgBoxClick_Inventory(short msX, short msY);
	void DlgBoxClick_Magic(short msX, short msY);
	void DlgBoxClick_GuildMenu(short msX, short msY);
	void DlgBoxClick_GuildOp(short msX, short msY);
	void DlgBoxClick_Shop(short msX, short msY);
	void DlgBoxClick_LevelUpSettings(short msX, short msY);
	void DlgBoxClick_CityhallMenu(short msX, short msY);
	void DlgBoxClick_Bank(short msX, short msY);
	void DlgBoxClick_Skill(short msX, short msY);
	void DlgBoxClick_MagicShop(short msX, short msY);
	void DlgBoxClick_FeedBackCard(short msX, short msY);
	void DlgBoxClick_Text(short msX, short msY);
	void DlgBoxClick_SysMenu(short msX, short msY);
	void DlgBoxClick_NpcActionQuery(short msX, short msY);
	void DlgBoxClick_NpcTalk(int msX, int msY);
	void DlgBoxClick_ItemSellorRepair(short msX, short msY);
	void DlgBoxClick_Fish(short msX, short msY);
	void DlgBoxClick_ShutDownMsg(short msX, short msY);
	void DlgBoxClick_SkillDlg(short msX, short msY);
	void DlgBoxClick_Exchange(short msX, short msY);

	void DlgBoxClick_Quest(int msX, int msY);
	void DlgBoxClick_SellList(short msX, short msY);
	void DlgBoxClick_IconPannel(short msX, short msY);
	void DlgBoxClick_Party(short msX, short msY);
	void DlgBoxClick_CrusadeJob(short msX, short msY);
	void DlgBoxClick_ItemUpgrade(int msX, int msY);
	void DlgBoxClick_Help(int msX, int msY);
	void DlgBoxClick_Commander(int msX, int msY);
	void DlgBoxClick_Constructor(int msX, int msY);
	void DlgBoxClick_Soldier(int msX, int msY);
	void NotifyMsgHandler(char * pData);
	void NotifyMsg_GlobalAttackMode(char * pData);
	void NotifyMsg_QuestReward(char * pData);
	void NotifyMsg_QuestContents(char * pData);
	void NotifyMsg_ItemColorChange(char * pData);
	void NotifyMsg_DropItemFin_CountChanged(char * pData);
	void NotifyMsg_CannotGiveItem(char * pData);
	void NotifyMsg_GiveItemFin_CountChanged(char * pData);
	void NotifyMsg_SetExchangeItem(char * pData);
	void NotifyMsg_OpenExchageWindow(char * pData);
	void NotifyMsg_DownSkillIndexSet(char * pData);
	void NotifyMsg_AdminInfo(char * pData);
	void NotifyMsg_WhetherChange(char * pData);
	void NotifyMsg_FishChance(char * pData);
	void NotifyMsg_EventFishMode(char * pData);
	void NotifyMsg_NoticeMsg(char * pData);
	void NotifyMsg_RatingPlayer(char * pData);
	void NotifyMsg_CannotRating(char * pData);
	void NotifyMsg_PlayerShutUp(char * pData);
	void NotifyMsg_TimeChange(char * pData);
	void NotifyMsg_Hunger(char * pData);
	void NotifyMsg_PlayerProfile(char * pData);
	void NotifyMsg_WhisperMode(BOOL bActive, char * pData);
	void NotifyMsg_PlayerStatus(BOOL bOnGame, char * pData);
	void NotifyMsg_Charisma(char * pData);
	void NotifyMsg_ItemRepaired(char * pData);
	void NotifyMsg_RepairItemPrice(char * pData);
	void NotifyMsg_CannotRepairItem(char * pData);
	void NotifyMsg_CannotSellItem(char * pData);
	void NotifyMsg_SellItemPrice(char * pData);
	void NotifyMsg_ShowMap(char * pData);
	void NotifyMsg_SkillUsingEnd(char * pData);
	void NotifyMsg_TotalUsers(char * pData);
	void NotifyMsg_MagicEffectOff(char * pData);
	void NotifyMsg_MagicEffectOn(char * pData);
	void NotifyMsg_SetItemCount(char * pData);
	void NotifyMsg_ItemDepleted_EraseItem(char * pData);
	void NotifyMsg_ServerChange(char * pData);
	void NotifyMsg_Skill(char * pData);
	void NotifyMsg_DropItemFin_EraseItem(char * pData);
	void NotifyMsg_GiveItemFin_EraseItem(char * pData);
	void NotifyMsg_EnemyKillReward(char * pData);
	void NotifyMsg_PKcaptured(char * pData);
	void NotifyMsg_PKpenalty(char * pData);
	void NotifyMsg_ItemToBank(char * pData);
	void NotifyMsg_ItemLifeSpanEnd(char * pData);
	void NotifyMsg_ItemReleased(char * pData);
	void NotifyMsg_LevelUp(char * pData);
	void NotifyMsg_SettingSuccess(char * pData); // CLEROTH - LU
	void NotifyMsg_MP(char * pData);
	void NotifyMsg_SP(char * pData);
	void NotifyMsg_SkillTrainSuccess(char * pData);
	void NotifyMsg_MagicStudyFail(char * pData);
	void NotifyMsg_MagicStudySuccess(char * pData);
	void NotifyMsg_DismissGuildsMan(char * pData);
	void NotifyMsg_NewGuildsMan(char * pData);
	void NotifyMsg_CannotJoinMoreGuildsMan(char * pData);
	void NotifyMsg_GuildDisbanded(char * pData);
	void NotifyMsg_Exp(char * pData);
	void NotifyMsg_Killed(char * pData);
	void NotifyMsg_HP(char * pData);
	void NotifyMsg_ItemPurchased(char * pData);
	void NotifyMsg_DismissGuildReject(char * pData);
	void NotifyMsg_DismissGuildApprove(char * pData);
	void NotifyMsg_JoinGuildReject(char * pData);
	void NotifyMsg_JoinGuildApprove(char * pData);
	void NotifyMsg_QueryDismissGuildPermission(char * pData);
	void NotifyMsg_QueryJoinGuildPermission(char * pData);
	void NotifyMsg_ItemObtained(char * pData);
	void NotifyMsg_ForceDisconn(char * pData);
	void NotifyMsg_BanGuildMan(char * pData);

	void ResponsePanningHandler(char * pData);
	void _CalcSocketClosed();
	void UpdateScreen_OnSelectServer();
	void StartInputString(int sX, int sY, unsigned char iLen, char * pBuffer, BOOL bIsHide = FALSE);
	void _SetIlusionEffect(int iOwnerH);
	int _iGetFOE(int iStatus);
	void NoticementHandler(char * pData);
	void GetItemName(char * cItemName, DWORD dwAttribute, char *pStr1, char *pStr2, char *pStr3);
	void GetItemName(class CItem * pItem, char * pStr1, char * pStr2, char * pStr3);
	void _InitOnCreateNewCharacter();
	void _LoadGameMsgTextContents();
	BOOL _bCheckCurrentBuildItemStatus();
	BOOL _bCheckBuildItemStatus();
	BOOL _bDecodeBuildItemContents();
	BOOL _bCheckBadWords(char * pMsg);
	void GetNpcName(short sType, char * pName);


#ifdef DEF_MAKE_ACCOUNT
	int m_iAgreeView;
	void _LoadAgreementTextContents(char cType);
	void UpdateScreen_OnAgreement();
	void UpdateScreen_OnCreateNewAccount();
#endif


	void UseShortCut( int num );
	void UpdateScreen();
	void UpdateScreen_OnMainMenu();
	void UpdateScreen_OnGame();
	void UpdateScreen_OnConnecting();
	void UpdateScreen_OnWaitInitData();
	void MakeSprite( char* FileName, short sStart, short sCount, bool bAlphaEffect = TRUE);
	void MakeTileSpr( char* FileName, short sStart, short sCount, bool bAlphaEffect = TRUE);
	void MakeEffectSpr( char* FileName, short sStart, short sCount, bool bAlphaEffect = TRUE);
	void UpdateScreen_OnLoading(bool bActive);
	void UpdateScreen_OnConnectionLost();
	void UpdateScreen_OnLogin();
	void UpdateScreen_OnMsg();
	void UpdateScreen_OnQuit();
	void UpdateScreen_OnQueryForceLogin();
	void UpdateScreen_OnQueryDeleteCharacter();
	void UpdateScreen_OnWaitingResponse();
	void UpdateScreen_OnCreateNewCharacter();
	void UpdateScreen_OnSelectCharacter();
	void UpdateScreen_OnLogResMsg();
	void UpdateScreen_OnSelectCharacter(short sX, short sY, short msX, short msY, BOOL bIgnoreFocus = FALSE);
	void UpdateScreen_OnChangePassword();
	void UpdateScreen_OnLoading_Progress();
	void UpdateScreen_OnVersionNotMatch();
	void NpcTalkHandler(char * pData);
	int  _iGetWeaponSkillType();
	void SetCameraShakingEffect(short sDist, int iMul = 0);
	BOOL bDlgBoxPress_SkillDlg(short msX, short msY);
	BOOL bDlgBoxPress_Inventory(short msX, short msY);
	BOOL bDlgBoxPress_Character(short msX, short msY);
	void ClearSkillUsingStatus();
	BOOL bCheckItemOperationEnabled(char cItemID);
	void _DrawThunderEffect(int sX, int sY, int dX, int dY, int rX, int rY, char cType);
	void DrawLine2(int x0, int y0, int x1, int y1, int iR, int iG, int iB);
	void DrawLine(int x0, int y0, int x1, int y1, int iR, int iG, int iB);
	void SetWhetherStatus(BOOL bStart, char cType);
	void WhetherObjectFrameCounter();
	void DrawWhetherEffects();
	BOOL bCheckExID(char * pName);
	BOOL bCheckLocalChatCommand(char * pMsg);
	char GetOfficialMapName(char * pMapName, char * pName);
	int iGetLevelExp(int iLevel);
	int _iCalcTotalWeight();
	void DrawVersion(BOOL bAuthor = FALSE);
	BOOL _bIsItemOnHand();
	void DynamicObjectHandler(char * pData);
	BOOL _bCheckItemByType(char cType);
	void _DrawBlackRect(int iSize);
	void DrawNpcName(   short sX, short sY, short sOwnerType, int iStatus);
	void DrawObjectName(short sX, short sY, char * pName, int iStatus);
	void PlaySound(char cType, int iNum, int iDist, long lPan = 0);
	void _RemoveChatMsgListByObjectID(int iObjectID);
	void _LoadTextDlgContents(int cType);
	int  _iLoadTextDlgContents2(int iType);
	void DrawChatMsgs(short sX, short sY, short dX, short dY);
	void RequestFullObjectData(WORD wObjectID);
	BOOL bInitSkillCfgList();
	BOOL bCheckImportantFile();
	void DlbBoxDoubleClick_Inventory(short msX, short msY);
	void DlbBoxDoubleClick_Character(short msX, short msY);
	void DlbBoxDoubleClick_GuideMap(short msX, short msY);
	BOOL _bCheckDlgBoxDoubleClick(short msX, short msY);
	void EraseItem(char cItemID);
	void RetrieveItemHandler(char * pData);
	void CivilRightAdmissionHandler(char * pData);
	void _Draw_CharacterBody(short sX, short sY, short sType);
	void ClearContents_OnSelectCharacter();
	void ClearContents_OnCreateNewAccount();
	void _Draw_UpdateScreen_OnCreateNewAccount();
	BOOL _bDraw_OnCreateNewCharacter(char * pName, short msX, short msY, int iPoint);
	BOOL _bGetIsStringIsNumber(char * pStr);
	BOOL bInitMagicCfgList();
	BOOL __bDecodeContentsAndBuildItemForSaleList(char * pBuffer);
	void _LoadShopMenuContents(char cType);
	void PutChatScrollList(char * pMsg, char cType);
	void RequestTeleportAndWaitData();
	void DrawEffectLights();
	void PointCommandHandler(int indexX, int indexY, char cItemID = -1);
	void DrawEffects();
	void bAddNewEffect(short sType, int sX, int sY, int dX, int dY, char cStartFrame, int iV1 = 1);
	void AddEventList(char * pTxt, char cColor = 0, BOOL bDupAllow = TRUE);
	void ShowEventList(DWORD dwTime);
	void SetItemCount(char * pItemName, DWORD dwCount);
	void _ShiftGuildOperationList();
	void _PutGuildOperationList(char * pName, char cOpMode);
	void DisbandGuildResponseHandler(char * pData);
	void InitPlayerCharacteristics(char * pData);
	void CreateNewGuildResponseHandler(char * pData);
	void _GetHairColorRGB(int iColorType , int * pR, int * pG, int * pB);
	void InitGameSettings();
	void CommonEventHandler(char * pData);
	BOOL _bCheckDraggingItemRelease(short msX, short msY);
	void _SetItemOrder(char cWhere, char cItemID);
	int iGetTopDialogBoxIndex();
	void DisableDialogBox(int iBoxID);
	void EnableDialogBox(int iBoxID, int cType, int sV1, int sV2, char * pString = NULL);
	void InitItemList(char * pData);
	int _iCheckDlgBoxFocus(short msX, short msY, char cButtonSide);
	void GetPlayerTurn();
	BOOL __fastcall DrawObject_OnDead(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnDying(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnMagic(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnAttack(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnAttackMove(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnStop(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnMove_ForMenu(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnMove(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnDamageMove(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnRun(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnDamage(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnGetItem(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL bEffectFrameCounter();
	void ClearGuildNameList();
	void DrawBackground(short sDivX, short sModX, short sDivY, short sModY);
	void DrawChatMsgBox(short sX, short sY, int iChatIndex, BOOL bIsPreDC);
	void ReleaseTimeoverChatMsg();
	void ChatMsgHandler(char * pData);
	void ReleaseUnusedSprites();
	BOOL bReadIp();
	void OnKeyUp(WPARAM wParam);
	void OnSysKeyDown(WPARAM wParam);
	void OnSysKeyUp(WPARAM wParam);
	void ChangeGameMode(char cMode);
	void PutString(int iX, int iY, char * pString, COLORREF color);
	void PutString(int iX, int iY, char * pString, COLORREF color, BOOL bHide, char cBGtype, BOOL bIsPreDC = FALSE);
	void PutString2(int iX, int iY, char * pString, short sR, short sG, short sB);
	void PutAlignedString(int iX1, int iX2, int iY, char * pString, short sR = 0, short sG = 0, short sB = 0);
	void PutString_SprFont(int iX, int iY, char * pStr, short sR, short sG, short sB);
	void PutString_SprFont2(int iX, int iY, char * pStr, short sR, short sG, short sB);
	void PutString_SprFont3(int iX, int iY, char * pStr, short sR, short sG, short sB, BOOL bTrans = FALSE, int iType = 0);
	void PutString_SprNum(int iX, int iY, char * pStr, short sR, short sG, short sB);
	void LogRecvMsgHandler(char * pData);
	void LogResponseHandler(char * pData);
	void OnLogSocketEvent(WPARAM wParam, LPARAM lParam);
	void OnTimer();
	void LogEventHandler(char * pData);
	void _ReadMapData(short sPivotX, short sPivotY, char * pData);
	void MotionEventHandler(char * pData);
	void InitDataResponseHandler(char * pData);
	void InitPlayerResponseHandler(char * pData);
	void ConnectionEstablishHandler(char cWhere);
	void MotionResponseHandler(char * pData);
	void GameRecvMsgHandler(DWORD dwMsgSize, char * pData);
	void DrawObjects(short sPivotX, short sPivotY, short sDivX, short sDivY, short sModX, short sModY, short msX, short msY);
	BOOL bSendCommand(DWORD dwMsgID, WORD wCommand, char cDir, int iV1, int iV2, int iV3, char * pString, int iV4 = NULL); // v1.4
	char cGetNextMoveDir(short sX, short sY, short dstX, short dstY, BOOL bMoveCheck = FALSE, BOOL bMIM = FALSE);
	void RestoreSprites();
	void CommandProcessor(short msX, short msY, short indexX, short indexY, char cLB, char cRB);
	void OnGameSocketEvent(WPARAM wParam, LPARAM lParam);
	void CalcViewPoint();
	void OnKeyDown(WPARAM wParam);
	void Quit();
	BOOL bInit(HWND hWnd, HINSTANCE hInst, char * pCmdLine);

	void ReserveFightzoneResponseHandler(char * pData);
	int _iGetAttackType();
	BOOL __bDecodeBuildItemContents(char * pBuffer);
	int _iGetBankItemCount();
	int _iGetTotalItemNum();
	LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);
	void GoHomepage();
	void StartBGM();

#ifdef DEF_EQUILIBRIUM_PROJECT
	// Snoopy: added MP3 support
	void LoopBGM();
	void StopBGM();
	void PauseBGM();
	void ResumeBGM();
	void SetBGMVolume();
#endif

#ifdef DEF_ANTI_HACK
	bool CheckProcesses();
	void DoCRC();
#endif
	//Snoopy: added function:
	void DebugLog(char * cStr);
	BOOL bReadLoginConfigFile(char * cFn);
	int bHasHeroSet( short Appr3, short Appr4, char OwnerType);
	void ShowHeldenianVictory(short sSide);
	void DrawDialogBox_Resurect(short msX, short msY);
	void DlgBoxClick_Resurect(short msX, short msY);
	void DrawDialogBox_CMDHallMenu(short msX, short msY);
	void DlgBoxClick_CMDHallMenu(short msX, short msY);
	void ResponseHeldenianTeleportList(char *pData);
	void DKGlare(int iWeaponColor, int iWeaponIndex, int *iWeaponGlare);
	void DrawDruncncity();
	void DlgBoxClick_ConfirmExchange(short msX, short msY);
	void Abaddon_corpse(int sX, int sY);
	void DrawAngel(int iSprite, short sX, short sY, char cFrame, DWORD dwTime);


	BOOL _ItemDropHistory(char * ItemName);
	CGame();
	virtual ~CGame();

	struct {
		short sX;
		short sY;
		short sCursorFrame;
		char  cPrevStatus;
		char  cSelectedObjectType;
		short sSelectedObjectID;
		short sPrevX, sPrevY, sDistX, sDistY;
		DWORD dwSelectClickTime;
		short sClickX, sClickY;
	} m_stMCursor;

	struct {
		int   sV1, sV2, sV3, sV4, sV5, sV6, sV7, sV8, sV9, sV10, sV11, sV12, sV13, sV14; // v1.4 short
		DWORD dwV1, dwV2, dwT1;
		BOOL  bFlag;
		short sX, sY;
		short sSizeX, sSizeY;
		short sView;
		char  cStr[32], cStr2[32], cStr3[32], cStr4[32];
		char  cMode;
		BOOL  bIsScrollSelected;
	} m_stDialogBoxInfo[61];	 // Snoopy passé à 61 (origine 41, Alastor 60), j'ai mis +20 car plus pratique.
	char m_cDialogBoxOrder[61];
	CInt m_bIsDialogEnabled[61];//was BOOL
//Snoopy=>>>>>>>>>>>>>>>>>>>>>
	struct {
		int   sV1, sV2, sV3, sV4, sV5, sV6, sV7, sItemID;
		DWORD dwV1;
		char  cStr1[32], cStr2[32];
	} m_stDialogBoxExchangeInfo[8];
//Snoopy end<<<<<<<<<<<<<<<<<<
	struct {
		int iIndex;
		int iAmount;
	} m_stSellItemList[DEF_MAXSELLLIST];

	struct {
		char cName[22];
		char cOpMode;
	} m_stGuildOpList[100];

	struct {
		DWORD dwTime;
		char  cColor;
		char  cTxt[96];
	} m_stEventHistory[6];

	struct {
		DWORD dwTime;
		char  cColor;
		char  cTxt[96];
	} m_stEventHistory2[6];

	struct {
		short sX, sY, sBX;
		char cStep;
	} m_stWhetherObject[DEF_MAXWHETHEROBJECTS];

	struct {
		BOOL bIsQuestCompleted;
		short sWho, sQuestType, sContribution, sTargetType, sTargetCount, sX, sY, sRange;
		short sCurrentCount; // by Snoopy
		char cTargetName[22];
	} m_stQuest;

	struct {
		char cStatus;
		char cName[12];
	} m_stPartyMember[DEF_MAXPARTYMEMBERS];

	struct {
		short sX, sY;
		char cType;
		char cSide;
	} m_stCrusadeStructureInfo[DEF_MAXCRUSADESTRUCTURES];

	struct {
		char cName[12];
	} m_stPartyMemberNameList[DEF_MAXPARTYMEMBERS+1];

	// v2.171 2002-6-14
	struct {
		DWORD dwRefTime;
		int iGuildRank;
		char cCharName[12];
		char cGuildName[24];
	} m_stGuildName[DEF_MAXGUILDNAMES];

	struct {
		int iIndex;
		char mapname[12];
		int iX;
		int iY;
		int iCost;
	} m_stTeleportList[20];

	class YWSound m_DSound;
	class CSoundBuffer *	m_pCSound[DEF_MAXSOUNDEFFECTS];
	class CSoundBuffer *	m_pMSound[DEF_MAXSOUNDEFFECTS];
	class CSoundBuffer *	m_pESound[DEF_MAXSOUNDEFFECTS];
	class CSoundBuffer *    m_pBGM;
	class DXC_ddraw  m_DDraw;
	class DXC_dinput m_DInput;
	class CMisc      m_Misc;
	class CSprite  * m_pSprite[DEF_MAXSPRITES];
	class CSprite  * m_pTileSpr[DEF_MAXTILES];
	class CSprite  * m_pEffectSpr[DEF_MAXEFFECTSPR];
	class CMapData * m_pMapData;
	class XSocket * m_pGSock;
	class XSocket * m_pLSock;
	class CMsg    * m_pChatMsgList[DEF_MAXCHATMSGS];
	class CMsg    * m_pChatScrollList[DEF_MAXCHATSCROLLMSGS];
	class CMsg    * m_pWhisperMsg[DEF_MAXWHISPERMSG];
	class CEffect * m_pEffectList[DEF_MAXEFFECTS];
	class CItem   * m_pItemList[DEF_MAXITEMS];
	class CItem   * m_pBankList[DEF_MAXBANKITEMS];
	class CMagic * m_pMagicCfgList[DEF_MAXMAGICTYPE];
	class CSkill * m_pSkillCfgList[DEF_MAXSKILLTYPE];
	class CMsg * m_pMsgTextList[DEF_TEXTDLGMAXLINES];
	class CMsg * m_pMsgTextList2[DEF_TEXTDLGMAXLINES];
	class CMsg * m_pAgreeMsgTextList[DEF_TEXTDLGMAXLINES];
	class CMsg * m_pExID;
	class CBuildItem * m_pBuildItemList[DEF_MAXBUILDITEMS];
	class CBuildItem * m_pDispBuildItemList[DEF_MAXBUILDITEMS];


	class CGameMonitor * m_pCGameMonitor;
	class CItem * m_pItemForSaleList[DEF_MAXMENUITEMS];
	class CCharInfo * m_pCharList[4];
	class CMsg * m_pGameMsgList[DEF_MAXGAMEMSGS];
	class CItemName * m_pItemNameList[DEF_MAXITEMNAMES];
	class CCurse m_curse;

	char * m_pInputBuffer;

	DWORD G_dwGlobalTime;
	DWORD m_dwCommandTime; //v2.15 SpeedHack
	DWORD m_dwConnectMode;
	DWORD m_dwTime;
	DWORD m_dwCurTime;
	DWORD m_dwCheckConnTime, m_dwCheckSprTime, m_dwCheckChatTime;
	DWORD m_dwDialogCloseTime;
	CInt  m_dwLogOutCountTime;//was DWORD
	DWORD m_dwRestartCountTime;
	DWORD m_dwWOFtime; //v1.4
	DWORD m_dwObserverCamTime;
	DWORD m_dwDamagedTime;
	DWORD m_dwSpecialAbilitySettingTime;
	DWORD m_dwCommanderCommandRequestedTime;
	DWORD m_dwTopMsgTime;
	DWORD m_dwEnvEffectTime;

	//v2.2
	DWORD m_dwMonsterEventTime;
	short m_sMonsterID;
	short m_sEventX, m_sEventY;


	//v2.183 Hunter Mode;
	BOOL m_bHunter;
	BOOL m_bAresden;
	BOOL m_bCitizen;
	//v2.183 Hunter Mode;

	BOOL m_bZoomMap;
	BOOL m_bIsProgramActive;
	CInt m_bCommandAvailable;//was BOOL
	BOOL m_bSoundFlag;
	BOOL m_bSoundStat, m_bMusicStat; // On/Off
	CInt m_bIsItemEquipped[DEF_MAXITEMS];//was BOOL
	CInt m_bIsItemDisabled[DEF_MAXITEMS];//was BOOL
	CInt m_bIsGetPointingMode;//was BOOL
	BOOL m_bEnterPressed, m_bEscPressed, m_bCtrlPressed, m_bRunningMode, m_bShiftPressed;

	BOOL m_bDialogTrans;
	BOOL m_bIsCombatMode;
	BOOL m_bIsSafeAttackMode;
	CInt m_bSkillUsingStatus;//was BOOL
	CInt m_bItemUsingStatus;//was BOOL
	BOOL m_bIsWhetherEffect;
	BOOL m_bSuperAttackMode;	//
	BOOL m_bIsObserverMode, m_bIsObserverCommanded;
	CInt m_bIsPoisoned;//was BOOL
	BOOL m_bIsFirstConn;
	BOOL m_bIsConfusion;
	BOOL m_bIsRedrawPDBGS;
	BOOL m_bDrawFlagDir;
	BOOL m_bIsCrusadeMode;
	CInt m_bIsSpecialAbilityEnabled;//was BOOL
	BOOL m_bInputStatus;
	BOOL m_bToggleScreen;
	BOOL m_bIsSpecial;

	BOOL m_bIsF1HelpWindowEnabled;
	CInt m_bIsTeleportRequested;//was BOOL
	BOOL m_bIsPrevMoveBlocked;
	BOOL m_bIsHideLocalCursor;

	CInt m_bForceDisconn;//was BOOL
	BOOL m_bForceAttack;
	BOOL m_bParalyze;

	short m_sFrameCount;
	short m_sFPS;
	DWORD m_dwFPStime;
	BOOL  m_bShowFPS;

	int m_iFightzoneNumber;
	int m_iFightzoneNumberTemp;
	int m_iPlayerApprColor; // v1.4
	CInt m_iHP;//was int			// Hit Point
	CInt m_iMP;//was int			// Mana Point
	CInt m_iSP;//was int			// Staminar Point
	int m_iAC;						// Armour Class
	int m_iTHAC0;					// To Hit Armour Class 0

	int m_iLevel, m_iStr, m_iInt, m_iVit, m_iDex, m_iMag, m_iCharisma, m_iExp, m_iContribution;
	// Snoopy: Added Angels
	int m_iAngelicStr, m_iAngelicInt, m_iAngelicDex, m_iAngelicMag;

	int m_iEnemyKillCount;
	int m_iPKCount;
	int m_iRewardGold;
	int m_iGuildRank, m_iTotalGuildsMan;
	int m_iPointCommandType;
	int m_iTotalChar;
//	int m_iAccountStatus;
	short m_sMagicShortCut;
	int m_iLU_Point;
	int m_iCameraShakingDegree;
	int m_iSuperAttackLeft;
	int m_iAccntYear, m_iAccntMonth, m_iAccntDay;
	int m_iIpYear, m_iIpMonth, m_iIpDay;
	int m_iDownSkillIndex;

	int m_iIlusionOwnerH;
	int m_iApprColor_IE;
	int m_iInputX, m_iInputY;
	int m_iPDBGSdivX, m_iPDBGSdivY;			   // Pre-Draw Background Surface
	short m_sRecentShortCut;
	short m_sShortCut[6]; // Snoopy: 6 shortcuts
	int	m_iSpecialAbilityTimeLeftSec;
	int m_iDrawFlag;
	int m_iSpecialAbilityType;
	int m_iTimeLeftSecAccount, m_iTimeLeftSecIP;
	int m_iCrusadeDuty;
	int m_iLogServerPort;
	int m_iRating; //Rating

	int m_iPrevMoveX, m_iPrevMoveY;
	int m_iBlockYear, m_iBlockMonth, m_iBlockDay;
	unsigned char m_iTopMsgLastSec;
	int m_iConstructionPoint;
	int m_iWarContribution;
	int m_iConstructLocX, m_iConstructLocY;
	int m_iNetLagCount;
	int m_iTeleportLocX, m_iTeleportLocY;
	int m_iTotalPartyMember;
	int m_iPartyStatus;
	int m_iGizonItemUpgradeLeft;
	//int m_iFeedBackCardIndex; // removed by Snoopy

	short m_sItemEquipmentStatus[DEF_MAXITEMEQUIPPOS];
	short m_sPlayerX, m_sPlayerY;
	short m_sPlayerObjectID;
	short m_sPlayerType;
	short m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4;
	int m_iPlayerStatus;
	short m_sMCX, m_sMCY;
	short m_sCommX, m_sCommY;
	int   m_iCastingMagicType;
	short m_sDamageMove, m_sDamageMoveAmount;
	short m_sAppr1_IE, m_sAppr2_IE, m_sAppr3_IE, m_sAppr4_IE;
	int m_iStatus_IE;
	short m_sViewDstX, m_sViewDstY;
	short m_sViewPointX, m_sViewPointY;
	short m_sVDL_X, m_sVDL_Y;

	WORD m_wCommObjectID;
	WORD m_wEnterGameType;
	WORD m_wR[16], m_wG[16], m_wB[16];
	WORD m_wWR[16], m_wWG[16], m_wWB[16];

	unsigned char m_cInputMaxLen;
	char m_cEdit[4];
	char G_cTxt[128];
	char m_cGameModeCount;
	char m_cBGMmapName[12];
	char m_cItemOrder[DEF_MAXITEMS];
	char m_cAmountString[12];
	char m_cLogOutCount;
	char m_cRestartCount;
	char m_cGameMode;
	char m_cWhisperIndex;
	char m_cAccountName[12];
	char m_cAccountPassword[12];
	char m_cAccountAge[12];
	char m_cNewPassword[12];
	char m_cNewPassConfirm[12];
	char m_cAccountCountry[18];
	char m_cAccountSSN[32];
	char m_cEmailAddr[52];
	char m_cAccountQuiz[46];// Quiz
	char m_cAccountAnswer[22];
	char m_cPlayerName[12];
	char m_cPlayerDir;
	char m_cMsg[200];
	char m_cLocation[12];
	char m_cCurLocation[12];
   	char m_cGuildName[22];
	char m_cMCName[12];
	char m_cMapName[12];
	char m_cMapMessage[32];
	char m_cMapIndex;
	char m_cPlayerTurn;
	char m_cCommand;
	char m_cCurFocus, m_cMaxFocus;
	char m_cEnterCheck, m_cTabCheck, m_cLeftArrowCheck;
	char m_cArrowPressed;
	char m_cLogServerAddr[16];
	char m_cChatMsg[64];
	char m_cBackupChatMsg[64];
	char m_cGender, m_cSkinCol, m_cHairStyle, m_cHairCol, m_cUnderCol;
	char m_ccStr, m_ccVit, m_ccDex, m_ccInt, m_ccMag, m_ccChr;
	char m_cLU_Str, m_cLU_Vit, m_cLU_Dex, m_cLU_Int, m_cLU_Mag, m_cLU_Char;

	char m_cMagicMastery[DEF_MAXMAGICTYPE];
	unsigned char m_cSkillMastery[DEF_MAXSKILLTYPE]; // v1.4
	char m_cWorldServerName[32];
	char m_cDetailLevel;
	char m_cMenuDir, m_cMenuDirCnt, m_cMenuFrame;
	char m_cSoundVolume, m_cMusicVolume;
	char m_cWhetherEffectType;
	char m_cWhetherStatus;
	char m_cIlusionOwnerType;
	char m_cName_IE[12];
	char m_sViewDX, m_sViewDY;
	char m_cCommandCount;
	char m_cLoading;
	char m_cDiscount;

	char m_cStatusMapName[12];
	char m_cTopMsg[64];
	char m_cTeleportMapName[12];
	char m_cConstructMapName[12];
	char m_cGameServerName[22]; //  Gateway

	char m_cItemDrop[25][25];

	RECT m_rcPlayerRect, m_rcBodyRect;
	HWND m_hWnd;

	HANDLE m_hPakFile;

	BOOL m_bWhisper;
	BOOL m_bShout;

	BOOL m_bItemDrop;
    int  m_iItemDropCnt;

	// Snoopy: Apocalypse Gate
	char m_cGateMapName[12];
	int  m_iGatePositX, m_iGatePositY;
	int m_iHeldenianAresdenLeftTower;
	int m_iHeldenianElvineLeftTower;
	int m_iHeldenianAresdenFlags;
	int m_iHeldenianElvineFlags;
	BOOL m_bIllusionMVT;
	int m_iGameServerMode;
	BOOL m_bIsXmas;
	BOOL m_bUsingSlate;
	BOOL m_bIsHeldenianMode;
	BOOL m_bIsHeldenianMap;


	//Snoopy: Avatar
	BOOL m_bIsAvatarMode;
	BOOL m_bIsAvatarMessenger;

	//Snoopy: Crafting
	//BOOL _bDecodeCraftItemContents();
	//BOOL __bDecodeCraftItemContents(char *pBuffer);
	//BOOL _bCheckCraftItemStatus();
	//BOOL _bCheckCurrentCraftItemStatus();

	class CBuildItem * m_pCraftItemList[DEF_MAXBUILDITEMS];
	class CBuildItem * m_pDispCraftItemList[DEF_MAXBUILDITEMS];
	int   m_iContributionPrice;

	char m_cTakeHeroItemName[100]; //Drajwer - hero item str


	//Snoopy: CRC32
#ifdef DEF_ANTI_HACK
	DWORD	m_dwCRC32;
	WORD	m_wCRC16_1;
	WORD	m_wCRC16_2;
	BOOL	m_bUseCRC_2;
	int		m_iMangler;
	class   CRCdemo  m_CRCdemo;

	BOOL m_bHackMoveBlocked;
#endif

#ifdef DEF_EQUILIBRIUM_PROJECT
	BOOL m_bFullParalyze;// Add by Snoopy for a lvl 20 para spell that prevents even casting turning, hiting, using item
	bool m_bVK_OEM_7Pressed;
#endif


};

#endif // !defined(AFX_GAME_H__0089D9E3_74E6_11D2_A8E6_00001C7030A6__INCLUDED_)
