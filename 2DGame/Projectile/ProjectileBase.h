#pragma once

#include "ProjectileSource.h"

namespace gp
{
	// Forward declaration to access other namespace
	namespace system { class ManagerRenderer; class ManagerCollision;}

	namespace projectile
	{
		class ProjectileBase
		{
			// To allow other classes to access the private member. (forward declaration)
			friend class ManagerProjectiles;
			friend class gp::system::ManagerRenderer;
			friend class gp::system::ManagerCollision;

		public:
			ProjectileBase(unsigned int IDOwner, gp::system::ProjectileSource* source,sf::Vector2f position,sf::Vector2f direction, float scale);
			~ProjectileBase();

			void update(const float& elapsedTime);

		private:
			gp::system::ProjectileSource* m_p_source;
			sf::Vector2f m_position;
			sf::Vector2f m_positionOld;
			sf::Vector2f m_direction;
			sf::Vector2f m_size;
			sf::Vector2f m_velocity;
			float m_speed;
			float m_lifeTimeCur;
			float m_damage;

			unsigned int m_IDOwner;
		};
	}
}