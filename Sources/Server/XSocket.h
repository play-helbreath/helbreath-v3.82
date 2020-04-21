// XSocket.h: interface for the XSocket class.
//
//////////////////////////////////////////////////////////////////////

// Çì´õÀÇ È®ÀÎÄÚµå´Â 1¹ÙÀÌÆ®, Å©±â´Â WORD·Î º¯°æµÇ¾úÀ½. Áï Çì´õ´Â ÃÑ 3¹ÙÀÌÆ® 


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

#define DEF_XSOCKEVENT_SOCKETMISMATCH			-121	// ¼ÒÄÏ ÀÌº¥Æ®¿Í ¼ÒÄÏÀÌ ¼­·Î ´Ù¸£´Ù. (ÀÌ·± °æ¿ì°¡?)
#define DEF_XSOCKEVENT_CONNECTIONESTABLISH		-122	// Á¢¼ÓÀÌ ÀÌ·ç¾î Á³´Ù.
#define DEF_XSOCKEVENT_RETRYINGCONNECTION		-123	// Á¢¼ÓÀ» ´Ù½Ã ½ÃµµÇÏ´Â ÁßÀÌ´Ù.
#define DEF_XSOCKEVENT_ONREAD					-124	// ¸Þ½ÃÁö¸¦ ÀÐ´Â ÁßÀÌ´Ù. 
#define DEF_XSOCKEVENT_READCOMPLETE				-125	// ÇÏ³ªÀÇ ¸Þ½ÃÁö¸¦ ¿ÏÀüÈ÷ ¼ö½ÅÇß´Ù.
#define DEF_XSOCKEVENT_UNKNOWN					-126	// ¾Ë¼ö¾ø´Â ÀÌº¥Æ®ÀÌ´Ù.
#define DEF_XSOCKEVENT_SOCKETCLOSED				-127	// ¼ÒÄÏÀÌ ´ÝÇû´Ù. 
#define DEF_XSOCKEVENT_BLOCK					-128	// ¸Þ½ÃÁö¸¦ º¸³»´Ù°¡ ¼ÒÄÏÀÌ ºí·°µÈ »óÅÂÀÌ´Ù.
#define DEF_XSOCKEVENT_SOCKETERROR				-129	// ¼ÒÄÏ¿¡ ¿¡·¯°¡ ¹ß»ýÇß´Ù. ÀÌ°æ¿ì Å¬·¡½º¸¦ »èÁ¦ÇÏ¿©¾ß ÇÑ´Ù.
#define DEF_XSOCKEVENT_CRITICALERROR			-130    // Ä¡¸íÀûÀÎ ¿¡·¯·Î ÇÁ·Î±×·¥ ÀüÃ¼°¡ ¸ØÃç¾ß ÇÑ´Ù.
#define DEF_XSOCKEVENT_NOTINITIALIZED			-131	// Å¬·¡½º°¡ ÃÊ±âÈ­ µÇÁö ¾ÊÀº »óÅÂ·Î »ç¿ëµÆ´Ù.
#define DEF_XSOCKEVENT_MSGSIZETOOLARGE			-132	// º¸³»°íÀÚ ÇÏ´Â ¸Þ½ÃÁöÀÇ »çÀÌÁî°¡ ³Ê¹« Å©´Ù.
#define DEF_XSOCKEVENT_CONFIRMCODENOTMATCH		-133	// È®ÀÎÄÚµå°¡ ÀÏÄ¡ÇÏÁö ¾Ê´Â´Ù. »èÁ¦µÇ¾î¾ß ÇÑ´Ù.
#define DEF_XSOCKEVENT_QUENEFULL                -134    // ºí·Ï Å¥ÀÇ °ø°£ÀÌ ¾ø´Ù.
#define DEF_XSOCKEVENT_UNSENTDATASENDBLOCK		-135    // Å¥¿¡ ÀÖ´Â µ¥ÀÌÅÍ¸¦ º¸³»´Ù°¡ ¶Ç ºí·ÏÀÌ °É·È´Ù. 
#define DEF_XSOCKEVENT_UNSENTDATASENDCOMPLETE	-136	// Å¥¿¡ ÀÖ´Â ¸ðµç µ¥ÀÌÅÍ¸¦ º¸³Â´Ù.

#define DEF_XSOCKBLOCKLIMIT						300		// ÀÌ Å¬·¡½º ¼ÒÄÏÀº ?¹øÀÌ»ó ºí·ÏµÇ¸é ´õÀÌ»ó µ¥ÀÌÅÍ¸¦ ÀúÀåÇÒ ¼ö ¾ø´Ù. 	

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
