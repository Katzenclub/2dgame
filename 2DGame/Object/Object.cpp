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
		}

		Object::~Object()
		{
		}
	}
}