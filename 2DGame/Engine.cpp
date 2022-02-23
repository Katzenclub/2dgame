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

		sf::Vector2f m_positionSpawn = sf::Vector2f((g_WORLD_SIZE_X * g_CHUNK_SIZE * g_CHUNK_TEXTURE_SIZE) / 2, g_WORLD_SIZE_X * g_CHUNK_SIZE * g_CHUNK_TEXTURE_SIZE * 0.2f);

		m_p_managerWorld = new gp::world::ManagerWorld(m_p_view);
		m_p_managerObject = new gp::object::ManagerObject(m_p_Loader);
		m_p_managerRenderer = new gp::system::ManagerRenderer(m_p_rw, m_p_managerWorld, m_p_managerObject, m_p_Loader, m_p_view);
		m_p_managerPlayer = new gp::game::ManagerPlayer(m_p_managerObject->create(m_positionSpawn, sf::Vector2f(64.f, 64.f), 0,gp::object::player),m_p_managerWorld,m_p_view,m_p_rw);
		m_p_managerCollision = new gp::system::ManagerCollision(m_p_managerWorld,m_p_managerObject);
	}

	Engine::~Engine()
	{
	}

	void Engine::handle(float deltaTime)
	{
		m_p_managerPlayer->handle(deltaTime);
	}

	void Engine::update(float deltaTime)
	{
		m_p_managerPlayer->update(deltaTime);
		m_p_managerObject->update(deltaTime);
		m_p_managerCollision->update(deltaTime);
	}

	void Engine::render()
	{
		m_p_managerRenderer->render(m_p_managerPlayer->m_p_objectPlayer->m_position);

		if (m_showAtlas)
		{
			m_p_rw->draw(m_debugAtlas);
		}
	}

	void Engine::debug(float deltaTime)
	{
		ImGui::Checkbox("Show Atlas", &m_showAtlas);

		

		ImGui::Text("Objects Count: %ld", m_p_managerObject->m_listObjects.size());

		sf::Vector2i l_chunkPos = m_p_managerWorld->convertToChunkPos(m_p_managerPlayer->m_p_objectPlayer->m_position);
		ImGui::Text("Chunkposition: x: %d y: %d", l_chunkPos.x,l_chunkPos.y);
		sf::Vector2i l_blockPos = m_p_managerWorld->convertToBlockPos(m_p_managerPlayer->m_p_objectPlayer->m_position);
		ImGui::Text("Blockposition: x: %d y: %d", l_blockPos.x,l_blockPos.y);
		ImGui::Text("Select Block: MMB");
		ImGui::Text("SelectedBlock: %d", m_p_managerPlayer->m_selectedBlock);
		ImGui::Text("Place Selected Block: LMB");
		ImGui::Text("Spawn Objects: RMB");
		if (ImGui::Button("Kill All"))
		{
			m_p_managerObject->killAll();
		}

		if (ImGui::Button("Save World"))
		{
			m_p_managerWorld->save();
		}
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2f l_positionWorld = m_p_rw->mapPixelToCoords(sf::Mouse::getPosition(*m_p_rw));
			for (int i = 0; i < 10; i++)
			{
				srand(m_p_managerObject->m_clock.getElapsedTime().asMicroseconds() + i * 32);
				m_p_managerObject->create(l_positionWorld, sf::Vector2f(128.f, 128.f), rand() % m_p_Loader->m_listObjectAssets.size(), gp::object::oType::npc)->m_speed = rand() % 500;
			}
		}
	}
}