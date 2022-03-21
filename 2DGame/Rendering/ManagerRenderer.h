#pragma once
#include <SFML/Graphics.hpp>

#include "../Util/Loader.h"

#include "../World/ManagerWorld.h"
#include "../Object/ManagerObject.h"


namespace gp
{
	namespace system
	{
		class ManagerRenderer
		{
		public:
			ManagerRenderer(sf::RenderWindow* rw, gp::world::ManagerWorld* world, gp::object::ManagerObject *managerObject, gp::system::Loader* loader, sf::View *view);
			~ManagerRenderer();

			void render(sf::Vector2f pos);
			
			bool m_debugShowObjectHeatmap = false;
			bool m_debugShowObjectPositions = false;

		private:
			sf::RenderWindow* m_p_rw;
			sf::VertexArray* m_p_VertexArray;
			gp::world::ManagerWorld* m_p_world;
			gp::object::ManagerObject* m_p_objects;
			gp::system::Loader* m_p_loader;
			sf::View* m_p_view;
			sf::VertexArray* m_p_VertexArrayObjects;
			
			void renderChunks(sf::Vector2f pos);	
			void renderChunk(gp::world::Chunk *chunk);
			void renderObjects();
			void renderDebug();

			
		};
	}
}