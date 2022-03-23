#include "ProjectileSource.h"

namespace gp
{
	namespace system
	{
		ProjectileSource::ProjectileSource(std::string name, std::string path)
		{
			m_ID = gp::util::hash(name.c_str());
			m_texture.loadFromFile(path);
			m_lifeTimeMax = 1.f; // seconds
			m_speed = 1000.f; // Pixel per seconds
		}

		ProjectileSource::~ProjectileSource()
		{
		}
	}
}