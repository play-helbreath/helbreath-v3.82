// Map.h: interface for the CMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_H__12609160_8060_11D2_A8E6_00001C7030A6__INCLUDED_)
#define AFX_MAP_H__12609160_8060_11D2_A8E6_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>
#include "OccupyFlag.h"
#include "Tile.h"
#include "StrategicPoint.h"


#define DEF_OWNERTYPE_PLAYER			1
#define DEF_OWNERTYPE_NPC				2
#define DEF_OWNERTYPE_PLAYER_INDIRECT	3
#define DEF_OWNERTYPE_PLAYER_WAITING	8 // Snoopy: added to wait for the player connecting again...
#define DEF_OWNERTYPE_PLAYER_FREE		9 // Snoopy: added for every player to take over this summon

// for Client Data
#define DEF_MAPDATASIZEX		30
#define DEF_MAPDATASIZEY		25
#define DEF_MAXTELEPORTLOC		200
#define DEF_MAXWAYPOINTCFG		200
#define DEF_MAXMGAR				50
#define DEF_MAXNMR				50
#define DEF_MAXSPOTMOBGENERATOR	100
#define DEF_MAXFISHPOINT		200
#define DEF_MAXITEMEVENTS		200
#define DEF_MAXMINERALPOINT		200
#define DEF_MAXHELDENIANDOOR	10  // 4 exists at HRampart
#define DEF_MAXOCCUPYFLAG		201 //by Snoopy thats enougth! (n�1..200) //3001
#define	DEF_MAXINITIALPOINT		20
#define DEF_MAXAGRICULTURE		200
#define DEF_MAXDYNAMICGATES		10
#define DEF_MAXHELDENIANTOWER	200

#include "GlobalDef.h"
#include <windows.h>
#include "Game.h"
#include "StrTok.h"
#include "TeleportLoc.h"

#define DEF_MAPTYPE_NORMAL				0
#define DEF_MAPTYPE_NOPENALTY_NOREWARD	1
// SNOOPY: Added new types for events
#define DEF_MAPTYPE_NOPCDROP			2
#define DEF_MAPTYPE_NOPCDROP_NOPK		3



#define DEF_MAXENERGYSPHERES			10
#define DEF_MAXSTRATEGICPOINTS			200
#define DEF_MAXSECTORS					60
#define DEF_MAXSTRIKEPOINTS				20




class CMap  
{
public:
	
	BOOL bCheckFlySpaceAvailable(short sX, char sY, char cDir, short sOwner);
	BOOL bGetIsFarm(short tX, short tY);
	void RestoreStrikePoints();
	BOOL bRemoveCrusadeStructureInfo(short sX, short sY);
	BOOL bAddCrusadeStructureInfo(char cType, short sX, short sY, char cSide);
	int iGetAttribute(int dX, int dY, int iBitMask);
	void _SetupNoAttackArea();
	void ClearTempSectorInfo();
	void ClearSectorInfo();
	int iRegisterOccupyFlag(int dX, int dY, int iSide, int iEKNum, int iDOI);
	int  iCheckItem(short sX, short sY);
	void SetTempMoveAllowedFlag(int dX, int dY, BOOL bFlag);
	int iAnalyze(char cType, int *pX, int *pY, int * pV1, int *pV2, int * pV3);
	BOOL bGetIsWater(short dX, short dY);
	void GetDeadOwner(short * pOwner, char * pOwnerClass, short sX, short sY);
	BOOL bGetIsMoveAllowedTile(short dX, short dY);
	//Snoopy:
	BOOL bGetIsStayAllowedTile(short dX, short dY);
	void SetStayAllowedFlag(int dX, int dY, BOOL bFlag);

	void SetNamingValueEmpty(int iValue);
	int iGetEmptyNamingValue();
	BOOL bGetDynamicObject(short sX, short sY, short * pType, DWORD * pRegisterTime, int * pIndex = NULL);
	void SetDynamicObject(WORD wID, short sType, short sX, short sY, DWORD dwRegisterTime);
	BOOL bGetIsTeleport(short dX, short dY);
	BOOL bSearchTeleportDest(int sX, int sY, char * pMapName, int * pDx, int * pDy, char * pDir);
	BOOL bInit(char * pName);
	BOOL bIsValidLoc(short sX, short sY);
	class CItem * pGetItem(short sX, short sY, short * pRemainItemSprite, short * pRemainItemSpriteFrame, char * pRemainItemColor);
	BOOL pCheckBombItem(short sX, short sY);
	BOOL bSetItem(short sX, short sY, class CItem * pItem);
	void ClearDeadOwner(short sX, short sY);
	void ClearOwner(int iDebugCode, short sOwnerH, char cOwnerType, short sX, short sY);
	BOOL bGetMoveable(short dX, short dY, short * pDOtype = NULL, short * pTopItem = NULL);
	void GetOwner(short * pOwner, char * pOwnerClass, short sX, short sY);
	void SetOwner(short sOwner, char cOwnerClass, short sX, short sY);
	void SetDeadOwner(short sOwner, char cOwnerClass, short sX, short sY);
	BOOL bRemoveCropsTotalSum();
	BOOL bAddCropsTotalSum();
	//void SetBigOwner(short sOwner, char cOwnerClass, short sX, short sY, char cArea);

	CMap(class CGame * pGame);
	virtual ~CMap();

	class CTile * m_pTile;
	class CGame * m_pGame;
	char  m_cName[11];
	char  m_cLocationName[11];
	short m_sSizeX, m_sSizeY, m_sTileDataSize;
	class CTeleportLoc * m_pTeleportLoc[DEF_MAXTELEPORTLOC];
	
	//short m_sInitialPointX, m_sInitialPointY;
	POINT m_pInitialPoint[DEF_MAXINITIALPOINT];

	BOOL  m_bNamingValueUsingStatus[1000]; // 0~999

	// Snoopy: Changed m_bRandomMobGenerator to int
	// 0 means no mobs (still used for zerking spot mobs)
	// Above 1 value will be used to remove npc every 5 minutes 
	// (5 minutes is Special event time)
	int   m_iRandomMobGeneratorSA;
	char  m_cRandomMobGeneratorLevel;
	int	  m_iMapLevel;
	int   m_iTotalActiveObject;
	int   m_iMaximumObject;
	// SNOOPY: Added this for GM reverse to standard Object numbers
	int   m_iMaximumObjectDefault;
	bool  m_bHpMpSpPopoEnabled; // TRUE by default

	char  m_cType;				// 맵의 형식. 0이면 보통. 1이면 공격행위가 범죄가 아니다.

	BOOL  m_bIsFixedDayMode;	// 항상 주간모드인지: 건물 내부 등 

	struct {		    
		BOOL bDefined;
		char cType;				// 1:RANDOMAREA   2:RANDOMWAYPOINT 3: sequencial Waypoints 
								// 4+: Attracting spawns      -1 & below: moving all arround		
		char cWaypoint[10];     // RANDOMWAYPOINT 등
		RECT rcRect;			// RANDOMAREA발생의 경우 		
		int  iTotalActiveMob;
		int  iMobType;
		int  iMaxMobs;
		int  iCurMobs;
		int  iKilledMobs;
		
	} m_stSpotMobGenerator[DEF_MAXSPOTMOBGENERATOR];
	BOOL  m_bHasMagicSMG;

	POINT m_WaypointList[DEF_MAXWAYPOINTCFG];
	RECT  m_rcMobGenAvoidRect[DEF_MAXMGAR];
	RECT  m_rcNoAttackRect[DEF_MAXNMR];

	POINT m_FishPointList[DEF_MAXFISHPOINT];
	int   m_iTotalFishPoint, m_iMaxFish, m_iCurFish;
	
	int	  m_iApocalypseMobGenType, m_iApocalypseBossMobNpcID;
	
	//short m_sApocalypseBossMobRectX1, m_sApocalypseBossMobRectY1, m_sApocalypseBossMobRectX2, m_sApocalypseBossMobRectY2;
	//Snoopy: tranformed to RECT
	RECT	m_sApocalypseBossMobRect;

	char  m_cDynamicGateType;
	short m_sDynamicGateCoordRectX1, m_sDynamicGateCoordRectY1, m_sDynamicGateCoordRectX2, m_sDynamicGateCoordRectY2;
	char  m_cDynamicGateCoordDestMap[11];
	short m_sDynamicGateCoordTgtX, m_sDynamicGateCoordTgtY;
	BOOL  m_bIsCitizenLimit;
//	short m_sHeldenianTowerType, m_sHeldenianTowerXPos, m_sHeldenianTowerYPos;
//	char  m_cHeldenianTowerSide;
	char  m_cHeldenianModeMap;
	short m_sHeldenianWinningZoneX;
	short m_sHeldenianWinningZoneY;

	BOOL  m_bMineralGenerator;
	char  m_cMineralGeneratorLevel;
	POINT m_MineralPointList[DEF_MAXMINERALPOINT];
	int   m_iTotalMineralPoint, m_iMaxMineral, m_iCurMineral;

	char  m_cWhetherStatus;		// 기상 상태. 0이면 없음. 1~3 비 4~6 눈 7~9 폭풍 
	DWORD m_dwWhetherLastTime, m_dwWhetherStartTime;  // 날씨 지속, 시작 시간 

	int   m_iLevelLimit;
	int   m_iUpperLevelLimit;	// 상위 렙 제한 

	class COccupyFlag * m_pOccupyFlag[DEF_MAXOCCUPYFLAG];
	int   m_iTotalOccupyFlags;
	
	class CStrategicPoint * m_pStrategicPointList[DEF_MAXSTRATEGICPOINTS];
	BOOL  m_bIsAttackEnabled;

	BOOL  m_bIsFightZone;

	struct {
		char cType;
		int sX, sY;
	} m_stEnergySphereCreationList[DEF_MAXENERGYSPHERES];

	int m_iTotalEnergySphereCreationPoint;
	
	struct {
		char cResult;
		int aresdenX, aresdenY, elvineX, elvineY;
	} m_stEnergySphereGoalList[DEF_MAXENERGYSPHERES];

	int m_iTotalEnergySphereGoalPoint;

	BOOL m_bIsEnergySphereGoalEnabled;
	int m_iCurEnergySphereGoalPointIndex; 


	struct {
		int iPlayerActivity;
		int iNeutralActivity;
		int iAresdenActivity;
		int iElvineActivity;
		int iMonsterActivity;
		int iExecutorActivity;

	} m_stSectorInfo[DEF_MAXSECTORS][DEF_MAXSECTORS], m_stTempSectorInfo[DEF_MAXSECTORS][DEF_MAXSECTORS];
	short sMobEventAmount;
	int m_iTotalItemEvents;
	struct {
		char cItemName[21];	// Name of the item
		int iAmount;		// Number of items in a drop
		int iTotalNum;		// Max items that can be given
		int iDropped;		// Nbe of already dropped items
		int iMonth;
		int iDay;
		int iType;			// 0
		char *cMob[5];		// mobs names pointers
		int iNbeMob;		// Nbe of mobs in the list
	} m_stItemEventList[DEF_MAXITEMEVENTS];

	struct {
		char  cDir;
		short dX;
		short dY;
	} m_stHeldenianGateDoor[DEF_MAXHELDENIANDOOR];

	struct {
		short sTypeID;
		short dX;
		short dY;
		char  cSide;
	} m_stHeldenianTower[DEF_MAXHELDENIANTOWER];

	int m_iMaxNx, m_iMaxNy, m_iMaxAx, m_iMaxAy, m_iMaxEx, m_iMaxEy, m_iMaxMx, m_iMaxMy, m_iMaxPx, m_iMaxPy, m_iMaxXx, m_iMaxXy;
	
	struct {
		char cRelatedMapName[11];
		int iMapIndex;
		int dX, dY;
		int iHP, iInitHP;
		int iEffectX[5];
		int iEffectY[5];
	
	} m_stStrikePoint[DEF_MAXSTRIKEPOINTS];
	int m_iTotalStrikePoints;

	BOOL m_bIsDisabled;		// 폭격으로 기능이 마비된 경우 
	int m_iTotalAgriculture;

	struct {
		char cType;			// 이게 NULL이면 정의되지 않은것을 의미.
		char cSide;			// 사이드
		short sX, sY;		// 설치된 위치 
	} m_stCrusadeStructureInfo[DEF_MAXCRUSADESTRUCTURES];
	int m_iTotalCrusadeStructures;
	BOOL m_bIsEnergySphereAutoCreation;
private:
	BOOL _bDecodeMapDataFileContents();
public:
	// Snow BOOLean for certain maps to snow instead of rain
	BOOL m_bIsSnowEnabled;
	BOOL m_bIsRecallImpossible;
	BOOL m_bIsApocalypseMap;
	BOOL m_bIsHeldenianMap;
	// SNOOPY for implementing safe mode
	int m_iPKmode;
	//SNopy for change XP on some maps...
	int m_iXPRate;
	//SNopy for change Drop rate on some maps...
	int m_iExtraDrop;
	// Snoopy to adjust Boss spawning rate (not in pits)
	int m_iBossAdjust;
	// SNOOPY: to prevent character to log out on non permanentlly hosted maps.
	BOOL m_nIsNotPermanentMap;
	int m_iDropType; // SNOOPY: to change player drops type
	BOOL m_bInsideBuildingLimitedCast;
	BOOL m_bChangedForCrusade; // SNOOPY: to stored a changed map during crusade...
	char m_cThunder; //0: normal, 1:Lightning, 2: Apoc FireThunder
	int m_iNoSMRGKilledMobs;
};

#endif // !defined(AFX_MAP_H__12609160_8060_11D2_A8E6_00001C7030A6__INCLUDED_)
