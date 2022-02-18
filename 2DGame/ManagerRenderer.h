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
			ManagerRenderer(sf::RenderWindow* rw, gp::world::ManagerWorld* world,gp::system::Loader* loader, sf::View *view);
			~ManagerRenderer();

			void render(sf::Vector2f pos);

		private:
			sf::RenderWindow* m_p_rw;
			sf::VertexArray* m_p_VertexArray;
			gp::world::ManagerWorld* m_p_world;
			gp::system::Loader* m_p_loader;
			sf::View* m_p_view;
			
			void renderChunks(sf::Vector2f pos);	
			void renderChunk(gp::world::Chunk *chunk);
		};
	}
}