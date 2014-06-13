#pragma once

#include "core/fs/ifile_system_defines.h"
#include "core/lux.h"

namespace Lux
{
	namespace FS
	{
		class IFile //abstract
		{
		public:
			IFile() {}
			virtual ~IFile() {}

			virtual bool open(const char* path, Mode mode) = 0;
			virtual void close() = 0;

			virtual bool read(void* buffer, size_t size) = 0;
			virtual bool write(const void* buffer, size_t size) = 0;

			virtual const void* getBuffer() const = 0;
			virtual size_t size() = 0;

			virtual size_t seek(SeekMode base, size_t pos) = 0;
			virtual size_t pos() = 0;
		};

	} // ~namespace FS
} // ~namespace Lux