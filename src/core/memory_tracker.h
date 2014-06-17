#pragma once

#ifdef MEM_TRACK

#include "core/delegate.h"
#include "core/pod_hash_map.h"
#include "core/MT/spin_mutex.h"

//#include <crtdbg.h>
#include <stdlib.h>

namespace Lux
{
	class MemTrackAllocator
	{
	public:
		void* allocate(size_t n) { return malloc(n); }
		void deallocate(void* p) { free(p); }
		void* reallocate(void* p, size_t n) { return realloc(p, n); }
	};

	class LUX_CORE_API MemoryTracker
	{
	public:
		class Entry
		{
		public:
			Entry()
				: m_file(NULL), m_line(0), m_alloc_id(0), m_size(0), m_mark(0)
			{}

			// copy constructor
			Entry(const Entry& src)
				: m_file(src.m_file), m_line(src.m_line), m_alloc_id(src.m_alloc_id), m_size(src.m_size), m_mark(src.m_mark)
			{}

			Entry(const char* file, int line, size_t size)
				: m_file(file), m_line(line), m_alloc_id(MemoryTracker::getAllocID()), m_size(size), m_mark(0)
			{}

			const char* file() const { return m_file; }
			const int line() const { return m_line; }
			const uint32_t allocID() const { return m_alloc_id; }
			const size_t size() const { return m_size; }

			void mark() { ++m_mark; }
			const uint8_t getMark() const { return m_mark; }

		private:
			const char* m_file;
			uint32_t m_line;
			uint32_t m_alloc_id;
			size_t m_size;
			uint8_t m_mark;
		};
		
		typedef Delegate<void(const char*, const char*)> DebuggerLogCb;

	public:
		static MemoryTracker& getInstance();
		static void destruct();

		void add(void* p, const size_t size, const char* file, const int line);
		void remove(void* p);

		void dumpDetailed();
		void dumpSortedByAllocationOrder();
		void dumpTruncatedPerFileLine();
		void dumpTruncatedPerFile();

		void markAll();
		void dumpUnmarked();

		static uint32_t getAllocID() { return s_alloc_counter++; }

		DebuggerLogCb& getDebuggerLogCb() { return m_debugger_log; }

	private:
		typedef PODHashMap<void*, Entry, PODHashFunc<void*>, MemTrackAllocator> EntryTable;

		MemoryTracker();
		~MemoryTracker();

		void log(const char* message, ...) const;

		EntryTable m_map;

		MT::SpinMutex m_spin_mutex;
		size_t m_allocated_memory;
		uint8_t m_mark;
		DebuggerLogCb m_debugger_log;

		static MemoryTracker s_instance;
		static uint32_t s_alloc_counter;
	};
} //~namespace Lux

#endif // MEM_TRACK
