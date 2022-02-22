#include "ManagerRenderer.h"
#include <iostream>
namespace gp
{
	namespace system
	{
		ManagerRenderer::ManagerRenderer(sf::RenderWindow* rw, gp::world::ManagerWorld* world, gp::object::ManagerObject* managerObject, gp::system::Loader* loader, sf::View *view) :
			m_p_rw(rw),
			m_p_world(world),
			m_p_objects(managerObject),
			m_p_loader(loader),
			m_p_view(view)
		{
			m_p_VertexArray = new sf::VertexArray(sf::PrimitiveType::Quads, g_CHUNK_SIZE * g_CHUNK_SIZE * 4);
			m_p_VertexArrayObjects = new sf::VertexArray(sf::PrimitiveType::Quads, 0);
		}

		ManagerRenderer::~ManagerRenderer()
		{
		}

		void ManagerRenderer::render(sf::Vector2f pos)
		{
			renderChunks(pos);
			renderObjects();
			//RENDER OBJECTS
		}

		void ManagerRenderer::renderChunks(sf::Vector2f pos)
		{
			int l_visibleChunkXIndex = pos.x / g_CHUNK_TEXTURE_SIZE / g_CHUNK_SIZE;
			int l_visibleChunkYIndex = pos.y / g_CHUNK_TEXTURE_SIZE / g_CHUNK_SIZE;

			float l_amountVisibleChunksX =  (m_p_view->getSize().x / (g_CHUNK_SIZE * g_CHUNK_TEXTURE_SIZE) + 1) / 2 + 0.5;
			float l_amountVisibleChunksY =  (m_p_view->getSize().y / (g_CHUNK_SIZE * g_CHUNK_TEXTURE_SIZE) + 1) / 2 + 0.5;

			for (auto it : m_p_world->m_listChunks)
			{
				
				if (it->m_ID.x > l_visibleChunkXIndex - l_amountVisibleChunksX && it->m_ID.x < l_visibleChunkXIndex + l_amountVisibleChunksX &&
				    it->m_ID.y > l_visibleChunkYIndex - l_amountVisibleChunksY && it->m_ID.y < l_visibleChunkYIndex + l_amountVisibleChunksY)
				{
					renderChunk(it);
				}
			}
		}

		void ManagerRenderer::renderChunk(gp::world::Chunk* chunk)
		{
			for (int y = 0; y < g_CHUNK_SIZE; y++)
			{
				for (int x = 0; x < g_CHUNK_SIZE; x++)
				{
					int l_index = (y * g_CHUNK_SIZE + x) * 4;

					sf::Vector2f l_positionOffset = sf::Vector2f(chunk->m_ID * g_CHUNK_SIZE * g_CHUNK_TEXTURE_SIZE);

					(*m_p_VertexArray)[l_index + 0].position = l_positionOffset + sf::Vector2f(0 + x * g_CHUNK_TEXTURE_SIZE, 0 + y * g_CHUNK_TEXTURE_SIZE);
					(*m_p_VertexArray)[l_index + 1].position = l_positionOffset + sf::Vector2f((1 * g_CHUNK_TEXTURE_SIZE) + x * g_CHUNK_TEXTURE_SIZE, 0 + y * g_CHUNK_TEXTURE_SIZE);
					(*m_p_VertexArray)[l_index + 2].position = l_positionOffset + sf::Vector2f((1 * g_CHUNK_TEXTURE_SIZE) + x * g_CHUNK_TEXTURE_SIZE, (1 * g_CHUNK_TEXTURE_SIZE) + y * g_CHUNK_TEXTURE_SIZE);
					(*m_p_VertexArray)[l_index + 3].position = l_positionOffset + sf::Vector2f(0 + x * g_CHUNK_TEXTURE_SIZE, (1 * g_CHUNK_TEXTURE_SIZE) + y * g_CHUNK_TEXTURE_SIZE);

					int l_BlockID = chunk->m_data[x][y];
					sf::Vector2f l_texPos = sf::Vector2f(l_BlockID / g_ATLAS_BLOCK_SIZE, l_BlockID % g_ATLAS_BLOCK_SIZE);

					(*m_p_VertexArray)[l_index + 0].texCoords = sf::Vector2f(1.f + l_texPos.x * g_CHUNK_TEXTURE_SIZE, 1.f + l_texPos.y * g_CHUNK_TEXTURE_SIZE);
					(*m_p_VertexArray)[l_index + 1].texCoords = sf::Vector2f((1 * g_CHUNK_TEXTURE_SIZE) + l_texPos.x * g_CHUNK_TEXTURE_SIZE - 1.f, 1.f + l_texPos.y * g_CHUNK_TEXTURE_SIZE);
					(*m_p_VertexArray)[l_index + 2].texCoords = sf::Vector2f((1 * g_CHUNK_TEXTURE_SIZE) + l_texPos.x * g_CHUNK_TEXTURE_SIZE - 1.f, (1 * g_CHUNK_TEXTURE_SIZE) + l_texPos.y * g_CHUNK_TEXTURE_SIZE - 1.f);
					(*m_p_VertexArray)[l_index + 3].texCoords = sf::Vector2f(1.f + l_texPos.x * g_CHUNK_TEXTURE_SIZE, (1 * g_CHUNK_TEXTURE_SIZE) + l_texPos.y * g_CHUNK_TEXTURE_SIZE - 1.f);


				}
			}
			sf::RenderStates l_states;
			l_states.texture = &m_p_loader->m_textureAtlas;

			m_p_rw->draw(*m_p_VertexArray, l_states);
		}

		void ManagerRenderer::renderObjects()
		{
			m_p_VertexArrayObjects->resize(m_p_objects->m_listObjects.size() * 4);
			for (size_t i = 0; i < m_p_objects->m_listObjects.size(); i++)
			{
				auto l_it = m_p_objects->m_listObjects[i];

				//if (m_p_view->getCenter().x - m_p_view->getSize().x / 2.f < l_it->m_position.x && m_p_view->getCenter().x + m_p_view->getSize().x / 2.f >= l_it->m_position.x && //
				//	m_p_view->getCenter().y - m_p_view->getSize().y / 2.f < l_it->m_position.y && m_p_view->getCenter().y + m_p_view->getSize().y / 2.f >= l_it->m_position.y)   //
				//{
					//std::cout << "Render" << std::endl;
					int l_index = i * 4;

					(*m_p_VertexArrayObjects)[l_index + 0].position = l_it->m_position + sf::Vector2f(-l_it->m_size.x, -l_it->m_size.y);
					(*m_p_VertexArrayObjects)[l_index + 1].position = l_it->m_position + sf::Vector2f(l_it->m_size.x, -l_it->m_size.y);
					(*m_p_VertexArrayObjects)[l_index + 2].position = l_it->m_position + sf::Vector2f(l_it->m_size.x, l_it->m_size.y);
					(*m_p_VertexArrayObjects)[l_index + 3].position = l_it->m_position + sf::Vector2f(-l_it->m_size.x, l_it->m_size.y);

					auto l_objectAsset = m_p_loader->m_listObjectAssets[l_it->m_objectAssetID];

					(*m_p_VertexArrayObjects)[l_index + 0].texCoords = l_objectAsset->m_PositionTexture + sf::Vector2f(0, 0);
					(*m_p_VertexArrayObjects)[l_index + 1].texCoords = l_objectAsset->m_PositionTexture + sf::Vector2f(l_objectAsset->m_SizeTexture.x, 0);
					(*m_p_VertexArrayObjects)[l_index + 2].texCoords = l_objectAsset->m_PositionTexture + sf::Vector2f(l_objectAsset->m_SizeTexture.x, l_objectAsset->m_SizeTexture.y);
					(*m_p_VertexArrayObjects)[l_index + 3].texCoords = l_objectAsset->m_PositionTexture + sf::Vector2f(0, l_objectAsset->m_SizeTexture.y);
				//}
			}

			sf::RenderStates l_states;
			l_states.texture = &m_p_loader->m_objectsAtlas;

			m_p_rw->draw(*m_p_VertexArrayObjects, l_states);
		}
	}
}