// Misc.h: interface for the CMisc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MISC_H__C3D29FC0_755B_11D2_A8E6_00001C7030A6__INCLUDED_)
#define AFX_MISC_H__C3D29FC0_755B_11D2_A8E6_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class CMisc  						    
{
public:
	void Temp();
	BOOL bCheckValidName(char *pStr);
	BOOL bDecode(char cKey, char *pStr);
	BOOL bEncode(char cKey, char *pStr);
	void GetDirPoint(char cDir, int * pX, int * pY);
	void GetPoint2(int x0, int y0, int x1, int y1, int * pX, int * pY, int * pError, int iCount);
	void GetPoint(int x0, int y0, int x1, int y1, int * pX, int * pY, int * pError);
	char cGetNextMoveDir(short sX, short sY, short dX, short dY);
	void GetMyCursorPos(short * pX, short * pY);
	CMisc();
	virtual ~CMisc();

};

#endif // !defined(AFX_MISC_H__C3D29FC0_755B_11D2_A8E6_00001C7030A6__INCLUDED_)
