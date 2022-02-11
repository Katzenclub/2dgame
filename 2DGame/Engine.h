#pragma once

#include "ManagerWorld.h"
#include "ManagerRenderer.h"

namespace gp
{
	class Engine
	{
	public:
		Engine(sf::RenderWindow *rw,sf::View *view);
		~Engine();

		void handle();
		void update();
		void render();
		void debug();

	private:

		sf::RenderWindow *m_p_rw;
		sf::View* m_p_view;

		gp::world::ManagerWorld* m_p_world;
		gp::system::ManagerRenderer* m_p_ManagerRenderer;

		sf::Vector2f m_positionDebug;
		float m_speedDebug = 1.5f;
		float m_speedZoomDebug = 0.05f;
		float m_zoom = 1.f;
	};

	
}