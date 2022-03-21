#include "ManagerObject.h"

namespace gp
{
	namespace object
	{
		ManagerObject::ManagerObject(gp::system::Loader* loader,gp::world::ManagerWorld *MW) :
			m_p_loader(loader),
			m_pMW(MW)
		{
		}

		ManagerObject::~ManagerObject()
		{
		}

		gp::object::Object* ManagerObject::create(sf::Vector2f position, float scale, unsigned int assetID, unsigned int oType)
		{
			auto l_object = new gp::object::Object(position, m_p_loader->m_listObjectAssets[assetID]->m_SizeTexture * scale, assetID, oType);
			m_listObjects.push_back(l_object);
			return l_object;
		}

		void ManagerObject::update(float deltaTime)
		{
			if (m_debugEnableGravity)
			{
				gravity(deltaTime);
			}
			
			int l_rand = 0;
			for (auto it : m_listObjects)
			{
				l_rand++;
				if (it->m_oType == gp::object::npc)
				{
					if (it->m_speed == 0.f)
					{
						srand(m_clock.getElapsedTime().asMicroseconds() + l_rand);
						it->m_direction = gp::util::getDirectionNormalised(float(rand() % 360));
						it->m_speed = 500.f;
					}

					it->m_position = it->m_position + it->m_direction * it->m_speed * deltaTime;
					it->m_speed = it->m_speed - 250.f * deltaTime;
					if (it->m_speed <= 0.f)
					{
						it->m_speed = 0;
					}
				}
			}

			updateObjectBlockPositions();
			cleanupDebug();
			cleanup();
		}

		void ManagerObject::killAll()
		{
			for (auto it : m_listObjects)
			{
				it->m_HP = 0;
			}
		}

		void ManagerObject::cleanup()
		{
			for (std::vector<gp::object::Object*>::iterator it = m_listObjects.begin(); it != m_listObjects.end(); ++it)
			{
				if ((*it)->m_HP <= 0.f && (*it)->m_oType != gp::object::oType::player)
				{
					m_pMW->removeFromContainer((*it)->m_blockPosCur, (*it));
					delete (*it);
					it = m_listObjects.erase(it);
					it--;
				}
			}
		}

		void ManagerObject::cleanupDebug()
		{
			for (auto it : m_listObjects)
			{
				it->m_collider.clear();
				it->m_pushback = sf::Vector2f(0.f, 0.f);
			}
			
		}

		void ManagerObject::updateObjectBlockPositions()
		{
			for (auto it : m_listObjects)
			{
				sf::Vector2i l_blockPosNow = m_pMW->convertWorldPosToBlockPos(it->m_position);
				if (it->m_blockPosCur != l_blockPosNow)
				{
					if (it->m_blockPosCur.x >= 0 && it->m_blockPosCur.y >= 0)
					{
						m_pMW->removeFromContainer(it->m_blockPosCur, it);
					}
					
					if (l_blockPosNow.x >= 0 && l_blockPosNow.y >= 0)
					{
						m_pMW->addToContainer(l_blockPosNow, it);
					}

					it->m_blockPosCur = l_blockPosNow;
				}
			}
		}
		void ManagerObject::updatePosition()
		{
			for (auto it : m_listObjects)
			{
				it->m_positionOld = it->m_position;
			}
		}
		void ManagerObject::gravity(float deltaTime)
		{
			for (auto it : m_listObjects)
			{
				it->m_velocity.y = it->m_velocity.y + g_RELATIVE_GRAVITY * deltaTime * 144.f;
				it->m_position = it->m_position + it->m_velocity * deltaTime * 144.f;
			}
		}
	}
}