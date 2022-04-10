#pragma once

#include "ObjectBase.h"
#include "../World/ManagerWorld.h"
#include "../Projectile/ManagerProjectiles.h"

namespace gp
{
	namespace game
	{
		enum interactionMode
		{
			shoot,
			pickaxe
		};

		class ManagerPlayer
		{
		public:
			ManagerPlayer(gp::object::ObjectBase* objectPlayer, gp::world::ManagerWorld* MW, gp::projectile::ManagerProjectiles *MP, sf::View* view, sf::RenderWindow* rw, sf::Vector2f spawnPoint);
			~ManagerPlayer();

			void handle(float deltaTime);
			void update(float deltaTime);

			void respawn(); // currently not used
			
			gp::object::ObjectBase* m_p_objectPlayer;
			gp::world::ManagerWorld* m_p_MW;

			uint16_t m_selectedBlock = 0;

			uint16_t m_interactionMode = gp::game::pickaxe;
			float m_speed = 575.f;
			float m_jumpHeight = 1000.f;
			float m_firerate = 10.f;
			float m_tmpTime = 0.f;
			
		private:
			sf::View* m_p_view;
			sf::RenderWindow* m_p_rw;
			gp::projectile::ManagerProjectiles* m_p_MP;

			float m_speedZoom = 5.f;
			float m_zoom = 1.f;
			sf::Vector2f m_spawnPoint; // currently not used
		};
	}
}