// Player.h: interface for the CPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYER_H__C3D29FC6_755B_11D2_A8E6_00001C7030A6__INCLUDED_)
#define AFX_PLAYER_H__C3D29FC6_755B_11D2_A8E6_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>
#include "XSocket.h"


class CPlayer  				  
{
public:
	CPlayer();
	virtual ~CPlayer();

	class XSocket * m_pXSock;

private:

	

};

#endif // !defined(AFX_PLAYER_H__C3D29FC6_755B_11D2_A8E6_00001C7030A6__INCLUDED_)
