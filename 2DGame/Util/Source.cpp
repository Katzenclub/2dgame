#include "Source.h"

namespace gp
{
	namespace system
	{
		Source::Source(std::string name, std::string path) :
			m_name(name)
		{
			m_ID = gp::util::hash(name.c_str());
			m_texture.loadFromFile(path);
			m_SizeTexture = sf::Vector2f(m_texture.getSize());
		}

		Source::~Source()
		{
		}
	}
}