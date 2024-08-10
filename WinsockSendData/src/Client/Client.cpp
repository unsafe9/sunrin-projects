#include "Client.h"

#include <iostream>
#include <string>

using namespace std;

Client::Client() : m_isConnected(false) {}
Client::~Client() {}

bool Client::Initialize(const char *serverIP, int serverPort)
{
	// ������ ������ Ŭ���̾�Ʈ ���� ���� (IPv4, ����������, TCP��������)
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		PrintErrorMessage();
		return false;
	}

	// IPv4 �ּ�ü�迡�� ����ϴ� ����ü
	ZeroMemory(&m_serveraddr, sizeof(m_serveraddr));
	m_serveraddr.sin_family = AF_INET;
	m_serveraddr.sin_addr.s_addr = inet_addr(serverIP);
	m_serveraddr.sin_port = htons(serverPort);
	// ������ ���� ��û
	if (connect(m_socket, (SOCKADDR *)&m_serveraddr, sizeof(m_serveraddr)) == SOCKET_ERROR)
	{
		PrintErrorMessage();
		return false;
	}

	m_isConnected = true;

	// ������ ����
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
		<< " - help : ���� ���" << endl
		<< " - exit : ����" << endl
		<< " - char : ���� ����" << endl
		<< " - int : ���� ����" << endl
		<< " - float : 4����Ʈ �Ǽ� ����" << endl
		<< " - double : 8����Ʈ �Ǽ� ����" << endl
		<< " - string : ���ڿ� ����" << endl
		<< " - file : ���� ����" << endl << endl;
}

void Client::Process()
{
	cout << "Ŭ���̾�Ʈ�� �ʱ�ȭ�Ǿ����ϴ�. ������ ����Ǿ����ϴ�." << endl << endl;

	// ���� ���
	PrintHelp();
	// ���ڿ��� �Է¹��� std::string ��ü
	char input[BUFSIZE];
	// ���� �ϷḦ �����κ��� �˸� ���� ����
	bool completed;
	// Ÿ���� ������ ����
	Type type;

	while (true)
	{
		// ��� �Է�
		cout << "order << ";
		cin >> input;
		cin.ignore();

#define Send1(arg1) if (Send(arg1) == SOCKET_ERROR) break
#define Send2(arg1, arg2) if (Send(arg1, arg2) == SOCKET_ERROR) break

		if (strcmp(input, "help") == 0) // ����
		{
			PrintHelp();
		}
		else if (strcmp(input, "exit") == 0)
		{
			break;
		}
		else if (strcmp(input, "char") == 0) // ����
		{
			// ���ڸ� �����Ѵٰ� �˸�
			type = CHAR;
			Send1(type);
			// ������ ���� �Է�
			char data;
			cout << "input char data << ";
			cin >> data;
			cout << "send "; PrintTime();
			// ���� ����
			Send1(data);
		}
		else if (strcmp(input, "int") == 0) // ����
		{
			// ������ �����Ѵٰ� �˸�
			type = INT;
			Send1(type);
			// ������ ���� �Է�
			int data;
			cout << "input int data << ";
			cin >> data;
			cout << "send "; PrintTime();
			// ���� ����
			Send1(data);
		}
		else if (strcmp(input, "float") == 0) // 4����Ʈ �Ǽ�
		{
			// 4����Ʈ �Ǽ��� �����Ѵٰ� �˸�
			type = FLOAT;
			Send1(type);
			// ������ 4����Ʈ �Ǽ� �Է�
			float data;
			cout << "input float data << ";
			cin >> data;
			cout << "send "; PrintTime();
			// 4����Ʈ �Ǽ� ����
			Send1(data);
		}
		else if (strcmp(input, "double") == 0) // 8����Ʈ �Ǽ�
		{
			// 8����Ʈ �Ǽ��� �����Ѵٰ� �˸�
			type = DOUBLE;
			Send1(type);
			// ������ 8����Ʈ �Ǽ� �Է�
			double data;
			cout << "input double data << ";
			cin >> data;
			cout << "send "; PrintTime();
			// 8����Ʈ �Ǽ� ����
			Send1(data);
		}
		else if (strcmp(input, "string") == 0) // ���ڿ�
		{
			// ���ڿ��� �����Ѵٰ� �˸�
			type = STRING;
			Send1(type);
			// ������ ���ڿ� �Է�
			cout << "input string data(max 1023byte) << ";
			cin >> input;
			int length = strlen(input) + 1; // null ���� ����
			cout << "send "; PrintTime();
			// ���ڿ��� ���� ����
			Send1(length);
			// ���ڿ� ����
			Send2(*input, length);
		}
		else if (strcmp(input, "file") == 0) // ����
		{
			// ������ ���ϸ� �Է�
			cout << "input file name << ";
			cin >> input;
			// ���� ����
			::FILE *file;
			file = fopen(input, "rb");
			// ���Ͽ��¿� �������� �� ����
			if (file == NULL)
			{
				cout << "error << ������ �� �� �����ϴ�.";
			}
			else // ������ ������ ��
			{
				// ������ �����Ѵٰ� �˸�
				type = FILE;
				Send(type);
				cout << "send "; PrintTime();
				// ���ϸ��� ���� ����
				int fileNameLength = strlen(input) + 1; // null ���� ����
				Send1(fileNameLength);
				// ���ϸ� ����
				Send2(*input, fileNameLength);
				// ������ ũ�⸦ ���ϰ� ����
				::fseek(file, 0, SEEK_END);
				int fileSize = ftell(file) + 1;
				Send1(fileSize); // null ���� ����
				// ������ �а� ����
				::fseek(file, 0, SEEK_SET);
				char *fileBuf = new char[fileSize];
				::fread(fileBuf, sizeof(char), fileSize, file);
				fileBuf[fileSize - 1] = '\0';
				// ���� ���� ����
				Send2(*fileBuf, fileSize);
				// ������ �ݰ� �ӽ÷� ����� ���۸� ����
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
	cout << endl << "Ŭ���̾�Ʈ�� ����˴ϴ�." << endl;
}

void Client::PrintTime()
{
	// ��¥ �ð� ���� ���
	timer = time(NULL);
	t = localtime(&timer);
	printf("%02d%02d%02d_%02d%02d%02d\n",
		t->tm_year % 100, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
}
