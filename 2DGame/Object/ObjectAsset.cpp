#include "ObjectAsset.h"

namespace gp
{
	namespace object
	{
		ObjectAsset::ObjectAsset(std::string name, std::string path) :
			m_name(name)			
		{
			m_ID = g_objectAssetID;
			g_objectAssetID++;
			m_texture.loadFromFile(path);
			m_boundingBoxPoints = getBoundingBoxPoints((sf::Vector2f(m_texture.getSize()) / 2.f) * 0.95f);
		}

		ObjectAsset::~ObjectAsset()
		{
		}

		void ObjectAsset::getLinePoints(size_t pointsCount, sf::Vector2f offset, float distance, bool x, std::vector<sf::Vector2f> &l_points)
		{
			float l_base = 0.f;
			for (size_t i = 0; i <= pointsCount; i++)
			{	
				if (x)
				{
					l_points.push_back(sf::Vector2f(l_base + offset.x, offset.y));
				}
				else
				{
					l_points.push_back(sf::Vector2f( offset.x,l_base + offset.y));
				}
				l_base = l_base + distance;	
			}
		}

		std::vector<sf::Vector2f> ObjectAsset::getBoundingBoxPoints(sf::Vector2f size)
		{
			std::vector<sf::Vector2f> l_points;
			size_t l_pointsCountx = (size.x *2.f) / g_CHUNK_TEXTURE_SIZE;
			getLinePoints(l_pointsCountx,sf::Vector2f(-size.x, - size.y), g_CHUNK_TEXTURE_SIZE, true, l_points);

			size_t l_pointsCounty = (size.y * 2.f) / g_CHUNK_TEXTURE_SIZE;
			getLinePoints(l_pointsCounty, sf::Vector2f(+size.x, -size.y), g_CHUNK_TEXTURE_SIZE, false, l_points);
			
			getLinePoints(l_pointsCountx, sf::Vector2f(+size.x, +size.y), -g_CHUNK_TEXTURE_SIZE, true, l_points);

			getLinePoints(l_pointsCounty, sf::Vector2f(-size.x, +size.y), -g_CHUNK_TEXTURE_SIZE, false, l_points);
			return l_points;
		}
	}
}