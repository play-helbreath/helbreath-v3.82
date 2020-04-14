// Npc.h: interface for the CNpc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPC_H__6F7A5C80_A709_11D2_B143_00001C7030A6__INCLUDED_)
#define AFX_NPC_H__6F7A5C80_A709_11D2_B143_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <windows.h>
#include "Magic.h"

#define DEF_MAXWAYPOINTS			10

#define DEF_MOVETYPE_STOP			0		// 정지해 있는다. 초기화된 NPC의 기본 행동.
#define DEF_MOVETYPE_SEQWAYPOINT	1		// 이동경로를 순차적으로 이동. 맨 마지막 이동경로에서 해당 행동을 계속한다.
#define DEF_MOVETYPE_RANDOMWAYPOINT	2		// 이동경로를 랜덤하게 선택하여 움직인다.
#define DEF_MOVETYPE_FOLLOW			3		// 특정 대상을 따라 움직인다. 
#define DEF_MOVETYPE_RANDOMAREA		4		// 지정된 영역 안에서 랜덤한 곳으로 움직인다.
#define DEF_MOVETYPE_RANDOM			5		// 맵 내의 아무영역으로나 움직인다.
#define DEF_MOVETYPE_GUARD			6		// 처음 생성될 당시의 위치에 정지해 있으나 목표물 발견시는 추격한다.

#define DEF_BEHAVIOR_STOP			0
#define DEF_BEHAVIOR_MOVE			1
#define DEF_BEHAVIOR_ATTACK			2
#define DEF_BEHAVIOR_FLEE			3
#define DEF_BEHAVIOR_DEAD			4


#define DEF_NBE_MOBS_BEFORE_BOSS	20000

class CNpc  
{
public:
	CNpc(char * pName5);
	virtual ~CNpc();

	// Auras
	char m_pMagicConfigList[100];

	char  m_cNpcName[21];	// Name of the npc type

	char  m_cName[6];		// Unique name of this npc 
	char  m_cMapIndex;
	short m_sX, m_sY;
	short m_dX, m_dY;
	short m_vX, m_vY;
	int   m_tmp_iError;
	RECT  m_rcRandomArea;	// MOVETYPE_RANDOMAREA일때 영역좌표

	char  m_cDir;
	char  m_cAction;
	char  m_cTurn;

	short m_sType;
	short m_sOriginalType;
	short m_sAppr2;
	int	  m_iStatus;

	DWORD m_dwTime;
	DWORD m_dwActionTime;
	DWORD m_dwHPupTime, m_dwMPupTime;
	DWORD m_dwDeadTime, m_dwRegenTime;

	int  m_iHP;						// Hit Point 
	int  m_iExp;                    // 죽였을 경우 얻는 경험치. ExpDice에 의해 결정된다.

	int  m_iHitDice;				// 몬스터의 Hit Dice. 이것에 의해 HP가 결정된다.
	int  m_iDefenseRatio;			// Defense Ratio
	int  m_iHitRatio;				// HitRatio
	int  m_iMagicHitRatio;			// v1.4 마법 공격 Ratio
	int  m_iMinBravery;			    // 최소 용감치 
	int  m_iExpDiceMin;
	int	 m_iExpDiceMax;
	int  m_iGoldDiceMin;
	int  m_iGoldDiceMax;

	char m_cSide;					// NPC가 속한 팀 
	//SNOOPY: Added this here for Taming Skill
	char m_cOriginalSide;			// NPC
	DWORD m_dwTamingTime;
	char m_cActionLimit;            // 이 값이 1이면 Move만 가능하며 죽지도 않는다.  이 값이 2면 움직이지도 않으며 죽지도 않는다. 3이면 Dummy다. 맞는 역할, 
	                                // 4면 에너지 스피어, 5면 건축물   

	char m_cSize;					// 0: Small-Medium 1: Large
	char m_cAttackDiceThrow;		// 공격치 주사위 던지는 회수 
	char m_cAttackDiceRange;		// 공격치 주사위 범위 
	char m_cAttackBonus;			// 공격 보너스 
	char m_cBravery;				// NPC의 용감도 
	char m_cResistMagic;			// 마법 저항 
	char m_cMagicLevel;				// 마법 레벨 
	char m_cDayOfWeekLimit;		    // 생성시 날짜 제한 
	char m_cChatMsgPresence;		// 연결된 Chat Msg 존재유무 
	int  m_iMana;                   // 최대값은 MagicLevel*30
	int  m_iMaxMana;				// v1.4 새로 추가된 것들.
																    
	char  m_cMoveType;				// NPC의 이동경로 방식 
	char  m_cBehavior;				// NPC의 행동 
	short m_sBehaviorTurnCount;		// 행동 카운트 
	char  m_cTargetSearchRange;		// NPC공격목표 검색 범위 

	int   m_iFollowOwnerIndex;		// Who follows this npc (master or summoner)
	char  m_cFollowOwnerType;		// NPC or Player
	char  m_cFollowOwnerCharName[11]; // Name of the player oawner
	BOOL  m_bIsSummoned;            // Player summon (Spell, potion, scroll, crusade mob... -> No drop, no Quest, etc
	DWORD m_dwSummonedTime;			// 
	DWORD m_dwSummonWaitTime;		// 
	BOOL  m_bIsUnsummoned;			// Not killed by player -> No drop, or 2nd drop.

	int   m_iTargetIndex;			// Who is attacked by npc
	char  m_cTargetType;			// NPC or Player
	char  m_cCurWaypoint;			// 현재 이동위치 
	char  m_cTotalWaypoint;			// 총 이동위치 갯수 

	int   m_iSpotMobIndex;			// spot-mob-generator에서 만들어졌다면 인덱스를 저장 
	int   m_iWayPointIndex[DEF_MAXWAYPOINTS+1];
	char  m_cMagicEffectStatus[DEF_MAXMAGICEFFECTS];

	BOOL  m_bIsPermAttackMode;		// Permanent Attack
   	int   m_iNoDieRemainExp;		// 죽지 않고 명중시에 얻을 수 있는 경험치 
	int   m_iAttackStrategy; 		// 전투 교리 인공지능 타입  
	int   m_iAILevel;				// 지능 레벨 

	int   m_iAttackRange;			// 공격 범위 1이상이면 원거리 공격이 가능하다는 것 
	/*
		AI-Level 
			1: 보통 행동 
			2: 에너지가 가장 낮은 목표물을 추적 
			3: 마법 보호중인 목표물 마법 공격대상에서 제외 
	*/
	int   m_iAttackCount;			// 연속 공격 동작 횟수 카운트 
	BOOL  m_bIsKilled;

	int   m_iLastDamage;			// 마지막 죽기 전에 얻은 대미지. 대미지가 너무 크면 연금술 재료가 떨어지지 않는다.
	int   m_iSummonControlMode;		// 소환몹 조정 모드: 0이면 Free, 1 Hold 2 Tgt 
	char  m_cAttribute;				// 마법 속성:  땅 1 하늘 2 불 3 물 4  
	int   m_iAbsDamage;				// 양수면 마법 대미지 절감률, 음수면 물리 대미지 절감률 

//	int   m_iItemRatio;				// 특수 아이템 확률 
//	int   m_iAssignedItem;			// 할당된 아이템 

	int  m_iNpcBossType;			// 1 means Boss . Boss have "eyes in the back" (no 1/2 def ratio in the back)
									// Not 0, or -1 means "eyes in the back"       (no 1/2 def ratio in the back)
	char  m_cSpecialAbility;		// See below: 				
	/*
case 0: break;
case 1:  "Penetrating Invisibility"
case 2:  "Breaking Magic Protection"
case 3:  "Absorbing Physical Damage"
case 4:  "Absorbing Magical Damage"
case 5:  "Poisonous"
case 6:  "Extremely Poisonous"
case 7:  "Explosive"
case 8:  "Hi-Explosive" 
case 9:  "Swift"		// Fast moving, higher def and to Hit
case 10: "Mighty"		// Higher HPts, dmg, toHit
case 11: "Shaman"		// Cast powerfull spells
case 12: "Crippled"		// Moving slow, easyer to kill
// Negative value means a Boss type mob
									*/

	int	  m_iBuildCount;			// Stored on npc.cfg as m_iMinBravery
	int   m_iManaStock;				// 그랜드 매직 제네레이터의 경우 마나축적량 
	BOOL  m_bIsMaster;				// 마스터 몹인지의 여부 
	int   m_iGuildGUID;				// 전쟁용 유니트인 경우 소환자의 길드 아이디가 입력된다.
	
	char m_cCropType;
	char m_cCropSkill;

	int   m_iV1;
	char m_cArea;
	//int m_iNpcItemType;
	//int m_iNpcItemMax;
	// SNOOPY: to have ncp resisting poison or not
	char m_cPoisonResistance;
	char m_iPoisonLevel;	
};

#endif // !defined(AFX_NPC_H__6F7A5C80_A709_11D2_B143_00001C7030A6__INCLUDED_)
