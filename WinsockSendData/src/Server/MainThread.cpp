#include "MainThread.h"

#include <fstream>
#include <string>

using namespace std;

MainThread::MainThread(Server *server)
{
	m_server = server;
	ThreadStart();
}
MainThread::~MainThread() 
{
	closesocket(m_socket);
}

void MainThread::Process()
{
	cout << "���� ���� ������ ����" << endl << endl;

	while (true)
	{
		// ���ο� ������ ��ٸ�
		m_socket = m_server->Accepting();
		// ����� Ŭ���̾�Ʈ�� �߰�
		ClientPeerThread *client = new ClientPeerThread(this, m_socket);
		clients.push_back(client);
	}
	for (list<ClientPeerThread *>::iterator i = clients.begin(); i != clients.end(); ++i)
	{	
		// ���� �����尡 ����Ǹ� �׵��� ������� Ŭ���̾�Ʈ ���� ����
		delete (*i);
	}
}

void MainThread::EraseClientFromList(ClientPeerThread *peer)
{
	clients.remove(peer);
	delete peer;
}
