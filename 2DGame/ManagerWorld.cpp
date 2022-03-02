#include "ManagerWorld.h"

namespace gp
{
	namespace world
	{
		ManagerWorld::ManagerWorld(sf::View* view)
		{
			// Fill array with empty chunks so rest only needs to load or overwrite content
			for (int x = 0; x < g_WORLD_SIZE_X; x++)
			{
				for (int y = 0; y < g_WORLD_SIZE_Y; y++)
				{
					auto l_chunk = new gp::world::Chunk(sf::Vector2i(x, y), false);
					m_listChunks[x][y] = l_chunk;
				}
			}

			clock_t start_time = clock();
			load("world.uwu");
			clock_t end_time = clock();
			clock_t result = end_time - start_time;
			printf("World load took %ld clicks (%f seconds).\n", result, ((float)result) / CLOCKS_PER_SEC);
		}

		ManagerWorld::~ManagerWorld()
		{
		}

		void ManagerWorld::create(std::string path)
		{
			for (int x = 0; x < g_WORLD_SIZE_X; x++)
			{
				for (int y = 0; y < g_WORLD_SIZE_Y; y++)
				{
					m_listChunks[x][y]->generate();
				}
			}

			save(path);
		}

		void ManagerWorld::save(std::string path)
		{
			std::ofstream ofs(path, std::ofstream::binary);

			for (int x = 0; x < g_WORLD_SIZE_X; x++)
			{
				for (int y = 0; y < g_WORLD_SIZE_Y; y++)
				{
					m_listChunks[x][y]->save(ofs);
				}
			}

			ofs.close();
		}

		void ManagerWorld::load(std::string path)
		{			
			std::ifstream ifs(path, std::ifstream::binary);
			if (!ifs.is_open())
			{
				// File not found so create new
				create("world.uwu");
				return;
			}

			for (int x = 0; x < g_WORLD_SIZE_X; x++)
			{
				for (int y = 0; y < g_WORLD_SIZE_Y; y++)
				{
					m_listChunks[x][y]->load(ifs);
				}
			}
			ifs.close();
		}

		sf::Vector2i ManagerWorld::convertBlockPosToLocalBlockPos(sf::Vector2i blockPos)
		{
			return sf::Vector2i(
				blockPos.x % g_CHUNK_SIZE,
				blockPos.y % g_CHUNK_SIZE
			);
		}

		sf::Vector2i ManagerWorld::convertWorldPosToBlockPos(sf::Vector2f worldPos)
		{
			return sf::Vector2i(
				floor((float) worldPos.x / g_CHUNK_TEXTURE_SIZE),
				floor((float) worldPos.y / g_CHUNK_TEXTURE_SIZE)
			);
		}

		sf::Vector2i ManagerWorld::convertBlockPosToChunkPos(sf::Vector2i blockPos)
		{
			return sf::Vector2i(
				floor((float) blockPos.x / g_CHUNK_SIZE),
				floor((float) blockPos.y / g_CHUNK_SIZE)
			);
		}

		uint16_t ManagerWorld::getBlockIDByBlockPos(sf::Vector2i blockPos)
		{
			sf::Vector2i l_chunkPos = convertBlockPosToChunkPos(blockPos);

			if (isInvalidChunkPos(l_chunkPos))
			{
				return 0;
			}

			sf::Vector2i l_localBlockPos = convertBlockPosToLocalBlockPos(blockPos);
			return m_listChunks[l_chunkPos.x][l_chunkPos.y]->m_data[l_localBlockPos.x][l_localBlockPos.y];			
		}

		void ManagerWorld::setBlockIDByBlockPos(uint16_t blockID, sf::Vector2i blockPos)
		{
			sf::Vector2i l_chunkPos = convertBlockPosToChunkPos(blockPos);

			if (isInvalidChunkPos(l_chunkPos))
			{
				return;
			}

			sf::Vector2i l_localBlockPos = convertBlockPosToLocalBlockPos(blockPos);
			m_listChunks[l_chunkPos.x][l_chunkPos.y]->m_data[l_localBlockPos.x][l_localBlockPos.y] = blockID;		
		}

		bool ManagerWorld::removeFromContainer(sf::Vector2i blockPos, gp::object::Object* obj)
		{
			sf::Vector2i l_chunkPos = convertBlockPosToChunkPos(blockPos);

			if (isInvalidChunkPos(l_chunkPos))
			{
				return false;
			}

			sf::Vector2i l_localBlockPos = convertBlockPosToLocalBlockPos(blockPos);
			for (auto object = m_listChunks[l_chunkPos.x][l_chunkPos.y]->m_objects[l_localBlockPos.x][l_localBlockPos.y].begin();
				object != m_listChunks[l_chunkPos.x][l_chunkPos.y]->m_objects[l_localBlockPos.x][l_localBlockPos.y].end();
				object++) 
			{
				if ((*object) == obj)
				{
					object = m_listChunks[l_chunkPos.x][l_chunkPos.y]->m_objects[l_localBlockPos.x][l_localBlockPos.y].erase(object);
					return true;
				}
			}
			return false;
		}

		bool ManagerWorld::addToContainer(sf::Vector2i blockPos, gp::object::Object* obj)
		{
			sf::Vector2i l_chunkPos = convertBlockPosToChunkPos(blockPos);

			if (isInvalidChunkPos(l_chunkPos))
			{
				return false;
			}

			sf::Vector2i l_localBlockPos = convertBlockPosToLocalBlockPos(blockPos);
			m_listChunks[l_chunkPos.x][l_chunkPos.y]->m_objects[l_localBlockPos.x][l_localBlockPos.y].push_back(obj);
			return true;
		}

		std::vector<gp::object::Object*>* ManagerWorld::getContainer(sf::Vector2i blockPos)
		{
			sf::Vector2i l_chunkPos = convertBlockPosToChunkPos(blockPos);

			if (isInvalidChunkPos(l_chunkPos))
			{
				return nullptr;
			}

			sf::Vector2i l_localBlockPos = convertBlockPosToLocalBlockPos(blockPos);
			return &m_listChunks[l_chunkPos.x][l_chunkPos.y]->m_objects[l_localBlockPos.x][l_localBlockPos.y];
		}
	}
}