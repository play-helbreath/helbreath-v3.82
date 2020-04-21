// Map.cpp: implementation of the CMap class.
//
//////////////////////////////////////////////////////////////////////

#include "Map.h"

extern void PutLogFileList(char * cStr);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMap::CMap(class CGame * pGame)
: m_bIsSnowEnabled(FALSE)
{
 int i, ix, iy;

	for (i = 0; i < DEF_MAXTELEPORTLOC; i++)
		m_pTeleportLoc[i] = NULL;

	for (i = 0; i < DEF_MAXWAYPOINTCFG; i++) {
		m_WaypointList[i].x = -1;
		m_WaypointList[i].y = -1;
	}

	for (i = 0; i < DEF_MAXMGAR; i++) {
		m_rcMobGenAvoidRect[i].top  = -1;
		m_rcMobGenAvoidRect[i].left = -1;
	}

	for (i = 0; i < DEF_MAXNMR; i++) {
		m_rcNoAttackRect[i].top  = -1;
		m_rcNoAttackRect[i].left = -1;
	}

	for (i = 0; i < DEF_MAXSPOTMOBGENERATOR; i++) {
		m_stSpotMobGenerator[i].bDefined = FALSE;
		m_stSpotMobGenerator[i].iTotalActiveMob = 0;
		m_stSpotMobGenerator[i].iKilledMobs = 0;
	}
	m_bHasMagicSMG = FALSE;

	for (i = 0; i < DEF_MAXFISHPOINT; i++) {
		m_FishPointList[i].x = -1;
		m_FishPointList[i].y = -1;
	}

	for (i = 0; i < DEF_MAXMINERALPOINT; i++) {
		m_MineralPointList[i].x = -1;
		m_MineralPointList[i].y = -1;
	}

	for (i = 0; i < DEF_MAXINITIALPOINT; i++) {
		m_pInitialPoint[i].x = -1;
		m_pInitialPoint[i].y = -1;
	}
 
	for (i = 0; i < 1000; i++)
		m_bNamingValueUsingStatus[i] = FALSE;

	for (i = 0; i < DEF_MAXOCCUPYFLAG; i++)
		m_pOccupyFlag[i] = NULL;

	for (i = 0; i < DEF_MAXSTRATEGICPOINTS; i++)
		m_pStrategicPointList[i] = NULL;

	for (i = 0; i < DEF_MAXENERGYSPHERES; i++) {
		m_stEnergySphereCreationList[i].cType = NULL;
		m_stEnergySphereGoalList[i].cResult   = NULL;
	}
	
	m_iTotalActiveObject = 0;

	m_iTotalItemEvents = 0;
	for (i = 0; i < DEF_MAXITEMEVENTS; i++) 	
	{	ZeroMemory(m_stItemEventList[i].cItemName, sizeof(m_stItemEventList[i].cItemName));
		m_stItemEventList[i].iAmount	= 0;
		m_stItemEventList[i].iTotalNum	= 0;
		m_stItemEventList[i].iDropped	= 0;
		m_stItemEventList[i].iMonth		= 0;
		m_stItemEventList[i].iDay		= 0;
		m_stItemEventList[i].iType		= 0;
		m_stItemEventList[i].cMob[0]	= NULL;
		m_stItemEventList[i].cMob[1]	= NULL;
		m_stItemEventList[i].cMob[2]	= NULL;
		m_stItemEventList[i].cMob[3]	= NULL;
		m_stItemEventList[i].cMob[4]	= NULL;
		m_stItemEventList[i].iNbeMob	= 0;
	}

	sMobEventAmount = 15;
	//m_sInitialPointX = 0;
	//m_sInitialPointY = 0;

	m_bIsFixedDayMode = FALSE;

	m_iTotalFishPoint = 0;
	m_iMaxFish = 0;
	m_iCurFish = 0;

	m_iTotalMineralPoint = 0;
	m_iMaxMineral = 0;
	m_iCurMineral = 0;

	m_pTile = NULL;

	m_cWhetherStatus = NULL;
	m_cType          = DEF_MAPTYPE_NORMAL;

	m_pGame = pGame;

	m_iLevelLimit = 0;
	m_iUpperLevelLimit = 0; // v1.4
	m_bMineralGenerator = FALSE;

	m_iTotalOccupyFlags = 0;
	
	m_bIsAttackEnabled = TRUE; // To prevent any attack from npc/players
	m_cRandomMobGeneratorLevel = 0;
	m_iMapLevel = 0;

	m_bIsFightZone = FALSE;
	
	m_iTotalEnergySphereCreationPoint = 0;
	m_iTotalEnergySphereGoalPoint = 0;

	m_bIsEnergySphereGoalEnabled = FALSE;
	m_iCurEnergySphereGoalPointIndex = -1;

	for (ix = 0; ix < DEF_MAXSECTORS; ix++)
	for (iy = 0; iy < DEF_MAXSECTORS; iy++) {
		m_stSectorInfo[ix][iy].iNeutralActivity = 0;
		m_stSectorInfo[ix][iy].iAresdenActivity = 0;
		m_stSectorInfo[ix][iy].iElvineActivity  = 0;
		m_stSectorInfo[ix][iy].iMonsterActivity = 0;
		m_stSectorInfo[ix][iy].iPlayerActivity  = 0;
		m_stSectorInfo[ix][iy].iExecutorActivity  = 0;

		m_stTempSectorInfo[ix][iy].iNeutralActivity = 0;
		m_stTempSectorInfo[ix][iy].iAresdenActivity = 0;
		m_stTempSectorInfo[ix][iy].iElvineActivity  = 0;
		m_stTempSectorInfo[ix][iy].iMonsterActivity = 0;
		m_stTempSectorInfo[ix][iy].iPlayerActivity  = 0;
		m_stTempSectorInfo[ix][iy].iExecutorActivity  = 0;
	} 
	
	m_iMaxNx = m_iMaxNy = m_iMaxAx = m_iMaxAy = m_iMaxEx = m_iMaxEy = m_iMaxMx = m_iMaxMy = m_iMaxPx = m_iMaxPy = m_iMaxXx = m_iMaxXy =0;

	for (i = 0; i < DEF_MAXHELDENIANDOOR; i++) {
		m_stHeldenianGateDoor[i].cDir = 0;
		m_stHeldenianGateDoor[i].dX = 0;
		m_stHeldenianGateDoor[i].dY = 0;
	}

	for (i = 0; i < DEF_MAXHELDENIANTOWER; i++) {
		m_stHeldenianTower[i].sTypeID = 0;
		m_stHeldenianTower[i].dX = 0;
		m_stHeldenianTower[i].dY = 0;
		m_stHeldenianTower[i].cSide = 0;
	}
	
	for (i = 0; i < DEF_MAXSTRIKEPOINTS; i++) {
		m_stStrikePoint[i].dX  = 0;
		m_stStrikePoint[i].dY  = 0;
		m_stStrikePoint[i].iHP = 0;
		m_stStrikePoint[i].iMapIndex = -1;
		ZeroMemory(m_stStrikePoint[i].cRelatedMapName, sizeof(m_stStrikePoint[i].cRelatedMapName));
	}
	m_iTotalStrikePoints = 0;
	m_bIsDisabled = FALSE;

	for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++) {
		m_stCrusadeStructureInfo[i].cType = NULL;
		m_stCrusadeStructureInfo[i].cSide = NULL;
		m_stCrusadeStructureInfo[i].sX = NULL;
		m_stCrusadeStructureInfo[i].sY = NULL;
	}
	m_iTotalCrusadeStructures = 0;
	m_iTotalAgriculture = 0;

	// SNOOPY: initialising PKmode
	// 0: All PK allowed
	// 1: PK not for same city
	// 2: EK not allowed between Ares and Elvines, but "Evil" side can PK
	// 3: No PK allowed at all
	m_iPKmode = 0;
	m_iXPRate = 100; // as a percent...
	m_iExtraDrop = 0; // no bonus
	m_iBossAdjust = 100; // 100% base...
	m_bHpMpSpPopoEnabled = TRUE; 
	m_iDropType = 1; // Default, normal drops


	//SNOOPY: Setting some BOOL values here:
	m_bIsCitizenLimit		= FALSE;
	m_bIsSnowEnabled		= FALSE;
	m_bIsRecallImpossible	= FALSE;
	m_bIsApocalypseMap		= FALSE;
	m_bIsHeldenianMap		= FALSE;
	m_nIsNotPermanentMap	= FALSE;
	m_iApocalypseMobGenType = 0;
	m_iApocalypseBossMobNpcID = 0;
	m_cDynamicGateType = 0;
	m_bInsideBuildingLimitedCast = FALSE;
	m_bChangedForCrusade = FALSE;
	m_cThunder = 0;
	m_iNoSMRGKilledMobs = 0;
}

CMap::~CMap()
{
	
 int i;
	
	if (m_pTile != NULL) 
		delete []m_pTile;	
 	
	for (i = 0; i < DEF_MAXTELEPORTLOC; i++)
		if (m_pTeleportLoc[i] != NULL) delete m_pTeleportLoc[i];

	for (i = 0; i < DEF_MAXOCCUPYFLAG; i++)
		if (m_pOccupyFlag[i] != NULL) delete m_pOccupyFlag[i];

	for (i = 0; i < DEF_MAXSTRATEGICPOINTS; i++)
		if (m_pStrategicPointList[i] != NULL) delete m_pStrategicPointList[i];
}

void CMap::SetOwner(short sOwner, char cOwnerClass, short sX, short sY)
{
 class CTile * pTile;	
	
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return;
	
	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	pTile->m_sOwner      = sOwner;
	pTile->m_cOwnerClass = cOwnerClass;
}

char _tmp_cMoveDirX[9] = { 0,0,1,1,1,0,-1,-1,-1 };
char _tmp_cMoveDirY[9] = { 0,-1,-1,0,1,1,1,0,-1 };
BOOL CMap::bCheckFlySpaceAvailable(short sX, char sY, char cDir, short sOwner)
{
 class CTile * pTile;
 short dX, dY;

	if ((cDir <= 0) || (cDir > 8)) return 0;
	dX = _tmp_cMoveDirX[cDir] + sX;
	dY = _tmp_cMoveDirY[cDir] + sY;
	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return 0;
	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	if (pTile->m_sOwner != NULL) return 0;
	pTile->m_sOwner = sOwner;
	return 1;
}

void CMap::SetDeadOwner(short sOwner, char cOwnerClass, short sX, short sY)
{
 class CTile * pTile;	
	
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return;
 
	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	pTile->m_sDeadOwner      = sOwner;
	pTile->m_cDeadOwnerClass = cOwnerClass;
}


/*********************************************************************************************************************
**  void CMap::GetOwner(short * pOwner, char * pOwnerClass, short sX, short sY)										**
**  description			:: check if the tile contains a player														**
**  last updated		:: November 17, 2004; 10:48 PM; Hypnotoad													**
**	return value		:: void																						**
**  commentary			::	-	added check to see if owner is class 1 or if is greater than max clients 			**
**********************************************************************************************************************/
void CMap::GetOwner(short * pOwner, char * pOwnerClass, short sX, short sY)
{
 class CTile * pTile;	

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) 
	{	*pOwner      = NULL;	
		*pOwnerClass = NULL;
		return;	
	}

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	*pOwner      = pTile->m_sOwner;
	*pOwnerClass = pTile->m_cOwnerClass;
	
	if ((*pOwnerClass == 1) && (*pOwner > DEF_MAXCLIENTS)) 
	{	*pOwner      = NULL;	
		*pOwnerClass = NULL;
		return;	
	}
	
	if (pTile->m_sOwner == 0) *pOwnerClass = 0;
}

/*********************************************************************************************************************
**  void CMap::GetDeadOwner(short * pOwner, char * pOwnerClass, short sX, short sY)									**
**  description			:: check if the tile contains a dead player													**
**  last updated		:: November 20, 2004; 9:13 PM; Hypnotoad													**
**	return value		:: void																						**
**********************************************************************************************************************/
void CMap::GetDeadOwner(short * pOwner, char * pOwnerClass, short sX, short sY)
{
 class CTile * pTile;	

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) {
		*pOwner      = NULL;	
		*pOwnerClass = NULL;
		return;	
	}

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	*pOwner      = pTile->m_sDeadOwner;
	*pOwnerClass = pTile->m_cDeadOwnerClass;
}

 								  
BOOL CMap::bGetMoveable(short dX, short dY, short * pDOtype, short * pTopItem)
{
 class CTile * pTile;	
	
	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return FALSE;
	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);
	
	if (pDOtype != NULL) *pDOtype = pTile->m_sDynamicObjectType;
	if (pTopItem != NULL) *pTopItem = pTile->m_cTotalItem;

	if (pTile->m_sOwner != NULL) return FALSE;
	if (pTile->m_bIsMoveAllowed == FALSE) return FALSE;
	if (pTile->m_bIsTempMoveAllowed == FALSE) return FALSE;
	
	return TRUE;
}

BOOL CMap::bGetIsMoveAllowedTile(short dX, short dY)
{
 class CTile * pTile;	
	
	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return FALSE;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);
	
	if (pTile->m_bIsMoveAllowed == FALSE) return FALSE;
	if (pTile->m_bIsTempMoveAllowed == FALSE) return FALSE;
	
	return TRUE;
}
// SNoopy: Prevent characters to stay behind crusade structures
void CMap::SetStayAllowedFlag(int dX, int dY, BOOL bFlag)
{ class CTile * pTile;		
	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return;
	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);
	pTile->m_bCanStayHere = bFlag;
}
BOOL CMap::bGetIsStayAllowedTile(short dX, short dY) // Staying there, and suffer damage....
{ class CTile * pTile;		
	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return FALSE;
	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);	
	if (pTile->m_bIsMoveAllowed == FALSE) return FALSE;
	if (pTile->m_bIsTempMoveAllowed == FALSE) return FALSE;
	if (pTile->m_bCanStayHere == FALSE) return FALSE;
	return TRUE;
}

/*BOOL CMap::sub_4C0F20(short dX, short dY)
{
 class CTile * pTile;	
	
	3CA18h = 0;

	if ((dX < 14) || (dX >= m_sSizeX - 16) || (dY < 12) || (dY >= m_sSizeY - 14)) return FALSE;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);

}*/

BOOL CMap::bGetIsTeleport(short dX, short dY)
{
 class CTile * pTile;	
	
	if ((dX < 14) || (dX >= m_sSizeX - 16) || (dY < 12) || (dY >= m_sSizeY - 14)) return FALSE;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);
	
	if (pTile->m_bIsTeleport == FALSE) return FALSE;
	
	return TRUE;
}

void CMap::ClearOwner(int iDebugCode, short sOwnerH, char cOwnerType, short sX, short sY)
{
 class CTile * pTile;	
	
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return;
 
	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);

	if ((pTile->m_sOwner == sOwnerH) && (pTile->m_cOwnerClass == cOwnerType)) 
	{	pTile->m_sOwner      = NULL;
		pTile->m_cOwnerClass = NULL;
	}
	if ((pTile->m_sDeadOwner == sOwnerH) && (pTile->m_cDeadOwnerClass == cOwnerType)) 
	{	pTile->m_sDeadOwner      = NULL;
		pTile->m_cDeadOwnerClass = NULL;
	}
}

void CMap::ClearDeadOwner(short sX, short sY)
{
 class CTile * pTile;	

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return;	

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	pTile->m_sDeadOwner      = NULL;
	pTile->m_cDeadOwnerClass = NULL;
}

BOOL CMap::bSetItem(short sX, short sY, class CItem * pItem)
{
 class CTile * pTile;	
 register int i;
	
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return NULL; 

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);

	// v1.4 ¸¶Áö¸· Å¸ÀÏ¿¡ ¾ÆÀÌÅÛÀÌ ÀÖ´Ù¸é »èÁ¦½ÃÅ°°í ÀÌµ¿ÇÑ´Ù. 
	if (pTile->m_pItem[DEF_TILE_PER_ITEMS-1] != NULL) 
		delete pTile->m_pItem[DEF_TILE_PER_ITEMS-1];
	else pTile->m_cTotalItem++;
	
	for (i = DEF_TILE_PER_ITEMS-2; i >= 0; i--) 
		pTile->m_pItem[i+1] = pTile->m_pItem[i];

	pTile->m_pItem[0] = pItem;
	//pTile->m_cTotalItem++;
	return TRUE;
}


class CItem * CMap::pGetItem(short sX, short sY, short * pRemainItemSprite, short * pRemainItemSpriteFrame, char * pRemainItemColor) //v1.4 color
{
 class CTile * pTile;	
 class CItem * pItem;
 register int i;
	
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return NULL;

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	pItem =  pTile->m_pItem[0];
	if (pTile->m_cTotalItem == 0) return NULL;

	for (i = 0; i <= DEF_TILE_PER_ITEMS-2; i++)
		pTile->m_pItem[i] = pTile->m_pItem[i+1];
	pTile->m_cTotalItem--;
	pTile->m_pItem[pTile->m_cTotalItem] = NULL;
	
	if (pTile->m_pItem[0] == NULL) 
	{	*pRemainItemSprite      = 0;
		*pRemainItemSpriteFrame = 0;	
		*pRemainItemColor       = 0;
	}else
	{	*pRemainItemSprite      = pTile->m_pItem[0]->m_sSprite;
		*pRemainItemSpriteFrame = pTile->m_pItem[0]->m_sSpriteFrame;
		*pRemainItemColor       = pTile->m_pItem[0]->m_cItemColor;
	}
	return pItem;
}
// Snoopy:
BOOL CMap::pCheckBombItem(short sX, short sY)
{class CTile * pTile;	
 class CItem * pItem;
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return TRUE;

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	if (pTile->m_cTotalItem == 0) return TRUE;
	pItem =  pTile->m_pItem[0];
	// "Boom" item, can't be taken if burning	
	if (   (pItem != NULL) 
		&& (pItem->m_sItemEffectType == DEF_ITEMEFFECTTYPE_BOMB) 
		&& (pItem->m_sSprite == 16)
		&& (pItem->m_sSpriteFrame == 20))
	{	return TRUE;
	}else 
		return FALSE;
}

int CMap::iCheckItem(short sX, short sY)
{
 class CTile * pTile;	
 class CItem * pItem;
	
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return NULL;

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	pItem =  pTile->m_pItem[0];
	if (pTile->m_cTotalItem == 0) return NULL;

	return pItem->m_sIDnum;
}


BOOL CMap::bIsValidLoc(short sX, short sY)
{
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return FALSE;
	return TRUE;
}

BOOL CMap::bInit(char * pName)
{
 int i;
	// ¸ÊÆÄÀÏÀ» ·ÎµåÇÑ´Ù.
	ZeroMemory(m_cName, sizeof(m_cName));
	strcpy(m_cName, pName);

	ZeroMemory(m_cLocationName, sizeof(m_cLocationName));

	if (_bDecodeMapDataFileContents() == FALSE) 
		return FALSE;	

	for (i = 0; i < DEF_MAXTELEPORTLOC; i++)
		m_pTeleportLoc[i] = NULL;

	return TRUE;
}

BOOL CMap::_bDecodeMapDataFileContents()
{
 HANDLE hFile;
 char  cMapFileName[256], cHeader[260], cTemp[100];
 DWORD dwFileSize, nRead;
 register int i, ix, iy;
 char * token, cReadMode;
 char seps[] = "= \t\n";
 class CStrTok * pStrTok = NULL;
 class CTile * pTile;
 short * sp;

	ZeroMemory(cMapFileName, sizeof(cMapFileName));
	strcat(cMapFileName, "mapdata\\");
	strcat(cMapFileName, m_cName);
	strcat(cMapFileName, ".amd");
	
	hFile = CreateFile(cMapFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;
	dwFileSize = GetFileSize(hFile, NULL);
	
	ZeroMemory(cHeader, sizeof(cHeader));
	ReadFile(hFile, (char *)cHeader, 256, &nRead, NULL);

	// Çì´õÁ¤º¸¸¦ ºÐ¼®ÇÑ´Ù.

	// ¸ÕÀú ³Î¹®ÀÚ¸¦ ¾ø¾Ø´Ù.
	for (i = 0; i < 256; i++) 
		if (cHeader[i] == NULL) cHeader[i] = ' ';

	cReadMode = 0;

	pStrTok = new class CStrTok(cHeader, seps);
	token = pStrTok->pGet();
	//token = strtok( cHeader, seps );   
	while( token != NULL )   {
			
		if (cReadMode != 0) {
			switch (cReadMode) {
			case 1:
				m_sSizeX = atoi(token);
				cReadMode = 0;
				break;
			case 2:
				m_sSizeY = atoi(token);
				cReadMode = 0;
				break;
			case 3:
				m_sTileDataSize = atoi(token);
				cReadMode = 0;
				break;
			}
		}	
		else {
			if (memcmp(token, "MAPSIZEX",8) == 0) cReadMode = 1;
			if (memcmp(token, "MAPSIZEY",8) == 0) cReadMode = 2;
			if (memcmp(token, "TILESIZE",8) == 0) cReadMode = 3; 
		}
			
		//token = strtok( NULL, seps );
		token = pStrTok->pGet();
	}

	// Å©±â¿¡ ¸Â°Ô Å¸ÀÏÀ» »ý¼ºÇÑ´Ù.
	m_pTile = (class CTile *)new class CTile[m_sSizeX * m_sSizeY];

	// Å¸ÀÏÀÇ Á¤º¸¸¦ ÀÐ¾îµéÀÎ´Ù.
	for (iy = 0; iy < m_sSizeY; iy++)
	for (ix = 0; ix < m_sSizeX; ix++) {
		ReadFile(hFile, (char *)cTemp, m_sTileDataSize, &nRead, NULL);	
		pTile = (class CTile *)(m_pTile + ix + iy*m_sSizeY);
		if ((cTemp[8] & 0x80) != 0) {
			// °¥¼ö¾ø´Â ¼Ó¼ºÀÌ ¼¼Æ®µÇ¾î ÀÖ´Ù.
			 pTile->m_bIsMoveAllowed = FALSE;
		}
		else pTile->m_bIsMoveAllowed = TRUE;

		if ((cTemp[8] & 0x40) != 0) {
			// ÅÚ·¹Æ÷Æ® ¼Ó¼ºÀÌ ¼¼Æ®µÇ¾î ÀÖ´Ù.
			 pTile->m_bIsTeleport = TRUE;
		}
		else pTile->m_bIsTeleport = FALSE;

		if ((cTemp[8] & 0x20) != 0) {
			 pTile->m_bIsFarm = TRUE;
		}
		else pTile->m_bIsFarm = FALSE;

		sp = (short *)&cTemp[0];
		if (*sp == 19) {
			// ¹° Å¸ÀÏÀÌ´Ù. 
			 pTile->m_bIsWater = TRUE;
		}
		else pTile->m_bIsWater = FALSE;
	}

	CloseHandle(hFile);

	if (pStrTok != NULL) delete pStrTok;
	return TRUE;
}


BOOL CMap::bSearchTeleportDest(int sX, int sY, char * pMapName, int * pDx, int * pDy, char * pDir)
{
 register int i;
	for (i = 0; i < DEF_MAXTELEPORTLOC; i++) // DEF_MAXTELEPORTLOC 200
	if ((m_pTeleportLoc[i] != NULL) && (m_pTeleportLoc[i]->m_sSrcX == sX) && (m_pTeleportLoc[i]->m_sSrcY == sY)) {
		memcpy(pMapName, m_pTeleportLoc[i]->m_cDestMapName, 10);
		*pDx  = m_pTeleportLoc[i]->m_sDestX;
		*pDy  = m_pTeleportLoc[i]->m_sDestY;
		*pDir = m_pTeleportLoc[i]->m_cDir;
		return TRUE;
	}

	return FALSE;
}

void CMap::SetDynamicObject(WORD wID, short sType, short sX, short sY, DWORD dwRegisterTime)
{
 class CTile * pTile;	

	
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return; 

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);

	pTile->m_wDynamicObjectID   = wID;
	pTile->m_sDynamicObjectType = sType;
	pTile->m_dwDynamicObjectRegisterTime = dwRegisterTime;
}

BOOL CMap::bGetDynamicObject(short sX, short sY, short *pType, DWORD *pRegisterTime, int * pIndex)
{
 class CTile * pTile;	

	
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return FALSE; 

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);

	*pType = pTile->m_sDynamicObjectType;
	*pRegisterTime = pTile->m_dwDynamicObjectRegisterTime;
	if (pIndex != NULL) *pIndex = pTile->m_wDynamicObjectID;

	return TRUE;
}

int CMap::iGetEmptyNamingValue()
{
 register int i;

	for (i = 0; i < 1000; i++)
	if (m_bNamingValueUsingStatus[i] == FALSE) {

		m_bNamingValueUsingStatus[i] = TRUE;
		return i;
	}

	return -1;
}

void CMap::SetNamingValueEmpty(int iValue)
{
	m_bNamingValueUsingStatus[iValue] = FALSE;
}

BOOL CMap::bGetIsWater(short dX, short dY)
{
 class CTile * pTile;	
	
	if ((dX < 14) || (dX >= m_sSizeX - 16) || (dY < 12) || (dY >= m_sSizeY - 14)) return FALSE;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);
	
	if (pTile->m_bIsWater == FALSE) return FALSE;
	
	return TRUE;
}

//v2.19 2002-12-16 ³ó»ç ½ºÅ³ °ü·Ã
BOOL CMap::bRemoveCropsTotalSum()
{
	if(m_iTotalAgriculture < DEF_MAXAGRICULTURE)
	{
		m_iTotalAgriculture--;
		if(m_iTotalAgriculture < 0)
		{
			m_iTotalAgriculture = 0;
		}
		return TRUE;
	}
	return FALSE;
}

//v2.19 2002-12-16 ³ó»ç ½ºÅ³ °ü·Ã
BOOL CMap::bAddCropsTotalSum()
{
	if(m_iTotalAgriculture < DEF_MAXAGRICULTURE)
	{
		m_iTotalAgriculture++;
		return TRUE;
	}
	return FALSE;
}

BOOL CMap::bGetIsFarm(short tX, short tY)
{
 class CTile * pTile;	
	
	if ((tX < 14) || (tX >= m_sSizeX - 16) || (tY < 12) || (tY >= m_sSizeY - 14)) return FALSE;

	pTile = (class CTile *)(m_pTile + tX + tY*m_sSizeY);
	
	if (pTile->m_bIsFarm == FALSE) return FALSE;
	
	return TRUE;
}

int CMap::iAnalyze(char cType, int * pX, int * pY, int * pV1, int * pV2, int * pV3)
{

 
	// ÇöÀç ¸ÊÀÇ »óÈ²À» ºÐ¼®ÇÏ¿© Äõ¸®¿¡ ¸Â´Â À§Ä¡¸¦ ¹ÝÈ¯ÇÑ´Ù. 
	switch (cType) {
	case 1:
		// ÇöÀç ±³ÀüÀÌ ¹ú¾îÁö°í ÀÖ´Â °÷ÀÇ À§Ä¡¸¦ Ã£´Â´Ù. 

		break;


	}

	return 0;
}

void CMap::SetTempMoveAllowedFlag(int dX, int dY, BOOL bFlag)
{
 class CTile * pTile;	
	
	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);
	pTile->m_bIsTempMoveAllowed = bFlag;
}

int CMap::iRegisterOccupyFlag(int dX, int dY, int iSide, int iEKNum, int iDOI)
{int i;
	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return -1;
	for (i = 1; i < DEF_MAXOCCUPYFLAG; i++) 
	if (m_pOccupyFlag[i] == NULL) 
	{	m_pOccupyFlag[i] = new class COccupyFlag(dX, dY, iSide, iEKNum, iDOI);
		if (m_pOccupyFlag == NULL) return -1;
		else 
		{	m_iTotalOccupyFlags ++;
			return i;
		}
	}	
	return -1;
}



void CMap::ClearSectorInfo()
{
 int ix, iy;

	for (ix = 0; ix < DEF_MAXSECTORS; ix++)
	for (iy = 0; iy < DEF_MAXSECTORS; iy++) {
		m_stSectorInfo[ix][iy].iNeutralActivity = 0;
		m_stSectorInfo[ix][iy].iAresdenActivity = 0;
		m_stSectorInfo[ix][iy].iElvineActivity  = 0;
		m_stSectorInfo[ix][iy].iMonsterActivity = 0;
		m_stSectorInfo[ix][iy].iPlayerActivity  = 0;
		m_stSectorInfo[ix][iy].iExecutorActivity  = 0;
	} 
}

void CMap::ClearTempSectorInfo()
{
 int ix, iy;

	for (ix = 0; ix < DEF_MAXSECTORS; ix++)
	for (iy = 0; iy < DEF_MAXSECTORS; iy++) {
		m_stTempSectorInfo[ix][iy].iNeutralActivity = 0;
		m_stTempSectorInfo[ix][iy].iAresdenActivity = 0;
		m_stTempSectorInfo[ix][iy].iElvineActivity  = 0;
		m_stTempSectorInfo[ix][iy].iMonsterActivity = 0;
		m_stTempSectorInfo[ix][iy].iPlayerActivity  = 0;
		m_stTempSectorInfo[ix][iy].iExecutorActivity  = 0;
	} 
}

void CMap::_SetupNoAttackArea()
{
 int i, ix, iy;
 class CTile * pTile;	

	for (i = 0; i < DEF_MAXNMR; i++) {
		if ((m_rcNoAttackRect[i].top > 0)) {
			// No-Magic-Area°¡ Á¤ÀÇµÇ¾î ÀÖ´Ù.
			for (ix = m_rcNoAttackRect[i].left; ix <= m_rcNoAttackRect[i].right; ix++)
			for (iy = m_rcNoAttackRect[i].top; iy <= m_rcNoAttackRect[i].bottom; iy++) {
				pTile = (class CTile *)(m_pTile + ix + iy*m_sSizeY);
				pTile->m_iAttribute = pTile->m_iAttribute | 0x00000004;		// 3¹øÂ° ºñÆ®¸¦ ¼¼ÆÃÇÑ´Ù. ¾ÈÀüÁö´ë 
			}
		}
		else if (m_rcNoAttackRect[i].top == -10) 
		{	m_bInsideBuildingLimitedCast = TRUE;
			for (ix = 0; ix < m_sSizeX; ix++)
			for (iy = 0; iy < m_sSizeY; iy++) {
				pTile = (class CTile *)(m_pTile + ix + iy*m_sSizeY);
				pTile->m_iAttribute = pTile->m_iAttribute | 0x00000004;		// 3¹øÂ° ºñÆ®¸¦ ¼¼ÆÃÇÑ´Ù. ¾ÈÀüÁö´ë
			}
		}
	}
}

/*********************************************************************************************************************
**  int CMap::iGetAttribute(int dX, int dY, int iBitMask)															**
**  description			:: check if the tile contains a dead player													**
**  last updated		:: November 20, 2004; 9:55 PM; Hypnotoad													**
**	return value		:: int																						**
**********************************************************************************************************************/
int CMap::iGetAttribute(int dX, int dY, int iBitMask)
{
 class CTile * pTile;

	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return -1;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);
	return (pTile->m_iAttribute & iBitMask);
}

BOOL CMap::bAddCrusadeStructureInfo(char cType, short sX, short sY, char cSide)
{
 register int i;
 //class CTile * pTile;
	for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++)
	if (m_stCrusadeStructureInfo[i].cType == NULL) {
		m_stCrusadeStructureInfo[i].cType = cType;
		m_stCrusadeStructureInfo[i].cSide = cSide;
		m_stCrusadeStructureInfo[i].sX = sX;
		m_stCrusadeStructureInfo[i].sY = sY;
		// SNOOPY Tile just behind crusade structure is forbidden
		//pTile = (class CTile *)(m_pTile + sX + (sY-1)*m_sSizeY);
		//pTile->m_bIsMoveAllowed = FALSE;
		m_iTotalCrusadeStructures++;
		return TRUE;
	}

	return FALSE;
}

/*BOOL CMap::bAddHeldenianTowerInfo(char cType, short sX, short sY, char cSide)
{
 register int i;

	for (i = 0; i < DEF_MAXHELDENIANTOWER; i++)
	if (m_stHeldenianTower[i].cType == NULL) {
	if (m_stHeldenianTower[i].cSide == 1) {
		m_stHeldenianTower[i].sTypeID = sTypeID;
		m_stHeldenianTower[i].cSide = cSide;
		m_stHeldenianTower[i].sX = sX;
		m_stHeldenianTower[i].sY = sY;
		m_iHeldenianAresdenLeftTower++;
		return TRUE;
	}
	else if (m_stHeldenianTower[i].cSide == 2) {
		m_stHeldenianTower[i].sTypeID = sTypeID;
		m_stHeldenianTower[i].cSide = cSide;
		m_stHeldenianTower[i].sX = sX;
		m_stHeldenianTower[i].sY = sY;
		m_iHeldenianElvineLeftTower++;
		return TRUE;
	}

	return FALSE;
}*/

BOOL CMap::bRemoveCrusadeStructureInfo(short sX, short sY)
{
 register int i;
 //class CTile * pTile;
	for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++)
	if ((m_stCrusadeStructureInfo[i].sX == sX) && (m_stCrusadeStructureInfo[i].sY == sY)) 
	{	m_stCrusadeStructureInfo[i].cType = NULL;
		m_stCrusadeStructureInfo[i].cSide = NULL;
		m_stCrusadeStructureInfo[i].sX = NULL;
		m_stCrusadeStructureInfo[i].sY = NULL;
		// SNOOPY Tile just behind crusade structure was forbidden, allow it again		
		//pTile = (class CTile *)(m_pTile + sX + (sY-1)*m_sSizeY);
		goto RCSI_REARRANGE;
	}

	return FALSE;

RCSI_REARRANGE:;

	for (i = 0; i < DEF_MAXCRUSADESTRUCTURES-1; i++)
	if ((m_stCrusadeStructureInfo[i].cType == NULL) && (m_stCrusadeStructureInfo[i+1].cType != NULL)) 
	{	m_stCrusadeStructureInfo[i].cType = m_stCrusadeStructureInfo[i+1].cType;
		m_stCrusadeStructureInfo[i].cSide = m_stCrusadeStructureInfo[i+1].cSide;
		m_stCrusadeStructureInfo[i].sX = m_stCrusadeStructureInfo[i+1].sX;
		m_stCrusadeStructureInfo[i].sY = m_stCrusadeStructureInfo[i+1].sY;

		m_stCrusadeStructureInfo[i+1].cType = NULL;
		m_stCrusadeStructureInfo[i+1].cSide = NULL;
		m_stCrusadeStructureInfo[i+1].sX = NULL;
		m_stCrusadeStructureInfo[i+1].sY = NULL;
	}

	m_iTotalCrusadeStructures--;
	return TRUE;
}



void CMap::RestoreStrikePoints()
{
 int i;

	for (i = 0; i < DEF_MAXSTRIKEPOINTS; i++) {
		m_stStrikePoint[i].iInitHP = m_stStrikePoint[i].iHP;
	}
}

