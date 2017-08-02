#pragma once
#include "stdafx.h"

class TCP
{
private:
	WSADATA m_WsaData;
	SOCKET m_ServerSocket;

	SOCKET m_SocketBase[FD_SETSIZE]; // ����
	HANDLE m_hEventBase[FD_SETSIZE]; // �̺�Ʈ

	int m_iCount;

public:
	TCP();
	~TCP();

	void Init(); // ���� �ʱ�ȭ, ������ ����
	void Update();
	void Clean();

	void EventLoop(SOCKET _sock);	

	void AcceptProc(int _index);
	void ReadProc(int _index);
	void CloseProc(int _index);

	// ����Ʈ �ּ�
	IN_ADDR Get_DefaultMyIP();

	// ���� ����
	void Set_TCPSocket(short _portNum, int _backLog);

	// ��Ʈ��ũ �̺�Ʈ
	HANDLE Add_NetworkEvent(SOCKET _sock, long _netEvent);
};

