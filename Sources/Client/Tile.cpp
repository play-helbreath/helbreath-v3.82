// Tile.cpp: implementation of the CTile class.
//
//////////////////////////////////////////////////////////////////////

#include "Tile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTile::CTile()
{
	m_sOwnerType = NULL;
	ZeroMemory(m_cOwnerName, sizeof(m_cOwnerName));
	m_sDeadOwnerType = NULL;
	ZeroMemory(m_cDeadOwnerName, sizeof(m_cDeadOwnerName));
	m_cDeadOwnerFrame     = -1;

	m_sItemSprite      = NULL;
	m_sItemSpriteFrame = NULL;

	m_sDynamicObjectType  = NULL;
	m_cDynamicObjectFrame = NULL;

	m_iChatMsg       = NULL;
	m_iDeadChatMsg   = NULL;

	m_wObjectID = NULL;
	
	m_iEffectType  = 0;
	m_iEffectFrame = 0;
	m_iEffectTotalFrame = 0;
	m_dwEffectTime = NULL;
}

CTile::~CTile()
{

}

void CTile::Clear()
{
	m_wObjectID     = NULL;
	m_wDeadObjectID = NULL;

	m_sOwnerType = NULL;
	ZeroMemory(m_cOwnerName, sizeof(m_cOwnerName));
	
	m_sDeadOwnerType = NULL;
	ZeroMemory(m_cDeadOwnerName, sizeof(m_cDeadOwnerName));

	m_cDeadOwnerFrame = -1;
	m_dwDeadOwnerTime = NULL;

	m_cOwnerAction = NULL;
	m_cDir         = NULL;
	m_cOwnerFrame  = NULL;

	m_sItemSprite      = NULL;
	m_sItemSpriteFrame = NULL;
	m_cItemColor       = NULL;

	m_sDynamicObjectType  = NULL;
	m_cDynamicObjectFrame = NULL;

	m_iChatMsg     = NULL;
	m_iDeadChatMsg = NULL;

	m_iStatus      = NULL;
	m_iDeadStatus  = NULL;

	m_sV1 = NULL;
	m_sV2 = NULL;
	m_sV3 = NULL;

	m_sAppr1 = NULL;
	m_sAppr2 = NULL;
	m_sAppr3 = NULL;
	m_sAppr4 = NULL;
	m_iApprColor = NULL; 

	m_iEffectType  = 0;
	m_iEffectFrame = 0;
	m_iEffectTotalFrame = 0;
	m_dwEffectTime = NULL;

	m_dwOwnerTime        = NULL;
}

