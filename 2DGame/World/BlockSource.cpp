#include "BlockSource.h"

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
		BlockSource::BlockSource(std::string name, std::string path, std::map<std::string, int> flags) :
			gp::system::Source(name, path),
			m_flags(flags)
		{
			m_IDBlock = g_blockID;
			g_blockID++;

			// Override texture size for blocks;
			m_SizeTexture = sf::Vector2f(g_CHUNK_TEXTURE_SIZE,g_CHUNK_TEXTURE_SIZE);
		}

		BlockSource::~BlockSource()
		{
		}
	}
}