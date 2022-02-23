#pragma once

#include "Chunk.h"

#include <stdio.h>
#include <string>
#include <fstream>

namespace gp
{
	namespace world
	{
		class ManagerWorld
		{
		public:
			ManagerWorld(sf::View *view);
			~ManagerWorld();

			std::vector<gp::world::Chunk*> m_listChunks;
			void load(std::string path);

			sf::Vector2i convertToBlockPos(sf::Vector2f worldPos);
			sf::Vector2i convertToChunkPos(sf::Vector2f worldPos);

			uint16_t getBlockByChunkBlockID(sf::Vector2i chunkPos, sf::Vector2i blockPos);
			void setBlockByChunkBlockID(uint16_t blockID, sf::Vector2i chunkPos, sf::Vector2i blockPos);

		private:
			void save(std::string path);
			void create(std::string path);
		};
	}
}