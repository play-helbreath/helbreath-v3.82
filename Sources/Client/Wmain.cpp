// -------------------------------------------------------------- 
//                      Helbreath Client 						  
//
//                      1998.10 by Soph
//
// --------------------------------------------------------------


#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h> 
#include <winbase.h>
#include <mmsystem.h>
#include <process.h>
#include "resource.h"
#include "XSocket.h"
#include "winmain.h"
#include "Game.h"
#include "GlobalDef.h"
#include "mp3.h"

extern "C" __declspec( dllimport) int __FindHackingDll__(char *);

// --------------------------------------------------------------

#define WM_USER_TIMERSIGNAL		WM_USER + 500
#define WM_USER_CALCSOCKETEVENT WM_USER + 600

int				G_iAddTable31[64][510], G_iAddTable63[64][510]; 
int				G_iAddTransTable31[510][64], G_iAddTransTable63[510][64]; 

long    G_lTransG100[64][64], G_lTransRB100[64][64];
long    G_lTransG70[64][64], G_lTransRB70[64][64];
long    G_lTransG50[64][64], G_lTransRB50[64][64];
long    G_lTransG25[64][64], G_lTransRB25[64][64];
long    G_lTransG2[64][64], G_lTransRB2[64][64];

char			szAppClass[32];
HWND			G_hWnd = NULL;
HWND			G_hEditWnd = NULL;
HINSTANCE       G_hInstance = NULL;
MMRESULT		G_mmTimer;
char   G_cSpriteAlphaDegree;
class CGame * G_pGame;
class XSocket * G_pCalcSocket = NULL;
BOOL  G_bIsCalcSocketConnected = TRUE;
DWORD G_dwCalcSocketTime = NULL, G_dwCalcSocketSendTime = NULL;

char G_cCmdLine[256], G_cCmdLineTokenA[120], G_cCmdLineTokenA_Lowercase[120], G_cCmdLineTokenB[120], G_cCmdLineTokenC[120], G_cCmdLineTokenD[120], G_cCmdLineTokenE[120];


// --------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam, LPARAM lParam)
{ 
	if(G_pGame->GetText( hWnd, message, wParam, lParam)) return 0;

	switch (message) {
	case WM_USER_CALCSOCKETEVENT:
		G_pGame->_CalcSocketClosed();
		break;
	
	case WM_CLOSE:
		if ( (G_pGame->m_cGameMode == DEF_GAMEMODE_ONMAINGAME) && ( G_pGame->m_bForceDisconn == FALSE ) )
		{

#ifdef _DEBUG
			if (G_pGame->m_cLogOutCount == -1 || G_pGame->m_cLogOutCount > 2) G_pGame->m_cLogOutCount = 1; 
#else
			if (G_pGame->m_cLogOutCount == -1 || G_pGame->m_cLogOutCount > 11) G_pGame->m_cLogOutCount = 11; 
#endif

		}
			else if (G_pGame->m_cGameMode == DEF_GAMEMODE_ONLOADING) return (DefWindowProc(hWnd, message, wParam, lParam));
			else if (G_pGame->m_cGameMode == DEF_GAMEMODE_ONMAINMENU) G_pGame->ChangeGameMode(DEF_GAMEMODE_ONQUIT);
		break;
	
	case WM_SYSCOMMAND:
		if((wParam&0xFFF0)==SC_SCREENSAVE || (wParam&0xFFF0)==SC_MONITORPOWER) 
			return 0; 
		return DefWindowProc(hWnd, message, wParam, lParam);
			
	case WM_USER_TIMERSIGNAL:
		G_pGame->OnTimer();
		break;

	case WM_KEYDOWN:
		G_pGame->OnKeyDown(wParam);
		return (DefWindowProc(hWnd, message, wParam, lParam));
		
	case WM_KEYUP:
		G_pGame->OnKeyUp(wParam);
		return (DefWindowProc(hWnd, message, wParam, lParam));

	case WM_SYSKEYDOWN:
		G_pGame->OnSysKeyDown(wParam);
		return (DefWindowProc(hWnd, message, wParam, lParam));
		break;

	case WM_SYSKEYUP:
		G_pGame->OnSysKeyUp(wParam);
		return (DefWindowProc(hWnd, message, wParam, lParam));
		break;

	case WM_ACTIVATEAPP:
		if( wParam == 0 ) 
		{	G_pGame->m_bIsProgramActive = FALSE;
			G_pGame->m_DInput.SetAcquire(FALSE);

			// Snoopy: mp3 support
			if (G_pGame->m_bMusicStat == TRUE)
			{	G_pGame->PauseBGM(); // If music running, pause it
			}else
			{	G_pGame->StopBGM();	 // 
			}			
		}else 
		{	G_pGame->m_bIsProgramActive = TRUE;
			G_pGame->m_DInput.SetAcquire(TRUE);
			G_pGame->m_bCtrlPressed = FALSE;

			// Snoopy: mp3 support
			if (G_pGame->m_bMusicStat == TRUE)
			{	G_pGame->ResumeBGM(); // If music running, resume it it
			}else
			{	G_pGame->StopBGM();	 // 
			}			
			if (G_pGame->bCheckImportantFile() == FALSE) 
			{	MessageBox(G_pGame->m_hWnd, "File checksum error! Get Update again please!", "ERROR1", MB_ICONEXCLAMATION | MB_OK);
				PostQuitMessage(0);
				return 0;
			}			
			if (__FindHackingDll__("CRCCHECK") != 1) 
			{	G_pGame->ChangeGameMode(DEF_GAMEMODE_ONQUIT);
				return NULL;
		}	}
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;

	case WM_SETCURSOR:
		SetCursor(NULL);
		return TRUE;

	case WM_DESTROY:
		OnDestroy();
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
		
	case WM_USER_GAMESOCKETEVENT:
		G_pGame->OnGameSocketEvent(wParam, lParam);
		break;

	case WM_USER_LOGSOCKETEVENT:
		G_pGame->OnLogSocketEvent(wParam, lParam);
		break;

	// Snoopy: mp3 support
	case WM_USER_MP3_EVENT:
		G_pGame->LoopBGM();
		break;
		
	default: 
		return (DefWindowProc(hWnd, message, wParam, lParam));
	}	
	return NULL;
}
//////////////////////////////////////////////////////////////////////////////
///		Crash log
///	
//////////////////////////////////////////////////////////////////////////////
void GetOSName()
{	OSVERSIONINFOEX osvi;
	BOOL bOsVersionInfoEx;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
	{	osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
		if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) ) return;
	}
	//OS Info
	ZeroMemory(G_cVersionTxt, sizeof(G_cVersionTxt));
	strcat(G_cVersionTxt, "Operating System information:\r\n");
	switch (osvi.dwPlatformId)	{// Test for the Windows NT product family.
	case VER_PLATFORM_WIN32_NT:
		// Test for the specific product family.
		if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
			strcat(G_cVersionTxt,"Microsoft Windows Server 2003 family, ");
		if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
			strcat(G_cVersionTxt,"Microsoft Windows XP ");
		if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
			strcat(G_cVersionTxt,"Microsoft Windows 2000 ");
		if ( osvi.dwMajorVersion <= 4 )
			strcat(G_cVersionTxt,"Microsoft Windows NT 4");
		// ServicePack
		wsprintf(&G_cVersionTxt[strlen(G_cVersionTxt)], " %s (Build %d)\r\n",
			osvi.szCSDVersion,
			osvi.dwBuildNumber & 0xFFFF);
		break;	
	case VER_PLATFORM_WIN32_WINDOWS:	// Test for the Windows 95 product family.
		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
		{	strcat(G_cVersionTxt,"Microsoft Windows 95 ");
			if ( osvi.szCSDVersion[1] == 'C' || osvi.szCSDVersion[1] == 'B' )
				strcat(G_cVersionTxt,"OSR2 " );
		} 
		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
		{	strcat(G_cVersionTxt,"Microsoft Windows 98 ");
			if ( osvi.szCSDVersion[1] == 'A' )
				strcat(G_cVersionTxt,"SE " );
		} 
		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
		{	strcat(G_cVersionTxt,"Microsoft Windows Millennium Edition\r\n");
		} 
		break;
	case VER_PLATFORM_WIN32s:
		strcat(G_cVersionTxt,"Microsoft Win32s\r\n");
		break;
	}
} 

LONG lpTopLevelExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo)
{	ZeroMemory(G_cCrashTxt, sizeof(G_cCrashTxt));

	// Client information:
	strcpy(G_cCrashTxt, "\r\nClient information:\r\nWorld server name : ");
	strcat(G_cCrashTxt, G_pGame->m_cAccountName);
	strcat(G_cCrashTxt, "\r\nClient's name        : ");
	strcat(G_cCrashTxt, G_pGame->m_cPlayerName);
	strcat(G_cCrashTxt, "\r\nClient's map          : ");
	strcat(G_cCrashTxt, G_pGame->m_cMapName);
	strcat(G_cCrashTxt, "\r\n\r\n\r\n");

	//Shutdown everything
	_StopTimer(G_mmTimer);
	try
	{	delete G_pGame;
		G_pGame = NULL;
	}catch (...) {}  

	// OS information:
	GetOSName();
	strcat(G_cCrashTxt, G_cVersionTxt);

	//Reason for crash
	strcat(G_cCrashTxt, "\r\n\r\nClient's Exception Information:");
	strcat(G_cCrashTxt, "\r\nCode : ");
//-- figure out which type of exception         
switch( ExceptionInfo->ExceptionRecord->ExceptionCode ) {            
//--standard exceptions           
case EXCEPTION_ACCESS_VIOLATION:   
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Access Violation)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);
    break;            
case EXCEPTION_DATATYPE_MISALIGNMENT:  
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Datatype Misalignment)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);           
	break;            
case EXCEPTION_BREAKPOINT:  
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Breakpoint)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);        
	 break;            
case EXCEPTION_SINGLE_STEP: 
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Single Step)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);            
	break;            
case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:  
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Array Bound Exceeded)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);           
	break;            
case EXCEPTION_FLT_DENORMAL_OPERAND: 
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Floating Point Denormal Operand)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);            
	break;            
case EXCEPTION_FLT_DIVIDE_BY_ZERO:    
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Floating Point Divide By Zero)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);        
	break;            
case EXCEPTION_FLT_INEXACT_RESULT: 
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Floating Point Inexact Result)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);            
	break;            
case EXCEPTION_FLT_INVALID_OPERATION: 
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Floating Point Invalid Operation)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);            
	break;            
case EXCEPTION_FLT_OVERFLOW: 
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Floating Point Overflow)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);            
	break;            
case EXCEPTION_FLT_STACK_CHECK: 
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Floating Point Stack Check)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);            
	break;            
case EXCEPTION_FLT_UNDERFLOW:    
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Floating Point Underflow)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);         
	break;           
 case EXCEPTION_INT_DIVIDE_BY_ZERO: 
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Integer Divide By Zero)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);            
	break;            
case EXCEPTION_INT_OVERFLOW:  
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Integer Overflow)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);           
	break;            
case EXCEPTION_PRIV_INSTRUCTION: 
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Privileged Instruction)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);            
	break;            
case EXCEPTION_IN_PAGE_ERROR:  
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (In Page Error)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);           
	break;            //-- Debug exceptions           
case DBG_TERMINATE_THREAD:   
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Terminate Thread)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);         
	break;            
case DBG_TERMINATE_PROCESS:   
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Terminate Process)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);          
	break;            
case DBG_CONTROL_C:  
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X(Control+C) \r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);           
	break;            
case DBG_CONTROL_BREAK: 
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Control+Break)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);           
	break;            
//-- RPC exceptions (some)           
case RPC_S_UNKNOWN_IF:   
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (RPC - Unknown Interface)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);          
	break;            
case RPC_S_SERVER_UNAVAILABLE: 
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (RPC - Server Unavailable)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);            
	break;
default:   
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X (Unknown)\r\n", ExceptionInfo->ExceptionRecord->ExceptionCode);
	break;	
}
	strcat(G_cCrashTxt, "Flags : ");
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X\r\n", ExceptionInfo->ExceptionRecord->ExceptionFlags);
	strcat(G_cCrashTxt, "Address : ");
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X\r\n", ExceptionInfo->ExceptionRecord->ExceptionAddress);
	strcat(G_cCrashTxt, "Parameters : ");
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "0x%.8X\r\n\r\n", ExceptionInfo->ExceptionRecord->NumberParameters);

	strcat(G_cCrashTxt, "\r\n");

	//Crash Details
	strcat(G_cCrashTxt, "Context :\r\n");
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "EDI: 0x%.8X\t\tESI: 0x%.8X\t\tEAX: 0x%.8X\r\n",ExceptionInfo->ContextRecord->Edi,
																						ExceptionInfo->ContextRecord->Esi,
																						ExceptionInfo->ContextRecord->Eax);
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "EBX: 0x%.8X\t\tECX: 0x%.8X\t\tEDX: 0x%.8X\r\n",ExceptionInfo->ContextRecord->Ebx,
																						ExceptionInfo->ContextRecord->Ecx,
																						ExceptionInfo->ContextRecord->Edx);
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "EIP: 0x%.8X\t\tEBP: 0x%.8X\t\tSegCs: 0x%.8X\r\n",ExceptionInfo->ContextRecord->Eip,
																						ExceptionInfo->ContextRecord->Ebp,
																						ExceptionInfo->ContextRecord->SegCs);
	wsprintf(&G_cCrashTxt[strlen(G_cCrashTxt)], "EFlags: 0x%.8X\t\tESP: 0x%.8X\t\tSegSs: 0x%.8X\r\n",ExceptionInfo->ContextRecord->EFlags,
																						ExceptionInfo->ContextRecord->Esp,
																						ExceptionInfo->ContextRecord->SegSs);
	// SNOOPY: Tweacked Exeption handler to suit my needs
	HANDLE outHand;
	char cCrashFileName[MAX_PATH];
	char cLF[]={0x0d,0x0a};
	char cDash ='-';
	char cCrashTime[200];
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	ZeroMemory(cCrashTime, sizeof(cCrashTime));	
	wsprintf(cCrashTime, "%4d %2d %2d - %2d:%2d:%2d",  (short)sysTime.wYear, (short)sysTime.wMonth, (short)sysTime.wDay, (short)sysTime.wHour, (short)sysTime.wMinute, (short)sysTime.wSecond);
	wsprintf(cCrashFileName,"CrashData-%2d-%2d-%2dh%2dm.txt", sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute);

	DWORD written;
	//Open File For Writing
	outHand = CreateFile(cCrashFileName,GENERIC_READ+GENERIC_WRITE,FILE_SHARE_READ+FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	SetFilePointer(outHand, 0, 0, FILE_END);
	// Put Time
	WriteFile(outHand, cCrashTime, strlen(cCrashTime), &written, NULL);	
	// Put LF
	WriteFile(outHand, cLF, 2, &written, NULL);	
	// Put CrashText
	WriteFile(outHand, G_cCrashTxt, strlen(G_cCrashTxt), &written, NULL);
	// Put ----------------------------------
	for (int i = 0; i < 80; i++) WriteFile(outHand, &cDash, 1, &written, NULL);
	WriteFile(outHand, cLF, 2, &written, NULL);
	CloseHandle(outHand);

	return EXCEPTION_EXECUTE_HANDLER;
}


int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
               LPSTR lpCmdLine, int nCmdShow )
{HINSTANCE hDll;
 char cSearchDll[] = "rd`qbg-ckk";
 char cRealName[12];

	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)lpTopLevelExceptionFilter);
	srand((unsigned)time(NULL));
	char *pJammer = new char[(rand() % 100) +1];
	G_pGame = new class CGame;
	ZeroMemory(cRealName, sizeof(cRealName));
	strcpy(cRealName, cSearchDll);
	for (WORD i = 0; i < strlen(cRealName); i++)
	if (cRealName[i] != NULL) cRealName[i]++;

	hDll = LoadLibrary(cRealName);
	if( hDll == NULL ) 
	{	MessageBox(NULL, "don't find search.dll", "ERROR!", MB_OK);
		return 0;
	}

#ifdef DEF_USING_WIN_IME
	HINSTANCE hRichDll = LoadLibrary( "Riched20.dll" );
#endif

	typedef int (MYPROC)(char *) ;
	MYPROC *pFindHook; 
	pFindHook = (MYPROC *) GetProcAddress(hDll, "__FindHackingDll__") ;

	if (pFindHook== NULL) 
	{	MessageBox(NULL, "can't find search.dll", "ERROR!", MB_OK);
		return 0 ;
	}else if ((*pFindHook)("CRCCHECK") != 1) 
	{	return 0 ;
	}
	FreeLibrary(hDll);
	sprintf( szAppClass, "Client-I%d", hInstance);
	if (!InitApplication( hInstance))		return (FALSE);
    if (!InitInstance(hInstance, nCmdShow)) return (FALSE);

	Initialize((char *)lpCmdLine);
	// Snoopy: MP3 support
	Mp3Init();


#ifndef DEF_EQUILIBRIUM_PROJECT
#ifndef _DEBUG
	if (OpenMutex(MUTEX_ALL_ACCESS, FALSE, "0543kjg3j31%") != NULL) {
		MessageBox(NULL, "Only one Helbreath client program allowed!", "ERROR!", MB_OK);
		return 0;
	}
	HANDLE hMutex = CreateMutex(NULL, FALSE, "0543kjg3j31%");
#endif
#endif
	
	EventLoop();

#ifndef DEF_EQUILIBRIUM_PROJECT
#ifndef _DEBUG
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
#endif
#endif

	delete[] pJammer;
	delete G_pGame;

#ifdef DEF_USING_WIN_IME
	FreeLibrary(hRichDll);
#endif

	return 0;
}

BOOL InitApplication( HINSTANCE hInstance)
{WNDCLASS  wc;
	wc.style = (CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS);
	wc.lpfnWndProc   = (WNDPROC)WndProc;             
	wc.cbClsExtra    = 0;                            
	wc.cbWndExtra    = sizeof (int);
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadCursor(NULL, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = szAppClass;        
	return (RegisterClass(&wc));
}

BOOL InitInstance( HINSTANCE hInstance, int nCmdShow )
{	int cx = GetSystemMetrics(SM_CXFULLSCREEN)/2;
	int cy = GetSystemMetrics(SM_CYFULLSCREEN)/2;
	if(cy>280) cy -= 40;
	G_hWnd = CreateWindowEx(NULL, szAppClass, "Helbreath Crusade", WS_POPUP, cx-320, cy-240, 
							640, 480, NULL, NULL, hInstance, NULL);  
    if (!G_hWnd) return FALSE;
    G_hInstance	= hInstance;
	ShowWindow(G_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(G_hWnd);
	return TRUE;
}


void EventLoop()
{ register MSG msg;
	while( 1 ) 
	{	if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) ) 
		{	if( !GetMessage( &msg, NULL, 0, 0 ) ) return;// msg.wParam;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
		}
		else if (G_pGame->m_bIsProgramActive) G_pGame->UpdateScreen();
		else if (G_pGame->m_cGameMode == DEF_GAMEMODE_ONLOADING) G_pGame->UpdateScreen_OnLoading( FALSE );
		else WaitMessage();
	}
}

void OnDestroy()
{	G_pGame->m_bIsProgramActive = FALSE;		
	_StopTimer(G_mmTimer);
	G_pGame->Quit();
	WSACleanup();

	// Snoopy: MP3 support
	Mp3Cleanup();
	PostQuitMessage(0);
}

void CALLBACK _TimerFunc(UINT wID, UINT wUser, DWORD dwUSer, DWORD dw1, DWORD dw2)
{	PostMessage(G_hWnd, WM_USER_TIMERSIGNAL, wID, NULL);
}


MMRESULT _StartTimer(DWORD dwTime)
{TIMECAPS caps;
	timeGetDevCaps(&caps, sizeof(caps));
	timeBeginPeriod(caps.wPeriodMin);
	return timeSetEvent(dwTime,0,_TimerFunc,0, (UINT)TIME_PERIODIC);
}


void _StopTimer(MMRESULT timerid)
{TIMECAPS caps;
	if (timerid != 0) 
	{	timeKillEvent(timerid);
		timerid = 0;
		timeGetDevCaps(&caps, sizeof(caps));
		timeEndPeriod(caps.wPeriodMin);
	}
}


void Initialize(char * pCmdLine)
{int iX, iY, iSum;
 int     iErrCode;
 WORD	 wVersionRequested;
 WSADATA wsaData;
	wVersionRequested = MAKEWORD( 2, 2 ); 
	iErrCode = WSAStartup( wVersionRequested, &wsaData );
	if ( iErrCode ) 
	{	MessageBox(G_hWnd, "Winsock-V1.1 not found! Cannot execute program.","ERROR",MB_ICONEXCLAMATION | MB_OK);
		PostQuitMessage(0);
		return;
	}
	if (G_pGame->bInit(G_hWnd, G_hInstance, pCmdLine) == FALSE) 
	{	PostQuitMessage(0);
		return;
	}	
	G_mmTimer = _StartTimer(1000);
	for (iX = 0; iX < 64; iX++)
	for (iY = 0; iY < 510; iY++) 
	{	iSum = iX + (iY - 255);
		if (iSum <= 0)  iSum = 1;
		if (iSum >= 31) iSum = 31;
		G_iAddTable31[iX][iY] = iSum; 
		iSum = iX + (iY - 255);
		if (iSum <= 0)  iSum = 1;
		if (iSum >= 63) iSum = 63;
		G_iAddTable63[iX][iY] = iSum; 
		if ((iY - 255) < iX) G_iAddTransTable31[iY][iX] = iX;
		else if ((iY - 255) > 31) G_iAddTransTable31[iY][iX] = 31;
		else G_iAddTransTable31[iY][iX] = iY-255;
		if ((iY - 255) < iX) G_iAddTransTable63[iY][iX] = iX;
		else if ((iY - 255) > 63) G_iAddTransTable63[iY][iX] = 63;
		else G_iAddTransTable63[iY][iX] = iY-255;
	}
}

LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)
{   HKEY hkey;
    LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);
    if (retval == ERROR_SUCCESS) 
	{	long datasize = MAX_PATH;
        TCHAR data[MAX_PATH];
        RegQueryValue(hkey, NULL, data, &datasize);
        lstrcpy(retdata,data);
        RegCloseKey(hkey);
    }
    return retval;
}

void GoHomepage() 
{	LPCTSTR	url = MSG_HOMEPAGE;

#ifdef _DEBUG
	return;
#endif

	int		showcmd = SW_SHOW;
	char	key[MAX_PATH + MAX_PATH];	
    // First try ShellExecute()
    HINSTANCE result = ShellExecute(NULL, "open", url, NULL,NULL, showcmd);

    // If it failed, get the .htm regkey and lookup the program
    if ((UINT)result <= HINSTANCE_ERROR) 
	{  if (GetRegKey(HKEY_CLASSES_ROOT, ".htm", key) == ERROR_SUCCESS) 
		{  lstrcat(key, "\\shell\\open\\command");
            if (GetRegKey(HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS)
			{   char *pos;
                pos = strstr(key, "\"%1\"");
                if (pos == NULL) {                     // No quotes found
                    pos = strstr(key, "%1");           // Check for %1, without quotes 
                    if (pos == NULL)                   // No parameter at all...
                          pos = key+lstrlen(key)-1;
                    else *pos = '\0';                   // Remove the parameter
                }else    *pos = '\0';                   // Remove the parameter
                lstrcat(pos, " ");
                lstrcat(pos, url);
                result = (HINSTANCE) WinExec(key,showcmd);
    }	}	}
}
////////////////////////////////////////////////////////////////////////
