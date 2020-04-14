// TileSpr.cpp: implementation of the CTileSpr class.
//
//////////////////////////////////////////////////////////////////////

#include "TileSpr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTileSpr::CTileSpr()
{
	m_sTileSprite = 0;
	m_sTileSpriteFrame = 0;
	m_sObjectSprite = 0;
	m_sObjectSpriteFrame = 0;
	m_bIsMoveAllowed = TRUE;
	m_bIsTeleport = FALSE;
}

CTileSpr::~CTileSpr()
{

}
