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
					auto l_chunk = new gp::world::Chunk(sf::Vector2i(x, y));
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

		/**
		 * @brief Create the world by filling the Chunks with data and then save it
		 * 
		 * @param path Path of the file to save the world to
		 */
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

		/**
		 * @brief Save the world to a file
		 * 
		 * @param path Path of the file to save the world to
		 */
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

		/**
		 * @brief Load the world from a file
		 * 
		 * @param path Path of the file to load the world from
		 */
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

		/**
		 * @brief Convert x and y index of a Block to the local indexes
		 * inside the corresponding chunk
		 * 
		 * @param blockPos Vector with the indexes of the block in the world
		 * @return sf::Vector2i Vector for the indexes inside the chunk
		 */
		sf::Vector2i ManagerWorld::convertBlockPosToLocalBlockPos(sf::Vector2i blockPos)
		{
			return sf::Vector2i(
				blockPos.x % g_CHUNK_SIZE,
				blockPos.y % g_CHUNK_SIZE
			);
		}

		/**
		 * @brief Convert x and y coordinates into the indexes of the block
		 * that contains them
		 * 
		 * @param worldPos Vector with the coordinates in the world
		 * @return sf::Vector2i Vector for the indexes of the block
		 */
		sf::Vector2i ManagerWorld::convertWorldPosToBlockPos(sf::Vector2f worldPos)
		{
			return sf::Vector2i(
				floor((float) worldPos.x / g_CHUNK_TEXTURE_SIZE),
				floor((float) worldPos.y / g_CHUNK_TEXTURE_SIZE)
			);
		}

		/**
		 * @brief Convert x and y indexes of block to the ID of the chunk
		 * in which the block is
		 * 
		 * @param blockPos Vector with the indexes of the block
		 * @return sf::Vector2i Vector with the x and y ID of the Chunk
		 */
		sf::Vector2i ManagerWorld::convertBlockPosToChunkPos(sf::Vector2i blockPos)
		{
			return sf::Vector2i(
				floor((float) blockPos.x / g_CHUNK_SIZE),
				floor((float) blockPos.y / g_CHUNK_SIZE)
			);
		}

		/**
		 * @brief Gets the ID of the block at the given position
		 * 
		 * @param blockPos Indexes of the Block
		 * @return uint16_t ID of the Block 
		 */
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

		/**
		 * @brief Set the BlockID at the given position
		 * 
		 * @param blockID BlockID to set to
		 * @param blockPos Indexes of the Block
		 */
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

		/**
		 * @brief Remove a Object from it's container
		 * 
		 * @param blockPos Indexes of the block that the object is in
		 * @param obj Object to remove from the container
		 * @return true The object was removed sucessfully
		 * @return false The position was invalid or the object was not found in the container
		 */
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

		/**
		 * @brief Add a Object to a container
		 * 
		 * @param blockPos Indexes of the block that the object is in
		 * @param obj Object to add to the container
		 * @return true The object was sucessfully added
		 * @return false The position was invalid
		 */
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

		/**
		 * @brief Get the container at the given position
		 * 
		 * @param blockPos Indexes of the block / the container to get
		 * @return std::vector<gp::object::Object*>* 
		 */
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