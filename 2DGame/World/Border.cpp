#include "Border.h"

namespace gp
{
	namespace world
	{
		Border::Border(std::string name, std::string path) :
			m_name(name)
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