#include "ManagerWorld.h"

namespace gp
{
	namespace world
	{
		ManagerWorld::ManagerWorld()
		{
			m_p_chunk = new gp::world::Chunk(sf::Vector2i(0, 0));
		}

		ManagerWorld::~ManagerWorld()
		{
		}
		void ManagerWorld::update()
		{
		}
	}
}