#include "Teleport.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTeleport::CTeleport()
{

	ZeroMemory(m_cTeleportNpcName, sizeof(m_cTeleportNpcName));
	ZeroMemory(m_cSourceMap, sizeof(m_cSourceMap));
	ZeroMemory(m_cTargetMap, sizeof(m_cTargetMap));

	m_iDestinationX = -1;
	m_iDestinationY = -1;
	m_iCost			= -1;				// The amount of gold paid to teleport.
	m_sMaxLevel		= 0;
	m_sMinLevel		= 0;
	m_iSide			= -1;
	m_bHunter		= FALSE;
	m_bNetural		= FALSE;
	m_bCriminal		= FALSE;
}

CTeleport::~CTeleport()
{										    

}

