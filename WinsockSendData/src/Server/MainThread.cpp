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
	cout << "서버 메인 쓰레드 시작" << endl << endl;

	while (true)
	{
		// 새로운 연결을 기다림
		m_socket = m_server->Accepting();
		// 연결된 클라이언트를 추가
		ClientPeerThread *client = new ClientPeerThread(this, m_socket);
		clients.push_back(client);
	}
	for (list<ClientPeerThread *>::iterator i = clients.begin(); i != clients.end(); ++i)
	{	
		// 메인 쓰레드가 종료되면 그동안 만들어진 클라이언트 전부 해제
		delete (*i);
	}
}

void MainThread::EraseClientFromList(ClientPeerThread *peer)
{
	clients.remove(peer);
	delete peer;
}
