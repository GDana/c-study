// SocketClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <io.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib,"ws2_32")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 1024
void ErrorHandling(char* message);

struct Study
{
	char firstCh;
	char secondCh;
};

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	char message[BUF_SIZE];
	int strLen;
	SOCKADDR_IN servAdr;

	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling((char*)"WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling((char*)"socket() error");

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr(argv[1]);
	servAdr.sin_port = htons(atoi(argv[2]));

	if (connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling((char*)"connect() error!");
	else
		puts("Connected...........");

	while (1)
	{
		fputs("Input message(Q to quit): ", stdout);
		fgets(message, BUF_SIZE, stdin);	//메세지 입력 받음

		// strcmp(str1, str2) 두 매개변수의 문자열 비교
		// str1 < str2 = 음수, 반대는 양수, 같을 경우 0
		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;

		struct Study study;
		memset(&study, 0, sizeof(study));
		study.firstCh = 'a';
		study.secondCh = 'A';

		send(hSocket, (char*)&study, sizeof(study), 0);	//구조체 전송

		// strlen(char arr []) 문자열 길이 반환
		// char arr1[50' = "soni" -> strlen(arr1) -> 4
		//send(hSocket, message, strlen(message), 0);		//일반 메세지 전송
		strLen = recv(hSocket, message, BUF_SIZE - 1, 0);
		message[strLen] = 0;
		printf("Message from server: %s\n", message);
	}

	closesocket(hSocket);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}