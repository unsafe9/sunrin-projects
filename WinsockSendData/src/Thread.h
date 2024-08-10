#pragma once

#include <thread>

// 쓰레드 클래스
class Thread
{
private:
	std::thread *m_thread; // 쓰레드 객체를 할당할 포인터

public:
	Thread();
	virtual ~Thread(); // 객체가 소멸될때 쓰레드 정지 (thread_stop 내부호출)

public:
	virtual void Process() = 0 {} // 쓰레드

	void ThreadStart(); // 쓰레드 시작
	void ThreadStop(); // 쓰레드 정지

};