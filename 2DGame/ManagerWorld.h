#pragma once

#include "Chunk.h"

#include <iostream>

namespace gp
{
	namespace world
	{
		class ManagerWorld
		{
		public:
			ManagerWorld(sf::View *view);
			~ManagerWorld();

			void update(sf::Vector2f pos);
			//gp::world::Chunk* m_p_chunk;
			std::vector<gp::world::Chunk*> m_listChunks;



		private:
			sf::Vector2i m_chunkPositionOld;
			sf::Vector2i m_chunkVisibleCount;
			sf::View* m_p_view;
			void updateChunks(sf::Vector2i chunkPosition, sf::Vector2i chunkRadius, bool cleanup = false);
			sf::Vector2i calcVisibleChunkCount(sf::View* view);
		};
	}
}