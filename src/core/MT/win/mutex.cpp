#include "core/MT/mutex.h"
#include <Windows.h>
#include <cassert>


namespace Lux
{
	namespace MT
	{
		Mutex::Mutex(bool locked)
		{
			m_id = ::CreateMutex(NULL, locked, NULL);
		}

		Mutex::~Mutex()
		{
			::CloseHandle(m_id);
		}

		void Mutex::lock()
		{
			::WaitForSingleObject(m_id, INFINITE);
		}

		bool Mutex::poll()
		{
			uint32_t res = ::WaitForSingleObject(m_id, 0);
			return res > 0;
		}

		void Mutex::unlock()
		{
			::ReleaseMutex(m_id);
		}
	} // ~namespace MT
} // ~namespace Lux