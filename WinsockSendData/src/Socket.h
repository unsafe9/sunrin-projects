#pragma once

// 윈도우 소켓을 사용하기 위한 헤더와 라이브러리
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

// 소켓 클래스
class Socket
{
private:
	enum { BUFFER_SIZE = 512 };

	static WSADATA wsadata; // winsock을 사용하기 위한 정적 변수
	static char buffer[BUFFER_SIZE]; // 데이터 송신에 사용하는 임시 버퍼 정적 변수

protected:
	SOCKET m_socket; // 소켓 멤버 변수

public:
	Socket();
	virtual ~Socket();

	static int Winsock2Start(); // winsock2 dll 로딩(프로그램 시작시 호출)
	static int Winsock2Cleanup(); // winsock2 dll 언로딩(프로그램 종료시 호출)

	static int PrintErrorMessage(); // 마지막 발생한 소켓 에러를 출력한다.

	// 아래 함수들은 실패시 SOCKET_ERROR(-1) 반환

	// 데이터 송수신 정적 함수
	template <typename T> 
	static int Send(SOCKET socket, const T &data, int count = 1); // 소켓, 데이터 변수, 데이터 개수
	template <typename T>
	static int Recv(SOCKET socket, T *buf, int count = 1); // 소켓, 수신버퍼, 데이터 개수

	// 데이터 송수신 멤버 함수
	template <typename T>
	int Send(const T &data, int count = 1); // 데이터 변수, 데이터 개수
	template <typename T>
	int Recv(T *buf, int count = 1); // 수신 버퍼, 데이터 개수

};

// 템플릿 함수이므로 헤더파일에 정의
template <typename T>
inline int Socket::Send(SOCKET socket, const T &data, int count)
{
	int size = sizeof(T) * count;
	memcpy((void *)buffer, (const void *)&data, size);
	return send(socket, buffer, size, 0);
}
template <typename T>
inline int Socket::Recv(SOCKET socket, T *buf, int count)
{
	return recv(socket, (char *)buf, sizeof(T) * count, 0);
}

template <typename T>
inline int Socket::Send(const T &data, int count)
{
	int size = sizeof(T) * count;
	memcpy((void *)buffer, (const void *)&data, size);
	return send(m_socket, buffer, size, 0);
}
template <typename T>
inline int Socket::Recv(T *buf, int count)
{
	return recv(m_socket, (char *)buf, sizeof(T) * count, 0);
}
