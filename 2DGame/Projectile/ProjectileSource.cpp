#include "ProjectileSource.h"

namespace gp
{
	namespace system
	{
		ProjectileSource::ProjectileSource(std::string name, std::string path, float lifeTimeMax, float speed, float damage) :
			gp::system::Source(name, path),
			m_lifeTimeMax(lifeTimeMax),
			m_speed(speed),
			m_damage(damage)
		{
		}

		ProjectileSource::~ProjectileSource()
		{
		}
	}
}