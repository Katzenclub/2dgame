#pragma once

// STL
#include <string>

// SFML
#include "SFML/Graphics.hpp"

// Own
#include "../Util/Utils.h"
#include "../World/WorldConstants.h"

namespace gp
{
	namespace system
	{
		/**
		 * @brief This class is useful to avoid duplicated code.
		 */
		class Source
		{
		public:
			Source(std::string name, std::string path);
			~Source();

			// Render Stuff
			sf::Vector2f m_PositionTexture;
			sf::Vector2f m_SizeTexture;

			// Media Stuff
			sf::Texture m_texture;

			// Access Stuff
			std::string m_name;
			size_t m_ID;		
		};
	}
}