#include "Block.h"

namespace gp
{
	namespace world
	{
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