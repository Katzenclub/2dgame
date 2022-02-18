#include "ManagerWorld.h"

namespace gp
{
	namespace world
	{
		ManagerWorld::ManagerWorld(sf::View *view)
		{
			clock_t start_time = clock();
			load("world.uwu");
			clock_t end_time = clock();
			clock_t result = end_time - start_time;
			printf ("World load took %ld clicks (%f seconds).\n",result,((float)result)/CLOCKS_PER_SEC);
		}

		ManagerWorld::~ManagerWorld()
		{
		}

		void ManagerWorld::create(std::string path)
		{
			if (m_listChunks.size() == 0)
			{
				for (int y = 0; y < g_WORLD_SIZE_Y; y++)
				{
					for (int x = 0; x < g_WORLD_SIZE_X; x++)
					{
						auto l_chunk = new gp::world::Chunk(sf::Vector2i(x, y));
						m_listChunks.push_back(l_chunk);
					}
				}
			}

			save(path);
		}

		void ManagerWorld::save(std::string path)
		{
			std::ofstream ofs(path, std::ofstream::binary);

			for (auto &chunk : m_listChunks)
			{
				chunk->save(ofs);
			}

			ofs.close();
		}

		void ManagerWorld::load(std::string path)
		{
			// delete old chunks if any exist
			if (m_listChunks.size() == 0)
			{
				for (std::vector<gp::world::Chunk *>::iterator it = m_listChunks.begin(); it != m_listChunks.end(); ++it)
				{
					delete (*it);
					it = m_listChunks.erase(it);
					it--;
				}
			}

			std::ifstream ifs(path, std::ifstream::binary);
			if (!ifs.is_open())
			{
				// File not found so create new
				create("world.uwu");
				return;
			}

			for (int y = 0; y < g_WORLD_SIZE_Y; y++)
			{
				for (int x = 0; x < g_WORLD_SIZE_X; x++)
				{
					auto l_chunk = new gp::world::Chunk(sf::Vector2i(x, y), false);
					l_chunk->load(ifs);
					m_listChunks.push_back(l_chunk);
				}
			}
			ifs.close();
		}
	}
}