#pragma once

#include <string>
#include "../World/WorldConstants.h"

#include "GuillotineBinPack.h"
#include "../World/BlockSource.h"
#include "../Object/ObjectSource.h"
#include "../Projectile/ProjectileSource.h"

namespace gp
{
	namespace system
	{
		class Loader
		{
		public:
			Loader();
			~Loader();
			
			sf::Texture m_textureAtlas;
			sf::Texture m_objectsAtlas;
			sf::Texture m_projectileAtlas;
			std::vector<gp::world::BlockSource*> m_listBlocks;
			std::vector<gp::object::ObjectSource*> m_listObjectAssets;
			std::vector<gp::system::ProjectileSource*> m_listProjectiles;

			gp::system::ProjectileSource* getProjectileByName(const std::string& name);

		private:
			sf::Texture createTextureAtlas(const std::vector<gp::world::BlockSource*>& list);
			sf::Texture createTextureAtlas(const std::vector<gp::object::ObjectSource*>& list);
			sf::Texture createTextureAtlas(const std::vector<gp::system::ProjectileSource*>& list);
			sf::Texture createTextureAtlas(std::vector<RectInfo> &list);
					
		};
	}
}