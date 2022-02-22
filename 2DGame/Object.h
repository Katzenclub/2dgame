#pragma once

#include <SFML/Graphics.hpp>

namespace gp
{
	namespace object
	{
		class Object
		{
		public:
			Object(sf::Vector2f position,sf::Vector2f size, unsigned int assetID);
			~Object();
			
			float m_HP;
			
			sf::Vector2f m_position;
			sf::Vector2f m_size;
			
unsigned int m_objectAssetID;
		private:

			

			

			unsigned int m_ID;
			
		};

		static unsigned int g_objectID = 0;
	}
}