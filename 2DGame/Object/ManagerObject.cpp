#include "ManagerObject.h"

namespace gp
{
	namespace object
	{
		ManagerObject::ManagerObject(gp::system::Loader* loader, gp::world::ManagerWorld* MW) :
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
			l_object->m_boundingBoxPoints = m_p_loader->m_listObjectAssets[assetID]->m_boundingBoxPoints;
			m_listObjects.push_back(l_object);
			return l_object;
		}

		void ManagerObject::update(float deltaTime)
		{
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

			physics(deltaTime);

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

		void ManagerObject::updatePosition()
		{
			for (auto it : m_listObjects)
			{
				it->m_positionOld = it->m_position;
			}
		}

		void ManagerObject::physics(float deltaTime)
		{
			float l_velocityMax = 0.f;
			for (auto it : m_listObjects)
			{
				if (!it->m_debugEnableFly)
				{
					if (it->m_velocity.y > l_velocityMax)
					{
						l_velocityMax = it->m_velocity.y;
					}

					// the 144.f are only a speed that looks good for gravitation.
					it->m_velocity.y = it->m_velocity.y + g_RELATIVE_GRAVITY * deltaTime * 144.f;
					it->m_position = it->m_position + it->m_velocity * deltaTime * 144.f + it->m_forceImpulse * deltaTime;
				}
			}
		}
	}
}