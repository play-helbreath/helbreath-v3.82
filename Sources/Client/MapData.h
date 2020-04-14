// MapData.h: interface for the CMapData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPDATA_H__DA7A0760_758B_11D2_A8E6_00001C7030A6__INCLUDED_)
#define AFX_MAPDATA_H__DA7A0760_758B_11D2_A8E6_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>
#include <winbase.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "Tile.h"
#include "ActionID.h"
#include "Game.h"
#include "TileSpr.h"

#define MAPDATASIZEX	40
#define MAPDATASIZEY	35

class CMapData  
{
public:
	void * operator new (size_t size)
	{
		return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
	};
	
	void operator delete(void * mem)
	{
		HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, mem);
	};

	CMapData(class CGame * pGame);
	virtual ~CMapData();
	void Init();
	void OpenMapDataFile(char * cFn);
	void GetOwnerStatusByObjectID(WORD wObjectID, char * pOwnerType, char * pDir, short * pAppr1, short * pAppr2, short * pAppr3, short * pAppr4, int * pStatus, int * pColor, char * pName);
	void ClearDeadChatMsg(short sX, short sY);
	void ClearChatMsg(short sX, short sY);
	void ShiftMapData(char cDir);
	void _bDecodeMapInfo(char * pHeader);
	BOOL __fastcall bSetChatMsgOwner(WORD wObjectID, short sX, short sY, int iIndex);
	BOOL __fastcall bSetDeadOwner(WORD wObjectID, short sX, short sY, short sType, char cDir, short sAppr1, short sAppr2, short sAppr3, short sAppr4, int iApprColor, int iStatus, char * pName);
	BOOL __fastcall bGetDeadOwner(short sX, short sY, short * pOwnerType, char * pDir, short * pAppr1, short * pAppr2, short * pAppr3, short * pAppr4, int * pApprColor, char * pFrame, char * pName, short * pItemSprite, short * pItemSpriteFrame, int * pCharIndex);
	BOOL __fastcall bGetOwner(short sX, short sY, short * pOwnerType, char * pDir, short * pAppr1, short * pAppr2, short * pAppr3, short * pAppr4, int * pApprColor, int * pStatus, char * pName, char * pAction, char * pFrame, int * pChatIndex, short * pV1, short * pV2);
	BOOL __fastcall bSetOwner(WORD wObjectID, int sX, int sY, int sType, int cDir, short sAppr1, short sAppr2, short sAppr3, short sAppr4, int iApprColor, int iStatus, char * pName, short sAction, short sV1, short sV2, short sV3, int iPreLoc = 0, int iFrame = 0);
	BOOL __fastcall bGetOwner(short sX, short sY, char * pName, short * pOwnerType, int * pOwnerStatus, WORD * pObjectID);
	BOOL bSetDynamicObject(short sX, short sY, WORD wID, short sType, BOOL bIsEvent);
	BOOL bIsTeleportLoc(short sX, short sY);
	BOOL bGetIsLocateable(short sX, short sY);
	BOOL bSetItem(short sX, short sY, short sItemSpr, short sItemSprFrame, char cItemColor, BOOL bDropEffect = TRUE);
	int  iObjectFrameCounter(char * cPlayerName, short sViewPointX, short sViewPointY);

	class CTile m_pData[MAPDATASIZEX][MAPDATASIZEY];
	class CTile m_pTmpData[MAPDATASIZEX][MAPDATASIZEY];
	class CTileSpr m_tile[752][752];
	class CGame * m_pGame;

	struct {
		short m_sMaxFrame;
		short m_sFrameTime;
	} m_stFrame[DEF_TOTALCHARACTERS][DEF_TOTALACTION];
	DWORD m_dwFrameTime;
	DWORD m_dwDOframeTime;
	DWORD m_dwFrameCheckTime;
	int m_iObjectIDcacheLocX[30000];
	int m_iObjectIDcacheLocY[30000];
	DWORD m_dwFrameAdjustTime;
	short m_sMapSizeX, m_sMapSizeY;
	short m_sRectX, m_sRectY;
	short m_sPivotX, m_sPivotY;
};

#endif // !defined(AFX_MAPDATA_H__DA7A0760_758B_11D2_A8E6_00001C7030A6__INCLUDED_)
