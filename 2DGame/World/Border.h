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
			Border(std::string path);
			~Border();

			sf::Texture m_texture;
			unsigned int m_ID;

		private:
		};

		static unsigned int g_borderID = 0;
	}
}