#pragma once

#include <SFML/Graphics.hpp>
#include "../Util/Math.h"

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
	
			sf::Vector2f m_size;
			
			unsigned int m_objectAssetID;
			unsigned int m_oType;
			float m_speed = 0.f;
			sf::Vector2f m_direction;
			sf::Vector2f m_position;
			sf::Vector2f m_velocity = sf::Vector2f(0.f,0.f);
			
			//Technical Stuff
			sf::Vector2i m_blockPosCur;unsigned int m_ID;

			// Tracked Collider (Blocks)
			std::vector <sf::Vector2f> m_collider;
			sf::Vector2f m_pushback = sf::Vector2f(0, 0);
			
			// This Position should not be used in any case!
			sf::Vector2f m_positionOld;

			void setImpulse(const sf::Vector2f &directionNormalised, const float &speed);
			void setImpulse(const float &angle, const float& speed);

			sf::Vector2f m_forceImpulse = sf::Vector2f(0.f,0.f);

			bool m_debugEnableFly = false;

			std::vector<sf::Vector2f> m_boundingBoxPoints;

		private:
		};

		static unsigned int g_objectID = 0;
	}
}