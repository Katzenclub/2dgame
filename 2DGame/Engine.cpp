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

		m_positionDebug = sf::Vector2f((g_WORLD_SIZE_X * g_CHUNK_SIZE * g_CHUNK_TEXTURE_SIZE) / 2, g_WORLD_SIZE_X * g_CHUNK_SIZE * g_CHUNK_TEXTURE_SIZE * 0.2f);

		m_p_world = new gp::world::ManagerWorld(m_p_view);
		m_p_managerObject = new gp::object::ManagerObject(m_p_Loader);
		m_p_ManagerRenderer = new gp::system::ManagerRenderer(m_p_rw, m_p_world, m_p_managerObject, m_p_Loader, m_p_view);

		m_p_managerObject->create(m_positionDebug,sf::Vector2f(512,512), 0);
	}

	Engine::~Engine()
	{
	}

	void Engine::handle()
	{
	}

	void Engine::update(float deltaTime)
	{
		m_p_managerObject->update(deltaTime);
	}

	void Engine::render()
	{
		m_p_ManagerRenderer->render(m_positionDebug);

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			m_zoom = 1.f;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2f l_positionWorld = m_p_rw->mapPixelToCoords(sf::Mouse::getPosition());
			m_p_managerObject->create(l_positionWorld, sf::Vector2f(512, 512), 0);
		}

		ImGui::Text("Objects Count: %d", m_p_managerObject->m_listObjects.size());

		m_p_view->setCenter(m_positionDebug);
		m_p_view->setSize(sf::Vector2f(m_p_rw->getSize()) * m_zoom);
	}
}