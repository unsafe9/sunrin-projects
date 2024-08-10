#include "Thread.h"

#include <cassert>

Thread::Thread() : m_thread(NULL) {}
Thread::~Thread() 
{
	// 쓰레드를 할당했을 시 정지
	if (m_thread != NULL)
	{
		ThreadStop();
	}
}

void Thread::ThreadStart()
{
	// 쓰레드를 시작
	m_thread = new std::thread(&Thread::Process, this);
}

void Thread::ThreadStop()
{
	// 쓰레드가 끝날때까지 대기
	if (m_thread->joinable())
	{
		m_thread->join();
	}
	delete m_thread;
}
