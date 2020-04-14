// Mineral.h: interface for the CMineral class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MINERAL_H__1A17B280_B21E_11D3_9DC2_00001C7030A6__INCLUDED_)
#define AFX_MINERAL_H__1A17B280_B21E_11D3_9DC2_00001C7030A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMineral  
{
public:
	CMineral(char cType, char cMapIndex, int sX, int sY, int iRemain);
	virtual ~CMineral();
	
	char  m_cType;

	char  m_cMapIndex;
	int   m_sX, m_sY;
	int   m_iDifficulty;
	short m_sDynamicObjectHandle;
	
	int   m_iRemain;
};

#endif // !defined(AFX_MINERAL_H__1A17B280_B21E_11D3_9DC2_00001C7030A6__INCLUDED_)
