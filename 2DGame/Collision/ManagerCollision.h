#pragma once

#include "../Object/ManagerObject.h"
#include "../World/ManagerWorld.h"
#include "../Projectile/ManagerProjectiles.h"

namespace gp
{
	namespace system
	{
		class ManagerCollision
		{
		public:
			ManagerCollision(gp::world::ManagerWorld* MW, gp::object::ManagerObject* MO, gp::projectile::ManagerProjectiles* MP);
			~ManagerCollision();

			void update(float deltaTime);

		private:
			gp::world::ManagerWorld* m_p_MW;
			gp::object::ManagerObject* m_p_MO;
			gp::projectile::ManagerProjectiles* m_p_MP;

			void collisionObjectObject(float deltaTime);
			void collisionWorldObject(float deltaTime);
			void checkPositionIterative(gp::object::ObjectBase* obj);
			void updateObjectBlockPositions();
			void checkProjectiles();

			bool isCollide(std::vector<sf::Vector2f> bound, sf::Vector2f checkPosition);
		};
	}
}