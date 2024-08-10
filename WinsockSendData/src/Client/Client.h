#pragma once

#include "../Socket.h"
#include "../Thread.h"

#include <ctime>

class Client : public Thread, public Socket
{
private:
	enum { BUFSIZE = 1024 };

public:
	enum Type { CHAR = 1, INT, FLOAT, DOUBLE, STRING, FILE }; // ������ Ÿ��

private:
	// m_socket // ������ ����Ǵ� ����
	sockaddr_in m_serveraddr; // ���� ���� ����ü

	time_t timer;
	struct tm *t;

	bool m_isConnected;

public:
	Client();
	~Client() override;

public:
	bool Initialize(const char *serverIP, int serverPort); // �ʱ�ȭ
	int Close(); // ���� ���� ����

	void Process() override;

	void PrintTime(); // ���� �ð��� ����ϰ� cout�� ����

	bool IsConnected() const { return m_isConnected; }

};