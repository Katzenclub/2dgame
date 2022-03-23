#pragma once

#include "Util/Loader.h"
#include "World/ManagerWorld.h"
#include "Object/ManagerObject.h"
#include "Rendering/ManagerRenderer.h"
#include "Object/ManagerPlayer.h"
#include "Collision/ManagerCollision.h"
#include "Projectile/ManagerProjectiles.h"

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
		gp::projectile::ManagerProjectiles* m_p_managerProjectiles;
		gp::system::ManagerRenderer* m_p_managerRenderer;
		gp::game::ManagerPlayer* m_p_managerPlayer;
		gp::system::ManagerCollision* m_p_managerCollision;
		gp::system::Loader* m_p_Loader;

	};
}