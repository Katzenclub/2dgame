#pragma once

#include <string>
#include "../World/WorldConstants.h"

#include "GuillotineBinPack.h"
#include "../World/Block.h"
#include "../Object/ObjectAsset.h"
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
			std::vector<gp::world::Block*> m_listBlocks;
			std::vector<gp::object::ObjectAsset*> m_listObjectAssets;
			std::vector<gp::system::ProjectileSource*> m_listProjectiles;

			gp::system::ProjectileSource* getProjectileByName(const std::string& name);

		private:

			sf::Texture createTextureAtlas(const std::vector<gp::world::Block*>& list);
			sf::Texture createTextureAtlas(const std::vector<gp::object::ObjectAsset*>& list);
			sf::Texture createTextureAtlas(const std::vector<gp::system::ProjectileSource*>& list);
			sf::Texture createTextureAtlas(std::vector<RectInfo> &list);
			
		};
	}
}