#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

#define PORT_NUM      10200
#define MAX_MSG_LEN   256
#define SERVER_IP     "192.168.34.50"//서버 IP 주소

#pragma comment(lib, "ws2_32.lib")

void ErrorHandling(char* message);

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}