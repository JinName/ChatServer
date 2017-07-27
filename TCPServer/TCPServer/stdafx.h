#pragma once
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")

void ErrorHandling(char* message);

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}