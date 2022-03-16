#pragma once

#include <vector>

#include "ObjectAsset.h"

#define g_Size_ARRAY_CLUSTER 512
#define g_SIZE_ATLAS 512

namespace gp
{
	namespace util
	{
		class Atlas
		{
		public:
			Atlas();
			~Atlas();

			sf::Texture createAtlas(const std::vector<gp::object::ObjectAsset*>& list);
		private:

			// Search for possible texture space on atlas.
			bool searchSpace(sf::Vector2i& pos, sf::Vector2i size);

			// Check is texture space valid.
			bool checkSpace(sf::Vector2i pos, sf::Vector2i size);

			// Fill space with texture
			void fillSpace(sf::Vector2i pos, sf::Vector2i size);

			// Draw texture at selected position on atlas.
			void draw(sf::RenderTexture& rt, sf::Vector2i pos, sf::Texture* texture);

			// Clear cluster array
			void clear(int material);

			int m_arrayCluster[g_Size_ARRAY_CLUSTER][g_Size_ARRAY_CLUSTER];
			unsigned int m_stepSizeCluster;
		};
	}
}