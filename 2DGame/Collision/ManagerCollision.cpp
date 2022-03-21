#include "ManagerCollision.h"

namespace gp
{
	namespace system
	{
		ManagerCollision::ManagerCollision(gp::world::ManagerWorld* MW, gp::object::ManagerObject* MO) : m_p_MO(MO),
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
				sf::Vector2i l_pos = m_p_MW->convertWorldPosToBlockPos(object->m_position);
				sf::Vector2i l_size = m_p_MW->convertWorldPosToBlockPos(object->m_size) + sf::Vector2i(1, 1);
				// Iterate in Range from -radius to +radius around object position.
				for (int y = -l_size.y; y <= l_size.y; y++)
				{
					for (int x = -l_size.x; x <= l_size.x; x++)
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
									
									if (l_direction.y < -0.5f)
									{
										object->m_velocity.y = 0;
									}
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
			for (auto it : m_p_MO->m_listObjects)
			{
				checkPositionIterative(it);
			}
		}

		void ManagerCollision::checkPositionIterative(gp::object::Object* obj)
		{
			sf::Vector2f l_direction = gp::util::getDirectionNormalised(obj->m_positionOld, obj->m_position);
			float l_distance = gp::util::getDistance(obj->m_positionOld, obj->m_position);
			int l_distanceIteration = l_distance;
			float l_distanceLast = l_distance - float(l_distanceIteration);

			sf::Vector2f l_posTMP = obj->m_positionOld;

			for (size_t i = 0; i < l_distanceIteration; i++)
			{
				//CHECK X
				sf::Vector2f l_checkPosition = sf::Vector2f(l_posTMP.x + l_direction.x, l_posTMP.y);
				if (m_p_MW->getBlockIDByBlockPos(m_p_MW->convertWorldPosToBlockPos(l_checkPosition)) == 0)
				{
					l_posTMP = l_checkPosition;
				}
				else
				{
					goto skipx;
				}
			}

			if (l_distanceLast > 0.f)
			{
				//CHECK X Last 
				sf::Vector2f l_checkPosition = sf::Vector2f(l_posTMP.x + l_direction.x * l_distanceLast, l_posTMP.y);
				if (m_p_MW->getBlockIDByBlockPos(m_p_MW->convertWorldPosToBlockPos(l_checkPosition)) == 0)
				{
					l_posTMP = l_checkPosition;
				}
			}
		skipx:

			for (size_t i = 0; i < l_distanceIteration; i++)
			{
				//CHECK Y
				sf::Vector2f l_checkPosition = sf::Vector2f(l_posTMP.x, l_posTMP.y + l_direction.y);
				if (m_p_MW->getBlockIDByBlockPos(m_p_MW->convertWorldPosToBlockPos(l_checkPosition)) == 0)
				{
					l_posTMP = l_checkPosition;
				}
				else
				{
					// Reset Gravity when collide with bottom.
					if (obj->m_position.y >= obj->m_positionOld.y)
					{
						obj->m_velocity.y = 0;
					}
					goto skipy;
				}
			}

			if (l_distanceLast > 0.f)
			{
				//CHECK X Last 
				sf::Vector2f l_checkPosition = sf::Vector2f(l_posTMP.x, l_posTMP.y + l_direction.y * l_distanceLast);
				if (m_p_MW->getBlockIDByBlockPos(m_p_MW->convertWorldPosToBlockPos(l_checkPosition)) == 0)
				{
					l_posTMP = l_checkPosition;
				}
				else
				{
					// Reset Gravity when collide with bottom.
					if (obj->m_position.y >= obj->m_positionOld.y)
					{
						obj->m_velocity.y = 0;
					}
				}


			}
		skipy:

			obj->m_position = l_posTMP;
		}
	}
}
