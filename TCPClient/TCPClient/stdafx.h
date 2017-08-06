#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <iostream>
using namespace std;

#define PORT_NUM      10200
#define MAX_MSG_LEN   256
//#define SERVER_IP     "192.168.34.50"//辑滚 IP 林家
#define SERVER_IP     "127.0.0.1"//辑滚 IP 林家

#pragma comment(lib, "ws2_32.lib")

//void ErrorHandling(char* message);
//
//void ErrorHandling(char* message)
//{
//	fputs(message, stderr);
//	fputc('\n', stderr);
//	exit(1);
//}