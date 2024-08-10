#include "Client.h"

#include <iostream>

using namespace std;

int main()
{
	// ������ ������ ����ϱ� ���� winsock.dll�� �ε�
	Socket::Winsock2Start();

	// Ŭ���̾�Ʈ ��ü�� ����� 31415�� ��Ʈ�� ���� ����
	Client *client = new Client();
	client->Initialize("127.0.0.1", 31415);

	// ���� ����
	while (client->IsConnected()) {}

	// Ŭ���̾�Ʈ�� ����
	client->Close();
	delete client;

	// winsock.dll�� ��ε�
	Socket::Winsock2Cleanup();

	return 0;
}