#pragma once

#include <string>
#include <SFML/Graphics.hpp>

namespace gp
{
	namespace object
	{
		class ObjectAsset
		{
		public:
			ObjectAsset(std::string name, std::string path);
			~ObjectAsset();

			std::string m_name;
			sf::Texture m_texture;

			unsigned int m_ID;

			sf::Vector2f m_PositionTexture;
			sf::Vector2f m_SizeTexture;

		private:

		};

		static unsigned int g_objectAssetID = 0;
	}
}