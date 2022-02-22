#include "Object.h"

namespace gp
{
	namespace object
	{
		Object::Object(sf::Vector2f position, sf::Vector2f size, unsigned int assetID) :
			m_position(position),
			m_size(size),
			m_objectAssetID(assetID)
		{
		}

		Object::~Object()
		{
		}
	}
}