#include "ManagerCollision.h"

namespace gp
{
	namespace system
	{
		ManagerCollision::ManagerCollision(gp::world::ManagerWorld* MW, gp::object::ManagerObject* MO) :
			m_p_MO(MO),
			m_p_MW(MW)
		{
		}

		ManagerCollision::~ManagerCollision()
		{
		}

		void ManagerCollision::update(float deltaTime)
		{
			collisionObjectObject(deltaTime);
			collisionWorldObject(deltaTime);
		}

		void ManagerCollision::collisionObjectObject(float deltaTime)
		{

		}
		
		void ManagerCollision::collisionWorldObject(float deltaTime)
		{
			for (auto it : m_p_MO->m_listObjects)
			{
				sf::Vector2i l_chunkPos = m_p_MW->convertToChunkPos(it->m_position);
				sf::Vector2i l_blockPos = m_p_MW->convertToBlockPos(it->m_position);
				//m_p_MW->m_listChunks
			}
		}
	}
}