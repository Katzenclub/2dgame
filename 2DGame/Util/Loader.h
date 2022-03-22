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
			std::vector<gp::object::ObjectAsset*> m_listObjectAssets;

			gp::world::ManagerBorder m_managerBorder;
		private:

			sf::Texture createTextureAtlas(const std::vector<gp::world::Block*>& list);
			sf::Texture createBorderAtlas();
			sf::Texture createTextureAtlas(const std::vector<gp::object::ObjectAsset*>& list);

			std::vector<gp::world::Block*> m_listBlocks;
			std::vector<gp::world::Border*> m_listBorders;
			
			void addBlock(std::string borderFolder, int blockID);
		};

		
	}
}