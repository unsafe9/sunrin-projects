#pragma once

#include "Server.h"
#include "../Thread.h"

#include <ctime>

class ClientPeerThread : public Thread, public Socket
{
public:
	enum Type { CHAR = 1, INT, FLOAT, DOUBLE, STRING, FILE }; // ������ Ÿ��

private:
	// m_socket // Ŭ���̾�Ʈ���� ���� ����

	Thread *m_mainThread;

	time_t timer;
	struct tm *t;
	char currentTime[100]; // ���� �ð�

public:
	ClientPeerThread(Thread *mainThread, SOCKET peer); // Ŭ���̾�Ʈ���� ���� ������ ����
	~ClientPeerThread() override;

	void Process() override; // ������

	std::ostream& PrintTime(); // ���� �ð��� ����ϰ� cout�� ����
	void UpdateCurrentTimeString(); // currentTime�� ���� �ð� ����

};

