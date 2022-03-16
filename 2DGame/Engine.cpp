#include "Engine.h"

namespace gp
{
	Engine::Engine(sf::RenderWindow* rw, sf::View* view) :
		m_p_rw(rw),
		m_p_view(view)
	{
		m_p_Loader = new gp::system::Loader();

		sf::Vector2f m_positionSpawn = sf::Vector2f((g_WORLD_SIZE_X * g_CHUNK_SIZE * g_CHUNK_TEXTURE_SIZE) / 2, g_WORLD_SIZE_X * g_CHUNK_SIZE * g_CHUNK_TEXTURE_SIZE * 0.2f);

		m_p_managerWorld = new gp::world::ManagerWorld(m_p_view);
		m_p_managerObject = new gp::object::ManagerObject(m_p_Loader,m_p_managerWorld);
		m_p_managerRenderer = new gp::system::ManagerRenderer(m_p_rw, m_p_managerWorld, m_p_managerObject, m_p_Loader, m_p_view);
		m_p_managerPlayer = new gp::game::ManagerPlayer(m_p_managerObject->create(m_positionSpawn, 1.f, 0,gp::object::player),m_p_managerWorld,m_p_view,m_p_rw);
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
		
		m_p_managerObject->update(deltaTime);
		m_p_managerCollision->update(deltaTime);
		m_p_managerPlayer->update(deltaTime);
	}

	void Engine::render()
	{
		m_p_managerRenderer->render(m_p_managerPlayer->m_p_objectPlayer->m_position);
	}

	void Engine::debug(float deltaTime)
	{
		ImGui::Text("Objects Count: %ld", m_p_managerObject->m_listObjects.size());

		ImGui::Text(" ");

		static int page = 0;
		std::vector<std::string> l_taps = { "Block Atlas","Object Atlas" };
		ImGui::BeginGroup();
		for (int i = 0; i < l_taps.size(); i++)
		{
			if (ImGui::Button(l_taps[i].c_str(), ImVec2(512 / l_taps.size(), 25)))
				page = i;
			ImGui::SameLine();
		}
		ImGui::EndGroup();
		ImGui::BeginChild("InnerRegion", ImVec2(0, 512), true, ImGuiWindowFlags_AlwaysHorizontalScrollbar);
		if (page == 0) {
			ImGui::Image(m_p_Loader->m_textureAtlas);
		}
		else if (page == 1) {
			ImGui::Image(m_p_Loader->m_objectsAtlas);
		}	
		ImGui::EndChild();


		ImGui::Checkbox("Show Object Heatmap", &m_p_managerRenderer->m_debugShowObjectHeatmap);
		
		ImGui::Text(" ");

		sf::Vector2i l_chunkPos = m_p_managerWorld->convertBlockPosToChunkPos(m_p_managerPlayer->m_p_objectPlayer->m_blockPosCur);
		ImGui::Text("Player Chunk Pos: x: %d y: %d", l_chunkPos.x,l_chunkPos.y);
		sf::Vector2i l_blockPos = m_p_managerPlayer->m_p_objectPlayer->m_blockPosCur;
		ImGui::Text("Player Block Pos: x: %d y: %d", l_blockPos.x,l_blockPos.y);

		ImGui::Text(" ");

		ImGui::Text("Select Block: MMB");
		ImGui::Text("SelectedBlock: %d", m_p_managerPlayer->m_selectedBlock);
		ImGui::Text("Place Selected Block: LMB");
		ImGui::Text("Spawn Objects: RMB");

		ImGui::Text(" ");

		if (ImGui::Button("Kill All"))
		{
			m_p_managerObject->killAll();
		}

		if (ImGui::Button("Save World"))
		{
			m_p_managerWorld->save();
		}

		ImGui::Text(" ");

		sf::Vector2f l_positionWorld = m_p_rw->mapPixelToCoords(sf::Mouse::getPosition(*m_p_rw));
		sf::Vector2i l_mouseBlockPos = m_p_managerWorld->convertWorldPosToBlockPos(l_positionWorld);
		sf::Vector2i l_mouseChunkPos = m_p_managerWorld->convertBlockPosToChunkPos(l_mouseBlockPos);
		ImGui::Text("Mouse Chunk Pos: x: %d y: %d", l_mouseChunkPos.x, l_mouseChunkPos.y);
		sf::Vector2i l_mouseLocalBlockPos = m_p_managerWorld->convertBlockPosToLocalBlockPos(l_mouseBlockPos);
		ImGui::Text("Mouse Local  Block Pos: x: %d y: %d", l_mouseLocalBlockPos.x, l_mouseLocalBlockPos.y);
		ImGui::Text("Mouse Container Size: %ld\n", (m_p_managerWorld->getContainer(l_mouseBlockPos)) ? m_p_managerWorld->getContainer(l_mouseBlockPos)->size() : 0);
		if (m_p_managerWorld->getContainer(l_mouseBlockPos))
		{
			ImGui::Text("Container Found");
		}

		ImGui::Text(" ");

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2f l_positionWorld = m_p_rw->mapPixelToCoords(sf::Mouse::getPosition(*m_p_rw));
			for (int i = 0; i < 1; i++)
			{
				srand(m_p_managerObject->m_clock.getElapsedTime().asMicroseconds() + i * 32);
				m_p_managerObject->create(l_positionWorld, 1.f, rand() % (m_p_Loader->m_listObjectAssets.size()-1)+1, gp::object::oType::npc)->m_speed = rand() % 500;
			}
		}
	}
}