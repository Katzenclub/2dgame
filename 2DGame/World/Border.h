#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

#include <iostream>

namespace gp
{
	namespace world
	{
		class Border
		{
		public:
			Border(std::string name, std::string path);
			~Border();

			std::string m_name;
			sf::Texture m_texture;
			unsigned int m_ID;

		private:
		};

		static unsigned int g_borderID = 0;
	}
}