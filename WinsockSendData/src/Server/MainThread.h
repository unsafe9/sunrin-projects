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
	// m_socket // ���������� ����� Ŭ���̾�Ʈ���� ���� ����
	Server *m_server;
	std::list<ClientPeerThread *> clients;

public:
	MainThread(Server *server);
	~MainThread() override;

	void Process() override; // ������

	// Ŭ���̾�Ʈ ����Ʈ���� ����� Ŭ���̾�Ʈ�� ����
	void EraseClientFromList(ClientPeerThread *peer);

};

