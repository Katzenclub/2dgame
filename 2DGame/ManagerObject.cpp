#include "ManagerObject.h"

namespace gp
{
	namespace object
	{
		ManagerObject::ManagerObject(gp::system::Loader* loader) :
			m_p_loader(loader)
		{
		}

		ManagerObject::~ManagerObject()
		{
		}

		gp::object::Object* ManagerObject::create(sf::Vector2f position,sf::Vector2f size, unsigned int assetID, unsigned int oType)
		{
			auto l_object = new gp::object::Object(position, size, assetID, oType);
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
						it->m_direction = gp::utility::getDirectionNormalised(float(rand() % 360));
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
					delete (*it);
					it = m_listObjects.erase(it);
					it--;
				}
			}
		}
	}
}