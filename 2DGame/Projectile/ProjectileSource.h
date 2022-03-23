#pragma once

#include "SFML/Graphics.hpp"

#include "../Util/Utils.h"

namespace gp
{
	// Forward declaration to access other namespace
	namespace projectile { class ProjectileBase; }

	namespace system
	{
		class ProjectileSource
		{
			// To allow other classes to access the private member. (forward declaration)
			friend class gp::projectile::ProjectileBase;
			friend class Loader;
			friend class ManagerRenderer;

		public:
			ProjectileSource(std::string name, std::string path);
			~ProjectileSource();
		
		private:

			// Render Stuff
			sf::Vector2f m_PositionTexture;
			sf::Vector2f m_SizeTexture;

			// Media Stuff
			sf::Texture m_texture;

			// Software Stuff
			float m_lifeTimeMax;
			float m_speed;
			size_t m_ID;
		};
	}
}