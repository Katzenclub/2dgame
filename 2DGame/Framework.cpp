#include "Framework.h"

namespace gp
{
	//Step 1 Initialisation
	Framework::Framework(bool debug) :
		m_debug(debug)	//is equal to -> m_debug = debug;
	{
		m_p_window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Our Custom-Engine", sf::Style::Default);
		ImGui::SFML::Init(*m_p_window);

		m_active = true;
	}

	//Step last Deleting
	Framework::~Framework()
	{
		ImGui::SFML::Shutdown();
		delete m_p_window;
	}

	//Mainloop
	void Framework::run()
	{
		while (m_active)
		{
			handle();
			if (m_debug)
			{
				debug();
			}
			update(deltaTime());
			render();
		}
	}

	void Framework::handle()
	{
		sf::Event event;
		while (m_p_window->pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(*m_p_window, event);

			if (event.type == sf::Event::Closed)
			{
				m_p_window->close();
				m_active = false;
			}
		}
		ImGui::SFML::Update(*m_p_window, m_clockImGui.restart());

		// handle Stuff
	}

	void Framework::update(float deltaTime)
	{
		// update Stuff
	}

	void Framework::render()
	{
		m_p_window->clear(sf::Color(137, 207, 240));
		ImGui::SFML::Render(*m_p_window);

		// render Stuff

		m_p_window->display();
	}

	void Framework::debug()
	{
		ImGui::Begin("Engine Interface");
		if (ImGui::Button("Reset"))
		{
			std::cout << "DEBUG" << std::endl;
		}
		ImGui::End();
	}

	float Framework::deltaTime()
	{
		//calculate deltatime (its important to decouple game logic from real frametime (because we have different framerates 144 and 60 etc.)
		float l_deltaTime = m_clockFramerate.getElapsedTime().asSeconds();
		m_clockFramerate.restart();

		//This line looks random but it is important to avoid problems like: your pc lacks one time hard and because that the deltaTime would be so high that everything looks wrong in the next frame.
		return (l_deltaTime > 512) ? 512 : l_deltaTime;
		//is equal to
		/*if (l_deltaTime > 512)
		{
			l_deltaTime = 512;
		}
		else
		{
			l_deltaTime = l_deltaTime;
		}*/
	}
}