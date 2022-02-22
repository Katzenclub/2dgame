#pragma once

#include "Loader.h"
#include "ManagerWorld.h"
#include "ObjectManager.h"
#include "ManagerRenderer.h"

#include <imgui.h>
#include <imgui-SFML.h>

namespace gp
{
	class Engine
	{
	public:
		Engine(sf::RenderWindow *rw,sf::View *view);
		~Engine();

		void handle();
		void update(float deltaTime);
		void render();
		void debug(float deltaTime);

	private:

		sf::RenderWindow *m_p_rw;
		sf::View* m_p_view;

		gp::world::ManagerWorld* m_p_world;
		gp::object::ManagerObject* m_p_managerObject;
		gp::system::ManagerRenderer* m_p_ManagerRenderer;
		gp::system::Loader* m_p_Loader;

		sf::Vector2f m_positionDebug;
		float m_speedDebug = 1200.f;
		float m_speedZoomDebug = 5.f;
		float m_zoom = 1.f;

		sf::RectangleShape m_debugAtlas;
		bool m_showAtlas = false;
	};

	
}