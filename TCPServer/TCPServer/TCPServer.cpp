#include "stdafx.h"
#include <WinSock2.h>

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;

	short port = 5001;
	int szClntAddr;
	char message[] = "Hello World!";

	// ���� �ʱ�ȭ, ���� ����ϱ��� �ʱ�ȭ �ؾ���
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	// TCP ���ϻ���
	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error!");

	// ������ �ּ�����
	memset(&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port); // �� ������ ��Ʈ��ȣ 5001

									 // �ּ�����
	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("bind() error!");

	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error!");

	// ���� ����
	szClntAddr = sizeof(clntAddr);
	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr); // Ŭ���̾�Ʈ ����

	if (hClntSock == INVALID_SOCKET)
		ErrorHandling("accept() error!");

	send(hClntSock, message, sizeof(message), 0);

	closesocket(hClntSock);
	closesocket(hServSock);

	WSACleanup();

	return 0;
}