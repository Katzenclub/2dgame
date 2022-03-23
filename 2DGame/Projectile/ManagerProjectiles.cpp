#include "ManagerProjectiles.h"

namespace gp
{
	namespace projectile
	{
		ManagerProjectiles::ManagerProjectiles(gp::system::Loader* loader) : 
			m_p_loader(loader)
		{
		}

		ManagerProjectiles::~ManagerProjectiles()
		{
		}

		void ManagerProjectiles::create(unsigned int IDOwner,gp::system::ProjectileSource* source, sf::Vector2f position, sf::Vector2f direction, float scale)
		{
			auto l_projectile = new gp::projectile::ProjectileBase(IDOwner,source, position, direction, scale);
			m_listProjectiles.push_back(l_projectile);
		}

		void ManagerProjectiles::create(unsigned int IDOwner,std::string sourceName, sf::Vector2f position, sf::Vector2f direction, float scale)
		{
			create(IDOwner,m_p_loader->getProjectileByName(sourceName), position, direction, scale);
		}

		void ManagerProjectiles::update(const float& elapsedTime)
		{
			for (auto it : m_listProjectiles)
			{
				it->update(elapsedTime);
			}

			cleanup();
		}

		void ManagerProjectiles::cleanup()
		{
			for (auto it = m_listProjectiles.begin(); it != m_listProjectiles.end(); ++it)
			{
				if ((*it)->m_lifeTimeCur <= 0.f)
				{
					delete (*it);
					it = m_listProjectiles.erase(it);
					it--;
				}
			}
		}
	}
}