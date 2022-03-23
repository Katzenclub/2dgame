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
		m_p_managerObject = new gp::object::ManagerObject(m_p_Loader, m_p_managerWorld);
		m_p_managerProjectiles = new gp::projectile::ManagerProjectiles(m_p_Loader);
		m_p_managerRenderer = new gp::system::ManagerRenderer(m_p_rw, m_p_managerWorld, m_p_managerObject, m_p_managerProjectiles, m_p_Loader, m_p_view);
		m_p_managerPlayer = new gp::game::ManagerPlayer(m_p_managerObject->create(m_positionSpawn, 1.f, 0, gp::object::player), m_p_managerWorld,m_p_managerProjectiles, m_p_view, m_p_rw);
		m_p_managerCollision = new gp::system::ManagerCollision(m_p_managerWorld, m_p_managerObject,m_p_managerProjectiles);
	}

	Engine::~Engine()
	{
	}

	void Engine::handle(float deltaTime)
	{
		m_p_managerObject->updatePosition();
		m_p_managerPlayer->handle(deltaTime);
	}

	void Engine::update(float deltaTime)
	{
		m_p_managerObject->update(deltaTime);
		m_p_managerCollision->update(deltaTime);
		m_p_managerProjectiles->update(deltaTime);
		m_p_managerPlayer->update(deltaTime);
	}

	void Engine::render()
	{
		m_p_managerRenderer->render(m_p_managerPlayer->m_p_objectPlayer->m_position);
	}

	void Engine::debug(float deltaTime)
	{
		ImGui::Text("Objects Count: %ld", m_p_managerObject->m_listObjects.size());
		ImGui::Text("Projectile Count: %ld", m_p_managerProjectiles->m_listProjectiles.size());

		ImGui::Text(" ");

		static int page = 0;
		std::vector<std::string> l_taps = { "Block Atlas","Object Atlas","Projectile Atlas"};
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
		else if (page == 2) {
			ImGui::Image(m_p_Loader->m_projectileAtlas);
		}
		ImGui::EndChild();


		ImGui::Checkbox("Show Object Heatmap", &m_p_managerRenderer->m_debugShowObjectHeatmap);
		ImGui::Checkbox("Show Object Positions", &m_p_managerRenderer->m_debugShowObjectPositions);
		ImGui::Checkbox("Fly mode", &m_p_managerPlayer->m_p_objectPlayer->m_debugEnableFly);
		ImGui::InputFloat("Player Speed", &m_p_managerPlayer->m_speed,0.f,0.f,"%.0f");
		ImGui::InputFloat("Player Jump Height", &m_p_managerPlayer->m_jumpHeight, 0.f, 0.f, "%.0f");

		ImGui::Text(" ");

		sf::Vector2i l_chunkPos = m_p_managerWorld->convertBlockPosToChunkPos(m_p_managerPlayer->m_p_objectPlayer->m_blockPosCur);
		ImGui::Text("Player Chunk Pos: x: %d y: %d", l_chunkPos.x, l_chunkPos.y);
		sf::Vector2i l_blockPos = m_p_managerPlayer->m_p_objectPlayer->m_blockPosCur;
		ImGui::Text("Player Block Pos: x: %d y: %d", l_blockPos.x, l_blockPos.y);
		sf::Vector2f l_velocity = m_p_managerPlayer->m_p_objectPlayer->m_velocity;
		ImGui::Text("Player Velocity Pos: x: %f y: %f", l_velocity.x, l_velocity.y);
		ImGui::Text("Player Velocity Speed: %f", gp::util::getDistance(m_p_managerPlayer->m_p_objectPlayer->m_velocity, sf::Vector2f(0.f, 0.f)));
		ImGui::Text(" ");

		ImGui::Text("Select Block: MMB");
		ImGui::Text("SelectedBlock: %d", m_p_managerPlayer->m_selectedBlock);
		ImGui::Text("Place Selected Block: LMB");
		ImGui::Text("Spawn Objects: RMB");

		const char* items[] = { "Pickaxe", "Shoot" };
		static const char* current_item = "Pickaxe";
		if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
				if (ImGui::Selectable(items[n], is_selected))
					current_item = items[n];
				
				if (is_selected)
					ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
			}

			if (current_item == "Pickaxe")
			{
				m_p_managerPlayer->m_interactionMode = gp::game::interactionMode::pickaxe;
			}
			else if (current_item == "Shoot")
			{
				m_p_managerPlayer->m_interactionMode = gp::game::interactionMode::shoot;
			}
			ImGui::EndCombo();
		}

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
			if (m_p_managerWorld->getBlockIDByBlockPos(m_p_managerWorld->convertWorldPosToBlockPos(l_positionWorld)) == 0)
			{
				for (int i = 0; i < 1; i++)
				{
					srand(m_p_managerObject->m_clock.getElapsedTime().asMicroseconds() + i * 32);
					m_p_managerObject->create(l_positionWorld, 1.f, rand() % (m_p_Loader->m_listObjectAssets.size() - 1) + 1, gp::object::oType::npc)->m_speed = rand() % 500;
				}
			}
		}
	}
}