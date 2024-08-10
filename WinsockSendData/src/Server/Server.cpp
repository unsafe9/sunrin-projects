#include "Server.h"

Server::Server() {}
Server::~Server() {}

bool Server::Initialize(int port, int maxConnectNum)
{
	// Ŭ���̾�Ʈ ���� ���� (IPv4, ����������, TCP��������)
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		PrintErrorMessage();
		return false;
	}

	// IPv4 �ּ�ü�迡�� ����ϴ� ����ü
	ZeroMemory(&m_serveraddr, sizeof(m_serveraddr));
	m_serveraddr.sin_family = AF_INET;
	m_serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_serveraddr.sin_port = htons(port);
	// ���Ͽ� �ּ� ���� �Ҵ� (OS�� ��Ʈ�� �ý��� �ڿ� ��� ��û)
	if (bind(m_socket, (sockaddr *)&m_serveraddr, sizeof(m_serveraddr)) == SOCKET_ERROR) 
	{
		PrintErrorMessage();
		return false;
	}

	// Ŭ���̾�Ʈ�� ������ ���� �� �ִ� ���·� �����.
	if (listen(m_socket, maxConnectNum) == SOCKET_ERROR)
	{
		PrintErrorMessage();
		return false;
	}

	return true;
}
int Server::Close()
{
	// ���� ���� �ݱ�
	return closesocket(m_socket);
}

SOCKET Server::Accepting()
{
	// Ŭ���̾�Ʈ�� ������ ���� ��û�� �����ϰ� ����� ������ ��´�.
	sockaddr_in clientaddr;
	int addrlen = sizeof(clientaddr);
	SOCKET sock = accept(m_socket, (sockaddr *)&clientaddr, &addrlen);
	if (sock == INVALID_SOCKET) 
	{
		PrintErrorMessage();
	}
	return sock; // ������ �޾ư� �ʿ��� ����
}
