#include "Socket.h"

#include <iostream>

WSADATA Socket::wsadata;
char Socket::buffer[BUFFER_SIZE];

Socket::Socket() {}
Socket::~Socket() {}

int Socket::Winsock2Start()
{
	// ������ ������ ����ϱ� ���� winsock.dll�� �ε�
	return ::WSAStartup(MAKEWORD(2, 2), &wsadata); // ù��° �Ű������� �ε��� ��������� ����
}
int Socket::Winsock2Cleanup()
{
	// winsock.dll�� ��ε�
	return ::WSACleanup();
}

int Socket::PrintErrorMessage()
{
	// ������ �߻��� ������ ���
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
