#include "ManagerRenderer.h"
#include <iostream>
namespace gp
{
	namespace system
	{
		ManagerRenderer::ManagerRenderer(sf::RenderWindow* rw, gp::world::ManagerWorld* world, gp::object::ManagerObject* managerObject, gp::system::Loader* loader, sf::View* view) :
			m_p_rw(rw),
			m_p_world(world),
			m_p_objects(managerObject),
			m_p_loader(loader),
			m_p_view(view)
		{
			m_p_VertexArray = new sf::VertexArray(sf::PrimitiveType::Quads, g_CHUNK_SIZE * g_CHUNK_SIZE * 4);
			m_p_VertexArrayBorders = new sf::VertexArray(sf::PrimitiveType::Quads, g_CHUNK_SIZE * g_CHUNK_SIZE * 4);
			m_p_VertexArrayObjects = new sf::VertexArray(sf::PrimitiveType::Quads, 0);
		}

		ManagerRenderer::~ManagerRenderer()
		{
		}

		void ManagerRenderer::render(sf::Vector2f pos)
		{
			renderChunks(pos);
			renderObjects();
			renderDebug();
			//RENDER OBJECTS
		}

		void ManagerRenderer::renderChunks(sf::Vector2f pos)
		{
			float l_amountVisibleChunksX = m_p_view->getSize().x / (g_CHUNK_SIZE * g_CHUNK_TEXTURE_SIZE);
			float l_amountVisibleChunksY = m_p_view->getSize().y / (g_CHUNK_SIZE * g_CHUNK_TEXTURE_SIZE);

			int l_PlayerChunkX = pos.x / g_CHUNK_TEXTURE_SIZE / g_CHUNK_SIZE;
			int l_PlayerChunkY = pos.y / g_CHUNK_TEXTURE_SIZE / g_CHUNK_SIZE;

			int startX = l_PlayerChunkX - l_amountVisibleChunksX / 2;
			int startY = l_PlayerChunkY - l_amountVisibleChunksY / 2;

			if (startX < 0) {
				startX = 0;
			}
			if (startY < 0) {
				startY = 0;
			}

			int endX = l_PlayerChunkX + l_amountVisibleChunksX / 2 + 2;
			int endY = l_PlayerChunkY + l_amountVisibleChunksY / 2 + 2;

			if (endX > g_WORLD_SIZE_X) {
				endX = g_WORLD_SIZE_X;
			}
			if (endY > g_WORLD_SIZE_Y) {
				endY = g_WORLD_SIZE_Y;
			}

			for (int x = startX; x < endX; x++) {
				for (int y = startY; y < endY; y++) {
					renderChunk(m_p_world->m_listChunks[x][y]);
					renderBorders(m_p_world->m_listChunks[x][y]);
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
					l_positionOffset += sf::Vector2f(x * g_CHUNK_TEXTURE_SIZE, y * g_CHUNK_TEXTURE_SIZE);

					(*m_p_VertexArray)[l_index + 0].position = l_positionOffset;
					(*m_p_VertexArray)[l_index + 1].position = l_positionOffset + sf::Vector2f(g_CHUNK_TEXTURE_SIZE, 0);
					(*m_p_VertexArray)[l_index + 2].position = l_positionOffset + sf::Vector2f(g_CHUNK_TEXTURE_SIZE, g_CHUNK_TEXTURE_SIZE);
					(*m_p_VertexArray)[l_index + 3].position = l_positionOffset + sf::Vector2f(0, g_CHUNK_TEXTURE_SIZE);

					int l_BlockID = chunk->m_data[x][y];
					
					sf::Vector2f l_texPos = sf::Vector2f((l_BlockID / g_ATLAS_BLOCK_SIZE) * g_CHUNK_TEXTURE_SIZE, (l_BlockID % g_ATLAS_BLOCK_SIZE) * g_CHUNK_TEXTURE_SIZE);

					(*m_p_VertexArray)[l_index + 0].texCoords = l_texPos;
					(*m_p_VertexArray)[l_index + 1].texCoords = l_texPos + sf::Vector2f(g_CHUNK_TEXTURE_SIZE, 0);
					(*m_p_VertexArray)[l_index + 2].texCoords = l_texPos + sf::Vector2f(g_CHUNK_TEXTURE_SIZE, g_CHUNK_TEXTURE_SIZE);
					(*m_p_VertexArray)[l_index + 3].texCoords = l_texPos + sf::Vector2f(0, g_CHUNK_TEXTURE_SIZE);
				}
			}
			sf::RenderStates l_states;
			l_states.texture = &m_p_loader->m_textureAtlas;

			m_p_rw->draw(*m_p_VertexArray, l_states);
		}

		void ManagerRenderer::renderBorders(gp::world::Chunk* chunk)
		{
			for (int y = 0; y < g_CHUNK_SIZE; y++)
			{
				for (int x = 0; x < g_CHUNK_SIZE; x++)
				{
					int l_index = (y * g_CHUNK_SIZE + x) * 4;

					int l_BlockID = chunk->m_data[x][y];
					if (x != 0){
						int l_BlockIDLeftSide = chunk->m_data[(x-1)][y];
						//if (l_BlockIDLeftSide < l_BlockID) {
							sf::Vector2f l_positionOffset = sf::Vector2f(chunk->m_ID * g_CHUNK_SIZE * g_CHUNK_TEXTURE_SIZE);
							l_positionOffset += sf::Vector2f((x-1) * g_CHUNK_TEXTURE_SIZE, y * g_CHUNK_TEXTURE_SIZE);

							(*m_p_VertexArrayBorders)[l_index + 0].position = l_positionOffset;
							(*m_p_VertexArrayBorders)[l_index + 1].position = l_positionOffset + sf::Vector2f(g_CHUNK_TEXTURE_SIZE, 0);
							(*m_p_VertexArrayBorders)[l_index + 2].position = l_positionOffset + sf::Vector2f(g_CHUNK_TEXTURE_SIZE, g_CHUNK_TEXTURE_SIZE);
							(*m_p_VertexArrayBorders)[l_index + 3].position = l_positionOffset + sf::Vector2f(0, g_CHUNK_TEXTURE_SIZE);

							sf::Vector2f l_texPos = sf::Vector2f(( ((l_BlockID-1)*2) / g_ATLAS_BLOCK_SIZE) * g_CHUNK_TEXTURE_SIZE, ( ((l_BlockID-1)*2) % g_ATLAS_BLOCK_SIZE) * g_CHUNK_TEXTURE_SIZE);

							(*m_p_VertexArrayBorders)[l_index + 0].texCoords = l_texPos;
							(*m_p_VertexArrayBorders)[l_index + 1].texCoords = l_texPos + sf::Vector2f(g_CHUNK_TEXTURE_SIZE, 0);
							(*m_p_VertexArrayBorders)[l_index + 2].texCoords = l_texPos + sf::Vector2f(g_CHUNK_TEXTURE_SIZE, g_CHUNK_TEXTURE_SIZE);
							(*m_p_VertexArrayBorders)[l_index + 3].texCoords = l_texPos + sf::Vector2f(0, g_CHUNK_TEXTURE_SIZE);
						//}
					}
				}
			}
			sf::RenderStates l_states;
			l_states.texture = &m_p_loader->m_borderAtlas;

			m_p_rw->draw(*m_p_VertexArrayBorders, l_states);
		}

		void ManagerRenderer::renderObjects()
		{
			m_p_VertexArrayObjects->resize(m_p_objects->m_listObjects.size() * 4);
			for (size_t i = 0; i < m_p_objects->m_listObjects.size(); i++)
			{
				auto l_object = m_p_objects->m_listObjects[i];

				//if (m_p_view->getCenter().x - m_p_view->getSize().x / 2.f < l_it->m_position.x && m_p_view->getCenter().x + m_p_view->getSize().x / 2.f >= l_it->m_position.x && //
				//	m_p_view->getCenter().y - m_p_view->getSize().y / 2.f < l_it->m_position.y && m_p_view->getCenter().y + m_p_view->getSize().y / 2.f >= l_it->m_position.y)   //
				//{
					//std::cout << "Render" << std::endl;
				int l_index = i * 4;

				(*m_p_VertexArrayObjects)[l_index + 0].position = l_object->m_position;
				(*m_p_VertexArrayObjects)[l_index + 1].position = l_object->m_position + sf::Vector2f(l_object->m_size.x, 0);
				(*m_p_VertexArrayObjects)[l_index + 2].position = l_object->m_position + sf::Vector2f(l_object->m_size.x, l_object->m_size.y);
				(*m_p_VertexArrayObjects)[l_index + 3].position = l_object->m_position + sf::Vector2f(0, l_object->m_size.y);
				
				auto l_objectAsset = m_p_loader->m_listObjectAssets[l_object->m_objectAssetID];
				
				(*m_p_VertexArrayObjects)[l_index + 0].texCoords = l_objectAsset->m_PositionTexture;
				(*m_p_VertexArrayObjects)[l_index + 1].texCoords = l_objectAsset->m_PositionTexture + sf::Vector2f(l_objectAsset->m_SizeTexture.x, 0);
				(*m_p_VertexArrayObjects)[l_index + 2].texCoords = l_objectAsset->m_PositionTexture + sf::Vector2f(l_objectAsset->m_SizeTexture.x, l_objectAsset->m_SizeTexture.y);
				(*m_p_VertexArrayObjects)[l_index + 3].texCoords = l_objectAsset->m_PositionTexture + sf::Vector2f(0, l_objectAsset->m_SizeTexture.y);
				//}
			}

			sf::RenderStates l_states;
			l_states.texture = &m_p_loader->m_objectsAtlas;

			m_p_rw->draw(*m_p_VertexArrayObjects, l_states);
		}

		void ManagerRenderer::renderDebug()
		{
			if (m_debugShowObjectHeatmap)
			{
				sf::Vector2i l_blockPosition = m_p_world->convertWorldPosToBlockPos(m_p_view->getCenter() - m_p_view->getSize() / 2.f);
				sf::Vector2i l_size = m_p_world->convertWorldPosToBlockPos(m_p_view->getSize()) + sf::Vector2i(2, 2);
				sf::VertexArray l_array(sf::Quads, l_size.x * l_size.y * 4);
				for (int y = 0; y < l_size.y; y++)
				{
					for (int x = 0; x < l_size.x; x++)
					{
						int l_index = (y * l_size.x + x) * 4;

						sf::Vector2i l_positionOffset = sf::Vector2i(l_blockPosition.x + x, l_blockPosition.y + y);
						sf::Vector2f l_positionOffsetWorld = sf::Vector2f(l_positionOffset.x * g_CHUNK_TEXTURE_SIZE, l_positionOffset.y * g_CHUNK_TEXTURE_SIZE);

						l_array[l_index + 0].position = l_positionOffsetWorld + sf::Vector2f(0, 0);
						l_array[l_index + 1].position = l_positionOffsetWorld + sf::Vector2f(g_CHUNK_TEXTURE_SIZE, 0);
						l_array[l_index + 2].position = l_positionOffsetWorld + sf::Vector2f(g_CHUNK_TEXTURE_SIZE, g_CHUNK_TEXTURE_SIZE);
						l_array[l_index + 3].position = l_positionOffsetWorld + sf::Vector2f(0, g_CHUNK_TEXTURE_SIZE);

						const size_t l_size = m_p_world->getContainer(l_positionOffset) ? m_p_world->getContainer(l_positionOffset)->size() : 0;
						for (int i = 0; i < 4; i++)
						{
							if (l_size < 8)
							{
								l_array[l_index + i].color = sf::Color(0, 0, 255, 32 * l_size);
							}
							else
							{
								l_array[l_index + i].color = sf::Color(0, 0, 255, 32 * 7);
							}

						}
					}
				}

				m_p_rw->draw(l_array);
			}
		}
	}
}