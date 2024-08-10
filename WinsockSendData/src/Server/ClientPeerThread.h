#pragma once

#include "Server.h"
#include "../Thread.h"

#include <ctime>

class ClientPeerThread : public Thread, public Socket
{
public:
	enum Type { CHAR = 1, INT, FLOAT, DOUBLE, STRING, FILE }; // 전송할 타입

private:
	// m_socket // 클라이언트와의 연결 소켓

	Thread *m_mainThread;

	time_t timer;
	struct tm *t;
	char currentTime[100]; // 현재 시간

public:
	ClientPeerThread(Thread *mainThread, SOCKET peer); // 클라이언트와의 연결 소켓을 받음
	~ClientPeerThread() override;

	void Process() override; // 쓰레드

	std::ostream& PrintTime(); // 현재 시간을 출력하고 cout을 리턴
	void UpdateCurrentTimeString(); // currentTime에 현재 시간 저장

};

