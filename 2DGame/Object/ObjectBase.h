#pragma once

#include "ObjectSource.h"

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

		class ObjectBase
		{
		public:
			ObjectBase(gp::object::ObjectSource* source, sf::Vector2f position, sf::Vector2f size, unsigned int assetID, unsigned int oType);
			~ObjectBase();

			float m_health;
			float damageCollision;

			sf::Vector2f m_size;

			unsigned int m_oType;
			float m_speed = 0.f;
			sf::Vector2f m_direction;
			sf::Vector2f m_position;
			sf::Vector2f m_velocity = sf::Vector2f(0.f, 0.f);

			//Technical Stuff
			sf::Vector2i m_blockPosCur; unsigned int m_ID;

			// Tracked Collider (Blocks)
			std::vector <sf::Vector2f> m_collider;
			sf::Vector2f m_pushback = sf::Vector2f(0, 0);

			// This Position should not be used in any case!
			sf::Vector2f m_positionOld;

			void setImpulse(const sf::Vector2f& directionNormalised, const float& speed);
			void setImpulse(const float& angle, const float& speed);

			sf::Vector2f m_forceImpulse = sf::Vector2f(0.f, 0.f);

			bool m_debugEnableFly = false;

			std::vector<sf::Vector2f> m_boundingBoxPoints;

			gp::object::ObjectSource* m_p_source;

			float m_hitTimeMax = 1.0f;
			float m_hitTimeCur = 0.f;

		private:
		};

		static unsigned int g_objectID = 0;
	}
}