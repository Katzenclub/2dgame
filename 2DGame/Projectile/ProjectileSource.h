#pragma once

// Own
#include "../Util/Source.h"

namespace gp
{
	/**
	 * @brief Forward declaration to access other namespace.
	 */
	namespace projectile { class ProjectileBase; }

	namespace system
	{
		class ProjectileSource : public Source
		{
			/**
			 * @brief To allow other classes to access the private member. (forward declaration).
			 */
			friend class gp::projectile::ProjectileBase;
			friend class Loader;
			friend class ManagerRenderer;

		public:
			ProjectileSource(std::string name, std::string path,float lifeTimeMax, float speed, float damage);
			~ProjectileSource();

			float m_damage;

		private:
			float m_lifeTimeMax;
			float m_speed;
		};
	}
}