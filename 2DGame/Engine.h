#pragma once

#include "Loader.h"
#include "ManagerWorld.h"
#include "ManagerObject.h"
#include "ManagerRenderer.h"
#include "ManagerPlayer.h"
#include "ManagerCollision.h"

#include <imgui.h>
#include <imgui-SFML.h>

namespace gp
{
	class Engine
	{
	public:
		Engine(sf::RenderWindow *rw,sf::View *view);
		~Engine();

		void handle(float deltaTime);
		void update(float deltaTime);
		void render();
		void debug(float deltaTime);

	private:

		sf::RenderWindow *m_p_rw;
		sf::View* m_p_view;

		gp::world::ManagerWorld* m_p_managerWorld;
		gp::object::ManagerObject* m_p_managerObject;
		gp::system::ManagerRenderer* m_p_managerRenderer;
		gp::game::ManagerPlayer* m_p_managerPlayer;
		gp::system::ManagerCollision* m_p_managerCollision;
		gp::system::Loader* m_p_Loader;



		sf::RectangleShape m_debugAtlas;
		bool m_showAtlas = false;
	};

	
}