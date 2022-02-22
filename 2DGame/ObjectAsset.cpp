#include "ObjectAsset.h"

namespace gp
{
	namespace object
	{
		ObjectAsset::ObjectAsset(std::string name, std::string path) :
			m_name(name)			
		{
			m_ID = g_objectAssetID;
			g_objectAssetID++;
			m_texture.loadFromFile(path);
		}

		ObjectAsset::~ObjectAsset()
		{
		}
	}
}