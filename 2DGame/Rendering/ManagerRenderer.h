#pragma once
#include <SFML/Graphics.hpp>

#include "../Util/Loader.h"

#include "../World/ManagerWorld.h"
#include "../Object/ManagerObject.h"
#include "../Projectile/ManagerProjectiles.h"

namespace gp
{
	namespace system
	{
		class ManagerRenderer
		{
		public:
			ManagerRenderer(sf::RenderWindow* rw, gp::world::ManagerWorld* world, gp::object::ManagerObject *managerObject, gp::projectile::ManagerProjectiles *managerProjectiles, gp::system::Loader* loader, sf::View *view);
			~ManagerRenderer();

			void render(sf::Vector2f pos);
			
			bool m_debugShowObjectHeatmap = false;
			bool m_debugShowObjectPositions = false;

		private:
			sf::RenderWindow* m_p_rw;
			sf::VertexArray* m_p_VertexArray;
			gp::world::ManagerWorld* m_p_world;
			gp::object::ManagerObject* m_p_objects;
			gp::projectile::ManagerProjectiles* m_p_MP;
			gp::system::Loader* m_p_loader;
			sf::View* m_p_view;
			sf::VertexArray* m_p_VertexArrayObjects;
			sf::VertexArray* m_p_VertexArrayBorders;
			
			void renderChunks(sf::Vector2f pos);	
			void renderChunk(gp::world::Chunk *chunk);
			void renderBorders(gp::world::Chunk *chunk);
			void renderObjects();
			void renderProjectiles();
			void renderDebug();

			void fillVertexArrayBorders(sf::Vector2f positionOffset, sf::Vector2f texPos, int index);			
      
			sf::Vector2f roundVector(sf::Vector2f origin);			

		};
	}
}