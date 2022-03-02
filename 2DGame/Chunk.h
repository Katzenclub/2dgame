#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include "WorldConstants.h"
#include "Noise.h"
#include "Object.h"

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
			uint16_t m_data[g_CHUNK_SIZE][g_CHUNK_SIZE]; // ~65000 max value
			std::vector<gp::object::Object*> m_objects[g_CHUNK_SIZE][g_CHUNK_SIZE];
			sf::Vector2i m_ID;

			void load(std::ifstream& ifs);
			void save(std::ofstream& ofs);
			void generate();
		private:
			void generateLayer(int pattern, int minDepth, int maxDepth,float size, float sensitivity, int blockID);
			void initialiseChunk(int value);

			int seed = time(0);
		};


	}
}