#pragma once

#include "Chunk.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

namespace gp
{
	namespace world
	{
		class ManagerWorld
		{
		public:
			ManagerWorld(sf::View* view);
			~ManagerWorld();

			gp::world::Chunk *m_listChunks[g_WORLD_SIZE_X][g_WORLD_SIZE_Y];

			void load(std::string path = "world.uwu");
			void save(std::string path = "world.uwu");

			//Use this for every game logic stuff.
			sf::Vector2i convertWorldPosToBlockPos(sf::Vector2f worldPos);

			// with this function you don't have to think about the underlying chunks (now you can imagine that you access a array).
			uint16_t getBlockIDByBlockPos(sf::Vector2i blockPos);

			// with this function you don't have to think about the underlying chunks (now you can imagine that you access a array).
			void setBlockIDByBlockPos(uint16_t blockID, sf::Vector2i blockPos);

			// technical
			bool removeFromContainer(sf::Vector2i blockPos, gp::object::ObjectBase* obj);

			// technical
			bool addToContainer(sf::Vector2i blockPos, gp::object::ObjectBase* obj);

			std::vector <gp::object::ObjectBase*>* getContainer(sf::Vector2i blockPos);

			//Should not be used for logical stuff, only for technical purposes.
			sf::Vector2i convertBlockPosToChunkPos(sf::Vector2i blockPos);

			//Should not be used for logical stuff, only for technical purposes.
			sf::Vector2i convertBlockPosToLocalBlockPos(sf::Vector2i blockPos);

			static bool isInvalidChunkPos(sf::Vector2i chunkPos) {
				return (chunkPos.x < 0 || chunkPos.x >= g_WORLD_SIZE_X || chunkPos.y < 0 || chunkPos.y >= g_WORLD_SIZE_Y);
			}
		private:
			void create(std::string path = "world.uwu");
		};
	}
}