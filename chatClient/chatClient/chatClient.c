#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")

#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

#define BUFSIZE 1024

void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN servAddr;

    char message[BUFSIZE];
    //int strLen;
    int nRcv;


    if (argc != 2)
    {
        printf("Usage : %s\n ", argv[0]);
    }
    
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error");

    
    hSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (hSocket == INVALID_SOCKET)
        ErrorHandling("socket() error");

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]); //inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    //connect() : 클라이언트에서 서버에 접속을 '요청'하기 위한 함수
    if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        ErrorHandling("connect() error");

    //strLen = recv(hSocket, message, sizeof(message) - 1, 0);
    //if (strLen == -1)
    //    ErrorHandling("read() error");
    //printf("Message from server : %s \n", message);

    while (1) {
        printf("\nsend message : ");
        gets(message);

        if (strcmp(message, "exit") == 0) {
            send(hSocket, message, (int)strlen(message), 0);
            break;
        }

        send(hSocket, message, (int)strlen(message), 0);
        printf("message receives...\n");

        nRcv = recv(hSocket, message, sizeof(message) - 1, 0);
        if (nRcv == SOCKET_ERROR) {
            printf("receive error..\n");
            break;
        }
        message[nRcv] = '\0';

        if (strcmp(message, "exit") == 0) {
            printf("close server connection..\n");
            break;
        }

        printf("receive message : %s", message);
    }

    closesocket(hSocket);
    WSACleanup();

    printf("close connection..\n");
    _getch();

    return 0;
}

void ErrorHandling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}