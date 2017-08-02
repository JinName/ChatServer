#pragma once
#include "stdafx.h"

class TCP
{
private:
	WSADATA m_WsaData;
	SOCKET m_ServerSocket;

	SOCKET m_SocketBase[FD_SETSIZE]; // 소켓
	HANDLE m_hEventBase[FD_SETSIZE]; // 이벤트

	int m_iCount;

public:
	TCP();
	~TCP();

	void Init(); // 윈속 초기화, 대기소켓 설정
	void Update();
	void Clean();

	void EventLoop(SOCKET _sock);	

	void AcceptProc(int _index);
	void ReadProc(int _index);
	void CloseProc(int _index);

	// 디폴트 주소
	IN_ADDR Get_DefaultMyIP();

	// 소켓 셋팅
	void Set_TCPSocket(short _portNum, int _backLog);

	// 네트워크 이벤트
	HANDLE Add_NetworkEvent(SOCKET _sock, long _netEvent);
};

