#include "ObjectManager.h"

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

		void ManagerObject::create(sf::Vector2f position,sf::Vector2f size, unsigned int assetID)
		{
			m_listObjects.push_back(new gp::object::Object(position, size, assetID));
		}

		void ManagerObject::update(float deltaTime)
		{
			for (auto it : m_listObjects)
			{
				srand(m_clock.getElapsedTime().asMicroseconds());
				it->m_position.x = it->m_position.x + ((rand() % 2000) - 1000) * deltaTime;
				it->m_position.y = it->m_position.y + ((rand() % 2000) - 1000) * deltaTime;
			}
		}

		void ManagerObject::cleanup()
		{
			for (std::vector<gp::object::Object*>::iterator it = m_listObjects.begin(); it != m_listObjects.end(); ++it)
			{
				if ((*it)->m_HP <= 0.f)
				{
					delete (*it);
					it = m_listObjects.erase(it);
					it--;
				}
			}
		}
	}
}