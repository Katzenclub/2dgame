#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "../World/WorldConstants.h"
#include <iostream>

namespace gp
{
	namespace object
	{
		class ObjectAsset
		{
		public:
			ObjectAsset(std::string name, std::string path);
			~ObjectAsset();

			std::string m_name;
			sf::Texture m_texture;

			unsigned int m_ID;

			sf::Vector2f m_PositionTexture;
			sf::Vector2f m_SizeTexture;

			std::vector<sf::Vector2f> m_boundingBoxPoints;

		private:

			void getLinePoints(size_t pointsCount, sf::Vector2f offset, float distance, bool x,std::vector<sf::Vector2f>& l_points);
			std::vector<sf::Vector2f> getBoundingBoxPoints(sf::Vector2f size);
		};

		static unsigned int g_objectAssetID = 0;
	}
}