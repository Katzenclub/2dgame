#pragma once

#include <SFML/Graphics.hpp>

#include "WorldConstants.h"
#include "Noise.h"

namespace gp
{
	namespace world
	{
		enum Pattern
		{
			turbulence,
			none
		};

		class Chunk
		{
		public:
			Chunk(sf::Vector2i ID);
			~Chunk();
			int m_data[g_CHUNK_SIZE][g_CHUNK_SIZE];
		private:

			void generate();

			sf::Vector2i m_ID;

			void generateLayer(int pattern, int minDepth, int maxDepth,float size, float sensitivity, int blockID);
			void initialiseChunk(int value);
		};


	}
}