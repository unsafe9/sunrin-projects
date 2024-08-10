#include "ClientPeerThread.h"
#include "MainThread.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

ClientPeerThread::ClientPeerThread(Thread *mainThread, SOCKET peer)
{
	// ������ �����ϰ� �����带 ����
	m_mainThread = mainThread;
	m_socket = peer;
	ThreadStart();
}
ClientPeerThread::~ClientPeerThread()
{
	// ��ü�� ������� ������ ����
	closesocket(m_socket);
}

void ClientPeerThread::Process()
{
	cout << endl << "Ŭ���̾�Ʈ�� ����Ǿ����ϴ�." << endl;

	Type type;
	string filename;
	ofstream filestream;

	while (true)
	{
#define Recv1(arg1) if (Recv(arg1) == SOCKET_ERROR) break
#define Recv2(arg1, arg2) if (Recv(arg1, arg2) == SOCKET_ERROR) break
		// � ������ ���������� ����
		Recv1(&type);

		filename.clear();

		if (type == Type::CHAR) // ����
		{
			// ���� ������ �޾Ƽ� ���
			char data;
			Recv1(&data);
			PrintTime() << "type: char, data: " << data;

			UpdateCurrentTimeString();
			filename += "log_";
			filename += currentTime;
			filename += "_char.txt";
			// ������ �����ϰ� ����
			filestream.open(filename.c_str(), ios::out | ios::binary);
			filestream << data;
			filestream.close();
		}
		else if (type == Type::INT) // ����
		{
			// ���� ������ �޾Ƽ� ���
			int data;
			Recv1(&data);
			PrintTime() << "type: int, data: " << data;

			UpdateCurrentTimeString();
			filename += "log_";
			filename += currentTime;
			filename += "_int.txt";
			// ������ �����ϰ� ����
			filestream.open(filename.c_str(), ios::out | ios::binary);
			filestream << data;
			filestream.close();
		}
		else if (type == Type::FLOAT) // 4����Ʈ �Ǽ�
		{
			// 4����Ʈ �Ǽ� �޾Ƽ� ���
			float data;
			Recv1(&data);
			PrintTime() << "type: float, data: " << data;

			UpdateCurrentTimeString();
			filename += "log_";
			filename += currentTime;
			filename += "_float.txt";
			// ������ �����ϰ� ����
			filestream.open(filename.c_str(), ios::out | ios::binary);
			filestream << data;
			filestream.close();
		}
		else if (type == Type::DOUBLE) // 8����Ʈ �Ǽ�
		{
			// 8����Ʈ �Ǽ� �޾Ƽ� ���
			double data;
			Recv1(&data);
			PrintTime() << "type: double, data: " << data;

			UpdateCurrentTimeString();
			filename += "log_";
			filename += currentTime;
			filename += "_double.txt";
			// ������ �����ϰ� ����
			filestream.open(filename.c_str(), ios::out | ios::binary);
			filestream << data;
			filestream.close();
		}
		else if (type == Type::STRING) // ���ڿ�
		{
			// ���ڿ��� ���̸� ����
			int length;
			Recv1(&length);
			// ���ڿ��� ����
			char *buffer = new char[length];
			Recv2(buffer, length);
			// ���
			PrintTime() << "type: string, length: " << length << ", data: " << buffer;

			UpdateCurrentTimeString();
			filename += "log_";
			filename += currentTime;
			filename += "_string.txt";
			// ������ �����ϰ� ����
			filestream.open(filename.c_str(), ios::out | ios::binary);
			filestream << buffer;
			filestream.close();

			// �ӽ� ���� ����
			delete[] buffer;
		}
		else if (type == Type::FILE) // ����
		{
			// ���ϸ� ���� ����
			int fileNameLen; // null ���� ����
			Recv1(&fileNameLen);
			// ���ϸ� ����
			char *fileName = new char[fileNameLen];
			Recv2(fileName, fileNameLen);

			UpdateCurrentTimeString();
			filename += "log_";
			filename += currentTime;
			filename += "_file.txt";
			// ������ �����ϰ� ����
			filestream.open(filename.c_str(), ios::out | ios::binary);
			// ���� ũ�⸦ ����
			int fileSize;
			Recv1(&fileSize);
			// ���� ������ �޾Ƽ� ���Ͽ� ����
			char *fileBuffer = new char[fileSize];
			Recv2(fileBuffer, fileSize);
			filestream << fileBuffer;
			// ���� ���
			PrintTime() << "type: file, file size: " << fileSize << ", file name: " << fileName;

			// ������ �ݰ� �ӽ� ���۸� ����
			filestream.close();
			delete[] fileName;
			delete[] fileBuffer;
		}
#undef Recv1
#undef Recv2
		// ����
		cout << endl;

		// ���� �ϷḦ Ŭ���̾�Ʈ�� �˸�
		bool complete = true;
		if (Send(complete) == SOCKET_ERROR)
		{
			break;
		}
	}
	cout << endl << "Ŭ���̾�Ʈ�� ����Ǿ����ϴ�." << endl;
	// ((MainThread*)m_mainThread)->EraseClientFromList(this);
}

std::ostream& ClientPeerThread::PrintTime()
{
	// ��¥ �ð� ���� ���
	timer = time(NULL);
	t = localtime(&timer);
	printf("%02d%02d%02d_%02d%02d%02d >> ",
		t->tm_year % 100, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	return std::move(cout);
}

void ClientPeerThread::UpdateCurrentTimeString()
{
	// ��¥ �ð� ���� currentTime�� ����
	timer = time(NULL);
	t = localtime(&timer);
	sprintf(currentTime, "%02d%02d%02d_%02d%02d%02d",
		t->tm_year % 100, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
}
