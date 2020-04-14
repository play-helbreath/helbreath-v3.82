// DynamicObject.cpp: implementation of the CDynamicObject class.
//
//////////////////////////////////////////////////////////////////////

#include "DynamicObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDynamicObject::CDynamicObject(short sOwner, char cOwnerType, short sType, char cMapIndex, short sX, short sY, DWORD dwRegisterTime, DWORD dwLastTime, int iV1)
{
	m_sOwner         = sOwner;
	m_cOwnerType     = cOwnerType;

	m_sType          = sType;
	ZeroMemory(cOwnerName, sizeof(cOwnerName));
	
	m_cMapIndex      = cMapIndex;
	m_sX             = sX;
	m_sY             = sY;
	
	m_dwRegisterTime = dwRegisterTime;
	m_dwLastTime     = dwLastTime;

	m_iCount         = 0;
	m_iV1            = iV1;
}										   

CDynamicObject::~CDynamicObject()
{

}
