#include "TCP.h"



TCP::TCP()
	:m_iCount(0)
{
}


TCP::~TCP()
{
}


void TCP::Init()
{
	WSAStartup(MAKEWORD(2, 2), &m_WsaData);
	Set_TCPSocket(PORT_NUM, BLOG_SIZE);
}

void TCP::Update()
{
	if (m_ServerSocket == SOCKET_ERROR)
		perror("대기 소켓 오류");
	else
		EventLoop(m_ServerSocket);
}

void TCP::Clean()
{
	WSACleanup(); // 윈속 해제
}

void TCP::EventLoop(SOCKET _sock)
{
	Add_NetworkEvent(_sock, FD_ACCEPT);

	while (true) // 이벤트 루프
	{
		int index = WSAWaitForMultipleEvents(m_iCount, m_hEventBase, false, INFINITE, false);

		WSANETWORKEVENTS netEvents;
		WSAEnumNetworkEvents(m_SocketBase[index], m_hEventBase[index], &netEvents);

		switch (netEvents.lNetworkEvents)
		{
		case FD_ACCEPT:
			AcceptProc(index);
			break;

		case FD_READ:
			ReadProc(index);
			break;

		case FD_CLOSE:
			CloseProc(index);
			break;
		}
	}

	closesocket(_sock); // 소켓 닫기
}

void TCP::AcceptProc(int _index)
{
	SOCKADDR_IN clientAddr = { 0 };

	int len = sizeof(clientAddr);

	SOCKET doSock = accept(m_SocketBase[0], (SOCKADDR*)&clientAddr, &len);

	if (m_iCount == FD_SETSIZE)
	{
		printf("채팅방이 꽉 차서 %s:%d 입장하지 못하였음!\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
		closesocket(doSock);
		return;
	}

	Add_NetworkEvent(doSock, FD_READ | FD_CLOSE);
	printf("%s:%d 입장\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
}

void TCP::ReadProc(int _index)
{
	char msg[MAX_MSG_LEN];
	recv(m_SocketBase[_index], msg, MAX_MSG_LEN, 0);

	SOCKADDR_IN clientAddr = { 0 };
	int len = sizeof(clientAddr);
	getpeername(m_SocketBase[_index], (SOCKADDR *)&clientAddr, &len);

	char smsg[MAX_MSG_LEN];
	sprintf(smsg, "[%s:%d]:%s", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), msg);

	for (int i = 1; i < m_iCount; ++i)
	{
		send(m_SocketBase[i], smsg, MAX_MSG_LEN, 0);
	}
}

void TCP::CloseProc(int _index)
{
	SOCKADDR_IN clientAddr = { 0 };
	int len = sizeof(clientAddr);
	getpeername(m_SocketBase[_index], (SOCKADDR *)&clientAddr, &len);
	printf("[%s:%d]  님 나감~\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

	closesocket(m_SocketBase[_index]);
	WSACloseEvent(m_hEventBase[_index]);

	m_iCount--;
	m_SocketBase[_index] = m_SocketBase[m_iCount];
	m_hEventBase[_index] = m_hEventBase[m_iCount];

	char msg[MAX_MSG_LEN];
	sprintf(msg, "[%s:%d]님 나감~\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	for (int i = 1; i<m_iCount; i++)
	{
		send(m_SocketBase[i], msg, MAX_MSG_LEN, 0);
	}
}

IN_ADDR TCP::Get_DefaultMyIP()
{
	char localhostname[MAX_PATH];
	IN_ADDR addr = { 0, };

	if (gethostname(localhostname, MAX_PATH) == SOCKET_ERROR)
		return addr;

	HOSTENT *ptr = gethostbyname(localhostname);

	while (ptr && ptr->h_name)
	{
		if (ptr->h_addrtype == PF_INET) // IPv4 주소타입일떄
		{
			memcpy(&addr, ptr->h_addr_list[0], ptr->h_length);

			break;
		}
		++ptr;
	}

	return addr;
}

void TCP::Set_TCPSocket(short _portNum, int _backLog)
{
	m_ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_ServerSocket == INVALID_SOCKET)
		perror("socket() error");

	SOCKADDR_IN servAddr = { 0 };

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr = Get_DefaultMyIP();
	servAddr.sin_port = htons(_portNum);

	if (bind(m_ServerSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		perror("bind() error");

	if (listen(m_ServerSocket, _backLog) == SOCKET_ERROR)
		perror("listen() error");
}

HANDLE TCP::Add_NetworkEvent(SOCKET _sock, long _netEvent)
{
	HANDLE hEvent = WSACreateEvent(); // 이벤트 생성

	m_SocketBase[m_iCount] = _sock;
	m_hEventBase[m_iCount] = hEvent;

	WSAEventSelect(_sock, hEvent, _netEvent);

	return hEvent;
}