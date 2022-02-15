#pragma once
#include <SFML/Graphics.hpp>

#include "Loader.h"

#include "ManagerWorld.h"


namespace gp
{
	namespace system
	{
		class ManagerRenderer
		{
		public:
			ManagerRenderer(sf::RenderWindow* rw, gp::world::ManagerWorld* world,gp::system::Loader* loader);
			~ManagerRenderer();

			void render();

		private:
			sf::RenderWindow* m_p_rw;
			sf::VertexArray* m_p_VertexArray;
			gp::world::ManagerWorld* m_p_world;
			gp::system::Loader* m_p_loader;
			
			void renderChunks();			
		};
	}
}