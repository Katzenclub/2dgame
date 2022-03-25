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

			/**
			 * @brief converts vectors of all specified sources to vectors of the original sources.
			 * To keep the code simple and usefull, the function is declared in header file.
			 * (Info) This function will be specified by the compiler at compile time, no additional
			 * runtime calculations.
			 * 
			 * @param specifiedSources Is a vector of inherited sources. 
			 * @return std::vector<gp::system::Source*> Is a vector of sources.
			 */
			template <class T>
			static std::vector<gp::system::Source*> tranformToSource(std::vector<T*> specifiedSources)
			{
				std::vector<gp::system::Source*> l_source;
				for (auto it : specifiedSources)
				{
					l_source.push_back(it);
				}
				return l_source;
			}

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