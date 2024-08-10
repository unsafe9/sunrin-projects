#include "ClientPeerThread.h"
#include "MainThread.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

ClientPeerThread::ClientPeerThread(Thread *mainThread, SOCKET peer)
{
	// 소켓을 저장하고 쓰레드를 시작
	m_mainThread = mainThread;
	m_socket = peer;
	ThreadStart();
}
ClientPeerThread::~ClientPeerThread()
{
	// 객체가 사라질때 소켓을 종료
	closesocket(m_socket);
}

void ClientPeerThread::Process()
{
	cout << endl << "클라이언트가 연결되었습니다." << endl;

	Type type;
	string filename;
	ofstream filestream;

	while (true)
	{
#define Recv1(arg1) if (Recv(arg1) == SOCKET_ERROR) break
#define Recv2(arg1, arg2) if (Recv(arg1, arg2) == SOCKET_ERROR) break
		// 어떤 종류의 데이터인지 받음
		Recv1(&type);

		filename.clear();

		if (type == Type::CHAR) // 문자
		{
			// 문자 데이터 받아서 출력
			char data;
			Recv1(&data);
			PrintTime() << "type: char, data: " << data;

			UpdateCurrentTimeString();
			filename += "log_";
			filename += currentTime;
			filename += "_char.txt";
			// 파일을 생성하고 오픈
			filestream.open(filename.c_str(), ios::out | ios::binary);
			filestream << data;
			filestream.close();
		}
		else if (type == Type::INT) // 정수
		{
			// 정수 데이터 받아서 출력
			int data;
			Recv1(&data);
			PrintTime() << "type: int, data: " << data;

			UpdateCurrentTimeString();
			filename += "log_";
			filename += currentTime;
			filename += "_int.txt";
			// 파일을 생성하고 오픈
			filestream.open(filename.c_str(), ios::out | ios::binary);
			filestream << data;
			filestream.close();
		}
		else if (type == Type::FLOAT) // 4바이트 실수
		{
			// 4바이트 실수 받아서 출력
			float data;
			Recv1(&data);
			PrintTime() << "type: float, data: " << data;

			UpdateCurrentTimeString();
			filename += "log_";
			filename += currentTime;
			filename += "_float.txt";
			// 파일을 생성하고 오픈
			filestream.open(filename.c_str(), ios::out | ios::binary);
			filestream << data;
			filestream.close();
		}
		else if (type == Type::DOUBLE) // 8바이트 실수
		{
			// 8바이트 실수 받아서 출력
			double data;
			Recv1(&data);
			PrintTime() << "type: double, data: " << data;

			UpdateCurrentTimeString();
			filename += "log_";
			filename += currentTime;
			filename += "_double.txt";
			// 파일을 생성하고 오픈
			filestream.open(filename.c_str(), ios::out | ios::binary);
			filestream << data;
			filestream.close();
		}
		else if (type == Type::STRING) // 문자열
		{
			// 문자열의 길이를 받음
			int length;
			Recv1(&length);
			// 문자열을 받음
			char *buffer = new char[length];
			Recv2(buffer, length);
			// 출력
			PrintTime() << "type: string, length: " << length << ", data: " << buffer;

			UpdateCurrentTimeString();
			filename += "log_";
			filename += currentTime;
			filename += "_string.txt";
			// 파일을 생성하고 오픈
			filestream.open(filename.c_str(), ios::out | ios::binary);
			filestream << buffer;
			filestream.close();

			// 임시 버퍼 해제
			delete[] buffer;
		}
		else if (type == Type::FILE) // 파일
		{
			// 파일명 길이 받음
			int fileNameLen; // null 문자 포함
			Recv1(&fileNameLen);
			// 파일명 받음
			char *fileName = new char[fileNameLen];
			Recv2(fileName, fileNameLen);

			UpdateCurrentTimeString();
			filename += "log_";
			filename += currentTime;
			filename += "_file.txt";
			// 파일을 생성하고 오픈
			filestream.open(filename.c_str(), ios::out | ios::binary);
			// 파일 크기를 받음
			int fileSize;
			Recv1(&fileSize);
			// 파일 내용을 받아서 파일에 기입
			char *fileBuffer = new char[fileSize];
			Recv2(fileBuffer, fileSize);
			filestream << fileBuffer;
			// 정보 출력
			PrintTime() << "type: file, file size: " << fileSize << ", file name: " << fileName;

			// 파일을 닫고 임시 버퍼를 해제
			filestream.close();
			delete[] fileName;
			delete[] fileBuffer;
		}
#undef Recv1
#undef Recv2
		// 개행
		cout << endl;

		// 저장 완료를 클라이언트에 알림
		bool complete = true;
		if (Send(complete) == SOCKET_ERROR)
		{
			break;
		}
	}
	cout << endl << "클라이언트가 종료되었습니다." << endl;
	// ((MainThread*)m_mainThread)->EraseClientFromList(this);
}

std::ostream& ClientPeerThread::PrintTime()
{
	// 날짜 시간 정보 출력
	timer = time(NULL);
	t = localtime(&timer);
	printf("%02d%02d%02d_%02d%02d%02d >> ",
		t->tm_year % 100, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	return std::move(cout);
}

void ClientPeerThread::UpdateCurrentTimeString()
{
	// 날짜 시간 정보 currentTime에 갱신
	timer = time(NULL);
	t = localtime(&timer);
	sprintf(currentTime, "%02d%02d%02d_%02d%02d%02d",
		t->tm_year % 100, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
}
