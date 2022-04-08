#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "../World/WorldConstants.h"

#include "GuillotineBinPack.h"
#include "../World/Block.h"
#include "../World/Border.h"
#include "../World/ManagerBorder.h"
#include "../Object/ObjectAsset.h"
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
			sf::Texture m_borderAtlas;
			sf::Texture m_objectsAtlas;
			sf::Texture m_projectileAtlas;
			std::vector<gp::world::BlockSource*> m_listBlocks;
			std::vector<gp::object::ObjectSource*> m_listObjectAssets;
			std::vector<gp::system::ProjectileSource*> m_listProjectiles;

			gp::system::ProjectileSource* getProjectileByName(const std::string& name);

			gp::world::ManagerBorder m_managerBorder;
		private:
	
			sf::Texture createBorderAtlas();
			std::vector<gp::world::Border*> m_listBorders;
			void addBlock(std::string borderFolder, int blockID);
			sf::Texture createTextureAtlas(const std::vector<gp::system::Source*>& list);
			sf::Texture createTextureAtlas(std::vector<RectInfo> &list);

		};
	}
}