#include <windows.h>

#define MSG_RECV 1
#define MSG_SEND 2

class CDebugWindow
{

public:
	CDebugWindow();
	// Startups The Debug Dialog
	void Startup(void);
	void Shutdown(void);
	void AddEventMsg(char* cMsg);
	void AddEventMsg(int cMsgType, char* cData, DWORD dwSize, char cKey);
	void ShowWindow(bool isVisible);
private:
	bool m_isVisible;
};