#pragma once

#include <SFML/Graphics.hpp>

namespace gp
{
	namespace object
	{
		enum oType
		{
			player,
			npc,
			enemy
		};

		class Object
		{
		public:
			Object(sf::Vector2f position,sf::Vector2f size, unsigned int assetID, unsigned int oType);
			~Object();
			
			float m_HP = 100.f;
			
			sf::Vector2f m_position;
			sf::Vector2f m_size;
			
			unsigned int m_objectAssetID;
			unsigned int m_oType;
			float m_speed = 0.f;
			sf::Vector2f m_direction;
			
			//Technical Stuff
			sf::Vector2i m_blockPosCur;unsigned int m_ID;
		private:

			

			
			
			
			
		};

		static unsigned int g_objectID = 0;
	}
}