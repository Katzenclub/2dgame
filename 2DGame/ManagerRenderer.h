#pragma once
#include <SFML/Graphics.hpp>

#include "ManagerWorld.h"

namespace gp
{
	namespace system
	{
		class ManagerRenderer
		{
		public:
			ManagerRenderer(sf::RenderWindow* rw, gp::world::ManagerWorld* world);
			~ManagerRenderer();

			void render();

		private:
			sf::RenderWindow* m_p_rw;
			sf::VertexArray* m_p_VertexArray;
			gp::world::ManagerWorld* m_p_world;
			
			void renderChunks();			
		};
	}
}