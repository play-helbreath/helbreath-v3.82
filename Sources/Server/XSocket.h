// XSocket.h: interface for the XSocket class.
//
//////////////////////////////////////////////////////////////////////

// 헤더의 확인코드는 1바이트, 크기는 WORD로 변경되었음. 즉 헤더는 총 3바이트 


#if !defined(AFX_XSOCKET_H__F9D1BA42_7338_11D2_A8E6_00001C7030A6__INCLUDED_)
#define AFX_XSOCKET_H__F9D1BA42_7338_11D2_A8E6_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define _WINSOCK2API_
//#define  FD_SETSIZE 2000
#include <windows.h>
#include <windowsx.h>
#include <winsock2.h>
//#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include "DebugDialog.h"
#include <iostream>
#include <strstream>
#include <string>

#define DEF_XSOCK_LISTENSOCK			1
#define DEF_XSOCK_NORMALSOCK			2				
#define DEF_XSOCK_SHUTDOWNEDSOCK		3				

#define DEF_XSOCKSTATUS_READINGHEADER	11
#define DEF_XSOCKSTATUS_READINGBODY		12

#define DEF_XSOCKEVENT_SOCKETMISMATCH			-121	// 소켓 이벤트와 소켓이 서로 다르다. (이런 경우가?)
#define DEF_XSOCKEVENT_CONNECTIONESTABLISH		-122	// 접속이 이루어 졌다.
#define DEF_XSOCKEVENT_RETRYINGCONNECTION		-123	// 접속을 다시 시도하는 중이다.
#define DEF_XSOCKEVENT_ONREAD					-124	// 메시지를 읽는 중이다. 
#define DEF_XSOCKEVENT_READCOMPLETE				-125	// 하나의 메시지를 완전히 수신했다.
#define DEF_XSOCKEVENT_UNKNOWN					-126	// 알수없는 이벤트이다.
#define DEF_XSOCKEVENT_SOCKETCLOSED				-127	// 소켓이 닫혔다. 
#define DEF_XSOCKEVENT_BLOCK					-128	// 메시지를 보내다가 소켓이 블럭된 상태이다.
#define DEF_XSOCKEVENT_SOCKETERROR				-129	// 소켓에 에러가 발생했다. 이경우 클래스를 삭제하여야 한다.
#define DEF_XSOCKEVENT_CRITICALERROR			-130    // 치명적인 에러로 프로그램 전체가 멈춰야 한다.
#define DEF_XSOCKEVENT_NOTINITIALIZED			-131	// 클래스가 초기화 되지 않은 상태로 사용됐다.
#define DEF_XSOCKEVENT_MSGSIZETOOLARGE			-132	// 보내고자 하는 메시지의 사이즈가 너무 크다.
#define DEF_XSOCKEVENT_CONFIRMCODENOTMATCH		-133	// 확인코드가 일치하지 않는다. 삭제되어야 한다.
#define DEF_XSOCKEVENT_QUENEFULL                -134    // 블록 큐의 공간이 없다.
#define DEF_XSOCKEVENT_UNSENTDATASENDBLOCK		-135    // 큐에 있는 데이터를 보내다가 또 블록이 걸렸다. 
#define DEF_XSOCKEVENT_UNSENTDATASENDCOMPLETE	-136	// 큐에 있는 모든 데이터를 보냈다.

#define DEF_XSOCKBLOCKLIMIT						300		// 이 클래스 소켓은 ?번이상 블록되면 더이상 데이터를 저장할 수 없다. 	

class XSocket  
{
public:
	int iGetPeerAddress(char * pAddrString);
	char * pGetRcvDataPointer(DWORD * pMsgSize, char * pKey = NULL);
	SOCKET iGetSocket();
	BOOL bAccept(class XSocket * pXSock, unsigned int uiMsg);
	BOOL bListen(char * pAddr, int iPort, unsigned int uiMsg);

	int iSendMsg(char * cData, DWORD dwSize, char cKey = NULL);
	BOOL bConnect(char * pAddr, int iPort, unsigned int uiMsg);
	int  iOnSocketEvent(WPARAM wParam, LPARAM lParam);
	BOOL bInitBufferSize(DWORD dwBufferSize);
	XSocket(HWND hWnd, int iBlockLimit);
	virtual ~XSocket();

	int  m_WSAErr;
	BOOL m_bIsAvailable;

private:
	void _CloseConn();
	
	int _iSendUnsentData();
	int _iRegisterUnsentData(char * cData, int iSize);
	int _iSend(char * cData, int iSize, BOOL bSaveFlag);
	int _iSend_ForInternalUse(char * cData, int iSize);
	int _iOnRead();
	
	char   m_cType;
	char * m_pRcvBuffer;
	char * m_pSndBuffer;
	DWORD  m_dwBufferSize;
	int    m_iPortNum;
	
	SOCKET m_Sock;
	char   m_cStatus;
	DWORD  m_dwReadSize;
	DWORD  m_dwTotalReadSize;
	char   m_pAddr[30];

	char * m_pUnsentDataList[DEF_XSOCKBLOCKLIMIT];
	int    m_iUnsentDataSize[DEF_XSOCKBLOCKLIMIT];
	short  m_sHead, m_sTail;

	unsigned int m_uiMsg;
	HWND         m_hWnd;

	int			 m_iBlockLimit;
};


BOOL _InitWinsock();
void _TermWinsock();

#endif // !defined(AFX_XSOCKET_H__F9D1BA42_7338_11D2_A8E6_00001C7030A6__INCLUDED_)
