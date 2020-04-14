// TileSpr.h: interface for the CTileSpr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TILESPR_H__7D53D760_E457_11D2_B145_00001C7030A6__INCLUDED_)
#define AFX_TILESPR_H__7D53D760_E457_11D2_B145_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>

class CTileSpr  
{
public:
	CTileSpr();
	virtual ~CTileSpr();
	short m_sTileSprite;
	short m_sTileSpriteFrame;
	short m_sObjectSprite;
	short m_sObjectSpriteFrame;
	bool  m_bIsMoveAllowed;
	bool  m_bIsTeleport;
};

#endif // !defined(AFX_TILESPR_H__7D53D760_E457_11D2_B145_00001C7030A6__INCLUDED_)
