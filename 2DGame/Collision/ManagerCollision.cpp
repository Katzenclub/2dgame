#include "ManagerCollision.h"

namespace gp
{
	namespace system
	{
		ManagerCollision::ManagerCollision(gp::world::ManagerWorld* MW, gp::object::ManagerObject* MO, gp::projectile::ManagerProjectiles* MP) :
			m_p_MO(MO),
			m_p_MW(MW),
			m_p_MP(MP)

		{
		}

		ManagerCollision::~ManagerCollision()
		{
		}

		void ManagerCollision::update(float deltaTime)
		{
			updateObjectBlockPositions();
			collisionObjectObject(deltaTime);
			collisionWorldObject(deltaTime);
			updateObjectBlockPositions();
			checkProjectiles();
		}

		void ManagerCollision::updateObjectBlockPositions()
		{
			for (auto it : m_p_MO->m_listObjects)
			{
				sf::Vector2i l_blockPosNow = m_p_MW->convertWorldPosToBlockPos(it->m_position);
				if (it->m_blockPosCur != l_blockPosNow)
				{
					if (it->m_blockPosCur.x >= 0 && it->m_blockPosCur.y >= 0)
					{
						m_p_MW->removeFromContainer(it->m_blockPosCur, it);
					}

					if (l_blockPosNow.x >= 0 && l_blockPosNow.y >= 0)
					{
						m_p_MW->addToContainer(l_blockPosNow, it);
					}

					it->m_blockPosCur = l_blockPosNow;
				}
			}
		}

		void ManagerCollision::collisionObjectObject(float deltaTime)
		{
			for (int i = 0; i < 4; i++)
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
										std::isnan(l_direction.x) ? l_direction.x = 0.1f : l_direction.x = l_direction.x;
										std::isnan(l_direction.y) ? l_direction.y = -0.1f : l_direction.y = l_direction.y;
										float l_push = (l_distance - l_radius) * 0.5f;

										compObject->m_position = compObject->m_position + l_direction * l_push;
										compObject->m_position.x = roundf(compObject->m_position.x);
										compObject->m_position.y = roundf(compObject->m_position.y);
										//checkPositionIterative(compObject);

										if (l_direction.y < -0.5f)
										{
											object->m_velocity.y = std::min(compObject->m_velocity.y, object->m_velocity.y);
											object->m_forceImpulse = sf::Vector2f(0.f, 0.f);
										}
										object->m_position = object->m_position - l_direction * l_push;
										object->m_position.x = roundf(object->m_position.x);
										object->m_position.y = roundf(object->m_position.y);

										if (object->m_oType == gp::object::oType::player && compObject->m_oType == gp::object::oType::enemy)
										{
											if (object->m_hitTimeCur <= 0.f)
											{
												object->m_health -= compObject->damageCollision;
												object->m_hitTimeCur = object->m_hitTimeMax;
											}
											
										}

										
										//checkPositionIterative(object);
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
			for (auto it : m_p_MO->m_listObjects)
			{
				checkPositionIterative(it);
			}
		}

		bool ManagerCollision::isCollide(std::vector<sf::Vector2f> bound, sf::Vector2f checkPosition)
		{
			for (auto it : bound)
			{
				if (m_p_MW->getBlockIDByBlockPos(m_p_MW->convertWorldPosToBlockPos(checkPosition + it)) != 0)
				{
					return true;
				}
			}
			return false;
		}

		void ManagerCollision::checkPositionIterative(gp::object::ObjectBase* obj)
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
				if (!isCollide(obj->m_boundingBoxPoints, l_checkPosition))
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
				if (!isCollide(obj->m_boundingBoxPoints, l_checkPosition))
				{
					l_posTMP = l_checkPosition;
				}
			}
		skipx:

			for (size_t i = 0; i < l_distanceIteration; i++)
			{
				//CHECK Y
				sf::Vector2f l_checkPosition = sf::Vector2f(l_posTMP.x, l_posTMP.y + l_direction.y);
				if (!isCollide(obj->m_boundingBoxPoints, l_checkPosition))
				{
					l_posTMP = l_checkPosition;
				}
				else
				{
					// Reset Gravity when collide with bottom.
					if (obj->m_position.y >= obj->m_positionOld.y)
					{
						if (obj->m_velocity.y > 20.f)
						{
							obj->m_health -= (obj->m_velocity.y - 20.f ) * 5.f;
							obj->m_hitTimeCur = obj->m_hitTimeMax;
						}
						obj->m_velocity.y = 0;
						obj->m_forceImpulse = sf::Vector2f(0.f, 0.f);
						
						
					}
					else if (obj->m_position.y <= obj->m_positionOld.y)
					{
						//obj->m_forceImpulse = sf::Vector2f(0.f, 0.f);
					}
					goto skipy;
				}
			}

			if (l_distanceLast > 0.f)
			{
				//CHECK X Last 
				sf::Vector2f l_checkPosition = sf::Vector2f(l_posTMP.x, l_posTMP.y + l_direction.y * l_distanceLast);
				if (!isCollide(obj->m_boundingBoxPoints, l_checkPosition))
				{
					l_posTMP = l_checkPosition;
				}
				else
				{
					// Reset Gravity when collide with bottom.
					if (obj->m_position.y >= obj->m_positionOld.y)
					{
						obj->m_velocity.y = 0;
						obj->m_forceImpulse = sf::Vector2f(0.f, 0.f);
					}
					else if (obj->m_position.y <= obj->m_positionOld.y)
					{
						//obj->m_forceImpulse = sf::Vector2f(0.f, 0.f);
					}
				}
			}
		skipy:

			obj->m_position = l_posTMP;
		}

		void ManagerCollision::checkProjectiles()
		{
			for (auto projectile : m_p_MP->m_listProjectiles)
			{
				sf::Vector2i l_blockPos = m_p_MW->convertWorldPosToBlockPos(projectile->m_position);
				if (m_p_MW->getBlockIDByBlockPos(l_blockPos) == 0)
				{
					const int l_rad = 1; // This will be changed later.
					for (int x = -l_rad; x <= l_rad; x++)
					{
						for (int y = -l_rad; y <= l_rad; y++)
						{
							auto l_container = m_p_MW->getContainer(l_blockPos + sf::Vector2i(x, y));
							if (l_container)
							{
								for (auto object : *l_container)
								{
									if (object->m_ID != projectile->m_IDOwner && gp::util::getDistance(object->m_position, projectile->m_position) < object->m_size.y * 0.5f)
									{
										object->setImpulse(projectile->m_direction, projectile->m_speed);
										projectile->m_lifeTimeCur = 0.f;
										object->m_health -= projectile->m_damage;
										object->m_hitTimeCur = object->m_hitTimeMax;
									}
								}
							}
						}
					}
				}
				else
				{
					projectile->m_lifeTimeCur = 0.f;
				}
			}
		}
	}
}