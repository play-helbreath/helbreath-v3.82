// Teleport.h: interface for the CTeleport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TELEPORT_H__A9554BE2_A96B_11D2_B143_00001C7030A6__INCLUDED_)
#define AFX_TELEPORT_H__A9554BE2_A96B_11D2_B143_00001C7030A6__INCLUDED_

#include <windows.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTeleport  
{
public:
	CTeleport(); 
	virtual ~CTeleport();

	char  m_cTeleportNpcName[21];					// The npc with teleport ability.
	char  m_cSourceMap[11];							// The map the teleport npc is located in.
	char  m_cTargetMap[11];							// The map the player will be teleported to.
	
	int   m_iDestinationX, m_iDestinationY;			// The destination coordinates on the map.
	int	  m_iCost;									// The amount of gold paid to teleport.
	short m_sMinLevel, m_sMaxLevel;					// The required level range for the player.
	char  m_iSide;									// The side the player must be for a successful teleport.
			// 1 aresden
			// 2 elvine
			// 12 both
	BOOL m_bHunter, m_bNetural, m_bCriminal;		// Check if player is a Civilian, Neutral, or Criminal.
};

#endif // AFX_TELEPORT_H__A9554BE2_A96B_11D2_B143_00001C7030A6__INCLUDED_
