#pragma once

#include "Object.h"
#include "ManagerWorld.h"

namespace gp
{
	namespace game
	{
		class ManagerPlayer
		{
		public:
			ManagerPlayer(gp::object::Object* objectPlayer, gp::world::ManagerWorld* MW, sf::View* view, sf::RenderWindow* rw);
			~ManagerPlayer();

			void handle(float deltaTime);
			void update(float deltaTime);
			
			gp::object::Object* m_p_objectPlayer;
			gp::world::ManagerWorld* m_p_MW;

			uint16_t m_selectedBlock = 0;

		private:
			sf::View* m_p_view;
			sf::RenderWindow* m_p_rw;

			float m_speed = 1200.f;
			float m_speedZoom = 5.f;
			float m_zoom = 1.f;
		};


	}
}