#pragma once

#include "../Socket.h"

class Server : public Socket
{
private:
	// m_socket // 클라이언트를 처음 받아들이는 소켓
	sockaddr_in m_serveraddr;	// 서버 정보 구조체

public:
	Server();
	~Server() override;

public:
	bool Initialize(int port, int maxConnectNum = SOMAXCONN); // 초기화
	int Close(); // 서버 소켓 종료

	// 클라이언트의 연결 수락
	// 연결된 소켓 반환, 동적할당 되어있으므로 사용하는 쪽이 해제 해야 함
	SOCKET Accepting();

};