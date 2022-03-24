#include "ProjectileSource.h"

namespace gp
{
	namespace system
	{
		ProjectileSource::ProjectileSource(std::string name, std::string path) :
			gp::system::Source(name, path)
		{
			m_lifeTimeMax = 5.f; // seconds
			m_speed = 1000.f; // Pixel per seconds
		}

		ProjectileSource::~ProjectileSource()
		{
		}
	}
}