#include "core/lux.h"
#include "core/font_manager.h"

#include "core/fs/file_system.h"
#include "core/resource.h"
namespace Lux
{
	class FontResource : public Resource
	{
		friend class FontManager;

	protected:
		FontResource(const Path& path, ResourceManager& resource_manager)
			: Resource(path, resource_manager)
		{ }

		~FontResource()
		{ }


		virtual void doUnload(void) override
		{
		}

		FS::ReadCallback getReadCallback() { return FS::ReadCallback(); }
	};

		Resource* FontManager::createResource(const Path& path)
		{
			return LUX_NEW(FontResource)(path, getOwner());
		}

		void FontManager::destroyResource(Resource& resource)
		{
			LUX_DELETE(static_cast<FontResource*>(&resource));
		}
}