#include "Atlas.h"
namespace gp
{
	namespace util
	{
		Atlas::Atlas()
		{
			clear(0);
			m_stepSizeCluster = g_SIZE_ATLAS / g_Size_ARRAY_CLUSTER;
		}

		Atlas::~Atlas()
		{
		}
		
		sf::Texture Atlas::createAtlas(
			const std::vector<gp::object::ObjectAsset*>& list)
		{
			sf::RenderTexture l_RT;
			l_RT.create(g_SIZE_ATLAS, g_SIZE_ATLAS);
			l_RT.setSmooth(true);
			l_RT.clear(sf::Color::Magenta);

			for (auto its : list)
			{
				sf::Vector2i l_size_obj = sf::Vector2i(its->m_texture.getSize().x / m_stepSizeCluster, its->m_texture.getSize().y / m_stepSizeCluster);

				if (its->m_texture.getSize().x % m_stepSizeCluster != 0)
				{
					l_size_obj.x++;
				}
				if (its->m_texture.getSize().y % m_stepSizeCluster != 0)
				{
					l_size_obj.y++;
				}

				sf::Vector2i l_pos_draw;
				if (searchSpace(l_pos_draw, l_size_obj) == true)
				{
					its->m_PositionTexture = sf::Vector2f(l_pos_draw.x * m_stepSizeCluster + 1, l_pos_draw.y * m_stepSizeCluster + 1);
					its->m_SizeTexture = sf::Vector2f(its->m_texture.getSize());
					draw(l_RT, l_pos_draw, &its->m_texture);
				}
				else
				{
					//ERROR
					system("pause");
				}
			}

			l_RT.display();
			return l_RT.getTexture();
		}
		
		bool Atlas::searchSpace(sf::Vector2i& pos, sf::Vector2i size)
		{
			for (int y = 0; y < g_Size_ARRAY_CLUSTER; y++)
			{
				for (int x = 0; x < g_Size_ARRAY_CLUSTER; x++)
				{
					if (m_arrayCluster[x][y] == 0)
					{
						pos.x = x;
						pos.y = y;

						if ((x + (size.x - 1) < g_Size_ARRAY_CLUSTER) && (y + (size.y - 1) < g_Size_ARRAY_CLUSTER))
						{
							if (checkSpace(pos, size))
							{
								fillSpace(pos, size);
								return true;
							}
						}
					}
				}
			}
			return false;
		}

		bool Atlas::checkSpace(sf::Vector2i pos, sf::Vector2i size)
		{
			for (int j = 0; j < size.y; j++)
			{
				for (int i = 0; i < size.x; i++)
				{
					if (m_arrayCluster[pos.x + i][pos.y + j] != 0)
					{
						return false;
					}
				}
			}
			return true;
		}

		void Atlas::fillSpace(sf::Vector2i pos, sf::Vector2i size)
		{
			for (int j = 0; j < size.y; j++)
			{
				for (int i = 0; i < size.x; i++)
				{
					m_arrayCluster[pos.x + i][pos.y + j] = 1;
				}
			}
		}

		void Atlas::draw(sf::RenderTexture& RT, sf::Vector2i pos, sf::Texture* texture)
		{
			sf::RectangleShape l_shape;
			l_shape.setPosition(sf::Vector2f(pos.x * m_stepSizeCluster, pos.y * m_stepSizeCluster));
			l_shape.setTexture(texture, true);
			l_shape.setSize(sf::Vector2f(texture->getSize()));
			RT.draw(l_shape, sf::BlendNone);
		}

		void Atlas::clear(int material)
		{
			for (int i = 0; i < g_Size_ARRAY_CLUSTER; i++)
			{
				for (int j = 0; j < g_Size_ARRAY_CLUSTER; j++)
				{
					m_arrayCluster[i][j] = material;
				}
			}
		}	
	}
}