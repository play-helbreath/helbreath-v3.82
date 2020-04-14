// XSocket.cpp: implementation of the XSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "XSocket.h"
#include "Client.h"
#include "winmain.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XSocket::XSocket(HWND hWnd, int iBlockLimit)
{
 register int i;
	
	m_cType       = NULL;
	m_pRcvBuffer  = NULL;
	m_pSndBuffer  = NULL;
	m_Sock        = INVALID_SOCKET;
	m_dwBufferSize = 0;

	m_cStatus   = DEF_XSOCKSTATUS_READINGHEADER;      
	m_dwReadSize = 3;    
	m_dwTotalReadSize = 0;

	for (i = 0; i < DEF_XSOCKBLOCKLIMIT; i++) {
		m_iUnsentDataSize[i] = 0;
		m_pUnsentDataList[i] = NULL;
	}
	
	m_sHead = 0;
	m_sTail = 0;

	m_WSAErr = NULL;

	m_hWnd = hWnd;
	m_bIsAvailable = FALSE;

	m_iBlockLimit = iBlockLimit;
}

XSocket::~XSocket()
{
 register int i;
	
	if (m_pRcvBuffer != NULL) delete m_pRcvBuffer;
	if (m_pSndBuffer != NULL) delete m_pSndBuffer;

	for (i = 0; i < DEF_XSOCKBLOCKLIMIT; i++)
		if (m_pUnsentDataList[i] != NULL) delete m_pUnsentDataList[i];

	// 소켓을 마저 읽고 닫는다.
	_CloseConn(); 
}

BOOL XSocket::bInitBufferSize(DWORD dwBufferSize)
{
	if (m_pRcvBuffer != NULL) delete m_pRcvBuffer;
	if (m_pSndBuffer != NULL) delete m_pSndBuffer;

	m_pRcvBuffer = new char[dwBufferSize+8];
	if (m_pRcvBuffer == NULL) return FALSE;
	
	m_pSndBuffer = new char[dwBufferSize+8];
	if (m_pSndBuffer == NULL) return FALSE;

	m_dwBufferSize = dwBufferSize;

	return TRUE;
}

int XSocket::iOnSocketEvent(WPARAM wParam, LPARAM lParam)
{
 int WSAEvent;

	// 리스닝 소켓의 이벤트는 처리할 수 없다.
	if (m_cType != DEF_XSOCK_NORMALSOCK) return DEF_XSOCKEVENT_SOCKETMISMATCH;
	// 초기화 되지 않아서 처리할 수 없다.
	if (m_cType == NULL) return DEF_XSOCKEVENT_NOTINITIALIZED;

	if ((SOCKET)wParam != m_Sock) return DEF_XSOCKEVENT_SOCKETMISMATCH;
	WSAEvent = WSAGETSELECTEVENT(lParam);

	switch (WSAEvent) {
	case FD_CONNECT:
		if (WSAGETSELECTERROR(lParam) != 0) { 
			// 이 소켓의 접속이 실패했으므로 재접속을 시도한다.
			if (bConnect(m_pAddr, m_iPortNum, m_uiMsg) == FALSE) return DEF_XSOCKEVENT_SOCKETERROR;
				
			return DEF_XSOCKEVENT_RETRYINGCONNECTION;
		}
		else {
			m_bIsAvailable = TRUE;
			return DEF_XSOCKEVENT_CONNECTIONESTABLISH;
		}
		break;

	case FD_READ:
		if (WSAGETSELECTERROR(lParam) != 0) { 
			// 읽는 도중 에러가 발생했다.
			m_WSAErr = WSAGETSELECTERROR(lParam);
			return DEF_XSOCKEVENT_SOCKETERROR;
		}
		else return _iOnRead();
		break;
	
	case FD_WRITE:
		return _iSendUnsentData();
		break;

	case FD_CLOSE:
		m_cType = DEF_XSOCK_SHUTDOWNEDSOCK; // 소켓이 닫혔으므로 이 소켓은 사용 불가능. 
		return DEF_XSOCKEVENT_SOCKETCLOSED;
		break;
	}

	return DEF_XSOCKEVENT_UNKNOWN;
}

BOOL XSocket::bConnect(char * pAddr, int iPort, unsigned int uiMsg)
{
 SOCKADDR_IN	 saTemp;
 u_long          arg;
 int             iRet;
 DWORD			 dwOpt;

	// 리스닝 소켓으로 초기화된 클래스는 이 함수를 사용할 수 없다.
	if (m_cType == DEF_XSOCK_LISTENSOCK) return FALSE;
	if (m_Sock  != INVALID_SOCKET) closesocket(m_Sock);

	m_Sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Sock == INVALID_SOCKET) 
		return FALSE;
	
	// 소켓을 논블록킹 모드로 
	arg = 1;
	ioctlsocket(m_Sock, FIONBIO, &arg);
	
	// 주소를 바인드한다.
	memset(&saTemp,0,sizeof(saTemp));
	saTemp.sin_family = AF_INET;
	saTemp.sin_addr.s_addr = inet_addr(pAddr);
	saTemp.sin_port = htons(iPort);
	
	iRet = connect(m_Sock, (struct sockaddr *) &saTemp, sizeof(saTemp));
	if (iRet == SOCKET_ERROR) {
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			m_WSAErr = WSAGetLastError();
			return FALSE;
		}
	}

	WSAAsyncSelect(m_Sock, m_hWnd, uiMsg, FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
	// 소켓 옵션을 조정한다. 
	dwOpt = 8192*5;
	setsockopt(m_Sock, SOL_SOCKET, SO_RCVBUF, (const char FAR *)&dwOpt, sizeof(dwOpt));
	setsockopt(m_Sock, SOL_SOCKET, SO_SNDBUF, (const char FAR *)&dwOpt, sizeof(dwOpt));


	strcpy(m_pAddr, pAddr);
	m_iPortNum = iPort;

	m_uiMsg = uiMsg;
	m_cType = DEF_XSOCK_NORMALSOCK;

	return TRUE;
}

int XSocket::_iOnRead()
{
 int iRet, WSAErr;
 WORD  * wp;	

	if (m_cStatus == DEF_XSOCKSTATUS_READINGHEADER) {
		
		iRet = recv(m_Sock, (char *)(m_pRcvBuffer + m_dwTotalReadSize), m_dwReadSize, 0);	
		
		if (iRet == SOCKET_ERROR) {
			WSAErr = WSAGetLastError();
			if (WSAErr != WSAEWOULDBLOCK) {
				m_WSAErr = WSAErr;
				return DEF_XSOCKEVENT_SOCKETERROR;
			}
			else return DEF_XSOCKEVENT_BLOCK;
		}
		else 
		if (iRet == 0) {
			// 소켓이 닫혔다. 
			m_cType = DEF_XSOCK_SHUTDOWNEDSOCK;
			return DEF_XSOCKEVENT_SOCKETCLOSED;
		}
		
		m_dwReadSize      -= iRet;
		m_dwTotalReadSize += iRet;
		
		if (m_dwReadSize == 0) {
			// 헤더를 다 읽었다. 
			m_cStatus = DEF_XSOCKSTATUS_READINGBODY;
			// 읽어야 할 몸체 사이즈를 계산한다.
			wp = (WORD *)(m_pRcvBuffer + 1);
			m_dwReadSize = (int)(*wp - 3); // 헤더 사이즈는 포함하지 않는다. 
			
			if (m_dwReadSize == 0) {
				// 몸체 사이즈가 0이면 몸체부분을 읽을 필요가 없으므로 
				m_cStatus        = DEF_XSOCKSTATUS_READINGHEADER;
				m_dwReadSize      = 3;
				m_dwTotalReadSize = 0;
				return DEF_XSOCKEVENT_READCOMPLETE;
			}
			else 
			if (m_dwReadSize > m_dwBufferSize) {
				m_cStatus        = DEF_XSOCKSTATUS_READINGHEADER;
				m_dwReadSize      = 3;
				m_dwTotalReadSize = 0;
				return DEF_XSOCKEVENT_MSGSIZETOOLARGE;
			}
		}
		return DEF_XSOCKEVENT_ONREAD;
	}
	else
	if (m_cStatus == DEF_XSOCKSTATUS_READINGBODY) {
		
		iRet = recv(m_Sock, (char *)(m_pRcvBuffer + m_dwTotalReadSize), m_dwReadSize, 0);
		
		if (iRet == SOCKET_ERROR) {
			WSAErr = WSAGetLastError();
			if (WSAErr != WSAEWOULDBLOCK) {
				m_WSAErr = WSAErr;
				return DEF_XSOCKEVENT_SOCKETERROR;
			}
			else return DEF_XSOCKEVENT_BLOCK;
		}
		else 
		if (iRet == 0) {
			// 소켓이 닫혔다. 
			m_cType = DEF_XSOCK_SHUTDOWNEDSOCK;
			return DEF_XSOCKEVENT_SOCKETCLOSED;
		}

		m_dwReadSize      -= iRet;
		m_dwTotalReadSize += iRet;
		
		if (m_dwReadSize == 0) {
			// 몸체를 다 읽었다. 다음번 이벤트를 위해 상태를 바꾼다. 
			m_cStatus        = DEF_XSOCKSTATUS_READINGHEADER;
			m_dwReadSize      = 3;
			m_dwTotalReadSize = 0;
		}
		else return DEF_XSOCKEVENT_ONREAD;
	}

	// 메시지를 모두 읽었다. 이 메시지를 받으면 클래스 버퍼의 내용을 읽어 즉각 처리해야 한다.
	return DEF_XSOCKEVENT_READCOMPLETE;
}



int XSocket::_iSend(char * cData, int iSize, BOOL bSaveFlag)
{
 int  iOutLen, iRet, WSAErr;

	if (m_pUnsentDataList[m_sHead] != NULL) {
		if (bSaveFlag == TRUE) {
			// 만약 대기열에 데이터가 남아 있고 꼭 보내야 하는 데이터라면 
			// 메시지의 순서를 맞추기 위해 무조건 대기열에 저장해야 한다. 
			iRet = _iRegisterUnsentData(cData, iSize);
			switch (iRet) {
			case -1:
				// 할당할 메모리가 없다. 이경우는 복구할 방법이 없다.
				return DEF_XSOCKEVENT_CRITICALERROR;
			case 0:
				// 큐가 가득찼다. 이 소켓 클래스는 삭제되어야만 한다.
				return DEF_XSOCKEVENT_QUENEFULL;
			case 1:
				// 정상적으로 데이터를 등록했다.
				break;
			}
			return DEF_XSOCKEVENT_BLOCK;
		}
		else return 0;
	}

	iOutLen = 0;
	while (iOutLen < iSize) {
		
		iRet = send(m_Sock, (cData + iOutLen), iSize - iOutLen, 0); 
		
		if (iRet == SOCKET_ERROR) {
			WSAErr = WSAGetLastError();
			if (WSAErr != WSAEWOULDBLOCK) {
				// 소켓에 에러가 발생했다.
				m_WSAErr = WSAErr;
				return DEF_XSOCKEVENT_SOCKETERROR;
			}
			else {
				// 블럭상태이면 더이상 보낼 수 없으므로 남아있는 데이터를 리스트에 등록하고 리턴 
				if (bSaveFlag == TRUE) {
					iRet = _iRegisterUnsentData((cData + iOutLen), (iSize - iOutLen));
					switch (iRet) {
					case -1:
						// 할당할 메모리가 없다. 이경우는 복구할 방법이 없다.
						return DEF_XSOCKEVENT_CRITICALERROR;
						break;
					case 0:
						// 큐가 가득찼다. 이 소켓 클래스는 삭제되어야만 한다.
						return DEF_XSOCKEVENT_QUENEFULL;
						break;
					case 1:
						// 정상적으로 데이터를 등록했다.
						break;
					}
				}
				return DEF_XSOCKEVENT_BLOCK;
			}
		} else iOutLen += iRet;
		
	}
	
	return iOutLen;
}


// 이 함수는 _SendUnsentData에서만 사용한다. 블록이 아닌 에러시에는 음수값을, 블럭상태를 포함한 전송상태에서는 보낸 만큼의 값을 반환.
int XSocket::_iSend_ForInternalUse(char * cData, int iSize)
{
 int  iOutLen, iRet, WSAErr;

	iOutLen = 0;
	while (iOutLen < iSize) {
		
		iRet = send(m_Sock, (cData + iOutLen), iSize - iOutLen, 0); 
		
		if (iRet == SOCKET_ERROR) {
			WSAErr = WSAGetLastError();
			if (WSAErr != WSAEWOULDBLOCK) {
				// 소켓에 에러가 발생했다.
				m_WSAErr = WSAErr;
				return DEF_XSOCKEVENT_SOCKETERROR;
			}
			else {
				// 블럭상태이면 더이상 보낼 수 없으므로 지금까지 보낸 데이터 사이즈만을 반환  
				return iOutLen;
			}
		} else iOutLen += iRet;
	}
	
	return iOutLen;
}



int XSocket::_iRegisterUnsentData(char * cData, int iSize)
{
	// 큐가 가득차서 더이상 데이터를 대기열에 저장할 수 없다.
	if (m_pUnsentDataList[m_sTail] != NULL) return 0;
	
	m_pUnsentDataList[m_sTail] = new char[iSize];
	if (m_pUnsentDataList[m_sTail] == NULL) return -1; // 메모리 할당에 실패했다.

	// 데이터 저장 
	memcpy(m_pUnsentDataList[m_sTail], cData, iSize);
	m_iUnsentDataSize[m_sTail] = iSize;

	// 테일 포인터 증가 
	m_sTail++;
	//if (m_sTail >= DEF_XSOCKBLOCKLIMIT) m_sTail = 0;
	if (m_sTail >= m_iBlockLimit) m_sTail = 0;

	return 1;
}



int XSocket::_iSendUnsentData()
{
 int iRet;
 char * pTemp;
	
	// 가능한 한 대기열의 데이터를 보낸다. 
	while (m_pUnsentDataList[m_sHead] != NULL) {
		
		iRet = _iSend_ForInternalUse(m_pUnsentDataList[m_sHead], m_iUnsentDataSize[m_sHead]);

		if (iRet == m_iUnsentDataSize[m_sHead]) {
			// Head큐의 데이터를 다 보냈다.	다음 데이터를 보낸다.
			delete m_pUnsentDataList[m_sHead];
			m_pUnsentDataList[m_sHead] = NULL;
			m_iUnsentDataSize[m_sHead] = 0;
			// 헤드 포인터 증가 
			m_sHead++;
			//if (m_sHead >= DEF_XSOCKBLOCKLIMIT) m_sHead = 0;
			if (m_sHead >= m_iBlockLimit) m_sHead = 0;
		}
		else {
			// 보내던 중 소켓 에러가 발생하면 그냥 리턴한다. (제거되야만 한다)
			if (iRet < 0) 
				return iRet;

			// 데이터를 다 보내지 못하고 또 블록 상태가 발생했다. 보내지 못한 데이터만 남겨놓는다.
			pTemp = new char[m_iUnsentDataSize[m_sHead] - iRet];
			memcpy(pTemp, m_pUnsentDataList[m_sHead] + iRet, m_iUnsentDataSize[m_sHead] - iRet);

			delete m_pUnsentDataList[m_sHead];
			m_pUnsentDataList[m_sHead] = pTemp;

			return DEF_XSOCKEVENT_UNSENTDATASENDBLOCK;
		}
	}

	return DEF_XSOCKEVENT_UNSENTDATASENDCOMPLETE;
}


int XSocket::iSendMsg(char * cData, DWORD dwSize, char cKey)
{
 WORD * wp;
 int    i, iRet;

	//m_pSndBuffer = cData;
	if (dwSize > m_dwBufferSize) return DEF_XSOCKEVENT_MSGSIZETOOLARGE;

	if (m_cType != DEF_XSOCK_NORMALSOCK) return DEF_XSOCKEVENT_SOCKETMISMATCH;
	if (m_cType == NULL) return DEF_XSOCKEVENT_NOTINITIALIZED;

	m_pSndBuffer[0] = cKey;

	wp  = (WORD *)(m_pSndBuffer + 1);
	*wp = dwSize + 3;

	memcpy((char *)(m_pSndBuffer + 3), cData, dwSize);
	// v.14 : m_pSndBuffer +3 부터 dwSize까지 cKey�
	if (cKey != NULL) {//Encryption
		for (i = 0; i < dwSize; i++) {
			m_pSndBuffer[3+i] += (i ^ cKey);
			m_pSndBuffer[3+i]  = m_pSndBuffer[3+i] ^ (cKey ^ (dwSize - i));
		}
	}

	iRet = _iSend(m_pSndBuffer, dwSize + 3, TRUE);

	if (iRet < 0) return iRet;
	else return (iRet - 3);
}

BOOL XSocket::bListen(char * pAddr, int iPort, unsigned int uiMsg)
{
 SOCKADDR_IN	 saTemp;

	if (m_cType != NULL) return FALSE;
	if (m_Sock  != INVALID_SOCKET) closesocket(m_Sock);

	// 소켓을 생성한다. 
	m_Sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Sock == INVALID_SOCKET) 
		return FALSE;
	
	// 주소를 바인드한다.
	memset(&saTemp,0,sizeof(saTemp));
	saTemp.sin_family = AF_INET;
	saTemp.sin_addr.s_addr = inet_addr(pAddr);
	saTemp.sin_port = htons(iPort);
	if ( bind(m_Sock, (PSOCKADDR)&saTemp, sizeof(saTemp)) == SOCKET_ERROR) {
		closesocket(m_Sock);
		return FALSE;
	}
	
	if (listen(m_Sock, 5) == SOCKET_ERROR) {
		closesocket(m_Sock);
		return FALSE;
	}

	WSAAsyncSelect(m_Sock, m_hWnd, uiMsg, FD_ACCEPT);

	m_uiMsg = uiMsg;
	m_cType = DEF_XSOCK_LISTENSOCK;

	return TRUE;
}

BOOL XSocket::bAccept(class XSocket * pXSock, unsigned int uiMsg)
{
 SOCKET			AcceptedSock;
 sockaddr		Addr;
 register int	iLength;
 DWORD			dwOpt;

	if (m_cType != DEF_XSOCK_LISTENSOCK) return FALSE;
	if (pXSock == NULL) return FALSE;

	iLength = sizeof(Addr);
	AcceptedSock = accept(m_Sock, (struct sockaddr FAR *)&Addr,(int FAR *)&iLength);
	if (AcceptedSock == INVALID_SOCKET) 
		return FALSE;
		
	pXSock->m_Sock = AcceptedSock;
	WSAAsyncSelect(pXSock->m_Sock, m_hWnd, uiMsg, FD_READ | FD_WRITE | FD_CLOSE);

	// Accept
	pXSock->m_uiMsg = uiMsg;
	pXSock->m_cType = DEF_XSOCK_NORMALSOCK;


	dwOpt = 8192*5;
	setsockopt(pXSock->m_Sock, SOL_SOCKET, SO_RCVBUF, (const char FAR *)&dwOpt, sizeof(dwOpt));
	setsockopt(pXSock->m_Sock, SOL_SOCKET, SO_SNDBUF, (const char FAR *)&dwOpt, sizeof(dwOpt));

	return TRUE;
}

void XSocket::_CloseConn()
{
 char cTmp[100];
 BOOL bFlag = TRUE;	
 int  iRet;

	if (m_Sock == INVALID_SOCKET) return; // v1.4

	shutdown(m_Sock, 0x01);
	while (bFlag == TRUE) {
		iRet = recv(m_Sock, cTmp, sizeof(cTmp), 0);
		if (iRet == SOCKET_ERROR) bFlag = FALSE;
		if (iRet == 0) bFlag = FALSE;
	}

	closesocket(m_Sock);

	m_cType = DEF_XSOCK_SHUTDOWNEDSOCK;
}

SOCKET XSocket::iGetSocket()
{
	return m_Sock;
}

char * XSocket::pGetRcvDataPointer(DWORD * pMsgSize, char * pKey)
{
 WORD * wp;
 DWORD  dwSize;
 register int i;
 char cKey;
	
	cKey = m_pRcvBuffer[0];
	if (pKey != NULL) *pKey = cKey;		// v1.4

	wp = (WORD *)(m_pRcvBuffer + 1);
	*pMsgSize = (*wp) - 3;				// 헤더크기는 제외해서 반환한다. 
	dwSize    = (*wp) - 3;

	if (dwSize > DEF_MSGBUFFERSIZE) dwSize = DEF_MSGBUFFERSIZE;

	// v.14 : m_pSndBuffer +3 부터 dwSize까지 cKey가 0이 아니라면 암호화를 푼다.
	if (cKey != NULL) {//Encryption
		for (i = 0; i < dwSize; i++) {
			m_pRcvBuffer[3+i]  = m_pRcvBuffer[3+i] ^ (cKey ^ (dwSize - i));
			m_pRcvBuffer[3+i] -= (i ^ cKey);
		}
	}
	return (m_pRcvBuffer + 3);
}

BOOL _InitWinsock()
{
 int     iErrCode;
 WORD	 wVersionRequested;
 WSADATA wsaData;

	// 소켓의 버젼을 체크한다.
	wVersionRequested = MAKEWORD( 2, 2 ); 
	iErrCode = WSAStartup( wVersionRequested, &wsaData );
	if ( iErrCode ) return FALSE;

	return TRUE;
}


void _TermWinsock()
{
	WSACleanup();
}

///

int XSocket::iGetPeerAddress(char * pAddrString)
{
 SOCKADDR_IN sockaddr;
 int iRet, iLen;
	
	iLen = sizeof(sockaddr);
	iRet = getpeername(m_Sock, (struct sockaddr *)&sockaddr, &iLen);
	strcpy(pAddrString, (const char *)inet_ntoa(sockaddr.sin_addr));

	return iRet;
}
