#include "Thread.h"

#include <cassert>

Thread::Thread() : m_thread(NULL) {}
Thread::~Thread() 
{
	// �����带 �Ҵ����� �� ����
	if (m_thread != NULL)
	{
		ThreadStop();
	}
}

void Thread::ThreadStart()
{
	// �����带 ����
	m_thread = new std::thread(&Thread::Process, this);
}

void Thread::ThreadStop()
{
	// �����尡 ���������� ���
	if (m_thread->joinable())
	{
		m_thread->join();
	}
	delete m_thread;
}
