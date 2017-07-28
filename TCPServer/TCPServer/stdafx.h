#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

#define PORT_NUM		10200
#define BLOG_SIZE		5
#define MAX_MSG_LEN		256

#pragma comment(lib, "ws2_32.lib")

void ErrorHandling(char* message);

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}