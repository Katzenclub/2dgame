#include "ManagerRenderer.h"

namespace gp
{
	namespace system
	{
		ManagerRenderer::ManagerRenderer(sf::RenderWindow* rw, gp::world::ManagerWorld* world) :
			m_p_rw(rw),
			m_p_world(world)
		{
			m_p_VertexArray = new sf::VertexArray(sf::PrimitiveType::Quads, g_CHUNK_SIZE * g_CHUNK_SIZE * 4);
		}

		ManagerRenderer::~ManagerRenderer()
		{
		}

		void ManagerRenderer::render()
		{
			renderChunks();
		}

		void ManagerRenderer::renderChunks()
		{
			for (int y = 0; y < g_CHUNK_SIZE; y++)
			{
				for (int x = 0; x < g_CHUNK_SIZE; x++)
				{
					int l_index = (y * g_CHUNK_SIZE + x) * 4;

					(*m_p_VertexArray)[l_index + 0].position = sf::Vector2f(0 + x * g_CHUNK_TEXTURE_SIZE, 0 + y * g_CHUNK_TEXTURE_SIZE);
					(*m_p_VertexArray)[l_index + 1].position = sf::Vector2f((1 * g_CHUNK_TEXTURE_SIZE) + x * g_CHUNK_TEXTURE_SIZE, 0 + y * g_CHUNK_TEXTURE_SIZE);
					(*m_p_VertexArray)[l_index + 2].position = sf::Vector2f((1 * g_CHUNK_TEXTURE_SIZE) + x * g_CHUNK_TEXTURE_SIZE, (1 * g_CHUNK_TEXTURE_SIZE) + y * g_CHUNK_TEXTURE_SIZE);
					(*m_p_VertexArray)[l_index + 3].position = sf::Vector2f(0 + x * g_CHUNK_TEXTURE_SIZE, (1 * g_CHUNK_TEXTURE_SIZE) + y * g_CHUNK_TEXTURE_SIZE);

					int l_BlockID = m_p_world->m_p_chunk->m_data[x][y]; 

					if (l_BlockID == 0)
					{
						(*m_p_VertexArray)[l_index + 0].color = sf::Color(0, 0, 0, 0);
						(*m_p_VertexArray)[l_index + 1].color = sf::Color(0, 0, 0, 0);
						(*m_p_VertexArray)[l_index + 2].color = sf::Color(0, 0, 0, 0);
						(*m_p_VertexArray)[l_index + 3].color = sf::Color(0, 0, 0, 0);
					}
					else if (l_BlockID > 0 && l_BlockID <= 16)
					{
						(*m_p_VertexArray)[l_index + 0].color = sf::Color(16 * l_BlockID, 16 * l_BlockID, 16 * l_BlockID);
						(*m_p_VertexArray)[l_index + 1].color = sf::Color(16 * l_BlockID, 16 * l_BlockID, 16 * l_BlockID);
						(*m_p_VertexArray)[l_index + 2].color = sf::Color(16 * l_BlockID, 16 * l_BlockID, 16 * l_BlockID);
						(*m_p_VertexArray)[l_index + 3].color = sf::Color(16 * l_BlockID, 16 * l_BlockID, 16 * l_BlockID);
					}
					else
					{
						(*m_p_VertexArray)[l_index + 0].color = sf::Color::Yellow;
						(*m_p_VertexArray)[l_index + 1].color = sf::Color::Yellow;
						(*m_p_VertexArray)[l_index + 2].color = sf::Color::Yellow;
						(*m_p_VertexArray)[l_index + 3].color = sf::Color::Yellow;
					}

				}
			}

			m_p_rw->draw(*m_p_VertexArray);
		}
	}
}