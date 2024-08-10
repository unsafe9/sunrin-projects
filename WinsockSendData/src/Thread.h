#pragma once

#include <thread>

// ������ Ŭ����
class Thread
{
private:
	std::thread *m_thread; // ������ ��ü�� �Ҵ��� ������

public:
	Thread();
	virtual ~Thread(); // ��ü�� �Ҹ�ɶ� ������ ���� (thread_stop ����ȣ��)

public:
	virtual void Process() = 0 {} // ������

	void ThreadStart(); // ������ ����
	void ThreadStop(); // ������ ����

};