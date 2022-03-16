#pragma once

#include <string>
#include "WorldConstants.h"

#include "Block.h"
#include "ObjectAsset.h"

#include "Atlas.h"

namespace gp
{
	namespace system
	{
		class Loader
		{
		public:
			Loader();
			~Loader();
			
			sf::Texture m_textureAtlas;
			sf::Texture m_objectsAtlas;
			std::vector<gp::object::ObjectAsset*> m_listObjectAssets;

		private:

			sf::Texture createTextureAtlas(const std::vector<gp::world::Block*>& list);
			sf::Texture createTextureAtlas(const std::vector<gp::object::ObjectAsset*>& list);

			std::vector<gp::world::Block*> m_listBlocks;
			

			gp::util::Atlas m_Atlas;
		};

		
	}
}