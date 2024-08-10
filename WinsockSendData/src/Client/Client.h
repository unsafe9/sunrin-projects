#pragma once

#include "../Socket.h"
#include "../Thread.h"

#include <ctime>

class Client : public Thread, public Socket
{
private:
	enum { BUFSIZE = 1024 };

public:
	enum Type { CHAR = 1, INT, FLOAT, DOUBLE, STRING, FILE }; // 전송할 타입

private:
	// m_socket // 서버와 연결되는 소켓
	sockaddr_in m_serveraddr; // 서버 정보 구조체

	time_t timer;
	struct tm *t;

	bool m_isConnected;

public:
	Client();
	~Client() override;

public:
	bool Initialize(const char *serverIP, int serverPort); // 초기화
	int Close(); // 서버 소켓 종료

	void Process() override;

	void PrintTime(); // 현재 시간을 출력하고 cout을 리턴

	bool IsConnected() const { return m_isConnected; }

};