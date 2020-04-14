// winmain.h

BOOL InitApplication( HINSTANCE hInstance);
BOOL InitInstance( HINSTANCE hInstance, int nCmdShow );
LRESULT CALLBACK WndProc( HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam );
void EventLoop();
void OnDestroy();
void Initialize(char * pCmdLine);
void CALLBACK _TimerFunc(UINT wID, UINT wUser, DWORD dwUSer, DWORD dw1, DWORD dw2);
MMRESULT _StartTimer(DWORD dwTime);

void _StopTimer(MMRESULT timerid);
void CPSocketConnet() ;
LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);
void GoHomepage();

// Snoopy
char G_cCrashTxt[50000];
char G_cVersionTxt[1024];
#include "Game.h"	//20030220 mando..