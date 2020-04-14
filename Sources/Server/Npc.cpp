// Npc.cpp: implementation of the CNpc class.
//
//////////////////////////////////////////////////////////////////////

#include "Npc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNpc::CNpc(char * pName5)
{
 int i;
	ZeroMemory(m_cName, sizeof(m_cName));
	memcpy(m_cName, pName5, 5);
	
	for (i = 0; i < DEF_MAXWAYPOINTS; i++)			  
		m_iWayPointIndex[i] = -1;
	
	for (i = 0; i < DEF_MAXMAGICEFFECTS; i++) 
		m_cMagicEffectStatus[i]	= 0;

	m_bIsSummoned       = FALSE;
	m_bIsPermAttackMode = FALSE;

	m_dwRegenTime = NULL;
	m_bIsKilled   = FALSE;

	m_sOriginalType      = NULL;
	m_iSummonControlMode = NULL;
	
	m_cAttribute = NULL;
	m_iAbsDamage = NULL;
	m_iStatus    = NULL;
	m_sAppr2     = NULL;

	m_iAttackRange    = 1;
	m_cSpecialAbility = 0;
	
	m_iExp = 0;

	m_iBuildCount = 0;
	m_iManaStock  = 0;
	m_bIsUnsummoned = FALSE;
	m_cCropType = 0;
	m_cCropSkill = 0;

	m_bIsMaster  = FALSE;
	m_iGuildGUID = NULL;
	m_iV1 = 0;

	//m_iNpcItemType   = 0;
	//m_iNpcItemMax    = 0;
	//SNOOPY: Unless stated otherwize all npc have absolute poison resistance.
	m_cPoisonResistance = 110;
	m_iPoisonLevel  = 0;
	m_iNpcBossType  = 0;

}

CNpc::~CNpc()
{

}


/*// .text:004BAFD0
// xfers to: m_vNpcItem.at, bGetItemNameWhenDeleteNpc, sub_4BC360
void CNpc::m_vNpcItem.size()
{
 int iRet;
 class CNpcItem * pTempNpcItem;
	
	if (pTempNpcItem->m_cName == NULL) {
		iRet = 0;
	}
	else {
		iRet = pTempNpcItem->8 - (pTempNpcItem->m_cName >> 5);
	}
	return iRet;

}

// .text:.text:004BB010
// xfers to: bGetItemNameWhenDeleteNpc
// xfers from: sub_4BB3D0, sub_4BB340, m_vNpcItem.size
void CNpc::m_vNpcItem.at(int iResult)
{ 
	if (iResult < m_vNpcItem.size()) {
		sub_4BB3D0();
	}
	sub_4BB340() += (iResult << 5);

}*/