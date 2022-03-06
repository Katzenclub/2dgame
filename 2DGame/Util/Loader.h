#pragma once

#include <string>
#include "../World/WorldConstants.h"

#include "GuillotineBinPack.h"
#include "../World/Block.h"
#include "../Object/ObjectAsset.h"

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
			sf::Texture m_borderAtlas;
			sf::Texture m_objectsAtlas;
			std::vector<gp::object::ObjectAsset*> m_listObjectAssets;

		private:

			sf::Texture createTextureAtlas(const std::vector<gp::world::Block*>& list);
			sf::Texture createTextureAtlas(const std::vector<gp::object::ObjectAsset*>& list);

			std::vector<gp::world::Block*> m_listBlocks;
			std::vector<gp::world::Block*> m_listBorders;
			
		};

		
	}
}