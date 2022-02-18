#pragma once

#include "Chunk.h"

#include <stdio.h>
#include <string>
#include <fstream>

namespace gp
{
	namespace world
	{
		class ManagerWorld
		{
		public:
			ManagerWorld(sf::View *view);
			~ManagerWorld();

			std::vector<gp::world::Chunk*> m_listChunks;
			void load(std::string path);

		private:
			void save(std::string path);
			void create(std::string path);
		};
	}
}