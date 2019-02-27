#include "stdafx.h"
#include "thread.h"

namespace CommonLib
{
	thread_id_t CThread::GetCurThreadId()
	{
#ifdef _WIN32
		return (thread_id_t)GetCurrentThreadId();
#else
		return (thread_id_t)pthread_self();
#endif 
	}
}