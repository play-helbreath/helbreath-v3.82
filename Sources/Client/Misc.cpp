// Misc.cpp: implementation of the CMisc class.
//
//////////////////////////////////////////////////////////////////////

#include "Misc.h"
#include "GlobalDef.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMisc::CMisc()
{

}

CMisc::~CMisc()
{

}

char CMisc::cGetNextMoveDir(short sX, short sY, short dX, short dY)
{
 short absX, absY;
 char  cRet = 0;

	absX = sX - dX;
	absY = sY - dY;

	if ((absX == 0) && (absY == 0)) cRet = 0;

	if (absX == 0) {
		if (absY > 0) cRet = 1;
		if (absY < 0) cRet = 5;
	}
	if (absY == 0) {
		if (absX > 0) cRet = 7;
		if (absX < 0) cRet = 3;
	}
	if ( (absX > 0)	&& (absY > 0) ) cRet = 8;
	if ( (absX < 0)	&& (absY > 0) ) cRet = 2;
	if ( (absX > 0)	&& (absY < 0) ) cRet = 6;
	if ( (absX < 0)	&& (absY < 0) ) cRet = 4;

	return cRet;
}


void CMisc::GetPoint(int x0, int y0, int x1, int y1, int * pX, int * pY, int * pError, int iCount)
{int dx, dy, x_inc, y_inc, error, index;
 int iResultX, iResultY, iCnt = 0;

	if ((x0 == x1) && (y0 == y1))
	{	*pX = x0;
		*pY = y0;
		return;
	}
	error = *pError;
	iResultX = x0;
	iResultY = y0;
	dx = x1-x0;
	dy = y1-y0;
	if(dx>=0) x_inc = 1;
	else
	{	x_inc = -1;
		dx = -dx;
	}
	if(dy>=0) y_inc = 1;
	else
	{	y_inc = -1;
		dy = -dy;
	}
	if(dx>dy)
	{	for(index = 0; index <= dx; index++)
		{	error += dy;
			if(error > dx)
			{	error -= dx;
				iResultY += y_inc;
			}
			iResultX += x_inc;
			iCnt++;
			if (iCnt >= iCount) break;
		}
	}else
	{	for(index = 0; index <= dy; index++)
		{	error += dx;
			if(error > dy)
			{	error -= dy;
				iResultX += x_inc;
			}
			iResultY += y_inc;
			iCnt++;
			if (iCnt >= iCount) break;
	}	}
	*pX = iResultX;
	*pY = iResultY;
	*pError = error;
}


void CMisc::GetDirPoint(char cDir, int * pX, int * pY)
{	switch(cDir) {
	case 1:	*pY--; break;
	case 2:	*pY--; *pX++;	break;
	case 3:	*pX++; break;
	case 4:	*pX++; *pY++;	break;
	case 5:	*pY++; break;
	case 6:	*pX--; *pY++;	break;
	case 7:	*pX--; break;
	case 8:	*pX--; *pY--;	break;
	}
}

BOOL CMisc::bCheckValidString(char * str)
{	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{	if(str[i] == ' ') return FALSE;
	}
	return TRUE;
}

BOOL CMisc::bCheckIMEString(char * str)
{	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{	if(str[i] < 0) return FALSE;
	}
	return TRUE;
}

void CMisc::ReplaceString(char * pStr, char cFrom, char cTo)
{	int len = strlen(pStr);
	for (int i = 0; i < len; i++)
	{	if (pStr[i] == cFrom) pStr[i] = cTo;
	}
}

char CMisc::cCalcDirection(short sX, short sY, short dX, short dY)
{double dTmp1, dTmp2, dTmp3;
// short x,y;
// double r;
	if ((sX == dX) && (sY == dY)) return 1;
	if ((sX == dX) && (sY != dY))
	{	if (sY > dY) return 1;
		else return 5;
	}
	if ((sX != dX) && (sY == dY))
	{	if (sX > dX) return 7;
		else return 3;
	}
	dTmp1 = (double)(dX - sX);
	dTmp2 = (double)(dY - sY);
	dTmp3 = dTmp1 / dTmp2;
	if (dTmp3 < -3)
	{	if (sX > dX) return 7;
		else return 3;
	}
	if (dTmp3 > 3)
	{	if (sX > dX) return 7;
		else return 3;
	}
	if ((dTmp3 > -0.3333f) && (dTmp3 <= 0.3333f))
	{	if (sY > dY) return 1;
		else return 5;
	}
	if ((dTmp3 > 0.3333f) && (dTmp3 <= 3.0f))
	{	if (sX > dX) return 8;
		else return 4;
	}
	if ((dTmp3 >= -0.3333f) && (dTmp3 < 3.0f))
	{	if (sX > dX) return 7;
		else return 3;
	}
	if ((dTmp3 >= -3.0f) && (dTmp3 < -0.3333f))
	{	if (sX > dX) return 6;
		else return 2;
	}
	return 1;
}

void CMisc::ColorTransfer(char cPixelFormat, COLORREF fcolor, WORD * wR, WORD * wG, WORD * wB)
{ WORD result = 0x0000;
	switch(cPixelFormat) {
	case 1:
		// R
		result = result|(WORD)((fcolor&0x000000f8)<<8);
		// G
		result = result|(WORD)((fcolor&0x0000fc00)>>5);
		// B
		result = result|(WORD)((fcolor&0x00f80000)>>19);
		break;

	case 2:
		// R
		result = result|(WORD)((fcolor&0x000000f8)<<7);
		// G
		result = result|(WORD)((fcolor&0x0000f800)>>6);
		// B
		result = result|(WORD)((fcolor&0x00f80000)>>19);
		break;
	}
	switch(cPixelFormat) {
	case 1:
		*wR = (result&0xF800) >> 11;
		*wG = (result&0x7E0) >> 5;
		*wB = (result&0x1F);
		break;

	case 2:
		*wR = (result&0x7C00) >> 10;
		*wG = (result&0x3E0) >> 5;
		*wB = (result&0x1F);
		break;
	}
}


BOOL CMisc::bEncode(char cKey, char *pStr)
{	int iLen = strlen(pStr);
	for (int i = 0; i <= iLen-1; i++)
	{	pStr[i] += i;
		pStr[i]  = pStr[i] ^ (cKey ^ (iLen - i));
	}
	return TRUE;
}


BOOL CMisc::bDecode(char cKey, char *pStr)
{int iLen = strlen(pStr);
	for (int i = 0; i <= iLen-1; i++)
	{	pStr[i]  = pStr[i] ^ (cKey ^ (iLen - i));
		pStr[i] -= i;
	}
	return TRUE;
}


BOOL CMisc::bCheckValidName(char *pStr)
{int i, iLen;
 iLen = strlen(pStr);
	for (i = 0; i < iLen; i++)
	{	if ( pStr[i] < 0 )	return FALSE;
		if ( (pStr[i] == ',')  || (pStr[i] == '=') || (pStr[i] == ' ')  || (pStr[i] == '\n') ||
			 (pStr[i] == '\t') || (pStr[i] == '.') || (pStr[i] == '\\') || (pStr[i] == '/')  ||
			 (pStr[i] == ':')  || (pStr[i] == '*') || (pStr[i] == '?')  || (pStr[i] == '<')  ||
			 (pStr[i] == '>')  || (pStr[i] == '|') || (pStr[i] == '"')  || (pStr[i] == '`')  ||
			 (pStr[i] == ';')  || (pStr[i] == '=') || (pStr[i] == '@')  || (pStr[i] == '[')  ||
			 (pStr[i] == ']')  || (pStr[i] == '^') || (pStr[i] == '_')  || (pStr[i] == '\'') ) return FALSE;
		if( (pStr[i] < '0') || (pStr[i] > 'z')) return FALSE;
	}
	return TRUE;
}


int CMisc::_iGetFileCheckSum(char * pFn)
{	HANDLE hFile;
	FILE * pFile;
	DWORD  dwFileSize;
	char * pContents;
	int    iCheckSum, iV1, iV2, iV3;
	UINT i;
	char cRealFn[512];
	ZeroMemory(cRealFn, sizeof(cRealFn));
	strcpy(cRealFn, pFn);
	for (i = 0; i < strlen(cRealFn); i++)
	if (cRealFn[i] != NULL)	cRealFn[i]++;

	hFile = CreateFile(cRealFn, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);//CreateFile(cRealFn, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	CloseHandle(hFile);
	if (hFile == INVALID_HANDLE_VALUE) {
		return 0;
	}

	pFile = fopen(cRealFn, "rb");
	if (pFile == NULL) return 0;
	else {
		pContents = new char[dwFileSize+1];
		ZeroMemory(pContents, dwFileSize+1);
		fread(pContents, 1, dwFileSize, pFile);
		fclose(pFile);
	}

	iCheckSum = 0;

	iV1 = (int)pContents[dwFileSize/2];
	iV2 = (int)pContents[dwFileSize/2 - (dwFileSize/2)/2];
	iV3 = (int)pContents[dwFileSize/2 + (dwFileSize/2)/2];

	iCheckSum = iV1+iV2+iV3;

	delete[] pContents;
	return abs(iCheckSum);
}

BOOL CMisc::_iConvertFileXor(char *pFn, char * pDestFn, char cKey)
{
 HANDLE hFile;
 DWORD  dwFileSize;
 FILE * pFile;
 char * pContents;
 int    i;
 //	.mando
 char pHeader[10];
 char cHeaderKey = 20;
	hFile = CreateFile(pFn, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL) - 10;
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);
	pFile = fopen(pFn, "rt");
	if (pFile == NULL)
		return FALSE;

	pContents = new char[dwFileSize+1];
	ZeroMemory(pContents, dwFileSize+1);
	ZeroMemory(pHeader, 10);
	fread(pHeader, 10, 1, pFile);
	fread(pContents, dwFileSize, 1, pFile);
	fclose(pFile);
	for (i = 0; i < (int)(dwFileSize); i++)
		pContents[i] = pContents[i] ^ cKey;
	pFile = fopen(pDestFn, "wt");
	if (pFile == NULL) {
		delete[] pContents;
		return FALSE;
	}
	//=======================================	mando..
	i = 0;
	while(pHeader[i])
	{	pHeader[i] = pHeader[i] ^ cHeaderKey;
		i++;
	}
	if(atoi(pHeader) != (int)(dwFileSize))
		return FALSE;
	fwrite(pContents, dwFileSize, 1, pFile);
	fclose(pFile);

	delete pContents;

	return TRUE;
}

int CMisc::iGetTextLengthLoc(HDC hDC, char *pStr, int iLength)
{
 int i;
 BOOL bFlag;
 SIZE Size;
 int len = strlen(pStr);

	i = 0;
	bFlag = FALSE;
	while (bFlag == FALSE) {
		if (i > len) return 0;
		i++;
		GetTextExtentPoint32(hDC, pStr, i, &Size);
		if (Size.cx > iLength) bFlag = TRUE;
	}
	return i;
}


BOOL CMisc::bIsValidSSN(char *pStr)
{int a, b, c, d, e, f, g, h, i, j, k, l, m, X, Y;
	if (strlen(pStr) < 14) return FALSE;
	a = pStr[0] - 48;
	b = pStr[1] - 48;
	c = pStr[2] - 48;
	d = pStr[3] - 48;
	e = pStr[4] - 48;
	f = pStr[5] - 48;
	g = pStr[7] - 48;
	h = pStr[8] - 48;
	i = pStr[9] - 48;
	j = pStr[10] - 48;
	k = pStr[11] - 48;
	l = pStr[12] - 48;
	m = pStr[13] - 48;
	X = (a*2) + (b*3) + (c*4) + (d*5) + (e*6) + (f*7) + (g*8) + (h*9) + (i*2) + (j*3) + (k*4) + (l*5);
	Y = X % 11;
	Y = 11 - Y;
	if (Y >= 10) Y = Y - 10;
	if (Y != m) return FALSE;
	return TRUE;
}

BOOL CMisc::bIsValidEmail(char *pStr)
{
	int len = strlen( pStr );
	if( len < 7 ) return FALSE;
	char cEmail[52];
	ZeroMemory( cEmail, sizeof(cEmail) );
	memcpy( cEmail, pStr, len );
	BOOL bFlag = FALSE;
	for( int i=0 ; i<len ; i++ )
	{
		if( cEmail[i] == '@' ) bFlag = TRUE;
	}
	if( bFlag == FALSE ) return FALSE;
	bFlag = FALSE;
	for( i=0 ; i<len ; i++ )
	{
		if( cEmail[i] == '.' ) bFlag = TRUE;
	}
	if( bFlag == FALSE ) return FALSE;
	return TRUE;
}
// v351 codded by D.u.u.u.d.e.&.S.n.o.o.p.y.8.1
#ifdef DEF_ANTI_HACK
/*********************************************************************************************************************
**  void CGame:EnumProcHack(HWND hWnd, long lp)	( Snoopy )															**
**  description			: 	Check if forbiden precesses running 													**
**********************************************************************************************************************/
bool __stdcall EnumProcHack(HWND hWnd, long lp)
{   if(hWnd==NULL)  return false;
    unsigned long* pPid;   //LPDWORD
    unsigned long result;  //DWORD
    void *hg;              //HGLOBAL
    char title[110];
    char utitle[111];
	WORD i;

 char cSearch1[] = "RodDcDqmS"; // SPEEDERNT
 char cSearch2[] = "RodDcDqwO"; // SPEEDERXP
 char cSearch3[] = "@RodDcDq";  // ASPEEDER
 char cSearch4[] = "Srd@Qbg";   // TSEARCH
 char cSearch5[] = "VodoQn";    // WPEPRO
 //char cSearch6[] = "rd`qbg-ckk"; // search.dll
 char cRealName[12];
 char *pJammer = new char[(rand() % 100) +1];

 int *presult = (int *)lp;
    hg = GlobalAlloc(GMEM_SHARE,sizeof(unsigned long));
    pPid = (unsigned long *)GlobalLock(hg);
    result = GetWindowThreadProcessId(hWnd,pPid);
    if(result)
    {   GetWindowText(hWnd,title,110);
		strcpy (utitle, _strupr( title ));
		
		// SPEEDERNT
		ZeroMemory(cRealName, sizeof(cRealName));
		strcpy(cRealName, _strupr(cSearch1));
		for (i = 0; i < strlen(cRealName); i++)
		{	if (cRealName[i] != NULL) cRealName[i]++;
		}
        if (strstr(title, cRealName) != NULL) *presult = 1;
		
		// SPEEDERXP
		ZeroMemory(cRealName, sizeof(cRealName));
		strcpy(cRealName, _strupr(cSearch2));
		for (i = 0; i < strlen(cRealName); i++)
		{	if (cRealName[i] != NULL) cRealName[i]++;
		}
        if (strstr(title, cRealName) != NULL) *presult = 2;

		// ASPEEDER
		ZeroMemory(cRealName, sizeof(cRealName));
		strcpy(cRealName, _strupr(cSearch3));
		for (i = 0; i < strlen(cRealName); i++)
		{	if (cRealName[i] != NULL) cRealName[i]++;
		}
        if (strstr(title, cRealName) != NULL) *presult = 3;


		// TSEARCH
		ZeroMemory(cRealName, sizeof(cRealName));
		strcpy(cRealName, _strupr(cSearch4));
		for (i = 0; i < strlen(cRealName); i++)
		{	if (cRealName[i] != NULL) cRealName[i]++;
		}
        if (strstr(title, cRealName) != NULL) *presult = 4;


		// WPEPRO
		ZeroMemory(cRealName, sizeof(cRealName));
		strcpy(cRealName, _strupr(cSearch5));
		for (i = 0; i < strlen(cRealName); i++)
		{	if (cRealName[i] != NULL) cRealName[i]++;
		}
        if (strstr(title, cRealName) != NULL) *presult = 5;
    }else
    {   GlobalUnlock(hg);
        GlobalFree(hg);		
		delete[] pJammer;
        return false;
    };
    GlobalUnlock(hg);
    GlobalFree(hg);	
	delete[] pJammer;
    return true;
}
bool CMisc::CheckProcesses2() // Vicieux, sert à blocquer le CCM, d'ou une detection hack par serveur.
{	// recherche windows
	long lp;
	int iresult = 0;
	int *presult = &iresult;
	lp = (long)presult;
    EnumWindows((WNDENUMPROC)EnumProcHack, lp);
	if (iresult !=0) return (TRUE); // True => hacker!
    return (FALSE); 
}
#endif
