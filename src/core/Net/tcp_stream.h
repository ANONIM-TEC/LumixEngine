#pragma once

#include "core/lux.h"
#include <string.h>

namespace Lux
{
	namespace Net
	{
		class LUX_CORE_API TCPStream
		{
		public:
			TCPStream(uintptr_t socket) : m_socket(socket) { } 
			~TCPStream();

			LUX_FORCE_INLINE bool read(bool& val)
			{
				return read(&val, sizeof(val));
			}

			LUX_FORCE_INLINE bool read(uint8_t& val)
			{
				return read(&val, sizeof(val));
			}

			LUX_FORCE_INLINE bool read(int8_t& val)
			{
				return read(&val, sizeof(val));
			}

			LUX_FORCE_INLINE bool read(uint16_t& val)
			{
				return read(&val, sizeof(val));
			}

			LUX_FORCE_INLINE bool read(int16_t& val)
			{
				return read(&val, sizeof(val));
			}

			LUX_FORCE_INLINE bool read(uint32_t& val)
			{
				return read(&val, sizeof(val));
			}

			LUX_FORCE_INLINE bool read(int32_t& val)
			{
				return read(&val, sizeof(val));
			}

			LUX_FORCE_INLINE bool read(uint64_t& val)
			{
				return read(&val, sizeof(val));
			}

			LUX_FORCE_INLINE bool read(int64_t& val)
			{
				return read(&val, sizeof(val));
			}
#ifdef 64_PLATFORM
			LUX_FORCE_INLINE bool read(size_t& val)
			{
				return read(&val, sizeof(val));
			}
#endif //~_PLATFORM
			LUX_FORCE_INLINE bool write(bool val)
			{
				return write(&val, sizeof(val));
			}

			LUX_FORCE_INLINE bool write(uint8_t val)
			{
				return write(&val, sizeof(val));
			}

			LUX_FORCE_INLINE bool write(int8_t val)
			{
				return write(&val, sizeof(val));
			}

			LUX_FORCE_INLINE bool write(uint16_t val)
			{
				return write(&val, sizeof(val));
			}

			LUX_FORCE_INLINE bool write(int16_t val)
			{
				return write(&val, sizeof(val));
			}

			LUX_FORCE_INLINE bool write(uint32_t val)
			{
				return write(&val, sizeof(val));
			}

			LUX_FORCE_INLINE bool write(int32_t val)
			{
				return write(&val, sizeof(val));
			}

			LUX_FORCE_INLINE bool write(uint64_t val)
			{
				return write(&val, sizeof(val));
			}

			LUX_FORCE_INLINE bool write(int64_t val)
			{
				return write(&val, sizeof(val));
			}
#ifdef _PLATFORM
			LUX_FORCE_INLINE bool write(size_t val)
			{
				return write(&val, sizeof(val));
			}
#endif //~_PLATFORM			
			bool readString(char* string, uint32_t max_size);
			bool writeString(const char* string);

			bool read(void* buffer, size_t size);
			bool write(const void* buffer, size_t size);

		private:
			TCPStream();

			uintptr_t m_socket;
		};
	} // ~namespace Net
} // ~namespace Lux