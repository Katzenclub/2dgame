#include "Loader.h"

namespace gp
{
	namespace system
	{
		Loader::Loader()
		{
			m_listBlocks.push_back(new gp::world::Block("Air", "data/assets/blocks/Air.png", { }));
			m_listBlocks.push_back(new gp::world::Block("Wood", "data/assets/blocks/Wood.png", { {"InflictBurning", 5}, {"InflictDrowning", 10} }));
			m_listBlocks.push_back(new gp::world::Block("Dirt", "data/assets/blocks/Dirt.png", { {"InflictBurning", 5}, {"InflictDrowning", 10} }));

			m_textureAtlas = createTextureAtlas(m_listBlocks);
		}

		Loader::~Loader()
		{
		}

		sf::Texture Loader::createTextureAtlas(const std::vector<gp::world::Block*>& listBlocks)
		{
			sf::RenderTexture l_RT;
			l_RT.create(g_CHUNK_TEXTURE_SIZE * g_ATLAS_BLOCK_SIZE, g_CHUNK_TEXTURE_SIZE * g_ATLAS_BLOCK_SIZE);
			l_RT.clear(sf::Color(0,0,0,0));

			for (auto it : m_listBlocks)
			{
				sf::RectangleShape l_shape;
				l_shape.setTexture(&it->m_texture);
				l_shape.setSize(sf::Vector2f(g_CHUNK_TEXTURE_SIZE, g_CHUNK_TEXTURE_SIZE));
				l_shape.setPosition(sf::Vector2f(
					(it->m_ID / g_ATLAS_BLOCK_SIZE) * g_CHUNK_TEXTURE_SIZE,
					(it->m_ID % g_ATLAS_BLOCK_SIZE) * g_CHUNK_TEXTURE_SIZE) );

				l_RT.draw(l_shape);

			}

			l_RT.display();

			return l_RT.getTexture();
		}
		
	}
}