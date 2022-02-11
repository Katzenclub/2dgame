#include "Engine.h"

namespace gp
{
	Engine::Engine(sf::RenderWindow* rw, sf::View* view) :
		m_p_rw(rw),
		m_p_view(view)
	{
		m_p_world = new gp::world::ManagerWorld();
		m_p_ManagerRenderer = new gp::system::ManagerRenderer(m_p_rw, m_p_world);
	}

	Engine::~Engine()
	{
	}

	void Engine::handle()
	{
	}

	void Engine::update()
	{
	}

	void Engine::render()
	{
		m_p_ManagerRenderer->render();
	}

	void Engine::debug()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_positionDebug.x = m_positionDebug.x - m_speedDebug * (m_zoom);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_positionDebug.x = m_positionDebug.x + m_speedDebug * (m_zoom);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_positionDebug.y = m_positionDebug.y - m_speedDebug * (m_zoom);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_positionDebug.y = m_positionDebug.y + m_speedDebug * (m_zoom);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			m_zoom = m_zoom + m_speedZoomDebug;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		{
			m_zoom = m_zoom - m_speedZoomDebug;
		}

		m_p_view->setCenter(m_positionDebug);
		m_p_view->setSize(sf::Vector2f(m_p_rw->getSize()) * m_zoom);
	}
}