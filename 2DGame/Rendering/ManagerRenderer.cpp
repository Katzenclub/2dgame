#include "ManagerRenderer.h"
#include <iostream>
namespace gp
{
	namespace system
	{
		ManagerRenderer::ManagerRenderer(sf::RenderWindow* rw, gp::world::ManagerWorld* world, gp::object::ManagerObject* managerObject, gp::projectile::ManagerProjectiles* managerProjectiles, gp::system::Loader* loader, sf::View* view) :
			m_p_rw(rw),
			m_p_world(world),
			m_p_objects(managerObject),
			m_p_MP(managerProjectiles),
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
			renderProjectiles();
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

					sf::Vector2f l_texPos = m_p_loader->m_listBlocks[chunk->m_data[x][y]]->m_PositionTexture;
					// Texture Coordinates					  = UVPosition + Round to avoid flickering + TextureBound
					(*m_p_VertexArray)[l_index + 0].texCoords = l_texPos + sf::Vector2f(0.5f, 0.5f);
					(*m_p_VertexArray)[l_index + 1].texCoords = l_texPos + sf::Vector2f(-1.f, 0.5f) + sf::Vector2f(g_CHUNK_TEXTURE_SIZE, 0.f);
					(*m_p_VertexArray)[l_index + 2].texCoords = l_texPos + sf::Vector2f(-1.f, -1.f) + sf::Vector2f(g_CHUNK_TEXTURE_SIZE, g_CHUNK_TEXTURE_SIZE);
					(*m_p_VertexArray)[l_index + 3].texCoords = l_texPos + sf::Vector2f(0.5f, -1.f) + sf::Vector2f(0.f, g_CHUNK_TEXTURE_SIZE);
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
				auto l_object = m_p_objects->m_listObjects[i];

				int l_index = i * 4;
				auto l_size = sf::Vector2f(l_object->m_size.x * 0.5f, l_object->m_size.y * 0.5f);

				(*m_p_VertexArrayObjects)[l_index + 0].position = l_object->m_position + sf::Vector2f(-l_size.x, -l_size.y);
				(*m_p_VertexArrayObjects)[l_index + 1].position = l_object->m_position + sf::Vector2f(l_size.x, -l_size.y);
				(*m_p_VertexArrayObjects)[l_index + 2].position = l_object->m_position + sf::Vector2f(l_size.x, l_size.y);
				(*m_p_VertexArrayObjects)[l_index + 3].position = l_object->m_position + sf::Vector2f(-l_size.x, l_size.y);

				auto l_p_source = l_object->m_p_source;
				(*m_p_VertexArrayObjects)[l_index + 0].texCoords = l_p_source->m_PositionTexture + sf::Vector2f(0.5f, 0.5f) + sf::Vector2f(0, 0);
				(*m_p_VertexArrayObjects)[l_index + 1].texCoords = l_p_source->m_PositionTexture + sf::Vector2f(-1.f, 0.5f) + sf::Vector2f(l_p_source->m_SizeTexture.x, 0);
				(*m_p_VertexArrayObjects)[l_index + 2].texCoords = l_p_source->m_PositionTexture + sf::Vector2f(-1.f, -1.f) + sf::Vector2f(l_p_source->m_SizeTexture.x, l_p_source->m_SizeTexture.y);
				(*m_p_VertexArrayObjects)[l_index + 3].texCoords = l_p_source->m_PositionTexture + sf::Vector2f(0.5f, -1.f) + sf::Vector2f(0, l_p_source->m_SizeTexture.y);
			}

			sf::RenderStates l_states;
			l_states.texture = &m_p_loader->m_objectsAtlas;

			m_p_rw->draw(*m_p_VertexArrayObjects, l_states);
		}

		void ManagerRenderer::renderProjectiles()
		{
			size_t l_size = m_p_MP->m_listProjectiles.size();
			m_p_VertexArrayObjects->resize(l_size * 4);
			for (size_t i = 0; i < l_size; i++)
			{
				auto l_object = m_p_MP->m_listProjectiles[i];

				int l_index = i * 4;
				auto l_size = sf::Vector2f(l_object->m_size.x * 0.5f, l_object->m_size.y * 0.5f);

				sf::Transform l_transform;
				l_transform.rotate(gp::util::getDegAngle(gp::util::getDirectionNormalised(l_object->m_positionOld, l_object->m_position)));
				
				(*m_p_VertexArrayObjects)[l_index + 0].position = l_object->m_position + l_transform.transformPoint(sf::Vector2f(-l_size.x, -l_size.y));
				(*m_p_VertexArrayObjects)[l_index + 1].position = l_object->m_position + l_transform.transformPoint( sf::Vector2f(l_size.x, -l_size.y));
				(*m_p_VertexArrayObjects)[l_index + 2].position = l_object->m_position + l_transform.transformPoint( sf::Vector2f(l_size.x, l_size.y));
				(*m_p_VertexArrayObjects)[l_index + 3].position = l_object->m_position + l_transform.transformPoint( sf::Vector2f(-l_size.x, l_size.y));

				auto l_source = l_object->m_p_source;
				(*m_p_VertexArrayObjects)[l_index + 0].texCoords = l_source->m_PositionTexture + sf::Vector2f(0.5f, 0.5f) + sf::Vector2f(0, 0);
				(*m_p_VertexArrayObjects)[l_index + 1].texCoords = l_source->m_PositionTexture + sf::Vector2f(-1.f, 0.5f) + sf::Vector2f(l_source->m_SizeTexture.x, 0);
				(*m_p_VertexArrayObjects)[l_index + 2].texCoords = l_source->m_PositionTexture + sf::Vector2f(-1.f, -1.f) + sf::Vector2f(l_source->m_SizeTexture.x, l_source->m_SizeTexture.y);
				(*m_p_VertexArrayObjects)[l_index + 3].texCoords = l_source->m_PositionTexture + sf::Vector2f(0.5f, -1.f) + sf::Vector2f(0, l_source->m_SizeTexture.y);
			}

			sf::RenderStates l_states;
			l_states.texture = &m_p_loader->m_projectileAtlas;

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
							int l_intensity = 4;

							if (l_size < l_intensity)
							{
								l_array[l_index + i].color = sf::Color(0, 0, 255, ((256 / l_intensity) - 1) * l_size);
							}
							else
							{
								l_array[l_index + i].color = sf::Color(0, 0, 255, ((256 / l_intensity) - 1) * l_intensity);
							}

						}
					}
				}

				m_p_rw->draw(l_array);
			}
			
			if (m_debugShowObjectPositions)
			{
				sf::CircleShape l_circle;
				l_circle.setPointCount(5);
				l_circle.setFillColor(sf::Color::Magenta);
				l_circle.setOutlineThickness(2.f);
				l_circle.setOutlineColor(sf::Color::Green);
				l_circle.setRadius(8.f);
				l_circle.setOrigin(l_circle.getRadius(), l_circle.getRadius());

				sf::CircleShape l_circleRadius;
				l_circleRadius.setFillColor(sf::Color::Transparent);
				l_circleRadius.setOutlineColor(sf::Color::Red);
				l_circleRadius.setOutlineThickness(1.f);

				size_t l_count = 5;
				sf::VertexArray l_linestrip(sf::PrimitiveType::LinesStrip, l_count);
				for (size_t i = 0; i < l_count; i++)
				{
					l_linestrip[i].color = sf::Color::Green;
				}

				for (auto it : m_p_objects->m_listObjects)
				{
					if (m_p_view->getCenter().x - m_p_view->getSize().x * 0.5f < it->m_position.x && m_p_view->getCenter().x + m_p_view->getSize().x * 0.5f > it->m_position.x &&
						m_p_view->getCenter().y - m_p_view->getSize().y * 0.5f < it->m_position.y && m_p_view->getCenter().y + m_p_view->getSize().y * 0.5f > it->m_position.y)
					{
						size_t l_countb = it->m_boundingBoxPoints.size();
						sf::VertexArray l_linestripb(sf::PrimitiveType::LinesStrip, l_countb + 1);
						for (size_t i = 0; i < l_countb; i++)
						{
							l_linestripb[i].color = sf::Color::Red;
							l_linestripb[i].position = it->m_boundingBoxPoints[i] + it->m_position;
							
							l_circle.setPosition(l_linestripb[i].position);
							l_circle.rotate(5.f);
							m_p_rw->draw(l_circle);
						}
						l_linestripb[l_countb].position = it->m_boundingBoxPoints[0] + it->m_position;
						l_linestripb[l_countb].color = sf::Color::Red;
						m_p_rw->draw(l_linestripb);

						l_circleRadius.setPosition(it->m_position);
						l_circleRadius.setRadius(it->m_size.y * 0.5f);
						l_circleRadius.setOrigin(l_circleRadius.getRadius(), l_circleRadius.getRadius());
						m_p_rw->draw(l_circleRadius);

						if (it->m_pushback != sf::Vector2f(0.f, 0.f))
						{
							//std::cout << it->m_pushback.x << std::endl;
							l_circle.setPosition(it->m_pushback);
							m_p_rw->draw(l_circle);					
						}

						for (auto its : it->m_collider)
						{
							l_circleRadius.setPosition(its);
							l_circleRadius.setRadius(g_CHUNK_TEXTURE_SIZE * 0.5f);
							l_circleRadius.setOrigin(l_circleRadius.getRadius(), l_circleRadius.getRadius());
							m_p_rw->draw(l_circleRadius);
							//std::cout << "Hallo" << std::endl;
						}
					}
				}
			}
		}
	}
}