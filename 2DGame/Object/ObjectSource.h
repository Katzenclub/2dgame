#pragma once

// Own
#include "..\Util\Source.h"

namespace gp
{
	namespace object
	{
		class ObjectSource : public gp::system::Source
		{
		public:
			ObjectSource(std::string name, std::string path, sf::Vector2f relativeBoundingBoxSize = sf::Vector2f(1.f,1.f));
			~ObjectSource();

			std::vector<sf::Vector2f> m_boundingBoxPoints;

		private:
			void getLinePoints(size_t pointsCount, sf::Vector2f offset, float distance, bool x,std::vector<sf::Vector2f>& l_points);
			std::vector<sf::Vector2f> getBoundingBoxPoints(sf::Vector2f size);
		};
	}
}