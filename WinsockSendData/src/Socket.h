#pragma once

// ������ ������ ����ϱ� ���� ����� ���̺귯��
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

// ���� Ŭ����
class Socket
{
private:
	enum { BUFFER_SIZE = 512 };

	static WSADATA wsadata; // winsock�� ����ϱ� ���� ���� ����
	static char buffer[BUFFER_SIZE]; // ������ �۽ſ� ����ϴ� �ӽ� ���� ���� ����

protected:
	SOCKET m_socket; // ���� ��� ����

public:
	Socket();
	virtual ~Socket();

	static int Winsock2Start(); // winsock2 dll �ε�(���α׷� ���۽� ȣ��)
	static int Winsock2Cleanup(); // winsock2 dll ��ε�(���α׷� ����� ȣ��)

	static int PrintErrorMessage(); // ������ �߻��� ���� ������ ����Ѵ�.

	// �Ʒ� �Լ����� ���н� SOCKET_ERROR(-1) ��ȯ

	// ������ �ۼ��� ���� �Լ�
	template <typename T> 
	static int Send(SOCKET socket, const T &data, int count = 1); // ����, ������ ����, ������ ����
	template <typename T>
	static int Recv(SOCKET socket, T *buf, int count = 1); // ����, ���Ź���, ������ ����

	// ������ �ۼ��� ��� �Լ�
	template <typename T>
	int Send(const T &data, int count = 1); // ������ ����, ������ ����
	template <typename T>
	int Recv(T *buf, int count = 1); // ���� ����, ������ ����

};

// ���ø� �Լ��̹Ƿ� ������Ͽ� ����
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
