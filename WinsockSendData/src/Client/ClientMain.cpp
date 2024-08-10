#include "Client.h"

#include <iostream>

using namespace std;

int main()
{
	// 윈도우 소켓을 사용하기 위해 winsock.dll을 로드
	Socket::Winsock2Start();

	// 클라이언트 객체를 만들고 31415번 포트로 서버 오픈
	Client *client = new Client();
	client->Initialize("127.0.0.1", 31415);

	// 메인 루프
	while (client->IsConnected()) {}

	// 클라이언트를 해제
	client->Close();
	delete client;

	// winsock.dll을 언로드
	Socket::Winsock2Cleanup();

	return 0;
}