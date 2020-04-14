//MYDIB.CPP BMP
//#include <afx.h>
//#include <AfxWin.h>
#include <windows.h>
#include <stdio.h>
#include "mydib.h"

CMyDib::CMyDib(char *szFilename, unsigned long dwFilePointer)
{
	BITMAPFILEHEADER fh; //bmp 
	m_lpDib = NULL;	
	HANDLE hFileRead;
	DWORD nCount;
	char PathName[28];
	wsprintf( PathName, "sprites\\%s.pak", szFilename );
	hFileRead = CreateFile(PathName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	SetFilePointer(hFileRead, dwFilePointer, NULL, FILE_BEGIN);
	ReadFile(hFileRead, (char *)&fh, 14, &nCount, NULL);//sizeof(bmpHeader)==14
	m_lpDib = (LPSTR)new char[fh.bfSize-14];
	ReadFile(hFileRead, (char *)m_lpDib, fh.bfSize-14, &nCount, NULL);
	CloseHandle(hFileRead);
	LPBITMAPINFOHEADER bmpInfoHeader = (LPBITMAPINFOHEADER)m_lpDib;
	m_bmpInfo = (LPBITMAPINFO)m_lpDib;
	m_wWidthX = (WORD)(bmpInfoHeader->biWidth);
	m_wWidthY = (WORD)(bmpInfoHeader->biHeight);
	if (bmpInfoHeader->biClrUsed == 0)
	{	if(bmpInfoHeader->biBitCount == 24) m_wColorNums = 0;
		else if(bmpInfoHeader->biBitCount == 8) m_wColorNums = 256;
		else if(bmpInfoHeader->biBitCount == 1) m_wColorNums = 2;
		else if(bmpInfoHeader->biBitCount == 4) m_wColorNums = 16;
		else m_wColorNums = 0;
	}else m_wColorNums = (WORD)(bmpInfoHeader->biClrUsed);
}

CMyDib::~CMyDib()
{	if(m_lpDib != NULL) delete[] m_lpDib;
}

void CMyDib::PaintImage(HDC hDC)
{	if (m_lpDib == NULL) return;
	SetDIBitsToDevice(hDC, 0, 0, m_wWidthX, m_wWidthY, 0, 0, 0, m_wWidthY, m_lpDib + *(LPDWORD)m_lpDib + 4*m_wColorNums, m_bmpInfo, DIB_RGB_COLORS);
}

