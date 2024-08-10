#include "Socket.h"

#include <iostream>

WSADATA Socket::wsadata;
char Socket::buffer[BUFFER_SIZE];

Socket::Socket() {}
Socket::~Socket() {}

int Socket::Winsock2Start()
{
	// 윈도우 소켓을 사용하기 위해 winsock.dll을 로드
	return ::WSAStartup(MAKEWORD(2, 2), &wsadata); // 첫번째 매개변수는 로드할 윈도우소켓 버전
}
int Socket::Winsock2Cleanup()
{
	// winsock.dll을 언로드
	return ::WSACleanup();
}

int Socket::PrintErrorMessage()
{
	// 마지막 발생한 에러를 출력
	void *message;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&message, 0, NULL);
	std::cerr << (LPCTSTR)message << std::endl;
	LocalFree(message);

	return WSAGetLastError();
}
