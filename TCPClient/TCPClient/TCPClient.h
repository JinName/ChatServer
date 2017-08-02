#pragma once
#include "stdafx.h"
#include <process.h>

class TCPClient
{
private:
	WSADATA m_WsaData;
	SOCKET m_ClientSocket;

	char msg[MAX_MSG_LEN];

public:
	TCPClient() {}
	~TCPClient() {}

	void Init();
	void Update();
	void Clean();

	// 소켓 셋팅
	void Set_TCPSocket();

	// 연결 시도
	void Connect(short _portNum);

	void Threading();

	void RecvThreadPoint(void* param)
};