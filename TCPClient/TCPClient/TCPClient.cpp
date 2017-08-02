#include "TCPClient.h"

void TCPClient::Init()
{
}

void TCPClient::Update()
{
}

void TCPClient::Clean()
{
}

void TCPClient::Set_TCPSocket()
{
	m_ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_ClientSocket == INVALID_SOCKET)
		perror("socket() error");	
}

void TCPClient::Connect(short _portNum)
{
	SOCKADDR_IN servAddr = { 0 };

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	servAddr.sin_port = htons(_portNum);

	if (connect(m_ClientSocket, (struct sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		perror("connect() error");
}

void TCPClient::Threading()
{
	_beginthread(RecvThreadPoint, 0, (void*)m_ClientSocket);
}

void TCPClient::RecvThreadPoint(void* param)
{
	SOCKET sock = (SOCKET)param;
	char msg[MAX_MSG_LEN];

	SOCKADDR_IN cliaddr = { 0 };
	int len = sizeof(cliaddr);

	while (recv(sock, msg, MAX_MSG_LEN, 0)>0)
	{
		printf("%s\n", msg);
	}
	closesocket(sock);

	return;
}

// TCPClient.cpp

//#include "stdafx.h"
//#include <WinSock2.h>
//#include <WS2tcpip.h>
//
//int main(int argc, char* argv[])
//{
//	WSADATA wsaData;
//	SOCKET hSocket;
//	SOCKADDR_IN servAddr;
//
//	int port = 5001;
//	char message[30];
//	int strLen;
//
//	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//		ErrorHandling("WSAStartup() error!");
//
//	hSocket = socket(PF_INET, SOCK_STREAM, 0);
//
//	if (hSocket == INVALID_SOCKET)
//		ErrorHandling("hSocket() error!");
//
//	memset(&servAddr, 0, sizeof(servAddr));
//
//	servAddr.sin_family = AF_INET;
//	servAddr.sin_port = htons(port);
//	inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr.s_addr);
//
//	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
//		ErrorHandling("connect() error!");
//
//	strLen = recv(hSocket, message, sizeof(message) - 1, 0);
//
//	if (strLen == -1)
//		ErrorHandling("read() error!");
//
//	printf("message from server: %s \n", message);
//
//	closesocket(hSocket);
//	WSACleanup();
//
//	return 0;
//}