#pragma once

#include "core/string.h"

namespace Lux
{
	class LUX_CORE_API Path
	{
	public:
		inline Path()
			: m_id(0)
		{
			m_path[0] = '\0';
		}

		Path(const Path& rhs);
		Path(const char* path);
		Path(const string& path);
		Path(uint32_t id, const char* path);

		~Path();

		operator const char*() const { return m_path; }
		operator uint32_t() const { return m_id; }
		operator string() const { return string(m_path); }

		const char* c_str() const { return m_path; }
		size_t length() const { return strlen(m_path); }

		bool operator == (const Path& rhs) const { return m_id == rhs.m_id; }
		bool operator == (const char* rhs) const { Path path(rhs); return m_id == path.m_id; }
		bool operator == (uint32_t rhs) const { return m_id == rhs; }

		bool isValid() { return NULL != m_path; }

	private:
		char		m_path[LUX_MAX_PATH];
		uint32_t	m_id;
	};
}