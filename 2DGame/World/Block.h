#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

#include <iostream>

namespace gp
{
	namespace world
	{
		class Block
		{
		public:
			Block(std::string name, std::string path, std::map<std::string, int> flags);
			~Block();

			std::string m_name;
			sf::Texture m_texture;
			std::map<std::string, int> m_flags;

			unsigned int m_ID;

		private:
		};

		static unsigned int g_blockID = 0;
	}
}