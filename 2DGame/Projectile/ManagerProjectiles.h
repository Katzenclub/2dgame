#pragma once

#include "../Util/Loader.h"

#include "ProjectileBase.h"

namespace gp
{
	namespace projectile
	{
		class ManagerProjectiles
		{
			// To allow other classes to access the private member. (forward declaration)
			friend class gp::system::ManagerRenderer;

		public:
			ManagerProjectiles(gp::system::Loader* loader);
			~ManagerProjectiles();

			void create(unsigned int IDOwner, gp::system::ProjectileSource *source,sf::Vector2f position,sf::Vector2f direction, float scale = 1.f);
			void create(unsigned int IDOwner, std::string sourceName, sf::Vector2f position, sf::Vector2f direction, float scale = 1.f);
			void update(const float &elapsedTime);
			void updatePosition();
			
			std::vector<gp::projectile::ProjectileBase*> m_listProjectiles;

		private:
			gp::system::Loader* m_p_loader;

			void cleanup();		
			void physics(const float &elapsedTime);
		};
	}
}
