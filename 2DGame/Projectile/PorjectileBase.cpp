#include "ProjectileBase.h"

namespace gp
{
	namespace projectile
	{
		ProjectileBase::ProjectileBase(unsigned int IDOwner, gp::system::ProjectileSource* source, sf::Vector2f position, sf::Vector2f direction, float scale) :
			m_p_source(source),
			m_position(position),
			m_direction(direction),
			m_IDOwner(IDOwner)
		{
			m_speed = m_p_source->m_speed;
			m_lifeTimeCur = m_p_source->m_lifeTimeMax;
			m_damage = m_p_source->m_damage;
			m_size = m_p_source->m_SizeTexture * scale;
		}

		ProjectileBase::~ProjectileBase()
		{
		}

		void ProjectileBase::update(const float& elapsedTime)
		{
			m_position += m_direction * m_speed * elapsedTime;
			m_lifeTimeCur -= elapsedTime;
		}
	}
}