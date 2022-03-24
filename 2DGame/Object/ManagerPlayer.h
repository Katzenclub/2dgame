#pragma once

#include "Object.h"
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
			ManagerPlayer(gp::object::Object* objectPlayer, gp::world::ManagerWorld* MW, gp::projectile::ManagerProjectiles *MP, sf::View* view, sf::RenderWindow* rw);
			~ManagerPlayer();

			void handle(float deltaTime);
			void update(float deltaTime);
			
			gp::object::Object* m_p_objectPlayer;
			gp::world::ManagerWorld* m_p_MW;

			uint16_t m_selectedBlock = 0;

			uint16_t m_interactionMode = gp::game::pickaxe;
			float m_speed = 575.f;
			float m_jumpHeight = 1000.f;
		private:
			sf::View* m_p_view;
			sf::RenderWindow* m_p_rw;
			gp::projectile::ManagerProjectiles* m_p_MP;

			float m_speedZoom = 5.f;
			float m_zoom = 1.f;
		};
	}
}