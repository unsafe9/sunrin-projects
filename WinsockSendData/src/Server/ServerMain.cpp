#include "Server.h"
#include "MainThread.h"

#include <iostream>

using namespace std;

int main()
{
	// 윈도우 소켓을 사용하기 위해 winsock.dll을 로드
	Socket::Winsock2Start();

	// 서버 객체를 만들고 31415번 포트로 서버 오픈
	Server *server = new Server();
	server->Initialize(31415);

	MainThread *mainThread = new MainThread(server);

	// 메인 루프
	while (true) {}
	
	// 서버를 해제
	server->Close();
	delete server;

	// winsock.dll을 언로드
	Socket::Winsock2Cleanup();

	return 0;
}