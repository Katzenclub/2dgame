#pragma once

#include "../Object/ManagerObject.h"
#include "../World/ManagerWorld.h"

namespace gp
{
	namespace system
	{
		class ManagerCollision
		{
		public:
			ManagerCollision(gp::world::ManagerWorld* MW, gp::object::ManagerObject* MO);
			~ManagerCollision();

			void update(float deltaTime);

		private:
			gp::world::ManagerWorld* m_p_MW;
			gp::object::ManagerObject* m_p_MO;

			void collisionObjectObject(float deltaTime);
			void collisionWorldObject(float deltaTime);
			void checkPositionIterative(gp::object::Object* obj);
		};
	}
}