#pragma once

#include <string>
#include "Block.h"
#include "WorldConstants.h"

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

		private:

			sf::Texture createTextureAtlas(const std::vector<gp::world::Block*>& listBlocks);

			std::vector<gp::world::Block*> m_listBlocks;
			
		};

		
	}
}