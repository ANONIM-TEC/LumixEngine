#pragma once


#include "core/string.h"
#include "core/resource.h"
#include "graphics/gl_ext.h"


namespace Lux
{
namespace FS
{
	class FileSystem;
}


class Texture : public Resource
{
	public:
		Texture(const Path& path, ResourceManager& resource_manager);
		~Texture();

		bool create(int w, int h);
		void apply(int unit = 0);
		int getWidth() const { return m_width; }
		int getHeight() const { return m_height; }
		int getBytesPerPixel() const { return m_BPP; }
		const uint8_t* getData() const { return m_data.empty() ? NULL : &m_data[0]; }
		void setNonGL(bool is_nonGL) { m_is_nonGL = is_nonGL; }
	
	private:
		void loaded(FS::IFile* file, bool success, FS::FileSystem& fs);
		bool loadDDS(FS::IFile& file);
		bool loadTGA(FS::IFile& file);

		virtual void doUnload(void) override;
		virtual FS::ReadCallback getReadCallback() override;

	private:
		GLuint m_id;
		int m_width;
		int m_height;
		int m_BPP;
		Array<uint8_t> m_data;
		bool m_is_nonGL;
};


} // ~namespace Lux
