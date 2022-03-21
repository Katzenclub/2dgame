#include "ManagerCollision.h"

namespace gp
{
	namespace system
	{
		ManagerCollision::ManagerCollision(gp::world::ManagerWorld *MW, gp::object::ManagerObject *MO) : m_p_MO(MO),
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
			for (auto object : m_p_MO->m_listObjects)
			{
				sf::Vector2i l_pos = m_p_MW->convertWorldPosToBlockPos(object->m_position - object->m_size);
				sf::Vector2i l_size = m_p_MW->convertWorldPosToBlockPos(object->m_size) + sf::Vector2i(2, 2);
				for (int y = -l_size.y; y < l_size.y; y++)
				{
					for (int x = -l_size.x; x < l_size.x; x++)
					{
						sf::Vector2i l_curBlockPos = l_pos + sf::Vector2i(x, y);
						auto l_object = m_p_MW->getContainer(l_curBlockPos);
						if (!l_object)
						{
							continue;
						}

						for (auto compObject : *l_object)
						{
							if (compObject != object)
							{
								float l_radius = (object->m_size.y + compObject->m_size.y) * 0.5f;
								float l_distance = gp::util::getDistance(compObject->m_position, object->m_position);
								if (l_distance < l_radius)
								{
									auto l_direction = gp::util::getDirectionNormalised(compObject->m_position, object->m_position);
									std::isnan(l_direction.x) ? l_direction.x = 0.1 : l_direction.x = l_direction.x;
									std::isnan(l_direction.y) ? l_direction.y = -0.1 : l_direction.y = l_direction.y;
									float l_push = (l_distance - l_radius) * 0.5f;

									compObject->m_position = compObject->m_position + l_direction * l_push;
									object->m_position = object->m_position - l_direction * l_push;
								}
							}
						}
					}
				}
			}
		}

		void ManagerCollision::collisionWorldObject(float deltaTime)
		{
		//	for (auto it : m_p_MO->m_listObjects)
		//	{
		//		sf::Vector2i l_pos = m_p_MW->convertWorldPosToBlockPos(it->m_position - it->m_size);
		//		sf::Vector2i l_size = m_p_MW->convertWorldPosToBlockPos(sf::Vector2f(g_CHUNK_TEXTURE_SIZE, g_CHUNK_TEXTURE_SIZE));
		//		for (int y = -l_size.y; y < l_size.y; y++)
		//		{
		//			for (int x = -l_size.x; x < l_size.x; x++)
		//			{
		//				sf::Vector2i l_posCur = sf::Vector2i(l_pos.x + x, l_pos.y + y);
		//
		//				if (m_p_MW->getBlockIDByBlockPos(l_posCur) > 0)
		//				{
		//					std::cout << "Collidion" << std::endl;
		//					sf::Vector2f l_posBlockTMP = sf::Vector2f(l_posCur.x + g_CHUNK_TEXTURE_SIZE * 0.5f, l_posCur.y + g_CHUNK_TEXTURE_SIZE * 0.5f);
		//					collide(it->m_position, l_posBlockTMP, g_CHUNK_TEXTURE_SIZE * 0.5f, g_CHUNK_TEXTURE_SIZE * 0.5f);
		//				}
		//			}
		//		}
		//	}
		}
		//
		//void ManagerCollision::collide(sf::Vector2f& posObj, const sf::Vector2f& posCollider, const float& radiusObj, const float& radiusCollider)
		//{
		//	while (gp::util::getDistance(posObj,posCollider) < radiusObj + radiusCollider)
		//	{
		//		posObj - gp::util::getDirectionNormalised(posObj, posCollider);
		//	}
		//}
	}
}
