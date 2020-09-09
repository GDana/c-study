#pragma comment(lib,"ws2_32.lib")

#include <stdio.h>  //C언어에서의 입출력 작업을 할 수 있는 표준 입출력 헤더파일
#include <stdlib.h> //C언어에서 범용적으로 사용되는 표준 유틸리티 함수들을 모아놓은 헤더파일
#include <WinSock2.h>   //윈도우용 소켓 프로그래밍, 'ws2_32' 라이브러리를 추가해야 한다.

#define BUFSIZE 1024
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    SOCKET hServSock, hClntSock;
    SOCKADDR_IN servAddr, clntAddr; //sockaddr_in : 주소 체계 정의 - 주소 패밀리, 포트 번호, ip, 패딩

    //char message[] = "hello world!";
    char message[BUFSIZE];
    int strLen;
    int fromLen, nRcv;

    if (argc != 2)
    {
        printf("Usage : %s\n ", argv[0]);
    }

    //WSAStartup() : WinSock2.h을 사용하기 위해 ws2_32.dll 파일을 초기화 시켜준다 
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error");

    // socket() : 새로운 소켓을 정의
    // PF_INET : 프로토콜 패밀리 중 하나로 IPv4 인터넷 프로토콜을 뜻한다. 
    // SOCK_STREAM : TCP방식, SOCK_DGRAM : UDP방식
    // 0 : 0으로 설정할 시 통신에 맞는 프로토콜을 자동으로 선정하여 사용한다.
    hServSock = socket(PF_INET, SOCK_STREAM, 0);    //성공 : return socket handle, 실패 : INVALID_SOCKET
    if (hServSock == INVALID_SOCKET)
        ErrorHandling("socket() error");

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;  //소켓의 주소체계 정의, AF_INET : 주소 패밀리 중 하나로 IPv4 인터넷 프로토콜을 뜻한다.
    servAddr.sin_port = htons(atoi(argv[1]));
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY : 서버의 IP 주소를 자동으로 찾아 대입

    //bind() : 클라이언트가 서버에 접속하기 위한 함수
    //서버의 ip, port 등록 작업
    //sockaddr_in 구조체 : socket 주소, port 할당
    if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        ErrorHandling("bind() error");

    //listen() : 클라이언트의 connect() 의 접속 요청을 '확인'하도록 요청
    //5 : 최대 연결 개수, 최대 5개의 연결까지 기다린다는 것
    if (listen(hServSock, 5) == SOCKET_ERROR)
        ErrorHandling("listen() error!");

    fromLen = sizeof(clntAddr);

    //accept() : listen()에서 확인이 완료된 요청 처리를 맡는다
    //확인 완료된 요청의 접속을 허락하고 소켓을 생성한다.
    hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &fromLen);
    if (hClntSock == INVALID_SOCKET)
        ErrorHandling("accept() error");

    //send(hClntSock, message, sizeof(message), 0);
    //closesocket(hClntSock);
    closesocket(hServSock);

    while (1) {
        printf("message receives...\n");

        //recv() : 클라이언트가 send()를 통해 전송한 데이터를 받는다.
        //hClntSock : 소켓
        //message : 수신할 버퍼 오니터 데이터
        //sizeof(message)-1 : 버퍼의 바이트 단위 크기
        //0 : 플래그를 사용하지 않을 경우
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
        
        //gets : \n, EOF(파일끝)을 만나기 전까지 가져온다
        //\n은 message에 포함되지 않는다
        gets(message);
        if (strcmp(message, "exit") == 0) {
            // send() : 클라이언트에게 데이터를 전송해준다.
            // strlen() : 문자열의 시작부터 \n 직전까지의 문자의 개수를 센다.
            send(hClntSock, message, (int)strlen(message), 0); 
            break;
        }
        send(hClntSock, message, (int)strlen(message), 0);
    }

    //closesocket() : 서버와 클라이언트 소켓 연결을 종료한다
    closesocket(hClntSock);
    //WSACleanup() 를 호출해서 소켓을 리셋시켜줘야 
    //queue에 남지 않아 다음 소켓연결때 에러를 방지할 수 있고 
    //socket이 정상적으로 닫히게 된다.
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