#include "Framework.h"

namespace gp
{
	//Step 1 Initialisation
	Framework::Framework(bool debug) :
		m_debug(debug)	//is equal to -> m_debug = debug;
	{
		m_p_window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Our Custom-Engine", sf::Style::Default);
		m_p_window->setVerticalSyncEnabled(true);
		ImGui::SFML::Init(*m_p_window);

		m_active = true;

		m_p_viewWorld = new sf::View(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));

		m_p_Engine = new gp::Engine(m_p_window, m_p_viewWorld);
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
			m_deltaTime = deltaTime();
			handle(m_deltaTime);
			if (m_debug)
			{
				debug(m_deltaTime);
			}
			update(m_deltaTime);
			render();
		}
	}

	void Framework::handle(float deltaTime)
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

		m_p_Engine->handle(deltaTime);

		// handle Stuff
	}

	void Framework::update(float deltaTime)
	{
		// update Stuff

		m_p_Engine->update(deltaTime);
	}

	void Framework::render()
	{
		m_p_window->clear(sf::Color(137, 207, 240));
		

		// render Stuff

		m_p_window->setView(*m_p_viewWorld);
		m_p_Engine->render();


		ImGui::SFML::Render(*m_p_window);
		m_p_window->display();
	}

	void Framework::debug(float deltaTime)
	{
		ImGui::Begin("Engine Interface");
		ImGui::Text("Framerate: %0.f", (1.f / m_deltaTime) + 0.5f);

		//if (ImGui::Button("Reset"))
		//{
		//	std::cout << "DEBUG" << std::endl;
		//}
		

		m_p_Engine->debug(deltaTime);
		
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