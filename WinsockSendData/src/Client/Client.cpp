#include "Client.h"

#include <iostream>
#include <string>

using namespace std;

Client::Client() : m_isConnected(false) {}
Client::~Client() {}

bool Client::Initialize(const char *serverIP, int serverPort)
{
	// 서버에 연결할 클라이언트 소켓 생성 (IPv4, 연결지향형, TCP프로토콜)
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		PrintErrorMessage();
		return false;
	}

	// IPv4 주소체계에서 사용하는 구조체
	ZeroMemory(&m_serveraddr, sizeof(m_serveraddr));
	m_serveraddr.sin_family = AF_INET;
	m_serveraddr.sin_addr.s_addr = inet_addr(serverIP);
	m_serveraddr.sin_port = htons(serverPort);
	// 서버에 접속 요청
	if (connect(m_socket, (SOCKADDR *)&m_serveraddr, sizeof(m_serveraddr)) == SOCKET_ERROR)
	{
		PrintErrorMessage();
		return false;
	}

	m_isConnected = true;

	// 쓰레드 생성
	ThreadStart();
}
int Client::Close()
{
	m_isConnected = false;
	return closesocket(m_socket);
}

inline void PrintHelp()
{
	cout << endl << "help" << endl
		<< " - help : 도움말 출력" << endl
		<< " - exit : 종료" << endl
		<< " - char : 문자 전송" << endl
		<< " - int : 정수 전송" << endl
		<< " - float : 4바이트 실수 전송" << endl
		<< " - double : 8바이트 실수 전송" << endl
		<< " - string : 문자열 전송" << endl
		<< " - file : 파일 전송" << endl << endl;
}

void Client::Process()
{
	cout << "클라이언트가 초기화되었습니다. 서버에 연결되었습니다." << endl << endl;

	// 도움말 출력
	PrintHelp();
	// 문자열을 입력받을 std::string 객체
	char input[BUFSIZE];
	// 저장 완료를 서버로부터 알림 받을 변수
	bool completed;
	// 타입을 저장할 변수
	Type type;

	while (true)
	{
		// 명령 입력
		cout << "order << ";
		cin >> input;
		cin.ignore();

#define Send1(arg1) if (Send(arg1) == SOCKET_ERROR) break
#define Send2(arg1, arg2) if (Send(arg1, arg2) == SOCKET_ERROR) break

		if (strcmp(input, "help") == 0) // 도움말
		{
			PrintHelp();
		}
		else if (strcmp(input, "exit") == 0)
		{
			break;
		}
		else if (strcmp(input, "char") == 0) // 문자
		{
			// 문자를 전송한다고 알림
			type = CHAR;
			Send1(type);
			// 전송할 문자 입력
			char data;
			cout << "input char data << ";
			cin >> data;
			cout << "send "; PrintTime();
			// 문자 전송
			Send1(data);
		}
		else if (strcmp(input, "int") == 0) // 정수
		{
			// 정수를 전송한다고 알림
			type = INT;
			Send1(type);
			// 전송할 정수 입력
			int data;
			cout << "input int data << ";
			cin >> data;
			cout << "send "; PrintTime();
			// 정수 전송
			Send1(data);
		}
		else if (strcmp(input, "float") == 0) // 4바이트 실수
		{
			// 4바이트 실수를 전송한다고 알림
			type = FLOAT;
			Send1(type);
			// 전송할 4바이트 실수 입력
			float data;
			cout << "input float data << ";
			cin >> data;
			cout << "send "; PrintTime();
			// 4바이트 실수 전송
			Send1(data);
		}
		else if (strcmp(input, "double") == 0) // 8바이트 실수
		{
			// 8바이트 실수를 전송한다고 알림
			type = DOUBLE;
			Send1(type);
			// 전송할 8바이트 실수 입력
			double data;
			cout << "input double data << ";
			cin >> data;
			cout << "send "; PrintTime();
			// 8바이트 실수 전송
			Send1(data);
		}
		else if (strcmp(input, "string") == 0) // 문자열
		{
			// 문자열을 전송한다고 알림
			type = STRING;
			Send1(type);
			// 전송할 문자열 입력
			cout << "input string data(max 1023byte) << ";
			cin >> input;
			int length = strlen(input) + 1; // null 문자 포함
			cout << "send "; PrintTime();
			// 문자열의 길이 전송
			Send1(length);
			// 문자열 전송
			Send2(*input, length);
		}
		else if (strcmp(input, "file") == 0) // 파일
		{
			// 전송할 파일명 입력
			cout << "input file name << ";
			cin >> input;
			// 파일 오픈
			::FILE *file;
			file = fopen(input, "rb");
			// 파일오픈에 실패했을 시 무시
			if (file == NULL)
			{
				cout << "error << 파일을 열 수 없습니다.";
			}
			else // 파일을 열었을 시
			{
				// 파일을 전송한다고 알림
				type = FILE;
				Send(type);
				cout << "send "; PrintTime();
				// 파일명의 길이 전송
				int fileNameLength = strlen(input) + 1; // null 문자 포함
				Send1(fileNameLength);
				// 파일명 전송
				Send2(*input, fileNameLength);
				// 파일의 크기를 구하고 전송
				::fseek(file, 0, SEEK_END);
				int fileSize = ftell(file) + 1;
				Send1(fileSize); // null 문자 포함
				// 파일을 읽고 전송
				::fseek(file, 0, SEEK_SET);
				char *fileBuf = new char[fileSize];
				::fread(fileBuf, sizeof(char), fileSize, file);
				fileBuf[fileSize - 1] = '\0';
				// 파일 내용 전송
				Send2(*fileBuf, fileSize);
				// 파일을 닫고 임시로 사용한 버퍼를 삭제
				::fclose(file);
				delete[] fileBuf;
			}
		}
		else
		{
			cout << endl;
			continue;
		}
		Recv(&completed);
		cout << "recv "; PrintTime();
		cout << endl;
}
	m_isConnected = false;
	cout << endl << "클라이언트가 종료됩니다." << endl;
}

void Client::PrintTime()
{
	// 날짜 시간 정보 출력
	timer = time(NULL);
	t = localtime(&timer);
	printf("%02d%02d%02d_%02d%02d%02d\n",
		t->tm_year % 100, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
}
