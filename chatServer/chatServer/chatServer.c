#pragma comment(lib,"ws2_32.lib")

#include <stdio.h>  //C������ ����� �۾��� �� �� �ִ� ǥ�� ����� �������
#include <stdlib.h> //C���� ���������� ���Ǵ� ǥ�� ��ƿ��Ƽ �Լ����� ��Ƴ��� �������
#include <WinSock2.h>   //������� ���� ���α׷���, 'ws2_32' ���̺귯���� �߰��ؾ� �Ѵ�.

#define BUFSIZE 1024
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    SOCKET hServSock, hClntSock;
    SOCKADDR_IN servAddr, clntAddr; //sockaddr_in : �ּ� ü�� ���� - �ּ� �йи�, ��Ʈ ��ȣ, ip, �е�

    //char message[] = "hello world!";
    char message[BUFSIZE];
    int strLen;
    int fromLen, nRcv;

    if (argc != 2)
    {
        printf("Usage : %s\n ", argv[0]);
    }

    //WSAStartup() : WinSock2.h�� ����ϱ� ���� ws2_32.dll ������ �ʱ�ȭ �����ش� 
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error");

    // socket() : ���ο� ������ ����
    // PF_INET : �������� �йи� �� �ϳ��� IPv4 ���ͳ� ���������� ���Ѵ�. 
    // SOCK_STREAM : TCP���, SOCK_DGRAM : UDP���
    // 0 : 0���� ������ �� ��ſ� �´� ���������� �ڵ����� �����Ͽ� ����Ѵ�.
    hServSock = socket(PF_INET, SOCK_STREAM, 0);    //���� : return socket handle, ���� : INVALID_SOCKET
    if (hServSock == INVALID_SOCKET)
        ErrorHandling("socket() error");

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;  //������ �ּ�ü�� ����, AF_INET : �ּ� �йи� �� �ϳ��� IPv4 ���ͳ� ���������� ���Ѵ�.
    servAddr.sin_port = htons(atoi(argv[1]));
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY : ������ IP �ּҸ� �ڵ����� ã�� ����

    //bind() : Ŭ���̾�Ʈ�� ������ �����ϱ� ���� �Լ�
    //������ ip, port ��� �۾�
    //sockaddr_in ����ü : socket �ּ�, port �Ҵ�
    if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        ErrorHandling("bind() error");

    //listen() : Ŭ���̾�Ʈ�� connect() �� ���� ��û�� 'Ȯ��'�ϵ��� ��û
    //5 : �ִ� ���� ����, �ִ� 5���� ������� ��ٸ��ٴ� ��
    if (listen(hServSock, 5) == SOCKET_ERROR)
        ErrorHandling("listen() error!");

    fromLen = sizeof(clntAddr);

    //accept() : listen()���� Ȯ���� �Ϸ�� ��û ó���� �ô´�
    //Ȯ�� �Ϸ�� ��û�� ������ ����ϰ� ������ �����Ѵ�.
    hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &fromLen);
    if (hClntSock == INVALID_SOCKET)
        ErrorHandling("accept() error");

    //send(hClntSock, message, sizeof(message), 0);
    //closesocket(hClntSock);
    closesocket(hServSock);

    while (1) {
        printf("message receives...\n");

        //recv() : Ŭ���̾�Ʈ�� send()�� ���� ������ �����͸� �޴´�.
        //hClntSock : ����
        //message : ������ ���� ������ ������
        //sizeof(message)-1 : ������ ����Ʈ ���� ũ��
        //0 : �÷��׸� ������� ���� ���
        nRcv = recv(hClntSock, message, sizeof(message) - 1, 0);

        if (nRcv == SOCKET_ERROR) {
            printf("receive error..\n");
            break;
        }
        message[nRcv] = '\0';

        if (strcmp(message, "exit") == 0) {
            printf("close client connection..\n");
            break;
        }
        printf("receive message : %s", message);
        printf("\nsend message : ");
        
        //gets : \n, EOF(���ϳ�)�� ������ ������ �����´�
        //\n�� message�� ���Ե��� �ʴ´�
        gets(message);
        if (strcmp(message, "exit") == 0) {
            // send() : Ŭ���̾�Ʈ���� �����͸� �������ش�.
            // strlen() : ���ڿ��� ���ۺ��� \n ���������� ������ ������ ����.
            send(hClntSock, message, (int)strlen(message), 0); 
            break;
        }
        send(hClntSock, message, (int)strlen(message), 0);
    }

    //closesocket() : ������ Ŭ���̾�Ʈ ���� ������ �����Ѵ�
    closesocket(hClntSock);
    //WSACleanup() �� ȣ���ؼ� ������ ���½������ 
    //queue�� ���� �ʾ� ���� ���Ͽ��ᶧ ������ ������ �� �ְ� 
    //socket�� ���������� ������ �ȴ�.
    WSACleanup();

    printf("close connection..\n");
    //_getch(); 

    return 0;
}

void ErrorHandling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}