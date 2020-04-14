// DXC_ddraw.cpp: implementation of the DXC_ddraw class.
//
//////////////////////////////////////////////////////////////////////

#include <string.h>
#include <objbase.h>
#include "DXC_ddraw.h"

extern HWND G_hEditWnd;
extern HWND G_hWnd;

extern long    G_lTransG100[64][64], G_lTransRB100[64][64];
extern long    G_lTransG70[64][64], G_lTransRB70[64][64];
extern long    G_lTransG50[64][64], G_lTransRB50[64][64];
extern long    G_lTransG25[64][64], G_lTransRB25[64][64];
extern long    G_lTransG2[64][64], G_lTransRB2[64][64];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DXC_ddraw::DXC_ddraw()
{
	m_lpFrontB4		= NULL;
	m_lpDD4			= NULL;
	m_lpPDBGS		= NULL;
	m_lpBackB4flip	= NULL;
	m_cPixelFormat	= 0;

#ifdef DEF_WINDOWED_MODE	
	m_bFullMode		= FALSE;
#else
	m_bFullMode		= TRUE;
#endif

}

DXC_ddraw::~DXC_ddraw()
{
	if (m_hFontInUse != NULL) DeleteObject(m_hFontInUse);
	if (m_lpBackB4flip != NULL) m_lpBackB4flip->Release();
	if (m_lpBackB4 != NULL) m_lpBackB4->Release();
	if (m_lpFrontB4 != NULL) m_lpFrontB4->Release();
	if (m_bFullMode == TRUE)
	{
		if (m_lpDD4 != NULL) m_lpDD4->RestoreDisplayMode();
	}
	if (m_lpDD4 != NULL) m_lpDD4->Release();
}

BOOL DXC_ddraw::bInit(HWND hWnd)
{
 HRESULT        ddVal;
 DDSURFACEDESC2 ddsd;
 int            iS, iD;

	SetRect(&m_rcClipArea, 0,0, 640, 480);

	ddVal = DirectDrawCreateEx(NULL, (VOID**)&m_lpDD4, IID_IDirectDraw7, NULL);
    if (ddVal != DD_OK) return FALSE;

	if( m_bFullMode == TRUE )
	{
		DDSCAPS2       ddscaps;
		ddVal = m_lpDD4->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
		if (ddVal != DD_OK) return FALSE;

		ddVal = m_lpDD4->SetDisplayMode(640, 480, 16,0,0);
		if (ddVal != DD_OK) return FALSE;
		memset( (VOID *)&ddsd, 0, sizeof(ddsd) );
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.dwBackBufferCount = 1;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		
		ddVal = m_lpDD4->CreateSurface(&ddsd, &m_lpFrontB4, NULL);
		if (ddVal != DD_OK) return FALSE;

		ZeroMemory(&ddscaps, sizeof(ddscaps));
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		ddVal = m_lpFrontB4->GetAttachedSurface(&ddscaps, &m_lpBackB4flip);
		if (ddVal != DD_OK) return FALSE;
		SetRect(&m_rcFlipping, 0, 0, 640, 480); // our fictitious sprite bitmap is 
	}
	else
	{
		int cx = GetSystemMetrics(SM_CXFULLSCREEN);
		int cy = GetSystemMetrics(SM_CYFULLSCREEN);

		ddVal = m_lpDD4->SetCooperativeLevel(hWnd, DDSCL_NORMAL);
		if (ddVal != DD_OK) return FALSE;
		
		cx = cx/2;
		cy = cy/2;
		if(cy>280) cy -= 40;
		SetWindowPos( hWnd, HWND_TOP, cx-320, cy-240, 640, 480, SWP_SHOWWINDOW);
		memset( (VOID *)&ddsd, 0, sizeof(ddsd) );
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS;
		//ddsd.dwBackBufferCount = 0;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		
		ddVal = m_lpDD4->CreateSurface(&ddsd, &m_lpFrontB4, NULL);
		if (ddVal != DD_OK) return FALSE;

		SetRect(&m_rcFlipping, cx-320, cy-240, cx+320, cy+240); // our fictitious sprite bitmap is 
	}

	InitFlipToGDI(hWnd);
	m_lpBackB4 = pCreateOffScreenSurface(640, 480);
	if (m_lpBackB4 == NULL) return FALSE;

	// Pre-draw background surface
	m_lpPDBGS = pCreateOffScreenSurface(640+32, 480+32);
	if (m_lpPDBGS == NULL) return FALSE;

	ddsd.dwSize = sizeof(ddsd);
	if (m_lpBackB4->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL) != DD_OK) return FALSE;
	m_pBackB4Addr        = (WORD *)ddsd.lpSurface;
	m_sBackB4Pitch       = (short)ddsd.lPitch >> 1;
	m_lpBackB4->Unlock(NULL);

	_TestPixelFormat();
	for (iS = 0; iS < 64; iS++)
	for (iD = 0; iD < 64; iD++) {
		m_lTransRB100[iD][iS] = _CalcMaxValue(iS, iD, 'R', 1, 1.0f);
		m_lTransG100[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 1, 1.0f);

		m_lTransRB70[iD][iS] = _CalcMaxValue(iS, iD, 'R', 1, 0.7f);
		m_lTransG70[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 1, 0.7f);
		
		m_lTransRB50[iD][iS] = _CalcMaxValue(iS, iD, 'R', 1, 0.5f);
		m_lTransG50[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 1, 0.5f);

		m_lTransRB25[iD][iS] = _CalcMaxValue(iS, iD, 'R', 1, 0.25f);
		m_lTransG25[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 1, 0.25f);

		m_lTransRB2[iD][iS] = _CalcMaxValue(iS, iD, 'R', 2, 1.0f);
		m_lTransG2[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 2, 1.0f);

		m_lFadeRB[iD][iS]  = _CalcMinValue(iS, iD, 'R');
		m_lFadeG[iD][iS]   = _CalcMinValue(iS, iD, 'G');

		G_lTransRB100[iD][iS] = _CalcMaxValue(iS, iD, 'R', 1, 1.0f);
		G_lTransG100[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 1, 1.0f);

		G_lTransRB70[iD][iS] = _CalcMaxValue(iS, iD, 'R', 1, 0.7f);
		G_lTransG70[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 1, 0.7f);
		
		G_lTransRB50[iD][iS] = _CalcMaxValue(iS, iD, 'R', 1, 0.5f);
		G_lTransG50[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 1, 0.5f);

		G_lTransRB25[iD][iS] = _CalcMaxValue(iS, iD, 'R', 1, 0.25f);
		G_lTransG25[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 1, 0.25f);

		G_lTransRB2[iD][iS] = _CalcMaxValue(iS, iD, 'R', 2, 1.0f);
		G_lTransG2[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 2, 1.0f);
	}

	m_hFontInUse = NULL;	
	m_hFontInUse = CreateFont(16,0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, VARIABLE_PITCH, "Comic Sans MS") ;
	m_hDC = NULL;
		
	return TRUE;
}

HRESULT DXC_ddraw::iFlip()
{
	HRESULT ddVal;
	
	if( m_bFullMode )
	{
#ifdef DEF_USING_WIN_IME
		ddVal = m_lpFrontB4->Blt( NULL, m_lpBackB4, NULL, DDBLT_WAIT, NULL );
		if (G_hEditWnd != NULL) {
			if (ddVal != DDERR_SURFACELOST) m_lpDD4->FlipToGDISurface();
		}
#else

		ddVal = m_lpBackB4flip->BltFast( 0, 0, m_lpBackB4, &m_rcFlipping, DDBLTFAST_NOCOLORKEY); // | DDBLTFAST_WAIT);
		ddVal = m_lpFrontB4->Flip(m_lpBackB4flip, DDFLIP_WAIT);

#endif
	}
	else
	{
		//SetRect( &m_rcFlipping, 0, 0, 1152, 864 );
		ddVal = m_lpFrontB4->Blt(&m_rcFlipping, m_lpBackB4, NULL, DDBLT_WAIT, NULL);
	}

	if (ddVal == DDERR_SURFACELOST) {
		DDSURFACEDESC2 ddsd2;
		m_lpFrontB4->Restore();
		m_lpBackB4->Restore();
		
		ddsd2.dwSize = sizeof(ddsd2);
		if (m_lpBackB4->Lock(NULL, &ddsd2, DDLOCK_WAIT, NULL) != DD_OK) return FALSE;
		m_pBackB4Addr  = (WORD *)ddsd2.lpSurface;
		m_lpBackB4->Unlock(NULL);

		return DDERR_SURFACELOST;
	}
	return DD_OK;
}

void DXC_ddraw::ChangeDisplayMode(HWND hWnd)
{
	HRESULT        ddVal;
	DDSURFACEDESC2 ddsd;

	if (m_lpBackB4flip != NULL)
	{
		m_lpBackB4flip->Release();
		m_lpBackB4flip = NULL;
	}
	if (m_lpBackB4 != NULL) m_lpBackB4->Release();
	if (m_lpFrontB4 != NULL) m_lpFrontB4->Release();
	if (m_lpDD4 != NULL)
	{
		if (m_bFullMode == TRUE) m_lpDD4->RestoreDisplayMode();
	}

	if( m_bFullMode == TRUE )
	{
		int cx = GetSystemMetrics(SM_CXFULLSCREEN);
		int cy = GetSystemMetrics(SM_CYFULLSCREEN);

		ddVal = m_lpDD4->SetCooperativeLevel(hWnd, DDSCL_NORMAL);
		if (ddVal != DD_OK) return;

		cx = cx/2;
		cy = cy/2;
		if(cy>280) cy -= 40;
		SetWindowPos( hWnd, NULL, cx-320, cy-240, 640, 480, SWP_SHOWWINDOW);

		memset( (VOID *)&ddsd, 0, sizeof(ddsd) );
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS;
		//ddsd.dwBackBufferCount = 0;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		
		ddVal = m_lpDD4->CreateSurface(&ddsd, &m_lpFrontB4, NULL);
		if (ddVal != DD_OK) return;

		SetRect(&m_rcFlipping, cx-320, cy-240, cx+320, cy+240); // our fictitious sprite bitmap is 
		m_bFullMode = FALSE;
	}
	else
	{
		DDSCAPS2       ddscaps;
		ddVal = m_lpDD4->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
		if (ddVal != DD_OK) return;

		ddVal = m_lpDD4->SetDisplayMode(640, 480, 16,0,0);
		if (ddVal != DD_OK) return;
		memset( (VOID *)&ddsd, 0, sizeof(ddsd) );
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.dwBackBufferCount = 1;//2; //v1.3
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		
		ddVal = m_lpDD4->CreateSurface(&ddsd, &m_lpFrontB4, NULL);
		if (ddVal != DD_OK) return;

		ZeroMemory(&ddscaps, sizeof(ddscaps));
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		ddVal = m_lpFrontB4->GetAttachedSurface(&ddscaps, &m_lpBackB4flip);
		if (ddVal != DD_OK) return;
		SetRect(&m_rcFlipping, 0, 0, 640, 480); // our fictitious sprite bitmap is 
		m_bFullMode = TRUE;
	}
	InitFlipToGDI(hWnd);
	m_lpBackB4 = pCreateOffScreenSurface(640, 480);
	if (m_lpBackB4 == NULL) return;

	// Pre-draw background surface
	m_lpPDBGS = pCreateOffScreenSurface(640+32, 480+32);
	if (m_lpPDBGS == NULL) return;

	ddsd.dwSize = sizeof(ddsd);
	if (m_lpBackB4->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL) != DD_OK) return;
	m_pBackB4Addr        = (WORD *)ddsd.lpSurface;
	m_sBackB4Pitch       = (short)ddsd.lPitch >> 1;
	m_lpBackB4->Unlock(NULL);
}

IDirectDrawSurface7 * DXC_ddraw::pCreateOffScreenSurface(WORD wSzX, WORD wSzY)
{
	DDSURFACEDESC2 ddsd;
	IDirectDrawSurface7 * pdds4;

    ZeroMemory(&ddsd, sizeof(ddsd));
	if ((wSzX % 4) != 0) wSzX += 4 - (wSzX % 4);
    ddsd.dwSize  = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth  = (DWORD)wSzX;
    ddsd.dwHeight = (DWORD)wSzY;
    if (m_lpDD4->CreateSurface(&ddsd, &pdds4, NULL) != DD_OK) return NULL;
	return pdds4;
}

HRESULT DXC_ddraw::iSetColorKey(IDirectDrawSurface7 * pdds4, COLORREF rgb)
{
 DDCOLORKEY ddck;

	ddck.dwColorSpaceLowValue  = _dwColorMatch(pdds4, rgb);
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
    return pdds4->SetColorKey(DDCKEY_SRCBLT, &ddck);
}

HRESULT DXC_ddraw::iSetColorKey(IDirectDrawSurface7 * pdds4, WORD wColorKey)
{
 DDCOLORKEY ddck;

	ddck.dwColorSpaceLowValue  = _dwColorMatch(pdds4, wColorKey);
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
    return pdds4->SetColorKey(DDCKEY_SRCBLT, &ddck);
}

DWORD DXC_ddraw::_dwColorMatch(IDirectDrawSurface7 * pdds4, COLORREF rgb)
{
 COLORREF rgbT;
 HDC hdc;
 DWORD dw = CLR_INVALID;
 DDSURFACEDESC2 ddsd2;
 HRESULT hres;

    if (rgb != CLR_INVALID && pdds4->GetDC(&hdc) == DD_OK)
    {
        rgbT = GetPixel(hdc, 0, 0);             
        SetPixel(hdc, 0, 0, rgb);               
        pdds4->ReleaseDC(hdc);
    }

    ddsd2.dwSize = sizeof(ddsd2);
    while ((hres = pdds4->Lock(NULL, &ddsd2, 0, NULL)) == DDERR_WASSTILLDRAWING);

    if (hres == DD_OK)
    {
        dw  = *(DWORD *)ddsd2.lpSurface;                     
        dw &= (1 << ddsd2.ddpfPixelFormat.dwRGBBitCount)-1;  
        pdds4->Unlock(NULL);
    }

    if (rgb != CLR_INVALID && pdds4->GetDC(&hdc) == DD_OK)
    {
        SetPixel(hdc, 0, 0, rgbT);
        pdds4->ReleaseDC(hdc);
    }

    return dw;
}

DWORD DXC_ddraw::_dwColorMatch(IDirectDrawSurface7 * pdds4, WORD wColorKey)
{
 DWORD dw = CLR_INVALID, * dwp;
 DDSURFACEDESC2 ddsd2;
 HRESULT hres;
   
    ddsd2.dwSize = sizeof(ddsd2);
    while ((hres = pdds4->Lock(NULL, &ddsd2, 0, NULL)) == DDERR_WASSTILLDRAWING);

    if (hres == DD_OK)
    {
        dwp = (DWORD *)ddsd2.lpSurface;
		*dwp = (DWORD)wColorKey;
		dw  = *(DWORD *)ddsd2.lpSurface;                     
        dw &= (1 << ddsd2.ddpfPixelFormat.dwRGBBitCount)-1;  
        pdds4->Unlock(NULL);
    }

    return dw;
}

void DXC_ddraw::TextOut(int x, int y, char * cStr, COLORREF rgb)
{
	SetTextColor(m_hDC, rgb );
	::TextOut(m_hDC, x, y, cStr, strlen(cStr));
}

void DXC_ddraw::_TestPixelFormat()
{
 DDSURFACEDESC2 ddSurfaceDesc2;
 HRESULT       hResult;

	ZeroMemory(&ddSurfaceDesc2, sizeof(DDSURFACEDESC2));
	ddSurfaceDesc2.dwSize  = sizeof(ddSurfaceDesc2);
	ddSurfaceDesc2.dwFlags = DDSD_PIXELFORMAT;
	hResult                = m_lpBackB4->GetSurfaceDesc(&ddSurfaceDesc2);

	if (hResult == DD_OK)
	{
	   if (ddSurfaceDesc2.ddpfPixelFormat.dwRBitMask == 0x0000F800) {
		   m_cPixelFormat = 1;
		  // RGB 5:6:5
	   }
	   if (ddSurfaceDesc2.ddpfPixelFormat.dwRBitMask == 0x00007C00) {
		   m_cPixelFormat = 2;
		  // RGB 5:5:5 
	   }
	   if (ddSurfaceDesc2.ddpfPixelFormat.dwRBitMask == 0x0000001F) {
		   m_cPixelFormat = 3;
		  // BGR 5:6:5 
	   }
	}
}

long DXC_ddraw::_CalcMaxValue(int iS, int iD, char cMode, char cMethod, double dAlpha)
{
 long Sum;
 double dTmp;
 
	switch (cMethod) {
	case 1:
		dTmp = (double)iS;
		dTmp = dTmp * dAlpha;
		iS = (int)dTmp;
		Sum = (iS) + (iD);
		if (Sum < iD) Sum = iD;
		break;

	case 2:
		Sum = (iS + iD) / 2;
		break;
	}

	switch (cMode) {
	case 'G':
		switch (m_cPixelFormat) {
		case 1:
			if (Sum >= 64) Sum = 63; //v1.3
			break;
		case 2:
			if (Sum >= 32) Sum = 31;
			break;
		}
		break;
	
	default:
		if (Sum >= 32) Sum = 31;
		break;
	}

	return Sum;
}

long DXC_ddraw::_CalcMinValue(int iS, int iD, char cMode)
{
 long Sum;

 
	Sum = iD - iS;
	if (Sum < 0) Sum = 0;

	switch (cMode) {
	case 'G':
		switch (m_cPixelFormat) {
		case 1:
			if (Sum >= 64) Sum = 63;
			break;
		case 2:
			if (Sum >= 32) Sum = 31;
			break;
		}
		break;
	
	default:
		if (Sum >= 32) Sum = 31;
		break;
	}

	return Sum;
}

void DXC_ddraw::ClearBackB4()
{
	DDSURFACEDESC2 ddsd2;	
	ddsd2.dwSize = sizeof(ddsd2);
	if (m_lpBackB4->Lock(NULL, &ddsd2, DDLOCK_WAIT, NULL) != DD_OK) return;
	memset((char *)ddsd2.lpSurface, 0, ddsd2.lPitch * 480);
	m_lpBackB4->Unlock(NULL);
}

void DXC_ddraw::DrawShadowBox(short sX, short sY, short dX, short dY, int iType)
{
	WORD * pDst, wValue;
	int ix, iy;

	pDst = (WORD *)m_pBackB4Addr + sX + ((sY)*m_sBackB4Pitch);

	if (iType == 0) {
		switch (m_cPixelFormat) {
		case 1:
			for (iy = 0; iy <= (dY - sY); iy++) {
				for (ix = 0; ix <= (dX - sX); ix++) 
					pDst[ix] = (pDst[ix] & 0xf7de) >> 1; 	
			
				pDst += m_sBackB4Pitch;
			}
			break;

		case 2:
			for (iy = 0; iy <= (dY - sY); iy++) {
				for (ix = 0; ix <= (dX - sX); ix++) 
					pDst[ix] = (pDst[ix] & 0x7bde) >> 1;
				
				pDst += m_sBackB4Pitch;
			}
			break;
		}
	}
	else 
	{
		switch (iType) {
		case 1:
			if (m_cPixelFormat == 1) 
				 wValue = 0x38e7;
			else wValue = 0x1ce7;
			break;

		case 2:
			if (m_cPixelFormat == 1) 
				 wValue = 0x1863;
			else wValue = 0xc63;
			break;
		}
		
		for (iy = 0; iy <= (dY - sY); iy++) {
			for (ix = 0; ix <= (dX - sX); ix++) 
				pDst[ix] = wValue; 	
				
			pDst += m_sBackB4Pitch;
		}
	}
}

void DXC_ddraw::PutPixel(short sX, short sY, WORD wR, WORD wG, WORD wB)
{
 WORD * pDst;

	if ((sX < 0) || (sY < 0) || (sX > 639) || (sY > 479)) return;

	pDst = (WORD *)m_pBackB4Addr + sX + ((sY)*m_sBackB4Pitch);
	
	switch (m_cPixelFormat) {
	case 1:
		*pDst = (WORD)( ((wR>>3)<<11) | ((wG>>2)<<5) | (wB>>3) );
		//*pDst = (WORD)((wR<<11) | (wG<<5) | wB);
		break;
	case 2:
		*pDst = (WORD)( ((wR>>3)<<10) | ((wG>>3)<<5) | (wB>>3) );
		//*pDst = (WORD)((wR<<10) | (wG<<5) | wB);
		break;
	}
}

void DXC_ddraw::_GetBackBufferDC()
{
	m_lpBackB4->GetDC(&m_hDC);
	SelectObject(m_hDC, m_hFontInUse);
	SetBkMode(m_hDC, TRANSPARENT);
	SetBkColor(m_hDC, RGB(0,0,0));
}

void DXC_ddraw::_ReleaseBackBufferDC()
{
	m_lpBackB4->ReleaseDC(m_hDC);
}

void DXC_ddraw::DrawText(LPRECT pRect, char *pString, COLORREF rgb)
{
	SetTextColor(m_hDC, rgb);
	::DrawText(m_hDC, pString, strlen(pString), pRect, DT_CENTER | DT_NOCLIP | DT_WORDBREAK | DT_NOPREFIX);//v2.15
}

HRESULT DXC_ddraw::InitFlipToGDI(HWND hWnd)
{
 LPDIRECTDRAWCLIPPER pClipper;
 HRESULT hr;
 DDCAPS ddcaps;

    ZeroMemory( &ddcaps, sizeof(ddcaps) );
    ddcaps.dwSize = sizeof(ddcaps);
    m_lpDD4->GetCaps( &ddcaps, NULL );

    if( (ddcaps.dwCaps2 & DDCAPS2_CANRENDERWINDOWED) == 0 )
    {
        // This means FlipToGDISurface() is not supported, so to display GDI 
        // on these cards, you you must create a bitmap of the GDI window 
        // and BitBlt the bitmap to the backbuffer then flip as normal. However,
        // this specific sample does not show this. 
        return E_FAIL;
    }

    // Create a clipper when using GDI to draw on the primary surface 
    if( FAILED( hr = m_lpDD4->CreateClipper( 0, &pClipper, NULL ) ) )
        return hr;

    pClipper->SetHWnd( 0, hWnd );

    if( FAILED( hr = m_lpFrontB4->SetClipper( pClipper ) ) ) return hr;

    // We can release the clipper now since g_pDDSPrimary 
    // now maintains a ref count on the clipper
	if( pClipper )
	{
		pClipper->Release();
		pClipper = NULL;
	}
    return S_OK;
}

void DXC_ddraw::ColorTransferRGB(COLORREF fcolor, int * iR, int * iG, int * iB)
{
 WORD wR, wG, wB;

	switch(m_cPixelFormat)
	{
	case 1:
		// R
		wR = (WORD)((fcolor&0x000000f8)>>3);
		// G
		wG = (WORD)((fcolor&0x0000fc00)>>10);
		// B
		wB = (WORD)((fcolor&0x00f80000)>>19);
		*iR = (int)wR;
		*iG = (int)wG;
		*iB = (int)wB;
		break;
	case 2:
		// R
		wR = (WORD)((fcolor&0x000000f8)>>3);
		// G
		wG = (WORD)((fcolor&0x0000f800)>>11);
		// B
		wB = (WORD)((fcolor&0x00f80000)>>19);
		*iR = (int)wR;
		*iG = (int)wG;
		*iB = (int)wB;
		break;
	}
}

//---------------------------------------------------------------------------

bool DXC_ddraw::Screenshot(LPCTSTR FileName, LPDIRECTDRAWSURFACE7 lpDDS)
{
    if (!FileName || !lpDDS) return false;

    bool Success=false;
    HDC SurfDC=NULL;        // GDI-compatible device context for the surface
    HBITMAP OffscrBmp=NULL; // bitmap that is converted to a DIB
    HDC OffscrDC=NULL;      // offscreen DC that we can select OffscrBmp into
    LPBITMAPINFO lpbi=NULL; // bitmap format info; used by GetDIBits
    LPVOID lpvBits=NULL;    // pointer to bitmap bits array
    HANDLE BmpFile=INVALID_HANDLE_VALUE;    // destination .bmp file
    BITMAPFILEHEADER bmfh;  // .bmp file header

try
{
    // Get dimensions of Surface:
    DDSURFACEDESC2 ddsd;
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    if (FAILED(lpDDS->GetSurfaceDesc(&ddsd))) throw 0;
    int Width = ddsd.dwWidth;
    int Height = ddsd.dwHeight;

    // Create a GDI-compatible device context for the surface:
    if (FAILED(lpDDS->GetDC(&SurfDC))) throw 1;

    // We need an HBITMAP to convert it to a DIB:
    if ((OffscrBmp = CreateCompatibleBitmap(SurfDC, Width, Height)) == NULL)
        throw 2;

    // The bitmap is empty, so let's copy the contents of the surface to it.
    // For that we need to select it into a device context. We create one.
    if ((OffscrDC = CreateCompatibleDC(SurfDC)) == NULL) throw 3;
    // Select OffscrBmp into OffscrDC:
    HBITMAP OldBmp = (HBITMAP)SelectObject(OffscrDC, OffscrBmp);
    // Now we can copy the contents of the surface to the offscreen bitmap:
    BitBlt(OffscrDC, 0, 0, Width, Height, SurfDC, 0, 0, SRCCOPY);

    // We don't need SurfDC anymore. Free it:
    lpDDS->ReleaseDC(SurfDC); SurfDC = NULL;

    // GetDIBits requires format info about the bitmap. We can have GetDIBits
    // fill a structure with that info if we pass a NULL pointer for lpvBits:
    // Reserve memory for bitmap info (BITMAPINFOHEADER + largest possible
    // palette):
    if ((lpbi = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) +
        256 * sizeof(RGBQUAD)])) == NULL) throw 4;
    ZeroMemory(&lpbi->bmiHeader, sizeof(BITMAPINFOHEADER));
    lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    // Get info but first de-select OffscrBmp because GetDIBits requires it:
    SelectObject(OffscrDC, OldBmp);
    if (!GetDIBits(OffscrDC, OffscrBmp, 0, Height, NULL, lpbi, DIB_RGB_COLORS))
        throw 5;

    // Reserve memory for bitmap bits:
    if ((lpvBits = new char[lpbi->bmiHeader.biSizeImage]) == NULL)
        throw 6;

    // Have GetDIBits convert OffscrBmp to a DIB (device-independent bitmap):
    if (!GetDIBits(OffscrDC, OffscrBmp, 0, Height, lpvBits, lpbi,
        DIB_RGB_COLORS)) throw 7;

    // Create a file to save the DIB to:
    if ((BmpFile = CreateFile(FileName,
                              GENERIC_WRITE,
                              0, NULL,
                              CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL)) == INVALID_HANDLE_VALUE) throw 8;

    DWORD Written;    // number of bytes written by WriteFile
    
    // Write a file header to the file:
    bmfh.bfType = 19778;        // 'BM'
    // bmfh.bfSize = ???        // we'll write that later
    bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
    // bmfh.bfOffBits = ???     // we'll write that later
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        throw 9;
    if (Written < sizeof(bmfh)) throw 9;

    // Write BITMAPINFOHEADER to the file:
    if (!WriteFile(BmpFile, &lpbi->bmiHeader, sizeof(BITMAPINFOHEADER),
        &Written, NULL)) throw 10;
    if (Written < sizeof(BITMAPINFOHEADER)) throw 10;

    // Calculate size of palette:
    int PalEntries;
    // 16-bit or 32-bit bitmaps require bit masks:
    if (lpbi->bmiHeader.biCompression == BI_BITFIELDS) PalEntries = 3;
    else
        // bitmap is palettized?
        PalEntries = (lpbi->bmiHeader.biBitCount <= 8) ?
            // 2^biBitCount palette entries max.:
            (int)(1 << lpbi->bmiHeader.biBitCount)
        // bitmap is TrueColor -> no palette:
        : 0;
    // If biClrUsed use only biClrUsed palette entries:
    if (lpbi->bmiHeader.biClrUsed) PalEntries = lpbi->bmiHeader.biClrUsed;

    // Write palette to the file:
    if (PalEntries)
    {
        if (!WriteFile(BmpFile, &lpbi->bmiColors, PalEntries * sizeof(RGBQUAD),
            &Written, NULL)) throw 11;
        if (Written < PalEntries * sizeof(RGBQUAD)) throw 11;
    }

    // The current position in the file (at the beginning of the bitmap bits)
    // will be saved to the BITMAPFILEHEADER:
    bmfh.bfOffBits = SetFilePointer(BmpFile, 0, 0, FILE_CURRENT);

    // Write bitmap bits to the file:
    if (!WriteFile(BmpFile, lpvBits, lpbi->bmiHeader.biSizeImage,
        &Written, NULL)) throw 12;
    if (Written < lpbi->bmiHeader.biSizeImage) throw 12;

    // The current pos. in the file is the final file size and will be saved:
    bmfh.bfSize = SetFilePointer(BmpFile, 0, 0, FILE_CURRENT);

    // We have all the info for the file header. Save the updated version:
    SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        throw 13;
    if (Written < sizeof(bmfh)) throw 13;
	OutputDebugString("Screenshot Success\r\n");
    Success = true;
}
catch (int &errorcode)
{
    char Buf[100];
    wsprintf(Buf, "Screenshot error #%i\r\n", errorcode);
    OutputDebugString(Buf);
}
catch (...)
{
    OutputDebugString("Screenshot error\r\n");
}

    if (SurfDC) lpDDS->ReleaseDC(SurfDC);
    if (OffscrDC) DeleteDC(OffscrDC);
    if (OffscrBmp) DeleteObject(OffscrBmp);
    if (lpbi) delete[] lpbi;
    if (lpvBits) delete[] lpvBits;
    if (BmpFile != INVALID_HANDLE_VALUE) CloseHandle(BmpFile);
    
    return Success;
}
//---------------------------------------------------------------------------