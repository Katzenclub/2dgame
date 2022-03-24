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

			unsigned int m_ID;

			sf::Vector2f m_PositionTexture;
			sf::Vector2f m_SizeTexture;

			std::map<std::string, int> m_flags;
		private:
		};

		static unsigned int g_blockID = 0;
	}
}