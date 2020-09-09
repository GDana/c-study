// SocketServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>	//?

#include <io.h>		//?
#include <winsock2.h>	//?
#include <Ws2tcpip.h>	//?
#pragma comment(lib,"ws2_32")


#include <stdio.h>
#include <stdlib.h>
#include <string.h>	//?
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
	SOCKET hServSock, hClntSock;
	char message[BUF_SIZE];
	int strLen, i;
	Study* study;

	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSize;	// = fromLen

	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling((char*)"WSAStartup() error!");

	// 소켓 정의
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling((char*)"socket() error");

	// 소켓 초기화
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));

	// 클라이언트가 서버에 접속하기 위한 설정
	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling((char*)"bind() error");

	// 클라이언트 접속 요청을 확인 설정
	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling((char*)"listen() error");

	// clntAdrSize = clntAdr의 크기를 가리키는 포인터
	clntAdrSize = sizeof(clntAdr);

	// 하나의 클라이언트 접속 및 종료가 완료된 후 다음 클라이언트를 진행
	for (i = 0; i < 5; i++)
	{
		// listen에서 확인 완료된 요청 처리를 맡는다
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSize);
		if (hClntSock == -1)	// -1 == INVALID_SOCKET (?!)
			ErrorHandling((char*)"accept() error");
		else
			printf("Connected client %d \n", i + 1);


		//while ((strLen = recv(hClntSock, message, BUF_SIZE, 0)) != 0)
		while ((strLen = recv(hClntSock, message, sizeof(study), 0)) != 0)	//구조체 사이즈 만큼만 받기
		{
			message[strLen] = '\0';
			printf("receive message : %s\n", message);
			//printf("receive message : %#x\n", message[0]);
			int num = message[0];
			int num1 = message[1];
			int num2 = message[2]; //0 0
			int num3 = message[3]; //
			int num4 = message[4]; //
			printf("receive message : %#x %d\n", num, num);
			printf("receive message : %#x %d\n", num1, num1);
			printf("receive message : %#x %d\n", num2, num2);
			//printf("receive message : %#x %d\n", num3, num3); 
			//printf("receive message : %#x %d\n", num4, num4);

			/* accept() error 발생함
			memcpy(&study, &message, sizeof(message));
			printf("receive message : %c\n", study.firstCh);
			printf("receive message : %c\n", study.secondCh);
			*/
			/* 구조체 받기 */
			study = (Study*)message;	//study가 구조체 포인터여야 함
			printf("receive message : %c\n", study->firstCh);
			printf("receive message : %c\n", study->secondCh);

			send(hClntSock, message, strLen, 0);
		}

		closesocket(hClntSock);
	}

	closesocket(hServSock);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}