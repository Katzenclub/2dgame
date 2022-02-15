#include "Engine.h"

namespace gp
{
	Engine::Engine(sf::RenderWindow* rw, sf::View* view) :
		m_p_rw(rw),
		m_p_view(view)
	{
		m_p_Loader = new gp::system::Loader();
		m_debugAtlas.setTexture(&m_p_Loader->m_textureAtlas);
		m_debugAtlas.setSize(sf::Vector2f(m_p_Loader->m_textureAtlas.getSize()));

		m_p_world = new gp::world::ManagerWorld();
		m_p_ManagerRenderer = new gp::system::ManagerRenderer(m_p_rw, m_p_world,m_p_Loader);
	}

	Engine::~Engine()
	{
	}

	void Engine::handle()
	{
	}

	void Engine::update(float deltaTime)
	{
	}

	void Engine::render()
	{
		m_p_ManagerRenderer->render();

		if (m_showAtlas)
		{
			m_p_rw->draw(m_debugAtlas);
		}
	}

	void Engine::debug(float deltaTime)
	{
		ImGui::Checkbox("Show Atlas", &m_showAtlas);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_positionDebug.x = m_positionDebug.x - m_speedDebug * m_zoom * deltaTime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_positionDebug.x = m_positionDebug.x + m_speedDebug * m_zoom * deltaTime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_positionDebug.y = m_positionDebug.y - m_speedDebug * m_zoom * deltaTime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_positionDebug.y = m_positionDebug.y + m_speedDebug * m_zoom * deltaTime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			m_zoom = m_zoom + m_speedZoomDebug * deltaTime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			m_zoom = m_zoom - m_speedZoomDebug * deltaTime;
		}

		m_p_view->setCenter(m_positionDebug);
		m_p_view->setSize(sf::Vector2f(m_p_rw->getSize()) * m_zoom);
	}
}