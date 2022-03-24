#include "Object.h"

namespace gp
{
	namespace object
	{
		Object::Object(sf::Vector2f position, sf::Vector2f size, unsigned int assetID, unsigned int oType) :
			m_position(position),
			m_positionOld(position),
			m_size(size),
			m_objectAssetID(assetID),
			m_oType(oType)
		{
			m_ID = gp::object::g_objectID++;
		}

		Object::~Object()
		{
		}

		void Object::setImpulse(const sf::Vector2f& directionNormalised, const float& speed)
		{
			if (m_forceImpulse == sf::Vector2f(0.f, 0.f))
			{
				m_forceImpulse = directionNormalised * speed;
			}
			//m_velocity = m_velocity + directionNormalised * speed;
		}

		void Object::setImpulse(const float& angle, const float& speed)
		{
			if (m_forceImpulse == sf::Vector2f(0.f, 0.f))
			{
				m_forceImpulse = gp::util::getDirectionNormalised(angle) * speed;
			}
		}
	}
}