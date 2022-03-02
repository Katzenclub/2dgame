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
			for (auto it : m_p_MO->m_listObjects)
			{
				sf::Vector2i l_pos = m_p_MW->convertWorldPosToBlockPos(it->m_position - it->m_size);
				sf::Vector2i l_size = m_p_MW->convertWorldPosToBlockPos(it->m_size) + sf::Vector2i(2, 2);
				for (int y = -l_size.y; y < l_size.y; y++)
				{
					for (int x = -l_size.x; x < l_size.x; x++)
					{
						sf::Vector2i l_curBlockPos = l_pos + sf::Vector2i(x, y);
						auto l_object = m_p_MW->getContainer(l_curBlockPos);
						if (l_object)
						{
							for (auto its : *l_object) 
							{
								if (its != it)
								{
									float l_radius = (it->m_size.y + its->m_size.y) * 0.75f;
									float l_distance = gp::util::getDistance(its->m_position, it->m_position);
									if (l_distance < l_radius)
									{
										auto l_direction = gp::util::getDirectionNormalised(its->m_position, it->m_position);
										std::isnan(l_direction.x) ? l_direction.x = 0.1 : l_direction.x = l_direction.x;
										std::isnan(l_direction.y) ? l_direction.y = -0.1 : l_direction.y = l_direction.y;
										float l_push = (l_distance - l_radius) * 0.5f;

										its->m_position = its->m_position + l_direction * l_push;
										it->m_position = it->m_position - l_direction * l_push;
									}
								}
							}
						}
					}
				}
			}
		}
		
		void ManagerCollision::collisionWorldObject(float deltaTime)
		{

		}	
	}
}