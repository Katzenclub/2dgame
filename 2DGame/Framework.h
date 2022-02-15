#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

#include <rapidxml.hpp>

#include "Engine.h"

namespace gp
{
	//Step 0 Definition
	class Framework
	{
	public:
		Framework(bool debug);
		~Framework();

		void run();

	private:

		void handle();
		void update(float deltaTime);
		void render();
		void debug(float deltaTime);

		float deltaTime();
		float m_deltaTime;

		sf::RenderWindow* m_p_window;
		sf::Clock m_clockFramerate;
		sf::Clock m_clockImGui;

		sf::View *m_p_viewWorld;

		gp::Engine *m_p_Engine;

		bool m_debug;
		bool m_active;
	};
}