#include "Border.h"

namespace gp
{
	namespace world
	{
		Border::Border(std::string path)
		{
			m_ID = g_borderID; 
			g_borderID++;
			m_texture.loadFromFile(path);
		}

		Border::~Border()
		{
		}
	}
}