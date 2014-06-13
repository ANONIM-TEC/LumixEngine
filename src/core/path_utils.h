#pragma once

namespace Lux
{
	struct LUX_CORE_API PathUtils
	{
		static void normalize(const char* path, char* out, size_t max_size)
		{
			ASSERT(max_size > 0);
			size_t i = 0;
			if (path[0] == '\\' || path[0] == '/')
				++path;
			while (*path != '\0' && i < max_size)
			{
				*out = *path == '\\' ? '/' : *path;
				*out = *path >= 'A' && *path <= 'Z' ? *path - 'A' + 'a' : *out;

				path++;
				out++;
				i++;
			}
			(i < max_size ? *out : *(out - 1)) = '\0';
		}

	private:
		PathUtils();
		~PathUtils();
	};
}