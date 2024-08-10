#pragma once

#include "../Socket.h"

class Server : public Socket
{
private:
	// m_socket // Ŭ���̾�Ʈ�� ó�� �޾Ƶ��̴� ����
	sockaddr_in m_serveraddr;	// ���� ���� ����ü

public:
	Server();
	~Server() override;

public:
	bool Initialize(int port, int maxConnectNum = SOMAXCONN); // �ʱ�ȭ
	int Close(); // ���� ���� ����

	// Ŭ���̾�Ʈ�� ���� ����
	// ����� ���� ��ȯ, �����Ҵ� �Ǿ������Ƿ� ����ϴ� ���� ���� �ؾ� ��
	SOCKET Accepting();

};