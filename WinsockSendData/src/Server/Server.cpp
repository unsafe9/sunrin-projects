#include "Server.h"

Server::Server() {}
Server::~Server() {}

bool Server::Initialize(int port, int maxConnectNum)
{
	// 클라이언트 소켓 생성 (IPv4, 연결지향형, TCP프로토콜)
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		PrintErrorMessage();
		return false;
	}

	// IPv4 주소체계에서 사용하는 구조체
	ZeroMemory(&m_serveraddr, sizeof(m_serveraddr));
	m_serveraddr.sin_family = AF_INET;
	m_serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_serveraddr.sin_port = htons(port);
	// 소켓에 주소 정보 할당 (OS에 포트등 시스템 자원 사용 요청)
	if (bind(m_socket, (sockaddr *)&m_serveraddr, sizeof(m_serveraddr)) == SOCKET_ERROR) 
	{
		PrintErrorMessage();
		return false;
	}

	// 클라이언트의 연결을 받을 수 있는 상태로 만든다.
	if (listen(m_socket, maxConnectNum) == SOCKET_ERROR)
	{
		PrintErrorMessage();
		return false;
	}

	return true;
}
int Server::Close()
{
	// 서버 소켓 닫기
	return closesocket(m_socket);
}

SOCKET Server::Accepting()
{
	// 클라이언트로 부터의 연결 요청을 수락하고 연결된 소켓을 얻는다.
	sockaddr_in clientaddr;
	int addrlen = sizeof(clientaddr);
	SOCKET sock = accept(m_socket, (sockaddr *)&clientaddr, &addrlen);
	if (sock == INVALID_SOCKET) 
	{
		PrintErrorMessage();
	}
	return sock; // 소켓을 받아간 쪽에서 삭제
}
