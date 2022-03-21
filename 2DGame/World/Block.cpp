#include "Block.h"

namespace gp
{
	namespace world
	{
		/**
		 * @brief Construct a new Block object
		 * 
		 * @param name Name of the Block
		 * @param path Path of the texture the block should have
		 * @param flags Flags that the block should have
		 */
		Block::Block(std::string name, std::string path, std::map<std::string, int> flags) :
			m_name(name),
			m_flags(flags)
		{
			m_ID = g_blockID; 
			g_blockID++;
			m_texture.loadFromFile(path);
		}

		Block::~Block()
		{
		}
	}
}