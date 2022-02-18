#include "ManagerWorld.h"

namespace gp
{
	namespace world
	{
		ManagerWorld::ManagerWorld(sf::View *view) :
			m_p_view(view)
		{		
			sf::Vector2i l_visibleChunks = calcVisibleChunkCount(m_p_view);
			updateChunks(sf::Vector2i(0,0), l_visibleChunks);
		}

		ManagerWorld::~ManagerWorld()
		{
		}

		void ManagerWorld::update(sf::Vector2f pos)
		{
			/*
			sf::Vector2i l_blockPosition = sf::Vector2i(pos.x / g_CHUNK_TEXTURE_SIZE, pos.y / g_CHUNK_TEXTURE_SIZE);
			sf::Vector2i l_chunkPosition = sf::Vector2i(l_blockPosition.x / g_CHUNK_SIZE, l_blockPosition.y / g_CHUNK_SIZE);
			sf::Vector2i l_visibleChunks = calcVisibleChunkCount(m_p_view);
			if (l_chunkPosition != m_chunkPositionOld || m_chunkVisibleCount != l_visibleChunks)
			{		
				updateChunks(l_chunkPosition, l_visibleChunks, true);

				m_chunkPositionOld = l_chunkPosition;
				m_chunkVisibleCount = l_visibleChunks;
			}
			*/
			if (m_listChunks.size() == 0) {
				updateChunks(sf::Vector2i(1,1), sf::Vector2i(1,1), true);
			}
		}

		void ManagerWorld::updateChunks(sf::Vector2i chunkPosition, sf::Vector2i chunkRadius, bool cleanup)
		{
			//std::cout << chunkRadius.x << " : " << chunkRadius.y << std::endl;
			/*
			if (cleanup)
			{
				for (std::vector<gp::world::Chunk*>::iterator it = m_listChunks.begin(); it != m_listChunks.end(); ++it)
				{
					delete (*it);
					it = m_listChunks.erase(it);
					it--;
				}
			}
		
			for (int y = -chunkRadius.y; y <= chunkRadius.y; y++)
			{
				for (int x = -chunkRadius.x; x <= chunkRadius.x; x++)
				{
					sf::Vector2i l_chunkPositionCur = sf::Vector2i(chunkPosition.x + x, chunkPosition.y + y);

					if (l_chunkPositionCur.x >= 0 && l_chunkPositionCur.y >= 0 && l_chunkPositionCur.x < g_WORLD_SIZE_X && l_chunkPositionCur.y < g_WORLD_SIZE_Y)
					{
						auto l_chunk = new gp::world::Chunk(sf::Vector2i(l_chunkPositionCur.x, l_chunkPositionCur.y));
						m_listChunks.push_back(l_chunk);
					}
				}
			}
			*/
			for (int y = 0; y < g_WORLD_SIZE_Y; y++) 
			{
				for (int x = 0; x < g_WORLD_SIZE_X; x++) 
				{
					auto l_chunk = new gp::world::Chunk(sf::Vector2i(x, y));
						m_listChunks.push_back(l_chunk);
				}
			}
		}

		sf::Vector2i ManagerWorld::calcVisibleChunkCount(sf::View* view)
		{
			return sf::Vector2i((view->getSize().x / (g_CHUNK_SIZE * g_CHUNK_TEXTURE_SIZE)) + 1,(view->getSize().y / (g_CHUNK_SIZE * g_CHUNK_TEXTURE_SIZE)) +1 );
		}
	}
}