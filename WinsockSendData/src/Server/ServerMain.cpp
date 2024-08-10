#include "Server.h"
#include "MainThread.h"

#include <iostream>

using namespace std;

int main()
{
	// ������ ������ ����ϱ� ���� winsock.dll�� �ε�
	Socket::Winsock2Start();

	// ���� ��ü�� ����� 31415�� ��Ʈ�� ���� ����
	Server *server = new Server();
	server->Initialize(31415);

	MainThread *mainThread = new MainThread(server);

	// ���� ����
	while (true) {}
	
	// ������ ����
	server->Close();
	delete server;

	// winsock.dll�� ��ε�
	Socket::Winsock2Cleanup();

	return 0;
}