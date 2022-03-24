#include "ObjectBase.h"

namespace gp
{
	namespace object
	{
		ObjectBase::ObjectBase(gp::object::ObjectSource* source, sf::Vector2f position, sf::Vector2f size, unsigned int assetID, unsigned int oType) :
			m_position(position),
			m_positionOld(position),
			m_size(size),
			m_p_source(source),
			m_oType(oType)
		{
			m_ID = gp::object::g_objectID++;
		}

		ObjectBase::~ObjectBase()
		{
		}

		void ObjectBase::setImpulse(const sf::Vector2f& directionNormalised, const float& speed)
		{
			if (m_forceImpulse == sf::Vector2f(0.f, 0.f))
			{
				m_forceImpulse = directionNormalised * speed;
			}
			//m_velocity = m_velocity + directionNormalised * speed;
		}

		void ObjectBase::setImpulse(const float& angle, const float& speed)
		{
			if (m_forceImpulse == sf::Vector2f(0.f, 0.f))
			{
				m_forceImpulse = gp::util::getDirectionNormalised(angle) * speed;
			}
		}
	}
}