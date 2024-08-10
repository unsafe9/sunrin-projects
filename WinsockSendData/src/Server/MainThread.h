#pragma once

#include "Server.h"
#include "../Thread.h"
#include "ClientPeerThread.h"

#include <iostream>
#include <ctime>
#include <list>

class MainThread : public Thread, public Socket
{
private:
	// m_socket // 마지막으로 연결된 클라이언트와의 연결 소켓
	Server *m_server;
	std::list<ClientPeerThread *> clients;

public:
	MainThread(Server *server);
	~MainThread() override;

	void Process() override; // 쓰레드

	// 클라이언트 리스트에서 종료된 클라이언트를 삭제
	void EraseClientFromList(ClientPeerThread *peer);

};

